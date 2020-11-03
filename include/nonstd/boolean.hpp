//
// Copyright (c) 2020-2020 Martin Moene
//
// https://github.com/martinmoene/boolean-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// boolean-lite is inspired on the article
// "Fun with Concepts: Do You Even Lift, Bool?" by Colby Pike (vector-of-bool), Oct 26, 2020.
// https://vector-of-bool.github.io/2020/10/26/strong-bool.html

// The name boolean_ is used to prevent clashing with boolean from the Windows SDK (rpcndr.h(193))

#ifndef NONSTD_BOOLEAN_LITE_HPP
#define NONSTD_BOOLEAN_LITE_HPP

#define boolean_lite_MAJOR  0
#define boolean_lite_MINOR  1
#define boolean_lite_PATCH  0

#define boolean_lite_VERSION  boolean_STRINGIFY(boolean_lite_MAJOR) "." boolean_STRINGIFY(boolean_lite_MINOR) "." boolean_STRINGIFY(boolean_lite_PATCH)

#define boolean_STRINGIFY(  x )  boolean_STRINGIFY_( x )
#define boolean_STRINGIFY_( x )  #x

// tweak header support:

#ifdef __has_include
# if __has_include(<nonstd/boolean.tweak.hpp>)
#  include <nonstd/boolean.tweak.hpp>
# endif
#define boolean_HAVE_TWEAK_HEADER  1
#else
#define boolean_HAVE_TWEAK_HEADER  0
//# pragma message("boolean.hpp: Note: Tweak header not supported.")
#endif

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   boolean_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define boolean_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define boolean_CPLUSPLUS  __cplusplus
# endif
#endif

#define boolean_CPP98_OR_GREATER  ( boolean_CPLUSPLUS >= 199711L )
#define boolean_CPP11_OR_GREATER  ( boolean_CPLUSPLUS >= 201103L )
#define boolean_CPP14_OR_GREATER  ( boolean_CPLUSPLUS >= 201402L )
#define boolean_CPP17_OR_GREATER  ( boolean_CPLUSPLUS >= 201703L )
#define boolean_CPP20_OR_GREATER  ( boolean_CPLUSPLUS >= 202000L )

// C++ language version (represent 98 as 3):

#define boolean_CPLUSPLUS_V  ( boolean_CPLUSPLUS / 100 - (boolean_CPLUSPLUS > 200000 ? 2000 : 1994) )

// half-open range [lo..hi):
#define boolean_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Compiler versions:

// MSVC++  6.0  _MSC_VER == 1200  boolean_COMPILER_MSVC_VERSION ==  60  (Visual Studio 6.0)
// MSVC++  7.0  _MSC_VER == 1300  boolean_COMPILER_MSVC_VERSION ==  70  (Visual Studio .NET 2002)
// MSVC++  7.1  _MSC_VER == 1310  boolean_COMPILER_MSVC_VERSION ==  71  (Visual Studio .NET 2003)
// MSVC++  8.0  _MSC_VER == 1400  boolean_COMPILER_MSVC_VERSION ==  80  (Visual Studio 2005)
// MSVC++  9.0  _MSC_VER == 1500  boolean_COMPILER_MSVC_VERSION ==  90  (Visual Studio 2008)
// MSVC++ 10.0  _MSC_VER == 1600  boolean_COMPILER_MSVC_VERSION == 100  (Visual Studio 2010)
// MSVC++ 11.0  _MSC_VER == 1700  boolean_COMPILER_MSVC_VERSION == 110  (Visual Studio 2012)
// MSVC++ 12.0  _MSC_VER == 1800  boolean_COMPILER_MSVC_VERSION == 120  (Visual Studio 2013)
// MSVC++ 14.0  _MSC_VER == 1900  boolean_COMPILER_MSVC_VERSION == 140  (Visual Studio 2015)
// MSVC++ 14.1  _MSC_VER >= 1910  boolean_COMPILER_MSVC_VERSION == 141  (Visual Studio 2017)
// MSVC++ 14.2  _MSC_VER >= 1920  boolean_COMPILER_MSVC_VERSION == 142  (Visual Studio 2019)

