#include "Vector.h"
#include "Matrix.h"

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	auto A = s2::Matrix(2, 3);
	A << 1, 2, 3,
		4, 5, 6;

	auto x = s2::Vector(3);
	x << 0.5f << 3.4f << -6.0f;

	cout << A * x << endl;

	fflush(stdin);
	cin.get();

	return 0;
}