#pragma once

#include <vector>
#include <glm/vec3.hpp> // glm::vec3
using namespace std;

class Face {
private:
	std::vector<int> vertsPosition;
	std::vector<int> textsPosition;
	std::vector<int> normsPosition;
	

public:
	Face(std::vector<int> vertsPosition, std::vector<int> textsPosition, std::vector<int> normsPosition) {
		this->vertsPosition = vertsPosition;
		this->textsPosition = textsPosition;
		this->normsPosition = normsPosition;
	}

	glm::vec3 getVertVec3() {
		glm::vec3 vec;
		vec.x = this->vertsPosition.at(0);
		vec.y = this->vertsPosition.at(1);
		vec.z = this->vertsPosition.at(2);
		return vec;
	}

	glm::vec3 getNormVec3() {
		glm::vec3 norm;
		norm.x = this->normsPosition.at(0);
		norm.y = this->normsPosition.at(1);
		norm.z = this->normsPosition.at(2);
		return norm;
	}

	glm::vec3 getTextVec3() {
		glm::vec3 text;
		text.x = this->textsPosition.at(0);
		text.y = this->textsPosition.at(1);
		text.z = this->textsPosition.at(2);
		return text;
	}

};
