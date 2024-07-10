//cube.hpp
//created 7/2/2024 last edited 7/6/2024
//the class for a cube. It generates it's own buffer data

#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
public:
	Cube(float R = 0, float G = 0, float B = 0, int posx = 0, int posy = 0, int posz = 0, bool faceVisibility[6] = 0);
    ~Cube();

    std::vector<GLfloat> getVertexBufferData();
    std::vector<GLfloat> getColorBufferData();

    void deleteCube();

private:

    std::vector<GLfloat> colorBufferData;
    std::vector<GLfloat> vertexBufferData;

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
};

#endif
