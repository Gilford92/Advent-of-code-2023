#pragma once
#include <list>

struct engine_value
{
public:
	void reset();

	int row = -1;
	std::list<int> columns = {};
	int number = -1;
};
