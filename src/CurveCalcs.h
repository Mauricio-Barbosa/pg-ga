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
#include <math.h>       /* atan */

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
		std::vector<glm::vec3> InternalPoints;
		float w = 0;
		float h = 0;
		float alpha = 0;
		float theta = 0;
		float m = 0.05f; // Largura da curva
		float Cx = 0;
		float Cy = 0;
		float Cz = 0;
		float Ax = 0;
		float Ay = 0;
		int sizePoints = controlPointsIn.size();
		float degrees = atan(1) * 4; //"atan(1) * 4" � equivalente a 90 graus
		for (int i = 0; i < sizePoints; i += 1) {
			Ax = controlPointsIn.at((i) % sizePoints).x;
			Ay = controlPointsIn.at((i) % sizePoints).y;
			w = controlPointsIn.at((i + 1) % sizePoints).x - controlPointsIn.at((i) % sizePoints).x;
			h = controlPointsIn.at((i + 1) % sizePoints).y - controlPointsIn.at((i) % sizePoints).y;
			theta = atan(h / m);
			if (w < 0) {
				alpha = theta - degrees;
			}
			else
			{
				alpha = theta + degrees;
			}
			Cx = cos(alpha) * m + Ax;
			Cy = cos(alpha) * m + Ay;
			Cz = controlPointsIn.at((i) % sizePoints).z;
			InternalPoints.push_back(glm::vec3(Cx, Cy, Cz));
		}
		std::vector<glm::vec3> InternalMinorPoints;
		InternalMinorPoints = this->generateCurve(InternalPoints);
		return InternalMinorPoints;
	}

	std::vector<glm::vec3> generateExternalCurve(std::vector<glm::vec3> controlPointsIn) {
		std::vector<glm::vec3> ExternalPoints;
		float w = 0;
		float h = 0;
		float alpha = 0;
		float theta = 0;
		float m = -0.05f; // Largura da curva
		float Cx = 0;
		float Cy = 0;
		float Cz = 0;
		float Ax = 0;
		float Ay = 0;
		int sizePoints = controlPointsIn.size();
		float degrees = atan(1) * 4; //"atan(1) * 4" � equivalente a 90 graus
		for (int i = 0; i < sizePoints; i += 1) {

			Ax = controlPointsIn.at((i) % sizePoints).x;
			Ay = controlPointsIn.at((i) % sizePoints).y;
			w = controlPointsIn.at((i + 1) % sizePoints).x - controlPointsIn.at((i) % sizePoints).x;
			h = controlPointsIn.at((i + 1) % sizePoints).y - controlPointsIn.at((i) % sizePoints).y;
			theta = atan(h / m);
			if (w < 0) {
				alpha = theta - degrees;
			}
			else
			{
				alpha = theta + degrees;
			}
			Cx = cos(alpha) * m + Ax;
			Cy = cos(alpha) * m + Ay;
			Cz = controlPointsIn.at((i) % sizePoints).z;
			ExternalPoints.push_back(glm::vec3(Cx, Cy, Cz));
		}
		std::vector<glm::vec3> ExternalMinorPoints;
		ExternalMinorPoints = this->generateCurve(ExternalPoints);
		return ExternalMinorPoints;
	}

};