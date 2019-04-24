#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "AssetManager.h"
#include <SOIL.h>

//https://open.gl/content/code/c3_multitexture.txt


using namespace std;

//#define EXIT_FAILURE -1
//#define EXIT_SUCCESS 0

const char* vertex_shader =
"#version 410\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"uniform mat4 matrix;"
//-----------vv
//layout(location = 0) in vec3 vertex_position;
//layout(location = 1) in vec3 colors;
"layout(location = 2) in vec2 texture_mapping;"
"out vec2 texture_coordinates;"
//out vec3 color_values;
//-----------^^
"out vec3 color_values;"
"void main () {"
//------------vv
"texture_coordinates = texture_mapping;"
//color_values = colors;
//gl_Position = vec4(vertex_position, 1.0);
//--------------^^
"   color_values = vc;"
" gl_Position = matrix * vec4 (vp, 1.0);"
"}";


const char* fragment_shader =
"#version 410\n"

//----------------vv
"in vec2 texture_coordinates;"
//in vec3 color_values;
"uniform sampler2D basic_texture;"
//out vec4 frag_color; // final colour of surface
//-----------------^^
"in vec3 color_values;"
"out vec4 frag_color;"
//"uniform sampler2D texKitten;"
"void main () {"
//------------vv
"frag_color = texture(basic_texture, texture_coordinates) * vec4(color_values, 1.0);"
//------------^^
//" frag_color = vec4 (color, 1.0);"

"}";


Mesh* m = new Mesh;

//cameraPos personalizado para que fique à esquerda, à cima
glm::vec3 cameraPos = glm::vec3(-2.0f, 2.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view;
Shader coreShader;
int activeGroup = 0;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	glfwSwapBuffers(window);
}

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float fov = 45.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
	
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	//if (glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	//}
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}



void processInput(GLFWwindow *window)
{
		float cameraSpeed = 0.005f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m->getGroup(activeGroup)->increaseX();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m->getGroup(activeGroup)->decreaseX();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m->getGroup(activeGroup)->increaseY();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m->getGroup(activeGroup)->decreaseY();
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m->getGroup(activeGroup)->increaseZ();
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m->getGroup(activeGroup)->decreaseZ();
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		activeGroup = 0;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		activeGroup = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		activeGroup = 2;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		activeGroup = 3;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		activeGroup = 4;
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		activeGroup = 5;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		activeGroup = 6;
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		activeGroup = 7;

}


