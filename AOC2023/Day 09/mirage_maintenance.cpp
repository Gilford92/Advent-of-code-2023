#include "mirage_maintenance.h"
#include <fstream>
#include <iostream>
#include "node.h"


long long mirage_maintenance::part_one(const std::string& file_name, const bool debug)
{
	long long sum_extrapolated_values = 0;

	const std::list<std::list<long long>> data = parse_data(file_name, debug);

	for(const std::list<long long>& history : data)
	{
		sum_extrapolated_values += extrapolate_next_value(history, debug);
	}

	if(debug)
	{
		std::cout << '\n';
	}

	return sum_extrapolated_values;
}

std::list<std::list<long long>> mirage_maintenance::parse_data(const std::string& file_name, const bool debug)
{
	std::list<std::list<long long>> data = {};

	std::ifstream input_file(file_name);

	int line_counter = 0;

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		char* c_line = &line[0];
		char* next_token;
		char* p = strtok_s(c_line, " ", &next_token);

		std::list<long long> history = {};

		while(p != nullptr)
		{
			history.push_back(atoll(p));
			p = strtok_s(nullptr, " ", &next_token);
		}

		data.push_back(history);

		++line_counter;
	}

	if(debug)
	{
		std::cout << '\n';
	}

	return data;
}

long long mirage_maintenance::extrapolate_next_value(std::list<long long> history, const bool debug)
{
	node* previous = nullptr;

	for(std::list<long long>::iterator it = history.begin(); it != history.end(); ++it)
	{
		node* current_node = new node;
		current_node->current_value = *it;

		if(previous != nullptr)
		{
			current_node->previous = previous;
			current_node->difference = new node;
			current_node->difference->current_value = current_node->current_value - previous->current_value;

			recur_difference(current_node->difference, previous->difference, debug);
		}

		previous = current_node;
	}

	node* next = new node;
	next->difference = new node;
	next->previous = previous;

	const long long next_value = calculate_difference(next->difference, previous->difference, debug) + previous->current_value;

	node* previous_previous = next;

	do
	{
		previous = previous_previous;
		recur_clean(previous, debug);
		previous_previous = previous->previous;
		delete previous;
	}
	while(previous_previous != nullptr);

	if(debug)
	{
		std::cout << "Next value: " << next_value << '\n';
	}

	return next_value;
}

void mirage_maintenance::recur_difference(node* difference, node* previous_difference, const bool debug)
{
	if(previous_difference != nullptr)
	{
		difference->previous = previous_difference;

		if(difference->current_value != 0 || previous_difference->current_value != 0)
		{
			difference->difference = new node;
			difference->difference->current_value = difference->current_value - previous_difference->current_value;
			recur_difference(difference->difference, previous_difference->difference, debug);
		}
	}
}

long long mirage_maintenance::calculate_difference(node* difference, node* previous_difference, const bool debug)
{
	if(previous_difference != nullptr)
	{
		difference->previous = previous_difference;

		if(difference->previous->difference != nullptr)
		{
			difference->difference = new node;
			difference->current_value = calculate_difference(difference->difference, previous_difference->difference, debug) + previous_difference->current_value;
		}
	}

	return difference->current_value;
}

void mirage_maintenance::recur_clean(const node* current_node, const bool debug)
{
	if(current_node != nullptr && current_node->difference != nullptr)
	{
		recur_clean(current_node->difference, debug);
	}

	delete current_node->difference;
}
