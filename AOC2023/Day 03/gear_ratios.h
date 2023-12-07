#pragma once
#include <map>
#include <string>

#include "engine_value.h"

class gear_ratios
{
public:
	static int part_one(const std::string& file_name, bool debug = false);
	static int part_two(const std::string& file_name, bool debug = false);

private:
	static void parse(const std::string& line, int row, std::list<engine_value>& engine_values, std::map<int, std::list<int>>& symbols_coordinates, bool debug = false);
	static void parse_gears(const std::string& line, int row, std::list<std::pair<int, int>>& gears, std::map<int, std::list<engine_value>>& engine_values_coordinates, bool debug);
	static void store_engine_value(engine_value& value_to_store, std::list<engine_value>& engine_values);
	static bool find_adjacent_symbol(std::map<int, std::list<int>> symbols_coordinates, int row_to_search, const engine_value& engine_value, int& numbers_sum, bool debug = false);
	static int find_adjacent_numbers(std::pair<int, int> gear, int row_to_search, std::map<int, std::list<engine_value>> engine_values_coordinates, int& ratio);
};
