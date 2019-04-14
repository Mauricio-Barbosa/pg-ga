#pragma once

#include <vector>
#include <glm/vec3.hpp> // glm::vec3
using namespace std;

class Face {
private:
	//std::vector<glm::vec3> m_verts; //= glm::vec3(0.f, 0.f, 0.f);
	std::vector<int> vertsPosition;
	std::vector<int> textsPosition;
	std::vector<int> normsPosition;
	

public:
	//Face() {}
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

};
