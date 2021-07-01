//
// Created by MavkaWork on 7/1/2021.
//
#include <iostream>
#include <cmath>
#include <sstream>
#ifndef MAIN_RATIONAL_H
#define MAIN_RATIONAL_H


class Rational {
public:
    Rational();
    Rational(int numerator, int denominator);
    void Reduction();
    int GetCommonDivisor;

    int Numerator() const {
        return numerator;
    }

    int Denominator() const{
        return denominator;
    }
private:
    int numerator;
    int denominator;
};

int findCommonDenominator(Rational const& lhs, Rational const& rhs);
Rational operator+(Rational const& lhs, Rational const& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
std::ostream& operator<<(std::ostream& stream, const Rational& rationalNumber);
std::istream& operator>>(std::istream& stream, Rational& rationalNumber);
bool operator<(const Rational & lhs, const Rational & rhs);
int minimal(int first, int second);
#endif //MAIN_RATIONAL_H
