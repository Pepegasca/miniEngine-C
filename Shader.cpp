#include "Shader.h"
using std::fstream;
Shader::Shader(){

}

Shader::Shader(const char *filename){
	loadShaderFile(filename);
}

int Shader::loadShaderFile(const char *Filename){
	char buffer[1024];
	string endLine("\n");
	fstream obj;
	obj.open(Filename, ios::in); 
	if(!obj.is_open())
		return -1;

	while(!obj.eof()){
		obj.getline(buffer,1024,'\n');
		shadText += (buffer);
		shadText += endLine;
	}
	obj.close();
	return 0;

}

const char *Shader::getTextShader(){
	return shadText.data();
}