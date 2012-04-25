#include"Vector3d.h"
Vector3d::Vector3d(void)
{
	x=0;y=0;z=0;w=0;
}

Vector3d::Vector3d(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
	w = 0;
}
Vector3d::Vector3d(int x1, int y1, int z1)
{
	x = (float)x1;
	y = (float)y1;
	z = (float)z1;
}


float Vector3d::getLengthSqr()
{
	return (x*x+y*y+z*z);
}

Vector3d Vector3d::operator +(const Vector3d &v){
	return Vector3d(x+v.x,+y+v.y,z+v.z);
}

float Vector3d::operator *(const Vector3d &v){
	return (x*v.x+y*v.y+z*v.z);
}
