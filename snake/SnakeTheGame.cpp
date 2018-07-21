// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iterator>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <common/shader.hpp>
#include "classes/snake.hpp"
#include "classes/controls.hpp"
#include "classes/apple.hpp"
#include "classes/fragmentShaders.hpp"
#include "classes/vertexShaders.hpp"





//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


void spawnWall(glm::mat4 *MVP, GLuint * ProgramID, GLuint * MatrixID, unsigned int size, float left, float right, float top, float bottom);

int main(void) {

	float gameSpeed = float(1) / float(5);

	VertexShaders vertexShaders = VertexShaders();
	FragmentShaders fragmentShaders = FragmentShaders();

	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Snek the game", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);



	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);


	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	//GLuint programSnake = LoadShadersExternal("vertex_shader_snake.vertexshader", "fragment_shader_snake.fragmentshader");
	//GLuint programApple = LoadShadersExternal("vertex_shader_apple.vertexshader", "fragment_shader_apple.fragmentshader");


	GLuint programSnake = LoadShaders(vertexShaders.getGeneral3DShader(), fragmentShaders.getSnakeShader());
	GLuint programApple = LoadShaders(vertexShaders.getGeneral3DShader(), fragmentShaders.getAppleShader());
	GLuint programWall = LoadShaders(vertexShaders.getGeneral3DShader(), fragmentShaders.getWallShader());






	//SNEK
	Snake snake = Snake("UP");
	//
	//
	//
	//
	//snake.setDirection("LEFT");

	Apple apple = Apple();
	apple.spawnApple(&snake);




	GLuint MatrixID = glGetUniformLocation(programSnake, "MVP");
	/*
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, -3, 25), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0.5, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices

	*/
	glm::mat4 MVP;// = Projection * View * Model; // Remember, matrix multiplication is the other way around






	static const GLfloat vertices_square[] = {
		-0.5f, 0.5f, 0.5f, //front top left
		-0.5f, -0.5f, 0.5f, //front bottom left
		0.5f, -0.5f, 0.5f, //front bottom right
		0.5f, 0.5f, 0.5f, //front top right

		-0.5f, 0.5f, -0.5f, //back top left
		-0.5f, -0.5f, -0.5f, //back bottom left
		0.5f, -0.5f, -0.5f, //back bottom right
		0.5f, 0.5f, -0.5f //back top right

	};

	GLuint squareVertexBuffer;
	glGenBuffers(1, &squareVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, squareVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_square), vertices_square, GL_STATIC_DRAW);


	static const glm::uint indecies_square[] = {
		0, 1, 2,
		0, 3, 2,
		0, 1, 5,
		0, 4, 5,
		0, 4, 3,
		0, 4, 7,
		6, 7, 3,
		6, 2, 3,
		6, 5, 1,
		6, 2, 1,
		6, 5, 4,
		6, 7, 4
	};

	GLuint indeciesSquareBuffer;
	glGenBuffers(1, &indeciesSquareBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indeciesSquareBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies_square), indecies_square, GL_STATIC_DRAW);

	double timeStamp = glfwGetTime();
	do {
		checkForKeyboardInput(window, &snake);

		double currentTimeStamp = glfwGetTime();
		if (currentTimeStamp - timeStamp > gameSpeed) {
			timeStamp = currentTimeStamp;
			snake.move(&apple);
			//printf("Snake head y:%f\tx:%f\n", snake.getBody().at(0).y, snake.getBody().at(0).x);
		}
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		computeMVP(&MVP, &snake, window);

		// Use our shader
		glUseProgram(programSnake);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, squareVertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		std::vector<Tile> snakeBody = snake.getBody();
		for (std::vector<Tile>::iterator it = snakeBody.begin(); it != snakeBody.end(); it++) {
			glm::mat4 tempMVP = MVP * it->position;

			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tempMVP[0][0]);

			// Draw the triangle !
			//glDrawArrays(GL_LINES, 0, 3); // 3 indices starting at 0 -> 1 triangle
			glDrawElements(GL_TRIANGLES, sizeof(indecies_square) / sizeof(indecies_square[0]), GL_UNSIGNED_INT, 0);
		}




		// Use our shader
		glUseProgram(programApple);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glm::mat4 transformApple = glm::translate(glm::mat4(), glm::vec3(apple.getX(), 0.0f, apple.getY()));
		glm::mat4 MVPApple = MVP * transformApple;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPApple[0][0]);

		// Draw the triangle !
		//glDrawArrays(GL_LINES, 0, 3); // 3 indices starting at 0 -> 1 triangle
		glDrawElements(GL_TRIANGLES, sizeof(indecies_square) / sizeof(indecies_square[0]), GL_UNSIGNED_INT, 0);

		spawnWall(&MVP, &programWall,&MatrixID, sizeof(indecies_square) / sizeof(indecies_square[0]), -14.0f, 14.0f, 10.0f, -9.0f);

		glDisableVertexAttribArray(0);


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO
	glDeleteBuffers(1, &squareVertexBuffer);
	glDeleteBuffers(1, &indeciesSquareBuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programSnake);
	glDeleteProgram(programApple);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}



void spawnWall(glm::mat4 * MVP, GLuint * ProgramID, GLuint * MatrixID, unsigned int size, float left, float right, float top, float bottom) {
	glUseProgram(*ProgramID);
	for (float x = left - 1.0f; x <= right + 1.0f; x++) {
		glm::mat4 transformMatrix = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, top + 2.0f));
		glm::mat4 tempMVP = *MVP * transformMatrix;

		glUniformMatrix4fv(*MatrixID, 1, GL_FALSE, &tempMVP[0][0]);

		glDrawElements(GL_LINES, size, GL_UNSIGNED_INT, 0);

		transformMatrix = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, bottom - 2.0f));
		tempMVP = *MVP * transformMatrix;

		glUniformMatrix4fv(*MatrixID, 1, GL_FALSE, &tempMVP[0][0]);

		glDrawElements(GL_LINES, size, GL_UNSIGNED_INT, 0);

	}
	for (float y = bottom - 1.0f; y <= top + 1.0f; y++) {
		glm::mat4 transformMatrix = glm::translate(glm::mat4(), glm::vec3(left -1.0f , 0.0f, y));
		glm::mat4 tempMVP = *MVP * transformMatrix;

		glUniformMatrix4fv(*MatrixID, 1, GL_FALSE, &tempMVP[0][0]);

		glDrawElements(GL_LINES, size, GL_UNSIGNED_INT, 0);


		transformMatrix = glm::translate(glm::mat4(), glm::vec3(right + 1.0f, 0.0f, y));
		tempMVP = *MVP * transformMatrix;

		glUniformMatrix4fv(*MatrixID, 1, GL_FALSE, &tempMVP[0][0]);

		glDrawElements(GL_LINES, size, GL_UNSIGNED_INT, 0);

	}
}