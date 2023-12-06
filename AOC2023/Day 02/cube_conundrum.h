#pragma once
#include <string>

class cube_conundrum
{
public:
	static int part_one(const std::string& file_name, bool debug = false);
	static int part_two(const std::string& file_name, bool debug = false);

private:
	static void parse(std::string line, bool debug, int& game_id, int& red, int& green, int& blue);
};
