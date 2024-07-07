#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cube.hpp"


Cube::Cube(float R, float G, float B, int posx, int posy, int posz, bool FaceVisibility[6]) {
    //faceVisibility: 0 top, 1 left, 2 front, 3 right, 4 back, 5 bottom
    for (int i = 0; i < 6; i++) {
        if (FaceVisibility[i] == true) {
            for (int j = 0; j < 18; j++) {
                if (j % 3 == 0) {
                    vertexBufferData.push_back(cubeVertexDefault[i][j] + posx);
                    colorBufferData.push_back(R);
                }
                else if (j % 3 == 1) {
                    vertexBufferData.push_back(cubeVertexDefault[i][j] + posy);
                    colorBufferData.push_back(G);
                }
                else {
                    vertexBufferData.push_back(cubeVertexDefault[i][j] + posz);
                    colorBufferData.push_back(B);
                }
            }
        }
    }


    //variables storing position and color of cube
    //currently unused
    pos[0] = posx;
	pos[1] = posy;
	pos[2] = posz;

	color[0] = R;
	color[1] = G;
	color[2] = B;
}

Cube::~Cube() {
    deleteCube();
}

void Cube::deleteCube() {
    colorBufferData.clear();
    vertexBufferData.clear();
}

std::vector<GLfloat> Cube::getVertexBufferData() {
    return vertexBufferData;
}

std::vector<GLfloat> Cube::getColorBufferData() {
    return colorBufferData;
}


