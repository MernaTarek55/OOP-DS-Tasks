#include <iostream>
#include <vector>
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
using namespace std;


int main() {
    int choose = -1;
    inventory i; 

    while (choose != 0) {
        cout << "Welcome to our app \n"
            << "Choose 1: if you want to print the timetable of 5 using recursion \n"
            << "Choose 2: if you need the The Factorial and Power of number \n"
            << "Choose 3: if you want to add and get items from struct \n"
            << "Choose 0: to exit\n";
        cin >> choose;

        switch (choose) {
        case 1:
            timetable();
            cout << "/////////////////////////////////////////////////////////////////" << endl;
            break;
        case 2:
            int num , pow, numWithfactorial ,pownumber , number;
            cout << "Enter the number and the power please : ";
            cin >> num >> pow;
            numWithfactorial = num;
            number = num;
            pownumber = pow;
            factorialWithPointers(&numWithfactorial);
            powerWithPointer(&number, &pownumber);
            cout << "The Factorial of number is : " << factorial(num) << endl;
            cout << "The Factorial With Pointers of number is : " << numWithfactorial << endl;
            cout << "The Power of number is : " << power(num , pow) << endl;
            cout << "The Power of number With Pointers is : " << number << endl;
            cout << "/////////////////////////////////////////////////////////////////" << endl;
            break;
        case 3: {
            int x, id;
            string name;

            cout << "If you need to add, press 1; if you want to get, press 2: ";
            cin >> x;

            if (x == 1) {
                cout << "Enter ID : ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                i.add(id, name);
            }
            else if (x == 2) {
                cout << "Enter ID to get: ";
                cin >> id;
                i.get(id);
            }
            cout << "/////////////////////////////////////////////////////////////////" << endl;

            break;
        }

        default:
            if (choose != 0)
                cout << "Invalid choice." << endl;
            break;
        }
    }

    return 0;
}
