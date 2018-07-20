#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <cstdio>
#include <string>
#include <iterator>
#include "apple.hpp"

class Apple;

struct tile {
	float x;
	float y;
	std::string direction;
};

class Snake {

	std::vector<tile> body;
	std::string nextDirection;
	int size = 5;

public:
	Snake(std::string direction);
	std::vector<tile> getBody();
	unsigned int getSize();
	void addTile(float x, float y, std::string dir);
	void addTile(tile newTile);
	void move(Apple *apple);
	void setDirection(std::string dir);
	std::string getCurrentDirection();
	void reset(std::string direction);

};


#endif SNAKE_HPP