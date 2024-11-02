#include <iostream>
#include "ComplexNum.h"

using namespace std;
void findTreasure();

ComplexNum Add(ComplexNum c1, ComplexNum c2) {
	ComplexNum sum;
	sum.setreal(c1.getreal() + c2.getreal());
	sum.setimagenary(c2.getimagenary() + c1.getimagenary());
	return sum;
}
ComplexNum sub(ComplexNum c1, ComplexNum c2) {
	ComplexNum sub;
	sub.setreal(c2.getreal() - c1.getreal());
	sub.setimagenary(c2.getimagenary() - c1.getimagenary());
	return sub;
}
int main()
{
	int i = -1;
	while (i != 0) {
		cout << "Please Enter 1 If you need to add and subtract two complex numbers\n";
        cout << "Please Enter 2 If you need to ++ and --\n";
        cout << "Please Enter 3 If you need check to complex numbers\n";
        cout << "Please Enter 0 If you want to Quit\n";
		cin >> i;
		switch (i)
		{
		case 1: {
			ComplexNum c1(1, 2);
			ComplexNum c2(3, 4);
			ComplexNum c3 = c1 + c2;
			ComplexNum c4 = c1 - c2;
			cout << "Addition: " << c3.getreal() << " + " << c3.getimagenary() << "i" << std::endl;
			cout << "Subtraction: " << c4.getreal() << " + " << c4.getimagenary() << "i" << std::endl;
			
			cout << "\n#################################################################\n";
			break;
		}
		case 2:
		{
			ComplexNum c3(3, 4);
			c3++;
			cout << "complex++: " << c3.getreal() << " + " << c3.getimagenary() << "i" << std::endl;
			c3--;
			cout << "complex--: " << c3.getreal() << " + " << c3.getimagenary() << "i" << std::endl;
			++c3;
			cout << "++complex: " << c3.getreal() << " + " << c3.getimagenary() << "i" << std::endl;
			--c3;
			cout << "--complex: " << c3.getreal() << " + " << c3.getimagenary() << "i" << std::endl;
			cout << "\n#################################################################\n";
			break;
		}
		case 3:
		{
			ComplexNum c1(1, 2);
			ComplexNum c2(3, 4);
			if (c1 == c2)
				cout << "yes" << endl;
			if (c1 != c2)
				cout << "no" << endl;
			float x = c2;
			cout << x << endl;
			cout << "\n#################################################################\n";
			break;
		}
		case 0:
			cout << "\n#################################################################\n";
		default:
			break;
		}
	}

}
