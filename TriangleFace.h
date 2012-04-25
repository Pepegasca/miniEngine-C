#pragma once
#include "Vertex3d.h"

class TriangleFace{
public:	
	Vertex3d point;
	Vertex3d normal;
	Vertex3d texture;

	TriangleFace(void);
	
	TriangleFace(Vertex3d a1, Vertex3d b1, Vertex3d c1);

};