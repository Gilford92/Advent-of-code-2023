#include "haunted_wasteland.h"

#include <fstream>
#include <iostream>
#include <list>
#include <numeric>

int haunted_wasteland::part_one(const std::string& file_name, const bool debug)
{
	std::map<std::string, directions> map = {};
	const std::string instructions = parse_map(file_name, map, debug);
	return calculate_steps(instructions, map, debug);
}

long long haunted_wasteland::part_two(const std::string& file_name, const bool debug)
{
	std::map<std::string, directions> map = {};
	std::list<std::string> starts = {};
	const std::string instructions = parse_map_multiple(file_name, map, starts, debug);
	return calculate_steps_multiple(instructions, map, starts, debug);
}

std::string haunted_wasteland::parse_map(const std::string& file_name, std::map<std::string, directions>& map, const bool debug)
{
	std::string instructions;

	std::ifstream input_file(file_name);

	int line_counter = 0;

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		if(line_counter == 0)
		{
			instructions = line;
		}
		else if(line_counter > 1)
		{
			char* c_line = &line[0];
			char* next_token;
			char* p = strtok_s(c_line, " ", &next_token);

			std::string current_node;
			std::string left;

			int index = 0;

			while(p != nullptr)
			{
				if(index == 0)
				{
					current_node = p;
				}
				else if(index == 2)
				{
					left = std::string({p[1], p[2], p[3]});
				}
				else if(index == 3)
				{
					std::string right = std::string({p[0], p[1], p[2]});
					directions current_directions = {};
					current_directions.init(current_node, left, right);
					map[current_node] = current_directions;
					break;
				}

				p = strtok_s(nullptr, " ", &next_token);
				++index;
			}
		}

		++line_counter;
	}

	if(debug)
	{
		std::cout << '\n';
	}

	return instructions;
}

std::string haunted_wasteland::parse_map_multiple(const std::string& file_name, std::map<std::string, directions>& map, std::list<std::string>& starts, const bool debug)
{
	std::string instructions;

	std::ifstream input_file(file_name);

	int line_counter = 0;

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		if(line_counter == 0)
		{
			instructions = line;
		}
		else if(line_counter > 1)
		{
			char* c_line = &line[0];
			char* next_token;
			char* p = strtok_s(c_line, " ", &next_token);

			std::string current_node;
			std::string left;

			int index = 0;

			while(p != nullptr)
			{
				if(index == 0)
				{
					current_node = p;

					constexpr char start = 'A';

					if(current_node[2] == start)
					{
						starts.push_back(current_node);
					}
				}
				else if(index == 2)
				{
					left = std::string({p[1], p[2], p[3]});
				}
				else if(index == 3)
				{
					std::string right = std::string({p[0], p[1], p[2]});
					directions current_directions = {};
					current_directions.init(current_node, left, right);
					map[current_node] = current_directions;
					break;
				}

				p = strtok_s(nullptr, " ", &next_token);
				++index;
			}
		}

		++line_counter;
	}

	if(debug)
	{
		std::cout << '\n';
	}

	return instructions;
}

int haunted_wasteland::calculate_steps(const std::string& instructions, std::map<std::string, directions> map, const bool debug)
{
	const std::string start = "AAA";
	const std::string end = "ZZZ";
	const size_t instructions_length = instructions.length();

	std::string current_node = start;

	int steps = 0;

	do
	{
		char current_instruction = instructions[steps % instructions_length];

		if(debug)
		{
			std::cout << current_node << " -> " << map[current_node].next[current_instruction] << " (" << steps + 1 << ")\n";
		}

		current_node = map[current_node].next[current_instruction];
		++steps;
	}
	while(current_node != end);

	if(debug)
	{
		std::cout << '\n';
	}

	return steps;
}

long long haunted_wasteland::calculate_steps_multiple(const std::string& instructions, std::map<std::string, directions> map, const std::list<std::string>& starts, const bool debug)
{
	const size_t instructions_length = instructions.length();

	int steps = 0;
	std::list<int> min_steps = {};

	for(const std::string& start : starts)
	{
		steps = 0;
		std::string current_node = start;
		constexpr char end = 'Z';

		do
		{
			char current_instruction = instructions[steps % instructions_length];

			if(debug)
			{
				std::cout << current_node << " -> " << map[current_node].next[current_instruction] << " (" << steps + 1 << ")\n";
			}

			current_node = map[current_node].next[current_instruction];
			++steps;
		}
		while(current_node[2] != end);

		if(debug)
		{
			std::cout << '\n' << "Min steps: " << steps << '\n';
		}

		min_steps.push_back(steps);
	}

	if(debug)
	{
		std::cout << '\n';
	}

	long long lcm = 1;
	for(const int min_step : min_steps)
	{
		lcm = std::lcm<long long, long long>(lcm, min_step);
	}

	return lcm;
}
