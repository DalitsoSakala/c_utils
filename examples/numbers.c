#include "numbers.h"
#include <stdio.h>

int main(void) {
  size_t s;
  long min[2];
  long max[2];
  const double mata[][2]={{1,0},{0,1}};
  const double matb[][2]={{8,0},{9,4}};
  double matr[2][2];
  long int p;
  char mstr[50];
  long lst[] = {5, 28, 11, 9, 7, 1, 3, 2, 16, 0, 30, 22, 10, 4, 1};

  s = sizeof(lst) / sizeof(lst[0]);
  sort(lst, s);
  min_pos(min, lst, s);
  max_pos(max, lst, s);
  for (int i = 0; i < s; i++)
    printf("%ld, ", lst[i]);
  p = b_search(22, lst, s);
  printf("\npos of 22: %ld\n", p);
  printf("Min and Max are %ld at %ld and %ld at %ld\n", *min, min[1], *max,
         max[1]);
  mat_mult(&matr,&mata,&matb,2,2,2,2);
  mat_tostr(mstr,&matr,2,2,3);
  printf("%s\n",mstr);
  return (0);
}
