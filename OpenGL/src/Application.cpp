#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "primitives/Mesh.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "primitives/Vertex.h"
#include "primitives/ShapeGenerator.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

// next vid https://www.youtube.com/watch?v=XA1P4PtXl_Q&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY&index=37

int initialWidth = 1280;
int initialHeight = 720;



static bool fullscreen = false;

static bool wPressed = false;
static bool sPressed = false;
static bool aPressed = false;
static bool dPressed = false;
static bool spacePressed = false;
static bool shiftPressed = false;

static int currentWidth = initialWidth;
static int currentHeight = initialHeight;


static int oldMouseX = 0;
static int oldMouseY = 0;
static float mouseSensitivity = 0.005f;
static float movementSpeed = 0.1f;

Mesh mesh = Mesh(type::blankModel, "", "airplane.obj");

static bool movementEnabled = true;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		wPressed = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		wPressed = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		sPressed = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		sPressed = false;
	}



	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		aPressed = true;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		aPressed = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		dPressed = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		dPressed = false;
	}



	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		spacePressed = true;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		spacePressed = false;
	}

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		shiftPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		shiftPressed = false;
	}





	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		movementEnabled = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
		movementEnabled = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	camera.LookAt(xpos, ypos);
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	currentWidth = width;
	currentHeight = height;
	if (width > 0 && height > 0) {
		glViewport(0, 0, width, height);
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	if (fullscreen) {
		window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", NULL, NULL);
	}

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // Enable v-sync

	if (glewInit() != GLEW_OK) {
		std::cout << "Error!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable the cursor to allow infinite movement
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		glfwSetCursorPosCallback(window, cursorPositionCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		


		ShapeData shape = ShapeGenerator::loadShape("airplane.obj");



		GLuint vertexBufferID;
		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));
		// index, amount of values, type of value, normalize? (not sure what that means), step (distance in bytes between each starting
		// point of data), starting point (amount of bytes to skip from the beginning of the data set to begin the desired data set i.e.
		// skipping the vertices to get the color for the color attribpointer.



		GLuint indexBufferID;
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
		
		GLsizei numIndices = (GLsizei) shape.numIndices;

		shape.cleanUp(); // You don't need to keep these values because the coordinates for the shapes will never change.
		// The only values that will change are what the shader returns based on the MVP
		


		Shader shader("res/shaders/Basic.shader");
		shader.Bind();



		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, false);
		ImGui::StyleColorsDark();



		int width;
		int height;
		glm::vec3 objectTranslation(0.0f, 0.0f, -3.0f);
		glm::vec3 objectRotation(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraTranslation(0.0f, 0.0f, 0.0f);
		glfwSetCursorPos(window, 0.0, 0.0);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			ImGui_ImplGlfwGL3_NewFrame();


			if (movementEnabled) {
				if (wPressed) {
					cameraTranslation += movementSpeed * viewDirection;
				}
				if (sPressed) {
					cameraTranslation += -movementSpeed * viewDirection;
				}
				if (aPressed) {
					glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
					cameraTranslation += -movementSpeed * strafeDirection;
				}
				if (dPressed) {
					glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
					cameraTranslation += movementSpeed * strafeDirection;
				}
				if (spacePressed) {
					cameraTranslation += movementSpeed * upDirection;
				}
				if (shiftPressed) {
					cameraTranslation += -movementSpeed * upDirection;
				}
			}
			
			glm::mat4 viewMatrix = glm::lookAt(cameraTranslation, cameraTranslation + viewDirection, upDirection);

			glm::mat4 projectionMatrix;
			if (currentWidth > 0 && currentHeight > 0) {
				projectionMatrix = glm::perspective(glm::radians(90.0f), (float)currentWidth / (float)currentHeight, 0.1f, 100.0f);
			}

			glm::mat4 modelTransformMatrix = mesh.GetModelTransformMatrix();


			glm::mat4 MVP = projectionMatrix * viewMatrix * modelTransformMatrix;
			shader.SetUniformMat4f("MVP", MVP);



			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);



			{
				ImGui::SliderFloat("Object X Translation", &objectTranslation.x, -1.0f, 1.0f);
				ImGui::SliderFloat("Object Y Translation", &objectTranslation.y, -1.0f, 1.0f);
				ImGui::SliderFloat("Object Z Translation", &objectTranslation.z, -10.0f, 1.0f);
				ImGui::SliderFloat("Object X Rotation", &objectRotation.x, 0.0f, 360.0f);
				ImGui::SliderFloat("Object Y Rotation", &objectRotation.y, 0.0f, 360.0f);
				ImGui::SliderFloat("Object Z Rotation", &objectRotation.z, 0.0f, 360.0f);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			
			mesh.rotatev(objectRotation);
			mesh.translatev(objectTranslation);

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}