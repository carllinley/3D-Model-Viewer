#pragma once

#include <string>

class MVVector;
class Vector4;

/*
 A variable size matrix.
 */
class Matrix {
	public:
		Matrix(int columns, int rows);
		Matrix(const Matrix& toCopy);
		~Matrix();

		void setElement(int row, int column, float value);
		void setElements(float values[]);
		float getElement(int row, int column);

		/*
		* Returns true if this matrix is / is equal to the specified matrix.
		*/
		bool operator==(Matrix& toCheck);

		Matrix operator=(Matrix& toAssign);
		Matrix operator+(Matrix& toAdd);
		Matrix operator-(Matrix& toSubtract);
		Matrix operator*(float scalar);

		/*
		 * Converts the vector into a 1xX matrix and multiplies it. Could probably be optimised by... not.
		 */
		Matrix operator*(Vector4& toMultiply);
		Matrix operator*(Matrix& toMultiply);
		Matrix operator/(float scalar);
		void toIdentity();
		Matrix transpose();

		/*
		 Returns this matrix as a string, surrounded by square brackets.
		 */
		std::string toString();

		int getRows();
		int getColumns();

	private:
		int sizeY, sizeX;
		float* p_elements;

		void init(int sizeX, int sizeY, bool initToZero);
};