#include "GameHeader.h"
int Ball::FirstXV = 2;
int Ball::FirstYV = 2;
Ball::Ball()
{
	run = 0;
	xv = yv = 2;
	power = 1;
}
Ball::Ball(const char* FilePath, SDL_Renderer* rend) :GameObject(FilePath, rend)
{
	run = 0;
	xv = yv = 2;
	power = 1;
}
pair<int, int> Ball::GetVelocity()
{
	return make_pair(xv, yv);
}
int Ball::GetPower()
{
	return power;
}
void Ball::SetPower(int power)
{
	this->power = power;
}
SDL_Rect Ball::GetSource()
{
	return SourceRect;
}
void Ball::Update(int speedx,int speedy)
{
	xv = speedx, yv = speedy;
	if (GameLevel::MyEvent.type == SDL_KEYDOWN)
	{
		if (GameLevel::MyEvent.key.keysym.sym == SDLK_s)run = 1;
	}
	if (run)DestRect.x += xv;
	if (run)DestRect.y += yv;
}
Ball::~Ball()
{}
