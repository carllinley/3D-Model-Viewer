#pragma once

#include "Mesh.h"
#include "Vector3.h"

class Model {
	public:
		Model(Mesh* mesh);

		void setTranslation(Vector3& localTranslation);
		void setScale(Vector3& scale);
		void setScale(float scale);
		void setRotation(Vector3& rotation);
		void setTexture(MVTexture* p_texture);

		Mesh* getMesh();
		Matrix& getRotationMatrix();
		Matrix& getTransformationMatrix();
		Vector3& getTranslation();
		MVTexture* getTexture();

	private:
		Mesh* p_mesh;
		MVTexture* p_texture;

		Vector3 translation;

		Matrix translationMatrix = Matrix(4, 4);
		Matrix rotationMatrix = Matrix(4, 4);
		Matrix scalingMatrix = Matrix(4, 4);

		Matrix transformationMatrix = Matrix(4, 4);

		void recalculateTransform();
};