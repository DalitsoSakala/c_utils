#include "numbers.h"
#include <stdlib.h>

long b_search(long n, const long *arr, size_t s) {
  unsigned long lo = 0, hi = s - 1, m;
  while (hi >= lo) {
    m = (lo + hi) / 2;
    if (n == arr[m])
      return m;
    if (n > arr[m])
      lo = m + 1;
    else
      hi = m - 1;
  }
  return -1 - m;
}

void sort(long *arr, size_t s) {
  long a, *b;
  int i = 1, cascade;
  for (; i < s; i++) {
    b = arr + i;
    cascade = 0;
    do {
      a = arr[i - 1];
      if (a > *b) {
#ifdef DEBUG
        printf("swap a=%d,b=%d,i=%d\n", a, *b, i);
#endif
        cascade = 1;
        swap(arr, i - 1, b - arr);
        b = arr + i - 1;
#ifdef DEBUG
        printf("arr => {");
        for (int x = 0; x < s;)
          printf("%d,", x++[arr]);
        printf("}\n");
#endif
      }
    } while (cascade && --i);
  }
}

void min_pos(long *rs, const long *arr, size_t s) {
  long i = 0, x, n;
  for (n = arr[x = i]; i < s; i++)
    if (n > arr[i])
      n = arr[x = i];

  *rs = n;
  rs[1] = x;
}

void max_pos(long *rs, const long *arr, size_t s) {
  long i = 0, x, n;
  for (n = arr[x = i]; i < s; i++)
    if (n < arr[i])
      n = arr[x = i];

  *rs = n;
  rs[1] = x;
}

void swap(long *a, int i, int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}
