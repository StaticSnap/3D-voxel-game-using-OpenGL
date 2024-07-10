#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdlib.h>
#include "worldSeeding.hpp"
#include "bufferGen.hpp"


WorldSeeding::WorldSeeding(int newWorldWidth, int newWorldHeight) {
	worldWidth = newWorldWidth;
	worldHeight = newWorldHeight;
	
	masterVertexBufferID = -1;
	masterColorBufferID = -1;


	//init the 3d array on the heap
	levelDat = new short**[worldWidth + 1];
	for (int i = 0; i < worldWidth + 1; i++) {
		levelDat[i] = new short* [worldHeight];
		for (int j = 0; j < worldHeight; j++) {
			levelDat[i][j] = new short[worldWidth];
		}
	}
	//------------------------------

	//set all values to 0, the air block
	for (int i = 0; i < worldWidth; i++) {
		for (int j = 0; j < worldHeight; j++) {
			for (int k = 0; k < worldWidth; k++) {
				levelDat[i][j][k] = 0;
			}
		}
	}
	//----------------------------------

	short** noiseGrid = new short* [8];
	for (int i = 0; i < 8; i++) {
		noiseGrid[i] = new short[8];
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			noiseGrid[i][j] = rand() % worldHeight;
		}
	}

	for (int i = 0; i < worldWidth; i++) {
		for (int k = 0; k < worldWidth; k++) {
			short xIndex = short(trunc(i / float(worldWidth) / 8.0));
			short zIndex = short(trunc(k / float(worldWidth) / 8.0));

			short c01 = noiseGrid[xIndex % 8][zIndex % 8];
			short c11 = noiseGrid[(xIndex+1) % 8][zIndex % 8];
			short c00 = noiseGrid[xIndex % 8][(zIndex+1) % 8];
			short c10 = noiseGrid[(xIndex+1) % 8][(zIndex+1) % 8];

			float t = i % (worldWidth / 8) / float(worldWidth / 8);

			float a = c01 * (1 - t) + c11 * t;
			float b = c00 * (1 - t) + c10 * t;

			float t2 = k % (worldWidth / 8) / float(worldWidth / 8);

			short res = short(trunc(a * (1 - t2) + b * t2)) % worldHeight;

			levelDat[i][res][k] = 1;

			for (int l = 0; l < res; l++) {
				levelDat[i][l][k] = 1;
			}
		}
	}


	BufferGen terrain(levelDat, worldWidth, worldHeight);

	masterVertexBufferID = terrain.getVertexBufferID();
	masterColorBufferID = terrain.getColorBufferID();

	vertexCount = terrain.getVertexCount();

	for (int i = 0; i < 8; i++) {
		delete[] noiseGrid[i];
	}
	delete[] noiseGrid;
}

WorldSeeding::~WorldSeeding() {
	/*for (int i = 0; i < worldWidth; i++) {
		for (int j = 0; j < worldHeight; j++) {
			delete[] levelDat[i][j];
		}
		delete[] levelDat[i];
	}*/
	delete[] levelDat;
}

GLuint WorldSeeding::getMasterVertexBufferID() {
	return masterVertexBufferID;
}

GLuint WorldSeeding::getmasterColorBufferID() {
	return masterColorBufferID;
}

int WorldSeeding::getWorldWidth() {
	return worldWidth;
}

int WorldSeeding::getWorldHeight() {
	return worldHeight;
}

int WorldSeeding::getVertexCount() {
	return vertexCount;
}