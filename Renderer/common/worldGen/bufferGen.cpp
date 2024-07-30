#include "bufferGen.hpp"

extern glm::vec3 position;

BufferGen::BufferGen(int newWorldWidth, int newWorldHeight) {
	worldWidth = newWorldWidth;
	worldHeight = newWorldHeight;
	
	seed = new WorldSeeding(worldWidth, worldHeight);


	different = false;
	changing = false;

	masterVertexBufferID = -1;
	masterColorBufferID = -1;

	prevChunk = glm::vec3(0, 0, 0);
}

std::vector<int> BufferGen::getVertexCount() {
	return vertCountTotal;
}

void BufferGen::threadDataUpdate() {
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

	//represents the chunk the player is currently in
	glm::vec3 chunk;
	chunk[0] = int(position[0] / 32);
	chunk[1] = int(position[1] / 32);
	chunk[2] = int(position[2] / 32);

	if (chunk == prevChunk) {
		return;
	}

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

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (isInBounds(glm::vec3(chunk[0] + i - 2, chunk[1] + j - 2, chunk[2] + k -2))) {
					chunksInView.push_back(glm::vec3(chunk[0] + i - 2, chunk[1] + j - 2, chunk[2] + k - 2));
				}
			}
		}
	}

	prevChunk = chunk;

	changing = true;
	different = true;




	short**** chunkDat = seed->retrieveChunkData(chunksInView);

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
		vertexCount = 0;
	}
	//------------------------------------------------------------------

	vertexBuff.clear();
	colorBuff.clear();

	vertexBuff.resize(chunksInView.size());
	colorBuff.resize(chunksInView.size());


	//iterate over every position in render distance
	for (int l = 0; l < chunksInView.size(); l++) {
		//read all of chunk data and generate data accordingly
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
								cubeDat[0] = float(rand() % 40 / 40.0);
								cubeDat[1] = float(rand() % 40 / 40.0);
								cubeDat[2] = float(rand() % 40 / 40.0);

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
							for (int n = 0; n < vertexBufferData.size(); n++) {
								vertexBuff[l].push_back(vertexBufferData[n]);
								colorBuff[l].push_back(colorBufferData[n]);
							}
						}
					}
				}
			}
		}
	}

	chunksInView.clear();

	changing = false;
	
}

void BufferGen::updateBuffers() {
	//this returns if no new data to render
	if (!different) {
		return;
	}
	//this returns if there is new data but the thread is still writing it
	//basically serving as a lock
	else if (changing){
		
		return;
	}
	else {
		chunkBuffersVert.clear();
		chunkBuffersCol.clear();
		vertCountTotal.clear();
		for (int l = 0; l < vertexBuff.size(); l++) {
			//init the two buffers
			glGenBuffers(1, &masterVertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, masterVertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, vertexBuff[l].size() * sizeof(GLfloat), vertexBuff[l].data(), GL_STATIC_DRAW);

			glGenBuffers(1, &masterColorBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, masterColorBufferID);
			glBufferData(GL_ARRAY_BUFFER, vertexBuff[l].size() * sizeof(GLfloat), colorBuff[l].data(), GL_STATIC_DRAW);

			chunkBuffersVert.push_back(masterVertexBufferID);
			chunkBuffersCol.push_back(masterColorBufferID);

			vertCountTotal.push_back(vertexBuff[l].size());
		}
		different = false;
	}
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