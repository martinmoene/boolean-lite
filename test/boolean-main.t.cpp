// Copyright 2020-2020 by Martin Moene
//
// https://github.com/martinmoene/boolean-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "boolean-main.t.hpp"

// C++ language version (represent 98 as 3):

#define boolean_CPLUSPLUS_V  ( boolean_CPLUSPLUS / 100 - (boolean_CPLUSPLUS > 200000 ? 2000 : 1994) )

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

#define boolean_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define boolean_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "boolean-lite version" "[.boolean][.version]" )
{
    boolean_PRESENT( boolean_lite_MAJOR   );
    boolean_PRESENT( boolean_lite_MINOR   );
    boolean_PRESENT( boolean_lite_PATCH   );
    boolean_PRESENT( boolean_lite_VERSION );

    boolean_PRESENT( boolean_CPP98_FALLBACK );
}

CASE( "boolean-lite configuration" "[.boolean][.config]" )
{
    boolean_PRESENT( boolean_CPLUSPLUS );
    boolean_PRESENT( boolean_CPLUSPLUS_V );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    boolean_PRESENT( __cplusplus );

#if _MSVC_LANG
    boolean_PRESENT( _MSVC_LANG );
#else
    boolean_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
    boolean_PRESENT( boolean_COMPILER_APPLECLANG_VERSION );
    boolean_PRESENT( boolean_COMPILER_CLANG_VERSION );
    boolean_PRESENT( boolean_COMPILER_GNUC_VERSION );
    boolean_PRESENT( boolean_COMPILER_MSVC_VERSION );
    boolean_PRESENT( boolean_COMPILER_MSVC_VERSION_FULL );
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
    boolean_PRESENT( boolean_HAVE_CONSTEXPR_11 );
    boolean_PRESENT( boolean_HAVE_DEFAULT_FN_TPL_ARGS );
    boolean_PRESENT( boolean_HAVE_EXPLICIT_CONVERSION );
    boolean_PRESENT( boolean_HAVE_NODISCARD );
    boolean_PRESENT( boolean_HAVE_NOEXCEPT );
}

CASE( "presence of C++ library features" "[.stdlibrary]" )
{
#if _HAS_CPP0X
    boolean_PRESENT( _HAS_CPP0X );
#else
    boolean_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o boolean-main.t.exe boolean-main.t.cpp && boolean-main.t.exe --pass
g++ -std=c++98 -I../include -o boolean-main.t.exe boolean-main.t.cpp && boolean-main.t.exe --pass
g++ -std=c++03 -I../include -o boolean-main.t.exe boolean-main.t.cpp && boolean-main.t.exe --pass
g++ -std=c++0x -I../include -o boolean-main.t.exe boolean-main.t.cpp && boolean-main.t.exe --pass
g++ -std=c++11 -I../include -o boolean-main.t.exe boolean-main.t.cpp && boolean-main.t.exe --pass
g++ -std=c++14 -I../include -o boolean-main.t.exe boolean-main.t.cpp && boolean-main.t.exe --pass
g++ -std=c++17 -I../include -o boolean-main.t.exe boolean-main.t.cpp && boolean-main.t.exe --pass

cl -EHsc -I../include boolean-main.t.cpp && boolean-main.t.exe --pass
#endif

// end of file
