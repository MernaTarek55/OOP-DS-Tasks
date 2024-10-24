#pragma once
#include <iostream>
using namespace std;

void timetable(int number = 5, int number_ = 12) {
    if (number_ < 1) return;
    timetable(number, number_ - 1);
    int result = number * number_;
    cout << number << " * " << number_ << " = " << result << endl;

}