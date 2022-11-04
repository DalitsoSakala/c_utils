#include "strings.h"
#include <ctype.h>
#include <string.h>

int	_is_space(char c)
{
	return (c == SPACE || c == TAB || c == NL);
}

void	to_name(char *raw)
{
	char	c;

	short searching = 1; // Flag whether searching for new word
	for (int i = 0; i < strlen(raw) - 1; i++)
	{
		c = raw[i];
		if (searching)
		{
			if (c == 0 || _is_space(c))
				continue ;
			if (isalpha(c))
				raw[i] = toupper(c); // Convert to uppercase letter
			searching = 0;
		}
		else if (_is_space(c))
			searching = 1;
	}
}

void	to_cap(char *raw)
{
	for (int i = 0; i < strlen(raw) - 1; i++)
		i[raw] = toupper(i[raw]);
}

void	to_camel(char *raw)
{
	short	searching;

	searching = 1;
	for (int i = 0; i < strlen(raw) - 1; i++)
	{
	}
}

void	from_camel(char *raw)
{
}

void	from_camelrp(char *raw, char *spc_replacer)
{
}