#if defined(_MSC_VER ) && !defined(__clang__)
# define boolean_COMPILER_MSVC_VER           (_MSC_VER )
# define boolean_COMPILER_MSVC_VERSION       (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
# define boolean_COMPILER_MSVC_VERSION_FULL  (_MSC_VER - 100 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define boolean_COMPILER_MSVC_VER           0
# define boolean_COMPILER_MSVC_VERSION       0
# define boolean_COMPILER_MSVC_VERSION_FULL  0
#endif

#define boolean_COMPILER_VERSION( major, minor, patch ) ( 10 * ( 10 * (major) + (minor) ) + (patch) )

// AppleClang  7.0.0  __apple_build_version__ ==  7000172  boolean_COMPILER_APPLECLANG_VERSION ==  700  (Xcode 7.0, 7.0.1)               (LLVM 3.7.0)
// AppleClang  7.0.0  __apple_build_version__ ==  7000176  boolean_COMPILER_APPLECLANG_VERSION ==  700  (Xcode 7.1)                      (LLVM 3.7.0)
// AppleClang  7.0.2  __apple_build_version__ ==  7000181  boolean_COMPILER_APPLECLANG_VERSION ==  702  (Xcode 7.2, 7.2.1)               (LLVM 3.7.0)
// AppleClang  7.3.0  __apple_build_version__ ==  7030029  boolean_COMPILER_APPLECLANG_VERSION ==  730  (Xcode 7.3)                      (LLVM 3.8.0)
// AppleClang  7.3.0  __apple_build_version__ ==  7030031  boolean_COMPILER_APPLECLANG_VERSION ==  730  (Xcode 7.3.1)                    (LLVM 3.8.0)
// AppleClang  8.0.0  __apple_build_version__ ==  8000038  boolean_COMPILER_APPLECLANG_VERSION ==  800  (Xcode 8.0)                      (LLVM 3.9.0)
// AppleClang  8.0.0  __apple_build_version__ ==  8000042  boolean_COMPILER_APPLECLANG_VERSION ==  800  (Xcode 8.1, 8.2, 8.2.1)          (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020038  boolean_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3)                      (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020041  boolean_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3.1)                    (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020042  boolean_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3.2, 8.3.3)             (LLVM 3.9.0)
// AppleClang  9.0.0  __apple_build_version__ ==  9000037  boolean_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.0)                      (LLVM 4.0.0?)
// AppleClang  9.0.0  __apple_build_version__ ==  9000038  boolean_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.1)                      (LLVM 4.0.0?)
// AppleClang  9.0.0  __apple_build_version__ ==  9000039  boolean_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.2)                      (LLVM 4.0.0?)
// AppleClang  9.1.0  __apple_build_version__ ==  9020039  boolean_COMPILER_APPLECLANG_VERSION ==  910  (Xcode 9.3, 9.3.1)               (LLVM 5.0.2?)
// AppleClang  9.1.0  __apple_build_version__ ==  9020039  boolean_COMPILER_APPLECLANG_VERSION ==  910  (Xcode 9.4, 9.4.1)               (LLVM 5.0.2?)
// AppleClang 10.0.0  __apple_build_version__ == 10001145  boolean_COMPILER_APPLECLANG_VERSION == 1000  (Xcode 10.0, 10.1)               (LLVM 6.0.1?)
// AppleClang 10.0.1  __apple_build_version__ == 10010046  boolean_COMPILER_APPLECLANG_VERSION == 1001  (Xcode 10.2, 10.2.1, 10.3)       (LLVM 7.0.0?)
// AppleClang 11.0.0  __apple_build_version__ == 11000033  boolean_COMPILER_APPLECLANG_VERSION == 1100  (Xcode 11.1, 11.2, 11.3, 11.3.1) (LLVM 8.0.0?)
// AppleClang 11.0.3  __apple_build_version__ == 11030032  boolean_COMPILER_APPLECLANG_VERSION == 1103  (Xcode 11.4, 11.4.1, 11.5, 11.6) (LLVM 9.0.0?)

