#include "play.h"

#include <map>
#include <utility>

void play::init(std::string current_hand, const int current_bid, const bool joker)
{
	hand = std::move(current_hand);
	bid = current_bid;

	if(joker)
	{
		calculate_hand_type_joker();
	}
	else
	{
		calculate_hand_type();
	}
}

void play::calculate_hand_type()
{
	std::map<char, int> occurrences = {};

	for(char c : hand)
	{
		++occurrences[c];
	}

	type = high_card;

	for(std::map<char, int>::iterator it = occurrences.begin(); it != occurrences.end(); ++it)
	{
		switch(it->second)
		{
			case 5:
				type = five_of_a_kind;
				return;
			case 4:
				type = four_of_a_kind;
				return;
			case 3:
				if(type == one_pair)
				{
					type = full_house;
					return;
				}

				type = three_of_a_kind;
				break;
			case 2:
				if(type == three_of_a_kind)
				{
					type = full_house;
					return;
				}

				if(type == one_pair)
				{
					type = two_pair;
					return;
				}

				type = one_pair;
				break;
		}
	}
}

void play::calculate_hand_type_joker()
{
	std::map<char, int> occurrences = {};

	for(char c : hand)
	{
		++occurrences[c];
	}

	if(occurrences['J'] >= 4)
	{
		type = five_of_a_kind;
		return;
	}

	type = high_card;

	for(std::map<char, int>::iterator it = occurrences.begin(); it != occurrences.end(); ++it)
	{
		if(it->first != 'J')
		{
			switch(it->second)
			{
				case 5:
					type = five_of_a_kind;
					return;
				case 4:
					if(occurrences['J'] == 1)
					{
						type = five_of_a_kind;
					}
					else
					{
						type = four_of_a_kind;
					}
					return;
				case 3:
					if(occurrences['J'] == 2)
					{
						type = five_of_a_kind;
						return;
					}

					if(type == one_pair)
					{
						type = full_house;
						return;
					}

					if(occurrences['J'] == 1)
					{
						type = four_of_a_kind;
						return;
					}

					type = three_of_a_kind;
					break;
				case 2:
					if(occurrences['J'] == 3)
					{
						type = five_of_a_kind;
						return;
					}

					if(type == three_of_a_kind)
					{
						type = full_house;
						return;
					}

					if(occurrences['J'] == 2)
					{
						type = four_of_a_kind;
						return;
					}

					if(occurrences['J'] == 1)
					{
						type = three_of_a_kind;
						break;
					}

					if(type == one_pair)
					{
						type = two_pair;
						return;
					}

					type = one_pair;
					break;
			}
		}
	}

	if(type == high_card)
	{
		switch(occurrences['J'])
		{
			case 3:
				type = four_of_a_kind;
				return;
			case 2:
				type = three_of_a_kind;
				return;
			case 1:
				type = one_pair;
				break;
		}
	}
}

int play::compare(const play& other, const bool joker) const
{
	if(type > other.type)
	{
		return 1;
	}

	if(type < other.type)
	{
		return -1;
	}

	if(joker)
	{
		return compare_tie(other, cards_rank_joker_);
	}

	return compare_tie(other, cards_rank_);
}

int play::compare_tie(play other, std::map<char, int> ranks) const
{
	std::string::iterator it = other.hand.begin();

	for(char c : hand)
	{
		if(ranks[c] > ranks[*it])
		{
			return 1;
		}

		if(ranks[c] < ranks[*it])
		{
			return -1;
		}

		++it;
	}

	return 0;
}
