#pragma once

#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
//using namespace std;


class Callback {
	
private:
	
	int mode;
	bool firstMouse = true;
	Camera* camera;
	
	
public: 
	Callback(int mode, Camera* camera) {
		this->mode = mode;
		this->camera = camera;
	}
	
	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{

		if (firstMouse)
		{
			//lastX = xpos;
			//lastY = ypos;
			camera->lastX = xpos;
			camera->lastY = ypos;
			firstMouse = false;
		}

		//float xoffset = xpos - lastX;
		//float yoffset = lastY - ypos;
		float xoffset = xpos - camera->lastX;
		float yoffset = camera->lastY - ypos;
		//lastX = xpos;
		//lastY = ypos;
		camera->lastX = xpos;
		camera->lastY = ypos;

		float sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		/*yaw += xoffset;
		pitch += yoffset;*/
		camera->yaw += xoffset;
		camera->pitch += yoffset;

		/*if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;*/
		if (camera->pitch > 89.0f)
			camera->pitch = 89.0f;
		if (camera->pitch < -89.0f)
			camera->pitch = -89.0f;

		//if (glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glm::vec3 front;
		/*front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		camera->setCameraFront(glm::normalize(front));*/
		front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
		front.y = sin(glm::radians(camera->pitch));
		front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
		camera->setCameraFront(glm::normalize(front));
		//cameraFront = glm::normalize(front);
	//}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		/*if (fov >= 1.0f && fov <= 45.0f)
			fov -= yoffset;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 45.0f)
			fov = 45.0f;*/
		if (camera->fov >= 1.0f && camera->fov <= 45.0f)
			camera->fov -= yoffset;
		if (camera->fov <= 1.0f)
			camera->fov = 1.0f;
		if (camera->fov >= 45.0f)
			camera->fov = 45.0f;
	}

};