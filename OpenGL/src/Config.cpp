#include "Config.h"
#include <fstream>

void Config::loadConfig(std::string dir, std::string name)
{
	std::ifstream f(dir + name);
}