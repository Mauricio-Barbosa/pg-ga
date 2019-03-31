#pragma once

#include <vector>
#include <glm/vec3.hpp> // glm::vec3

class Face {
private:
	std::vector<glm::vec3> m_verts; //= glm::vec3(0.f, 0.f, 0.f);
	std::vector<glm::vec3> m_norms;
	std::vector<glm::vec2> m_texts;
	//glm::vec3 m_norms;
	//glm::vec2 m_texts;

public:
	Face() {}

	/*
	Face(float a, float b, float c) {
		m_verts[0] = a;
		m_verts[1] = b;
		m_verts[2] = c;
	}
	*/
	/*
	glm::vec3* getVert() {
		//float *i = new float[]{ m_verts.x, m_verts.y, m_verts.z };
		return &m_verts;
	}
	*/

	//float* getVert() {
	//	return &m_verts[0];
	//}

	glm::vec3* getVert(int n) {
		return &m_verts[n];
	}

	std::vector<glm::vec3>* getVector() {
		return &m_verts;
	}
};
