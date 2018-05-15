#include "GameHeader.h"
Bricks::Bricks()
{
	power = 1;
}
Bricks::Bricks(const char* FilePath, SDL_Renderer* rend) :GameObject(FilePath, rend)
{
	power = 1;
}
int Bricks::GetPower()
{
	return power;
}
void Bricks::SetPower(int power)
{
	this->power = power;
}
bool Bricks::IsDestroyed()
{
	return (power<=0);
}
void Bricks::Update(int x)  // called when the ball collids with the brick
{
	power -= x;
}
SDL_Rect Bricks::GetSource()
{
	return SourceRect;
}
Bricks::~Bricks()
{}