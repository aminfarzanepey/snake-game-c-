#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
//wrotten by AMIN FARZANEPEY.

using namespace std;
bool gameOver;
const int width = 50;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int n_tail;
enum e_direct {stop = 0, Left, Right, Up, Down}; 
e_direct dir;

void setup()
{
	
	gameOver = false;
	dir = stop;
	x = width / 2;
	y = height / 2;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;
}

void draw()
{
	system("cls");
	
	for (int i = 0; i < width+2; i++)
	cout << "#";
	cout << endl;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "@";	
			else if (i == fruit_y && j == fruit_x)
				cout << "*";	
			else
			{
				bool print = false;
				for(int k = 0; k < n_tail; k++)
				{
					if(tail_x[k] == j && tail_y[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
					if (!print)
				cout << " ";
			 } 	
				
			if (j == width-1)
				cout << "#" ;		
		}
		cout << endl;
	}
	
	for (int i = 0; i < width+2; i++)
	cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "press (Q) for quit." << endl; 
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				dir = Left;
				break;
			case 'd':
				dir = Right;
				break;
			case 'w':
				dir = Up;
				break;
			case 's':
				dir = Down;
				break;
			case 'q':
				gameOver = true;
				break;				
		}
	}
}

void logic()
{
	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	int prev2_x, prev2_y;
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < n_tail; i++)
	{
		prev2_x = tail_x[i];
		prev2_y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev2_x;
		prev_y = prev2_y;
	}
	switch (dir)
	{

		case Left:
			x--;
			break;
		case Right:
			x++;
			break;
		case Up:
			y--;
			break;
		case Down:
			y++;
			break;
		default:
			break;					
	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	for (int i = 0; i < n_tail; i++)
	if (tail_x[i] == x && tail_y[i] == y)
	gameOver = true;
	if (x == fruit_x && y == fruit_y)
	{
		score += 10; 
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		n_tail++;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
	
	system("MODE con cols = 24 lines = 25"); 
	setup();
	while (!gameOver)
	{
		draw();
		input();
		logic();
		Sleep(20);
	}
}