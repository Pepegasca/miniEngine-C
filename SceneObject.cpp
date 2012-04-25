#include "SceneObject.h"
SceneObject::SceneObject(){
	/**  Init variables  **/
	vPos = new Vector3d(0.0f,0.0f,0.0f);
	angRot = 0.0f;
	vRot = new Vector3d(0.0f,0.0f,0.0f); // vector de rotacion
	sxObj = syObj = szObj = 1; // rotation
}
SceneObject::SceneObject(string objFile, string vertShaderFile, string fragShaderFile, string textFile){
	objectFile = objFile;
	vertexShaderFile = vertShaderFile;
	fragmentShaderFile = fragShaderFile;
	textureFile = textFile;

	vertexShader = new Shader();
	fragmentShader = new Shader();
	vPos = new Vector3d(0.0f,0.0f,0.0f);
	angRot = 0.0f;
	vRot = new Vector3d(0.0f,0.0f,0.0f); // vector de rotacion
	sxObj = syObj = szObj = 1; // rotation
}

void SceneObject::assignResources(ObjModel *model, Shader *vShader, Shader *fShader, int textureIndex){
	Objeto  = model;
	vertexShader = vShader;
	fragmentShader = fShader;
	baseMapTexId =  textureIndex;
	programObject = esLoadProgram ( vertexShader->getTextShader(),  fragmentShader->getTextShader() );
}

void SceneObject::load(){

	vertexShader->loadShaderFile(vertexShaderFile.c_str());
	fragmentShader->loadShaderFile(fragmentShaderFile.c_str());
	programObject = esLoadProgram ( vertexShader->getTextShader(),  fragmentShader->getTextShader() );

	Objeto = new ObjModel();
	Objeto->loadModel(objectFile.c_str());
	Objeto->generateGLVerticesTexture();
	Objeto->generateGLVertices();
	Objeto->generateGLIndices();

	baseMapTexId = Texture::LoadTexture (textureFile.c_str());

	esMatrixLoadIdentity(&mvMatrix);
}

void SceneObject::setPosition(float a, float b, float c)
{
	vPos->x = a;
	vPos->y = b;
	vPos->z = c;
}

void SceneObject::setScale(float a, float b, float c){
	sxObj = a;
	syObj = b;
	szObj = c;
}


void SceneObject::update(){
	scale(sxObj, syObj, szObj);
	rotate(angRot, vRot->x, vRot->y, vRot->z);
	translate(vPos->x,vPos->y,vPos->z);
}

void SceneObject::destroy(){
	glDeleteProgram ( programObject );
}
void SceneObject::translate(float a, float b, float c){
	esTranslate(&mvMatrix, a,b,c);
}
void SceneObject::scale(float a, float b, float c){
	esScale(&mvMatrix, a,b,c);
}
///
// Function rotate matrix around axis x
///
void SceneObject::rotate(float ang, float x, float y, float z){
	esRotate(&mvMatrix,ang, x,y,x);
}
/*
GLuint SceneObject::LoadTexture (const char *fileName )
{
	int width,
		height;
	char *buffer = esLoadTGA ((char *) fileName, &width, &height );
	GLuint texId;

	if ( buffer == NULL )
	{
		esLogMessage ( "Error loading (%s) image.\n", fileName );
		return 0;
	}

	glGenTextures ( 1, &texId );
	glBindTexture ( GL_TEXTURE_2D, texId );

	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	free ( buffer );

	return texId;
}
*/