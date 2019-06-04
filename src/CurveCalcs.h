#pragma once

#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

class CurveCalcs {

private:


public:

	CurveCalcs() {};

	std::vector<glm::vec3> generateCurve(std::vector<glm::vec3> controlPoints) {
		std::vector<glm::vec3> curve;
		float inc = 0.01;
		for (int i = 0; i < controlPoints.size() -4; i++) {
			float x0 = controlPoints.at(i).x;
			float y0 = controlPoints.at(i).y;
			for (float t = 0; t <= 1; t += inc) {
				float x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints.at(i).x +
					(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints.at(i+1).x +
					(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints.at(i + 2).x +
					(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints.at(i + 3).x) / 6);
				float y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints.at(i).y +
					(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints.at(i + 1).y +
					(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints.at(i + 2).y +
					(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints.at(i + 3).y) / 6);
				//plot(x0, y0, x, y);
				x0 = x;
				y0 = y;
				curve.push_back(glm::vec3(x, y, 0));
			}
		}
		return curve;
	}

};