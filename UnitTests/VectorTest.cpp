#include "CppUnitTest.h"
#include <functional>

#include "Vector.h"
using namespace s2;

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(VectorTest)
	{
	public:

		TEST_METHOD(Vector_CreateDefaultVector_HasSizeZero)
		{
			Given_DefaultVector();
			Then_VectorSizeIsCorrect();
		}

		TEST_METHOD(Vector_CreateFromSize_VectorSizeIsCorrect)
		{
			Given_VectorFromSize(15);
			Then_VectorSizeIsCorrect();
		}

		TEST_METHOD(Vector_CreateFromNegativeSize_ThrowsException)
		{
			Given_Action_CreateVectoFromNegativeSize();
			Then_ExecutingActionThrowsExceptionOfType<invalid_argument>();
		}

		TEST_METHOD(Vector_CreateWithInitialValue_ValuesCorrectlyInitialized)
		{
			Given_VectorFromSizeAndValue(7, 3.13f);
			Then_ValuesCorrectlyInitialized();
		}

		TEST_METHOD(Vector_InputValues_ValuesAreCorrect)
		{
			Given_VectorFromSize(5);
			When_InputIncreasingValues();
			Then_ValuesAreCorrect();
		}

		TEST_METHOD(Vector_AddNegativeConstant_ResultIsCorrect)
		{
			Given_VectorFromSize(5);
			When_InputIncreasingValues();
			When_AddConstant(-7);
			Then_ResultOfAddConstantIsCorrect();
		}

		TEST_METHOD(Vector_AddPositiveConstant_ResultIsCorrect)
		{
			Given_VectorFromSize(5);
			When_InputIncreasingValues();
			When_AddConstant(14.5f);
			Then_ResultOfAddConstantIsCorrect();
		}

		TEST_METHOD(Vector_AddVectorFromPositiveConstant_ResultIsCorrect)
		{
			Given_VectorFromSize(5);
			When_InputIncreasingValues();
			When_AddVectorFromConstant(5, 3.14f);
			Then_ResultOfAddVectorIsCorrect();
		}

		TEST_METHOD(Vector_UpdateSingleElement_OnlyElementIsUpdated)
		{
			Given_VectorFromSize(5);
			When_InputIncreasingValues();
			When_UpdateElementAtIndex(2, 1.234f);
			Then_OnlyElementIsUpdated();
		}

		TEST_METHOD(Vector_AddVectorOfDifferenctSize_ExceptionThrown)
		{
			Given_VectorFromSize(5);
			When_InputIncreasingValues();
			When_SetAction_AddVectorFromConstant(3, 3.14f);
			Then_ExecutingActionThrowsExceptionOfType<exception>();
		}

		TEST_METHOD(Vector_NegateValues_ResultIsCorrect)
		{
			Given_VectorFromSize(10);
			When_InputIncreasingValues();
			When_NegateVector();
			Then_NegationResultIsCorrect();
		}

		TEST_METHOD(Vector_SubtractConstant_ResultIsCorrect)
		{
			Given_VectorFromSize(5);
			When_InputIncreasingValues();
			When_SubtractVectorFromConstant(5, 3.14f);
			Then_ResultOfSubtractVectorIsCorrect();
		}

		TEST_METHOD(Vector_MultiplyByConstant_ResultIsCorrect)
		{
			Given_VectorFromSize(42);
			When_InputIncreasingValues();
			When_MultiplyByConstant(7.5f);
			Then_ResultOfMultiplyByConstantIsCorrect();
		}

	private:
		Vector _v;
		Vector _summand;

		float _expectedInitialValue;
		float _addedConstant;
		float _multipliedConstant;

		int _updatedIndex;
		float _updatedValue;

		int _expectedSize;
		function<void(void)> _action;

		void Given_Action_CreateVectoFromNegativeSize()
		{
			_action = [this](void) { Given_VectorFromSize(-3); };
		}

		void Given_DefaultVector()
		{
			_v = Vector();
			_expectedSize = 0;
		}

		void Given_VectorFromSize(int size)
		{
			_v = Vector(size);
			_expectedSize = size;
		}

		void Given_VectorFromSizeAndValue(int size, float initialValue)
		{
			_v = Vector(size, initialValue);
			_expectedInitialValue = initialValue;
		}

		void When_InputIncreasingValues()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				_v << (float)i;
			}
		}

		void When_NegateVector()
		{
			_v = -_v;
		}

		void When_AddConstant(float constant)
		{
			_v = _v + constant;
			_addedConstant = constant;
		}

		void When_AddVectorFromConstant(int size, float constant)
		{
			_summand = Vector(size, constant);
			_v = _v + _summand;
		}

		void When_SubtractVectorFromConstant(int size, float constant)
		{
			_summand = Vector(size, constant);
			_v = _v - _summand;
		}

		void When_MultiplyByConstant(float constant)
		{
			_v = _v * constant;
			_multipliedConstant = constant;
		}

		void When_UpdateElementAtIndex(const int index, float value)
		{
			_v(index) = value;
			_updatedIndex = index;
			_updatedValue = value;
		}

		void When_SetAction_AddVectorFromConstant(int size, float value)
		{
			_action = [this, size, value](void) { When_AddVectorFromConstant(size, value); };
		}

		void Then_VectorSizeIsCorrect()
		{
			Assert::AreEqual(_expectedSize, _v.Size());
		}

		void Then_ValuesAreCorrect()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				Assert::AreEqual((float)i, _v(i));
			}
		}

		void Then_ResultOfAddConstantIsCorrect()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				Assert::AreEqual((float)(i + _addedConstant), _v(i));
			}
		}

		void Then_ResultOfAddVectorIsCorrect()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				Assert::AreEqual((float)i + _summand(i), _v(i));
			}
		}

		void Then_ValuesCorrectlyInitialized()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				Assert::AreEqual(_expectedInitialValue, _v(i));
			}
		}

		template <typename T>
		void Then_ExecutingActionThrowsExceptionOfType()
		{
			Assert::ExpectException<T>(_action);
		}

		void Then_OnlyElementIsUpdated()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				if (i == _updatedIndex)
				{
					Assert::AreEqual(_updatedValue, _v(i));
				}
				else
				{
					Assert::AreEqual((float)i, _v(i));
				}
			}
		}

		void Then_NegationResultIsCorrect()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				Assert::AreEqual((float)-i, _v(i));
			}
		}

		void Then_ResultOfSubtractVectorIsCorrect()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				Assert::AreEqual((float)(i - _summand(i)), _v(i));
			}
		}

		void Then_ResultOfMultiplyByConstantIsCorrect()
		{
			for (auto i = 0; i < _v.Size(); ++i)
			{
				Assert::AreEqual((float)(i * _multipliedConstant), _v(i));
			}
		}
	};
}