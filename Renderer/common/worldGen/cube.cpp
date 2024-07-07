#include <GL/glew.h>

#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cube.hpp"


Cube::Cube(float R, float G, float B, int posx, int posy, int posz) {
	//variables storing position and color of cube
    //currently unused
    pos[0] = posx;
	pos[1] = posy;
	pos[2] = posz;

	color[0] = R;
	color[1] = G;
	color[2] = B;

    //iterate over whole cube and fill each vertex data and color data for all 12 triangles
    for (int i = 0; i < 108; i++) {
        vertexBufferData[i] = 0;

        vertexBufferData[i] += cubeVertexDefault[i];
        if (i % 3 == 0) {
            vertexBufferData[i] += posx;
            colorBufferData[i] = R;
        }
        else if (i % 3 == 1) {
            vertexBufferData[i] += posy;
            colorBufferData[i] = G;
        }
        else {
            vertexBufferData[i] += posz;
            colorBufferData[i] = B;
        }
    }
}

Cube::~Cube() {
    deleteCube();
}

void Cube::deleteCube() {
    delete[] colorBufferData;
    delete[] vertexBufferData;
}

GLfloat* Cube::getVertexBufferData() {
    return vertexBufferData;
}

GLfloat* Cube::getColorBufferData() {
    return colorBufferData;
}


