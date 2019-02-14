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
	tempTile.position = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z));
	tempTile.direction = dir;
	body.push_back(tempTile);
};

void Snake::addTile(Tile *prevTile) {
	float xOffset = 0.0f;
	float zOffset = 0.0f;
	if (prevTile->direction == "UP") {
		zOffset = 1.0;
	} else if (prevTile->direction == "DOWN") {
		zOffset = -1.0;
	} else if (prevTile->direction == "LEFT") {
		xOffset = 1.0;
	} else if (prevTile->direction == "RIGHT") {
		xOffset = -1.0;
	}

	Tile newTile;
	newTile.direction = prevTile->direction;
	newTile.position = glm::translate(prevTile->position, glm::vec3(xOffset, 0.0f, zOffset));
	newTile.prevTurn = glm::mat4(NULL);
	body.push_back(newTile);

};

unsigned int Snake::getSize() {
	//std::cout << "\n" << body.size() << "\n";
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
		body.at(0).timeToTurn = 1 / speed;

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




	if (body.at(0).direction == "UP") {
		//it->y += 1.0f;
		body.at(0).position = glm::translate(body.at(0).position, glm::vec3(0.0f, 0.0f, -speed) * deltaTime);
	} else if (body.at(0).direction == "DOWN") {
		//it->y -= 1.0f;
		body.at(0).position = glm::translate(body.at(0).position, glm::vec3(0.0f, 0.0f, speed) * deltaTime);

	} else if (body.at(0).direction == "LEFT") {
		//it->x -= 1.0f;
		body.at(0).position = glm::translate(body.at(0).position, glm::vec3(-speed, 0.0f, 0.0f) * deltaTime);

	} else if (body.at(0).direction == "RIGHT") {
		//it->x += 1.0f;
		body.at(0).position = glm::translate(body.at(0).position, glm::vec3(speed, 0.0f, 0.0f) * deltaTime);

	}





	for (std::vector<Tile>::reverse_iterator it = body.rbegin(); it != body.rend() - 1; it++) {
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


		//		if (it + 1 != body.rend()) {
		//it->direction = it->direction;
		if ((it + 1)->timeToTurn != NULL) {
			(it + 1)->timeToTurn -= deltaTime;
			//std::cout << "time to turn: " << (it + 1)->timeToTurn << "\n";
		}

		if ((it + 1)->prevTurn != glm::mat4(NULL) && (it + 1)->timeToTurn < 0.005) {
			it->direction = (it + 1)->direction;
			it->position = (it + 1)->prevTurn;
			if (it != body.rbegin()) {
				it->prevTurn = (it + 0)->position;
				it->timeToTurn = 1 / speed;
			}
			//it->position = (it + 1)->prevTurn;
			//std::cout << "pos: " << it->prevTurn[3].x << " " << it->prevTurn[3].y << " " << it->prevTurn[3].z << "\n";
			(it + 1)->prevTurn = glm::mat4(NULL);
			(it + 1)->timeToTurn = NULL;
		}
		//		}


	}

	//CHECK COLLISION

//std::cout<<"HALP: "<< glm::to_string(it->position[3])<<"\n";
	float x = body.at(0).position[3].x;
	float z = body.at(0).position[3].z;
	if (x < -14.0f || x > 14.0f || z > 11.0f || z < -10.0f) {
		shouldReset = true;
		turnCamera = 1;
	} else if (checkCollision(apple->getPosition(), body.at(0).position)) {
		shouldAddTile = true;
	} else if (isColidingWithSnakeBody(body.at(0).position)) {
		shouldReset = true;
		turnCamera = 1;
	}



	if (shouldAddTile) {
		Tile *lastTile = &body.at(getSize() - 1);
		addTile(lastTile);

		apple->spawnApple(this);
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

//bool Snake::closeEnough(glm::mat4 tile1, glm::mat4 tile2) {
//
//	double x = tile1[3].x;
//	double x1 = tile2[3].x;
//
//
//	double z = tile1[3].z;
//	double z1 = tile2[3].z;
//	double dist = pow((x - x1), 2) + pow((z - z1), 2);
//
//	//std::cout << x << " " << x1 << " " << z << " " << z1 << "\n";
//	//std::cout << dist << "\n";
//
//
//
//	return dist <= 0.001;
//
//}

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
