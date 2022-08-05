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

// C++ language version detection (C++23 is speculative):
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
#define boolean_CPP20_OR_GREATER  ( boolean_CPLUSPLUS >= 202002L )
#define boolean_CPP23_OR_GREATER  ( boolean_CPLUSPLUS >= 202300L )

// MSVC version:

#if defined(_MSC_VER ) && !defined(__clang__)
# define boolean_COMPILER_MSVC_VER  (_MSC_VER )
#else
# define boolean_COMPILER_MSVC_VER  0
#endif

// Presence of language and library features:

#define boolean_CPP11_120  (boolean_CPP11_OR_GREATER || boolean_COMPILER_MSVC_VER >= 1800)
#define boolean_CPP11_140  (boolean_CPP11_OR_GREATER || boolean_COMPILER_MSVC_VER >= 1900)

#define boolean_CPP17_000  (boolean_CPP17_OR_GREATER)

// Presence of C++11 language features:

#define boolean_HAVE_CONSTEXPR_11           boolean_CPP11_140
#define boolean_HAVE_NOEXCEPT               boolean_CPP11_140
#define boolean_HAVE_DEFAULT_FN_TPL_ARGS    boolean_CPP11_120
#define boolean_HAVE_EXPLICIT_CONVERSION    boolean_CPP11_120

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

#define boolean_CPP98_FALLBACK  ( !boolean_HAVE_DEFAULT_FN_TPL_ARGS )

// Select between C++98 and C++11/later version of boolean_:

#if ! boolean_CPP98_FALLBACK

// Additional includes:

#include <type_traits>

namespace nonstd {
namespace boolean_lite {

//
// class boolean_, C++11 and later:
//

class boolean_
{
private:
    bool value;

public:
    // [1] Converting constructor

    template< typename T
    , typename std::enable_if< std::is_same<T,bool>::value, int >::type = 0 >
    /*explicit*/ boolean_constexpr boolean_( T v ) boolean_noexcept
    : value( v ) {}

    template< typename T
    , typename std::enable_if< !std::is_same<T,bool>::value, int >::type = 0 >
    explicit boolean_constexpr boolean_( T v ) boolean_noexcept
    : value( v ) {}

    // [2] Conversion operator

    template< typename T
    , typename std::enable_if< std::is_same<T,bool>::value, int >::type = 0 >
    boolean_nodiscard /*explicit*/ boolean_constexpr operator T() const boolean_noexcept
    {
        return T( value );
    }

    template< typename T
    , typename std::enable_if< !std::is_same<T,bool>::value, int >::type = 0 >
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

}} // namespace nonstd::boolean_lite

#else // boolean_CPP98_FALLBACK

namespace nonstd {
namespace boolean_lite {

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

}} // namespace nonstd::boolean_lite

#endif // boolean_CPP98_FALLBACK

//
// Provide type boolean in namespace nonstd:
//

namespace nonstd {

using boolean_lite::boolean_;

} // namespace nonstd

#endif // NONSTD_BOOLEAN_LITE_HPP
