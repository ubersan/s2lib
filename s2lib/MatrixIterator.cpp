#include "MatrixIterator.h"
#include <iostream>

using namespace s2;
using namespace std;

MatrixIterator::MatrixIterator(bool isColumnIterator, int rows, int cols)
	: _isColumnIterator(isColumnIterator), _rows(rows), _cols(cols), _currentRow(0), _currentCol(0)
{
}


MatrixIterator::MatrixIterator()
{
	MatrixIterator(true, 0, 0);
}

MatrixIterator MatrixIterator::CreateRowOrderIterator(int rows, int cols)
{
	return MatrixIterator(false, rows, cols);
}

MatrixIterator MatrixIterator::CreateColumnOrderIterator(int rows, int cols)
{
	return MatrixIterator(true, rows, cols);
}

int MatrixIterator::GetIndexAndAdvance()
{
	auto index = _currentCol*_rows + _currentRow;

	if (_isColumnIterator)
	{
		// move to next row in same column
		_currentRow = ++_currentRow % _rows;

		if (_currentRow == 0)
		{
			// reached end of column, go to next one
			++_currentCol;

			if (_currentCol > _cols)
			{
				throw invalid_argument("Too many coefficients provided");
			}
		}
	}
	else
	{
		// move to next column in same row
		_currentCol = ++_currentCol % _cols;

		if (_currentCol == 0)
		{
			// reached end of row, go to next one
			++_currentRow;

			if (_currentRow > _rows)
			{
				throw invalid_argument("Too many coefficients provided");
			}
		}
	}

	return index;
}