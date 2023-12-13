#include "mirage_maintenance.h"
#include <fstream>
#include <iostream>
#include <utility>
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

long long mirage_maintenance::part_two(const std::string& file_name, const bool debug)
{
	long long sum_extrapolated_values = 0;

	const std::list<std::list<long long>> data = parse_data(file_name, debug);

	for(const std::list<long long>& history : data)
	{
		sum_extrapolated_values += extrapolate_previous_value(history, debug);
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
	const auto [start, end] = create_history(std::move(history));

	node* next = new node;
	next->difference = new node;
	next->previous = end;

	const long long next_value = calculate_difference_forward(next->difference, end->difference) + end->current_value;

	clean(next);

	if(debug)
	{
		std::cout << "Next value: " << next_value << '\n';
	}

	return next_value;
}

long long mirage_maintenance::extrapolate_previous_value(std::list<long long> history, const bool debug)
{
	const auto [start, end] = create_history(std::move(history));

	node* previous = new node;
	previous->difference = new node;
	start->previous = previous;

	const long long next_value = start->current_value - calculate_difference_backward(end->difference, previous->difference);

	clean(end);

	if(debug)
	{
		std::cout << "Next value: " << next_value << '\n';
	}

	return next_value;
}

std::pair<node*, node*> mirage_maintenance::create_history(std::list<long long> history)
{
	node* start = nullptr;
	node* end = nullptr;

	for(std::list<long long>::iterator it = history.begin(); it != history.end(); ++it)
	{
		node* current_node = new node;
		current_node->current_value = *it;

		if(end != nullptr)
		{
			current_node->previous = end;
			current_node->difference = new node;
			current_node->difference->current_value = current_node->current_value - end->current_value;

			recur_difference(current_node->difference, end->difference);
		}

		if(start == nullptr)
		{
			start = current_node;
		}

		end = current_node;
	}

	return std::pair<node*, node*>{start, end};
}

void mirage_maintenance::recur_difference(node* difference, node* previous_difference)
{
	if(previous_difference != nullptr)
	{
		difference->previous = previous_difference;

		if(difference->current_value != 0 || previous_difference->current_value != 0)
		{
			difference->difference = new node;
			difference->difference->current_value = difference->current_value - previous_difference->current_value;
			recur_difference(difference->difference, previous_difference->difference);
		}
	}
}

long long mirage_maintenance::calculate_difference_forward(node* difference, node* previous_difference)
{
	if(previous_difference != nullptr)
	{
		difference->previous = previous_difference;

		if(difference->previous->difference != nullptr)
		{
			difference->difference = new node;
			difference->current_value = calculate_difference_forward(difference->difference, previous_difference->difference) + previous_difference->current_value;
		}
	}

	return difference->current_value;
}

long long mirage_maintenance::calculate_difference_backward(node* difference, node* previous_difference)
{
	if(difference->difference != nullptr)
	{
		calculate_difference_backward(difference->difference, difference);

		node* diff_previous = difference;
		const node* diff_previous_previous = difference;
		while(diff_previous->previous != nullptr)
		{
			diff_previous_previous = diff_previous;
			diff_previous = diff_previous->previous;
		}

		diff_previous->difference = new node;
		diff_previous_previous->difference->previous = diff_previous->difference;

		if(diff_previous_previous->difference->difference != nullptr)
		{
			diff_previous->difference->current_value = diff_previous_previous->difference->current_value - diff_previous_previous->difference->difference->current_value;
		}
		else
		{
			diff_previous->difference->current_value = 0;
		}

		return diff_previous->current_value - diff_previous->difference->current_value;
	}

	return difference->current_value;
}

void mirage_maintenance::clean(const node* previous_node)
{
	do
	{
		const node* current_node = previous_node;
		recur_clean(current_node);
		previous_node = current_node->previous;
		delete current_node;
	}
	while(previous_node != nullptr);
}

void mirage_maintenance::recur_clean(const node* current_node)
{
	if(current_node != nullptr && current_node->difference != nullptr)
	{
		recur_clean(current_node->difference);
	}

	delete current_node->difference;
}
