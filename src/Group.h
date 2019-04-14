#pragma once


#include "Face.h"

class Group {
private:
	char m_name;
	char m_material;
	std::vector<Face*> m_face;
	
public:
	Group() {
		//Face* face = new Face();
		//m_face.insert(m_face.begin(), face);
	}

	Face* getFace(int i) {
		return m_face.at(i);
	}
	
	void addFace(Face* f) {
		this->m_face.push_back(f);
	}

};
