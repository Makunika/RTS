#pragma once
#include <string>

//"C:\\Users\\pshbl\\source\\repos\\RTS\\RTS\\resources";
//"C:\\Users\\Max\\source\\repos\\Makunika\\RTS\\RTS\\resources";

class Utils {
public:
	static std::string getShaderPathString(std::string name) {
		std::string alo = "C:\\Users\\Max\\source\\repos\\Makunika\\RTS\\RTS\\resources\\shaders\\" + name;
		return alo;
	}

	static std::string getImagePathString(std::string name) {
		return "C:\\Users\\Max\\source\\repos\\Makunika\\RTS\\RTS\\resources\\images\\" + name;
	}

	static std::string getImagePathString() {
		return "C:\\Users\\Max\\source\\repos\\Makunika\\RTS\\RTS\\resources\\images\\";
	}
};

