#include <GL/glew.h>

#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cube.hpp"


Cube::Cube(float R, float G, float B, int posx, int posy, int posz) {
	pos[0] = posx;
	pos[1] = posy;
	pos[2] = posz;

	color[0] = R;
	color[1] = G;
	color[2] = B;


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

    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

    
}

Cube::~Cube() {
    deleteCube();
}


GLuint Cube::getVertexBuffer() {
    return vertexBufferID;
}

GLuint Cube::getColorBuffer() {
    return colorBufferID;
}

void Cube::deleteBuffer() {
    glDeleteBuffers(1, &vertexBufferID);
}

void Cube::deleteCube() {
    deleteBuffer();
    delete[] colorBufferData;
    delete[] vertexBufferData;
}

GLfloat* Cube::getVertexBufferData() {
    return vertexBufferData;
}

GLfloat* Cube::getColorBufferData() {
    return colorBufferData;
}


