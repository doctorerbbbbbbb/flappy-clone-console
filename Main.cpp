#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>
#include <vector>

using namespace std;

/*Written By Muhammad Asif*/
/*A MILESTONE for me*/

class Pipe
{

public:
	int pipeX;
	int pipeY;
	int cords[20] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	int getSize() const {
		return size(cords);
	}

};

bool GameOver = false;
const int width = 50, height = 20;
int x, y;
int jumpForce = 2, gravity = 1/*Gravity*/;
const float timer = 0.5f; //For player and Gravity
const float pTimer = 0.3f; //For Pipe Movement General Delay in movement
const float pCTimer = 5; //For Pipe Creation
float currentTimer = 1;
float currentPTime = 1;
float currentPCTime = 1;

vector<Pipe> pipes;


int randomInRange(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());  // Static = created only once
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

void Setup()
{
	x = width / 4;
	y = height / 2;
}


void AddNewPipe()
{
	Pipe tempPipe;
	int randNum = randomInRange(2,  14);

	for (int i = 0; i < tempPipe.getSize(); i++)
	{
		if (i == randNum)
		{
			tempPipe.cords[i] = 0;
			tempPipe.cords[i + 1] = 0;
			tempPipe.cords[i + 2] = 0;
			tempPipe.cords[i + 3] = 0;
			break;
		}
	}
	tempPipe.pipeX = width - 1;

	pipes.emplace_back(tempPipe);
}

void Update()
{
	currentTimer -= 0.1f;
	currentPTime -= 0.1f;
	currentPCTime -= 0.1f;

	//Time Delay Btw Adding new Pipes
	if (currentPCTime <= 0)
	{
		AddNewPipe();
		currentPCTime = pCTimer;
	}

	//Time Delay btw movement of pipes less the number faster they move
	if (currentPTime <= 0)
	{
		currentPTime = pTimer;
		for (int i = 0; i < pipes.size(); i++)
		{
			pipes[i].pipeX -= 1;
		}
	}
	//Time Delay Btw Player Gravity
	if (currentTimer <= 0)
	{
		currentTimer = timer;
		y += gravity;
	}

    //Player Input
	if (_kbhit())
	{
		char c = _getch();
		if (c == 32 && y != 0)
			y -= jumpForce;
			
	}

	
	
	//Game Over if player touches the ground
	if (y == height)
	{
		GameOver = true;
		cout << "Game OVEr";
	}
}
// Function to Draw the Map the Player the pipes
void Draw()
{
	system("cls");

	for (int i = 0; i < width - 1 ; i ++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{

		
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			
			if (j == x && i == y)
				cout << "O";
			else
			{
				bool isPrint = false;
				for (int k = 0; k < pipes.size(); k++)
				{
					if (pipes[k].pipeX <= 0)
					{
						pipes.erase(pipes.begin() + k);
						continue;
					}
					if (j == pipes[k].pipeX && i < height && pipes[k].cords[i] == 1)
					{
						cout << "%";
						isPrint = true;
					}
				}
				if(!isPrint)
				cout << " ";
			}
			
			if (j == width - 1)
			{
				cout<<"#";
			}
			
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

}



int main()
{
	Setup();
	while (!GameOver)
	{
		Draw();
		Sleep(50);
		Update();
	}
	
	return 0;
}
