#include "GameHeader.h"
Paddle::Paddle()
{}
Paddle::Paddle(const char* FilePath, SDL_Renderer* rend) :GameObject(FilePath, rend)
{}
void Paddle::Update(int speed)
{	
	if (GameLevel::MyEvent.type == SDL_KEYDOWN)
	{
		SDL_Keycode tmpkeycode = GameLevel::MyEvent.key.keysym.sym;
		if (tmpkeycode == SDLK_a &&DestRect.x>=0)
		{
			DestRect.x = __max(DestRect.x - speed, 0);
		}
		else if (tmpkeycode == SDLK_d &&DestRect.x+DestRect.w<=WindowWidth)
		{
			DestRect.x = __min(WindowWidth-DestRect.w, DestRect.x + speed);
		}
	}
}
SDL_Rect Paddle::GetSource()
{
	return SourceRect;
}
Paddle::~Paddle()
{}