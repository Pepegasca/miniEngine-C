#include "SceneManager.h"

SceneManager::SceneManager(){
	esMatrixLoadIdentity( &mvMatrix );
	esMatrixLoadIdentity( &mvpMatrix );
	esMatrixLoadIdentity( &perspectiveMatrix );
	angle = 0.0f;
}
void SceneManager::Draw(){

	for(int i=0;i<(int)objects.size();i++)
	{
		// Use the program object
		glUseProgram ( objects[i]->programObject );

		glVertexAttribPointer ( objects[i]->positionLoc, 3, GL_FLOAT, GL_FALSE, 0,objects[i]->Objeto->verticesGL);  
		glEnableVertexAttribArray (objects[i]->positionLoc );

		glVertexAttribPointer ( objects[i]->texCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, objects[i]->Objeto->vertTextGL );	
		glEnableVertexAttribArray ( objects[i]->texCoordLoc );

		// Bind the base map
		glActiveTexture ( GL_TEXTURE0);
		glBindTexture ( GL_TEXTURE_2D, objects[i]->baseMapTexId );

		// Set the base map sampler to texture unit to 0
		glUniform1i(objects[i]->baseMapLoc, 0 );
		glUniform1f(objects[i]->fogStart,2.0f);
		glUniform1f(objects[i]->fogLength,15.0f);
		glUniform4f(objects[i]->colorFog,0.0f,0.0f,0.0f,0.0f);
		glUniform1f(objects[i]->maxHeight,5.0f);

		glUniform4f(objects[i]->posCamera, 0.0f,vecCameraPos[1],0.0f, 0.0f);
		//glUniform4f(objects[i]->posCamera, vecCameraPos[0],vecCameraPos[1],vecCameraPos[2], 0.0f);


		// Load the MV matrix
		glUniformMatrix4fv( objects[i]->mvLoc, 1, GL_FALSE, (GLfloat*) &objects[i]->mvMatrix.m[0][0] );

		// Load the MVP matrix
		glUniformMatrix4fv( objects[i]->mvpLoc, 1, GL_FALSE, (GLfloat*) &objects[i]->mvpMatrix.m[0][0] );

		// Draw the obj Model
		glDrawElements(GL_TRIANGLES,3*objects[i]->Objeto->getNumberFaces(), GL_UNSIGNED_SHORT, objects[i]->Objeto->indices);
	}

}
void SceneManager::Update(ESContext *esContext)
{
	//UserData *userData = (UserData*) esContext->userData;
	float    aspect;

	// Compute the window aspect ratio
	aspect = (GLfloat) esContext->width / (GLfloat) esContext->height;
	
	// Generate a perspective matrix with a 60 degree FOV
	esMatrixLoadIdentity( &perspectiveMatrix );
	
	esPerspective( &perspectiveMatrix, 60.0f, aspect, 0.5f, 50.0f );

	// Generate a model view matrix to rotate/translate the objects
	for(int i=0;i<(int)objects.size();i++)
	{
		esMatrixLoadIdentity( &objects[i]->mvMatrix );
		
		objects[i]->update();
		esTranslate(&objects[i]->mvMatrix, vecCameraPos[0],vecCameraPos[1],vecCameraPos[2]);
		esRotate(&objects[i]->mvMatrix, angle, 0.0f,1.0f,0.0f);

		// Compute the final MVP by multiplying the 
		// modelview and perspective matrices together
		esMatrixMultiply( &objects[i]->mvpMatrix, &objects[i]->mvMatrix, &perspectiveMatrix );
	}
}

void SceneManager::addObject(SceneObject *ob){
	objects.push_back(ob);
}

void SceneManager::destroySceneManager(){
	for(int i=0;i<(int)objects.size();i++)
	{
		objects[i]->destroy();
	}

}
