#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdlib.h>
#include "bufferGen.hpp"
#include "cube.hpp"

BufferGen::BufferGen(short*** levelDat) {

	//itterate over whole world to determine amount of cubes in existance
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 256; k++) {
				if (levelDat[i][j][k] != 0) {
					if ((i > 1 && levelDat[i - 1][j][k] != 0) && (i < 254 && levelDat[i + 1][j][k] != 0) && (j > 1 && levelDat[i][j - 1][k] != 0) && (j < 254 && levelDat[i][j + 1][k] != 0) && (k > 1 && levelDat[i][j][k - 1] != 0) && (k < 254 && levelDat[i][j][k + 1] != 0)) {
						//this block has blocks on every side of it. don't draw
					}
					else {
						cubeCount += 108;
					}
				}
			}
		}
	}
	//------------------------------------------------------------------

	

	//init the two bufferIDs but don't store any data inside yet
	glGenBuffers(1, &masterVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, masterVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, cubeCount * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);

	glGenBuffers(1, &masterColorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, masterColorBufferID);
	glBufferData(GL_ARRAY_BUFFER, cubeCount * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);
	//-----------------------------------------------------------

	//buffers for all of the vertex and color data
	std::vector<GLfloat> vertexBuff;
	std::vector<GLfloat> colorBuff;

	//iterate over every position in the world
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 256; k++) {
				//if the given position contains a block that is not air
				if (levelDat[i][j][k] != 0) {
					//don't render if block is fully encased
					if ((i > 1 && levelDat[i - 1][j][k] != 0) && (i < 254 && levelDat[i+1][j][k] != 0) && (j > 1 && levelDat[i][j-1][k] != 0) && (j < 254 && levelDat[i][j+1][k] != 0) && (k > 1 && levelDat[i][j][k-1] != 0) && (k < 254 && levelDat[i][j][k+1] != 0)) {
						//this block has blocks on every side of it. don't draw
					}
					else {
						//(this needs to be rewritten once I have more block types)
					//initiate array for block data and then the position
						float cubeDat[6];
						cubeDat[3] = i;
						cubeDat[4] = j;
						cubeDat[5] = k;
						//depending on the typ eof block, the color will be different
						if (levelDat[i][j][k] == 1) {
							cubeDat[0] = (rand() % 40) / 40.0 + 0.3;
							cubeDat[1] = (rand() % 40) / 40.0 + 0.3;
							cubeDat[2] = (rand() % 40) / 40.0 + 0.3;
						}
						else {
							//other block types
						}

						//make a block using the position and color data given
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
						//the bufferoffset needs to be kept track of to properly add to the OpenGL buffer object
						bufferOffset++;

						vertexBuff.clear();
						colorBuff.clear();

						delete block;
					}
				}
			}
		}
	}
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