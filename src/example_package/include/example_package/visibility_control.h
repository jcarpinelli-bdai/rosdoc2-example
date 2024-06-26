#ifndef EXAMPLE_PACKAGE__VISIBILITY_CONTROL_H_
#define EXAMPLE_PACKAGE__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define EXAMPLE_PACKAGE_EXPORT __attribute__ ((dllexport))
    #define EXAMPLE_PACKAGE_IMPORT __attribute__ ((dllimport))
  #else
    #define EXAMPLE_PACKAGE_EXPORT __declspec(dllexport)
    #define EXAMPLE_PACKAGE_IMPORT __declspec(dllimport)
  #endif
  #ifdef EXAMPLE_PACKAGE_BUILDING_LIBRARY
    #define EXAMPLE_PACKAGE_PUBLIC EXAMPLE_PACKAGE_EXPORT
  #else
    #define EXAMPLE_PACKAGE_PUBLIC EXAMPLE_PACKAGE_IMPORT
  #endif
  #define EXAMPLE_PACKAGE_PUBLIC_TYPE EXAMPLE_PACKAGE_PUBLIC
  #define EXAMPLE_PACKAGE_LOCAL
#else
  #define EXAMPLE_PACKAGE_EXPORT __attribute__ ((visibility("default")))
  #define EXAMPLE_PACKAGE_IMPORT
  #if __GNUC__ >= 4
    #define EXAMPLE_PACKAGE_PUBLIC __attribute__ ((visibility("default")))
    #define EXAMPLE_PACKAGE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define EXAMPLE_PACKAGE_PUBLIC
    #define EXAMPLE_PACKAGE_LOCAL
  #endif
  #define EXAMPLE_PACKAGE_PUBLIC_TYPE
#endif

#endif  // EXAMPLE_PACKAGE__VISIBILITY_CONTROL_H_
