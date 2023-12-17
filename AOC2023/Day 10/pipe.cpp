#include "pipe.h"

pipe pipe::parse(const char ch, int position[2])
{
	pipe p = {{position[0], position[1]}};

	switch(ch)
	{
		case '|':
			p.first_connection[0] = position[0] - 1;
			p.first_connection[1] = position[1];
			p.second_connection[0] = position[0] + 1;
			p.second_connection[1] = position[1];
			break;
		case '-':
			p.first_connection[0] = position[0];
			p.first_connection[1] = position[1] - 1;
			p.second_connection[0] = position[0];
			p.second_connection[1] = position[1] + 1;
			break;
		case 'L':
			p.first_connection[0] = position[0] - 1;
			p.first_connection[1] = position[1];
			p.second_connection[0] = position[0];
			p.second_connection[1] = position[1] + 1;
			break;
		case 'J':
			p.first_connection[0] = position[0] - 1;
			p.first_connection[1] = position[1];
			p.second_connection[0] = position[0];
			p.second_connection[1] = position[1] - 1;
			break;
		case '7':
			p.first_connection[0] = position[0];
			p.first_connection[1] = position[1] - 1;
			p.second_connection[0] = position[0] + 1;
			p.second_connection[1] = position[1];
			break;
		case 'F':
			p.first_connection[0] = position[0];
			p.first_connection[1] = position[1] + 1;
			p.second_connection[0] = position[0] + 1;
			p.second_connection[1] = position[1];
			break;
		default:
			break;
	}

	return p;
}
