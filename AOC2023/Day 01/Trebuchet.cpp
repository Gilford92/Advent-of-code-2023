#include "Trebuchet.h"
#include <fstream>
#include <iostream>
#include <string>

int Trebuchet::part_one(const std::string& file_name, const bool debug)
{
	int sum = 0;

	std::ifstream input_file(file_name);

	for(std::string line; std::getline(input_file, line);)
	{
		int first = -1, last = -1;

		for(const char& ch : line)
		{
			if(std::isdigit(static_cast<unsigned char>(ch)))
			{
				last = ch - '0';

				if(first == -1)
				{
					first = last;
				}
			}
		}

		sum += first * 10 + last;

		if(debug)
		{
			std::cout << first << ' ' << last << ' ' << sum << '\n';
		}
	}

	return sum;
}
