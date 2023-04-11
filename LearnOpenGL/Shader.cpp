#include "Shader.h"
#include <iostream>
#include <fstream>
#include<sstream>


#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

Shader::Shader(const char* vertexPath,const char* fragmentPath) {
	 
	ifstream vertexFile;
	ifstream fragmentFile;

	stringstream vertexSStream;
	stringstream fragmentSStream;


	//開檔 != 資料進到內存
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	
	//判斷是不是壞檔
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	//判斷是不是有開檔
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
			throw exception("Open file error");
		//把資料丟到內存中
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();
		//把內存轉成 String
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();
		//把 String 轉成 Char*
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		
		//把 Vertex source 綁到 shader 上面
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		//把 fragment source 綁到 shader 上面
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMWNT");

		//Create Program ID
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		//把 兩個shader link 在一起，為了函示位置的對接
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		glDeleteShader(vertex);
		glDeleteShader(fragment);




	}
	catch (const std::exception& ex)
	{
		printf(ex.what());	
	}


}

void Shader::Use() {
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type) {

	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			cout << "Shader Compile Error:" << infoLog << endl;
		}
	}
	else{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "Program Compile Error:" << infoLog << endl;
		}
	}


}