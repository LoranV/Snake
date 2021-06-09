#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[120], tail_y[120];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruit_x = rand() % width;
	fruit_y = rand() & height;
	score = 0;
};

void Draw() {
	system("cls"); // Очистка консолі
	for (int i = 0; i < width + 1; i++) cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1) { cout << "#"; }
			if (i == y && j == x)
			{
				cout << "0";
			}
			else if (i == fruit_y && j == fruit_x)
			{
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tail_x[k] == j && tail_y[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++) cout << "#";
	cout << endl;
	cout << "Score: " << score;
};

void Input() {
	if (_kbhit())
	{
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			system("cls");
			cout << "GAME OVER";
			break;
		}
	}
};

void Logic() {
	int prevX = tail_x[0];
	int prevY = tail_y[0];
	int prev2X, prev2Y;
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tail_x[i];
		prev2Y = tail_y[i];
		tail_x[i] = prevX;
		tail_y[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	};
	if (x >= width || x < 0 || y >= height || y < 0)// Кінець гри, якщо вийшов за межі
	{
		gameOver = true;
	}
	if (x == fruit_x && y == fruit_y)
	{
		score+=10;
		fruit_x = rand() % width;
		fruit_y = rand() & height;
		nTail++;
	}
};

int main() {
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
};