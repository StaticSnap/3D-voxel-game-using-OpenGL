//renderer project, started 06/01/2024, lasted changed 7/6/2024
//started to help build understanding on renderering and hopefully create a game
//early code is taken following the openGL tutorial found at www.opengl-tutorial.org

//to do: implement perlin noise and start making a real game

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>

//include glew BEFORE gl.h and glfw3.h
#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.hpp>

#include "common/controls.hpp"
#include "common/worldGen/worldSeeding.hpp"

int main(void)
{

    std::srand(3);


    //initialize glfw
    if (!glfwInit()) {
        fprintf(stderr, "failed to initialize GLFW\n");
        return -1;
    }

    //set window parameters
    glfwWindowHint(GLFW_SAMPLES,4); //4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3); //for openGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //used for MacOS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //use the new openGL

    
    window = glfwCreateWindow(1024, 768, "renderer", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0, 0.7, 0.9, 1);


    //creating the VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders("shaders/VertexShader.txt", "shaders/FragmentShader.txt");

    //this class is he entire game. taking a seed as a paremter. this will change eventually
    WorldSeeding terrain(256,30); 

    //this tells openGL to not overdraw vertecies that should be behind others
    //enable depth test
    glEnable(GL_DEPTH_TEST);
    //accept fragment if it is closer to the camera than the former one
    glDepthFunc(GL_LESS);

    //cull triangles whose normal is not facing the camera
    //glEnable(GL_CULL_FACE);


    do {
        //clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        //get a handle for our "MVP" uniform
        GLuint MatrixID = glGetUniformLocation(programID, "MVP");

        computeMatricesFromInputs();

        //projection matrix
        glm::mat4 Projection = getProjectionMatrix();
        //camera matrix
        glm::mat4 View = getViewMatrix();
        //model matrix
        glm::mat4 Model = glm::mat4(1.0f);
        //finally combine all, matrix mult is performed right to left
        glm::mat4 MVP = Projection * View * Model;


        //use the shader
        glUseProgram(programID);

        //send transformation to the currently bound shader
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        //first attribute buffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, terrain.getMasterVertexBufferID());
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        //2nd attribute buffer, color
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, terrain.getmasterColorBufferID());
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );


        //draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, terrain.getVertexCount()/3); //draw 12 triangles per cube

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);


        //swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();


    } //check if escape was pressed or if window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    terrain.~WorldSeeding();

    glfwTerminate();

    return 0;

}