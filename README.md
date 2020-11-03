# boolean lite: A strong boolean type for C++98 and later

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://travis-ci.org/martinmoene/boolean-lite.svg?branch=master)](https://travis-ci.org/martinmoene/boolean-lite) [![Build status](https://ci.appveyor.com/api/projects/status/1ha3wnxtam547m8p?svg=true)](https://ci.appveyor.com/project/martinmoene/boolean-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fboolean-lite.svg)](https://github.com/martinmoene/boolean-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://github.com/martinmoene/boolean-lite/blob/master/include/nonstd/boolean.hpp) <!-- [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/boolean-lite)--> [![Try it on wandbox](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/permlink/TMURDai5p2CSWn9a) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/z/E1onYM)

**Contents**  

- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation and use](#installation-and-use)
- [Synopsis](#synopsis)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)

<!--
- [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests)
- [Other implementations of boolean](#other-implementations-of-boolean)
-->

## Example usage

```cpp
#include <iostream>

using nonstd::boolean_;

void eat_cookies( int count, boolean_ leave_crumbs )
{
    std::cout << "Eat " << count << " cookies and leave " << (leave_crumbs ? "" : "no ") << "crumbs\n";
}

void santa( int num_cookies )
{
    const boolean_ leave_crumbs = num_cookies > 4;

//  eat_cookies( leave_crumbs, num_cookies );  // Does not compile: wrong argument order
    eat_cookies( num_cookies, leave_crumbs );  // Ok
}

int main()
{
    santa( 3 );
    santa( 5 );
}
```

### Compile and run

```bash
prompt >g++ -std=c++11 -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe
Eat 3 cookies and leave no crumbs
Eat 5 cookies and leave crumbs
```

## In a nutshell

**boolean lite** is a single-file header-only library to provide a strong boolean type.

*boolean lite* is inspired on the article [Fun with Concepts: Do You Even Lift, Bool?](https://vector-of-bool.github.io/2020/10/26/strong-bool.html) by Colby Pike (vector-of-bool), Oct 26, 2020.

**Features and properties of boolean lite** are ease of installation (single header), freedom of dependencies other than the standard library.

## License

*boolean lite* is distributed under the [Boost Software License](https://github.com/martinmoene/boolean-lite/blob/master/LICENSE.txt).

## Dependencies

*boolean lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation and use

*boolean lite* is a single-file header-only library. Put `boolean.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

**Contents**  
[Documentation of `nonstd::boolean`](#documentation-of-nonstdboolean)  
[Configuration](#configuration)  

### Documentation of `nonstd::boolean`

The behaviour of boolean differs under C++98 and C++11 and later. Specifically the C++11 version allows the following that is not supported by the C++98 version of `boolean_`.

- copy initialization like `boolean_ b = true;`
- comparison to `bool`, like `boolean_ f( false ); boolean_ result = f == true;`

Note: The name `boolean_` is used for the type to prevent clashing with type `boolean` from the Windows SDK (rpcndr.h(193)).

| Kind                    | std   | Function or method |
|-------------------------|-------|--------------------|
| **Construction**        |C++11  | template&lt;typename T *[bool]*> constexpr **boolean\_(T v)** noexcept; |
| &nbsp;                  |&#8942;| template&lt;typename T *[!bool]*> explicit constexpr **boolean\_(T v)** noexcept; |
| **Conversion**          |&#8942;| template&lt;typename T *[bool]*> \[[nodiscard]] constexpr **operator T()** const noexcept; |
| &nbsp;                  |&#8942;| template&lt;typename T *[!bool]*> \[[nodiscard]] explicit constexpr **operator T()** const noexcept; |
| **Negation**            |&#8942;| \[[nodiscard]] friend explicit constexpr **operator!()** const noexcept; |
| **Equality**            |&#8942;| \[[nodiscard]] friend explicit constexpr **operator==(boolean\_ a, boolean\_ b)** noexcept; |
| &nbsp;                  |&#8942;| \[[nodiscard]] friend explicit constexpr **operator!=(boolean\_ a, boolean\_ b)** noexcept; |
| **Ordering**            |&#8942;| \[[nodiscard]] friend explicit constexpr **operator<(boolean\_ a, boolean\_ b)** noexcept; |
| &nbsp;                  |&#8942;| \[[nodiscard]] friend explicit constexpr **operator>(boolean\_ a, boolean\_ b)** noexcept; |
| &nbsp;                  |&#8942;| \[[nodiscard]] friend explicit constexpr **operator<=(boolean\_ a, boolean\_ b)** noexcept; |
| &nbsp;                  |C++11  | \[[nodiscard]] friend explicit constexpr **operator>=(boolean\_ a, boolean\_ b)** noexcept; |
| &nbsp;                  |&nbsp; |&nbsp;|
| **Construction**<br>&nbsp;|C++98<br>&nbsp;  | explicit **boolean\_(bool v)**;<br>Note: no copy initialization: `boolean_ b = true;` |
| **Conversion**<br>&nbsp;  |&#8942;<br>&nbsp;| operator **bool_type()** const;<br>Note: bool_type allows for safe convertions |
| **Negation**            |&#8942;| boolean_ **operator!()** const; |
| **Equality**            |&#8942;| friend boolean\_ **operator==(boolean\_ a, boolean\_ b)**; |
| &nbsp;                  |&#8942;| friend boolean\_ **operator!=(boolean\_ a, boolean\_ b)**; |
| **Ordering**            |&#8942;| friend boolean\_ **operator<(boolean\_ a, boolean\_ b)**; |
| &nbsp;                  |&#8942;| friend boolean\_ **operator>(boolean\_ a, boolean\_ b)**; |
| &nbsp;                  |&#8942;| friend boolean\_ **operator<=(boolean\_ a, boolean\_ b)**; |
| &nbsp;                  |C++98  | friend boolean\_ **operator>=(boolean\_ a, boolean\_ b)**; |

### Configuration

#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *boolean lite* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/boolean.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define boolean_CPLUSPLUS 201103L`.

#### Standard selection macro

\-D<b>boolean\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.

## Notes and references

- [Fun with Concepts: Do You Even Lift, Bool?](https://vector-of-bool.github.io/2020/10/26/strong-bool.html) by Colby Pike ([vector-of-bool](https://github.com/vector-of-bool)), Oct 26, 2020.
- [A New Approach to Build-Time Library Configuration](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) by Colby Pike ([vector-of-bool](https://github.com/vector-of-bool)), Oct 4, 2020.

## Appendix

### A.1 Compile-time information

The version of *boolean lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

### A.2 Span lite test specification

```Text
boolean: Allows to direct initialize from bool
boolean: Allows to copy initialize from bool (C++11)
boolean: Allows to direct initialize from type convertible to bool
boolean: Allows to compare equal
boolean: Allows to compare unequal
boolean: Allows to compare less than
boolean: Allows to compare less than or equal
boolean: Allows to compare greater than
boolean: Allows to compare greater than or equal
boolean: Allows to compare equal with bool (C++11)
boolean: Allows to compare unequal with bool (C++11)
boolean: Allows to compare less than with bool (C++11)
boolean: Allows to compare less than or equal with bool (C++11)
boolean: Allows to compare greater than with bool (C++11)
boolean: Allows to compare greater than or equal with bool (C++11)
boolean: Supports no discard (C++17, -DBOOLEAN_TEST_NODISCARD=1)
tweak header: Reads tweak header if supported [tweak]
```
