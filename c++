#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;
void Shift_Right(int arr[], int size) {
	for (int i = size - 2; i >= 0; i--)
		arr[i + 1] = arr[i];
}
//.....................Properties.....................//
enum Direction {Top = 1, Down,Right,Left};
struct Map { int Widht, Height, FruitX, FruitY; };
struct Snake { int HeadX, HeadY, Tail_N,Tail_X[50],Tail_Y[50]; char Dir; };
struct Player { int Score; bool lose; };
//...................................................//
Map Map1; Snake Snake1; Player Player1;
void Generate_Fruit() {
	srand(time(NULL));
	Map1.FruitX = rand() % (Map1.Widht - 2) + 1; // 1 to 38
	Map1.FruitY = rand() % (Map1.Height - 2) + 1; // 1 to 38
}
void Setup() {
	//.................properties_Map..................//
	Map1.Widht = 40;
	Map1.Height = 20;
	Generate_Fruit();
	//................properties_Snake.................//
	Snake1.HeadX = Map1.Widht / 2;
	Snake1.HeadY = Map1.Height / 2;
	Snake1.Tail_N = 0;
	//................properties_Player................//
	Player1.Score = 0;
	Player1.lose = false;
}
void Draw() {
	system("cls");
		for (int i = 0; i < Map1.Height; i++) {
			for (int j = 0; j < Map1.Widht; j++) {
				if (i == 0 || i == Map1.Height - 1) cout << "*";
				else if (j == 0 || j == Map1.Widht - 1) cout << "*";
				else if (i == Snake1.HeadY && j == Snake1.HeadX) cout << "O";
				else if (i == Map1.FruitY && j == Map1.FruitX) cout << "$";
				else
				{
					bool printed = false;
					for (int z = 0; z < Snake1.Tail_N; z++) {
						if (Snake1.Tail_X[z] == j && Snake1.Tail_Y[z] == i) {
							cout << "o";
							printed = true;
							break;
						}

					}
					if (!printed) cout << " ";
				}
			}
			cout << endl;
		}
		cout << "Player Score : " << Player1.Score << endl;
		        cout<<"................."<<"\n";
        cout<<"W = Top"<<"\n"<<"S = Down"<<"\n"<<"A = Left"<<"\n"<<"D = right"<<"\n"<<"x = exit"<<"\n";
	}
void Input() {
	if (_kbhit()) {
		char c = _getch();
		switch (c) {
		case 'w':Snake1.Dir = Top; break;
		case 's':Snake1.Dir = Down; break;
		case 'd':Snake1.Dir = Right; break;
		case 'a':Snake1.Dir = Left; break;
		case 'x':exit(0);
		}
	}
}
void Move() {
	Shift_Right(Snake1.Tail_X, 50);
	Shift_Right(Snake1.Tail_Y, 50);
	Snake1.Tail_X[0] = Snake1.HeadX;
	Snake1.Tail_Y[0] = Snake1.HeadY;
	switch (Snake1.Dir)
	{
	case Top: Snake1.HeadY--; break;
	case Down: Snake1.HeadY++; break;
	case Right:Snake1.HeadX++; break;
	case Left:Snake1.HeadX--; break;
	}
	if (Snake1.HeadY >= Map1.Height || Snake1.HeadY <= 0 || Snake1.HeadX >= Map1.Widht || Snake1.HeadX <= 0)
	{
		Player1.lose = true;
	}
	if (Snake1.HeadX == Map1.FruitX && Snake1.HeadY == Map1.FruitY) {
		Generate_Fruit();
		Player1.Score += 1;
		Snake1.Tail_N++;
	}
}
int main()
{
	Setup();
	while (!Player1.lose)
	{
		Draw();
		Input();
		Move();
		Sleep(50);
	}
	system("pause");
	return 0;
}
