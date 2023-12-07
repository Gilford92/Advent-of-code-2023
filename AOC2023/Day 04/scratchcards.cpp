#include "scratchcards.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>

int scratchcards::part_one(const std::string& file_name, const bool debug)
{
	int points_sum = 0;

	std::ifstream input_file(file_name);

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		const std::string separator = "|";

		char* c_line = &line[0];
		char* next_token;
		char* p = strtok_s(c_line, " ", &next_token);

		int index = 0;
		bool winning_column = true;
		std::list<int> winning_numbers = {};
		int points = 0;

		while(p != nullptr)
		{
			if(index > 1)
			{
				if(p == separator)
				{
					winning_column = false;
				}
				else if(winning_column)
				{
					winning_numbers.push_back(atoi(p));
				}
				else
				{
					const int current_number = atoi(p);

					for(const int winning_number : winning_numbers)
					{
						if(winning_number == current_number)
						{
							if(points == 0)
							{
								points = 1;
							}
							else
							{
								points *= 2;
							}

							if(debug)
							{
								std::cout << "Found winning number: " << current_number << '\n';
								std::cout << "Points: " << points << " (" << points_sum << ")\n";
							}

							break;
						}
					}
				}
			}

			p = strtok_s(nullptr, " ", &next_token);
			++index;
		}

		points_sum += points;
	}

	return points_sum;
}

int scratchcards::part_two(const std::string& file_name, const bool debug)
{
	int scratchcards_count = 0;
	std::map<int, int> scratchcards_copies = {};

	std::ifstream input_file(file_name);

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		const std::string separator = "|";

		char* c_line = &line[0];
		char* next_token;
		char* p = strtok_s(c_line, " ", &next_token);

		int index = 0;
		bool winning_column = true;
		std::list<int> winning_numbers = {};
		int game_id = 0;
		int copy_index = 0;

		while(p != nullptr)
		{
			if(index > 0)
			{
				if(index == 1)
				{
					game_id = atoi(p);
					scratchcards_count += scratchcards_copies[game_id] + 1;

					if(debug)
					{
						std::cout << "Game id: " << game_id << ". Current copies: " << scratchcards_copies[game_id] + 1 << ". Total copies : " << scratchcards_count << '\n';
					}
				}
				else if(p == separator)
				{
					winning_column = false;
				}
				else if(winning_column)
				{
					winning_numbers.push_back(atoi(p));
				}
				else
				{
					const int current_number = atoi(p);

					for(const int winning_number : winning_numbers)
					{
						if(winning_number == current_number)
						{
							++copy_index;
							scratchcards_copies[game_id + copy_index] += scratchcards_copies[game_id] + 1;

							break;
						}
					}
				}
			}

			p = strtok_s(nullptr, " ", &next_token);
			++index;
		}
	}

	return scratchcards_count;
}
