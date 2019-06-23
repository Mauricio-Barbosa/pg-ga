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
#include "Camera.h"
#include "Callback.h"
#include <SOIL.h>
#include "curveCalcs.h"

using namespace std;

//#define EXIT_FAILURE -1
//#define EXIT_SUCCESS 0



const char* vertex_shader =
"#version 410\n"
"layout(location=0) in vec3 vp;" //vertex position
"layout(location=1) in vec3 vc;" //vertex color
"layout(location=2) in vec2 texture_mapping;" //texture
"layout(location=3) in vec3 vn;" //vertex normal
"uniform mat4 matrix;"
//"gl_PointSize = 20.0f;"
"out vec2 texture_coordinates;"
"out vec3 color_values;"
"out vec3 vertex_normals;"
"out vec3 pos;"
//"out vec3 matrix;"

"void main () {"
"	texture_coordinates = texture_mapping;"
"	vertex_normals = vn;"
"   color_values = vc;"
//"	vec4 pos = matrix * vec4 (vp, 1.0);"
"	vec3 pos = vec3(matrix) * vp ;"
"	gl_Position = matrix * vec4 (vp, 1.0);"
"}";





const char* fragment_shader =
"#version 410\n"
"in vec3 pos;"
"in vec2 texture_coordinates;"
"in vec3 vertex_normals;"
//"in vec3(matrix);"

"uniform sampler2D basic_texture;"
"uniform float pa = 0.2;"
"uniform float pd = 0.1;"
"uniform float ps = 0.1;"

"varying vec3 norm;"
"uniform vec3 lightPos;"
"vec3 lightDir;"

"vec3 lightColor = vec3(0.3f, 0.1f, 1.0f);"
"in vec3 color_values;"
"out vec4 frag_color;"
"void main () {"
"	vec3 norm = normalize(vertex_normals);"
//"	vec3 lightPos = vec3(0.0f, 0.0f, 3.0f);"
"	vec3 lightPos = vec3(0.0f, 0.0f, 3.0f);"
"	vec3 lightDir = normalize(lightPos - pos);"
"	float diff = max(dot(norm, lightDir), 0.0);"
"	diff = clamp(diff, 0.0, 1.0);"
//"	vec3 diffuse = diff * lightColor;"
"	float ilum = pa+pd+ps;"
"	frag_color = texture(basic_texture, texture_coordinates) * vec4(color_values, 1.0) * (diff);"//(diff + ilum);"
//"	frag_color = texture(basic_texture, texture_coordinates) * (diff + ilum);"
"}";
/*
const char* vertex_shader_points =
"#version 410\n"
"layout(location=0) in vec3 vp;" //vertex position
"layout(location=1) in vec3 vc;" //vertex color
"uniform mat4 matrix;"
"out vec3 color_values;" ///////////
"void main () {"
"   color_values = vc;"
"	gl_Position = matrix * vec4 (vp, 1.0);"
"}";

const char* fragment_shader_points =
"#version 410\n"
"in vec3 color_values;"
"out vec4 frag_color;"
"void main () {"
//"	vec4 frag_color = vec4(color_values, 1.0);"
"	frag_color = vec4(1.0f, 0.0f, 1.0f, 1.0f);"
"}";
*/

const char* vertex_shader_points =
"#version 410\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"uniform mat4 matrix;"
"out vec3 color;"
"out vec3 pos;"
"void main () {"
"   color = vc;"
"	gl_PointSize = 10.0f; "
"	vec3 pos = vec3(matrix) * vp ;"
"	gl_Position = matrix * vec4 (vp, 1.0);"
"}";

const char* fragment_shader_points =
"#version 410\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main () {"
" frag_color = vec4 (color, 1.0);"
"}";


//Mode 0 = leitura obj, mode 1 = editor
int mode = 1;
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 700;




Mesh* m = new Mesh;
glm::mat4 view;
Camera* camera = new Camera(SCR_WIDTH, SCR_HEIGHT);
static Callback* callback;
Shader coreShader;
int activeGroup = 0;
bool firstMouse = true;
CurveCalcs curveCalcs;





