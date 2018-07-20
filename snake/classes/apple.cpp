#include "apple.hpp"
#include <time.h>

Apple::Apple() {
	srand(time(NULL));
}

void Apple::spawnApple(Snake *snek) {
	float randX, randY;
	randomPos(&randX, &randY);
	std::vector<tile> snakeBody = snek->getBody();
	for (std::vector<tile>::iterator it = snakeBody.begin(); it != snakeBody.end(); it++) {
		if (it->x == randX && it->y == randY) {
			it = snakeBody.begin() - 1;
			randomPos(&randX, &randY);
		}
	}
	x = randX;
	y = randY;

}

void Apple::randomPos(float *x, float *y) {
	float randX = rand() % 29 - 14;
	float randY = rand() % 20 - 9;
	*x = randX;
	*y = randY;
}

float Apple::getX() {
	return x;
}


float Apple::getY() {
	return y;
}