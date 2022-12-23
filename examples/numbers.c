#include "numbers.h"
#include <stdio.h>

int main(void) {
  size_t s;
  long min[2];
  long max[2];

  double tbl[][2] = {{2, 5}, {3, 10}, {4, 17}, {5, 26}};

  const double mata[][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  const double matb[][3] = {{8, 0, 3}, {9, 4, 1}, {1, 2, 5}};
  double matr[3][3];
  char mstra[150];
  char mstrb[150];
  char mstrr[150];

  long int b_search_position;
  long lst[] = {5, 28, 11, 9, 7, 1, 3, 2, 16, 0, 30, 22, 10, 4, 1};

  // Sorting a list
  s = sizeof(lst) / sizeof(lst[0]);
  sort(lst, s);
  printf("\nThe sorted list is:\n");
  for (int i = 0; i < s; i++)
    printf("%ld, ", lst[i]);

  // Binary search
  b_search_position = b_search(22, lst, s);
  printf("\n\nPosition of 22 after bunary search is: %ld\n", b_search_position);

  // Finding min and max in an array
  min_pos(min, lst, s);
  max_pos(max, lst, s);
  printf("\n\nMin and Max are %ld at %ld and %ld at %ld\n", *min, min[1], *max,
         max[1]);

  // Matrix multiplication
  mat_mult(&matr, &mata, &matb, 3, 3, 3, 3);

  mat_tostr(mstra, &mata, 3, 3, 4);
  mat_tostr(mstrb, &matb, 3, 3, 4);
  mat_tostr(mstrr, &matr, 3, 3, 4);

  printf("\nMultiplying matrix %s\nand %s\ngives %s\n", mstra, mstrb, mstrr);

  // lagrange
  double lg = lagrange(2.5, &tbl, 4);
  printf("\nla grange: (2.5, %lf)\n", lg);
  return (0);
}
