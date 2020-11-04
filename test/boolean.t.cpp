// Copyright 2020-2020 Martin Moene
//
// https://github.com/martinmoene/boolean-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "boolean-main.t.hpp"

namespace {

using namespace nonstd;

CASE( "boolean: Allows to direct initialize from bool" )
{
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT( f == boolean_(false) );
    EXPECT( t == boolean_(true ) );
}

CASE( "boolean: Allows to copy initialize from bool (C++11)" )
{
#if !boolean_CPP98_FALLBACK
    boolean_ b = true;

    EXPECT( b == boolean_(true) );
#else
    EXPECT( !!"No copy-initialization from bool (C++98 version of boolean_)." );
#endif
}

CASE( "boolean: Allows to direct initialize from type convertible to bool" )
{
    boolean_ b( 1 );

    EXPECT( b == boolean_(true) );
}

CASE( "boolean: Allows to compare equal" )
{
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT( f == f );
    EXPECT( t == t );
}

CASE( "boolean: Allows to compare unequal" )
{
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT( f != t );
}

CASE( "boolean: Allows to compare less than" )
{
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT( f <  t );
}

CASE( "boolean: Allows to compare less than or equal" )
{
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT( f <= t );
    EXPECT( f <= f );
}

CASE( "boolean: Allows to compare greater than" )
{
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT( t >  f );
}

CASE( "boolean: Allows to compare greater than or equal" )
{
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT( t >= f );
    EXPECT( t >= t );
}

CASE( "boolean: Allows to compare equal with bool (C++11)" )
{
#if !boolean_CPP98_FALLBACK
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT(     f == false );
    EXPECT(     t == true  );
    EXPECT( false == f     );
    EXPECT(  true == t     );
#else
    EXPECT( !!"No comparison with bool (C++98 version of boolean_)." );
#endif
}

CASE( "boolean: Allows to compare unequal with bool (C++11)" )
{
#if !boolean_CPP98_FALLBACK
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT(     f != true  );
    EXPECT(     t != false );
    EXPECT( true  != f     );
    EXPECT( false != t     );
#else
    EXPECT( !!"No comparison with bool (C++98 version of boolean_)." );
#endif
}

CASE( "boolean: Allows to compare less than with bool (C++11)" )
{
#if !boolean_CPP98_FALLBACK
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT(     f < true );
    EXPECT( false < t    );
#else
    EXPECT( !!"No comparison with bool (C++98 version of boolean_)." );
#endif
}

CASE( "boolean: Allows to compare less than or equal with bool (C++11)" )
{
#if !boolean_CPP98_FALLBACK
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT(     f <= false );
    EXPECT(     f <= true  );
    EXPECT( false <= f     );
    EXPECT( false <= t     );
#else
    EXPECT( !!"No comparison with bool (C++98 version of boolean_)." );
#endif
}

CASE( "boolean: Allows to compare greater than with bool (C++11)" )
{
#if !boolean_CPP98_FALLBACK
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT(    t >  false );
    EXPECT( true >  f     );
#else
    EXPECT( !!"No comparison with bool (C++98 version of boolean_)." );
#endif
}

CASE( "boolean: Allows to compare greater than or equal with bool (C++11)" )
{
#if !boolean_CPP98_FALLBACK
    boolean_ f( false );
    boolean_ t( true  );

    EXPECT(    t >= false );
    EXPECT(    t >= true  );
    EXPECT( true >= f     );
    EXPECT( true >= t     );
#else
    EXPECT( !!"No comparison with bool (C++98 version of boolean_)." );
#endif
}

CASE( "boolean: Supports no discard (C++17, -DBOOLEAN_TEST_NODISCARD=1)" )
{
#if defined BOOLEAN_TEST_NODISCARD && BOOLEAN_TEST_NODISCARD
    boolean_ f( false );
    boolean_ t( true  );

    static_cast<bool>(t);
    f == t;
    f != t;
    f <  t;
    f <= t;
    f >  t;
    f >= t;
#else
    EXPECT( !!"No compilation for [[nodiscard]]." );
#endif
}

CASE( "tweak header: Reads tweak header if supported " "[tweak]" )
{
#if boolean_HAVE_TWEAK_HEADER
    EXPECT( BOOLEAN_TWEAK_VALUE == 42 );
#else
    EXPECT( !!"Tweak header is not available (boolean_HAVE_TWEAK_HEADER: 0)." );
#endif
}
} // anonymous namespace
