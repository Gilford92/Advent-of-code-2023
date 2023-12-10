#pragma once
#include <list>
#include <string>

class wait_for_it
{
public:
	static int part_one(const std::string& file_name, bool debug = false);

private:
	static void parse_line(std::string line, std::list<int>& values);
};
