#include <vector>
#include "Shader.h"
#include "ObjModel.h"
#include "Texture.h"
#include "SceneManager.h"

using namespace std;

class ResourceManager{

	vector<Shader*> shaders;
	vector<ObjModel*> models;
	vector<Texture*> textures;

public:
	
	int addShader(Shader *shad);
	int addObjModel(ObjModel *model);
	int addTexture(Texture *text);

	int initResources(SceneManager *scnManager);

	int LoadTexture (const char *fileName );
};