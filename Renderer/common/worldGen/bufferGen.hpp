//bufferGen.hpp 
//created 7/4/2024 last editied 7/6/2024
//takes in data of what cubes to generate where adn tehn creates all of the required cube objects 
//and then combines their data into one buffer for openGL to render all at once

#ifndef BUFFERGEN_HPP
#define BUFFERGEN_HPP

class BufferGen {

public:
	BufferGen(short*** levelDat, int worldWidth, int worldHeight);

	GLuint getVertexBufferID();
	GLuint getColorBufferID();

	int getVertexCount();

private:
	GLuint masterVertexBufferID;
	GLuint masterColorBufferID;

	int vertexCount = 0;
	int bufferOffset = 0;
};


#endif