#pragma once
#include <string>

//"D:\oldold\code\vs\RTS\RTS\resources";
//"C:\\Users\\Max\\source\\repos\\Makunika\\RTS\\RTS\\resources";

class Utils {
public:
	static std::string getShaderPathString(std::string name) {
		return R"(D:\oldold\code\vs\RTS\RTS\resources\shaders\)" + name;
	}

	static std::string getImagePathString(std::string name) {
		return R"(D:\oldold\code\vs\RTS\RTS\resources\images\)" + name;
	}

	static std::string getImagePathString() {
		return R"(D:\oldold\code\vs\RTS\RTS\resources\images\)";
	}
};

