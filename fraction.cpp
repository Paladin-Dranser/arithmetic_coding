#include "fraction.h"
#include <iostream>

Fraction::Fraction(boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int d) :
    numerator(n), denominator(d)
{
    if (0 == d)
        denominator = 1;
    else if (d < 0)
    {
        denominator = -d;
        numerator = -numerator;
    }
    else
        denominator = d;

    this->lowest_term();
}

Fraction::Fraction() :
    numerator(0), denominator(1)
{
    // empty;
}

Fraction::~Fraction()
{

}

void Fraction::inverse()
{
    numerator = -numerator;
}

void Fraction::reverse()
{
    boost::multiprecision::cpp_int temp = 0;
    temp = numerator;
    numerator = denominator;
    denominator = temp;
}

void Fraction::lowest_term()
{
    boost::multiprecision::cpp_int temp = this->gcd();
    while (temp != 1)
    {
        numerator /= temp;
        denominator /= temp;

        temp = this->gcd();
    }
}

boost::multiprecision::cpp_int Fraction::gcd()
{
    return (denominator == 0) ? numerator : gcd(denominator, numerator % denominator);
}

boost::multiprecision::cpp_int Fraction::gcd(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

Fraction & Fraction::operator=(const Fraction & other)
{
    if (this != &other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
    }

    return *this;
}

Fraction operator+(const Fraction & f1, const Fraction & f2)
{
    boost::multiprecision::cpp_int temp_numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    boost::multiprecision::cpp_int temp_denominator = f1.denominator * f2.denominator;

    return Fraction(temp_numerator, temp_denominator);
}

Fraction operator-(const Fraction & f1, const Fraction & f2)
{
    boost::multiprecision::cpp_int temp_numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    boost::multiprecision::cpp_int temp_denominator = f1.denominator * f2.denominator;

    return Fraction(temp_numerator, temp_denominator);
}

Fraction operator*(const Fraction & f1, const Fraction & f2)
{
    boost::multiprecision::cpp_int temp_numerator = f1.numerator * f2.numerator;
    boost::multiprecision::cpp_int temp_denominator = f1.denominator * f2.denominator;

    return Fraction(temp_numerator, temp_denominator);
}

Fraction operator/(const Fraction & f1, const Fraction & f2)
{
    boost::multiprecision::cpp_int temp_numerator = f1.numerator * f2.denominator;
    boost::multiprecision::cpp_int temp_denominator = f1.denominator * f2.numerator;

    return Fraction(temp_numerator, temp_denominator);
}

bool operator<(const Fraction & f1, const Fraction & f2)
{
    return f1.numerator * f2.denominator < f1.denominator * f2.numerator;
}

bool operator>(const Fraction & f1, const Fraction & f2)
{
    return f2 < f1;
}

bool operator==(const Fraction & f1, const Fraction & f2)
{
    return f1.numerator * f2.denominator == f1.denominator * f2.numerator;
}

bool operator<=(const Fraction & f1, const Fraction & f2)
{
    return f1 < f2 || f1 == f2;
}

bool operator>=(const Fraction & f1, const Fraction & f2)
{
    return f2 < f1 || f1 == f2;
}

boost::multiprecision::cpp_int Fraction::getNumerator() const
{
    return numerator;
}
boost::multiprecision::cpp_int Fraction::getDenominator() const
{
    return denominator;
}
