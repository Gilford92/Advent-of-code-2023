#pragma once
#include <string>

#include "play.h"

class camel_cards
{
public:
	static int part_one(const std::string& file_name, bool debug = false);

private:
	static play parse_play(std::string line);
};
