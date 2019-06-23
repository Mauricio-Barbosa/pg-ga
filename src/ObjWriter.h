#pragma once


#include <iostream>
#include <fstream>
#include <vector>
#include <glm/vec3.hpp> // glm::vec3

//using namespace std;

class ObjWriter {

private:

public:

	void writeObj(std::vector<glm::vec3> road) {
		ofstream myfile("road.obj");
		if (myfile.is_open())
		{
			//Headers
			myfile << "#road.obj\n";
			myfile << "#\n";
			myfile << "\n";
			myfile << "mtllib road.mtl\n";
			myfile << "\n";

			//Vertex
			for (int i = 0; i < road.size(); i++) {
				myfile << "v " << road.at(i).x << " " << road.at(i).y << " " << road.at(i).z << "\n";
			}
			myfile << "\n";

			//Texture
			myfile << "vt 0.000000 0.000000\n";
			myfile << "vt 1.000000 0.000000\n";
			myfile << "vt 0.000000 1.000000\n";
			myfile << "vt 1.000000 1.000000\n";
			myfile << "\n";

			//Normal
			myfile << "vn 0.0 1.0 0.0\n";
			myfile << "\n";

			//Faces

			myfile << "g road\n";
			myfile << "usemtl road\n";
			int tamanho = road.size() / 2;

			for (int i = 0; i < tamanho - 1; i++) {
				myfile << "f" << " " << (i + 1) << "/" << 1 << "/" << 1 << " " << (i + tamanho + 1) << "/" << 2 << "/" << 1 << " " << (i + tamanho + 1 + 1) << "/" << 3 << "/" << 1 << std::endl;
				myfile << "f" << " " << (i + 1) << "/" << 1 << "/" << 1 << " " << (i + tamanho + 1 + 1) << "/" << 3 << "/" << 1 << " " << (i + 1 + 1) << "/" << 4 << "/" << 1 << std::endl;
			}

			myfile << "f" << " " << (tamanho) << "/" << 1 << "/" << 1 << " " << (tamanho + tamanho) << "/" << 2 << "/" << 1 << " " << (tamanho + 1) << "/" << 3 << "/" << 1 << std::endl;
			myfile << "f" << " " << (tamanho) << "/" << 1 << "/" << 1 << " " << (tamanho + 1) << "/" << 3 << "/" << 1 << " " << (1) << "/" << 4 << "/" << 1 << std::endl;


			myfile.close();
		}
		else cout << "Unable to open file";


		ofstream myfile2("road.mtl");
		if (myfile2.is_open())
		{
			//Headers
			myfile2 << "#newmtl road\n";
			myfile2 << "Ka 0.3 0.3 0.3\n";
			myfile2 << "Kd 0.3 0.3 0.3\n";
			myfile2 << "Ks 0.3 0.3 0.3\n";
			myfile2 << "Ns 90\n";
			
			myfile2.close();
		}
		else cout << "Unable to open file";


	}

	std::vector<glm::vec3> curvesToRoadVerts(std::vector<glm::vec3> internalCurve, std::vector<glm::vec3> externalCurve) {
		std::vector<glm::vec3> roadVerts;
		glm::vec3 point;
		float x;
		float y;
		float z;
		int curveSize = internalCurve.size();

		for (int i = 0; i < curveSize; i++) {
			x = internalCurve.at(i).x;
			y = internalCurve.at(i).z;
			z = internalCurve.at(i).y;
			point = glm::vec3(x, y, z);
			roadVerts.push_back(point);
		}

		for (int i = 0; i < curveSize; i++) {
			x = externalCurve.at(i).x;
			y = externalCurve.at(i).z;
			z = externalCurve.at(i).y;
			point = glm::vec3(x, y, z);
			roadVerts.push_back(point);
		}

		return roadVerts;
	}
};