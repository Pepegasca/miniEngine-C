#pragma once

#include <string>
#include <stdlib.h>

class Texture{
public:
	char *filename;
	int id;

	static int LoadTexture (const char *fileName );
};