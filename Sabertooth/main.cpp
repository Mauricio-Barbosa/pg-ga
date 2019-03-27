#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

using namespace std;

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	glfwSwapBuffers(window);
}

int main() {


	const char* vertex_shader =
		"#version 410\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vc;"
		"uniform mat4 matrix;"
		"out vec3 color;"
		"void main () {"
		"   color = vc;"
		" gl_Position = matrix * vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 410\n"
		"in vec3 color;"
		"out vec4 frag_color;"
		"void main () {"
		" frag_color = vec4 (color, 1.0);"
		"}";


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
	glClear(GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	//DADOS-------------------------------
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	GLuint colorsVBO = 0;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//-----------------------------------------------------------------

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

	int i = 0;

	float speedX = 1.0f;
	float lastPositionX = 0.0f;
	float speedY = 0.8f;
	float lastPositionY = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

		if (N[0] != 0 || N[1] != 0) {
			cout << "N zero:" << N[0] << " N um" << N[1] << "\n";
		}

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



		cout << "speed X: " << speedX << "\n";
		cout << "speed Y: " << speedY << "\n";
		cout << "matrix 12 antes translate: " << lastPositionX << "\n";
		cout << "matrix 13 antes translate: " << lastPositionY << "\n";
		cout << "elapsedSeconds: " << elapsedSeconds << "\n";

		//Perspectiva
		glm::mat4 proj = glm::perspective(glm::radians(30.0f), (float)1 / (float)1, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(3, 3, 4), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		glm::mat4 t2 = glm::translate(glm::mat4(1.f), glm::vec3((elapsedSeconds * speedX + lastPositionX), (elapsedSeconds * speedY + lastPositionY), 0.f));
		glm::vec4 vector(0.f, 0.f, 1.f, 1.f);
		glm::vec4 transformedVector = t2 * vector;

		

		if (!(transformedVector[1] >= 0.5f)) {
			lastPositionY = transformedVector[1];
		}
		else { lastPositionY = 0.5f; }


		if (!(transformedVector[0] >= 0.5f)) {
			lastPositionX = transformedVector[0];
		}
		else { lastPositionX = 0.5f; }
		
		
		cout << "matrix 12 depois translate: " << lastPositionX << "\n";
		cout << "matrix 13 depois translate: " << lastPositionY << "\n";

		// Move forward
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && fabs(lastPositionY) + 0.02f  < 0.5f) {
			lastPositionY += 0.02f;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && (lastPositionY) - 0.02f > -0.5f) {
			lastPositionY -= 0.02f;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && fabs(lastPositionX) + 0.02f  < 0.5f) {
			lastPositionX += 0.02f;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && (lastPositionX) - 0.02f  > -0.5f) {
			lastPositionX -= 0.02f;
		}


		



		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(proj*view*t2));
		//glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);
		// Define vao como verte array atual
		// desenha pontos a partir do p0 e 3 no total do VAO atual com o shader    
		// atualmente em uso  
		glfwSwapBuffers(window);
	}
}