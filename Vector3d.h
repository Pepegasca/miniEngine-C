#pragma once
class Vector3d{
public:
	float x, y , z, w;
	Vector3d(void);
	Vector3d(float x1, float y1, float z1);
	Vector3d(int x1, int y1, int z1);
	float getLengthSqr();
	Vector3d operator +(const Vector3d &v);
	float operator *(const Vector3d &v);
};