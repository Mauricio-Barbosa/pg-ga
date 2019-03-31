#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Group.h"

class Mesh {
private:
	std::vector<Group*> m_vec;

public:
	Mesh() {
		Group* g = new Group;
		m_vec.insert(m_vec.begin(), g);
	}


	Group* getN(int n) {
		return m_vec.at[n];
	}

	void setN(int n, Group* group) {
		m_vec[n] = group;
	}
	
};
