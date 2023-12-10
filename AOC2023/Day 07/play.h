#pragma once
#include <map>
#include <string>

#include "hand_type.h"

struct play
{
public:
	void init(std::string current_hand, int current_bid, bool joker);
	int compare(const play& other, bool joker) const;

	std::string hand;
	int bid;
	hand_type type;

private:
	void calculate_hand_type();
	void calculate_hand_type_joker();
	int compare_tie(play other, std::map<char, int> ranks) const;

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

	std::map<char, int> cards_rank_joker_ =
	{
		{'J', 0},
		{'2', 1},
		{'3', 2},
		{'4', 3},
		{'5', 4},
		{'6', 5},
		{'7', 6},
		{'8', 7},
		{'9', 8},
		{'T', 9},
		{'Q', 10},
		{'K', 11},
		{'A', 12}
	};
};
