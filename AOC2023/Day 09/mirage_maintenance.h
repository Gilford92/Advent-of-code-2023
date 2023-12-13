#pragma once
#include <list>
#include <string>

#include "node.h"

class mirage_maintenance
{
public:
	static long long part_one(const std::string& file_name, bool debug = false);
	static long long part_two(const std::string& file_name, bool debug = false);

private:
	static std::list<std::list<long long>> parse_data(const std::string& file_name, bool debug);
	static long long extrapolate_next_value(std::list<long long> history, bool debug);
	static long long extrapolate_previous_value(std::list<long long> history, bool debug);
	static std::pair<node*, node*> create_history(std::list<long long> history);
	static void recur_difference(node* difference, node* previous_difference);
	static long long calculate_difference_forward(node* difference, node* previous_difference);
	static long long calculate_difference_backward(node* difference, node* previous_difference);
	static void clean(const node* previous_node);
	static void recur_clean(const node* current_node);
};
