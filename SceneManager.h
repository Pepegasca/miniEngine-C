#pragma once
#include <vector>
#include "esUtil.h"
#include "Vector3d.h"
#include "SceneObject.h"
#include "Texture.h"

class SceneManager{
public:
	// MVP matrix
	ESMatrix  mvpMatrix;
	ESMatrix  mvMatrix; // modelview matrix
	ESMatrix  perspectiveMatrix;
	
	// Camera
	float vecCameraPos[3];
	float angle;

	//Objects in scene
	vector<SceneObject*> objects;

	SceneManager();
	
	void Draw();
	void Update(ESContext *esContext);
	void addObject(SceneObject *ob);
	void destroySceneManager();

};