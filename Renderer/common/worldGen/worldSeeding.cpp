#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdlib.h>
#include "worldSeeding.hpp"
#include "bufferGen.hpp"


WorldSeeding::WorldSeeding(int seed) {
	masterVertexBufferID = -1;
	masterColorBufferID = -1;


	//init the 3d array on the heap
	for (int i = 0; i < 256; i++) {
		levelDat[i] = new short* [100];
		for (int j = 0; j < 100; j++) {
			levelDat[i][j] = new short[256];
		}
	}

	//set all values to 0, the air block
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 256; k++) {
				levelDat[i][j][k] = 0;
			}
		}
	}

	//fill the values this will be perlin eventually
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			levelDat[i][1][j] = 1;
		}
	}

	BufferGen terrain(levelDat);

	masterVertexBufferID = terrain.getVertexBufferID();
	masterColorBufferID = terrain.getColorBufferID();

	cubeCount = terrain.getCubeCount();
}

WorldSeeding::~WorldSeeding() {
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 100; j++) {
			delete[] levelDat[i][j];
		}
		delete[] levelDat[i];
	}
	delete[] levelDat;
}

GLuint WorldSeeding::getMasterVertexBufferID() {
	return masterVertexBufferID;
}

GLuint WorldSeeding::getmasterColorBufferID() {
	return masterColorBufferID;
}

int WorldSeeding::getCubeCount() {
	return cubeCount;
}