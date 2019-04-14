#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Group.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Mesh {
private:
	std::vector<Group*> m_vec;
	std::vector<glm::vec3> m_verts;
	std::vector<glm::vec3> m_norms;
	std::vector<glm::vec2> m_texts;
	std::vector<glm::vec3> m_color;
	std::vector<glm::vec3> m_full;
	//aux2 é utilizado para armazenar temporariament o vec3 de float montado com base nas faces
	//quando o método getFull é chamado
	std::vector<glm::vec3> aux2;
	Group* g;

public:
	Mesh() {
		g = new Group;
		m_vec.insert(m_vec.begin(), g);
		
	}

	/*
	void insertVert(float x, float y, float z) {
	glm::vec3 m_vec1 = glm::vec3(x, y, z);
	m_verts.insert(m_verts.begin(), m_vec1);
	}
	*/
	void insertVert(float x, float y, float z) {
		glm::vec3 m_vec1 = glm::vec3(x, y, z);
		m_verts.push_back(m_vec1);
	}

	/*
	void insertColor(float x, float y, float z) {
	glm::vec3 m_vec1 = glm::vec3(x, y, z);
	m_color.insert(m_color.begin(), m_vec1);
	}
	*/
	void insertColor(float x, float y, float z) {
		glm::vec3 m_vec1 = glm::vec3(x, y, z);
		m_color.push_back(m_vec1);
	}

	/*
	void insertText(int x, int y) {
	glm::vec2 m_vec1 = glm::vec2(x, y);
	m_texts.insert(m_texts.end(), m_vec1);
	}
	*/
	void insertText(int x, int y) {
		glm::vec2 m_vec1 = glm::vec2(x, y);
		m_texts.push_back(m_vec1);
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
	/*
	std::vector<glm::vec3>* getColor() {
		for (int i = 0; i < m_texts.size(); i++) {
			glm::vec3* aux = getVert(m_texts[i].y);
			aux2.insert(aux2.end(), *aux);
		}
		return &aux2;
	}
	*/
	std::vector<glm::vec3>* getColor() {
		for (int i = 0; i < m_texts.size(); i++) {
			glm::vec3* aux = getVert(m_texts[i].y);
			aux2.push_back(*aux);
		}
		return &aux2;
	}

	glm::vec2* getText(int n) {
		return &m_texts[n];
	}

	std::vector<glm::vec2>* getText() {
		return &m_texts;
	}

	/*
	std::vector<glm::vec3>* getFull() {
		for (int i = 0; i < m_texts.size(); i++) {
			glm::vec3* aux = getVert(m_texts[i].x);
			m_full.insert(m_full.end(), *aux);
			int temp = m_texts[i].x;
			cout << "Valor do m_texts[i].x: " << temp << endl;
		}
		return &m_full;
	}
	*/
	std::vector<glm::vec3>* getFull() {
		for (int i = 0; i < m_texts.size(); i++) {
			glm::vec3* aux = getVert(m_texts[i].x);
			m_full.push_back(*aux);
			int temp = m_texts[i].x;
			//cout << "Valor do m_texts[i].x: " << temp << endl;
		}
		return &m_full;
	}
	
	
	Group* getN(int n) {
		return m_vec[n];
	}



	
	Mesh *read(std::string filename) {

		cout << "Sheguei aqui1" << endl;
		Mesh *mesh = new Mesh;
		cout << "Sheguei aqui2" << endl;
		std::ifstream arq("cube.obj");
		while (!arq.eof()) {
			string line;
			getline(arq, line);
			stringstream sline;
			sline << line;
			string temp;
			sline >> temp;
			if (temp == "v") {
				// ler vértice ...
				float x, y, z;
				sline >> x >> y >> z;
				this->insertVert(x, y, z);
				this->insertColor(1.f, 1.f, 1.f);

			}
			else if (temp == "f") {
				// implementar lógica de varições
				// para face: v, v/t/n, v/t e v//n

				string token;
				sline >> token; // v/t/n, por exemplo
								//cout << "Valor do token:" << token << endl;
				stringstream fileStream(line);
				string aux;	//linha inteira
				string aux2; //terça parte de uma linha
				float point;
				float fakeColor;

				getline(fileStream, aux, 'f');
				getline(fileStream, aux, ' ');
				//etline(stoken, aux, '/');
				while (getline(fileStream, aux, '\n')) {
					stringstream lineStream(aux);
					while (getline(lineStream, aux2, ' ')) {
						stringstream sectionStream(aux2);
						cout << "Valor do aux:" << aux2 << endl;
						glm::vec2 texts;
						getline(sectionStream, aux2, '/');
						point = (std::stoi(aux2)) - 1;
						getline(sectionStream, aux2, '/');
						getline(sectionStream, aux2);
						fakeColor = (std::stoi(aux2)) - 1;
						texts.x = point;
						texts.y = fakeColor;
						this->insertText(texts.x, texts.y);
					}
	
				}
				// ...
			}
			//---------------------------------------
			else {// else-if
				  // Verificar outras possibilidades:
				  // g, vn, ...
			}
		}
		return mesh;
	}
	
	
};
