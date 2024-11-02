#include "ComplexNum.h"
#include <iostream>
int ComplexNum::counter = 0;
ComplexNum::ComplexNum() {
    counter++;
    this->real = 0;
    this->imaginary = 0;
}

ComplexNum::ComplexNum(int real, int imag) {
    counter++;
    this->real = real;
    this->imaginary = imag;
}
ComplexNum::ComplexNum(int real) {
    counter++;
    this->real = real;
    this->imaginary = 0;
}
ComplexNum::~ComplexNum() {

    counter--;
}

void ComplexNum::setreal(int r)
{
    this->real = r;
}

void ComplexNum::setimagenary(int i)
{
    this->imaginary = i;
}

int ComplexNum::getreal()
{
    return this->real;
}

int ComplexNum::getimagenary()
{
    return this->imaginary;
}

ComplexNum ComplexNum::operator+(ComplexNum& right)
{
    ComplexNum result;
    result.setreal(this->real + right.getreal());
    result.setimagenary(this->imaginary + right.getimagenary());
    return result;
}

ComplexNum ComplexNum::operator-(ComplexNum& right)
{
    ComplexNum result;
    result.setreal(this->real - right.getreal());
    result.setimagenary(this->imaginary - right.getimagenary());
    return result;
}

bool ComplexNum::operator==(ComplexNum& right)
{
    if (real == right.getreal() && imaginary == right.getimagenary())
        return true ;
    return false;
}

bool ComplexNum::operator!=(ComplexNum& right)
{
    if (this->real != right.getreal() && this->imaginary != right.getimagenary())
        return true;
    return false;
}

void ComplexNum::operator=(ComplexNum& orignal)
{
    this->real = orignal.getreal();
    this->imaginary = orignal.getimagenary();
    return ;
}

void ComplexNum::operator++()
{
    real += 1;
    imaginary += 1;
}

ComplexNum ComplexNum::operator++(int)
{
    ComplexNum temp = *this;
    this->real += 1;
    this->imaginary += 1;
    return temp;
}


void ComplexNum::operator--()
{
    real -= 1;
    imaginary -= 1;
}

ComplexNum  ComplexNum::operator--(int)
{
    ComplexNum temp = *this; 
    this->real -= 1;
    this->imaginary -= 1;
    return temp;
}

ComplexNum::operator float()
{
    return this->real + this->imaginary;
}
