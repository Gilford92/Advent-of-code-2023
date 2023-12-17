#pragma once
#include <string>
#include <vector>

#include "pipe.h"

class pipe_maze
{
public:
	static int part_one(const std::string& file_name, bool debug = false);

private:
	static pipe parse_data(const std::string& file_name, std::vector<std::vector<pipe>>& pipes, bool debug);
	static int detect_loop(const pipe& start, std::vector<std::vector<pipe>>& pipes, int next_row, int next_column, bool check_end, int current_length);
	static bool try_get_next(const pipe& start, const pipe& current, const std::vector<std::vector<pipe>>& pipes, bool check_end, pipe& next);
	static bool is_one_way_connected(const pipe& start, const pipe& current, int next_row, int next_col, const std::vector<std::vector<pipe>>& pipes, bool check_end, pipe& next);
};
