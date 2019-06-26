#pragma once


#include "Face.h"
#include <SOIL.h>

using namespace std;

class Group {

private:
	char m_name;
	char m_material;
	float speed;
	string mtlName;
	const char * textureImage;
	int width, height;
	std::vector<glm::vec3> m_verts;
	std::vector<glm::vec3> m_colors;
	std::vector<glm::vec3> m_full;
	std::vector<glm::vec3> m_normsSave;
	std::vector<glm::vec3> m_vertsSave;
	std::vector<glm::vec2> m_texturesSave;
	std::vector<glm::vec3> m_fullVerts;
	std::vector<glm::vec3> m_fullNorms;
	std::vector<glm::vec2> m_fullText;
	std::vector<glm::vec2> m_textures;
	std::vector<Face*> m_face;
	GLuint textures;
	GLuint vertsVBO;
	GLuint colorsVBO;
	GLuint texturesVBO;
	GLuint normsVBO;
	GLuint VAO;
	unsigned char* image; //imagem lida pelo soil
	
public:
	Face* face;
	float lastPositionX;
	float lastPositionY;
	float lastPositionZ;

	Group() {
		lastPositionX = 0;
		lastPositionY = 0;
		lastPositionZ = 0;
		speed = 0.002f;
		this->textureImage = "road.jpg";
	}

	Group(char * textureName) {
		lastPositionX = 0;
		lastPositionY = 0;
		lastPositionZ = 0;
		speed = 0.002f;
		this->textureImage = textureName;
	}

	void setTexture(char * textureName) {
		this->textureImage = textureName;
	}

	void increaseY() {
		lastPositionY += speed;
	}
	void decreaseY() {
		lastPositionY -= speed;
	}
	void setY(float pos) {
		lastPositionY = pos;
	}
	void increaseX() {
		lastPositionX += speed;
	}
	void decreaseX() {
		lastPositionX -= speed;
	}
	void setX(float pos) {
		lastPositionX = pos;
	}
	void increaseZ() {
		lastPositionZ += speed;
	}
	void decreaseZ() {
		lastPositionZ -= speed;
	}
	void setZ(float pos) {
		lastPositionZ = pos;
	}

	float getlastPositionX() {
		return this->lastPositionX;
	}
	float getlastPositionY() {
		return this->lastPositionY;
	}
	float getlastPositionZ() {
		return this->lastPositionZ;
	}

	Face* getFace(int i) {
		return m_face.at(i);
	}
	
	int getFaceSize() {
		return m_face.size();
	}

	void addFace(Face* f) {
		this->m_face.push_back(f);
	}

	void addFace(vector<int> vertsPosition, vector<int> textsPosition, vector<int> normsPosition) {
		Face* f = new Face(vertsPosition, textsPosition, normsPosition);
		this->m_face.push_back(f);
	}


	std::vector<glm::vec3> getFakeColor() {
		return this->getFullVerticesColor();
	}

	std::vector<glm::vec3> getFullVertices(vector<glm::vec3> m_verts) {
		for (int j = 0; j < this->getFaceSize(); j++) {
			glm::vec3 aux = getFace(j)->getVertVec3();
			glm::vec3 aux1;  //vertice
			aux1 = m_verts.at(aux.x);
			m_full.push_back(aux1);
			aux1 = m_verts.at(aux.y);
			m_full.push_back(aux1);
			aux1 = m_verts.at(aux.z);
			m_full.push_back(aux1);
		}
		return m_full;
	}

	std::vector<glm::vec3> getFullNorms(vector<glm::vec3> m_norms) {
		for (int j = 0; j < this->getFaceSize(); j++) {
			glm::vec3 aux = getFace(j)->getNormVec3();
			glm::vec3 aux1;  //vertice
			aux1 = m_norms.at(aux.x);
			m_fullNorms.push_back(aux1);
			aux1 = m_norms.at(aux.y);
			m_fullNorms.push_back(aux1);
			aux1 = m_norms.at(aux.z);
			m_fullNorms.push_back(aux1);
		}
		return m_fullNorms;
	}

	//Retorna o m_full sem adicionar mais elementos nele.
	//Usar temporariamente até que leitura de cores seja definida.
	std::vector<glm::vec3> getFullVerticesColor() {
		return m_full;
	}


	std::vector<glm::vec2> getFullTextures(vector<glm::vec2> m_textures) {
		for (int j = 0; j < this->getFaceSize(); j++) {
			glm::vec3 text = getFace(j)->getTextVec3();
			glm::vec2 texAux;
			texAux = m_textures.at(text.x);
			m_fullText.push_back(texAux);
			texAux = m_textures.at(text.y);
			m_fullText.push_back(texAux);
			texAux = m_textures.at(text.z);
			m_fullText.push_back(texAux);
		}
		return m_fullText;
	}

