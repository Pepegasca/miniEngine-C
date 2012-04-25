class Vertex3d{

public:
	float x, y , z, w;
	
	Vertex3d(void)
	{
		x=0;y=0;z=0;w=1;
	}

	Vertex3d(float x1, float y1, float z1)
	{
		x = x1;
		y = y1;
		z = z1;
		w = 1;
	}
	Vertex3d(int x1, int y1, int z1)
	{
		x = (float)x1;
		y = (float)y1;
		z = (float)z1;
		w = (float)1;
	}
};