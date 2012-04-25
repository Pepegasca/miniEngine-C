#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>
#include "Texture.h"
#include "esUtil.h"
#include "ObjModel.h"
#include "Shader.h"
#include "Vector3d.h"

class SceneObject{
public:
	string objectFile;
	string vertexShaderFile;
	string fragmentShaderFile;
	string textureFile;

	Shader *vertexShader;
	Shader *fragmentShader;

	ObjModel *Objeto;

	/* Position, rotation and scale object */
	Vector3d *vPos;
	float angRot;
	Vector3d *vRot; // vector de rotacion
	float sxObj, syObj, szObj; // rotation

	ESMatrix mvMatrix;
	ESMatrix mvpMatrix;
	ESMatrix perspectiveMatrix;
	/*OpenGL Shader variables*/
	GLuint programObject;
	GLuint baseMapTexId;

	GLint texCoordLoc;
	GLint positionLoc;
	GLint baseMapLoc;
	
	GLint posCamera;
	GLint fogStart;
	GLint fogLength;
	GLint colorFog;

	GLint maxHeight;

	GLint mvpLoc;
	GLint mvLoc;

	SceneObject();
	SceneObject(string objFile, string vertShaderFile, string fragShaderFile, string textFile);
	SceneObject(ObjModel *model, Shader *vShader, Shader *fShader, int textureIndex);

	void load();
	void assignResources(ObjModel *model, Shader *vShader, Shader *fShader, int textureIndex);

	void update();

	void destroy();
	void translate(float a, float b, float c);
	void scale(float a, float b, float c);
	void rotate(float ang, float x, float y, float z);

	void setPosition(float a, float b, float c);
	void setScale(float a, float b, float c);
};