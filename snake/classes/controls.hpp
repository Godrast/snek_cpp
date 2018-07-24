#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "snake.hpp"


void checkForKeyboardInput(GLFWwindow *window, Snake *snek, bool * canPressLeft, bool * canPressRight, int * lastPressedLeft, int * lastPressedRight);

void computeMVP(glm::mat4 *MVP, Snake *snek);
#endif // !CONTROLS_HPP
