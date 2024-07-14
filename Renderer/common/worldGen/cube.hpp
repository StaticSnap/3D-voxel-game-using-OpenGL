//cube.hpp
//created 7/2/2024 last edited 7/12/2024
//the class for a cube. It holds all related values such as color and position. It does NOT generate it's own buffer.

#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
public:
	Cube(float R = 0, float G = 0, float B = 0, int posx = 0, int posy = 0, int posz = 0, bool faceVisibility[6] = 0);
    ~Cube();

    float* getColorDat();
    float* getPosDat();
    bool* getFaceVisibility();

private:

    //decide wether you can afford to use the stack for this class!
    //answer, probibly not
    float* colorDat = new float[3];
    float* posDat = new float[3];
    bool* faceVisibility = new bool[6];

};

#endif
