#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
//#include <conio.h>
#include <easyx.h>
using namespace std;
ExMessage msg = { 0 };
//生成随机数(1到19）
int Game::getRandomNum()
{
	srand(static_cast<unsigned>(time(nullptr)));//将time_t转化为unsigned
	return rand() % 19 + 1;
}
inline int randInt(int min, int max) {
	static bool initialized = false;
	if (!initialized) {
		srand(static_cast<unsigned>(time(nullptr)));
		initialized = true;
	}
	return rand() % (max - min + 1) + min;
}
Game::Game() :snake(200, 200), width(500), height(500), isRuning(true)
{
	GenerateFood();
}
void Game::GenerateFood()//此时还要思考食物是否会生成在蛇上面
{
	int x, y;
	auto& body = snake.getbody();
	while (true)
	{
		bool able = true;
		x = randInt(10, width - 10);
		y = randInt(10, height - 10);
		for (int i = 0; i < body.size(); i++)
		{
			if (body[i]==make_pair(x,y))
			{
				able = false;
			}
		}
		if (able)
		{
			food = { x,y };
			break;
		}
	}
}
//void Game::Blender()//渲染食物，边缘，蛇身
//{
//	system("cls");//清屏
//	for (int y = 0; y < width; y++)
//	{
//		for (int x = 0; x < height; x++)
//		{
//			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
//			{
//				cout << "+";
//			}
//			else if(food==make_pair(x,y))
//			{
//				cout << "@";
//			}
//			else
//			{
//				auto& body = snake.getbody();
//				bool isbody = false;
//				for (int i = 0; i < body.size(); i++)
//				{
//					if (body[i] == make_pair(x, y))
//					{
//						cout << "#";
//						isbody = true;
//						break;
//					}
//				}
//				if (!isbody)
//					cout << " ";
//			}
//		}
//		cout << endl;
//	}
//}
void Game::Blender() 
{
	cleardevice();
	BeginBatchDraw();
	settextcolor(BLACK);
	char score[50];
	sprintf_s(score, "Score:%d", snake.getbody().size());
	outtextxy(500-100, 10, score);
	for (auto& segment : snake.getbody())
	{
		setfillcolor(GREEN);
		fillcircle(segment.first, segment.second, 15);
		setfillcolor(RED);
		fillcircle(food.first, food.second, 15);
	}
	EndBatchDraw();
}
void Game::HandleInput()
{
	if (peekmessage(&msg, EX_KEY))
	{
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case 'A':
				snake.setDirection(LEFT);
				break;
			case 'S':
				snake.setDirection(DOWN);
				break;
			case 'W':
				snake.setDirection(UP);
				break;
			case 'D':
				snake.setDirection(RIGHT);
				break;
			}
		}
	}
}
void Game::start()
{
	initgraph(500, 500, EX_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	while (isRuning)
	{
		Blender();
		HandleInput();
		snake.move();
		if (snake.checkEat(food))
		{
			snake.grow();
			GenerateFood();
		}
		if (snake.checkCollision(width, height))
		{
			isRuning = false;
		}
		Sleep(20);
	}
	while (1)
	{
		setbkcolor(WHITE);
		cleardevice();
		BeginBatchDraw();
		settextcolor(BLACK);
		char a[] = "Game Over";
		outtextxy(200, 200, a);
		EndBatchDraw();
	}
	closegraph();
}