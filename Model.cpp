#include "Model.h"

#include <iostream>
#include <cmath>

Model::Model(Mesh* mesh) {
	p_mesh = mesh;

	translationMatrix.toIdentity();
	scalingMatrix.toIdentity();
	rotationMatrix.toIdentity();
}

void Model::setTranslation(Vector3& localTranslation) {
	translation.set(localTranslation);

	translationMatrix.setElement(0, 3, localTranslation.getX());
	translationMatrix.setElement(1, 3, localTranslation.getY());
	translationMatrix.setElement(2, 3, localTranslation.getZ());

	recalculateTransform();
}

void Model::setScale(Vector3& scale) {
	scalingMatrix.toIdentity();

	scalingMatrix.setElement(0, 0, scale.getX());
	scalingMatrix.setElement(1, 1, scale.getY());
	scalingMatrix.setElement(2, 2, scale.getZ());

	recalculateTransform();
}

void Model::setScale(float scale) {
	scalingMatrix.toIdentity();

	scalingMatrix.setElement(0, 0, scale);
	scalingMatrix.setElement(1, 1, scale);
	scalingMatrix.setElement(2, 2, scale);

	recalculateTransform();
}

void Model::setRotation(Vector3& rotation) {
	rotationMatrix.toIdentity();

	float cosX = cos(rotation.getX()), sinX = sin(rotation.getX()); // No point calculating repeatedly
	float cosY = cos(rotation.getY()), sinY = sin(rotation.getY());
	float cosZ = cos(rotation.getZ()), sinZ = sin(rotation.getZ());

	Matrix xMatrix = Matrix(rotationMatrix),
		   yMatrix = Matrix(rotationMatrix),
		   zMatrix = Matrix(rotationMatrix);

	// X
	xMatrix.setElement(1, 1, cosX);
	xMatrix.setElement(1, 2, sinX);
	xMatrix.setElement(2, 1, -sinX);
	xMatrix.setElement(2, 2, cosX);

	// Y
	yMatrix.setElement(0, 0, cosY);
	yMatrix.setElement(0, 2, sinY);
	yMatrix.setElement(2, 0, -sinY);
	yMatrix.setElement(2, 2, cosY);

	// Z
	zMatrix.setElement(0, 0, cosZ);
	zMatrix.setElement(0, 1, -sinZ);
	zMatrix.setElement(1, 0, sinZ);
	zMatrix.setElement(1, 1, cosZ);

	rotationMatrix = xMatrix * yMatrix * zMatrix;
	recalculateTransform();
}

Vector3& Model::getTranslation() {
	return translation;
}

MVTexture* Model::getTexture() {
	return p_texture;
}

Mesh* Model::getMesh() {
	return p_mesh;
}

Matrix& Model::getTransformationMatrix() {
	return transformationMatrix;
}

Matrix& Model::getRotationMatrix() {
	return rotationMatrix;
}

void Model::setTexture(MVTexture* p_texture) {
	this->p_texture = p_texture;
	std::cout << "Texture: " << p_texture << std::endl;
}

void Model::recalculateTransform() {
	transformationMatrix = translationMatrix * rotationMatrix * scalingMatrix;
}