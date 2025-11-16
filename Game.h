#pragma once
#ifndef GAME_H
#define GAME_H
#include "Snake.h"
//思考游戏里面需要什么？
//需要成员（尤其指要变化的变量）：蛇，食物，边缘大小，游戏状态
//需要的功能：构建游戏，生成食物，生成边缘，处理键盘按键（用户输入）
//(可以弄一个开始游戏，避免主程序复杂)
class Game {
private:
	Snake snake;
	pair<int, int> food;
	int width, height;
	bool isRuning;

	void GenerateFood();
	void Blender();
	void HandleInput();
	int getRandomNum();
public:
	Game();
	void start();
};

#endif 
