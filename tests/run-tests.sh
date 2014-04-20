#!/bin/bash
set -e

valgrind_run() {
	valgrind --leak-check=full --show-leak-kinds=definite --error-exitcode=1 --dsymutil=yes -q $@
}

setup() {
	set +e
	scan-build -h > /dev/null
	if [ $? -ne 0 ] ; then
		echo "Clang static analyzer not installed."
		exit $?
	fi

	valgrind --version > /dev/null
	if [ $? -ne 0 ] ; then
		echo "Valgrind not installed."
		echo $?
	fi

	set -e
	make clean > /dev/null
	echo "BUILDING TESTS"
	scan-build -v make all
}

cleanup() {
	if [ $? -ne 0 ] ; then
		echo "FAILED"
	else
		echo "OK"
	fi
	make clean > /dev/null
}

run() {
	echo "RUNNING TESTS"
	valgrind_run ./build/custom-allocators

	# test simple parsing of version strings
	# format of string "n version\n"
	# n: 0 or 1, indicates if the test should fail or pass
	while read version
	do
		valgrind_run ./build/simple-parse $version
	done < ./versions.txt

	# test the comparision functionality
	# format of string "version op version"
	# op: <, >, or = operator used in the test
	while read comparison
	do
		valgrind_run ./build/compare $comparison
	done < ./compare.txt
}

trap cleanup EXIT
setup
run
