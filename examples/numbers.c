#include "numbers.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	long		lst[];
	int			s;
	long		min[2];
	long		max[2];
	long int	p;

	lst[] = {5, 28, 11, 9, 7, 1, 3, 2, 16, 0, 30, 22, 10, 4, 1};
	s = sizeof(lst) / sizeof(long);
	sort(lst, s);
	min_pos(min, lst, s);
	max_pos(max, lst, s);
	for (int i = 0; i < s; i++)
		printf("%ld, ", lst[i]);
	p = b_search(22, lst, s);
	printf("\npos of 22: %ld\n", p);
	printf("Min and Max are %ld at %ld and %ld at %ld\n", *min, min[1], *max,
			max[1]);
	return (0);
}
