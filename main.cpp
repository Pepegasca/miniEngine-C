#include <stdlib.h>
#include <iostream>
#include "esUtil.h"
#include "SceneManager.h"
#include "ResourceManager.h"


typedef struct
{
	GLfloat   angle;	
} UserData;

SceneManager *scnManager;
ResourceManager *rscManager;

ESMatrix perspective;
ESMatrix modelview;

///
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
	UserData *userData = (UserData*)esContext->userData;

	scnManager  = new SceneManager();
	scnManager->vecCameraPos[0] = 0.0f;
	scnManager->vecCameraPos[1] = -2.0f;
	scnManager->vecCameraPos[2] = 0.0f;
	
	rscManager = new ResourceManager();

	rscManager->initResources(scnManager);
	userData->angle = 0.0f;

	return true;
}


///
// Update MVP matrix
//
void Update ( ESContext *esContext, float deltaTime )
{

	scnManager->Update(esContext);
}

///
// Draw
//
void Draw ( ESContext *esContext )
{
	// Set the viewport
	glViewport ( 0, 0, esContext->width, esContext->height );
	glClear ( GL_COLOR_BUFFER_BIT );
	glClearColor ( 0.0f,0.0f, 0.0f, 0.0f );
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	scnManager->Draw();
	
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void userKey(ESContext *esContext, unsigned char a, int x, int y){
	UserData *userData = (UserData*)esContext->userData;
	switch(a){
		case 'a':
			scnManager->vecCameraPos[0]--;
			break;
		case 's':
			scnManager->vecCameraPos[0]++;
			break;
		case 'w':
			scnManager->vecCameraPos[1]++;
			break;
		case 'z':
			scnManager->vecCameraPos[1]--;
			break;
		case 'e':
			scnManager->vecCameraPos[2]++;
			break;
		case 'd':
			scnManager->vecCameraPos[2]--;
			break;
		case 'r':
			scnManager->angle += 5;
			if( scnManager->angle >= 360.0f )
				scnManager->angle -= 360.0f;
			break;
		default:
			break;
	}
}

void ShutDown ( ESContext *esContext )
{
	UserData *userData = (UserData *)esContext->userData;

	for(int i=0; i<(int)scnManager->objects.size();i++)
		glDeleteProgram ( scnManager->objects[i]->programObject );
}


int main ( int argc, char *argv[] )
{
	ESContext esContext;
	UserData  userData;

	esInitContext ( &esContext );
	esContext.userData = &userData;

	esCreateWindow ( &esContext, "App Sample", 512, 512, ES_WINDOW_RGB|ES_WINDOW_DEPTH );

	if ( !Init ( &esContext ) )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc(&esContext,userKey);

	esMainLoop ( &esContext );

	ShutDown ( &esContext );


}