	void noColor() {
		for (int i = 0; i < m_colors.size(); i++) {
			m_colors.at(i).x = 1;
			m_colors.at(i).y = 1;
			m_colors.at(i).z = 1;
		}
		GLuint colorsVBO = 0;
		glGenBuffers(1, &colorsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_colors.size(), &m_colors[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}

	void selectColor() {
		for (int i = 0; i < m_colors.size(); i++) {
			m_colors.at(i).x = 1;
			m_colors.at(i).y = 0.5;
			m_colors.at(i).z = 1;
		}
		GLuint colorsVBO = 0;
		glGenBuffers(1, &colorsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_colors.size(), &m_colors[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}

	std::vector<glm::vec3> generateCarPath() {
		std::vector<glm::vec3> path;
		glm::vec3 point;
		for (int i = 0; i < this->m_fullVerts.size()-2; i+=2) {
			//if(i % 3 != 0){
				point.x = (this->m_fullVerts.at(i).x + this->m_fullVerts.at(i + 1).x) / 2;
				point.y = (this->m_fullVerts.at(i).y + this->m_fullVerts.at(i + 1).y) / 2;
				point.z = (this->m_fullVerts.at(i).z + this->m_fullVerts.at(i + 1).z) / 2;
				path.push_back(point);
			//}
		}
		return path;
	}

	void inicializacao(vector<glm::vec2> m_textures, vector<glm::vec3> m_verts, vector<glm::vec3> m_norms, string MtlName) {

		
		//this->m_vertsSave = m_verts;
		this->m_normsSave = m_norms;

		//GLuint VAO = 0;
		VAO = 0;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		this->m_fullVerts = this->getFullVertices(m_verts);
		this->m_fullNorms = this->getFullNorms(m_norms);
		this->mtlName = MtlName;

		m_colors = this->getFullVerticesColor();
		for (int i = 0; i < m_colors.size(); i++) {
			m_colors.at(i).x = 1;
			m_colors.at(i).y = 1;
			m_colors.at(i).z = 1;
		}
		m_textures = this->getFullTextures(m_textures);
		this->m_texturesSave = this->getFullTextures(m_textures);

		//GLuint vertsVBO = 0;
		vertsVBO = 0;
		glGenBuffers(1, &vertsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_fullVerts.size(), &m_fullVerts[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		// Load textures
		//GLuint textures;
		glGenTextures(1, &textures);
		glEnable(GL_TEXTURE_2D);
		//int width, height;
		//unsigned char* image;

		//Carregamento de imagem
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//image = SOIL_load_image("wall.png", &width, &height, 0, SOIL_LOAD_RGB);
		//image = SOIL_load_image("road.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		this->image = SOIL_load_image(textureImage, &width, &height, 0, SOIL_LOAD_RGB);

		if (image) {
			cout << "image loaded sucesfully:" << endl;
			cout << "image width = " << width << endl;
			cout << "image height = " << height << endl;
		}
		else {
			cout << "failed to load image" << endl;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);

		//VBO de cores
		//GLuint colorsVBO = 0;
		colorsVBO = 0;
		glGenBuffers(1, &colorsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_colors.size(), &m_colors[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

		//VBO de texturas
		//GLuint texturesVBO = 0;
		texturesVBO = 0;
		glGenBuffers(1, &texturesVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texturesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_textures.size(), &m_textures[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
		glGenerateMipmap(GL_TEXTURE_2D);

		//GLuint normsVBO = 0;
		normsVBO = 0;
		glGenBuffers(1, &normsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_norms.size(), &m_norms[0], GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(3);

	}

	void inicializacaoSimples() {
		
		VAO = 0;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		
		vertsVBO = 0;
		glGenBuffers(1, &vertsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_fullVerts.size(), &m_fullVerts[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindTexture(GL_TEXTURE_2D, textures);
		
		//VBO de cores
		colorsVBO = 0;
		glGenBuffers(1, &colorsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_colors.size(), &m_colors[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

		//VBO de texturas
		texturesVBO = 0;
		glGenBuffers(1, &texturesVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texturesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_texturesSave.size(), &m_texturesSave[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
		glGenerateMipmap(GL_TEXTURE_2D);

		normsVBO = 0;
		glGenBuffers(1, &normsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_normsSave.size(), &m_normsSave[0], GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(3);

	}

	void draw() {
		glDrawArrays(GL_TRIANGLES, 0, this->m_fullVerts.size());
	}

};
