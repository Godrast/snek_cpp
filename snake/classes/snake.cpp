#include "snake.hpp"
#include <iostream>


Snake::Snake(std::string direction) {
	nextDirection = direction;
	for (int i = 0; i < size; i++) {
		addTile(0.0f, (float)i, direction);
	}
}

std::vector<Tile> Snake::getBody() {
	return body;
}

void Snake::addTile(float x, float z, std::string dir) {
	Tile tempTile;
	tempTile.position = glm::translate(glm::mat4(), glm::vec3(float(x), 0.0f, float(z)));
	tempTile.direction = dir;
	body.push_back(tempTile);
};

void Snake::addTile(Tile newTile) {
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
	Tile lastTile = body.at(getSize() - 1);


	for (std::vector<Tile>::reverse_iterator it = body.rbegin(); it != body.rend(); it++) {
		if (it->direction == "UP") {
			//it->y += 1.0f;
			it->position = glm::translate(it->position, glm::vec3(0.0f, 0.0f, -1.0f));
		} else if (it->direction == "DOWN") {
			//it->y -= 1.0f;
			it->position = glm::translate(it->position, glm::vec3(0.0f, 0.0f, 1.0f));

		} else if (it->direction == "LEFT") {
			//it->x -= 1.0f;
			it->position = glm::translate(it->position, glm::vec3(-1.0f, 0.0f, 0.0f));

		} else if (it->direction == "RIGHT") {
			//it->x += 1.0f;
			it->position = glm::translate(it->position, glm::vec3(1.0f, 0.0f, 0.0f));

		}

		if (it + 1 != body.rend()) {
			it->direction = (it + 1)->direction;
		} else {
			//CHECK COLLISION

			//std::cout<<"HALP: "<< glm::to_string(it->position[3])<<"\n";
			float x = it->position[3].x;
			float z = it->position[3].z;
			if (x < -14.0f || x > 14.0f || z > 11.0f || z < -10.0f) {
				shouldReset = true;
			} else if (apple->getPosition() == it->position) {
				shouldAddTile = true;
			} else {
				if (findTile(*it)) {
					shouldReset = true;
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
	//TESTS
	//body.at(0).direction = dir;

	nextDirection = dir;
}

std::string Snake::getCurrentDirection() {
	return body.at(0).direction;
}

void Snake::reset(std::string direction) {
	body.clear();
	nextDirection = direction;
	for (int i = 0; i < size; i++) {
		addTile(0.0f, (float)i, direction);
	}
}


bool Snake::findTile(Tile myTile) {
	auto pred = [myTile](const Tile & otherTile) {
		return otherTile.position == myTile.position;
	};
	return std::find_if(body.begin() + 1, body.end(), pred) != body.end();

}
