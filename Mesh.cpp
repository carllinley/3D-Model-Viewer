#include "Mesh.h"
#include "OBJFileReader.h"
#include "Vector3.h"
#include "ModelViewer.h"

#include <Windows.h>
#include <gl/GL.h>

#include <iostream>
#include <set>
#include <unordered_map>

Mesh::Mesh(const char* fileName) {
	if (!load(fileName)) {
		p_vertexList = NULL;
		p_triangleList = NULL;
		triangleCount = 0;
		vertexCount = 0;
		texCoordCount = 0;

		std::cout << "Failed to load mesh '" << fileName << "'." << std::endl;
	}
	else {
		computeTriangleNormals();
		computeVertexNormals();
	}
}

Mesh::~Mesh() {
	delete[] p_vertexList;
	delete[] p_triangleList;
}

// Not great - struggles with big meshes.

void Mesh::render(const Matrix& transformationMatrix, ModelViewer* p_modelViewer, MVTexture* p_texture) {
	if (p_modelViewer->renderWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	glFrontFace((p_modelViewer->drawClockwise ? GL_CW : GL_CCW));

	if (p_modelViewer->useCulling) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	if (p_texture != nullptr) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, p_texture->glID);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glBegin(GL_TRIANGLES);

	for (int i = 0; i != triangleCount; i++) {
		if (!p_modelViewer->useVertexLighting) {
			glNormal3f(p_triangleList[i].normal.getX(), p_triangleList[i].normal.getY(), p_triangleList[i].normal.getZ());
		}

		for (int j = 0; j != 3; j++) {
			int index = p_triangleList[i].vertexIndices[j];

			Vector4 transformedVertex = p_vertexList[index].position.mult(transformationMatrix);

			if (p_modelViewer->useVertexLighting) {
				glNormal3f(p_vertexList[index].normal.getX(), p_vertexList[index].normal.getY(), p_vertexList[index].normal.getZ());
			}
			if (texCoordCount > 0 && p_texture != nullptr) {
				int texIndex = p_triangleList[i].texIndices[j];

				glTexCoord2f(p_texCoordList[texIndex].getX(), p_texCoordList[texIndex].getY());
			}
			glVertex4f(transformedVertex.getX(), transformedVertex.getY(), transformedVertex.getZ(), transformedVertex.getW());
		}
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Mesh::computeTriangleNormals() {
	long start = GetTickCount();

	for (int i = 0; i != triangleCount; i++) {
		Vector3 vertexA = Vector3(p_vertexList[p_triangleList[i].vertexIndices[0]].position);
		Vector3 vertexB = Vector3(p_vertexList[p_triangleList[i].vertexIndices[1]].position);
		Vector3 vertexC = Vector3(p_vertexList[p_triangleList[i].vertexIndices[2]].position);
		
		p_triangleList[i].normal.set(((vertexB - vertexA).crossLocal(vertexC - vertexA)).normaliseLocal());
	}
	std::cout << "Computed triangle normals in " << (GetTickCount() - start) << "ms." << std::endl;
}

void Mesh::computeVertexNormals() {
	long start = GetTickCount();

	std::unordered_map<int, std::set<int>> map; // <vertex index, <triangles using it>>

	for (int i = 0; i != triangleCount; i++) {
		for (int j = 0; j != 3; j++) {
			map[p_triangleList[i].vertexIndices[j]].emplace(i);
		}
	}
	
	for (int i = 0; i != vertexCount; i++) {
		std::set<int>& tris = map[i];
		Vector3 vertexNormal = Vector3();

		for (int j = 0; j != tris.size(); j++) {
			vertexNormal.addLocal(p_triangleList[j].normal);
		}
		p_vertexList[i].normal.set(vertexNormal.divideLocal((float) tris.size()));
	}
	std::cout << "Computed vertex normals in " << (GetTickCount() - start) << "ms." << std::endl;
}

bool Mesh::load(const char* filename) {
	int numVertices = 0,
		numNormals = 0,
		numTexCoords = 0,
		numTriangles = 0;

	if (OBJFileReader::firstPassOBJRead(filename, &numVertices, &numNormals, &numTexCoords, &numTriangles)) {
		printf("Error parsing file: %s\n", filename);
		return false;
	}
	
	if (p_vertexList && p_triangleList) { // Allocate memory for p_vertexList and p_triangleList
		printf("Vertex array and triangle array have already been allocated.\n");
		return false;
	}

	p_vertexList = new Vertex[numVertices];
	p_triangleList = new Triangle[numTriangles];
	p_texCoordList = new Vector2[numTexCoords];
	
	if (OBJFileReader::secondPassOBJRead(filename, p_vertexList, p_triangleList, p_texCoordList)) {
		printf("Error parsing file: %s\n", filename);
		return false;
	}
	triangleCount = numTriangles;
	vertexCount = numVertices;
	texCoordCount = numTexCoords;
	
	std::cout << "Successfully loaded mesh '" << filename << "'." << std::endl << "Vertices: " << vertexCount << " / Triangles: " << triangleCount << " / Tex coords: " << numTexCoords << std::endl;
	return true;
}