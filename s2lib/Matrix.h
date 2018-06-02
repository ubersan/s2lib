#pragma once

#include "Vector.h"
#include "MatrixIterator.h"

#include <vector>
#include <iostream>

namespace s2
{
	class Matrix
	{
	public:
		Matrix(int rows = 0, int cols = 0, float initialValue = 0.0f);

		friend Vector operator*(const Matrix& m, const Vector& v);

		friend Matrix& operator<<(Matrix& m, float value);
		friend Matrix& operator,(Matrix& m, float value);

		float& operator()(int row, int col);
		float operator()(int row, int col) const;

		int Rows;
		int Cols;

	private:
		// Stored in column order.
		std::vector<float> _values;
		std::vector<float>::iterator _valuesIterator;

		MatrixIterator _matrixIterator;
	};
}