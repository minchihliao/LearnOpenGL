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
    // 透明視窗
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
#pragma region 創建一個視窗
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
#pragma endregion
#pragma region 初始化 GLAD
    //
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD";
        return -1;
    }
    glViewport(0, 0, 800, 600);
#pragma endregion

    //Call back function - 當窗口調整大小的時候調用這個函數：
    glfwSetFramebufferSizeCallback(window, FrameBuffer_Size_CallBack);

    // Render Loop - 判斷 GLFW是否被要退出
    while (!glfwWindowShouldClose(window))
    {
        //輸入
        ProcessInput(window);

        //渲染指令
        //渲染顏色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //清除顏色 buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //交換顏色緩衝，用來繪製視窗
        glfwSwapBuffers(window);
        //檢查有沒有觸發事件(鍵盤滑鼠)
        glfwPollEvents();
    }

    //釋放之前分配的資源
    glfwTerminate();
    return 0;
}

void FrameBuffer_Size_CallBack(GLFWwindow* window, int width, int heigh) {
    glViewport(0, 0, width, heigh);
}

//在GLFW中判斷是否按下 ESC ，按下關閉視窗
void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}