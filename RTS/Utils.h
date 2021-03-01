#pragma once
#include <iostream>
#include <string>

class Utils {
public:
	static std::string getShaderPathString(std::string name) {
		std::string alo = "C:\\Users\\pshbl\\source\\repos\\RTS\\RTS\\resources\\shaders\\" + name;
		return alo;
	}

	static std::string getImagePathString(std::string name) {
		return ("C:\\Users\\pshbl\\source\\repos\\RTS\\RTS\\resources\\images\\" + name);
	}

	static std::string getImagePathString() {
		return "C:\\Users\\pshbl\\source\\repos\\RTS\\RTS\\resources\\images\\";
	}
};

