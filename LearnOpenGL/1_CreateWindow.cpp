#include "1_CreateWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void FrameBuffer_Size_CallBack(GLFWwindow*, int, int);
void ProcessInput(GLFWwindow*);

int CreateWindow::main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // �z������
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
#pragma region �Ыؤ@�ӵ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
#pragma endregion
#pragma region ��l�� GLAD
    //
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD";
        return -1;
    }
    glViewport(0, 0, 800, 600);
#pragma endregion

    //Call back function - ���f�վ�j�p���ɭԽեγo�Ө�ơG
    glfwSetFramebufferSizeCallback(window, FrameBuffer_Size_CallBack);

    // Render Loop - �P�_ GLFW�O�_�Q�n�h�X
    while (!glfwWindowShouldClose(window))
    {
        //��J
        ProcessInput(window);

        //��V���O
        //��V�C��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //�M���C�� buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //�洫�C��w�ġA�Ψ�ø�s����
        glfwSwapBuffers(window);
        //�ˬd���S��Ĳ�o�ƥ�(��L�ƹ�)
        glfwPollEvents();
    }

    //���񤧫e���t���귽
    glfwTerminate();
    return 0;
}

void FrameBuffer_Size_CallBack(GLFWwindow* window, int width, int heigh) {
    glViewport(0, 0, width, heigh);
}

//�bGLFW���P�_�O�_���U ESC �A���U��������
void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}