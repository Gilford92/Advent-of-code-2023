#pragma once
#include <list>
#include <map>
#include <string>

#include "directions.h"

class haunted_wasteland
{
public:
	static int part_one(const std::string& file_name, bool debug = false);
	static long long part_two(const std::string& file_name, bool debug = false);

private:
	static std::string parse_map(const std::string& file_name, std::map<std::string, directions>& map, bool debug);
	static std::string parse_map_multiple(const std::string& file_name, std::map<std::string, directions>& map, std::list<std::string>& starts, bool debug);
	static int calculate_steps(const std::string& instructions, std::map<std::string, directions> map, bool debug);
	static long long calculate_steps_multiple(const std::string& instructions, std::map<std::string, directions> map, const std::list<std::string>& starts, bool debug);
};
