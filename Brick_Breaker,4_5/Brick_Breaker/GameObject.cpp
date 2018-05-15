#include "GameHeader.h"
GameObject::GameObject()
{}
GameObject::GameObject(const char* FilePath, SDL_Renderer* rend)
{
	ObjRender = rend;
	ObjTexture = Textures::TextureLoader(FilePath, ObjRender);
}
void GameObject::SetSource(int x, int y, int width, int hight)// double
{
	SourceRect.x = x, SourceRect.y = y, SourceRect.w = width, SourceRect.h = hight;
}
void GameObject::SetDest(int x, int y, int width, int hight)//double
{
	DestRect.x = x, DestRect.y = y, DestRect.w = width, DestRect.h = hight;
}
void GameObject::Render()
{
	SDL_RenderCopy(ObjRender, ObjTexture, &SourceRect, &DestRect);
}
GameObject::~GameObject()
{
	SDL_DestroyRenderer(ObjRender);
	SDL_DestroyTexture(ObjTexture);
}