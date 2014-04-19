// Copyright (c) 2014 Eddy Luten - https://github.com/EddyLuten/lib-semver
// Distributed under MIT license.
#ifndef LIB_SEMVER_H
#define LIB_SEMVER_H
#include <stdint.h> // for uint64_t support
#include <stdio.h> // for FILE struct

#define LIB_SEMVER_VERSION "0.0.1-alpha"

struct SemVer
{
  uint64_t major;
  uint64_t minor;
  uint64_t patch;
  uint64_t pre_release_elements;
  char** pre_release;
  char* build_info;
};

void semver_config(void* (*custom_malloc)(size_t),
                   void* (*custom_realloc)(void*, size_t),
                   void  (*custom_free)(void*),
                   FILE* debug_output);
struct SemVer* semver_parse(const char* string);
void semver_destroy(struct SemVer* version);
char* semver_to_string(struct SemVer* version);
int semver_compare(struct SemVer* a, struct SemVer* b);
int semver_is_stable(struct SemVer* version);

#endif
