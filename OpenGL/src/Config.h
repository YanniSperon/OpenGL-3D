#pragma once
#include <string>

class Config {
private:
	bool fullscreen;
	bool vr;
	int initialWidth;
	int initialHeight;
	float mouseSensitivity;
	float FOV;
	int vsync;
public:
	Config(std::string name);
	Config(std::string dir, std::string name);
	~Config();
	void LoadConfig(std::string dir, std::string name);
	bool getFullscreenPreference();
	bool getVRPreference();
	int getInitialWidthPreference();
	int getInitialHeightPreference();
	float getMouseSensitivityPreference();
	float getFOVPreference();
	int getVSyncPreference();
};