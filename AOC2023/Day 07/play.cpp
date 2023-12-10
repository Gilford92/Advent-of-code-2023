#include "play.h"

#include <map>
#include <utility>

void play::init(std::string current_hand, const int current_bid)
{
	hand = std::move(current_hand);
	bid = current_bid;
	calculate_hand_type();
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

int play::compare(play other)
{
	if(type > other.type)
	{
		return 1;
	}

	if(type < other.type)
	{
		return -1;
	}

	std::string::iterator it = other.hand.begin();
	for(char c : hand)
	{
		if(cards_rank_[c] > cards_rank_[*it])
		{
			return 1;
		}

		if(cards_rank_[c] < cards_rank_[*it])
		{
			return -1;
		}

		++it;
	}

	return 0;
}
