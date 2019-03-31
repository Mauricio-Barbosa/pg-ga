#pragma once

#include <vector>
#include <glm/vec3.hpp> // glm::vec3

class Face {
private:
	glm::vec3 m_verts = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_norms;
	glm::vec2 m_texts;

public:
	Face() {}

	Face(float a, float b, float c) {
		m_verts[0] = a;
		m_verts[1] = b;
		m_verts[2] = c;
	}
	
	float *getVert() {
		float *i = new float[]{ m_verts.x, m_verts.y, m_verts.z };
		return i;
	}
};
