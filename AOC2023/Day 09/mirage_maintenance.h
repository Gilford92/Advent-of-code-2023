#pragma once
#include <list>
#include <string>

#include "node.h"

class mirage_maintenance
{
public:
	static long long part_one(const std::string& file_name, bool debug = false);

private:
	static std::list<std::list<long long>> parse_data(const std::string& file_name, bool debug);
	static long long extrapolate_next_value(std::list<long long> history, bool debug);
	static void recur_difference(node* difference, node* previous_difference, bool debug);
	static long long calculate_difference(node* difference, node* previous_difference, bool debug);
	static void recur_clean(const node* current_node, bool debug);
};
