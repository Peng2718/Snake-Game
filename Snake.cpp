#include "Snake.h"
#include <cmath>

//思考蛇有哪些性质需要填入，将蛇初始在中间，需要填入坐标，方向也要初始化
Snake::Snake(int startX,int startY) :direction(RIGHT)
{
	body.push_back({ startX,startY });
}
void Snake::move()
{
	pair<int, int> head = body.front();
	switch (direction)
	{
	case UP:
		head.second-=5;
		break;
	case DOWN:
		head.second+=5;
		break;
	case LEFT:
		head.first-=5;
		break;
	case RIGHT:
		head.first+=5;
		break;
	}
	body.insert(body.begin(), head);
	body.pop_back();
}
void Snake::grow()
{
	body.push_back(body.back());
}
bool Snake::checkCollision(int width,int height)
{
	pair<int, int> head = body.front();
	if (head.first < 1 || head.second < 1 || head.first - width >= -1 
		|| head.second - height >= -1)
		return true;
	for (size_t i = 1; i < body.size()-1; i++)
	{
		if (head == body[i])
			return true;
	}
	return false;
}
const vector<pair<int,int>>& Snake::getbody() const
{
	return body;
}
void Snake::setDirection(Direction newdirection)
{
	if ((direction == UP && newdirection != DOWN) ||
		(direction == DOWN && newdirection != UP) ||
		(direction == LEFT && newdirection != RIGHT) ||
		(direction == RIGHT && newdirection != LEFT)) {
		direction = newdirection;
	}
}
Direction Snake::getDirection() const
{
	return direction;
}
bool Snake::checkEat(pair<int,int> food)
{
	int x = body.front().first;
	int y = body.front().second;
	int a = food.first;
	int b = food.second;
	int dx = abs(x - a);
	int dy = abs(y - b);
	if (dx * dx + dy * dy < 50)
		return true;
	else
		return false;
}