#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <irrKlang.h>
#include <openvr.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Config.h"
#include "Object.h"
#include "PhysicsBody.h"
#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"
#include "AABBCollidable.h"
#include "Loader.h"
#include "Timer.h"
#include "Simple2DRenderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "primitives/Vertex.h"
#include "primitives/ShapeGenerator.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

Config config = Config("res/other/", "config.txt");
//#define DGPU

#ifdef DGPU 
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

static bool fullscreen = config.getFullscreenPreference();
static float mouseSensitivity = config.getMouseSensitivityPreference();
static float FOV = config.getFOVPreference();

static bool wPressed = false;
static bool sPressed = false;
static bool aPressed = false;
static bool dPressed = false;
static bool spacePressed = false;
static bool controlPressed = false;
static bool shiftPressed = false;
static bool tPressed = false;

static int oldMouseX = 0;
static int oldMouseY = 0;
static float movementSpeed = 10.0f;

Camera camera = Camera(true, movementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), mouseSensitivity);

static int initialWidth = config.getInitialWidthPreference();
static int initialHeight = config.getInitialHeightPreference();

static bool hasVR = config.getVRPreference();

static int currentWidth = initialWidth;
static int currentHeight = initialHeight;

static int VSyncPreference = config.getVSyncPreference();

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

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		controlPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) {
		controlPressed = false;
	}

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		movementSpeed *= 2;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		movementSpeed /= 2;
	}





	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		camera.DisableMovementControls();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
		camera.EnableMovementControls();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		tPressed = true;
	}
	else if (key == GLFW_KEY_T && action == GLFW_RELEASE) {
		tPressed = false;
	}
}
static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (ypos * mouseSensitivity > 1.5708) {
		double newMouseY = 1.57 / mouseSensitivity;
		glfwSetCursorPos(window, xpos, newMouseY);
		camera.LookAt(xpos, newMouseY);
	}
	else if (ypos * mouseSensitivity < -1.5708) {
		double newMouseY = -1.57 / mouseSensitivity;
		glfwSetCursorPos(window, xpos, newMouseY);
		camera.LookAt(xpos, newMouseY);
	}
	else {
		camera.LookAt(xpos, ypos);
	}
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

	if (!glfwInit()) {
		return -1;
	}

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

	glfwMakeContextCurrent(window);

	glfwSwapInterval(VSyncPreference);

	if (glewInit() != GLEW_OK) {
		printf("Error!\n");
	}

	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	vr::IVRSystem* vr_pointer = NULL;

	if (hasVR) {
		vr::EVRInitError eError = vr::VRInitError_None;
		vr_pointer = VR_Init(&eError, vr::VRApplication_Scene); // VRApplication_Background OR VRApplication_Scene OR VRApplication_Overlay OR VRApplication_Utility
		if (eError != vr::VRInitError_None)
		{
			hasVR = false;
			vr_pointer = NULL;
			printf("Unable to init VR runtime: %s \n", VR_GetVRInitErrorAsEnglishDescription(eError));
		}
	}
	
	printf("Vendor: %s\nModel: %s\nVersion: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		glfwSetCursorPosCallback(window, cursorPositionCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		const char* attackSFXFilename = "res/audio/sfx/attack.wav";
		const char* explosionSFXFilename = "res/audio/sfx/explosion.wav";
		const char* jumpSFXFilename = "res/audio/sfx/jump.wav";
		const char* pickupSFXFilename = "res/audio/sfx/pickup.wav";
		const char* selectSFXFilename = "res/audio/sfx/select.wav";
		const char* shootSFXFilename = "res/audio/sfx/shoot.wav";
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		engine->setSoundVolume(0);
		irrklang::ISound* attackSFX = engine->play2D(attackSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* explosionSFX = engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* jumpSFX = engine->play2D(jumpSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* pickupSFX = engine->play2D(pickupSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* selectSFX = engine->play2D(selectSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* shootSFX = engine->play2D(shootSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		//engine->play2D(steamSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);

		Simple2DRenderer renderer;

		Shader shader("res/shaders/Basic.shader");
		Shader glassShader("res/shaders/Window.shader");

		GLuint sphereCowTex = Loader::LoadTexture("res/textures/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint radaTex = Loader::LoadTexture("res/textures/", "rada.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint radaradaTex = Loader::LoadTexture("res/textures/", "radarada.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint new4kTex = Loader::LoadTexture("res/textures/", "4krgba.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint blankTex = Loader::LoadTexture("res/textures/", "blank.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint skyboxTex = Loader::LoadTexture("res/textures/", "skybox.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint glassTex = Loader::LoadTexture("res/textures/", "glass.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		
		Object object = Object(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec3(5.0f, 5.0f, 5.0f), type::blankModel, "res/models/", "plane.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 0.0f), blankTex, shader.GetShaderID());
		Object skybox = Object(glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), type::skyBox, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), skyboxTex, shader.GetShaderID());
		PhysicsBody object1 = PhysicsBody(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), type::texturedModel, "res/models/", "new.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-50.0f, 0.0f, 0.0f), new4kTex, shader.GetShaderID(), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.5f, 0.0f), 1.0f, glm::vec3(5.0f, 0.0f, 0.0f));
		AABBCollidable object2 = AABBCollidable(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), sphereCowTex, shader.GetShaderID(), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		std::vector<AABBCollidable> objects;
		for (unsigned int i = 0; i < 10; i++) {
			objects.push_back(AABBCollidable(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), type::cubeModel, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(i, 0.0f, 0.0f), sphereCowTex, shader.GetShaderID(), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
		}
		AABBCollidable object3 = AABBCollidable(glm::vec3(-2.5f, -2.5f, -0.125f), glm::vec3(2.5f, 2.5f, 0.125f), type::cubeModel, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 5.0f, 7.0f), glassTex, glassShader.GetShaderID(), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));



		GLuint leftEyeFrameBuffer;
		glGenFramebuffers(1, &leftEyeFrameBuffer);
		GLuint rightEyeFrameBuffer;
		glGenFramebuffers(1, &rightEyeFrameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, false);
		ImGui::StyleColorsDark();

		glm::vec3 camPos(0.0f, 0.0f, 0.0f);
		glfwSetCursorPos(window, 0.0, 0.0);

		float timeConstant = 1.0f;
		double lastTime = glfwGetTime();
		double deltaT = 0, nowTime = 0;
		engine->setSoundVolume(1);
		
		while (!glfwWindowShouldClose(window))
		{
			nowTime = glfwGetTime();
			deltaT = (nowTime - lastTime);
			lastTime = nowTime;

			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			ImGui_ImplGlfwGL3_NewFrame();

			float deltaTime = (float)deltaT * timeConstant;

			if (wPressed) {
				camera.MoveForward(deltaTime);
			}
			if (sPressed) {
				camera.MoveBackward(deltaTime);
			}
			if (aPressed) {
				camera.StrafeLeft(deltaTime);
			}
			if (dPressed) {
				camera.StrafeRight(deltaTime);
			}
			if (spacePressed) {
				camera.MoveUp(deltaTime);
			}
			if (controlPressed) {
				camera.MoveDown(deltaTime);
			}
			if (tPressed) {
				//engine->play2D(jumpSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
				printf("Linear Acceleration:(%f, %f, %f)\nLinear Velocity: (%f, %f, %f)\n", object1.GetLinearAcceleration().x, object1.GetLinearAcceleration().y, object1.GetLinearAcceleration().z, object1.GetLinearVelocity().x, object1.GetLinearVelocity().y, object1.GetLinearVelocity().z);
				object1.Stop();
			}

			///////////////////////////////////////////////////////////////////////////
			camera.ChangeMovementSpeed(movementSpeed);
			camera.BringWith(skybox);
			camPos = camera.GetTranslation();

			glm::mat4 viewMatrix = camera.GetViewTransformMatrix();
			glm::mat4 projectionMatrix;
			if (currentWidth > 0 && currentHeight > 0) {
				projectionMatrix = glm::perspective(glm::radians(FOV), (float)currentWidth / (float)currentHeight, 0.1f, 100.0f);
			}
			///////////////////////////////////////////////////////////////////////////
			object1.Update(deltaTime);
			///////////////////////////////////////////////////////////////////////////
			object2.Update(deltaTime);
			///////////////////////////////////////////////////////////////////////////
			object3.Update(deltaTime);
			///////////////////////////////////////////////////////////////////////////
			renderer.submitForceRender(&skybox);
			renderer.submit(&object, camPos);
			renderer.submit(&object1, camPos);
			renderer.submit(&object2, camPos);
			for (unsigned int i = 0; i < objects.size(); i++) {
				renderer.submit(&objects[i], camPos);
			}
			renderer.submit(&object3, camPos);
			
			if (hasVR) {
				vr::TrackedDevicePose_t trackedDevicePose;
				vr_pointer->GetDeviceToAbsoluteTrackingPose(
					vr::TrackingUniverseStanding, 0, &trackedDevicePose, 1);
				vr::VRCompositor()->WaitGetPoses(&trackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

				glBlitNamedFramebuffer(0, leftEyeFrameBuffer, 0, 0, currentWidth, currentHeight, 0, 0, currentWidth, currentHeight	, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				const vr::Texture_t tex = { reinterpret_cast<void*>(intptr_t(leftEyeFrameBuffer)), vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
				vr::EVRCompositorError value = vr::VRCompositor()->Submit(vr::Eye_Left, &tex);
				if (value != vr::VRCompositorError_None)
				{
					printf("VRCompositorError: %i \n", value);
					//vr::VRCompositorError_DoNotHaveFocus;
					//vr::VRCompositorError
				}
			}

			renderer.flush(viewMatrix, projectionMatrix);

			{
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
/*
				ImGui::SliderFloat("xPos", &object3Trans.x, -10.0f, 10.0f);
				ImGui::SliderFloat("yPos", &object3Trans.y, -10.0f, 10.0f);
				ImGui::SliderFloat("zPos", &object3Trans.z, -10.0f, 10.0f);*/
			}

			//object3.TranslateVec3(object3Trans);

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	if (vr_pointer != NULL)
	{
		vr::VR_Shutdown();
		vr_pointer = NULL;
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}