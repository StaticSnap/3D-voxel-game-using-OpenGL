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
	//------------------------------

	//set all values to 0, the air block
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 256; k++) {
				levelDat[i][j][k] = 0;
			}
		}
	}
	//----------------------------------

	////fill the values this will be perlin eventually
	//for (int i = 0; i < 256; i++) {
	//	for (int j = 0; j < 256; j++) {
	//		levelDat[i][rand() % 100][j] = 1;
	//	}
	//}
	////----------------------------------------------

	short** noiseGrid = new short*[8];
	for (int i = 0; i < 8; i++) {
		noiseGrid[i] = new short[8];
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			noiseGrid[i][j] = rand() % 100;
		}
	}

	for (int i = 0; i < 256; i++) {
		for (int k = 0; k < 256; k++) {
			short xIndex = short(trunc(i / 32.0));
			short zIndex = short(trunc(k / 32.0));

			short c01 = noiseGrid[xIndex % 8][zIndex % 8];
			short c11 = noiseGrid[(xIndex+1) % 8][zIndex % 8];
			short c00 = noiseGrid[xIndex % 8][(zIndex+1) % 8];
			short c10 = noiseGrid[(xIndex+1) % 8][(zIndex+1) % 8];

			float t = i % 32 / 32.0;

			float a = c01 * (1 - t) + c11 * t;
			float b = c00 * (1 - t) + c10 * t;

			float t2 = k % 32 / 32.0;

			short res = short(trunc(a * (1 - t2) + b * t2));

			levelDat[i][res][k] = 1;

			for (int l = 0; l < res; l++) {
				levelDat[i][l][k] = 1;
			}
		}
	}







	BufferGen terrain(levelDat);

	masterVertexBufferID = terrain.getVertexBufferID();
	masterColorBufferID = terrain.getColorBufferID();

	vertexCount = terrain.getVertexCount();

	for (int i = 0; i < 8; i++) {
		delete[] noiseGrid[i];
	}
	delete[] noiseGrid;
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

int WorldSeeding::getVertexCount() {
	return vertexCount;
}