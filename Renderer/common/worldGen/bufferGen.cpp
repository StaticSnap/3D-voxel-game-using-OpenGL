#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "bufferGen.hpp"
#include "cube.hpp"

BufferGen::BufferGen(short*** levelDat) {

	//itterate over whole world to determine amount of cubes in existance
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 256; k++) {
				//this needs to be rewritten once I have more block types
				if (levelDat[i][j][k] != 0) {
					cubeCount++;
				}
			}
		}
	}

	

	//init the two bufferIDs but don't store any data inside yet
	glGenBuffers(1, &masterVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, masterVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, cubeCount * 108 * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);

	glGenBuffers(1, &masterColorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, masterColorBufferID);
	glBufferData(GL_ARRAY_BUFFER, cubeCount * 108 * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);

	//buffers for all of the vertex and color data
	std::vector<GLfloat> vertexBuff;
	std::vector<GLfloat> colorBuff;

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 256; k++) {
				if (levelDat[i][j][k] != 0) {
					//this needs to be rewritten once I have more block types
					float cubeDat[6];
					cubeDat[3] = i;
					cubeDat[4] = j;
					cubeDat[5] = k;
					if (levelDat[i][j][k] == 1) {
						cubeDat[0] = 0.5;
						cubeDat[1] = 0.5;
						cubeDat[2] = 0.5;
					}
					else {
						//other block types
					}

					//make a block using the position and color data given
					//Cube block(cubeDat[0], cubeDat[1], cubeDat[2], cubeDat[3], cubeDat[4], cubeDat[5]);
					Cube* block = new Cube(cubeDat[0], cubeDat[1], cubeDat[2], cubeDat[3], cubeDat[4], cubeDat[5]);

					//fill the temp buffers with the data for 1 cube
					for (int l = 0; l < 108; l++) {
						vertexBuff.push_back(block->getVertexBufferData()[l]);
						colorBuff.push_back(block->getColorBufferData()[l]);
					}

					//update the master buffer to contain the new data
					glBindBuffer(GL_ARRAY_BUFFER, masterVertexBufferID);
					glBufferSubData(GL_ARRAY_BUFFER, bufferOffset * 108 * sizeof(GLfloat), vertexBuff.size() * sizeof(GLfloat), vertexBuff.data());

					glBindBuffer(GL_ARRAY_BUFFER, masterColorBufferID);
					glBufferSubData(GL_ARRAY_BUFFER, bufferOffset * 108 * sizeof(GLfloat), colorBuff.size() * sizeof(GLfloat), colorBuff.data());

					bufferOffset++;

					vertexBuff.clear();
					colorBuff.clear();

					delete block;
				}
			}
		}
	}

	vertexBuff.clear();
	colorBuff.clear();
}

GLuint BufferGen::getVertexBufferID() {
	return masterVertexBufferID;
}

GLuint BufferGen::getColorBufferID() {
	return masterColorBufferID;
}

int BufferGen::getCubeCount() {
	return cubeCount;
}