## lib-semver ##

A C library for parsing version numbers according to the Semantic Versioning
2.0.0 specification.

The specification is available at:
[http://semver.org/spec/v2.0.0.html](http://semver.org/spec/v2.0.0.html)

Must be compiled using a compiler that supports the C99 standard.

## Installation ##

Simply add the `source/semver.c` file to your project and make the
`include/semver.h` file available in your include path.

## API ##

Consult the documentation in [the `docs` directory](./docs/).

## Tests ##

Run `run-tests.sh` from the `tests` directory to perform some simple sanity
checks on the library. Change the variables in `Makefile` to fit your
environment before running the tests.

## License ##

Licensed under the MIT License, see the [`LICENSE`](./LICENSE) file for
details.
