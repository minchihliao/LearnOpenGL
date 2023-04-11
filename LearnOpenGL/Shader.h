#pragma once
#include<string>
class Shader
{
	public:
		Shader(const char* vertextPath, const char* fragmentPath);
		std::string vertexString;
		std::string fragmentString;
		const char* vertexSource;
		const char* fragmentSource;
		unsigned int ID; // Shader program ID
		unsigned int shaderProgram; // Shader program ID
		void Use();

	private:
		void checkCompileErrors(unsigned int ID,std::string type);
};

