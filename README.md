# boolean lite: A strong boolean type for C++98 and later

*boolean lite* is inspired on the article
[Fun with Concepts: Do You Even Lift, Bool?](https://vector-of-bool.github.io/2020/10/26/strong-bool.html) by Colby Pike (vector-of-bool), Oct 26, 2020.

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
boolean: no discard (C++17)
```
