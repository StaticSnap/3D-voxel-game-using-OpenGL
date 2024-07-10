//worldSeeding.hpp
//created 7/5/2024 last edited 7/6/2024
//this class uses perlin noise to generate a 3d array determining what blocks go to what coordinates
//this is then passed to bufferGen to create the buffer that will then be exchanged for main to compute

#ifndef WORLDSEEDING_HPP
#define WORLDSEEDING_HPP

class WorldSeeding {
public:
	WorldSeeding(int newWorldWidth, int newWorldHeight);
	~WorldSeeding();

	GLuint getMasterVertexBufferID();
	GLuint getmasterColorBufferID();

	int getWorldWidth();
	int getWorldHeight();

	int getVertexCount();

private:
	int worldWidth;
	int worldHeight;
	short*** levelDat;

	GLuint masterVertexBufferID;
	GLuint masterColorBufferID;

	int vertexCount = 0;
};


#endif
