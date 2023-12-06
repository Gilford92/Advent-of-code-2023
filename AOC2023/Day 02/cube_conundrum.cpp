#include "cube_conundrum.h"

#include <fstream>
#include <iostream>

int cube_conundrum::part_one(const std::string& file_name, bool debug)
{
	int ids_sum = 0;

	std::ifstream input_file(file_name);

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << std::endl;
		}

		constexpr int max_blue = 14;
		constexpr int max_green = 13;
		constexpr int max_red = 12;

		int red = 0, green = 0, blue = 0;
		int game_id = 0;

		const std::string game = "Game";
		const std::string red_str = "red";
		const std::string green_str = "green";
		const std::string blue_str = "blue";

		char* c_line = &line[0];
		char* next_token;
		char* p = strtok_s(c_line, " ", &next_token);

		int index = 0;
		int last_amount = 0;

		while(p != nullptr)
		{
			if(index > 0)
			{
				if(index == 1)
				{
					p[std::strlen(p) - 1] = '\0';
					game_id = atoi(p);
				}
				else if(index % 2 == 0)
				{
					last_amount = atoi(p);
				}
				else
				{
					constexpr char semicolon_str = ';';
					constexpr char comma_str = ',';
					unsigned last_p_index = std::strlen(p) - 1;

					if(p[last_p_index] == comma_str || p[last_p_index] == semicolon_str)
					{
						p[last_p_index] = '\0';
					}

					if(p == red_str)
					{
						red = std::max(last_amount, red);
					}
					else if(p == green_str)
					{
						green = std::max(last_amount, green);
					}
					else if(p == blue_str)
					{
						blue = std::max(last_amount, blue);
					}
				}
			}

			p = strtok_s(nullptr, " ", &next_token);
			++index;
		}

		if(red <= max_red && blue <= max_blue && green <= max_green)
		{
			ids_sum += game_id;

			if(debug)
			{
				std::cout << "Added to sum (" << ids_sum << ")\n";
			}
		}
		else
		{
			if(debug)
			{
				if(red > max_red)
				{
					std::cout << "Red too big: " << red << ' ';
				}

				if(green > max_green)
				{
					std::cout << "Green too big: " << green << ' ';
				}

				if(blue > max_blue)
				{
					std::cout << "Blue too big: " << blue << ' ';
				}

				std::cout << std::endl;
			}
		}
	}

	return ids_sum;
}
