// TEST: compares two versions based on an operator.

#include <stdlib.h>
#include <stdio.h>
#include "../include/semver.h"

int main(int argc, const char* argv[])
{
  char comparator;
  struct SemVer* v1;
  struct SemVer* v2;
  int compare_result;

  if (4 != argc)
  {
    printf("TEST compare: Not enough arguments provided.\n");
    return EXIT_FAILURE;
  }

  comparator = *argv[2];

  semver_config(NULL, NULL, NULL, stderr);

  v1 = semver_parse(argv[1]);
  if (NULL == v1)
  {
    printf("TEST compare: could not parse version string \"%s\"\n", argv[1]);
    return EXIT_FAILURE;
  }

  v2 = semver_parse(argv[3]);
  if (NULL == v2)
  {
    printf("TEST compare: could not parse version string \"%s\"\n", argv[3]);
    return EXIT_FAILURE;
  }

  printf("TEST compare: %s %c %s\n", argv[1], comparator, argv[3]);
  compare_result = semver_compare(v1, v2);

  semver_destroy(v1);
  semver_destroy(v2);

  switch (comparator)
  {
    case '<':
      return compare_result < 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    case  '>':
      return compare_result > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    case '=':
      return compare_result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    default:
      printf("Unknown comparator %c\n", comparator);
      return EXIT_FAILURE;
  }
}
