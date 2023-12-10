#include "camel_cards.h"

#include <fstream>
#include <iostream>
#include <list>

int camel_cards::part_one(const std::string& file_name, const bool debug)
{
	const std::list<play> plays = parse_plays(file_name, false, debug);
	const std::list<play> ordered_plays = get_ordered_plays(plays, false, debug);
	return calculate_total_winnings(ordered_plays, debug);
}

int camel_cards::part_two(const std::string& file_name, const bool debug)
{
	const std::list<play> plays = parse_plays(file_name, true, debug);
	const std::list<play> ordered_plays = get_ordered_plays(plays, true, debug);
	return calculate_total_winnings(ordered_plays, debug);
}

std::list<play> camel_cards::parse_plays(const std::string& file_name, const bool joker, const bool debug)
{
	std::list<play> plays = {};

	std::ifstream input_file(file_name);

	for(std::string line; std::getline(input_file, line);)
	{
		if(debug)
		{
			std::cout << line << '\n';
		}

		plays.push_back(parse_play(line, joker));
	}

	if(debug)
	{
		std::cout << '\n';
	}

	return plays;
}

play camel_cards::parse_play(std::string line, const bool joker)
{
	play parsed_play = {};

	char* c_line = &line[0];
	char* next_token;
	char* p = strtok_s(c_line, " ", &next_token);

	int index = 0;
	std::string hand;
	int bid = 0;

	while(p != nullptr)
	{
		switch(index)
		{
			case 0:
				hand = p;
				break;
			case 1:
				bid = atoi(p);
				break;
		}

		p = strtok_s(nullptr, " ", &next_token);
		++index;
	}

	parsed_play.init(hand, bid, joker);
	return parsed_play;
}

std::list<play> camel_cards::get_ordered_plays(const std::list<play>& plays, const bool joker, const bool debug)
{
	std::list<play> ordered_plays = {};

	for(play unordered_play : plays)
	{
		if(debug)
		{
			std::cout << "Hand " << unordered_play.hand << " with bid " << unordered_play.bid << ". Hand type: " << hand_type_str(unordered_play.type) << '\n';
		}

		bool added = false;

		for(std::list<play>::iterator it = ordered_plays.begin(); it != ordered_plays.end(); ++it)
		{
			if(unordered_play.compare(*it, joker) < 0)
			{
				ordered_plays.insert(it, unordered_play);
				added = true;
				break;
			}
		}

		if(!added)
		{
			ordered_plays.push_back(unordered_play);
		}
	}

	return ordered_plays;
}

int camel_cards::calculate_total_winnings(const std::list<play>& ordered_plays, const bool debug)
{
	int total_winnings = 0;

	if(debug)
	{
		std::cout << '\n' << "Sorted hands" << '\n';
	}

	int i = 1;
	for(const play& ordered_play : ordered_plays)
	{
		if(debug)
		{
			std::cout << ordered_play.hand << " " << ordered_play.bid << " " << hand_type_str(ordered_play.type) << '\n';
		}

		total_winnings += i * ordered_play.bid;
		++i;
	}

	if(debug)
	{
		std::cout << '\n';
	}

	return total_winnings;
}
