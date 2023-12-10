#include "directions.h"

void directions::init(const std::string& current_node, const std::string& left, const std::string& right)
{
	current = current_node;
	next['L'] = left;
	next['R'] = right;
}
