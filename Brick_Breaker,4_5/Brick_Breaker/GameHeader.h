#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include <string>
#include <fstream>
#include <SDL_mixer.h>
#include <vector>
#include <time.h>
#define INF 0x3f3f3f3f
using namespace std;
class GameObject
{
protected:
	SDL_Renderer* ObjRender;
	SDL_Texture* ObjTexture;
	SDL_Rect SourceRect, DestRect;
public:
	GameObject();
	GameObject(const char* FilePath, SDL_Renderer* rend);
    void Render();
	void SetSource(int x, int y, int width, int hight);
	void SetDest(int x, int y, int width, int hight);
	virtual SDL_Rect GetSource() =0;
	SDL_Rect GetDest() { return DestRect; };
	~GameObject();
};
class Ball :public GameObject
{
private:
	bool run;
	int yv, xv;
	int power;
public:
	static int FirstXV,FirstYV;
	Ball();
	Ball(const char* FilePath, SDL_Renderer* rend);
	void Update(int speedx, int speedy);
	pair<int, int> GetVelocity();
	SDL_Rect GetSource();
	int GetPower();
	void SetPower(int);
	~Ball();
};
class Paddle :public GameObject
{
private :
	const int WindowWidth = 750;
public:
	Paddle();
	Paddle(const char* FilePath, SDL_Renderer* rend);
	void Update(int speed);
	SDL_Rect GetSource();
	~Paddle();
};
class Bricks:public GameObject
{
private:
	int power;
public:
	Bricks();
	Bricks(const char* FilePath, SDL_Renderer* rend);
	bool IsDestroyed();
	SDL_Rect GetSource();
	void Update(int x);
	int GetPower();
	void SetPower(int);
	~Bricks();
};
class GameLevel
{
private:
	bool IsRunning;
	SDL_Window *MyWindow;
	SDL_Texture *Ground;
	SDL_Renderer *MyRender;
	Paddle* MyPaddle;
	Ball* MyBall;
	Bricks*** Bricks2dArr;// 2d Array of pointers (dinamically allocated)
	int Width, Hight;
	int Score;
	int difficulty;
	const int BricksRows = 6;
	const int BricksCols = 10;
	Mix_Music* SoundTrack;
	Mix_Chunk* Brickbleep;
public:
	static SDL_Event MyEvent;
	GameLevel();
	void InitAll(const char *, int , int , int , int ,int);
	void Update(int ,int);
	void UpdateBallPaddle();
	void Do_Bricks_Collision(int, int,int,int);
	void UpdatePaddle(int, int);
	void Render();
	void RenderBrick();
	void RenderPaddle();
	void RenderBall();
	void Events();
	int GetWidth();
	int GetHight();
	int GetScore();
	void Bricks_Arr_Initializer();
	void BricksLoader();
	string CheckBrickCollision(int,int); // return 'u' if the collision is from upward , 'd' downward, 'r' right , 'l' left*-
	bool GameOver();
	bool GameCompleted();
	~GameLevel();
};
class Textures
{
private:
	SDL_Texture* texture;
public:
	Textures();
	static SDL_Texture* TextureLoader(const char*, SDL_Renderer*);
	~Textures();
};
