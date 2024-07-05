#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "bufferGen.hpp"
#include "cube.hpp"

BufferGen::BufferGen() {
	//vector to store block data in
	std::vector<Cube> blocks;

	//init cube amount
	cubeCount = 0;

	//temporarilly creates cubes here hard coded
	Cube c1(0.2, 0.5, 1, 0, 0, 0);
	Cube c2(0.5, 0.3, 1, 4, 4, 4);

	//adds blocks to vector
	blocks.push_back(c1);
	blocks.push_back(c2);

	//increase cube count to be the amount of cubes. referenced by main
	cubeCount = 2;

	//buffers for all of the vertex and color data
	std::vector<GLfloat> vertexBuff;
	std::vector<GLfloat> colorBuff;

	//iterate over each block and put data from each into the two buffers
	for (auto item : blocks) {
		GLfloat* VertexEntry = item.getVertexBufferData();
		GLfloat* ColorEntry = item.getColorBufferData();

		//each cube has 108 points to create 36 spacial points which creates 12 triangles for each cube
		for (int i = 0; i < 108; i++) {
			vertexBuff.push_back(VertexEntry[i]);
			colorBuff.push_back(ColorEntry[i]);
		}
	}

	//using the data in the two buffer vectors create a bufferID to pass to openGL in main.
	glGenBuffers(1, &masterVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, masterVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexBuff.size() * sizeof(GLfloat), vertexBuff.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &masterColorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, masterColorBufferID);
	glBufferData(GL_ARRAY_BUFFER, colorBuff.size() * sizeof(GLfloat), colorBuff.data(), GL_STATIC_DRAW);

	//clear the now redundant vectors.
	vertexBuff.clear();
	colorBuff.clear();
	blocks.clear();
}

GLuint BufferGen::getVertexBufferID() {
	return masterVertexBufferID;
}

GLuint BufferGen::getColorBufferID() {
	return masterColorBufferID;
}