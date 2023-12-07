#include "scratchcards.h"

#include <fstream>
#include <iostream>
#include <list>

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
