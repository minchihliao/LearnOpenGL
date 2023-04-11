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


	//�}�� != ��ƶi�줺�s
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	
	//�P�_�O���O�a��
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	//�P�_�O���O���}��
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
			throw exception("Open file error");
		//���ƥ�줺�s��
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();
		//�⤺�s�ন String
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();
		//�� String �ন Char*
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		
		//�� Vertex source �j�� shader �W��
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		//�� fragment source �j�� shader �W��
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMWNT");

		//Create Program ID
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		//�� ���shader link �b�@�_�A���F��ܦ�m���ﱵ
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