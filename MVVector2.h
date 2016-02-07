#pragma once

#include "MVVector.h"

/**
 Provides a level of abstraction on top of MVVector allowing explicitly two-dimensional MVVectors.
 **/
class MVVector2 : public MVVector {
	public:
		MVVector2();
		MVVector2(float x, float y);
		MVVector2(MVVector2& copy);

		MVVector2(MVVector& convert);

		bool operator!=(MVVector2& toCheck);
		bool operator==(MVVector2& toCheck);
		MVVector2 operator+(MVVector2& toAdd);
		MVVector2 operator*(MVVector2& toMult);
		MVVector2 operator*(float scalar);
		MVVector2 operator/(MVVector2& toDivide);
		MVVector2 operator/(float scalar);
		MVVector2 operator-(MVVector2& toSubtract);

		/*
		 Returns a copy of this MVVector linearly interpolated with the specified MVVector using the specified percentage.
		 */
		MVVector2 interpolate(MVVector2& destinationMVVector, float percentage);

		/*
		 Sets x to the specified value and returns this MVVector.
		 */
		MVVector2& setX(float x);

		/*
		 Sets y to the specified value and returns this MVVector.
		 */
		MVVector2& setY(float y);

		void set(float x, float y);
		void set(int x, int y);
		void set(MVVector2& set);

		bool equals(float x, float y);

		float getX();
		float getY();
};