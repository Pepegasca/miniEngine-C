#pragma once
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "TriangleFace.h"
#include "Model3d.h"

class ObjModel{
private:
	vector<Vertex3d> vertices;
	vector<Vertex3d> vertexNormals;
	vector<Vertex3d> vertexTextures;
	vector<TriangleFace> faces;

public:

	float *verticesGL;
	float *vertTextGL;
	unsigned short *indices;

	bool generatedVerticesVector;
	bool generatedVertTextVector;
	bool generatedIndexVector;

	ObjModel();
	ObjModel(const char *file);
	int getNumberVertices();

	int getNumberVertexNormals();
	
	int getNumberVertexTextures();
	int getNumberFaces();
	int loadModel(const char *file);
	bool generateGLIndices();

	bool generateGLVertices();

	bool generateGLVerticesTexture();

	//Free memory
	int deleteModel();

private:
	int lineDescriptor(char a, char b);
};