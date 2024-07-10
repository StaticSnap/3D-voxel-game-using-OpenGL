#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdlib.h>
#include "bufferGen.hpp"
#include "cube.hpp"

BufferGen::BufferGen(short*** levelDat, int worldWidth, int worldHeight) {
	const GLfloat cubeVertexDefault[6][18] = {
		//top
		{-0.5f,0.5f,-0.5f,
		-0.5f,0.5f,0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,
		-0.5f,0.5f,0.5f,
		0.5f,0.5f,-0.5f},

		//left
		{-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f},

		//front
		{-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f},

		//right
		{0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,0.5f},

		//back
		{0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,
		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f},

		//bottom
		{-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f}
	};

	//itterate over whole world to determine amount of verticies in existance
	for (int i = 0; i < worldWidth; i++) {
		for (int j = 0; j < worldHeight; j++) {
			for (int k = 0; k < worldWidth; k++) {
				if (levelDat[i][j][k] != 0) {
					if (i > 0 && levelDat[i - 1][j][k] == 0) {
						vertexCount += 18;
					}
					if (i < worldWidth - 1 && levelDat[i + 1][j][k] == 0) {
						vertexCount += 18;
					}
					if (j > 0 && levelDat[i][j - 1][k] == 0) {
						vertexCount += 18;
					}
					if (j < worldHeight - 1 && levelDat[i][j + 1][k] == 0) {
						vertexCount += 18;
					}
					if (k > 0 && levelDat[i][j][k - 1] == 0) {
						vertexCount += 18;
					}
					if (k < worldWidth - 1 && levelDat[i][j][k + 1] == 0) {
						vertexCount += 18;
					}
				}
			}
		}
	}
	//------------------------------------------------------------------

	

	//init the two bufferIDs but don't store any data inside yet
	glGenBuffers(1, &masterVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, masterVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);

	glGenBuffers(1, &masterColorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, masterColorBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);
	//-----------------------------------------------------------

	//buffers for all of the vertex and color data
	std::vector<GLfloat> vertexBuff;
	std::vector<GLfloat> colorBuff;

	//iterate over every position in the world
	for (int i = 0; i < worldWidth; i++) {
		for (int j = 0; j < worldHeight; j++) {
			for (int k = 0; k < worldWidth; k++) {
				//if the given position contains a block that is not air
				if (levelDat[i][j][k] != 0) {
					//faceVisibility: 0 top, 1 left, 2 front, 3 right, 4 back, 5 bottom
					bool faceVisibility[6] = { false,false,false,false,false,false };
					if (i > 0 && levelDat[i - 1][j][k] == 0) {
						faceVisibility[1] = true;
					}
					if (i < worldWidth - 1 && levelDat[i + 1][j][k] == 0) {
						faceVisibility[3] = true;
					}
					if (j > 0 && levelDat[i][j - 1][k] == 0) {
						faceVisibility[5] = true;
					}
					if (j < worldHeight - 1 && levelDat[i][j + 1][k] == 0) {
						faceVisibility[0] = true;
					}
					if (k > 0 && levelDat[i][j][k - 1] == 0) {
						faceVisibility[2] = true;
					}
					if (k < worldWidth - 1 && levelDat[i][j][k + 1] == 0) {
						faceVisibility[4] = true;
					}

					if (faceVisibility[0] == false && faceVisibility[1] == false && faceVisibility[2] == false && faceVisibility[3] == false && faceVisibility[4] == false && faceVisibility[5] == false) {
						//this block has blocks on every side of it. don't draw
					}
					else {
						//(this needs to be rewritten once I have more block types)
						//initiate array for block data and then the position
						float cubeDat[6];
						cubeDat[3] = i;
						cubeDat[4] = j;
						cubeDat[5] = k;
						//depending on the type of block, the color will be different
						if (levelDat[i][j][k] == 1) {
							cubeDat[0] = (rand() % 40) / 40.0 + 0.3;
							cubeDat[1] = (rand() % 40) / 40.0 + 0.3;
							cubeDat[2] = (rand() % 40) / 40.0 + 0.3;
						}
						else {
							//other block types
						}

						//make a block using the position and color data given
						//Cube* block = new Cube(cubeDat[0], cubeDat[1], cubeDat[2], cubeDat[3], cubeDat[4], cubeDat[5], faceVisibility);
						std::vector<GLfloat> colorBufferData;
						std::vector<GLfloat> vertexBufferData;
						
						for (int i = 0; i < 6; i++) {
							if (faceVisibility[i] == true) {
								for (int j = 0; j < 18; j++) {
									if (j % 3 == 0) {
										vertexBufferData.push_back(cubeVertexDefault[i][j] + cubeDat[3]);
										colorBufferData.push_back(cubeDat[0]);
									}
									else if (j % 3 == 1) {
										vertexBufferData.push_back(cubeVertexDefault[i][j] + cubeDat[4]);
										colorBufferData.push_back(cubeDat[1]);
									}
									else {
										vertexBufferData.push_back(cubeVertexDefault[i][j] + cubeDat[5]);
										colorBufferData.push_back(cubeDat[2]);
									}
								}
							}
						}


						//fill the temp buffers with the data for the cube
						for (int l = 0; l < vertexBufferData.size(); l++) {
							vertexBuff.push_back(vertexBufferData[l]);
							colorBuff.push_back(colorBufferData[l]);
						}

						//update the master buffer to contain the new data
						glBindBuffer(GL_ARRAY_BUFFER, masterVertexBufferID);
						glBufferSubData(GL_ARRAY_BUFFER, bufferOffset * sizeof(GLfloat), vertexBuff.size() * sizeof(GLfloat), vertexBuff.data());

						glBindBuffer(GL_ARRAY_BUFFER, masterColorBufferID);
						glBufferSubData(GL_ARRAY_BUFFER, bufferOffset * sizeof(GLfloat), colorBuff.size() * sizeof(GLfloat), colorBuff.data());
						//the bufferoffset needs to be kept track of to properly add to the OpenGL buffer object
						bufferOffset += vertexBufferData.size();

						vertexBuff.clear();
						colorBuff.clear();

						//delete block;
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

int BufferGen::getVertexCount() {
	return vertexCount;
}