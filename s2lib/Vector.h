#pragma once

#include <vector>
#include <iostream>

namespace s2
{
	class Vector
	{
	public:
		Vector(int size = 0, float initialValue = 0.0f);

		int Size() const;

		friend Vector& operator<<(Vector& v, float value);
		friend std::ostream& operator<<(std::ostream& out, const Vector& v);

		friend Vector& operator-(Vector& v);
		friend Vector& operator-(Vector& v, const Vector& other);

		friend Vector& operator+(Vector& v, float value);
		friend Vector& operator+(Vector& v, const Vector& other);

		friend Vector& operator*(Vector& v, float value);
		friend Vector& operator*(float value, Vector& v);

		float& operator()(int i);
		float operator()(int i) const;

	private:
		std::vector<float> _values;
		std::vector<float>::iterator _valuesIterator;
	};
}