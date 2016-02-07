#include "ModelViewer.h"
#include "Vector3.h"

#include <Windows.h>
#include <gl\GL.h>
#include <iostream>

GLfloat ambientColour[4] = {0.0f, 0.0f, 0.0f, 0.0f};
GLfloat specularColour[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat diffuseColour[4] = {1.0f, 1.0f, 1.0f, 1.0f};

ModelViewer::ModelViewer() {
	model = loadModel("TEAPOT");
	next = nullptr;

	model->setTranslation(Vector3(0, 0, -100));
	model->setScale(Vector3(0.1f, 0.1f, 0.1f));

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColour);
}

ModelViewer::~ModelViewer() {
}

Model* ModelViewer::loadModel(const std::string& modelName) {
	next = createModel(modelName.c_str());
	return next;
}

void ModelViewer::setTexture(const std::string& texture) {
	Model* alter = (next != nullptr ? next : model); // No point changing death row's texture
	alter->setTexture(texture != "" ? textureManager.get("textures/" + texture + ".tga") : nullptr);
}

void ModelViewer::rotate(float x, float y, float z) {
	model->setRotation(Vector3(x, y, z));
}

void ModelViewer::translate(float x, float y, float z) {
	model->setTranslation(Vector3(x, y, z));
}

void ModelViewer::scale(float x, float y, float z) {
	model->setScale(Vector3(x, y, z));
}

void ModelViewer::setWireframe(bool wireframe) {
	this->renderWireframe = wireframe;
}

void ModelViewer::setIdlySpinning(bool idleSpin) {
	this->idleSpin = idleSpin;
}

void ModelViewer::setLighting(bool useLighting) {
	this->useLighting = useLighting;
}

void ModelViewer::setCulling(bool useCulling) {
	this->useCulling = useCulling;
}

void ModelViewer::setClockwise(bool drawClockwise) {
	this->drawClockwise = drawClockwise;
}

void ModelViewer::render() {
	if (next != nullptr) { // Changing model
		delete model;
		model = next;
		next = nullptr;
	}

	glColor3f(1.0f, 1.0f, 1.0f);

	if (idleSpin) {
		spinX += 0.005f;
		spinY += 0.01f;
		spinZ += 0.025f;
		model->setRotation(Vector3(spinX, spinY, spinZ));
	}

	if (useLighting) {
		Vector3 lighting = model->getTranslation() - light.getPosition();
		GLfloat position[4] = {lighting.getX(), lighting.getY(), lighting.getZ(), 1.0f};

		glEnable(GL_LIGHTING);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColour);

		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColour);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularColour);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColour);
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColour);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
	}
	else {
		glDisable(GL_LIGHTING);
	}
	model->getMesh()->render(model->getTransformationMatrix(), this, model->getTexture());
}

Model* ModelViewer::createModel(const char* fileName) {
	return new Model(meshManager.get(std::string("models/" + std::string(fileName) + ".obj").c_str()));
}
