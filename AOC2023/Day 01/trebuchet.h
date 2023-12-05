#pragma once
#include <string>
#include "literal_digit.h"

class trebuchet
{
public:
	static int part_one(const std::string& file_name, bool debug = false);
	static int part_two(const std::string& file_name, bool debug = false);

private:
	static int search_for_literals(char ch, literal_digit digits[], int n_of_digits);
	static int search_digit(char ch);
	static void clear_literals(literal_digit digits[], int n_of_digits);
};
