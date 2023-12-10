#pragma once
#include <list>
#include <string>

#include "play.h"

class camel_cards
{
public:
	static int part_one(const std::string& file_name, bool debug = false);
	static int part_two(const std::string& file_name, bool debug = false);

private:
	static std::list<play> parse_plays(const std::string& file_name, bool joker, bool debug);
	static play parse_play(std::string line, bool joker);
	static std::list<play> get_ordered_plays(const std::list<play>& plays, bool joker, bool debug);
	static int calculate_total_winnings(const std::list<play>& ordered_plays, bool debug);
};
