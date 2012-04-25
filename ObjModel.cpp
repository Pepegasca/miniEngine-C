#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "ObjModel.h"

ObjModel::ObjModel(){
	generatedVerticesVector = generatedVertTextVector = generatedIndexVector =  false;
}
ObjModel::ObjModel(const char *file){
	generatedVerticesVector = generatedVertTextVector = generatedIndexVector =  false;
	loadModel(file);
	generateGLVerticesTexture();
	generateGLVertices();
	generateGLIndices();
}

int ObjModel::getNumberVertices(){
	return (int)vertices.size();
}

int ObjModel::getNumberVertexNormals(){
	return (int)vertexNormals.size();
}

int ObjModel::getNumberVertexTextures(){
	return (int)vertexTextures.size();
}
int ObjModel::getNumberFaces(){
	return (int)faces.size();
}

int ObjModel::loadModel(const char *file)
{
	// variables to use in read vertex data
	float a,b,c;
	int a1,b1,c1,a2,b2,c2,a3,b3,c3; 

	char buffer[256];
	char desc[2];
	fstream obj;
	obj.open(file, ios::in); 

	while(!obj.eof()){
		obj.getline(buffer,256,'\n');

		switch(lineDescriptor(buffer[0],buffer[1])){
				case 1:		
					sscanf(buffer,"%c %f %f %f",desc,&a,&b,&c);
					vertices.push_back(Vertex3d(a,b,c));
					break;
				case 2:
					sscanf(buffer,"%2c %f %f %f",desc, &a,&b,&c);
					vertexNormals.push_back(Vertex3d(a,b,c));
					break;
				case 3:
					sscanf(buffer,"%2c %f %f %f",desc,&a,&b,&c);
					vertexTextures.push_back(Vertex3d(a,b,c));
					break;
				case 4:
					sscanf(buffer,"%c %d/%d/%d %d/%d/%d %d/%d/%d",desc, &a1,&a2,&a3,&b1,&b2,&b3,&c1,&c2,&c3);
					faces.push_back(TriangleFace(Vertex3d(a1-1,b1-1,c1-1),Vertex3d(a2-1,b2-1,c2-1),Vertex3d(a3-1,b3-1,c3-1)));
					break;
				default:
					break;
		}

	}
	obj.close();
	return 0;
}
bool ObjModel::generateGLIndices(){

	if(!generatedIndexVector)
		indices = (unsigned short*)malloc(sizeof(unsigned short)*getNumberFaces()*3);

	if(!indices)
		return false;

	for(int i=0; i < 3*getNumberFaces();i++)
	{
		indices[i] = i;
	}
	generatedIndexVector = true;
	return true;
}

bool ObjModel::generateGLVertices(){
	//float *vert = new float(3*3*getNumberFaces());
	if(!generatedVerticesVector)
		verticesGL = (float*)malloc(3*3*getNumberFaces()*sizeof(float));

	if(!verticesGL)
		return false;

	for(int i=0; i < getNumberFaces();i++)
	{
		verticesGL[i*9    ] = vertices[(int)faces[i].point.x].x;
		verticesGL[i*9 + 1] = vertices[(int)faces[i].point.x].y;
		verticesGL[i*9 + 2] = vertices[(int)faces[i].point.x].z;

		verticesGL[i*9 + 3] = vertices[(int)faces[i].point.y].x;
		verticesGL[i*9 + 4] = vertices[(int)faces[i].point.y].y;
		verticesGL[i*9 + 5] = vertices[(int)faces[i].point.y].z;

		verticesGL[i*9 + 6] = vertices[(int)faces[i].point.z].x;
		verticesGL[i*9 + 7] = vertices[(int)faces[i].point.z].y;
		verticesGL[i*9 + 8] = vertices[(int)faces[i].point.z].z;		
	}
	generatedVerticesVector = true;
	return true;
}

bool ObjModel::generateGLVerticesTexture(){
	if(!generatedVertTextVector)
		vertTextGL = (float*)malloc(2*3*getNumberFaces()*sizeof(float));


	if(!vertTextGL)
		return false;

	for(int i=0; i < getNumberFaces();i++)
	{
		vertTextGL[i*6    ] = vertexTextures[(int)faces[i].texture.x].x;
		vertTextGL[i*6 + 1] = vertexTextures[(int)faces[i].texture.x].y;

		vertTextGL[i*6 + 2] = vertexTextures[(int)faces[i].texture.y].x;
		vertTextGL[i*6 + 3] = vertexTextures[(int)faces[i].texture.y].y;

		vertTextGL[i*6 + 4] = vertexTextures[(int)faces[i].texture.z].x;
		vertTextGL[i*6 + 5] = vertexTextures[(int)faces[i].texture.z].y;
	}

	generatedVertTextVector = true;

	return true;
}

//Free memory
int ObjModel::deleteModel()
{
	vertices.clear();
	vertexNormals.clear();
	vertexTextures.clear();
	faces.clear();

	free(vertTextGL);
	free(verticesGL);
	free(indices);
	return 0;
}

int ObjModel::lineDescriptor(char a, char b){
	switch(a)
	{
	case 'v':
		if(b==' '){
			return 1;
		}else{
			if(b== 'n')
				return 2;
			else{
				if(b == 't')
					return 3;
			}
		}break;
	case 'f':
		return 4;break;
	case 'g':
		return 5;break;
	case 's':
		return 6;break;
	default:
		return -1;break;
	}
	return 0;
}