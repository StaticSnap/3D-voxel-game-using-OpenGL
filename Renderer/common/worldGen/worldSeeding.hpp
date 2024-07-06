//worldSeeding.hpp
//created 7/5/2024 last edited 7/5/2024
//this class uses perlin noise to generate a 3d array determining what blocks go to what coordinates
//this is then passed to bufferGen to create the buffer that will then be exchanged for main to compute

#ifndef WORLDSEEDING_HPP
#define WORLDSEEDING_HPP

class WorldSeeding {
public:
	WorldSeeding(int seed = 0);
	~WorldSeeding();

	GLuint getMasterVertexBufferID();
	GLuint getmasterColorBufferID();

	int getCubeCount();

private:
	short*** levelDat = new short** [256];

	GLuint masterVertexBufferID;
	GLuint masterColorBufferID;

	int cubeCount = 0;
};


#endif
