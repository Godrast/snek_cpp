#include <GLFW/glfw3.h>

#include "controls.hpp"


double gameSpeed = 1.0 / 20.0;
float turnAmount = 0.0f;


void checkForKeyboardInput(GLFWwindow *window, Snake *snek, bool * canPressLeft, bool * canPressRight) {

	/*if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (snek->getCurrentDirection() != "DOWN") {
			snek->setDirection("UP");
		}
	} else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (snek->getCurrentDirection() != "UP") {
			snek->setDirection("DOWN");
		}
	} else*/

	std::string currentDir = snek->getCurrentDirection();

	if (*canPressLeft == true && (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)) {
		if (currentDir == "UP") {
			snek->setDirection("LEFT");
			//- 3.14/2
		} else if (currentDir == "LEFT") {
			snek->setDirection("DOWN");
			// 0
		} else if (currentDir == "DOWN") {
			snek->setDirection("RIGHT");
			//3.14/2
		} else if (currentDir == "RIGHT") {
			snek->setDirection("UP");
			//3.14
		}
		*canPressLeft = false;
	} else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
		*canPressLeft = true;
	}

	if (*canPressRight == true && (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)) {
		if (currentDir == "UP") {
			snek->setDirection("RIGHT");
			//3.14/2
		} else if (currentDir == "RIGHT") {
			snek->setDirection("DOWN");
			//0
		} else if (currentDir == "DOWN") {
			snek->setDirection("LEFT");
			//-3.14/2
		} else if (currentDir == "LEFT") {
			snek->setDirection("UP");
			//3.14
		}

		*canPressRight = false;
	} else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
		*canPressRight = true;
	}

}

double horizontalAngle = 3.14f;
double verticalAngle = -0.6f;
glm::vec3 lookDirection(
	cos(verticalAngle) * sin(horizontalAngle),
	sin(verticalAngle),
	cos(verticalAngle) * cos(horizontalAngle)
);




void computeMVP(glm::mat4 *MVP, Snake *snek, double timeAmount) {
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(100.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	std::vector<Tile> snakeBody = snek->getBody();
	glm::vec4 position = snakeBody.at(1).position[3];
	float x = position.x;
	float y = position.y;
	float z = position.z;

	//std::string direction = snek->getCurrentDirection();


	if (turnAmount != 0) {

		double turnRate = roundf(((timeAmount / gameSpeed) * turnAmount) * 1000.0f) / 1000.0f;
		turnAmount = roundf(turnAmount * 1000.0f - turnRate * 1000.0f) / 1000.0f;
		horizontalAngle += turnRate;

		lookDirection = glm::vec3(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);
	}



	/*
	glm::vec3 lookDirection = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	*/



	float offsetX = 0.0f;
	float offsetY = 5.0f;



	//if (direction == "UP") {
	//	lookDirection = glm::vec3(
	//		cos(-0.6f) * sin(3.14f),
	//		sin(-0.6f),
	//		cos(-0.6f) * cos(3.14f)
	//	);
	//} else if (direction == "DOWN") {
	//	lookDirection = glm::vec3(
	//		cos(-0.6f) * sin(0.0f),
	//		sin(-0.6f),
	//		cos(-0.6f) * cos(0.0f)
	//	);
	//} else if (direction == "LEFT") {
	//	lookDirection = glm::vec3(
	//		cos(-0.6f) * sin(-3.14f / 2.0f),
	//		sin(-0.6f),
	//		cos(-0.6f) * cos(-3.14f / 2.0f)
	//	);
	//} else if (direction == "RIGHT") {
	//	lookDirection = glm::vec3(
	//		cos(-0.6f) * sin(3.14f / 2.0f),
	//		sin(-0.6f),
	//		cos(-0.6f) * cos(3.14f / 2.0f)
	//	);
	//}


	//lookDirection = glm::vec3(
	//	cos(verticalAngle) * sin(horizontalAngle),
	//	sin(verticalAngle),
	//	cos(verticalAngle) * cos(horizontalAngle)
	//);


	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(x, offsetY, z), // Camera is at (4,3,3), in World Space
		glm::vec3(x, offsetY, z) + lookDirection,//lookDirection, // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	*MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
}

void turnCamera(int sign) {

	turnAmount += 3.14f / 2.0f * sign;

}

void resetCamera() {
	horizontalAngle = 3.14f;
	turnAmount = 0.0f;
	lookDirection = glm::vec3 (
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

}