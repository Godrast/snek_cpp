#include "apple.hpp"
#include <time.h>

Apple::Apple() {
	srand(time(NULL));
}

void Apple::spawnApple(Snake *snek) {
	std::vector<Tile> snakeBody = snek->getBody();
	bool alreadyExists = false;
	do {
		randomPos();
		alreadyExists = snek->isColidingWithSnakeBody(position, true);
	} while (alreadyExists);


}

void Apple::randomPos() {
	float randX = (rand() % 270) / 10.0 - 13;
	float randZ = (rand() % 200) / 10.0 - 9;
	position = glm::translate(glm::mat4(), glm::vec3(randX, 0.0f, randZ));
}

glm::mat4 Apple::getPosition() {
	return position;
}

