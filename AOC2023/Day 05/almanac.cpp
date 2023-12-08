#include "almanac.h"

#include <fstream>
#include <iostream>

long long almanac::part_one(const std::string& file_name, const bool debug)
{
	long long lowest_location_number = LONG_MAX;

	std::ifstream input_file(file_name);

	std::list<long long> seeds = {};

	int line_counter = 0;
	bool direction_map_line = true;
	std::map<std::string, std::string> seed_maps = {};
	std::map<std::string, std::list<seed_map>> seed_values = {};
	std::string current_map_name;

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		if(line_counter == 0)
		{
			seeds = get_seeds(line);
		}
		else if(line_counter > 1)
		{
			if(!line.empty())
			{
				if(direction_map_line)
				{
					current_map_name = parse_direction_map(line, seed_maps);
					direction_map_line = false;
				}
				else
				{
					seed_map current_seed_map = get_seed_map(line);
					seed_values[current_map_name].push_back(current_seed_map);
				}
			}
			else
			{
				direction_map_line = true;
			}
		}

		++line_counter;
	}

	for(long long seed : seeds)
	{
		long long next = seed;
		std::string next_map_name = "seed";
		std::list<seed_map> current_seed_values;

		do
		{
			next_map_name = seed_maps[next_map_name];
			current_seed_values = seed_values[next_map_name];

			for(seed_map seed_map : current_seed_values)
			{
				if(next >= seed_map.source_range_start && next <= seed_map.source_range_start + seed_map.range_length)
				{
					long long next_converted = seed_map.destination_range_start + (next - seed_map.source_range_start);

					if(debug)
					{
						std::cout << "Value " << next << " corresponds to " << next_converted << " in " << next_map_name << '\n';
					}

					next = next_converted;
					break;
				}
			}
		}
		while(next_map_name != "location");

		if(debug)
		{
			std::cout << "Location value: " << next << '\n';
		}

		lowest_location_number = std::min(lowest_location_number, next);
	}

	return lowest_location_number;
}

std::list<long long> almanac::get_seeds(std::string line)
{
	char* c_line = &line[0];
	char* next_token;
	char* p = strtok_s(c_line, " ", &next_token);

	int index = 0;
	std::list<long long> seeds = {};

	while(p != nullptr)
	{
		if(index > 0)
		{
			seeds.push_back(atoll(p));
		}

		p = strtok_s(nullptr, " ", &next_token);
		++index;
	}

	return seeds;
}

std::string almanac::parse_direction_map(std::string line, std::map<std::string, std::string>& seed_maps)
{
	char* c_line = &line[0];
	char* next_token;
	char* p = strtok_s(c_line, "-", &next_token);

	int index = 0;
	std::string start;

	while(p != nullptr)
	{
		if(index == 0)
		{
			start = p;
		}
		else if(index == 2)
		{
			p = strtok_s(p, " ", &next_token);
			seed_maps[start] = p;
		}

		p = strtok_s(nullptr, "-", &next_token);
		++index;
	}

	return seed_maps[start];
}

seed_map almanac::get_seed_map(std::string line)
{
	char* c_line = &line[0];
	char* next_token;
	char* p = strtok_s(c_line, " ", &next_token);

	int index = 0;
	seed_map current_seed_map = {};

	while(p != nullptr)
	{
		switch(index)
		{
			case 0:
				current_seed_map.destination_range_start = atoll(p);
				break;
			case 1:
				current_seed_map.source_range_start = atoll(p);
				break;
			case 2:
				current_seed_map.range_length = atoll(p);
				break;
		}

		p = strtok_s(nullptr, " ", &next_token);
		++index;
	}

	return current_seed_map;
}
