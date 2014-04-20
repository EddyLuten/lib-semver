// TEST: verifies that custom allocators can be used.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/semver.h"

// Used to make sure that the custom allocators are called
size_t total_memory = 0;

// Some custom allocators
void* my_malloc(size_t size)
{
  total_memory += size;
  return malloc(size);
}

void* my_realloc(void* memory, size_t size)
{
  total_memory += size;
  return realloc(memory, size);
}

void my_free(void* mem)
{
  free(mem);
}

int main(void)
{
  semver_config(my_malloc, my_realloc, my_free, stderr);

  SemVer* semver = semver_parse("1.0.0-alpha+build.7621");
  assert(NULL != semver);

  char* version_string = semver_to_string(semver);
  assert(NULL != version_string);

  free(version_string);
  semver_destroy(semver);

  printf("TEST custom-allocators: %lu bytes handled.\n", total_memory);
  return 0 == total_memory ? EXIT_FAILURE : EXIT_SUCCESS;
}
