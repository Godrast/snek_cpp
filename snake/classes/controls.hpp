#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "snake.hpp"


void checkForKeyboardInput(GLFWwindow *window, Snake *snek, bool * canPressLeft, bool * canPressRight);

void computeMVP(glm::mat4 *MVP, Snake *snek, double timeAmount);

void turnCamera(int sign);

void resetCamera();
#endif // !CONTROLS_HPP
