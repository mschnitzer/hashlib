#pragma once

#include <string>

class Base64 {

public:
	static std::string encode(std::string &text);
	static std::string decode(std::string &text);

};