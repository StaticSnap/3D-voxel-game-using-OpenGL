//worldSeeding.hpp
//created 7/5/2024 last edited 7/14/2024
//this class uses perlin noise to generate a 3d array determining what blocks go to what coordinates
//this is then passed to bufferGen to create the buffer that will then be exchanged for main to compute

#include <vector> 

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdlib.h>

#include <iostream>

#ifndef WORLDSEEDING_HPP
#define WORLDSEEDING_HPP

class WorldSeeding {
public:
	WorldSeeding(int newWorldWidth = 100, int newWorldHeight = 100);
	~WorldSeeding();

	GLuint getMasterVertexBufferID();
	GLuint getmasterColorBufferID();

	int getWorldWidth();
	int getWorldHeight();

	int getVertexCount();

	short**** retrieveChunkData(std::vector<glm::vec3> chunkList);

private:
	int worldWidth;
	int worldHeight;
	short*** levelDat;
	short** noiseGrid;

	GLuint masterVertexBufferID;
	GLuint masterColorBufferID;

	int vertexCount = 0;
};


#endif
