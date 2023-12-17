#pragma once

struct pipe
{
public:
	int position[2] = {0, 0};
	int first_connection[2] = {0, 0};
	int second_connection[2] = {0, 0};
	bool visited = false;
	bool loop = false;

	static pipe parse(char ch, int position[2]);

	bool operator==(const pipe& rhs) const
	{
		return this->position[0] == rhs.position[0]
			&& this->position[1] == rhs.position[1];
	}
};
