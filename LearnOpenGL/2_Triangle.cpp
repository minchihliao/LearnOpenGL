#include "2_Triangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


void FrameBuffer_Size_CallBack_Triangle(GLFWwindow* window, int width, int heigh);
void ProcessInput_Triangle(GLFWwindow* window);

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.8f,0.8f,0.0f
};


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


int	Triangle::Excute() {
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

    //宣告 VAO
    unsigned int VAO; //VAO[10]
    glGenVertexArrays(1, &VAO); //(10,VAO)
    glBindVertexArray(VAO);

    //宣告VBO
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //compile vertect shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //compile Fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    // Link vertex and fragment shader to program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    //Call back function - 當窗口調整大小的時候調用這個函數：
    glfwSetFramebufferSizeCallback(window, FrameBuffer_Size_CallBack_Triangle);

    // Render Loop - 判斷 GLFW是否被要退出
    while (!glfwWindowShouldClose(window))
    {
        //輸入
        ProcessInput_Triangle(window);

        //渲染指令
        //渲染顏色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //清除顏色 buffer
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //交換顏色緩衝，用來繪製視窗
        glfwSwapBuffers(window);
        //檢查有沒有觸發事件(鍵盤滑鼠)
        glfwPollEvents();
    }

    //釋放之前分配的資源
    glfwTerminate();
    return 0;
}

void FrameBuffer_Size_CallBack_Triangle(GLFWwindow* window, int width, int heigh) {
    glViewport(0, 0, width, heigh);
}

//在GLFW中判斷是否按下 ESC ，按下關閉視窗
void ProcessInput_Triangle(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}