# lib-semver API Documentation #

The following file documents the API calls available in lib-semver.

## Preprocessor Symbols ##

`LIB_SEMVER_VERSION` Contains the version of the lib-semver library.

## Data Structures and Types ##

```semver_malloc_fnc``` Function pointer typedef used by `semver_config`,
evaluates to a function with the same signature as `malloc`.

```semver_realloc_fnc``` Function pointer typedef used by `semver_config`,
evaluates to a function with the same signature as `realloc`.

```semver_free_fnc``` Function pointer typedef used by `semver_config`,
evaluates to a function with the same signature as `free`.

### SemVer ###

```C
typedef struct _SemVer
{
  uint64_t major;
  uint64_t minor;
  uint64_t patch;
  uint64_t pre_release_elements;
  char** pre_release;
  char* build_info;
} SemVer;
```

`SemVer` contains all of the components of a semantic version. Consider
the struct as read-only and only modify it using the lib-semver API. Changes
made to the `pre_release` and `build_info` members could prove catastrophic to
memory deallocation.

`major`, `minor`, and `patch` contain the three required components of the
semantic version. The sum of the three components *must* be greater than zero.

`pre_release_elements` contains the count of elements contained in the
`pre_release` array. Each element in the `pre_release` array is one of the
dot-separated components of the pre-release version component. `pre_release` is
an optional member, and may be set to `NULL`. If it *is* set to `NULL`,
`pre_release_elements` will be set to zero.

`build_info` contains the optional build-information string component of the
semantic version. This is a null-terminated string and may be `NULL` since it's
also an optional member.

## Functions ##

### semver_config ###

```C
void semver_config(void* (*custom_malloc)(size_t),
                   void* (*custom_realloc)(void*, size_t),
                   void  (*custom_free)(void*),
                   FILE* debug_output);
```

Allows for the optional usage of a custom memory allocator/deallocator and
provides a method of providing a file-stream to which lib-semver can write
debug information.

If a custom allocator is passed into the `custom_malloc` argument, a custom
`realloc`, and `free` *must* be provided as well in the subsequent parameters.
If `NULL` is passed into these parameters, lib-semver will use the memory
management routines provided in the C standard library's `stdlib.h` file.

If the parameter `debug_output` is assigned with a valid file stream,
lib-semver will write debug information to the file *only* if NDEBUG is not
defined. lib-semver does not output debug information by default.

Once again, this function is optional and should only be
used if either a custom allocator is required or while debugging.

### semver_parse ###

```C
SemVer* semver_parse(const char* string);
```

Parses a null-terminated character string and returns the contained semantic
version through a pointer to a `SemVer` struct. The function returns `NULL` on
failure. The returned struct must be destroyed by providing it as the parameter
to `semver_destroy`.

### semver_create ###

```C
SemVer* semver_create(uint64_t major, uint64_t minor, uint64_t patch);
```

Creates an instance of a `SemVer` struct containing the required major, minor,
and patch components provided as arguments. Returns `NULL` on failure.

### semver_add_pre_release_component ###

```C
bool semver_add_pre_release_component(SemVer** version, const char* component);
```

Parses the null-terminated string provided in the `component` argument and
populates the `pre_release` member of the `version` argument. If the
`pre_release` member is already set in `version`, the function will deallocate
and overwrite its contents. Returns `true` on success, `false` on failure.

### semver_add_build_info_component ###

```C
bool semver_add_build_info_component(SemVer** version, const char* component);
```

Parses the null-terminated string provided in the `component` argument and
populates the `build_info` member of the `version` argument. If the
`build_info` member is already set in `version`, the function will deallocate
and overwrite its contents. Returns `true` on success, `false` on failure.

### semver_destroy ###

```C
void semver_destroy(SemVer* version);
```
Frees a `SemVer` structure allocated by lib-semver. The contents of the memor
pointed to by the pointer are undefined after this function executes.

### semver_to_string ###

```C
char* semver_to_string(SemVer* version);
```

Converts a SemVer structure into its string representation, or `NULL` on
failure. The string returned must be freed using the custom `free()` function
provided in the `semver_config()` function or the  `free()` function defined in
the C standard library's `stdlib.h` file if `semver_config()` was not called.

### semver_compare ###

```C
int semver_compare(SemVer* a, SemVer* b);
```

Compares two version instances. Returns 0 if `a` and `b` are equal, a value
less than 0 if `a` is less than `b`, a value greater than 0 if `a` is greater
than `b`.

### semver_is_stable ###

```C
int semver_is_stable(SemVer* version);
```

Returns 1 if the version is stable, 0 if not, and -1 if an invalid argument was
provided.

