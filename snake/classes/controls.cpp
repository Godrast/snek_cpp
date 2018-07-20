
#include <GLFW/glfw3.h>
#include "controls.hpp"

void checkForKeyboardInput(GLFWwindow *window, Snake *snek) {

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (snek->getCurrentDirection() != "DOWN") {
			snek->setDirection("UP");
		}
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (snek->getCurrentDirection() != "UP") {
			snek->setDirection("DOWN");
		}
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (snek->getCurrentDirection() != "RIGHT") {
			snek->setDirection("LEFT");
		}
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (snek->getCurrentDirection() != "LEFT") {
			snek->setDirection("RIGHT");
		}
	}
}