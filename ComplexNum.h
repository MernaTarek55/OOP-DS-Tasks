#pragma once
class ComplexNum {
    
public:
    static int counter;
    ComplexNum();
    ComplexNum(int real, int imag);
    ComplexNum(int real);
    ~ComplexNum();
    void setreal(int real);
    void setimagenary(int imagenary);
    int getreal();
    int getimagenary();
    ComplexNum operator+(ComplexNum& right);
    ComplexNum operator-(ComplexNum& right);
    bool operator==(ComplexNum& right);
    bool operator!=(ComplexNum& right);
    void operator=(ComplexNum& orignal);
    void operator++();
    ComplexNum  operator++(int);
    void operator--();
    ComplexNum  operator--(int);
    operator float();
private:
    int real;
    int imaginary;
};
