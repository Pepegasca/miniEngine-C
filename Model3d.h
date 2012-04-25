#pragma once
#include<vector>
#include<math.h>

#define PI 3.14159265358979323846

class Model3d{

public:
	vector<Vertex3d> vertices;
	vector<Vertex3d> vertexNormals;
	vector<Vertex3d> vertexTextures;
	vector<TriangleFace> faces;


	void translate(float a, float b, float c){
		for (int i=0; i<(int)vertices.size(); i++) {
			vertices[i].x += a;
			vertices[i].y += b;
			vertices[i].z += c;
		}
	}
	void scale(float a, float b, float c){
		for (int i=0; i<(int)vertices.size(); i++) {
			vertices[i].x *= a;
			vertices[i].y *= b;
			vertices[i].z *= c;
		}
	}
///
// Function rotate matrix around axis x
///
	void rotateX(float ang){
	
		for (int i=0; i<(int)vertices.size(); i++) {
			float x = vertices[i].x;
			float y = vertices[i].y;
			float z = vertices[i].z;
			vertices[i].x = x;
			vertices[i].y = (float)(y * cos(ang*PI/180.0) - z*sin(ang*PI/180.0));
			vertices[i].z = (float)(y * sin(ang*PI/180.0) + z*cos(ang*PI/180.0));
		}
	}
///
// Function rotate matrix around axis y
///
	void rotateY(float ang){
	
		for (int i=0; i<(int)vertices.size(); i++) {
			float x = vertices[i].x;
			float y = vertices[i].y;
			float z = vertices[i].z;
			vertices[i].x = (float)(x * cos(ang*PI/180.0) + z*sin(ang*PI/180.0));
			vertices[i].y = y;
			vertices[i].z = (float)(-1.0 * x * sin(ang*PI/180.0) + z*cos(ang*PI/180.0));
		}
	}
///
// Function rotate matrix around axis x
///
	void rotateZ(float ang){
	
		for (int i=0; i<(int)vertices.size(); i++) {
			float x = vertices[i].x;
			float y = vertices[i].y;
			float z = vertices[i].z;
			vertices[i].x = (float)(x * cos(ang*PI/180.0f) - y * sin(ang*PI/180.0f));
			vertices[i].y = (float)(x * sin(ang*PI/180.0f) + y * cos(ang*PI/180.0f));
			vertices[i].z = z;
		}
	}

};