#include "trebuchet.h"
#include <fstream>
#include <iostream>
#include <string>

int trebuchet::part_one(const std::string& file_name, const bool debug)
{
	int sum = 0;

	std::ifstream input_file(file_name);

	for(std::string line; std::getline(input_file, line);)
	{
		int first = -1, last = -1;

		for(const char& ch : line)
		{
			const int result = search_digit(ch);

			if(result != -1)
			{
				last = result;

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


int trebuchet::part_two(const std::string& file_name, const bool debug)
{
	constexpr int n_of_digits = 9;
	literal_digit digits[n_of_digits] =
	{
		{"one"},
		{"two"},
		{"three"},
		{"four"},
		{"five"},
		{"six"},
		{"seven"},
		{"eight"},
		{"nine"}
	};

	int sum = 0;

	std::ifstream input_file(file_name);

	for(std::string line; std::getline(input_file, line);)
	{
		int first = -1, last = -1;
		clear_literals(digits, n_of_digits);

		if(debug)
		{
			std::cout << line << ' ';
		}

		for(const char& ch : line)
		{
			int result = search_digit(ch);

			if(result != -1)
			{
				clear_literals(digits, n_of_digits);
			}
			else
			{
				result = search_for_literals(ch, digits, n_of_digits);
			}

			if(result != -1)
			{
				last = result;

				if(first == -1)
				{
					first = last;
				}

				if(debug)
				{
					std::cout << '(' << first << last << ") ";
				}
			}
		}

		const int partial = first * 10 + last;
		sum += partial;

		if(debug)
		{
			std::cout << first << ' ' << last << ' ' << partial << ' ' << sum << '\n';
		}
	}

	return sum;
}

int trebuchet::search_digit(const char ch)
{
	if(std::isdigit(static_cast<unsigned char>(ch)))
	{
		return ch - '0';
	}

	return -1;
}

int trebuchet::search_for_literals(const char ch, literal_digit digits[], const int n_of_digits)
{
	int result = -1;

	for(int i = 0; i < n_of_digits; ++i)
	{
		if(digits[i].parse(ch))
		{
			digits[i].index = 0;
			result = i + 1;
		}
	}

	return result;
}

void trebuchet::clear_literals(literal_digit digits[], const int n_of_digits)
{
	for(int i = 0; i < n_of_digits; ++i)
	{
		digits[i].index = 0;
	}
}
