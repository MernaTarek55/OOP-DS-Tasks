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
        cout << "Please Enter 2 If you need to see the number of instances in the class\n";
        cout << "Please Enter 3 If you need to play the treasure hunt game\n";
        cout << "Please Enter 0 If you want to Quit\n";
		cin >> i;
		switch (i)
		{
		case 1: {
			ComplexNum c1(1, 2);
			ComplexNum c2(3, 4);
			ComplexNum c3 = Add(c1, c2);
			ComplexNum c4 = sub(c1, c2);
			cout << "Addition: " << c3.getreal() << " + " << c3.getimagenary() << "i" << std::endl;
			cout << "Subtraction: " << c4.getreal() << " + " << c4.getimagenary() << "i" << std::endl;
			break;
		}
		case 2:
			cout << "The counter : " << ComplexNum::counter << endl;
		case 3:
			findTreasure();
			break;
		case 0:
			cout << "\n#################################################################\n";
		default:
			break;
		}
	}
	
	

}
