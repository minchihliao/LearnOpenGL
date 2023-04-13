#include "Program.h"

#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



void FrameBuffer_Size_CallBack_Triangle(GLFWwindow* window, int width, int heigh);
void ProcessInput_Triangle(GLFWwindow* window);

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
      ////第一個三角形
      //-0.5f, -0.5f, 0.0f, 1.0f,0,0,  // 0
      //0.5f, -0.5f, 0.0f,  0,1.0f,0,//  1
      //0.5f, 0.5f, 0.0f,   0,0,1.0f,//  2
      ////第二個三角形
      ////0.5f, -0.5f, 0.0f,  
      ////0.5f, 0.5f, 0.0f,   
      //-0.5f, 0.5f, 0.0f, 0.3f,0.5f,0.7f  // 3
};
// 0,1,2 2,3,1

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1\n"
"out vec4 vertexColor; \n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0); \n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor; \n"
"uniform vec4 ourColor; \n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";


int	Program::Excute() {


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
    //設定運行中狀態

    //背面剔除
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Shader* testShader = new Shader("vertexSource.txt", "fragmentSource.txt");

     
    //宣告 VAO
    unsigned int VAO; //VAO[10]
    glGenVertexArrays(1, &VAO); //(10,VAO)
    glBindVertexArray(VAO);

    //宣告VBO
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //宣告EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


//unsigned int vertexShader;
////compile vertect shader
//vertexShader = glCreateShader(GL_VERTEX_SHADER);
//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//glCompileShader(vertexShader);
// 
////compile Fragment shader
//unsigned int fragmentShader;
//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//glCompileShader(fragmentShader);
//
//// Link vertex and fragment shader to program
//unsigned int shaderProgram;
//shaderProgram = glCreateProgram();
//glAttachShader(shaderProgram, vertexShader);
//glAttachShader(shaderProgram, fragmentShader);
//glLinkProgram(shaderProgram);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //紋理屬性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //設置 TEXTUREA Buffer
    unsigned int TexBufferA;
    glGenTextures(1, &TexBufferA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TexBufferA);

    //Load Texture
    int width, height, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel,0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("load image failed");
    }
    stbi_image_free(data); 

    //設置 TEXTUREA Buffer
    unsigned int TexBufferB;
    glGenTextures(1, &TexBufferB);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, TexBufferB);

    //Load 第二張Texture
    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("load image failed");
    }
    stbi_image_free(data2);

    //Call back function - 當窗口調整大小的時候調用這個函數：
    glfwSetFramebufferSizeCallback(window, FrameBuffer_Size_CallBack_Triangle);


    // caclculate our transformation matrix here.
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0));
     //trans = glm::rotate(trans,glm::radians(45.0f) ,glm::vec3(0, 0, 1.0f));
    //trans = glm::scale(trans, glm::vec3(1.2f, 1.2f, 1.2f));
    

    // Render Loop - 判斷 GLFW是否被要退出
    while (!glfwWindowShouldClose(window))
    {
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 1.0f));
        //輸入
        ProcessInput_Triangle(window);

        //渲染指令
        //渲染顏色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //清除顏色 buffer
        glClear(GL_COLOR_BUFFER_BIT);

       


 //準備匯到Shader的資料
 //float timeValue = glfwGetTime();
 //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
 //取得 VertexColor location
 //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
 //使用Shader
 //glUseProgram(shaderProgram);
 //把CPU資料利用Uniform匯到Shader中
 //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
       
       
        //把 Texture 綁到 VAO
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, TexBufferB);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0);
        glUniform1i(glGetUniformLocation(testShader->ID, "ourFace"), 3);
        glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "transform"),1,GL_FALSE, glm::value_ptr(trans));

        testShader->Use();
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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