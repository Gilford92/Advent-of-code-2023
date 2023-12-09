#include "almanac.h"

#include <fstream>
#include <iostream>

long long almanac::part_one(const std::string& file_name, const bool debug)
{
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


	return get_lowest_location_number(seeds, seed_maps, seed_values, debug);
}

long long almanac::part_two(const std::string& file_name, const bool debug)
{
	std::ifstream input_file(file_name);

	std::list<std::pair<long long, long long>> seeds = {};

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
			seeds = get_seeds_range(line);
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
				order_maps(seed_values[current_map_name]);
				direction_map_line = true;
			}
		}

		++line_counter;
	}

	if(debug)
	{
		std::cout << '\n';
	}

	order_maps(seed_values[current_map_name]);
	return get_lowest_location_number_range(seeds, seed_maps, seed_values, debug);
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

std::list<std::pair<long long, long long>> almanac::get_seeds_range(std::string line)
{
	char* c_line = &line[0];
	char* next_token;
	char* p = strtok_s(c_line, " ", &next_token);

	int index = 0;
	std::list<std::pair<long long, long long>> seeds = {};
	long long seed_start = 0;

	while(p != nullptr)
	{
		if(index > 0)
		{
			if(index % 2 != 0)
			{
				seed_start = atoll(p);
			}
			else
			{
				seeds.emplace_back(seed_start, atoll(p));
			}
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

long long almanac::get_lowest_location_number(const std::list<long long>& seeds, std::map<std::string, std::string> seed_maps, std::map<std::string, std::list<seed_map>> seed_values, const bool debug)
{
	long long lowest_location_number = LLONG_MAX;

	for(const long long seed : seeds)
	{
		long long next = seed;
		std::string next_map_name = "seed";
		std::list<seed_map> current_seed_values;

		do
		{
			next_map_name = seed_maps[next_map_name];
			current_seed_values = seed_values[next_map_name];

			for(const seed_map seed_map : current_seed_values)
			{
				if(next >= seed_map.source_range_start && next <= seed_map.source_range_start + seed_map.range_length)
				{
					const long long next_converted = seed_map.destination_range_start + (next - seed_map.source_range_start);

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

long long almanac::get_lowest_location_number_range(const std::list<std::pair<long long, long long>>& seeds, std::map<std::string, std::string> seed_maps, std::map<std::string, std::list<seed_map>> seed_values, const bool debug)
{
	std::string next_map_name = "seed";

	std::map<std::string, std::string> seed_maps_backward = {};

	do
	{
		seed_maps_backward[seed_maps[next_map_name]] = next_map_name;
		next_map_name = seed_maps[next_map_name];
	}
	while(next_map_name != "location");

	for(const seed_map current_map : seed_values[next_map_name])
	{
		const long long min = current_map.source_range_start;
		const long long max = current_map.source_range_start + current_map.range_length - 1;
		std::list<std::pair<long long, long long>> desired = {std::pair<long long, long long>{min, max}};

		recur(seed_maps_backward[next_map_name], seed_values, seed_maps_backward, desired);

		for(const std::pair<long long, long long> d : desired)
		{
			if(debug)
			{
				std::cout << "Desired seeds: " << d.first << " " << d.second << '\n';
			}

			for(const std::pair<long long, long long> seed : seeds)
			{
				if(seed.first >= d.first && seed.first <= d.second)
				{
					if(debug)
					{
						std::cout << "Found seed: " << seed.first << '\n';
					}

					return get_lowest_location_number(std::list<long long>{seed.first}, seed_maps, seed_values, debug);
				}
				if(seed.first < d.first && seed.first + seed.second >= d.first)
				{
					if(debug)
					{
						std::cout << "Found seed: " << d.first << '\n';
					}

					return get_lowest_location_number(std::list<long long>{d.first}, seed_maps, seed_values, debug);
				}
			}
		}
	}

	return -1;
}

void almanac::order_maps(std::list<seed_map>& unordered_maps)
{
	long long remaining_range = LLONG_MAX;

	std::list<seed_map> ordered_dest_map = {};

	for(seed_map location_map : unordered_maps)
	{
		bool inserted = false;
		std::list<seed_map>::iterator it = ordered_dest_map.begin();
		for(const seed_map ordered_map : ordered_dest_map)
		{
			if(location_map.destination_range_start < ordered_map.destination_range_start)
			{
				ordered_dest_map.insert(it, location_map);
				inserted = true;
				remaining_range -= location_map.range_length;
				break;
			}
			++it;
		}
		if(!inserted)
		{
			ordered_dest_map.push_back(location_map);
			remaining_range -= location_map.range_length;
		}
	}

	const seed_map first_element = ordered_dest_map.front();
	if(first_element.destination_range_start > 0)
	{
		const seed_map zero_map = {0, 0, first_element.destination_range_start};
		ordered_dest_map.push_front(zero_map);
	}

	auto previous_location_map = ordered_dest_map.front();
	std::list<seed_map>::iterator it = ordered_dest_map.begin();
	for(const seed_map location_map : ordered_dest_map)
	{
		if(it != ordered_dest_map.begin())
		{
			if(previous_location_map.destination_range_start + previous_location_map.range_length != location_map.destination_range_start)
			{
				//There is an hole in the map
				seed_map map_to_insert =
				{
					previous_location_map.destination_range_start + previous_location_map.range_length,
					previous_location_map.destination_range_start + previous_location_map.range_length,
					location_map.destination_range_start - (previous_location_map.destination_range_start + previous_location_map.range_length)
				};
				ordered_dest_map.insert(it, map_to_insert);
			}
		}

		previous_location_map = location_map;
		++it;
	}

	const seed_map last_element = ordered_dest_map.back();
	const seed_map end_map = {last_element.destination_range_start + last_element.range_length, last_element.destination_range_start + last_element.range_length, remaining_range};
	ordered_dest_map.push_back(end_map);

	unordered_maps = ordered_dest_map;
}

void almanac::recur(const std::string& previous_map_name, std::map<std::string, std::list<seed_map>> seed_values, std::map<std::string, std::string>& seed_maps_backward, std::list<std::pair<long long, long long>>& desired)
{
	if(previous_map_name == "seed")
	{
		return;
	}

	std::list<std::pair<long long, long long>> current_desired = {};

	for(std::pair<long long, long long> d : desired)
	{
		for(const seed_map previous_map : seed_values[previous_map_name])
		{
			if(d.first >= previous_map.destination_range_start
				&& d.first <= previous_map.destination_range_start + previous_map.range_length - 1)
			{
				long long min = d.first - previous_map.destination_range_start + previous_map.source_range_start;
				long long max_one = d.second - previous_map.destination_range_start + previous_map.source_range_start;
				long long max_two = previous_map.source_range_start + previous_map.range_length - 1;

				current_desired.emplace_back(min, std::min(max_one, max_two));

				const long long last_range_value = previous_map.destination_range_start + previous_map.range_length - 1;
				const long long remaining_min = d.second - last_range_value;

				if(remaining_min > 0)
				{
					d.first = previous_map.destination_range_start + previous_map.range_length;
				}
				else
				{
					break;
				}
			}
		}
	}

	desired = current_desired;
	return recur(seed_maps_backward[previous_map_name], seed_values, seed_maps_backward, desired);
}
