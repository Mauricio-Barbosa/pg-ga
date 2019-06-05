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
	
	int wasKeyPressed = 0;
	
public: 

	std::vector<glm::vec3> click_verts;

	Callback(int mode, Camera* camera) {
		this->mode = mode;
		this->camera = camera;
	}
	
	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		if (mode == 0) {
			this->callbackReader(window, xpos, ypos);
		}
		else if (mode == 1) {
			this->callBackEditor(window, xpos, ypos);
		}
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			cout << "Cursor Position at (" << xpos << " : " << ypos << endl;
			this->click_verts.push_back(glm::vec3(xpos, ypos, 0));
		}
	}

	void callBackEditor(GLFWwindow* window, double xpos, double ypos) {
		
	}

	void callbackReader(GLFWwindow* window, double xpos, double ypos) {
		if (firstMouse)
		{
			camera->lastX = xpos;
			camera->lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - camera->lastX;
		float yoffset = camera->lastY - ypos;
		camera->lastX = xpos;
		camera->lastY = ypos;
		float sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		camera->yaw += xoffset;
		camera->pitch += yoffset;
		if (camera->pitch > 89.0f)
			camera->pitch = 89.0f;
		if (camera->pitch < -89.0f)
			camera->pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
		front.y = sin(glm::radians(camera->pitch));
		front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
		camera->setCameraFront(glm::normalize(front));

	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		if (camera->fov >= 1.0f && camera->fov <= 45.0f)
			camera->fov -= yoffset;
		if (camera->fov <= 1.0f)
			camera->fov = 1.0f;
		if (camera->fov >= 45.0f)
			camera->fov = 45.0f;
	}

};