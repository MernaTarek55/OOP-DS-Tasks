#pragma once
int factorial(int num) {
	if (num <= 1)return 1;
	return num * factorial(num - 1);
}
void factorialWithPointers(int* num) {
	if (*num <= 1)return;
	int n = *num - 1;
	factorialWithPointers(&n);
	*num = *num * n;
}

int power(int number, int pow) {
	if (pow <= 1)return number;
	return number * power(number, pow - 1);
}
void powerWithPointer(int* number, int* pow , int temp = 1) {
	if (*pow < 1) {
		*number = temp;
		return;
	}
	int p = *pow - 1;
	powerWithPointer(number, &p , temp * (*number));

}