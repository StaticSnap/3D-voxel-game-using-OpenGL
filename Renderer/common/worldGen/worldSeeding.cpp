#include "worldSeeding.hpp"

WorldSeeding::WorldSeeding(int newWorldWidth, int newWorldHeight) {
	worldWidth = newWorldWidth;
	worldHeight = newWorldHeight;
	
	masterVertexBufferID = -1;
	masterColorBufferID = -1;


	//init the 3d array on the heap
	levelDat = new short**[worldWidth];
	for (int i = 0; i < worldWidth; i++) {
		levelDat[i] = new short* [worldHeight];
		for (int j = 0; j < worldHeight; j++) {
			levelDat[i][j] = new short[worldWidth];
		}
	}
	//------------------------------

	//set all values to 0, the air block
	for (int i = 0; i < worldWidth; i++) {
		for (int j = 0; j < worldHeight; j++) {
			for (int k = 0; k < worldWidth; k++) {
				levelDat[i][j][k] = 0;
			}
		}
	}
	//----------------------------------

	//generate noise and interpolate

	//declare memory for the noise grid
	noiseGrid = new short* [8];
	for (int i = 0; i < 8; i++) {
		noiseGrid[i] = new short[8];
	}

	//fill each spot on the noise grid with a random height
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			noiseGrid[i][j] = rand() % worldHeight;
		}
	}

	//iterate over the world and reference the noise grid to apply noise to each block
	for (int i = 0; i < worldWidth; i++) {
		for (int k = 0; k < worldWidth; k++) {
			
			//select an index using sets of 32 blocks
			short xIndex = short(trunc(i / 32.0));
			short zIndex = short(trunc(k / 32.0));

			//find the 4 corners around the block inside of the noise grid
			short c01 = noiseGrid[xIndex % 8][zIndex % 8];
			short c11 = noiseGrid[(xIndex+1) % 8][zIndex % 8];
			short c00 = noiseGrid[xIndex % 8][(zIndex+1) % 8];
			short c10 = noiseGrid[(xIndex+1) % 8][(zIndex+1) % 8];

			//find the average height
			float t = i % 32 / float(32);

			float a = c01 * (1 - t) + c11 * t;
			float b = c00 * (1 - t) + c10 * t;

			float t2 = k % 32 / float(32);

			short res = short(trunc(a * (1 - t2) + b * t2)) % worldHeight;
			//-----------------------


			levelDat[i][res][k] = 1;

			for (int l = 0; l < res; l++) {
				levelDat[i][l][k] = 1;
			}
		}
	}
	//-------------------------------------------------------------------------------

	/*BufferGen terrain(levelDat, worldWidth, worldHeight);

	masterVertexBufferID = terrain.getVertexBufferID();
	masterColorBufferID = terrain.getColorBufferID();

	vertexCount = terrain.getVertexCount();

	terrain.updateBuffers();*/
}

WorldSeeding::~WorldSeeding() {
	for (int i = 0; i < 8; i++) {
		delete[] noiseGrid[i];
	}
	delete[] noiseGrid;
	
	for (int i = 0; i < worldWidth; i++) {
		for (int j = 0; j < worldHeight; j++) {
			delete[] levelDat[i][j];
		}
		delete[] levelDat[i];
	}
	delete[] levelDat;
}

GLuint WorldSeeding::getMasterVertexBufferID() {
	return masterVertexBufferID;
}

GLuint WorldSeeding::getmasterColorBufferID() {
	return masterColorBufferID;
}

int WorldSeeding::getWorldWidth() {
	return worldWidth;
}

int WorldSeeding::getWorldHeight() {
	return worldHeight;
}

int WorldSeeding::getVertexCount() {
	return vertexCount;
}

short**** WorldSeeding::retrieveChunkData(std::vector<glm::vec3> chunkList) {
	short**** renderDat = new short*** [chunkList.size()];
	for (int i = 0; i < chunkList.size(); i++) {
		renderDat[i] = new short** [32];
		for (int j = 0; j < 32; j++) {
			renderDat[i][j] = new short* [32];
			for (int k = 0; k < 32; k++) {
				renderDat[i][j][k] = new short[32];
			}
		}
	}



	for (int l = 0; l < chunkList.size(); l++) {
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 32; j++) {
				for (int k = 0; k < 32; k++) {
					renderDat[l][i][j][k] = levelDat[int(i+chunkList[l][0]*32)][int(j + chunkList[l][1] * 32)][int(k + chunkList[l][2] * 32)];
				}
			}
		}
	}

	return renderDat;
}