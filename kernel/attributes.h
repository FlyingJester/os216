#pragma once

#ifndef OS216_LIKELY
  #ifdef __GNUC__
    #define OS216_LIKELY(X) __builtin_expect(!!(X), 1)
  #else
    #define OS216_LIKELY(X) (!!(X))
  #endif
#endif

#ifndef OS216_UNLIKELY
  #ifdef __GNUC__
    #define OS216_UNLIKELY(X) __builtin_expect(!!(X), 0)
  #else
    #define OS216_UNLIKELY(X) (!!(X))
  #endif
#endif

#ifndef OS216_COLD
  #ifdef __GNUC__
    #define OS216_COLD __attribute__((cold))
  #else
    #define OS216_COLD
  #endif
#endif

#ifndef OS216_NORETURN
  #ifdef __GNUC__
    #define OS216_NORETURN __attribute__((noreturn,cold))
  #elif defined _MSC_VER_
    #define OS216_NORETURN __declspec(noreturn)
  #endif
#endif

#ifndef OS216_PURE
  #ifdef __GNUC__
    #define OS216_PURE __attribute__((pure))
  #elif defined _MSC_VER_
    #define OS216_PURE
  #endif
#endif

#ifndef OS216_MEMORY_PURE
  #ifdef __GNUC__
    #define OS216_MEMORY_PURE __attribute__((const))
  #elif defined _MSC_VER_
    #define OS216_MEMORY_PURE
  #endif
#endif

#ifndef OS216_MALLOC_ATTR
  #ifdef __GNUC__
    #define OS216_MALLOC_ATTR __attribute__((malloc,returns_nonnull,warn_unused_result))
  #else
    #define OS216_MALLOC_ATTR __declspec(restrict)
  #endif
#endif

#ifndef OS216_WARN_UNUSED_RESULT
  #ifdef __GNUC__
    #define OS216_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
  #else
    #define OS216_WARN_UNUSED_RESULT
  #endif
#endif

#if defined __cplusplus
    #if __cplusplus < 201103L
        #define OS216_CONSTEXPR_CONSTRUCTOR
        #define OS216_CONSTEXPR_FUNC OS216_MEMORY_PURE
        #define OS216_CONSTEXPR_VALUE const
    #else
        #define OS216_CONSTEXPR_CONSTRUCTOR constexpr
        #define OS216_CONSTEXPR_FUNC OS216_MEMORY_PURE constexpr
        #define OS216_CONSTEXPR_VALUE constexpr
    #endif
    #if __cplusplus >= 201103L
        #define OS216_OVERRIDE override
        #define OS216_FINAL final
    #elif  defined _MSC_VER && _MSC_VER >= 1700
        #define OS216_OVERRIDE override
        #define OS216_FINAL sealed
    #else
        #define OS216_OVERRIDE
        #define OS216_FINAL
    #endif
#endif
