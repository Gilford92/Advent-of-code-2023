#include "gear_ratios.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>

int gear_ratios::part_one(const std::string& file_name, const bool debug)
{
	int numbers_sum = 0;

	std::ifstream input_file(file_name);

	int row = 0;
	std::list<engine_value> engine_values = {};
	std::map<int, std::list<int>> symbols_coordinates = {};

	for(std::string line; std::getline(input_file, line);)
	{
		parse(line, row, engine_values, symbols_coordinates, debug);
		++row;
	}


	for(const engine_value& engine_value : engine_values)
	{
		if(!find_adjacent_symbol(symbols_coordinates, engine_value.row, engine_value, numbers_sum, debug))
		{
			if(!find_adjacent_symbol(symbols_coordinates, engine_value.row - 1, engine_value, numbers_sum, debug))
			{
				if(!find_adjacent_symbol(symbols_coordinates, engine_value.row + 1, engine_value, numbers_sum, debug))
				{
					if(debug)
					{
						std::cout << "Not added : " << engine_value.number << '\n';
					}
				}
			}
		}
	}

	return numbers_sum;
}

void gear_ratios::parse(const std::string& line, const int row, std::list<engine_value>& engine_values, std::map<int, std::list<int>>& symbols_coordinates, const bool debug)
{
	if(debug)
	{
		std::cout << line << '\n';
	}

	int column = 0;
	engine_value last_value;

	for(const char& ch : line)
	{
		constexpr char dot = '.';

		if(ch == dot)
		{
			store_engine_value(last_value, engine_values);
		}
		else if(std::isdigit(static_cast<unsigned char>(ch)))
		{
			if(last_value.number == -1)
			{
				last_value.row = row;
				last_value.number = 0;
			}

			last_value.number = (last_value.number * 10) + (ch - '0');
			last_value.columns.push_back(column);
		}
		else
		{
			symbols_coordinates[row].push_back(column);
			store_engine_value(last_value, engine_values);
		}

		++column;
	}

	store_engine_value(last_value, engine_values);
}

void gear_ratios::store_engine_value(engine_value& value_to_store, std::list<engine_value>& engine_values)
{
	if(value_to_store.number > 0)
	{
		engine_values.push_back(value_to_store);
		value_to_store.reset();
	}
}

bool gear_ratios::find_adjacent_symbol(std::map<int, std::list<int>> symbols_coordinates, const int row_to_search, const engine_value& engine_value, int& numbers_sum, const bool debug)
{
	const auto search = symbols_coordinates.find(row_to_search);

	if(search != symbols_coordinates.end())
	{
		for(const int column : engine_value.columns)
		{
			for(const int symbol_column : search->second)
			{
				if(column == symbol_column || column + 1 == symbol_column || column - 1 == symbol_column)
				{
					numbers_sum += engine_value.number;

					if(debug)
					{
						std::cout << "Found adjacent symbol (" << engine_value.row << ", " << symbol_column << ") (" << engine_value.row << ", " << column << ")\n";
						std::cout << "Engine value : " << engine_value.number << " (" << numbers_sum << ")\n";
					}

					return true;
				}
			}
		}
	}

	return false;
}