int main() {


	if (!glfwInit()) {
		cerr << "ERROR: could not start GLFW3" << endl;
		return 1;
	}
	GLFWwindow *window = glfwCreateWindow(
		1000, 700, "Teste de versão OpenGL", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!window) {
		cerr << "ERROR: could not open window with GLFW3" << endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	// inicia manipulador da extensão GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// obtenção de versão suportada da OpenGL e renderizador
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cerr << "Renderer:" << renderer << endl;
	cerr << "OpenGL (versão suportada) " << version << endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	//DADOS
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	
	m->read("cube2.obj");
	//m->read("cube2.obj");


	/*
	std::vector<glm::vec3> m_verts = *m->getFullVertices();
	//std::vector<glm::vec3> m_colors = *m->getFakeColor();
	std::vector<glm::vec3> m_colors = *m->getFullVerticesColor();
	for (int i = 0; i < m_colors.size(); i++) {
		m_colors.at(i).x = 1;
		m_colors.at(i).y = 1;
		m_colors.at(i).z = 1;
	}
	std::vector<glm::vec2> m_textures = *m->getFullTextures();
	cout << "Texture vector size" << m_textures.size() << endl;

	GLuint vertsVBO = 0;
	glGenBuffers(1, &vertsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_verts.size(), &m_verts[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	*/
	// identifica vs e o associa com vertex_shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	// identifica fs e o associa com fragment_shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);


	// identifica do programa, adiciona partes e faz "linkagem"
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glUseProgram(shader_programme);
	int matrixLocation = glGetUniformLocation(shader_programme, "matrix");
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));
	
	// Load textures
	GLuint textures;
	glGenTextures(1, &textures);
	glEnable(GL_TEXTURE_2D);
	int width, height;
	unsigned char* image;
	/*
	//Carregamento de imagem
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("wall.png", &width, &height, 0, SOIL_LOAD_RGB);

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
	glUniform1i(glGetUniformLocation(shader_programme, "basic_texture"), 0);


	//VBO de cores
	GLuint colorsVBO = 0;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(text_maps), text_maps, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_colors.size(), &m_colors[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(text_maps), &text_maps[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	//VBO de texturas
	GLuint texturesVBO = 0;
	glGenBuffers(1, &texturesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texturesVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(text_maps), text_maps, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_textures.size(), &m_textures[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(text_maps), &text_maps[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);
	glGenerateMipmap(GL_TEXTURE_2D);

	
	*/
	

	//-----------------------------------


	//Associa função mouse callback ao mouse_callback
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	int incremento = 0;

	glfwSetScrollCallback(window, scroll_callback);
	for (int i = 0; i < m->getGroupSize(); i++) {
		m->getGroup(i)->inicializacao(m->getTextures(), m->getVerts());
	}


	float speedX = 1.0f;
	float lastPositionX = 0.0f;
	float speedY = 0.8f;
	float lastPositionY = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.8f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;

		
		double N[] = { 0, 0 };

		if (fabs(lastPositionX) >= 0.5f && speedX > 0) {
			N[0] = -1;
			N[1] = 0;
		}
		else if (fabs(lastPositionX) >= 0.5f && speedX < 0) {
			N[0] = 1;
			N[1] = 0;
		}
		else if (fabs(lastPositionY) >= 0.5f && speedY > 0) {
			N[0] = 0;
			N[1] = -1;
		}
		else if (fabs(lastPositionY) >= 0.5f && speedY < 0) {
			N[0] = 0;
			N[1] = 1;
		};
		/*
		if (N[0] != 0 || N[1] != 0) {
			cout << "N zero:" << N[0] << " N um" << N[1] << "\n";
		}
		*/
		double Rin[] = { speedX, speedY };

		double RoutX = (2 * N[0] * (N[0] * Rin[0] + N[1] * Rin[1]) - Rin[0]);
		double RoutY = (2 * N[1] * (N[0] * Rin[0] + N[1] * Rin[1]) - Rin[1]);

		if (fabs(lastPositionX) >= 0.5f) {
			//speedX = -speedX;
			speedX = -RoutX;
		}
		if (fabs(lastPositionY) >= 0.5f) {
			//speedY = -speedY;
			speedY = -RoutY;
		}


		for (int i = 0; i < m->getGroupSize(); i++) {
		
			if (i == activeGroup) {
				m->getGroup(i)->selectColor();
			}
			else {
				m->getGroup(i)->noColor();
			}
		
		m->getGroup(i)->draw();
		

		glm::mat4 t2;
		//if (incremento % 2 == 0) {
			//t2 = glm::translate(glm::mat4(1.f), glm::vec3((elapsedSeconds * speedX + lastPositionX), (elapsedSeconds * speedY + lastPositionY), 0.f));
		//}
		//else {
		//t2 = glm::translate(glm::mat4(1.f), glm::vec3((elapsedSeconds * speedX + m->getGroup(activeGroup)->getlastPositionX()), (elapsedSeconds * speedY + m->getGroup(activeGroup)->getlastPositionY()), 0.f));
		t2 = glm::translate(glm::mat4(1.f), glm::vec3(m->getGroup(i)->getlastPositionX(), m->getGroup(i)->getlastPositionY(), m->getGroup(i)->getlastPositionZ() ));
		//}
		//glm::vec4 vector(0.f, 0.f, 1.f, 1.f);
		glm::vec4 vector(0.f, 0.f, 0.f, 0.f);
		glm::vec4 transformedVector = t2 * vector;
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);



		processInput(window);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(projection*view*t2));
		}
		//glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);
		// Define VAO como verte array atual
		// desenha pontos a partir do p0 e 3 no total do VAO atual com o shader    
		// atualmente em uso  
		glfwSwapBuffers(window);
	}
}