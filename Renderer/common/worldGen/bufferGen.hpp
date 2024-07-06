//bufferGen.hpp 
//created 7/4/2024 last editied 7/4/2024
//takes in data of what cubes to generate where adn tehn creates all of the required cube objects 
//and then combines their data into one buffer for openGL to render all at once

#ifndef BUFFERGEN_HPP
#define BUFFERGEN_HPP

class BufferGen {

public:
	BufferGen(short*** levelDat);

	GLuint getVertexBufferID();
	GLuint getColorBufferID();

	int getCubeCount();

private:
	GLuint masterVertexBufferID;
	GLuint masterColorBufferID;

	int cubeCount = 0;
	int bufferOffset = 0;
};


#endif