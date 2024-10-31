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

    std::cout << "The Odject was destroid \n";
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
