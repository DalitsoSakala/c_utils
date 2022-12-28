#define ERRNOT_INVERTIBLE 2
#define ERRPQ_COPRIME 3

typedef unsigned long long int ulong_t;

// RSA Encryption integers
struct RSACfg {
  ulong_t d;
  ulong_t e;
  ulong_t p;
  ulong_t q;
};

// Generates d  in private key (m, d) by iteration
int make_d(ulong_t *d, const struct RSACfg *cfg);


// Peform modular exponentiation
ulong_t mod_pow(ulong_t a, ulong_t exp, ulong_t mod);

// Check if argument is prime.
// Returns 0 if not prime and 1 otherwise.
int is_prime(ulong_t);

// Returns the GCD of the arguments
ulong_t gcd(ulong_t, ulong_t);

// Calculates modular inverse of a under
// modulus n assigning the inverse to result.
// Returns 2 if a is not invertible and 0
// on success
int mod_inv(ulong_t *result, const ulong_t a, const ulong_t n);

// Encrypts the second argument assigning result
// to the first argument using RSAConfig.
int encrypt(ulong_t *, const ulong_t, const struct RSACfg *);

// Encrypts the second argument assigning result
// to the first argument using RSAConfig.
// Returns error
int decrypt(ulong_t *, const ulong_t, const struct RSACfg *);

// Returns 0 when c is invalid
// that is (GCD of p, q and e is not 1) or 1 if
// GCD is valid.
int valid_rsa(const struct RSACfg *c);
