// TEST: validates that semver_to_string is working correctly.

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/semver.h"

int main(int argc, const char* argv[])
{
  if (2 != argc)
  {
    printf("TEST to-string: Not enough arguments\n");
    return EXIT_FAILURE;
  }

  char* s;
  SemVer* version = semver_parse(argv[1]);
  assert(NULL != version);

  s = semver_to_string(version);
  printf("TEST to-string:  in: \"%s\"\n", argv[1]);
  printf("TEST to-string: out: \"%s\"\n", s);
  assert(NULL != s);
  assert(0 == strcmp(argv[1], s));

  free(s);
  semver_destroy(version);
  return EXIT_SUCCESS;
}
