#include "esUtil.h"
#include "Texture.h"

int Texture::LoadTexture (const char *fileName )
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