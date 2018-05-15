#include "GameHeader.h"
SDL_Event GameLevel::MyEvent;

GameLevel::GameLevel()
{
	IsRunning = false;
	Score = 0;
	MyWindow = NULL;
	MyRender = NULL;
	MyBall = NULL;
	MyPaddle = NULL;
	SoundTrack = NULL;
	Brickbleep = NULL;
}
int GameLevel::GetHight()
{
	return Hight;
}
int GameLevel::GetWidth()
{
	return Width;
}
int GameLevel::GetScore()
{
	return Score;
}
void GameLevel::Bricks_Arr_Initializer()
{
	Bricks2dArr = new Bricks**[BricksRows];
	for (int c = 0; c  <BricksRows; c++)
	{
		Bricks2dArr[c] = new Bricks*[BricksCols];
	}
	return;

}
void GameLevel::BricksLoader()
{
	int score, sc[] = { 0, 5, 10, 15 },s=difficulty;
	int bricks[6][10];
	memset(bricks, 0, sizeof(bricks));
	srand(time(NULL));
	bool fr = 0;
	for (int i = 0; i<6; ++i){
		for (int j = 0; j<10; ++j){
			int idx = rand() % 1000000;
			if (s <= 0)break;
			bricks[i][j] = idx % 4, s -= sc[idx % 4];
		}
	}
	
	for (int i = 0,ypos=60; i < BricksRows; i++,ypos+=50)// hight of the Brick is 50
	{
		for (int j = 0,xpos=50; j < BricksCols; j++,xpos+=65)// width of the Brick is 65
		{
			if (bricks[i][j] == 1)
			{
				Bricks2dArr[i][j] = new Bricks("Textures/block1.png", MyRender);
				Bricks2dArr[i][j]->SetPower(1);
				Bricks2dArr[i][j]->SetDest(xpos, ypos, 65, 50);
				Bricks2dArr[i][j]->SetSource(0, 0, 128, 128);
			}
			else if (bricks[i][j] == 2)
			{
				Bricks2dArr[i][j] = new Bricks("Textures/block2.png", MyRender);
				Bricks2dArr[i][j]->SetPower(2);
				Bricks2dArr[i][j]->SetDest(xpos, ypos, 65, 50);
				Bricks2dArr[i][j]->SetSource(0, 0, 128, 128);
			}
			else if (bricks[i][j]== 3)
			{
				Bricks2dArr[i][j] = new Bricks("Textures/block3.png", MyRender);
				Bricks2dArr[i][j]->SetPower(3);
				Bricks2dArr[i][j]->SetDest(xpos, ypos, 65, 50);
				Bricks2dArr[i][j]->SetSource(0, 0, 128, 128);
			}
			else if (bricks[i][j]==0)Bricks2dArr[i][j] = NULL;
		}
	}
	return;
}
void GameLevel::InitAll(const char *title, int xpos, int ypos, int width, int hight,int Difficulty)
{
	// Kordy // 18_4_2018
	Width = width, Hight = hight;
	this->difficulty = Difficulty;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)>=0)
	{
		//  write to console if its can successfuly intialized
		cout << "Can be intialized" << endl;

		MyWindow = SDL_CreateWindow(title, xpos, ypos, width, hight, 0);
		if (MyWindow)//checks if the window was created successfully
			cout << "yaaa the window has been created " << endl;
		SoundTrack = Mix_LoadMUS("Audioss/breakout.mp3");
		Brickbleep = Mix_LoadWAV("Audioss/bleep.wav");
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(SoundTrack, -1);
		else if (Mix_PausedMusic())
			Mix_ResumeMusic();
		MyRender = SDL_CreateRenderer(MyWindow, -1, 0);
		cout << "yaaa the renderer has been created " << endl;

		/* creating the texture of the Background */
		Ground = Textures::TextureLoader("Textures/eg.jpg", MyRender);
		/* creating the texture of the Paddle */
		MyPaddle = new Paddle("Textures/paddle.png", MyRender);
		//MyPaddle->SetDest(Width/2-65, hight-40, 170, 32);
		MyPaddle->SetDest(Width / 2 -85, hight - 40, 170, 32);
		MyPaddle->SetSource(0, 0, 512, 128);
		/* creating the texture of the Ball */
		MyBall = new Ball("Textures/awesomeface.png", MyRender);
		MyBall->SetDest(Width/2-50,hight-70,30,30);
		MyBall->SetSource(0, 0, 512, 512);
		Bricks_Arr_Initializer();
		BricksLoader();
		IsRunning = true;
	}
	else
	{
		cout << "Sorry ... Can't be intialized" << endl;
		IsRunning = false;
	}
}
string GameLevel::CheckBrickCollision(int Row,int Col)
{
	if (Bricks2dArr[Row][Col] == NULL)return"no";
	SDL_Rect brickRect = Bricks2dArr[Row][Col]->GetDest();
	SDL_Rect ballRect = MyBall->GetDest();
	pair<int, int> tmpVelocity =MyBall->GetVelocity();
	tmpVelocity.first = abs(tmpVelocity.first);
	tmpVelocity.second = abs(tmpVelocity.second);

	pair<int, int> brickRight = make_pair((brickRect.x + brickRect.w), (brickRect.x + brickRect.w - tmpVelocity.first)); // Right border limits
	pair<int, int> brickLeft = make_pair((brickRect.x - ballRect.w), (brickRect.x + tmpVelocity.first - ballRect.w)); //  Left border limits
	pair<int, int> brickUp = make_pair((brickRect.y - ballRect.h + 3), (brickRect.y + tmpVelocity.second - ballRect.h + 3));// Upper border limits
	pair<int, int> brickLower = make_pair((brickRect.y + brickRect.h), (brickRect.y + brickRect.h - tmpVelocity.second)); // lower border limits
	if ((ballRect.x >= brickLeft.first) && (ballRect.x <= brickRight.first))
	{
		if (ballRect.y <= brickLower.first&&ballRect.y >= brickLower.second)return "d";
		 if (ballRect.y >= brickUp.first&&ballRect.y <= brickUp.second)return "u";
	}
	if ((ballRect.y >= brickUp.first) && (ballRect.y <= brickLower.first))
	{
		if (ballRect.x >= brickLeft.first&&ballRect.x <= brickLeft.second)return "l";
		if (ballRect.x <= brickRight.first&&ballRect.x >= brickRight.second)return "r";
	}
	return "no";
}
void GameLevel::UpdatePaddle(int PaddleSPeed, int PaddleWidth)
{
	SDL_Rect PaddleDestRect = MyPaddle->GetDest();
	MyPaddle->SetDest(PaddleDestRect.x, PaddleDestRect.y, PaddleWidth, PaddleDestRect.h); // Updateing The Paddle Width if there is a power up
    MyPaddle->Update(PaddleSPeed);

}
void GameLevel::UpdateBallPaddle()
{
	SDL_Rect PaddleDestRect = MyPaddle->GetDest();
	SDL_Rect BallDestRect = MyBall->GetDest();
	BallDestRect.h -= 5;
	pair<int, int>tmpVelocity = MyBall->GetVelocity();
	//cout << " 1 " << tmpVelocity.first << " " << tmpVelocity.second << endl;
	if (BallDestRect.y + BallDestRect.h >= PaddleDestRect.y && (BallDestRect.x >= PaddleDestRect.x&&BallDestRect.x <= PaddleDestRect.x + PaddleDestRect.w))
	{
		//cout << "AYWA" << endl;
		int borders = PaddleDestRect.w / 4 ;
		if (BallDestRect.x <= PaddleDestRect.x + borders - 5 || BallDestRect.x + BallDestRect.w<PaddleDestRect.x + borders - 5)
	{ 
		tmpVelocity.first = __min(abs(tmpVelocity.first) + 2, 5), tmpVelocity.second = __min(tmpVelocity.second + 1, 3); 
		tmpVelocity.first *= (tmpVelocity.first > 0) ? -1 : 1;
		// cout << 1 << " " << 1 << endl;
	}
		
	else if (BallDestRect.x >= PaddleDestRect.x + PaddleDestRect.w - borders)
	{
		tmpVelocity.first = __min(abs(tmpVelocity.first) + 2, 5), tmpVelocity.second = __min(tmpVelocity.second + 1, 3); 
		tmpVelocity.first *= (tmpVelocity.first < 0) ? -1 : 1; 
		//  cout << 2 << " BALLX " << BallDestRect.x << " BALLY " << BallDestRect.y << " PADDLEX " << PaddleDestRect.x << " PADDLEY " << PaddleDestRect.y << " SPEEDX " << tmpVelocity.first << " SPEEDY " << tmpVelocity.second << endl;
	}
	
	else if (BallDestRect.x + BallDestRect.w < PaddleDestRect.x + (PaddleDestRect.w / 2 )&& BallDestRect.x >= PaddleDestRect.x + borders)
	{
		tmpVelocity.first = Ball::FirstXV, tmpVelocity.second = Ball::FirstYV;
		tmpVelocity.first *= (tmpVelocity.first > 0) ? -1 : 1; //cout << 1 << " " << 3 << endl;
	}
		
	 else if (BallDestRect.x >= PaddleDestRect.x + (PaddleDestRect.w / 2 )&& BallDestRect.x <= PaddleDestRect.x + PaddleDestRect.w - borders)
	 {
		 tmpVelocity.first = Ball::FirstXV, tmpVelocity.second = Ball::FirstYV; 
		 tmpVelocity.first *= (tmpVelocity.first < 0) ? -1 : 1;
		 //cout << 1 << " " << 4 << endl;
	 }
		if (tmpVelocity.second>0)
		tmpVelocity.second *= -1;
	}
	 if (BallDestRect.y <= 0&&tmpVelocity.second<0)// Upper Border
	{
		tmpVelocity.second *= -1;
	}
	 if (BallDestRect.x + BallDestRect.w >= Width&&tmpVelocity.first>0)// Right Border
	{
		tmpVelocity.first *= -1;
		
	}
	 if (BallDestRect.x <= 0 && tmpVelocity.first<0) // left Border
	{
		tmpVelocity.first *= -1;
	}
	//cout << " 2 " << tmpVelocity.first << " " << tmpVelocity.second << endl;
	MyBall->Update(tmpVelocity.first, tmpVelocity.second);
	return;
}
void GameLevel::Do_Bricks_Collision(int Ball_X_Speed, int Ball_Y_Speed,int Row,int Col)
{
	SDL_Rect BallDestRect = MyBall->GetDest();
	SDL_Rect BrickRect = Bricks2dArr[Row][Col]->GetDest();
	BallDestRect.h -= 10;
	pair<int, int>tmpVelocity = MyBall->GetVelocity();
	int BrickPower = Bricks2dArr[Row][Col]->GetPower();
	int BallPower = MyBall->GetPower();
	if (BrickPower <= 0)
	{
		MyBall->Update(Ball_X_Speed, Ball_Y_Speed); return;
	}
	string check = CheckBrickCollision(Row,Col);
	if (check != "no"){ Score += 5; Bricks2dArr[Row][Col]->SetPower(BrickPower - BallPower);  }
	if (check == "u")
		Ball_Y_Speed *= (Ball_Y_Speed>0) ? -1 : 1;
	 if (check == "d")
		Ball_Y_Speed *= (Ball_Y_Speed<0) ? -1 : 1;
	 if (check == "r")
		Ball_X_Speed *= (Ball_X_Speed<0) ? -1 : 1;
	 if (check == "l")
		Ball_X_Speed *= (Ball_X_Speed>0) ? -1 : 1;
	MyBall->Update(Ball_X_Speed, Ball_Y_Speed);
	return;
}

