// TEST: validates that versions structs are created properly.

#include <stdlib.h>
#include <assert.h>
#include "../include/semver.h"

#define MAJOR 0u
#define MINOR 255u
#define PATCH 345678u

int main(void)
{
  SemVer* version = semver_create(MAJOR, MINOR, PATCH);

  assert(MAJOR == version->major);
  assert(MINOR == version->minor);
  assert(PATCH == version->patch);
  
  semver_destroy(version);
  return EXIT_SUCCESS;
}
