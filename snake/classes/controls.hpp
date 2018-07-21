#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "snake.hpp"


void checkForKeyboardInput(GLFWwindow *window, Snake *snek);

void computeMVP(glm::mat4 *MVP, Snake *snek, GLFWwindow *window);
#endif // !CONTROLS_HPP