#if defined( __apple_build_version__ )
# define boolean_COMPILER_APPLECLANG_VERSION boolean_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
# define boolean_COMPILER_CLANG_VERSION 0
#elif defined( __clang__ )
# define boolean_COMPILER_APPLECLANG_VERSION 0
# define boolean_COMPILER_CLANG_VERSION boolean_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
#else
# define boolean_COMPILER_APPLECLANG_VERSION 0
# define boolean_COMPILER_CLANG_VERSION 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
# define boolean_COMPILER_GNUC_VERSION boolean_COMPILER_VERSION( __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ )
#else
# define boolean_COMPILER_GNUC_VERSION 0
#endif

// Presence of language and library features:

#define boolean_HAVE( feature )  ( boolean_HAVE_##feature )

#ifdef _HAS_CPP0X
# define boolean_HAS_CPP0X  _HAS_CPP0X
#else
# define boolean_HAS_CPP0X  0
#endif

#define boolean_CPP11_90   (boolean_CPP11_OR_GREATER || boolean_COMPILER_MSVC_VER >= 1500)
#define boolean_CPP11_100  (boolean_CPP11_OR_GREATER || boolean_COMPILER_MSVC_VER >= 1600)
#define boolean_CPP11_110  (boolean_CPP11_OR_GREATER || boolean_COMPILER_MSVC_VER >= 1700)
#define boolean_CPP11_120  (boolean_CPP11_OR_GREATER || boolean_COMPILER_MSVC_VER >= 1800)
#define boolean_CPP11_140  (boolean_CPP11_OR_GREATER || boolean_COMPILER_MSVC_VER >= 1900)

#define boolean_CPP17_000  (boolean_CPP17_OR_GREATER)

// Presence of C++11 language features:

#define boolean_HAVE_CONSTEXPR_11           boolean_CPP11_140
#define boolean_HAVE_NOEXCEPT               boolean_CPP11_140
#define boolean_HAVE_EXPLICIT_CONVERSION    boolean_CPP11_120
#define boolean_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG  boolean_CPP11_120
#define boolean_HAVE_STATIC_ASSERT          boolean_CPP11_90

// Presence of C++11 library features:

#define boolean_HAVE_TYPE_TRAITS            boolean_CPP11_90
#define boolean_HAVE_TR1_TYPE_TRAITS        (!! boolean_COMPILER_GNUC_VERSION )

#define boolean_HAVE_IS_SAME                boolean_HAVE_TYPE_TRAITS
#define boolean_HAVE_IS_SAME_TR1            boolean_HAVE_TR1_TYPE_TRAITS

// Presence of C++17 language features:

#define boolean_HAVE_NODISCARD              boolean_CPP17_000

// Presence of C++ language features:

#if boolean_HAVE_CONSTEXPR_11
# define boolean_constexpr constexpr
#else
# define boolean_constexpr /*constexpr*/
#endif

#if boolean_HAVE_NOEXCEPT
# define boolean_noexcept noexcept
#else
# define boolean_noexcept /*noexcept*/
#endif

#if boolean_HAVE_NODISCARD
# define boolean_nodiscard [[nodiscard]]
#else
# define boolean_nodiscard /*[[nodiscard]]*/
#endif

#if boolean_HAVE_EXPLICIT_CONVERSION
# define boolean_explicit_cv explicit
#else
# define boolean_explicit_cv /*explicit*/
#endif

// Additional includes:

#if boolean_HAVE( TYPE_TRAITS )
# include <type_traits>
#elif boolean_HAVE( TR1_TYPE_TRAITS )
# include <tr1/type_traits>
#endif

#define boolean_CPP98_FALLBACK  ( !boolean_CPP11_120 )

namespace nonstd {
namespace boolean_lite {

#if ! boolean_CPP98_FALLBACK

namespace std11 {

#if boolean_HAVE( TYPE_TRAITS )
    using std::enable_if;
    using std::is_same;
#elif boolean_HAVE( TR1_TYPE_TRAITS )
    // using std::tr1::enable_if;
    using std::tr1::is_same;
#endif
}

//
// class boolean_, C++11:
//

class boolean_
{
private:
    bool value;

public:
    // [1] Converting constructor

