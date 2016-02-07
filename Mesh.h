/*
 Author: Minsi Chen, Carl Linley
 */

#pragma once

#include "MVTexture.h"

#include "gui/Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"

#include <vector>

class ModelViewer;

struct Triangle {
	Vector3 normal;
	int vertexIndices[3];
	int texIndices[3];

	void setIndices(int x, int y, int z) {
		vertexIndices[0] = x;
		vertexIndices[1] = y;
		vertexIndices[2] = z;
	}

	void setTexIndices(int x, int y, int z) {
		texIndices[0] = x;
		texIndices[1] = y;
		texIndices[2] = z;
	}
};

struct Vertex {
	Vector4 position;
	Vector3 normal;
};

class Mesh {
	public:
		Mesh(const char* filename);
		~Mesh();

		void render(const Matrix& transformationMatrix, ModelViewer* modelViewer, MVTexture* p_texture);

	private:
		Vertex* p_vertexList = NULL;
		Triangle* p_triangleList = NULL;
		Vector2* p_texCoordList = NULL;

		int vertexCount = 0,
			triangleCount = 0,
			texCoordCount = 0;

		bool load(const char* fileName);

		void computeTriangleNormals();
		void computeVertexNormals();
};
