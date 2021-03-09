#pragma once
#include <string>

//"C:\\Users\\pshbl\\source\\repos\\RTS\\RTS\\resources";
//"C:\\Users\\Max\\source\\repos\\Makunika\\RTS\\RTS\\resources";

class Utils {
public:
	static std::string getShaderPathString(std::string name) {
		return "C:\\Users\\pshbl\\source\\repos\\RTS\\RTS\\resources\\shaders\\" + name;
	}

	static std::string getImagePathString(std::string name) {
		return "C:\\Users\\pshbl\\source\\repos\\RTS\\RTS\\resources\\images\\" + name;
	}

	static std::string getImagePathString() {
		return "C:\\Users\\pshbl\\source\\repos\\RTS\\RTS\\resources\\images\\";
	}
};

