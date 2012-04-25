#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
class Shader{
private:
	string shadText;

public:
	Shader();
	Shader(const char *filename);
	int loadShaderFile(const char *Filename);
	const char *getTextShader();
};