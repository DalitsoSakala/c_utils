#include "include/modular.h"
#include <math.h>
#ifdef DEBUG
#include <stdio.h>
#endif

ulong_t gcd(ulong_t a, ulong_t b) {
  if (!b)
    return a;
  return gcd(b, a % b);
}

ulong_t mod_pow(ulong_t a, ulong_t exp, ulong_t mod) {
  ulong_t b = 1 % mod;
  a = a % mod;
  while (exp > 0) {
    if (exp % 2 == 1)
      b = (a * b) % mod;
    exp /= 2;
    a = (a * a) % mod;
  }
  return b;
}

int make_d(ulong_t *d, const struct RSACfg *cfg) {
  if (!valid_rsa(cfg))
    return -1;
  const ulong_t p = cfg->p, q = cfg->q, e = cfg->e, n = p * q,
              t = (p - 1) * (q - 1);
#ifdef DEBUG
  printf("info: solving '%ld x d = 1 (mod %ld)' using `make_d(long*, const "
         "struct RSACfg*)`\n",
         e, t);
#endif
  for (ulong_t i = 1; i < t; i++) {

    if ((i * e) % t == 1 && gcd(i, t) == 1) {
      *d = i;
      return 0;
    }
  }
#ifdef DEBUG
  fprintf(stderr,
          "error: %ld could not be used to calculate 'd' with totient %ld\n", e,
          t);
#endif
  return 1; // not invertible
}

int mod_inv(ulong_t *inv, const ulong_t a, const ulong_t n) {
  ulong_t t = 0, newt = 1;
  ulong_t r = n, newr = a;

  while (newr) {
    ulong_t quotient = r / newr, tmp = t;
    t = newt;
    newt = tmp - quotient * newt;
    tmp = r;
    r = newr;
    newr = tmp - quotient * newr;
  }

  if (r > 1)
    return 1;

  if (t < 0)
    t += n;

  *inv = t;
  return 0;
}

int valid_rsa(const struct RSACfg *c) {
  const ulong_t *e = &c->e, *p = &c->p, *q = &c->q, n = *p * (*q),
              m = (*p - 1) * (*q - 1);
  int pass_1 = gcd(*p, *q) == 1, pass_2 = gcd(m, *e) == 1,
      pass_3 = gcd(n, *e) == 1, pass_4 = *e > 0 && *e < (*p * (*q)), pass_5 = 1;

  if (c->d)
    pass_5 = gcd(c->d, m) == 1;

  return pass_1 & pass_2 & pass_3 & pass_4 & pass_5;
}

int encrypt(ulong_t *M, const ulong_t m, const struct RSACfg *r) {
  if (!valid_rsa(r))
    return 1;
  *M = mod_pow(m, r->e, r->p * r->q);
  return 0;
}

int decrypt(ulong_t *m, const ulong_t M, const struct RSACfg *r) {
  ulong_t d = r->d;
  const ulong_t *p = &r->p, *q = &r->q, *e = &r->e;
  if (!valid_rsa(r)) {
#ifdef DEBUG
    fprintf(stderr, "error: RSACfg is not valid (%s:%d)\n", __FILE__, __LINE__);
#endif
    return 1;
  }
  if (!d) {
    if (mod_inv(&d, *e, (*p - 1) * (*q - 1))) {
#ifdef DEBUG
      fprintf(stderr, "error: 'd' is not invertible '*m' not assigned\n");
#endif
      return 2;
    }
  }
  *m = mod_pow(M, d, *p * (*q));

  return 0;
}
