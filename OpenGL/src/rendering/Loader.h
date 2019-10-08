#pragma once
#include "GL/glew.h"
#include <string>
class Loader {
public:
	static GLuint LoadTexture(const std::string texDir, const std::string texName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter);
};