#include "numbers.h"
#include <stdlib.h>
#include<string.h>

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
double lagrange(double x,const double *table,size_t size){
	double (*tab)[size][2]=(double(*)[size][2])table;
	int i=0,j;
	double n,ni,fx,top,bot,tot=0;
	for(;i<size;){
	  n=*(*tab)[i];
	  fx=(*tab)[i++][1];
	  top=bot=1;
	  for(j=0;j<size;){
	   ni=*(*tab)[j++];
	   if(n==ni) continue;
	   top*=x-ni;
	   bot*=n-ni;
	  }
	  tot+=(top/bot)*fx;
	}
	return tot;
}

int mat_mult(double *result, const double *mta, const double *mtb, int ra,
              int ca, int rb, int cb) {
  double(*rs)[ra][cb];
  double(*ma)[ra][ca] = (double(*)[ra][ca])mta;
  double(*mb)[rb][cb] = (double(*)[rb][cb])mtb;

  int c = 0, r = 0, C = 0;
  double sum = 0;
  if (ca != rb) {
    return 0;
  }
  rs = (double(*)[ra][cb])result;
  for (; r < ra;) {
    sum = 0;
    for (c = 0; c < ca;) {
      double mcnd = (*ma)[r][c];
      double mlr = (*mb)[c++][C];
      sum += mlr * mcnd;
    }
    (*rs)[r++][C] = sum;
    if (r == ra && C + 1 < cb) {
      C++;
      r = 0;
    }
  }
  return 1;
}

void mat_tostr(char *to, const double *arr, size_t rows, size_t cols,
               int digits) {
  double(*ptr)[rows][cols];
  int i = 0;
  ptr = (double(*)[rows][cols])arr;
  strcat(to, "{\n");
  for (i = 0; i < rows; i++) {
    strcat(to, " { ");
    for (int x = 0; x < cols;) {
      char d[digits + 1];
      snprintf(d, digits, "%lf", (*ptr)[i][x]);
      strcat(to, d);
      if (++x != cols)
        strcat(to, ", ");
    }
    strcat(to, " }\n");
  }
  strcat(to, "}");
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
