#include "GameHeader.h"
#include "Game.h"
GameLevel *GameVar = nullptr;
int StringToInt(string score)
{
	int ans = 0;
	int sz = score.size();
	reverse(score.begin(), score.end());
	for (int c = 0; c < sz; c++)
	{
		ans += (score[c] - '0')*powl(10, c);
	}
	return ans;
}
vector<string> GetDataInFile(ifstream &file)
{
	string Fname = "";
	vector<string>vec;
	while (getline(file, Fname))
	{
		vec.push_back(Fname);
	}
	return vec;
}
int main(int argc,char *argv[])
{
	ifstream inFile;
	ofstream outFile;
	inFile.open("Files/Players.txt");
	const int FrameDelay = 15;
	unsigned long long FrameStart,FrameTime;
	string playerName, x;
	int score=-1,find,dif;
	vector<string> TmpFileData;
	TmpFileData = GetDataInFile(inFile);
	while (1)
	{
		cout << "Please Enter Your Name\n";
		getline(cin, playerName);
		for (int c = 0; c < TmpFileData.size(); c++)
		{
			find = c + 1;
			if (TmpFileData[c] == playerName)
			{
				score = StringToInt(TmpFileData[c + 1]); break;
			}
		}
		if (score == -1)
		{

			cout << "Your Name isn't stored in the file , press 1 to enter the name again or 2 to create a new account \n" << endl;
			getline(cin, x);
			if (x == "1")continue;
			else if (x == "2")
			{
				TmpFileData.push_back(playerName);
				score = 0;
				break;
			}
		}
		else break;

	}
    dif = 0;
	if (score!=0)
	cout << "Your Maximum Score is  \n"<<score << endl;
	while (1)
	{
		cout << " Choose Level Difficulty , for easy press 1 for midium press 2 for hard press 3 \n";
		getline(cin, x);
		if (x == "1")dif = 50;
		else if (x == "2")dif = 100;
		else if (x == "3")dif = 150;
		if (dif != 0)break;
		else
		{
			cout << "Please Enter a valid input \n";
		}
	}
	bool wantToPlay = 1;
	while (wantToPlay)
	{
		bool completed = 0;
		GameVar = new GameLevel();
		GameVar->InitAll("Brick Breaker ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 750, 550,dif);
		while (true) /* The Game Loop */
		{
			FrameStart = SDL_GetTicks();

			GameVar->Events();
			GameVar->Update(25, 160);
			GameVar->Render();
			FrameTime = SDL_GetTicks() - FrameStart;
			if (FrameDelay > FrameTime)
				SDL_Delay(FrameDelay - FrameTime);
			if (GameVar->GameCompleted())
			{
				cout << "WOOOOOOOOOOOOOW You Win \n";
				completed = 1;
				score +=  GameVar->GetScore();
				//SDL_Delay(1000);
				GameVar->~GameLevel();
				break;
			}
			if (!GameVar->GameOver())
			{
				cout << "You Lost :( \n";
				SDL_Delay(1000);
				GameVar->~GameLevel();
				break;
			}
		}
		if (completed)
		{
			cout << "Your maximum score is " << score << "\n";
			cout << "If You Want To Continue to the next level press 1 , or 2 to exit \n";
			while (cin >> x)
			{
				if (x == "1"){ dif += 25; break; }
				else if (x == "2"){
					wantToPlay = 0;
					break;
				}
			}
		}
		else if (!completed)
		{
			cout << "If You Want To try Again press 1 , or 2 to exit \n";
			while (cin >> x)
			{
				 if (x == "2")
				 {
					wantToPlay = 0;
					break;
				}
				 else if (x == "1")break;
			}
		}
		TmpFileData[find] = to_string(score);
		inFile.close();
		outFile.open("Files/Players.txt");
		for (int c = 0; c < TmpFileData.size(); c++)cout << TmpFileData[c] << endl;
		for (int c = 0; c < TmpFileData.size(); c++)outFile << TmpFileData[c] << endl;
	}
//	GameVar->~GameLevel(); /* Cleaning them allllll */
	system("pause");
	return EXIT_SUCCESS;
}