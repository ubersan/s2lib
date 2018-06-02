#pragma once

namespace s2
{
	class MatrixIterator
	{
	public:
		MatrixIterator();

		static MatrixIterator CreateRowOrderIterator(int rows, int cols);
		static MatrixIterator CreateColumnOrderIterator(int rows, int cols);

		int GetIndexAndAdvance();
	private:
		MatrixIterator(bool isColumnIterator, int rows, int cols);

		bool _isColumnIterator;

		int _rows;
		int _cols;

		int _currentRow;
		int _currentCol;
	};
}