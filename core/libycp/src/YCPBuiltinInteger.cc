/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|						     (C) SuSE Linux AG |
\----------------------------------------------------------------------/

   File:	YCPBuiltinInteger.cc
   Summary:     YCP Integer Builtins
   Authors:	Klaus Kaempf <kkaempf@suse.de>
		Arvin Schnell <arvin@suse.de>
   Maintainer:	Arvin Schnell <arvin@suse.de>

/-*/

#include "ycp/YCPBuiltinInteger.h"
#include "ycp/YCPInteger.h"
#include "ycp/YCPString.h"
#include "ycp/YCPFloat.h"

#include "ycp/StaticDeclaration.h"
#include "y2log.h"

extern StaticDeclaration static_declarations;


static YCPValue
i_plus (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 + integer i2 -> integer
     * Addition of integers.
     *
     * Example: <pre>
     * 1 + 2 -> 3
     * </pre>
     */
     
    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() + i2->value());
}


static YCPValue
i_minus (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 - integer i2 -> integer
     * Subtraction of integers.
     *
     * Example: <pre>
     * 1 - 2 -> -1
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() - i2->value());
}


static YCPValue
i_mult (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 * integer i2 -> integer
     * Multiplication of integers.
     *
     * Example: <pre>
     * 2 * 3 -> 6
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() * i2->value());
}


static YCPValue
i_div (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 / integer i2 -> integer
     * Division of integers.
     *
     * Examples: <pre>
     * 6 / 2 -> 3
     * 42 / 0 -> nil
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    if (i2->value() == 0)
    {
	ycp2error ("division by zero");
	return YCPNull ();
    }

    return YCPInteger (i1->value() / i2->value());
}


static YCPValue
i_mod (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 % integer i2 -> integer
     * Modulus of integers.
     *
     * Examples: <pre>
     * 7 % 4 -> 3
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() % i2->value());
}


static YCPValue
i_and (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 & integer i2 -> integer
     * Bitwise and of integers.
     *
     * Examples: <pre>
     * 13 & 8 -> 8
     * 13 & 7 -> 5
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() & i2->value());
}


static YCPValue
i_xor (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 ^ integer i2 -> integer
     * Bitwise exclusive or of integers.
     *
     * Examples: <pre>
     * 2 ^ 7 -> 5
     * 5 ^ 4 -> 1
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() ^ i2->value());
}


static YCPValue
i_or (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 | integer i2 -> integer
     * Bitwise or of integers.
     *
     * Examples: <pre>
     * 2 | 2 -> 2
     * 1 | 4 -> 5
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() | i2->value());
}


static YCPValue
i_left (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 << integer i2 -> integer
     * Bitwise shift left for integers.
     *
     * Example: <pre>
     * 8 << 2 -> 32
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() << i2->value());
}


static YCPValue
i_right (const YCPInteger &i1, const YCPInteger &i2)
{
    /**
     * @operator integer i1 >> integer i2 -> integer
     * Bitwise shift right for integers.
     *
     * Example: <pre>
     * 8 >> 2 -> 2
     * </pre>
     */

    if (i1.isNull () || i2.isNull ())
	return YCPNull ();

    return YCPInteger (i1->value() >> i2->value());
}


static YCPValue
i_neg (const YCPInteger &i1)
{
    /**
     * @operator - integer i -> integer
     * Negative of integer.
     */

    if (i1.isNull ())
	return YCPNull ();

    return YCPInteger (-(i1->value()));
}


static YCPValue
i_bnot (const YCPInteger &i1)
{
    /**
     * @operator ~ integer i -> integer
     * Bitwise not of integer.
     *
     * Example: <pre>
     * ~42 = -43
     * </pre>
     */

    if (i1.isNull ())
	return YCPNull ();

    return YCPInteger (~(i1->value()));
}


static YCPValue
i_tointeger (const YCPValue &v)
{
    /**
     * @builtin tointeger
     * @short Converts a value to an integer.
     * @description
     * If the value can't be converted to an integer, nilinteger is returned.
     * @param any VALUE
     * @return integer 
     *
     * @usage tointeger (4.03) -> 4
     * @usage tointeger ("42") -> 42
     * @usage tointeger ("0x42") -> 66
     * @usage tointeger ("042") -> 34
     */

    if (v.isNull())
	return v;
    switch (v->valuetype())
    {
	case YT_INTEGER:
	    return v->asInteger();
	break;
	case YT_FLOAT:
	    return YCPInteger ((long long int) (v->asFloat()->value()));
	break;
	case YT_STRING:
	    return YCPInteger (v->asString()->value_cstr ());
	break;
	default:
	break;
    }
    return YCPNull();

}


YCPBuiltinInteger::YCPBuiltinInteger ()
{
    // must be static, registerDeclarations saves a pointer to it!
    static declaration_t declarations[] = {
	{ "+",  "integer (integer, integer)",	(void *)i_plus },
	{ "-",  "integer (integer, integer)",	(void *)i_minus },
	{ "-",  "integer (integer)",		(void *)i_neg },
	{ "*",  "integer (integer, integer)",	(void *)i_mult },
	{ "/",  "integer (integer, integer)",	(void *)i_div },
	{ "%",  "integer (integer, integer)",	(void *)i_mod },
	{ "&",  "integer (integer, integer)",	(void *)i_and },
	{ "^",  "integer (integer, integer)",	(void *)i_xor },
	{ "|",  "integer (integer, integer)",	(void *)i_or },
	{ "<<", "integer (integer, integer)",	(void *)i_left },
	{ ">>", "integer (integer, integer)",	(void *)i_right },
	{ "~",  "integer (integer)",		(void *)i_bnot },
	{ "tointeger", "integer (const any)",	(void *)i_tointeger },
	{ 0 }
    };

    static_declarations.registerDeclarations ("YCPBuiltinInteger", declarations);
}
