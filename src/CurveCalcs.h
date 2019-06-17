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
#include <stdlib.h>     /* abs */

class CurveCalcs {

private:


public:

	CurveCalcs() {};

	bool checkIfPointsAreClose(glm::vec3 firstPoint, glm::vec3 lastPoint) {
		bool areClose = false;
		if (abs(firstPoint.x - lastPoint.x) < 100 && abs(firstPoint.y - lastPoint.y) < 100)
			areClose = true;

		return areClose;
	}

	std::vector<glm::vec3> generateCurve(std::vector<glm::vec3> controlPointsIn) {
		std::vector<glm::vec3> curve;
		std::vector<glm::vec3> controlPoints = controlPointsIn;

		bool fecharSomenteQuandoPerto = false;


		float inc = 0.01;
		for (int i = 0; i < controlPoints.size(); i++) {
			float x0 = controlPoints.at(i).x;
			float y0 = controlPoints.at(i).y;
			float z0 = controlPoints.at(i).z;
			for (float t = 0; t <= 1; t += inc) {
				float x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints.at(i % controlPoints.size()).x +
					(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints.at((i+1) % controlPoints.size()).x +
					(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints.at((i + 2) % controlPoints.size()).x +
					(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints.at((i + 3) % controlPoints.size()).x) / 6);
				float y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints.at(i % controlPoints.size()).y +
					(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints.at((i + 1) % controlPoints.size()).y +
					(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints.at((i + 2) % controlPoints.size()).y +
					(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints.at((i + 3) % controlPoints.size()).y) / 6);
				float z = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints.at(i % controlPoints.size()).z +
					(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints.at((i + 1) % controlPoints.size()).z +
					(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints.at((i + 2) % controlPoints.size()).z +
					(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints.at((i + 3) % controlPoints.size()).z) / 6);
				x0 = x;
				y0 = y;
				curve.push_back(glm::vec3(x, y, z));
			}
		}

		return curve;
	}

	std::vector<glm::vec3> generateInternalCurve(std::vector<glm::vec3> controlPointsIn) {
		std::vector<glm::vec3> curve;
		std::vector<glm::vec3> controlPoints = controlPointsIn;


		float inc = 0.01;
		for (int i = 0; i < controlPoints.size(); i++) {
			float x0 = controlPoints.at(i).x;
			float y0 = controlPoints.at(i).y;
			float z0 = controlPoints.at(i).z;
			for (float t = 0; t <= 1; t += inc) {
				float x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints.at(i % controlPoints.size()).x +
					(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints.at((i + 1) % controlPoints.size()).x +
					(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints.at((i + 2) % controlPoints.size()).x +
					(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints.at((i + 3) % controlPoints.size()).x) / 6);
				float y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints.at(i % controlPoints.size()).y +
					(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints.at((i + 1) % controlPoints.size()).y +
					(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints.at((i + 2) % controlPoints.size()).y +
					(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints.at((i + 3) % controlPoints.size()).y) / 6);
				float z = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints.at(i % controlPoints.size()).z +
					(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints.at((i + 1) % controlPoints.size()).z +
					(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints.at((i + 2) % controlPoints.size()).z +
					(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints.at((i + 3) % controlPoints.size()).z) / 6);
				x0 = x;
				y0 = y;
				curve.push_back(glm::vec3(x, y, z));
			}
		}

		return curve;
	}

};