#include "bufferGen.hpp"

extern glm::vec3 position;

BufferGen::BufferGen(int newWorldWidth, int newWorldHeight) {
	worldWidth = newWorldWidth;
	worldHeight = newWorldHeight;
	
	seed = new WorldSeeding(worldWidth, worldHeight);

	vertCountTotal = new int[1];

}

int* BufferGen::getVertexCount() {
	return vertCountTotal;
}

std::vector<GLuint> BufferGen::updateBuffers() {
	//cube vertex offsets
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

	//list of al chunks withen the player range
	std::vector<glm::vec3> chunksInView;
	//represents the chunk the player is currently in
	glm::vec3 chunk;
	chunk[0] = int(position[0] / 32);
	chunk[1] = int(position[1] / 32);
	chunk[2] = int(position[2] / 32);

	//if the chunk is in the negatives than subtract one from the chunk
	//because otherwise -0 would become 0 and the two chunks would merge
	//NOTE: this may mess with generation look into once negative values implemented
	if (position[0] < 0) {
		chunk[0]--;
	}
	if (position[1] < 0) {
		chunk[1]--;
	}
	if (position[2] < 0) {
		chunk[2]--;
	}

	//gather surrounding chunks and put into vector
	if (isInBounds(chunk)) {
		chunksInView.push_back(chunk);
	}
	if (isInBounds(glm::vec3(chunk[0], chunk[1] - 1, chunk[2]))) {
		chunksInView.push_back(glm::vec3(chunk[0], chunk[1] - 1, chunk[2]));
	}
	if (isInBounds(glm::vec3(chunk[0] - 1, chunk[1], chunk[2]))) {
		chunksInView.push_back(glm::vec3(chunk[0] - 1, chunk[1], chunk[2]));
	}
	if (isInBounds(glm::vec3(chunk[0], chunk[1], chunk[2] - 1))) {
		chunksInView.push_back(glm::vec3(chunk[0], chunk[1], chunk[2] - 1));
	}
	if (isInBounds(glm::vec3(chunk[0], chunk[1] + 1, chunk[2]))) {
		chunksInView.push_back(glm::vec3(chunk[0], chunk[1] + 1, chunk[2]));
	}
	if (isInBounds(glm::vec3(chunk[0] + 1, chunk[1], chunk[2]))) {
		chunksInView.push_back(glm::vec3(chunk[0] + 1, chunk[1], chunk[2]));
	}
	if (isInBounds(glm::vec3(chunk[0], chunk[1], chunk[2] + 1))) {
		chunksInView.push_back(glm::vec3(chunk[0], chunk[1], chunk[2] + 1));
	}

	if (chunksInView == prevChunksInView) {
		return chunkBuffersVert;
	}

	prevChunksInView.resize(chunksInView.size());
	for (int i = 0; i < chunksInView.size(); i++) {
		prevChunksInView[i] = chunksInView[i];
	}
	
	delete vertCountTotal;
	chunkBuffersVert.clear();
	chunkBuffersCol.clear();

	short**** chunkDat = seed->retrieveChunkData(chunksInView);

	vertCountTotal = new int[chunksInView.size()];

	int vertexCount = 0;

	//itterate over every chunk and count up total vertices 
	//TO FIX: border rendering
	for (int l = 0; l < chunksInView.size(); l++) {
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 32; j++) {
				for (int k = 0; k < 32; k++) {
					if (chunkDat[l][i][j][k] != 0) {
						if (i > 0 && chunkDat[l][i - 1][j][k] == 0 || i == 0) {
							vertexCount += 18;
						}
						if (i < 31 && chunkDat[l][i + 1][j][k] == 0 || i == 31) {
							vertexCount += 18;
						}
						if (j > 0 && chunkDat[l][i][j - 1][k] == 0 || j == 0) {
							vertexCount += 18;
						}
						if (j < 31 && chunkDat[l][i][j + 1][k] == 0 || j == 31) {
							vertexCount += 18;
						}
						if (k > 0 && chunkDat[l][i][j][k - 1] == 0 || k == 0) {
							vertexCount += 18;
						}
						if (k < 31 && chunkDat[l][i][j][k + 1] == 0 || k == 31) {
							vertexCount += 18;
						}
					}
				}
			}
		}
		vertCountTotal[l] = vertexCount;
		vertexCount = 0;
	}
	//------------------------------------------------------------------
	

	//buffers for all of the vertex and color data
	std::vector<GLfloat> vertexBuff;
	std::vector<GLfloat> colorBuff;


	//iterate over every position in render distance
	for (int l = 0; l < chunksInView.size(); l++) {
		//init the two buffers
		glGenBuffers(1, &masterVertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, masterVertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertCountTotal[l] * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);

		glGenBuffers(1, &masterColorBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, masterColorBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertCountTotal[l] * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);

		//read all of chunk data and generate buffer accordingly
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 32; j++) {
				for (int k = 0; k < 32; k++) {
					//if the given position contains a block that is not air
					if (chunkDat[l][i][j][k] != 0) {
						//faceVisibility: 0 top, 1 left, 2 front, 3 right, 4 back, 5 bottom
						bool faceVisibility[6] = { false,false,false,false,false,false };
						if (i > 0 && chunkDat[l][i - 1][j][k] == 0 || i == 0) {
							faceVisibility[1] = true;
						}
						if (i < 31 && chunkDat[l][i + 1][j][k] == 0 || i == 31) {
							faceVisibility[3] = true;
						}
						if (j > 0 && chunkDat[l][i][j - 1][k] == 0 || j == 0) {
							faceVisibility[5] = true;
						}
						if (j < 31 && chunkDat[l][i][j + 1][k] == 0 || j == 31) {
							faceVisibility[0] = true;
						}
						if (k > 0 && chunkDat[l][i][j][k - 1] == 0 || k == 0) {
							faceVisibility[2] = true;
						}
						if (k < 31 && chunkDat[l][i][j][k + 1] == 0 || k == 31) {
							faceVisibility[4] = true;
						}

						if (faceVisibility[0] == false && faceVisibility[1] == false && faceVisibility[2] == false && faceVisibility[3] == false && faceVisibility[4] == false && faceVisibility[5] == false) {
							//this block has blocks on every side of it. don't draw
						}
						else {
							//(this needs to be rewritten once I have more block types)
							//initiate array for block data and then the position
							float cubeDat[6];
							cubeDat[3] = float(i) + chunksInView[l][0] * 32;
							cubeDat[4] = float(j) + chunksInView[l][1] * 32;
							cubeDat[5] = float(k) + chunksInView[l][2] * 32;
							//depending on the type of block, the color will be different
							if (chunkDat[l][i][j][k] == 1) {
								cubeDat[0] = float((rand() % 40) / 40.0);
								cubeDat[1] = float((rand() % 40) / 40.0);
								cubeDat[2] = float((rand() % 40) / 40.0);
							}
							else {
								//other block types
							}

							//make a block using the position and color data given
							Cube* block = new Cube(cubeDat[0], cubeDat[1], cubeDat[2], int(cubeDat[3]), int(cubeDat[4]), int(cubeDat[5]), faceVisibility);

							std::vector<GLfloat> colorBufferData;
							std::vector<GLfloat> vertexBufferData;

							for (int i = 0; i < 6; i++) {
								if (block->getFaceVisibility()[i] == true) {
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
							//the buffer offset needs to be kept track of to properly add to the OpenGL buffer object
							bufferOffset += int(vertexBufferData.size());

							vertexBuff.clear();
							colorBuff.clear();

							
						}
					}
				}
			}
		}
		chunkBuffersVert.push_back(masterVertexBufferID);
		chunkBuffersCol.push_back(masterColorBufferID);
		bufferOffset = 0;
	}
	
	chunksInView.clear();

	return chunkBuffersVert;
}

std::vector<GLuint> BufferGen::getChunkBufferVert() {
	return chunkBuffersVert;
}

std::vector<GLuint> BufferGen::getChunkBufferCol() {
	return chunkBuffersCol;
}

bool BufferGen::isInBounds(glm::vec3 chunk) {
	if (chunk[0] < 0 || chunk[0] >= worldWidth / 32) {
		return false;
	}
	if (chunk[1] < 0 || chunk[1] >= worldHeight / 32) {
		return false;
	}
	if (chunk[2] < 0 || chunk[2] >= worldWidth / 32) {
		return false;
	}
	return true;
}