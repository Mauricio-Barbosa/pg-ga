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
	std::vector<Group*> groups;
	std::vector<glm::vec3> m_verts;
	std::vector<glm::vec3> m_norms;
	std::vector<glm::vec3> m_texts;
	std::vector<glm::vec3> m_full;
	//aux2 é utilizado para armazenar temporariament o vec3 de float montado com base nas faces
	//quando o método getFull é chamado
	std::vector<glm::vec3> aux2;
	Group* g;

public:
	Mesh() {
		g = new Group;
		groups.push_back(g);
	}

	void addFace(int groupPos, vector<int> vertsPosition, vector<int> textsPosition, vector<int> normsPosition) {
		this->groups.at(groupPos)->addFace(vertsPosition, textsPosition, normsPosition);
	}




	void insertVert(float x, float y, float z) {
		glm::vec3 m_vec1 = glm::vec3(x, y, z);
		m_verts.push_back(m_vec1);
	}


	void insertText(int x, int y) {
		glm::vec3 m_vec1 = glm::vec3(x, y, 0);
		m_texts.push_back(m_vec1);
	}

	void insertText(int x, int y, int z) {
		glm::vec3 m_vec1 = glm::vec3(x, y, z);
		m_texts.push_back(m_vec1);
	}
	
	glm::vec3* getVert(int n) {
		return &m_verts[n];
	}

	std::vector<glm::vec3>* getFakeColor() {
		for (int i = 0; i < m_texts.size(); i++) {
			glm::vec3* aux = getVert(m_texts[i].y);
			aux2.push_back(*aux);
		}
		return &aux2;
	}
	
	/*
	glm::vec2* getText(int n) {
		return &m_texts[n];
	}

	std::vector<glm::vec2>* getText() {
		return &m_texts;
	}

	std::vector<glm::vec3>* getVector() {
	return &m_verts;
	}
	*/
	/*
	std::vector<glm::vec3>* getFull() {
		for (int i = 0; i < m_texts.size(); i++) {
			glm::vec3* aux = getVert(m_texts[i].x);
			m_full.push_back(*aux);
			int temp = m_texts[i].x;
		}
		return &m_full;
	}
	*/
	std::vector<glm::vec3>* getFull() {
		for (int i = 0; i < groups.size(); i++) {
			for (int j = 0; j < this->groups.at(i)->getFaceSize(); j++) {
				glm::vec3 aux = groups.at(i)->getFace(j)->getVertVec3();
				//int textPos = groups.at(i)->getFace(j)->getVert(1);
				//int normPos = groups.at(i)->getFace(j)->getVert(2);
				glm::vec3 aux1; 
				//glm::vec3 aux2;
				//glm::vec3 aux3;
				aux1 = this->m_verts.at(aux.x);
				m_full.push_back(aux1);
				aux1 = this->m_verts.at(aux.y);
				m_full.push_back(aux1);
				aux1 = this->m_verts.at(aux.z);
				m_full.push_back(aux1);
				//aux2 = this->m_texts.at(textPos);
				//m_full.push_back(aux2);
				//aux3 = this->m_verts.at(normPos);
				//m_full.push_back(aux3);
			}
		}
		return &m_full;
	}
	
	Group* getN(int n) {
		return groups[n];
	}

	Mesh *read(std::string filename) {
		cout << "Cheguei aqui1" << endl;
		Mesh *mesh = new Mesh;
		cout << "Cheguei aqui2" << endl;
		std::ifstream arq(filename);

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
				
				
				//int groupNumber = 0;
				float point;
				float texture;
				float normal;
				getline(fileStream, aux, 'f');
				getline(fileStream, aux, ' ');

				while (getline(fileStream, aux, '\n')) {
					std::vector<int> vertsPosition;
					std::vector<int> textsPosition;
					std::vector<int> normsPosition;
					stringstream lineStream(aux);
					
					while (getline(lineStream, aux2, ' ')) {
						stringstream sectionStream(aux2);
						
						getline(sectionStream, aux2, '/');
						point = (std::stoi(aux2)) - 1;
						
						getline(sectionStream, aux2, '/');
						if(aux2.size() != 0){
							texture = (std::stoi(aux2)) - 1;
						} else {
							texture = 0;
						}
						
						getline(sectionStream, aux2);
						normal = (std::stoi(aux2)) - 1;
						
						//Remover depois que faces extiver funcionando
						this->insertText(point, normal, texture);

						vertsPosition.push_back(point);
						textsPosition.push_back(texture);
						normsPosition.push_back(normal);
					}
					this->addFace(0, vertsPosition, textsPosition, normsPosition);

				}
			}
			else {// else-if
				  // Verificar outras possibilidades:
				  // g, vn, ...
			}
		}
		return mesh;
	}
};
