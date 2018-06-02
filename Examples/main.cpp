#include "Vector.h"
#include "Matrix.h"

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	auto A = s2::Matrix(5, 3);
	A << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15;

	auto x = s2::Vector(3);
	x << 0.5 << 3.4 << -6;

	cout << A * x << endl;

	fflush(stdin);
	cin.get();

	return 0;
}