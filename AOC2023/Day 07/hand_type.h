#pragma once

enum hand_type
{
	high_card,
	one_pair,
	two_pair,
	three_of_a_kind,
	full_house,
	four_of_a_kind,
	five_of_a_kind
};

static std::string hand_type_str(const hand_type type)
{
	switch(type)
	{
		case high_card:
			return "High card";
		case one_pair:
			return "One pair";
		case two_pair:
			return "Two pair";
		case three_of_a_kind:
			return "Three of a kind";
		case full_house:
			return "Full house";
		case four_of_a_kind:
			return "Four of a kind";
		case five_of_a_kind:
			return "Five of a kind";
	}

	return "Unknown";
}
