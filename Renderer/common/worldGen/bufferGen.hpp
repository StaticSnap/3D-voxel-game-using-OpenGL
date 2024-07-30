//bufferGen.hpp 
//created 7/4/2024 last editied 7/29/2024
//takes in data of what cubes to generate where adn tehn creates all of the required cube objects 
//and then combines their data into one buffer for openGL to render all at once

#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdlib.h>
#include "cube.hpp"
#include "worldSeeding.hpp"

#include <iostream>

#ifndef BUFFERGEN_HPP
#define BUFFERGEN_HPP

class BufferGen {

public:
	BufferGen(int newWorldWidth, int newWorldHeight);

	std::vector<int> getVertexCount();

	void threadDataUpdate();

	void updateBuffers();

	std::vector<GLuint> getChunkBufferVert();
	std::vector<GLuint> getChunkBufferCol();
private:
	GLuint masterVertexBufferID;
	GLuint masterColorBufferID;

	std::vector<int> vertCountTotal;

	int bufferOffset = 0;

	glm::vec3 prevChunk;

	std::vector<GLuint> chunkBuffersVert;
	std::vector<GLuint> chunkBuffersCol;

	WorldSeeding* seed;

	int worldWidth;
	int worldHeight;

	//list of all chunks withen the player range
	std::vector<glm::vec3> chunksInView;

	//buffers for all of the vertex and color data
	std::vector<std::vector<GLfloat>> vertexBuff;
	std::vector<std::vector<GLfloat>> colorBuff;



	bool different;
	bool changing;

	bool isInBounds(glm::vec3 chunk);
};


#endif