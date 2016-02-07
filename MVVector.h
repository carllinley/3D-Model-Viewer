#pragma once

#include <string>

class MVVector2;

/*
 A variable size MVVector.
 Subclassed for ease of use - see 'MVVector2', 'MVVector3', 'MVVector4', etc.
 */
class MVVector {
	public:
		MVVector(int size);
		MVVector(int size, float* elements);
		MVVector(MVVector& copy);

		MVVector(MVVector2& v);

		~MVVector();

		/*
		 Sets all elements to the specified value.
		 */
		void setTo(int value);

		void setElement(int index, float value);
		float getElement(int index);

		int getDimension();
		float* elements();

		// Standard Vector operations

		// MVVector& operator=(MVVector& toAssign);

		MVVector& operator+(MVVector& toAdd);
		MVVector& operator-(MVVector& toSubtract);
		MVVector& operator*(MVVector& toMultiply);
		MVVector& operator/(MVVector& toDivide);

		MVVector& operator*(float scalar);
		MVVector& operator/(float scalar);

		/*
		 The dot product of this and the specified MVVector.
		 */
		float dot(MVVector& v);

		/*
		 The length (or magnitude) of this MVVector.
		 */
		float length();

		/*
		 This MVVector in string form, surrounded by brackets.
		 */
		std::string toString();

	protected:
		float* p_elements;
		int dimension;
};