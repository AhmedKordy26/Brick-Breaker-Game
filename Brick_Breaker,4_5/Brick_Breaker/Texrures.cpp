#include "GameHeader.h"
SDL_Texture* Textures::TextureLoader(const char *Path, SDL_Renderer* rend)
{
	SDL_Surface* tmpTextures = IMG_Load(Path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, tmpTextures);
	SDL_FreeSurface(tmpTextures);
	return texture;
}
Textures::Textures()
{}
Textures::~Textures()
{}