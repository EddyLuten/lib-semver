// TEST: validates that versions structs are created properly with meta data.

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/semver.h"

#define VERSION_STRING "1.0.255-alpha.1+build-6784"
#define VERSION_STRING_PRE_RELEASE "alpha.1"
#define VERSION_STRING_BUILD_INFO "build-6784"

int main(void)
{
  SemVer* ver1;
  SemVer* ver2;
  int result;

  semver_config(NULL, NULL, NULL, stdout);

  ver1 = semver_parse(VERSION_STRING);
  // First, validate the parsed string
  assert(NULL != ver1);
  assert(1u == ver1->major);
  assert(0u == ver1->minor);
  assert(255u == ver1->patch);

  // Create the second string with the data from the first
  ver2 = semver_create(ver1->major, ver1->minor, ver1->patch);
  assert(1u == ver2->major);
  assert(0u == ver2->minor);
  assert(255u == ver2->patch);

  assert(NULL != ver2);
  if (!semver_add_pre_release_component(&ver2, VERSION_STRING_PRE_RELEASE))
  {
    printf("TEST create-meta: could not set pre-release info.\n");
    return EXIT_FAILURE;
  }

  if (!semver_add_build_info_component(&ver2, VERSION_STRING_BUILD_INFO))
  {
    printf("TEST create-meta: could not set build info.\n");
    return EXIT_FAILURE;
  }

  assert(2u == ver2->pre_release_elements);
  assert(0 == strcmp("alpha", ver2->pre_release[0]));
  assert(0 == strcmp("1", ver2->pre_release[1]));
  assert(0 == strcmp(VERSION_STRING_BUILD_INFO, ver2->build_info));

  assert(0 == (result = semver_compare(ver1, ver2)));

  semver_destroy(ver1);
  semver_destroy(ver2);

  return 0 == result ? EXIT_SUCCESS : EXIT_FAILURE;
}
