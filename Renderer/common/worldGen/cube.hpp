//cube.hpp
//created 7/2/2024 last edited 7/5/2024
//the class for a cube. It generates it's own buffer data

#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
public:
	Cube(float R = 0, float G = 0, float B = 0, int posx = 0, int posy = 0, int posz = 0);
    ~Cube();

    GLfloat* getVertexBufferData();
    GLfloat* getColorBufferData();

    void deleteCube();

private:
	glm::vec3 color;
	glm::vec3 pos;

    GLfloat* colorBufferData = new GLfloat[108];
    GLfloat* vertexBufferData = new GLfloat[108];


    const GLfloat cubeVertexDefault[108] = {
    -0.5f, -0.5f, -0.5f,   // triangle 1 : begin
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,   // triangle 1 : end
     0.5f,  0.5f, -0.5f,   // triangle 2 : begin
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,   // triangle 2 : end
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f
    };
};

#endif
