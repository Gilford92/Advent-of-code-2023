#include "literal_digit.h"

bool literal_digit::parse(const char ch)
{
	if(index < word.length())
	{
		if(std::tolower(ch) == word[index])
		{
			++index;
		}
		else
		{
			if(std::tolower(ch) == word[0])
			{
				index = 1;
			}
			else
			{
				index = 0;
			}
		}
	}

	return index == word.length();
}
