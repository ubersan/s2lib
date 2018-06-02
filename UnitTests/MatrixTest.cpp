#include "CppUnitTest.h"
#include <functional>

#include "Matrix.h"
using namespace s2;

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(MatrixTest)
	{
	public:

		TEST_METHOD(Matrix_CreateDefaultMatrix_HasSizeZero)
		{
			Given_DefaultMatrix();
			Then_MatrixHasSizeZero();
		}

		TEST_METHOD(Matrix_CreateWithOnlyRowsSet_ThrowsException)
		{
			Given_ActionSetToCreateMatrixWithSingleDimensionSet();
			Then_ExecutingActionThrowsExceptionOfType<invalid_argument>();
		}

		TEST_METHOD(Matrix_CreateWithFixedDimensions_DimensionsAreCorrect)
		{
			Given_MatrixFromSizeAndInitialValue(7, 22);
			Then_DimensionsAreCoorect();
		}

		TEST_METHOD(Matrix_CreateWithInitialValue_DimensionsAreCorrect)
		{
			Given_MatrixFromSizeAndInitialValue(14, 99, 3.125f);
			Then_InitialValuesAreSet();
		}

	private:
		Matrix _m;

		function<void(void)> _action;
		function<bool(int row, int col, float value)> _thenCondition;

		int _expectedRows;
		int _expectedCols;
		float _expectedInitialValue;

		void Given_DefaultMatrix()
		{
			_m = Matrix();
		}

		void Given_ActionSetToCreateMatrixWithSingleDimensionSet()
		{
			_action = [this](void) { Given_MatrixFromSizeAndInitialValue(-3, 0); };
		}

		void Given_Matrix()
		{
			_m = Matrix(5, 5);
		}

		void Given_MatrixFromSizeAndInitialValue(int rows, int cols, float initialValue = 0.0f)
		{
			_m = Matrix(rows, cols, initialValue);

			_expectedRows = rows;
			_expectedCols = cols;
			_expectedInitialValue;
		}

		void Then_MatrixHasSizeZero()
		{
			Assert::AreEqual(0, _m.Rows);
			Assert::AreEqual(0, _m.Cols);
		}

		template <typename T>
		void Then_ExecutingActionThrowsExceptionOfType()
		{
			Assert::ExpectException<T>(_action);
		}

		void Then_DimensionsAreCoorect()
		{
			Assert::AreEqual(_expectedRows, _m.Rows);
			Assert::AreEqual(_expectedCols, _m.Cols);
		}

		void Then_InitialValuesAreSet()
		{
			_thenCondition = [this](int row, int col, float value) { return _m(row, col) == value; };
		}

		void AssertChecker(float expectedValue)
		{
			// Iterates in column-order
			for (auto col = 0; col < _m.Cols; ++col)
			{
				for (auto row = 0; row < _m.Rows; ++row)
				{
					Assert::IsTrue(_thenCondition(row, col, expectedValue));
				}
			}
		}
	};
}