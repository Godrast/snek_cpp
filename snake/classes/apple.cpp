#include "apple.hpp"
#include <time.h>

Apple::Apple() {
	srand(time(NULL));
}

void Apple::spawnApple(Snake *snek) {
	std::vector<Tile> snakeBody = snek->getBody();
	bool alreadyExists = false;
	do {
		alreadyExists = false;
		randomPos();
		for (std::vector<Tile>::iterator it = snakeBody.begin(); it != snakeBody.end(); ++it) {
			if (it->position == position) {
				alreadyExists = true;
				break;
			}
		}
	} while (alreadyExists);
	

}

void Apple::randomPos() {
	float randX = rand() % 27 - 13;
	float randZ = rand() % 20 - 9;
	position = glm::translate(glm::mat4(), glm::vec3(randX, 0.0f, randZ));
}

glm::mat4 Apple::getPosition() {
	return position;
}

