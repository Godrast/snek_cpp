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
	float xOffset = 0;
	float zOffset = 0;
	if (newTile.direction == "UP") {
		zOffset = 1.0;
	} else if (newTile.direction == "DOWN") {
		zOffset = -1.0;
	} else if (newTile.direction == "LEFT") {
		xOffset = 1.0;
	} else if (newTile.direction == "RIGHT") {
		xOffset = -1.0;
	}


	newTile.position = glm::translate(newTile.position, glm::vec3(xOffset, 0.0f, zOffset));
	body.push_back(newTile);
};

unsigned int Snake::getSize() {
	return static_cast<unsigned int>(body.size());
};

float Snake::getSpeed() {
	return speed;
}

bool Snake::isColidingWithSnakeBody(glm::mat4 other, bool includeHead) {

	for (std::vector<Tile>::iterator it = body.begin() + (includeHead ? 0 : 3); it != body.end(); ++it) {
		if (checkCollision(other, it->position)) {
			//std::cout << glm::to_string(it->position[3]) << "\n";
			return true;
		}
	}
	return false;
}

int Snake::applyDirectionChange() {

	int turnCamera = 0;
	if (getCurrentDirection() != nextDirection) {

		if ((getCurrentDirection() == "UP" && nextDirection == "RIGHT") || (getCurrentDirection() == "RIGHT" && nextDirection == "DOWN") || (getCurrentDirection() == "DOWN" && nextDirection == "LEFT") || (getCurrentDirection() == "LEFT" && nextDirection == "UP")) {
			turnCamera = -1;
		} else {
			turnCamera = 1;
		}
		//turnCamera = 1;
		body.at(0).direction = nextDirection;
		body.at(0).prevTurn = body.at(0).position;

	}
	return turnCamera;
}

std::string Snake::getNextDirection() {
	return nextDirection;
}

//save last tile before moving, after moving, if apple was eaten, add that tile to teh end
int Snake::move(Apple *apple, float deltaTime) {
	bool shouldAddTile = false;
	bool shouldReset = false;

	int turnCamera = 0;


	/*std::cout << "turned: " << turnedPos[3].x << " " << turnedPos[3].y << " " << turnedPos[3].z << "\n";
	std::cout << "pos: " << body.at(1).position[3].x << " " << body.at(1).position[3].y << " " << body.at(1).position[3].z << "\n";*/

	for (std::vector<Tile>::reverse_iterator it = body.rbegin(); it != body.rend(); it++) {
		if (it->direction == "UP") {
			//it->y += 1.0f;
			it->position = glm::translate(it->position, glm::vec3(0.0f, 0.0f, -speed) * deltaTime);
		} else if (it->direction == "DOWN") {
			//it->y -= 1.0f;
			it->position = glm::translate(it->position, glm::vec3(0.0f, 0.0f, speed) * deltaTime);

		} else if (it->direction == "LEFT") {
			//it->x -= 1.0f;
			it->position = glm::translate(it->position, glm::vec3(-speed, 0.0f, 0.0f) * deltaTime);

		} else if (it->direction == "RIGHT") {
			//it->x += 1.0f;
			it->position = glm::translate(it->position, glm::vec3(speed, 0.0f, 0.0f) * deltaTime);

		}

		if (it + 1 != body.rend()) {
			//it->direction = it->direction;
			if (closeEnough(it->position, (it + 1)->prevTurn)) {
				it->direction = (it + 1)->direction;
				it->prevTurn = it->position;
				//std::cout << "pos: " << it->prevTurn[3].x << " " << it->prevTurn[3].y << " " << it->prevTurn[3].z << "\n";
				(it + 1)->prevTurn = glm::mat4(NULL);
			}
		} else {
			//CHECK COLLISION

			//std::cout<<"HALP: "<< glm::to_string(it->position[3])<<"\n";
			float x = it->position[3].x;
			float z = it->position[3].z;
			if (x < -14.0f || x > 14.0f || z > 11.0f || z < -10.0f) {
				shouldReset = true;
				turnCamera = 1;
			} else if (checkCollision(apple->getPosition(), it->position)) {
				shouldAddTile = true;
			} else if (isColidingWithSnakeBody(it->position)) {
				shouldReset = true;
				turnCamera = 1;
			}
		}
	}

	Tile lastTile = body.at(getSize() - 1);


	if (shouldAddTile) {
		apple->spawnApple(this);
		addTile(lastTile);
	}
	if (shouldReset) {
		reset("UP");
	}
	return turnCamera;
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


//bool Snake::findTile(Tile myTile) {
//	auto pred = [myTile](const Tile & otherTile) {
//		return otherTile.position == myTile.position;
//	};
//	return std::find_if(body.begin() + 1, body.end(), pred) != body.end();
//
//}

bool Snake::closeEnough(glm::mat4 tile1, glm::mat4 tile2) {

	float x = tile1[3].x;
	float x1 = tile2[3].x;


	float z = tile1[3].z;
	float z1 = tile2[3].z;
	float dist = pow((x - x1), 2) + pow((z - z1), 2);
	//std::cout << dist << "\n";

	return dist <= 0.001;

}

bool Snake::checkCollision(glm::mat4 tile1, glm::mat4 tile2) {

	float size = 0.5f;

	float x = tile1[3].x;
	float x1 = tile2[3].x;


	float z = tile1[3].z;
	float z1 = tile2[3].z;


	if (x + size < x1 - size || x - size > x1 + size) {
		return false;
	}

	if (z - size > z1 + size || z + size < z1 - size) {
		return false;
	}


	return true;
}
