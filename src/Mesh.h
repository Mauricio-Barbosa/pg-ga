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
	Group* g;

public:
	Mesh() {
		g = new Group;
		m_vec.insert(m_vec.begin(), g);
	}

	
	Group* getN(int n) {
		return m_vec[n];
	}

	void setN(int n, Group* group) {
		m_vec[n] = group;
	}

	
	Mesh *read(std::string filename) {

		//ofstream myfile;
		//myfile.open("C:/PG/sampleObj.obj");
		//myfile << "Writing this to a file.\n";
		//myfile.close();
		//return 0;

		cout << "Sheguei aqui1" << endl;
		Mesh *mesh = new Mesh;
		cout << "Sheguei aqui2" << endl;
		std::ifstream arq("cube.obj");
		while (!arq.eof()) {
			string line;
			getline(arq, line);
			//cout << "Valor da line:" << line << endl;
			stringstream sline;
			sline << line;
			string temp;
			sline >> temp;
			if (temp == "v") {
				// ler vértice ...
				float x, y, z;
				sline >> x >> y >> z;
				this->g->getFace(0)->insertVert(x, y, z);
				this->g->getFace(0)->insertColor(1.f, 1.f, 1.f);

				//Abaixo prints de teste
				//cout << "X: " << x << endl;
				//cout << "Y: " << y << endl;
				//cout << "Z: " << z << endl;

				// ... atribuir vértices da malha
				// ...
			}
			else if (temp == "f") {
				// implementar lógica de varições
				// para face: v, v/t/n, v/t e v//n
				
				string token;
				sline >> token; // v/t/n, por exemplo
				//cout << "Valor do token:" << token << endl;
				stringstream stoken(line);
				string aux;
				string aux2;
				string aux3;
				
				getline(stoken, aux, 'f');
				getline(stoken, aux, ' ');
				//etline(stoken, aux, '/');
				while (getline(stoken, aux, '\n')) {
					stringstream stokenaux(aux);
					cout << "Valor do aux:" << aux << endl;
					glm::vec2 texts;
					getline(stokenaux, aux, '/');
					cout << "Valor do stokeaux:" << aux << endl;
					cout << "Primeiro getLine com barra:" << aux << endl;
					texts.x = (std::stoi(aux)) - 1;
					getline(stokenaux, aux, '/');
					cout << "Segundo getLine com barra:" << aux << endl;
					getline(stokenaux, aux, ' ');
					cout << "Terceiro getLine com barra:" << aux << endl;
					texts.y = (std::stoi(aux)) - 1;
					this->g->getFace(0)->insertText(texts.x, texts.y);
					
					
					//glm::vec2 texts;
					getline(stokenaux, aux2, '/');
					cout << "Valor do stokeaux:" << aux2 << endl;
					cout << "Primeiro getLine com barra:" << aux2 << endl;
					texts.x = (std::stoi(aux2)) - 1;
					getline(stokenaux, aux2, '/');
					cout << "Segundo getLine com barra:" << aux2 << endl;
					getline(stokenaux, aux2, ' ');
					cout << "Terceiro getLine com barra:" << aux2 << endl;
					texts.y = (std::stoi(aux2)) - 1;
					this->g->getFace(0)->insertText(texts.x, texts.y);

					//glm::vec2 texts;
					getline(stokenaux, aux2, '/');
					cout << "Valor do stokeaux:" << aux2 << endl;
					cout << "Primeiro getLine com barra:" << aux2 << endl;
					texts.x = (std::stoi(aux2)) - 1;
					getline(stokenaux, aux2, '/');
					cout << "Segundo getLine com barra:" << aux2 << endl;
					getline(stokenaux, aux2, '\n');
					cout << "Terceiro getLine com barra:" << aux2 << endl;
					texts.y = (std::stoi(aux2)) - 1;
					this->g->getFace(0)->insertText(texts.x, texts.y);
					
				}
				// ...
			}
			else {// else-if
				  // Verificar outras possibilidades:
				  // g, vn, ...
			}
		}
		return mesh;
	}
	
	
};
