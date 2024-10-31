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
private:
    int real;
    int imaginary;
};
