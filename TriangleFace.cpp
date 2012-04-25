#include "TriangleFace.h"
TriangleFace::TriangleFace(void){
		
	}
	
TriangleFace::TriangleFace(Vertex3d a1, Vertex3d b1, Vertex3d c1){
		point=a1; 
		texture=b1; 
		normal=c1;
	}
