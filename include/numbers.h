
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
void	sort(long *, size_t);
