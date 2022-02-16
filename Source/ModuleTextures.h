#ifndef __MODULE_TEXTURE_H__
#define __MODULE_TEXTURE_H__

#include "External/SDL/include/SDL.h"
#include "Module.h"
#include "List.h"

struct TexturePath
{
	std::string path = "";
	long index = 0;
	int direccion;
};

class ModuleTextures : public Module
{
public:
	ModuleTextures(Application* app, bool start_enabled = true);
	~ModuleTextures();

	bool Init(pugi::xml_node&);
	bool CleanUp();
	//bool CleanUpTextures();

	//SDL_Texture* Load(std::string path);

	SDL_Texture* Load(std::string path, bool isName = false);

	void Unload(SDL_Texture* texture);

public:
	List<SDL_Texture*> textures;

private:
	List<TexturePath> texturePath;
};

#endif // !__MODULE_TEXTURE_H__