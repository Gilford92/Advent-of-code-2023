#pragma once
#include <list>
#include <map>
#include <string>

#include "seed_map.h"

class almanac
{
public:
	static long long part_one(const std::string& file_name, bool debug = false);

private:
	static std::list<long long> get_seeds(std::string line);
	static std::string parse_direction_map(std::string line, std::map<std::string, std::string>& seed_maps);
	static seed_map get_seed_map(std::string line);
};
