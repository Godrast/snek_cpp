#ifndef APPLE_HPP
#define APPLE_HPP
#include "snake.hpp"

class Snake;

class Apple {
	float x;
	float y;

public:
	Apple();
	float getX();
	float getY();
	void spawnApple(Snake *snek);
	void randomPos(float *x, float *y);
};
#endif // !APPLE_HPP
