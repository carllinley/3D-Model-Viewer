#pragma once

#include "Model.h"
#include "Light.h"
#include "TGAReader.h"

#include <unordered_map>
#include <vector>
#include <iostream>

/*
 Stores textures to avoid re-loading images, re-creating textures, and wasting memory.
 May look hauntingly familiar... exactly the same system as in the GUI framework.
 */
struct MVTextureManager {
	std::unordered_map<std::string, MVTexture*> textures;

	~MVTextureManager() {
		for (auto kv : textures) {
			delete kv.second;
		}
	}

	MVTexture* get(const std::string& filePath) {
		if (textures[filePath] == nullptr) {
			load(filePath);
		}
		return textures[filePath];
	}

	MVTexture* load(const std::string& filePath) {
		MVTexture* texture = new MVTexture();

		unsigned char* buffer = nullptr;
		int bitsPerPixel = 0;
		int channelsPerPixel = 0;

		EImageReaderStatus result = ImageReader::LoadTGA(filePath.c_str(), &buffer, &texture->width, &texture->height, &bitsPerPixel, &channelsPerPixel);

		if (result == E_IMAGEREADER_SUCCESS) {
			glGenTextures(1, &texture->glID);
			glBindTexture(GL_TEXTURE_2D, texture->glID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

			textures[filePath] = texture;

			std::cout << "Loaded texture '" << filePath << "'\n" << texture->width << "x" << texture->height << ", BPP: " << bitsPerPixel << ", CPP: " << channelsPerPixel << ", Texture ID: " << texture->glID << std::endl;
			return texture;
		}
		else {
			std::cout << "Failed to load texture '" << filePath << "'." << std::endl;
			delete texture;
			return nullptr;
		}
	}
};

struct MeshManager {
	public:
		Mesh* get(const char* filePath) {
			if (meshList[filePath] == nullptr) {
				meshList[filePath] = new Mesh(filePath);
			}
			return meshList[filePath];
		}

	private:
		std::unordered_map<const char*, Mesh*> meshList;
};

class ModelViewer {
	friend class Mesh;

	public:
		ModelViewer();
		~ModelViewer();

		void render();

		Model* createModel(const char* filePath);
		Model* loadModel(const std::string& modelName);
		void setTexture(const std::string& texture);

		void scroll(bool toZ);

		void rotate(float x, float y, float z);
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);

		void setWireframe(bool wireframe);
		void setIdlySpinning(bool idleSpin);
		void setLighting(bool lighting);
		void setCulling(bool culling);
		void setClockwise(bool drawClockwise);

	private:
		Light light;

		Model* model;
		Model* next;

		MeshManager meshManager;
		MVTextureManager textureManager;

		bool renderWireframe,
			 idleSpin = true,
			 useLighting = true,
			 useCulling = true,
			 drawClockwise = true,
			 useVertexLighting = true;

		float spinX, spinY, spinZ;
};