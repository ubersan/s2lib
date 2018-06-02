#include "Matrix.h"
using namespace s2;
using namespace std;

Matrix::Matrix(int rows, int cols, float initialValue)
{
	if (rows != 0 && cols == 0)
	{
		throw invalid_argument("Either set none or both dimensions");
	}

	Rows = rows;
	Cols = cols;

	_values = vector<float>(Rows * Cols, initialValue);
	_valuesIterator = _values.begin();
}

Vector s2::operator*(const Matrix& m, const Vector& v)
{
	if (m.Cols != v.Size())
	{
		throw invalid_argument("Dimensions don't match");
	}

	auto res = Vector(m.Rows);

	// iterate row-by-row
	for (auto row = 0; row < m.Rows; ++row)
	{
		auto r = 0.0f;
		for (auto col = 0; col < m.Cols; ++col)
		{
			r += m(row, col) * v(col);
		}

		res(row) = r;
	}

	return res;
}

Matrix& s2::operator<<(Matrix& m, float value)
{
	*m._valuesIterator++ = value;

	return m;
}

float& Matrix::operator()(int row, int col)
{
	return _values[col * Rows + row];
}

float Matrix::operator()(int row, int col) const
{
	return _values[col * Rows + row];
}