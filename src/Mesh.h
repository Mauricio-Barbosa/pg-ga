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
				stringstream stoken;
				string aux;
				getline(stoken, aux, '/');


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
