// TEST: verifies the validity of the version string passed in as an argument.

#include <stdlib.h>
#include <stdio.h>
#include "../include/semver.h"

int main(int argc, const char* argv[])
{
  int result;
  struct SemVer* version;
  int test_truth;

  if (argc != 3)
  {
    printf("TEST simple-parse: Not enough arguments provided.\n");
    return EXIT_FAILURE;
  }

  test_truth = *argv[1] == '1' ? 1 : 0;

  semver_config(NULL, NULL, NULL, stderr);

  printf("TEST simple-parse: testing version string \"%s\" (should %s)\n",
         argv[2], test_truth ? "pass" : "fail");
  version = semver_parse(argv[2]);

  result = NULL == version ? EXIT_FAILURE : EXIT_SUCCESS;
  if (!test_truth)
    result = EXIT_FAILURE == result ? EXIT_SUCCESS : EXIT_FAILURE;
  semver_destroy(version);

  return result;
}