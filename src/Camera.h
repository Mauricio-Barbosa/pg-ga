#pragma once
#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:

	//cameraPos personalizado para que fique à esquerda, à cima
	//glm::vec3 cameraPos = glm::vec3(-2.0f, 2.0f, 10.0f);
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::mat4 view;
	

public:
	Camera(int SCR_WIDTH, int SCR_HEIGHT) {
		cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		cameraSpeed = 0.005f;
		this->SCR_WIDTH = SCR_WIDTH;
		this->SCR_HEIGHT = SCR_HEIGHT;
		lastX = SCR_WIDTH / 2.0f;
		lastY = SCR_HEIGHT / 2.0f;
	};
	
	float cameraSpeed; // adjust accordingly
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float fov = 45.0f;
	float lastX;
	float lastY;
	int SCR_WIDTH;
	int SCR_HEIGHT;

	glm::vec3 getCameraPos() {
		return this->cameraPos;
	}
	
	glm::vec3 getCameraFront() {
		return this->cameraFront;
	}

	glm::vec3 getCameraUp() {
		return this->cameraUp;
	}

	glm::mat4 getView() {
		return this->view;
	}

	float getCameraSpeed() {
		return this->cameraSpeed;
	}

	void setCameraPos(glm::vec3 cameraPos) {
		this->cameraPos = cameraPos;
	}

	void setCameraFront(glm::vec3 cameraFront) {
		this->cameraFront = cameraFront;
	}

	void setCameraUp(glm::vec3 cameraUp) {
		this->cameraUp = cameraUp;
	}

	void setView(glm::mat4 view) {
		this->view = view;
	}

};