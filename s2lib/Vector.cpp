#include "Vector.h"

using namespace std;
using namespace s2;

Vector::Vector(int size, float initialValue)
{
	// todo: DOn't thrown in ctor?
	if (size < 0)
	{
		throw invalid_argument("Size cannot be negative");
	}

	_values = vector<float>(size, initialValue);
	_valuesIterator = _values.begin();
}

int Vector::Size() const
{
	// vector size is declared as size_t.
	// Using unsigned can introduce bugs itself
	// when combined with signed integers. So internally
	// everything is treated as a signed integer and where
	// necessary, checks for negativity are inserted manually.
	return (int)_values.size();
}

Vector& s2::operator<<(Vector& v, float value)
{
	*v._valuesIterator++ = value;

	return v;
}

ostream& s2::operator<<(ostream& out, const Vector& v)
{
	for (auto i = 0; i < v.Size(); ++i)
	{
		out << v(i) << endl;
	}

	return out;
}

Vector& s2::operator-(Vector& v)
{
	for (auto i = 0; i < v.Size(); ++i)
	{
		v(i) *= -1;
	}

	return v;
}

Vector& s2::operator-(Vector& v, const Vector& other)
{
	if (v.Size() != other.Size())
	{
		throw invalid_argument("Vectors must have the same length");
	}

	for (auto i = 0; i < v.Size(); ++i)
	{
		v(i) -= other(i);
	}

	return v;
}

Vector& s2::operator+(Vector& v, float value)
{
	for (auto i = 0; i < v.Size(); ++i)
	{
		v(i) += value;
	}

	return v;
}

Vector& s2::operator+(Vector& v, const Vector& other)
{
	if (v.Size() != other.Size())
	{
		throw invalid_argument("Vectors must have the same length");
	}

	for (auto i = 0; i < v.Size(); ++i)
	{
		v(i) += other(i);
	}

	return v;
}

Vector& s2::operator*(Vector& v, float value)
{
	for (auto i = 0; i < v.Size(); ++i)
	{
		v(i) *= value;
	}

	return v;
}

Vector& s2::operator*(float value, Vector& v)
{
	return v * value;
}

inline float& Vector::operator()(int i)
{
	return _values[i];
}

inline float Vector::operator()(int i) const
{
	return _values[i];
}