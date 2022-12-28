#include "include/modular.h"
#include <math.h>
#ifdef DEBUG
#include <stdio.h>
#endif

int is_prime(const ulong_t n) {
  if (n == 2 || n == 3)
    return 1;
  if (n <= 1 || n % 2 == 0 || n % 3 == 0)
    return 0;
  for (ulong_t x = 5; x * x < n;) {
    if (x % n || (x + 2) % n)
      x += 6;
    else
      return 0;
  }
  return 1;
}

ulong_t gcd(ulong_t a, ulong_t b) {
  if (!b)
    return a;
  return gcd(b, a % b);
}

ulong_t mod_pow(ulong_t a, ulong_t exp, const ulong_t mod) {
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
  int code;
  if (code=valid_rsa(cfg))
    return code;
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
      return code;
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
                t = (*p - 1) * (*q - 1);
  int pass_p = is_prime(*p), pass_q = is_prime(*q), pass_pq = *p != *q,
      pass_et = gcd(t, *e) == 1, pass_er = *e > 0 && *e < n, pass_dt = 1,
      ret = RSA_OK;

  if (c->d)
    pass_dt = gcd(c->d, t) == 1;

  if (!pass_p)
    ret |= RSA_P_PRIME;
  if (!pass_q)
    ret |= RSA_Q_PRIME;
  if (!pass_pq)
    ret |= RSA_PQ_EQ;
  if (!pass_et)
    ret |= RSA_ET_COPRIME;
  if (!pass_er)
    ret |= RSA_E_OUT_OF_RANGE;
  if (!pass_dt)
    ret |= RSA_DT_COPRIME;
  return ret;
}

int encrypt(ulong_t *M, const ulong_t m, const struct RSACfg *r) {
  int code;
  if (code=valid_rsa(r)){
#ifdef DEBUG
    fprintf(stderr, "error: RSACfg is not valid, code:%d. (%s:%d)\n", code, __FILE__, __LINE__);
#endif
    return code;
}
  *M = mod_pow(m, r->e, r->p * r->q);
  return code; // RSA_OK=0
}

int decrypt(ulong_t *m, const ulong_t M, const struct RSACfg *r) {
  ulong_t d = r->d;
  int code;
  const ulong_t *p = &r->p, *q = &r->q, *e = &r->e;
  if (code=valid_rsa(r)) {
#ifdef DEBUG
    fprintf(stderr, "error: RSACfg is not valid, code:%d. (%s:%d)\n", code, __FILE__, __LINE__);
#endif
    return code;
  }
  if (!d) {
    if (mod_inv(&d, *e, (*p - 1) * (*q - 1))) {
#ifdef DEBUG
      fprintf(stderr, "error: 'e' is not invertible '*m' not assigned\n");
#endif
      return RSA_E_INVERT;
    }
  }
  *m = mod_pow(M, d, *p * (*q));

  return code; // RSA_OK=0
}
