#include "pipe_maze.h"

#include <fstream>
#include <iostream>
#include <list>

#include "pipe.h"

int pipe_maze::part_one(const std::string& file_name, const bool debug)
{
	int longest_distance = 0;

	std::vector<std::vector<pipe>> pipes;
	const pipe start = parse_data(file_name, pipes, debug);

	for(int i = -1; i < 2; ++i)
	{
		if(i == 0)
		{
			for(int j = -1; j < 2; ++j)
			{
				if(j != 0)
				{
					pipe next = {};
					if(is_one_way_connected(start, start, start.position[0], start.position[1] + j, pipes, true, next))
					{
						longest_distance = std::max(longest_distance, detect_loop(start, pipes, next.position[0], next.position[1], false, 0));
					}
				}
			}
		}
		else
		{
			pipe next = {};
			if(is_one_way_connected(start, start, start.position[0] + i, start.position[1], pipes, true, next))
			{
				longest_distance = std::max(longest_distance, detect_loop(start, pipes, next.position[0], next.position[1], false, 0));
			}
		}
	}

	if(debug)
	{
		std::cout << '\n';
	}

	return longest_distance / 2;
}

pipe pipe_maze::parse_data(const std::string& file_name, std::vector<std::vector<pipe>>& pipes, const bool debug)
{
	pipe start = {};

	std::ifstream input_file(file_name);

	int row = 0;
	int column = 0;

	std::list<std::list<pipe>> all_pipes = {};

	for(std::string line; std::getline(input_file, line);)
	{
		column = 0;
		std::list<pipe> pipe_rows = {};

		if(debug)
		{
			std::cout << line << '\n';
		}

		for(const char ch : line)
		{
			int position[2] = {row, column};
			pipe p = pipe::parse(ch, position);

			if(ch == 'S')
			{
				start = p;
				p.visited = true;
			}

			pipe_rows.push_back(p);

			++column;
		}

		all_pipes.push_back(pipe_rows);
		++row;
	}

	pipes.resize(row);
	for(int i = 0; i < row; ++i)
	{
		pipes[i].resize(column);
	}

	int i = 0;

	for(const std::list<pipe>& pipe_rows : all_pipes)
	{
		int j = 0;

		for(const pipe pipe : pipe_rows)
		{
			pipes[i][j] = pipe;
			++j;
		}

		++i;
	}

	if(debug)
	{
		std::cout << '\n';
	}

	return start;
}

int pipe_maze::detect_loop(const pipe& start, std::vector<std::vector<pipe>>& pipes, const int next_row, const int next_column, const bool check_end, const int current_length)
{
	if(start.position[0] == next_row && start.position[1] == next_column)
	{
		return current_length + 1;
	}

	if(pipes[next_row][next_column].visited)
	{
		return -1;
	}

	pipes[next_row][next_column].visited = true;

	pipe next = {};

	if(try_get_next(start, pipes[next_row][next_column], pipes, check_end, next))
	{
		pipes[next_row][next_column].loop = true;
		std::cout << "Going from (" << next_row << ", " << next_column << ") to (" << next.position[0] << ", " << next.position[1] << ")\n";

		return detect_loop(start, pipes, next.position[0], next.position[1], true, current_length + 1);
	}

	return -1;
}

bool pipe_maze::try_get_next(const pipe& start, const pipe& current, const std::vector<std::vector<pipe>>& pipes, const bool check_end, pipe& next)
{
	return is_one_way_connected(start, current, current.first_connection[0], current.first_connection[1], pipes, check_end, next) ||
		is_one_way_connected(start, current, current.second_connection[0], current.second_connection[1], pipes, check_end, next);
}

bool pipe_maze::is_one_way_connected(const pipe& start, const pipe& current, const int next_row, const int next_col, const std::vector<std::vector<pipe>>& pipes, const bool check_end, pipe& next)
{
	if(next_row >= 0 && next_row < pipes.size()
		&& next_col >= 0 && next_col < pipes[next_row].size())
	{
		next = pipes[next_row][next_col];

		if(check_end && (
			(current.first_connection[0] == start.position[0] && current.first_connection[1] == start.position[1])
			|| (current.second_connection[0] == start.position[0] && current.second_connection[1] == start.position[1])
		))
		{
			return true;
		}

		if(next.first_connection[0] == current.position[0] && next.first_connection[1] == current.position[1])
		{
			if(!next.visited)
			{
				return true;
			}
		}

		if(next.second_connection[0] == current.position[0] && next.second_connection[1] == current.position[1])
		{
			return !next.visited;
		}
	}

	return false;
}
