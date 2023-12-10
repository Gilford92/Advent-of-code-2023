#pragma once
#include <map>
#include <string>

#include "hand_type.h"

struct play
{
public:
	void init(std::string current_hand, int current_bid);
	int compare(play other);

	std::string hand;
	int bid;
	hand_type type;

private:
	void calculate_hand_type();

	std::map<char, int> cards_rank_ =
	{
		{'2', 0},
		{'3', 1},
		{'4', 2},
		{'5', 3},
		{'6', 4},
		{'7', 5},
		{'8', 6},
		{'9', 7},
		{'T', 8},
		{'J', 9},
		{'Q', 10},
		{'K', 11},
		{'A', 12}
	};
};
