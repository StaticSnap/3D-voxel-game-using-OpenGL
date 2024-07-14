//controls.hpp
//created 7/1/2024, lasted edited 7/12/2024
//used to store all the controls and apply transformations to the camera matrices as needed when moving or looking

#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();


#endif