void GameLevel::Update(int PaddleSPeed,int PaddleWidth)
{
	SDL_Rect PaddleDestRect = MyPaddle->GetDest();
	SDL_Rect BallDestRect = MyBall->GetDest();
	//SDL_Rect brickRect = MyBrick[0]->GetDest();
	pair<int, int>tmpVelocity = MyBall->GetVelocity();
	if (BallDestRect.y > PaddleDestRect.y)
	{
		IsRunning = false;
		return;
	}
	UpdateBallPaddle(); // Collision of Ball with The Paddle
	UpdatePaddle(PaddleSPeed, PaddleWidth);
	for (int i = 0; i < BricksRows; i++)
	{
		for (int j = 0; j < BricksCols; j++)
		{
			if (Bricks2dArr[i][j] && CheckBrickCollision(i, j) != "no"&&Bricks2dArr[i][j]->GetPower()>0){ Do_Bricks_Collision(tmpVelocity.first, tmpVelocity.second, i, j); }
		}
	}
	return;
}
void GameLevel::Render()
{
	// source is the texture coordinates of the part of texture you wanna draw
	// destination is where you wanna the texture to be drawn and the size of the texture
	SDL_RenderClear(MyRender);
	SDL_RenderCopy(MyRender, Ground, NULL, NULL);
	MyPaddle->Render();
	MyBall->Render();
	for (int i = 0; i < BricksRows; i++)
	{
		for (int j = 0; j <BricksCols; j++)
		{
			if (Bricks2dArr[i][j]&&Bricks2dArr[i][j]->GetPower()>0)
				Bricks2dArr[i][j]->Render();
		}
	}
	SDL_RenderPresent(MyRender);
}
void GameLevel::Events()
{
	SDL_PollEvent(&MyEvent);
	if (MyEvent.type == SDL_QUIT)
	{
		IsRunning = false;
	}
}
bool GameLevel::GameOver()
{
	return IsRunning;
}
bool GameLevel::GameCompleted()
{
	for (int i = 0; i < BricksRows; i++) 
	{
		for (int j = 0; j < BricksCols; j++) 
		{
			if (Bricks2dArr[i][j] && Bricks2dArr[i][j]->GetPower() > 0 )
			{
				return false;
			}
		}
	}
	return true;
}
GameLevel::~GameLevel()
{
	SDL_DestroyWindow(MyWindow);
	SDL_DestroyRenderer(MyRender);
	SDL_DestroyTexture(Ground);
	Mix_PauseMusic();
	delete MyPaddle;
	delete MyBall;
	for (int i = 0; i < BricksRows; i++) {
		for (int j = 0; j < BricksCols; j++) {
			delete Bricks2dArr[i][j]; // delete the pointers
		}
		delete[] Bricks2dArr[i]; // delete  columns of each row
	}
	delete[] Bricks2dArr; //delete the rows
	Bricks2dArr = NULL;
	SDL_Quit();
	cout << "The GameLevel has been cleaned SUCCESSFULLY" << endl;
}