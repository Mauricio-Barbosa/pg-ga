#pragma once

#include <vector>
#include <glm/vec3.hpp> // glm::vec3


class Face {
private:
	std::vector<glm::vec3> m_verts; //= glm::vec3(0.f, 0.f, 0.f);
	std::vector<glm::vec3> m_color;
	std::vector<glm::vec3> m_norms;
	std::vector<glm::vec2> m_texts;


public:
	Face() {
		//Abaixo codigo que cria triangulo de exemplo
		
		this->insertVert(0.f, 0.5f, 0.f);
		this->insertVert(0.5f, -0.5f, 0.f);
		this->insertVert(-0.5f, -0.5f, 0.);
		
	}

	void insertVert(float x, float y, float z) {
		glm::vec3 m_vec1 = glm::vec3(x, y, z);
		m_verts.insert(m_verts.begin(), m_vec1);
	}

	void insertColor(float x, float y, float z) {
		glm::vec3 m_vec1 = glm::vec3(x, y, z);
		m_color.insert(m_color.begin(), m_vec1);
	}

	glm::vec3* getVert(int n) {
		return &m_verts[n];
	}

	std::vector<glm::vec3>* getVector() {
		return &m_verts;
	}


	glm::vec3* getColor(int n) {
		return &m_color[n];
	}

	std::vector<glm::vec3>* getColor() {
		return &m_color;
	}
};
