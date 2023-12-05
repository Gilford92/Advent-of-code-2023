#pragma once
#include <string>

struct literal_digit
{
public:
	std::string word;
	uint8_t index = 0;

	bool parse(char ch);
};
