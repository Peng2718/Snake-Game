#pragma once
#ifndef SNAKE_H
#define SNAKE_H
#include <utility>
#include <vector>
using namespace std;
//思考蛇需要什么？
//成员：身体（一系列坐标的向量），方向
//功能：构建蛇，移动，长大，撞墙,获取蛇的性质
enum Direction
{
	UP,DOWN,LEFT,RIGHT
};
class Snake {
private:
	vector<pair<int, int>> body;
	Direction direction;
public:
	Snake(int staryX,int startY);
	void move();
	void grow();
	bool checkEat(pair<int,int> food);
	bool checkCollision(int width,int height);
	const vector<pair<int,int>>& getbody() const;
	void setDirection(Direction newdirection);
	Direction getDirection() const;
};
#endif 
