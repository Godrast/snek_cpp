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

};

class Snake {

	std::vector<Tile> body;
	std::string nextDirection;
	int size = 5;

public:
	Snake(std::string direction);
	std::vector<Tile> getBody();
	unsigned int getSize();
	void addTile(float x, float y, std::string dir);
	void addTile(Tile newTile);
	void move(Apple *apple);
	void setDirection(std::string dir);
	std::string getCurrentDirection();
	void reset(std::string direction);
	bool findTile(Tile myTile);


};


#endif // !SNAKE_HPP