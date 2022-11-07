#include <stdlib.h>
// modifies `rs` with
// `[0] - maximum number in a`
// `[1] - index in a of size s`
void	max_pos(long *rs, const long *a, size_t s);

// Modifies `rs` with
// `[0] - minimum number`
// `[1] - index in a of size s`
void	min_pos(long *rs, const long *a, size_t s);

// Perform a binary search with `n` on `a`
// of size `s`
long	b_search(long n, const long *a, size_t s);

// Swap values `a[i]` and `a[j]`
void	swap(long *a, int i, int j);

// Sort `a` of size `s` in ascending order
void	sort(long *a, size_t s);

// Multiply matrix `a` and `b` returning
// a pointer to the result to res such that it is
// 0 if `a` & `b` are not compatible.
void mat_mult(double* result,const double *a,const  double *b,int ra,int ca,int rb,int cb);

// presents multidementional array `from` as a string
// in initialized string `to`
void mat_tostr(char* to,const double *from,size_t r,size_t c,int digits);
