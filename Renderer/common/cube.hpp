//cube.hpp
//created 7/2/2024 last edited 7/2/2024
//the class for a cube. It generates it's own buffer data

#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
public:
	Cube(float R = 0, float G = 0, float B = 0, int posx = 0, int posy = 0, int posz = 0);


    GLuint getVertexBuffer();
    GLuint getColorBuffer();

    GLfloat* getVertexBufferData();
    GLfloat* getColorBufferData();


    void deleteBuffer();

private:
	glm::vec3 color;
	glm::vec3 pos;

	GLfloat colorBufferData[108];
	GLfloat vertexBufferData[108];


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

    GLuint vertexBufferID;
    GLuint colorBufferID;
};

#endif
