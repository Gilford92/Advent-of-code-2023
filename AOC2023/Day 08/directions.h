#pragma once
#include <map>
#include <string>

struct directions
{
public:
	void init(const std::string& current_node, const std::string& left, const std::string& right);

	std::string current;
	std::map<char, std::string> next;
};
