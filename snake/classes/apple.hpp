#ifndef APPLE_HPP
#define APPLE_HPP
#include "snake.hpp"

class Snake;

class Apple {
	glm::mat4 position;
public:
	Apple();
	glm::mat4 getPosition();
	void spawnApple(Snake *snek);
	void randomPos();

};
#endif // !APPLE_HPP
