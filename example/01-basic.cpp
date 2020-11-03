// Use boolean

#include "nonstd/boolean.hpp"
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

#if 0
cl -EHsc -I../include 01-basic.cpp && 01-basic.exe
g++ -std=c++11 -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe

Output:
Eat 3 cookies and leave no crumbs
Eat 5 cookies and leave crumbs
#endif
