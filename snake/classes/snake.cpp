#include "snake.hpp"

Snake::Snake(std::string direction) {
	nextDirection = direction;
	for (int i = 0; i < size; i++) {
		addTile(0.0f, (float)-i, direction);
	}
}

std::vector<tile> Snake::getBody() {
	return body;
}

void Snake::addTile(float x, float y, std::string dir) {
	tile tempTile;
	tempTile.x = x;
	tempTile.y = y;
	tempTile.direction = dir;
	body.push_back(tempTile);
};

void Snake::addTile(tile newTile) {
	body.push_back(newTile);
};

unsigned int Snake::getSize() {
	return static_cast<unsigned int>(body.size());
};

//save last tile before moving, after moving, if apple was eaten, add that tile to teh end
void Snake::move(Apple *apple) {
	bool shouldAddTile = false;
	bool shouldReset = false;
	if (getCurrentDirection() != nextDirection) {
		body.at(0).direction = nextDirection;
	}
	tile lastTile = body.at(getSize() - 1);


	for (std::vector<tile>::reverse_iterator it = body.rbegin(); it != body.rend(); it++) {
		if (it->direction == "UP") {
			it->y += 1.0f;
		} else if (it->direction == "DOWN") {
			it->y -= 1.0f;
		} else if (it->direction == "LEFT") {
			it->x -= 1.0f;
		} else if (it->direction == "RIGHT") {
			it->x += 1.0f;
		}

		if (it + 1 != body.rend()) {
			it->direction = (it + 1)->direction;
		} else {
			//CHECK COLLISION
			if (it->x < -14.0f || it->x > 14.0f || it->y > 10.0f || it->y < -10.0f) {
				shouldReset = true;
			} else if (apple->getX() == it->x && apple->getY() == it->y) {
				shouldAddTile = true;
			} else {
				for (std::vector<tile>::iterator it2 = body.begin() + 1; it2 != body.end(); it2++) {
					if (it2->x == it->x && it2->y == it->y) {
						shouldReset = true;
					}
				}
			}
		}
	}

	if (shouldAddTile) {
		apple->spawnApple(this);
		addTile(lastTile);
	}
	if (shouldReset) {
		reset("UP");
	}
};

void Snake::setDirection(std::string dir) {
	nextDirection = dir;
}

std::string Snake::getCurrentDirection() {
	return body.at(0).direction;
}

void Snake::reset(std::string direction) {
	body.clear();
	nextDirection = direction;
	for (int i = 0; i < size; i++) {
		addTile(0.0f, (float)-i, direction);
	}
}