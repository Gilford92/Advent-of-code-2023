#pragma once
#include <list>
#include <map>
#include <string>

#include "seed_map.h"

class almanac
{
public:
	static long long part_one(const std::string& file_name, bool debug = false);
	static long long part_two(const std::string& file_name, bool debug = false);

private:
	static std::list<long long> get_seeds(std::string line);
	static std::list<std::pair<long long, long long>> get_seeds_range(std::string line);
	static std::string parse_direction_map(std::string line, std::map<std::string, std::string>& seed_maps);
	static seed_map get_seed_map(std::string line);
	static long long get_lowest_location_number(const std::list<long long>& seeds, std::map<std::string, std::string> seed_maps, std::map<std::string, std::list<seed_map>> seed_values, bool debug);
	static long long get_lowest_location_number_range(const std::list<std::pair<long long, long long>>& seeds, std::map<std::string, std::string> seed_maps, std::map<std::string, std::list<seed_map>> seed_values, bool debug);
	static void order_maps(std::list<seed_map>& unordered_maps);
	static void recur(const std::string& previous_map_name, std::map<std::string, std::list<seed_map>> seed_values, std::map<std::string, std::string>& seed_maps_backward, std::list<std::pair<long long, long long>>& desired);
};
