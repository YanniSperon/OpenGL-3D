#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "primitives/Vertex.h"
#include "primitives/ShapeGenerator.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

// next vid https://www.youtube.com/watch?v=XA1P4PtXl_Q&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY&index=37

int initialWidth = 1280;
int initialHeight = 720;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", NULL, NULL);
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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		

		//ShapeData shape = ShapeGenerator::makeCube();
		ShapeData shape = ShapeGenerator::loadShape("airplane.obj");

		std::cout << "-------------------------" << std::endl;

		for (unsigned int i = 0; i < shape.numVertices; i++) {
			std::cout << "Vertex: " << shape.vertices[i].position.x << ", " << shape.vertices[i].position.y << ", " << shape.vertices[i].position.z << "\n";
			std::cout << "Color: " << shape.vertices[i].color.r << ", " << shape.vertices[i].color.g << ", " << shape.vertices[i].color.b << "\n";
		}

		std::cout << "-------------------------" << std::endl;
		for (unsigned int i = 0; i < shape.numIndices; i += 3) {
			std::cout << "Index: " << shape.indices[i] << ", " << shape.indices[i + 1] << ", " << shape.indices[i + 2] << "\n";
		}

		std::cout << "-------------------------" << std::endl;
		std::cout << shape.numVertices << std::endl;
		std::cout << shape.numIndices << std::endl;
		std::cout << "-------------------------" << std::endl;

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
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();



		int width;
		int height;
		glm::vec3 translation(0.0f, 0.0f, -3.0f);
		glm::vec3 rotation(0.0f, 0.0f, 0.0f);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			glfwGetWindowSize(window, &width, &height);
			glViewport(0, 0, width, height);
			/* Render here */
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			ImGui_ImplGlfwGL3_NewFrame();

			glm::mat4 modelTransformMatrix = glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
			glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);

			shader.SetUniformMat4f("modelTransformMatrix", modelTransformMatrix);
			shader.SetUniformMat4f("projectionMatrix", projectionMatrix);

			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

			/*{
				glBindVertexArray(vertexArrayObject);

				glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

				shader.Bind();

				glDrawArrays(GL_TRIANGLES, 0, 3);
			}*/

			{
				ImGui::SliderFloat("X Translation", &translation.x, -1.0f, 1.0f);
				ImGui::SliderFloat("Y Translation", &translation.y, -1.0f, 1.0f);
				ImGui::SliderFloat("Z Translation", &translation.z, -10.0f, 1.0f);
				ImGui::SliderFloat("X Rotation", &rotation.x, 0.0f, 360.0f);
				ImGui::SliderFloat("Y Rotation", &rotation.y, 0.0f, 360.0f);
				ImGui::SliderFloat("Z Rotation", &rotation.z, 0.0f, 360.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}