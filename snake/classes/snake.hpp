#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <cstdio>
#include <string>
#include <iterator>
#include <algorithm>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "apple.hpp"
class Apple;

struct Tile {
	glm::mat4 position;
	std::string direction;
	glm::mat4 prevTurn = glm::mat4(NULL);
};

class Snake {

	std::vector<Tile> body;
	std::string nextDirection;
	int size = 5;
	double speed = 6;
	int turnCamera = 0;

public:
	Snake(std::string direction);
	std::vector<Tile> getBody();
	int move(Apple *apple, float deltaTime);
	std::string getCurrentDirection();
	void setDirection(std::string dir);
	float getSpeed();
	bool isColidingWithSnakeBody(glm::mat4 other, bool includeHead = false);
	int applyDirectionChange();
	std::string getNextDirection();
private:
	unsigned int getSize();
	void addTile(float x, float y, std::string dir);
	void addTile(Tile newTile);
	void reset(std::string direction);
	//bool findTile(Tile myTile);
	bool closeEnough(glm::mat4 tile1, glm::mat4 tile2);

	bool checkCollision(glm::mat4 tile1, glm::mat4 tile2);


};


#endif // !SNAKE_HPP