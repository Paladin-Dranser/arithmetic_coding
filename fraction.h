#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>

class Fraction
{
public:
    Fraction(boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int d);
    Fraction();
    ~Fraction();

    void reverse();
    void inverse();

    Fraction & operator=(const Fraction & other);

    friend Fraction operator+(const Fraction & f1, const Fraction & f2);
    friend Fraction operator-(const Fraction & f1, const Fraction & f2);
    friend Fraction operator*(const Fraction & f1, const Fraction & f2);
    friend Fraction operator/(const Fraction & f1, const Fraction & f2);

    friend bool operator<(const Fraction & f1, const Fraction & f2);
    friend bool operator<=(const Fraction & f1, const Fraction & f2);
    friend bool operator>(const Fraction & f1, const Fraction & f2);
    friend bool operator>=(const Fraction & f1, const Fraction & f2);
    friend bool operator==(const Fraction & f1, const Fraction & f2);
    friend bool operator!=(const Fraction & f1, const Fraction & f2);

    boost::multiprecision::cpp_int getNumerator() const;
    boost::multiprecision::cpp_int getDenominator() const;

private:
    void lowest_term();
    boost::multiprecision::cpp_int gcd();
    boost::multiprecision::cpp_int gcd(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b);

private:
    boost::multiprecision::cpp_int numerator;
    boost::multiprecision::cpp_int denominator;
};

#endif // FRACTION_H
