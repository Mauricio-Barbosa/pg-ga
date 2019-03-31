#pragma once


#include "Face.h"

class Group {
private:
	char m_name;
	char m_material;
	std::vector<Face*> m_face;
public:
	Group() {
		std::cout << "Cheguei no construtor do group";
		Face* f1 = new Face(0.0f, 0.5f, 0.0f);
		Face* f2 = new Face(0.5f, -0.5f, 0.0f);
		Face* f3 = new Face(-0.5f, -0.5f, 0.0f);
		m_face.insert(m_face.begin(), f1);
		m_face.insert(m_face.begin(), f2);
		m_face.insert(m_face.begin(), f3);
	}

	Face* getFace(int i) {
		return m_face.at(i);
	}

};
