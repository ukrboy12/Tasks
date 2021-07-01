
#include "Rational.h"
using std::cout;
using std::endl;

int Rational::minimal(int first, int second){
    if(first>second){
        return second;
    }
    return first;
}

Rational::Rational(){
    this->numerator = 0;
    this->denominator = 1;
    }
Rational::Rational(int numerator, int denominator){
    if(denominator == 0){
        throw std::invalid_argument("");
    }
    if((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0)){
        numerator = -1*numerator;
        denominator = -1*denominator;
    }
    if (numerator == 0){
        denominator = 1;
    }
    this->numerator = numerator;
    this->denominator = denominator;
    if(GetCommonDivisor(numerator, denominator) != 1){
        Reduction();
    }
}

void Rational::Reduction(){
    int commonDivisor = GetCommonDivisor(numerator, denominator);
    if(commonDivisor != 1){
        numerator /= commonDivisor;
        denominator /= commonDivisor;
        Reduction();
    }
}

int Rational::GetCommonDivisor(int firstValue, int secondValue){
    int commonDivisor = 1;
    int min = minimal(std::fabs(firstValue), std::fabs(secondValue));
    for(int i = 1; i <= min; ++i){
        if(firstValue % i == 0 and secondValue % i == 0){
            commonDivisor = i;
        }
    }
    return commonDivisor;
}



int Rational::findCommonDenominator(Rational const& lhs, Rational const& rhs){
    int lDenominator = lhs.Denominator(), rDenominator = rhs.Denominator();
    int i = 1;
    while (true){
        if(i % lDenominator == 0 && i % rDenominator == 0){
            return i;
        }
        ++i;
    }
}

Rational::Rational operator+(Rational const& lhs, Rational const& rhs){
    int numerator;
    if((lhs.Denominator() != rhs.Denominator())){
        int commonDenominator = findCommonDenominator(lhs, rhs);

        numerator = lhs.Numerator()*(commonDenominator/lhs.Denominator())+rhs.Numerator()*(commonDenominator/rhs.Denominator());
        return Rational(numerator, commonDenominator);
    }
    return Rational(lhs.Numerator()+rhs.Numerator(),lhs.Denominator());
}

Rational::Rational operator-(const Rational& lhs, const Rational& rhs){
    int numerator;
    if((lhs.Denominator() != rhs.Denominator())){
        int commonDenominator = findCommonDenominator(lhs, rhs);
        numerator = lhs.Numerator()*(commonDenominator/lhs.Denominator()) - rhs.Numerator()*(commonDenominator/rhs.Denominator());
        return Rational(numerator, commonDenominator);
    }
    return Rational(lhs.Numerator()-rhs.Numerator(),lhs.Denominator());
}


Rational::Rational operator*(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
}

Rational::Rational operator/(const Rational& lhs, const Rational& rhs){
    if(rhs.Denominator() == 0 || rhs.Numerator() == 0){
        throw domain_error("");
    }
    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator()*rhs.Numerator());
}

std::ostream& Rational::operator<<(std::ostream& stream, const Rational& rationalNumber){
    stream<<rationalNumber.Numerator()<<"/"<<rationalNumber.Denominator();
    return stream;
}

std::istream& Rational::operator>>(std::istream& stream, Rational& rationalNumber){
    int numerator = 0, denominator = 0;
    char symbol;
    stream>>numerator;
    stream>>symbol;
    stream>>denominator;
    if(stream.fail()){
        return stream;
    }
    if(denominator == 0 || symbol != '/'){
        return stream;
    }
    rationalNumber = Rational(numerator,denominator);
    return stream;
}

bool Rational::operator<(const Rational & lhs, const Rational & rhs){
    if(lhs.Denominator() == rhs.Denominator()){
        if(lhs.Numerator() < rhs.Numerator()){
            return true;
        } else {
            return false;
        }
    } else {
        int commonDenominator = findCommonDenominator(lhs, rhs);
        if(lhs.Numerator()*(commonDenominator/lhs.Denominator()) < rhs.Numerator()*(commonDenominator/rhs.Denominator())){
            return true;
        } else {
            return false;
        }
    }
}