void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	glfwSwapBuffers(window);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	callback->mouse_callback(window,  xpos,  ypos);
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(mode == 1)
		callback->mouse_button_callback(window, button, action, mods);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	callback->scroll_callback(window, xoffset, yoffset);
}

void processInput(GLFWwindow *window){
	if(mode == 0){
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			camera->setCameraPos(camera->getCameraPos() + camera->getCameraSpeed() * camera->getCameraFront());
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			camera->setCameraPos(camera->getCameraPos() - camera->getCameraSpeed() * camera->getCameraFront());
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			camera->setCameraPos(camera->getCameraPos() - glm::normalize(glm::cross(
				camera->getCameraFront(), camera->getCameraUp())) * camera->getCameraSpeed());
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			camera->setCameraPos(camera->getCameraPos() + glm::normalize(glm::cross(
				camera->getCameraFront(), camera->getCameraUp())) * camera->getCameraSpeed());
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
		if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
			activeGroup = 0;
			m->enableObject(0);
		}	
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			activeGroup = 1;
			m->enableObject(1);
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			activeGroup = 2;
			m->enableObject(2);
		}
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
	else {

	}
}


int main() {

	callback = new Callback(mode, camera);
	glEnable(0x8642);
	//glEnable(GL_POINT_SMOOTH);

	if (!glfwInit()) {
		cerr << "ERROR: could not start GLFW3" << endl;
		return 1;
	}
	GLFWwindow *window = glfwCreateWindow(
		SCR_WIDTH, SCR_HEIGHT, "Teste de versão OpenGL", NULL, NULL);

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

	
	// identifica vs e o associa com vertex_shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	if (mode == 0) {
		glShaderSource(vs, 1, &vertex_shader, NULL);
	}
	else {
		glShaderSource(vs, 1, &vertex_shader_points, NULL);
	}

	glCompileShader(vs);

	GLint isCompiled = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog[0]);
		cout << "Shader vs deu pau." << endl;
		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(vs); // Don't leak the shader.
		
	}


	// identifica fs e o associa com fragment_shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	if (mode == 0) {
		glShaderSource(fs, 1, &fragment_shader, NULL);
	}
	else {
		glShaderSource(fs, 1, &fragment_shader_points, NULL);
	}

	glCompileShader(fs);

	isCompiled = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog[0]);
		cout << "Shader fs deu pau." << endl;
		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(fs); // Don't leak the shader.
		
	}


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

	std::vector<glm::vec3> drawPoints;
	std::vector<glm::vec3> drawLines;
	std::vector<glm::vec3> drawInternalLines;
	std::vector<glm::vec3> drawExternalLines;
	std::vector<glm::vec3> drawColors;
	std::vector<glm::vec3> LineColors;

	//GLuint vertsVBO = 0;
	//if (mode == 1) {	
	//}

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
		
	if (mode == 0) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m->read("cube2.obj");
		for (int i = 0; i < m->getGroupSize(); i++) {
			m->getGroup(i)->inicializacao(m->getTextures(), m->getVerts(), m->getNorms());
		}
	}
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(30.0f);

	glMatrixMode(GL_PROJECTION);
	//glMatrixMode("matrix");
	glLoadIdentity();
	glOrtho(0.0f, SCR_WIDTH, SCR_HEIGHT, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	//glViewport(0, 0, 1000, 1000);


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.8f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (mode == 0) {
			glm::mat4 t2;
			for (int i = 0; i < m->getGroupSize(); i++) {
				m->getGroup(i)->draw();

				t2 = glm::translate(glm::mat4(1.f), glm::vec3(m->getGroup(i)->getlastPositionX(), m->getGroup(i)->getlastPositionY(), m->getGroup(i)->getlastPositionZ()));

				glm::vec4 vector(0.f, 0.f, 0.f, 0.f);
				glm::vec4 transformedVector = t2 * vector;
				glm::mat4 projection = glm::perspective(glm::radians(camera->fov),
					(float)camera->SCR_WIDTH / (float)camera->SCR_HEIGHT, 0.1f, 100.0f);
				view = glm::lookAt(camera->getCameraPos(), camera->getCameraPos() +
					camera->getCameraFront(), camera->getCameraUp());
				glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(projection * view * t2));
			}
		}

		drawPoints = callback->click_verts;
		if (drawPoints.size() > 3) {
			drawPoints = callback->click_verts;
			drawLines = curveCalcs.generateCurve(drawPoints);
			drawInternalLines = curveCalcs.generateInternalCurve(curveCalcs.generateCurve(drawPoints));
			drawExternalLines = curveCalcs.generateExternalCurve(curveCalcs.generateCurve(drawPoints));
			LineColors = curveCalcs.generateCurveColor(drawInternalLines);
		}

		drawColors = callback->color;
		

		if (mode == 1 && drawPoints.size()>0) {
			
			

			GLuint vertsVBO = 0;
			glGenBuffers(1, &vertsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* drawPoints.size(), &drawPoints[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			
			//VBO de cores
			GLuint colorsVBO = 0;
			glGenBuffers(1, &colorsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* drawColors.size(), &drawColors[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			


			glDrawArrays(GL_POINTS, 0, drawPoints.size());
			
			
			glm::vec4 vector(0.f, 0.f, 0.f, 0.f);
			glm::vec4 transformedVector = vector;
			//glm::mat4 projection = glm::perspective(glm::radians(camera->fov),
			//	(float)camera->SCR_WIDTH / (float)camera->SCR_HEIGHT, 0.1f, 100.0f);

			glm::mat4 projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -20.0f, 20.0f);
			view = glm::lookAt(camera->getCameraPos(), camera->getCameraPos() +
				camera->getCameraFront(), camera->getCameraUp());
			glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(projection* view));
			
			
			if (drawLines.size() > 3) {
				GLuint vertsVBO = 0;
				glGenBuffers(1, &vertsVBO);
				glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* drawLines.size(), &drawLines[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				//VBO de cores
				GLuint colorsVBO = 0;
				glGenBuffers(1, &colorsVBO);
				glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
				//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* drawColors.size(), &drawColors[0], GL_STATIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* LineColors.size(), &LineColors[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				glDrawArrays(GL_LINE_STRIP, 0, drawLines.size());
			

				drawPoints = callback->click_verts;
				drawLines = curveCalcs.generateCurve(drawPoints);
				drawInternalLines = curveCalcs.generateInternalCurve(curveCalcs.generateCurve(drawPoints));
				//drawExternalLines = curveCalcs.generateExternalCurve(drawPoints);
				drawExternalLines = curveCalcs.generateExternalCurve(curveCalcs.generateCurve(drawPoints));
				LineColors = curveCalcs.generateCurveColor(drawInternalLines);
				//LineColors = curveCalcs.generateCurveColor(drawInternalLines);


				vertsVBO = 0;
				glGenBuffers(1, &vertsVBO);
				glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* drawInternalLines.size(), &drawInternalLines[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				colorsVBO = 0;
				glGenBuffers(1, &colorsVBO);
				glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
				//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* drawColors.size(), &drawColors[0], GL_STATIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* LineColors.size(), &LineColors[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				glDrawArrays(GL_LINE_STRIP, 0, drawLines.size());


				vertsVBO = 0;
				glGenBuffers(1, &vertsVBO);
				glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* drawExternalLines.size(), &drawExternalLines[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				colorsVBO = 0;
				glGenBuffers(1, &colorsVBO);
				glBindBuffer(GL_ARRAY_BUFFER, colorsVBO); 
				//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* drawColors.size(), &drawColors[0], GL_STATIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* LineColors.size(), &LineColors[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				glDrawArrays(GL_LINE_STRIP, 0, drawLines.size());


			}


		}
		processInput(window);
		glfwSwapBuffers(window);
	}
}