    template< typename T
    , typename std11::enable_if< std11::is_same<T,bool>::value, int >::type = 0 >
    /*explicit*/ boolean_constexpr boolean_( T v ) boolean_noexcept
    : value( v ) {}

    template< typename T
    , typename std11::enable_if< !std11::is_same<T,bool>::value, int >::type = 0 >
    explicit boolean_constexpr boolean_( T v ) boolean_noexcept
    : value( v ) {}

    // [2] Conversion operator

    template< typename T
    , typename std11::enable_if< std11::is_same<T,bool>::value, int >::type = 0 >
    boolean_nodiscard /*explicit*/ boolean_constexpr operator T() const boolean_noexcept
    {
        return T( value );
    }

    template< typename T
    , typename std11::enable_if< !std11::is_same<T,bool>::value, int >::type = 0 >
    boolean_nodiscard boolean_explicit_cv boolean_constexpr operator T() const boolean_noexcept
    {
        return T( value );
    }

    // [3] Negation

    boolean_nodiscard boolean_constexpr boolean_ operator!() const boolean_noexcept
    {
        return !value;
    }

    // [4] Equality comparison

    boolean_nodiscard friend boolean_constexpr boolean_ operator==( boolean_ a, boolean_ b ) boolean_noexcept
    {
        return a.value == b.value;
    }

    boolean_nodiscard friend boolean_constexpr boolean_ operator!=( boolean_ a, boolean_ b ) boolean_noexcept
    {
        return a.value != b.value;
    }

    // [5] Ordering

    boolean_nodiscard friend boolean_constexpr boolean_ operator<( boolean_ a, boolean_ b ) boolean_noexcept
    {
        return a.value < b.value;
    }

    boolean_nodiscard friend boolean_constexpr boolean_ operator>( boolean_ a, boolean_ b ) boolean_noexcept
    {
        return b.value < a.value;
    }

    boolean_nodiscard friend boolean_constexpr boolean_ operator<=( boolean_ a, boolean_ b ) boolean_noexcept
    {
        return !( a.value > b.value );
    }

    boolean_nodiscard friend boolean_constexpr boolean_ operator>=( boolean_ a, boolean_ b ) boolean_noexcept
    {
        return !( a.value < b.value );
    }
};

#else // boolean_CPP98_FALLBACK

//
// class boolean_, C++98:
//

class boolean_
{
private:
    bool value;

     // Strong boolean operator return type.

    typedef void ( boolean_::*bool_type )() const;

    // Address of method used as 'boolean',
    // inaccessibility of method used for prevented comparison error message.

    void ERROR_this_type_does_not_support_comparisons() const
    {}

public:
    // [1] Converting constructor

    explicit boolean_( bool value_ )
    : value( value_ ) {}

    // [2] Conversion operator

    /*explicit (C++11)*/ operator bool_type() const
    {
        return value ? &boolean_::ERROR_this_type_does_not_support_comparisons : 0;
    }

    // [3] Negation

    boolean_ operator!() const
    {
        return boolean_(!value);
    }

    // [4] Equality comparison

    friend boolean_ operator==( boolean_ a, boolean_ b )
    {
        return boolean_( a.value == b.value );
    }

    friend boolean_ operator!=( boolean_ a, boolean_ b )
    {
        return boolean_( a.value != b.value );
    }

    // [5] Ordering

    friend boolean_ operator<( boolean_ a, boolean_ b )
    {
        return boolean_( a.value < b.value );
    }

    friend boolean_ operator>( boolean_ a, boolean_ b )
    {
        return boolean_( b.value < a.value );
    }

    friend boolean_ operator<=( boolean_ a, boolean_ b )
    {
        return boolean_( !( a.value > b.value ) );
    }

    friend boolean_ operator>=( boolean_ a, boolean_ b )
    {
        return boolean_( !( a.value < b.value ) );
    }
};

#endif // boolean_CPP98_FALLBACK

} // namespace boolean_lite

using boolean_lite::boolean_;

} // namespace nonstd

#endif // NONSTD_BOOLEAN_LITE_HPP
