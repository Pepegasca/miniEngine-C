#include "ResourceManager.h"

int ResourceManager::addObjModel(ObjModel *model){
	models.push_back(model);
	return 0;
}

int ResourceManager::addTexture(Texture *text){
	textures.push_back(text);
	return 0;
}

int ResourceManager::addShader(Shader *shad){
	shaders.push_back(shad);
	return 0;
}

int ResourceManager::initResources(SceneManager *scnManager)
{
/***
	** Load all resources used in scene
	***/
	ObjModel *woman1 = new ObjModel("Resources/models/Woman1.obj");
	ObjModel *woman2 = new ObjModel("Resources/models/Woman2.obj");
	ObjModel *plane = new ObjModel("Resources/models/plan.obj");
	ObjModel *cube = new ObjModel("Resources/models/cube.obj");

	Shader *vFogShad = new Shader("Resources/shaders/FogvertexShader.fx");
	Shader *fFogShad = new Shader("Resources/shaders/FogfragShader.fx");

	Shader *vFogTerrainShad = new Shader("Resources/shaders/vertexTerrainFogShader.fx");
	Shader *fFogTerrainShad = new Shader("Resources/shaders/fragTerrainFogShader.fx");

	int idText = Texture::LoadTexture ("Resources/textures/sarah_color.tga");
	int idText2 = Texture::LoadTexture ("Resources/textures/betty_color.tga");
	int idText3 = Texture::LoadTexture ("Resources/textures/Grass1.tga");

	/***
	**	Config objects in scene
	***/
	SceneObject *scnObject = new SceneObject();
	scnObject->assignResources(woman2,vFogShad, fFogShad, idText2);
	scnObject->setPosition(1.0,0.0,-2.0);
	scnObject->setScale(1.0,1.0,1.0);

	SceneObject *scnObject2 = new SceneObject();
	scnObject2->assignResources(woman1,vFogShad, fFogShad, idText);
	scnObject2->setPosition(1.0,0.0,-5.0);

	SceneObject *scnObject3 = new SceneObject();
	scnObject3->assignResources(plane,vFogTerrainShad, fFogTerrainShad, idText3);

	SceneObject *scnObject4 = new SceneObject();
	scnObject4->assignResources(woman1,vFogShad, fFogShad, idText);
	scnObject4->setScale(1.5f,1.5f,1.5f);
	scnObject4->setPosition(1.5f,0.0f,-1.5f);

	SceneObject *scnObject5 = new SceneObject();
	scnObject5->assignResources(cube,vFogShad, fFogShad, idText);
	scnObject5->setScale(5.5f,5.5f,5.5f);
	scnObject5->setPosition(1.5f,0.0f,-1.5f);

	/***
	**	Add objects to scene Manager
	***/
	scnManager->addObject(scnObject);
	scnManager->addObject(scnObject2);
	scnManager->addObject(scnObject3);
	scnManager->addObject(scnObject4);
	scnManager->addObject(scnObject5);
	/***
	**	Add uniforms locations to shader objects
	***/
	for(int i=0; i<(int)scnManager->objects.size();i++)
	{
		scnManager->objects[i]->positionLoc =	glGetAttribLocation ( scnManager->objects[i]->programObject, "a_position" );
		scnManager->objects[i]->texCoordLoc =	glGetAttribLocation ( scnManager->objects[i]->programObject, "a_texCoord" );
		scnManager->objects[i]->mvpLoc =		glGetUniformLocation( scnManager->objects[i]->programObject, "u_mvpMatrix" );
		scnManager->objects[i]->baseMapLoc =	glGetUniformLocation ( scnManager->objects[i]->programObject, "s_baseMap" );
		
		scnManager->objects[i]->fogStart  = glGetUniformLocation ( scnManager->objects[i]->programObject,"u_fogStart");
		scnManager->objects[i]->fogLength = glGetUniformLocation ( scnManager->objects[i]->programObject,"u_fogLength");
		scnManager->objects[i]->colorFog = glGetUniformLocation  ( scnManager->objects[i]->programObject, "u_colorFog");
		scnManager->objects[i]->mvLoc =		glGetUniformLocation ( scnManager->objects[i]->programObject, "u_mvMatrix" );
		scnManager->objects[i]->posCamera = glGetUniformLocation (scnManager->objects[i]->programObject, "u_posCamera");

		scnManager->objects[i]->maxHeight = glGetUniformLocation(scnManager->objects[i]->programObject, "u_MaxHeight");
	}

	return 0;
}

