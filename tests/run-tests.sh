#!/bin/bash
set -e

setup() {
	make clean > /dev/null
	echo "BUILDING TESTS"
	make all
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
	./build/custom-allocators

	# test simple parsing of version strings
	# format of string "n version\n"
	# n: 0 or 1, indicates if the test should fail or pass
	while read version
	do
		./build/simple-parse $version
	done < ./versions.txt

	# test the comparision functionality
	# format of string "version op version"
	# op: <, >, or = operator used in the test
	while read comparison
	do
		./build/compare $comparison
	done < ./compare.txt
}

trap cleanup EXIT
setup
run
