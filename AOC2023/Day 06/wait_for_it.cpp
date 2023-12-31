﻿#include "wait_for_it.h"

#include <fstream>
#include <iostream>

int wait_for_it::part_one(const std::string& file_name, const bool debug)
{
	int combined_margin_of_error = 1;

	std::ifstream input_file(file_name);

	int line_counter = 0;
	std::list<int> time_values = {};
	std::list<int> distance_values = {};

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		switch(line_counter)
		{
			case 0:
				parse_line(line, time_values);
				break;
			case 1:
				parse_line(line, distance_values);
				break;
		}

		++line_counter;
	}

	if(debug)
	{
		std::cout << '\n';
	}

	std::list<int>::iterator it = distance_values.begin();
	for(const int time : time_values)
	{
		int margin_of_error = 0;

		for(int i = 1; i < time; ++i)
		{
			if(i * (time - i) > *it)
			{
				++margin_of_error;
			}
		}

		combined_margin_of_error *= margin_of_error;

		if(debug)
		{
			std::cout << "Margin of error for " << time << ": " << margin_of_error << " (" << combined_margin_of_error << ")\n";
		}

		++it;
	}

	return combined_margin_of_error;
}

long long wait_for_it::part_two(const std::string& file_name, const bool debug)
{
	long long margin_of_error = 0;

	std::ifstream input_file(file_name);

	int line_counter = 0;
	long long time = 0;
	long long distance = 0;

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		switch(line_counter)
		{
			case 0:
				time = parse_line_single_value(line);
				break;
			case 1:
				distance = parse_line_single_value(line);
				break;
		}

		++line_counter;
	}

	if(debug)
	{
		std::cout << '\n';
	}

	for(long long i = 1; i < time; ++i)
	{
		if(i * (time - i) > distance)
		{
			++margin_of_error;
		}
	}

	if(debug)
	{
		std::cout << "Margin of error for " << time << " and distance " << distance << ": " << margin_of_error << '\n';
	}

	return margin_of_error;
}

void wait_for_it::parse_line(std::string line, std::list<int>& values)
{
	char* c_line = &line[0];
	char* next_token;
	char* p = strtok_s(c_line, " ", &next_token);

	int index = 0;

	while(p != nullptr)
	{
		if(index > 0)
		{
			values.push_back(atoi(p));
		}

		p = strtok_s(nullptr, " ", &next_token);
		++index;
	}
}

long long wait_for_it::parse_line_single_value(const std::string& line)
{
	long long value = 0;

	for(const char c : line)
	{
		if(std::isdigit(c))
		{
			value = value * 10 + (c - '0');
		}
	}

	return value;
}
