#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cube.hpp"


Cube::Cube(float R, float G, float B, int posx, int posy, int posz, bool FaceVisibility[6]) {
    //faceVisibility: 0 top, 1 left, 2 front, 3 right, 4 back, 5 bottom
    colorDat[0] = R;
    colorDat[1] = G;
    colorDat[2] = B;

    posDat[0] = posx;
    posDat[1] = posy;
    posDat[2] = posz;

    for (int i = 0; i < 6; i++) {
        faceVisibility[i] = FaceVisibility[i];
    }
}

Cube::~Cube() {
    delete colorDat;
    delete posDat;
    delete faceVisibility;
}

float* Cube::getColorDat() {
    return colorDat;
}

float* Cube::getPosDat() {
    return posDat;
}

bool* Cube::getFaceVisibility() {
    return faceVisibility;
}

