#include "interface.h"

/* Rational number type */

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

void print_rational(Rational r)
{
    if (r.denominator != 0) printf("%d/%d", r.numerator, r.denominator);
    else printf("Invalid rational");
}

bool create_rational(int numerator, int denominator, Rational *result)
{
    if (denominator == 0) return false;
    result->numerator = numerator;
    result->denominator = denominator;
    return true;
}

bool add_rationals(Rational a, Rational b, Rational *result)
{
    if (a.denominator == 0 || b.denominator == 0) return false;
    result->numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result->denominator = a.denominator * b.denominator;
    return true;
}

bool subtract_rationals(Rational a, Rational b, Rational *result)
{
    if (a.denominator == 0 || b.denominator == 0) return false;
    result->numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    result->denominator = a.denominator * b.denominator;
    return true;
}

bool multiply_rationals(Rational a, Rational b, Rational *result)
{
    if (a.denominator == 0 || b.denominator == 0) return false;
    result->numerator = a.numerator * b.numerator;
    result->denominator = a.denominator * b.denominator;
    return true;
}

bool divide_rationals(Rational a, Rational b, Rational *result)
{
    if (a.denominator == 0 || b.denominator == 0 || b.numerator == 0) return false;
    result->numerator = a.numerator * b.denominator;
    result->denominator = a.denominator * b.numerator;
    return true;
}

bool simplify_rational(Rational *r)
{
    if (r->denominator == 0) return false;
    int common = gcd(abs(r->numerator), abs(r->denominator));
    r->numerator /= common;
    r->denominator /= common;
    if (r->denominator < 0)
    {
        r->numerator = -r->numerator;
        r->denominator = -r->denominator;
    }
    return true;
}