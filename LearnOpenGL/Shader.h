
#ifndef SHADER_H
#define SHADER_H



#include "top_header.h"

class Shader
{
public:
	//Program ID
	GLuint Program;
	//Constructor
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//Use the program
	void Use();

};

#endif /* SHADER_H */

