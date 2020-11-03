// Copyright 2020-2020 by Martin Moene
//
// https://github.com/martinmoene/boolean-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "boolean-main.t.hpp"

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
    boolean_PRESENT( boolean_COMPILER_CLANG_VERSION );
    boolean_PRESENT( boolean_COMPILER_GNUC_VERSION );
    boolean_PRESENT( boolean_COMPILER_MSVC_VERSION );
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
    boolean_PRESENT( boolean_HAVE_CONSTEXPR_11 );
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
