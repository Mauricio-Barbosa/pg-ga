#pragma once

#include <vector>
#include <glm/vec3.hpp> // glm::vec3
using namespace std;

class Face {
private:
	std::vector<glm::vec3> m_verts; //= glm::vec3(0.f, 0.f, 0.f);
	std::vector<glm::vec3> m_color;
	std::vector<glm::vec3> m_norms;
	std::vector<glm::vec2> m_texts;

	std::vector<glm::vec3> m_full;
	std::vector<glm::vec3> aux2;

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

	void insertText(int x, int y) {
		glm::vec2 m_vec1 = glm::vec2(x, y);
		m_texts.insert(m_texts.end(), m_vec1);
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
		//return &m_color;
		
		for (int i = 0; i < m_texts.size(); i++) {
			glm::vec3* aux = getVert(m_texts[i].y);
			aux2.insert(aux2.end(), *aux);
		}
		return &aux2;
	}

	glm::vec2* getText(int n) {
		return &m_texts[n];
	}

	std::vector<glm::vec2>* getText() {
		return &m_texts;
	}
	
	std::vector<glm::vec3>* getFull() {
		for (int i = 0; i < m_texts.size(); i++) {
			glm::vec3* aux = getVert(m_texts[i].x);
			m_full.insert(m_full.end(), *aux);
			int temp = m_texts[i].x;
			cout << "Valor do m_texts[i].x: " << temp << endl;
		}
		return &m_full;
	}
	
};
