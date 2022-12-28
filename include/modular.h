
/*--------- RSA Validity check codes --------*/
// RSA is valid
#define RSA_OK 0 
// RSA invalid: p is not prime
#define RSA_P_PRIME 0b0000001
// RSA invalid: q is not prime
#define RSA_Q_PRIME 0b0000010
// RSA invalid: p is equal to q
#define RSA_PQ_EQ 0b0000100
// RSA invalid: e and totient not coprime
#define RSA_ET_COPRIME 0b0001000
// RSA invalid: e is not in (0, p*q)
#define RSA_E_OUT_OF_RANGE 0b0010000
// RSA invalid: d is not coprime to totient
#define RSA_DT_COPRIME 0b0100000
// RSA invalid: e is not invertible
#define RSA_E_INVERT 0b1000000


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
ulong_t mod_pow(ulong_t a, ulong_t exp,const ulong_t mod);

// Check if argument is prime.
// Returns 0 if not prime and 1 otherwise.
int is_prime(const ulong_t);

// Returns the GCD of the arguments
ulong_t gcd(ulong_t, ulong_t);

// Calculates modular inverse of a under
// modulus n assigning the inverse to result.
// Returns 2 if a is not invertible and 0
// on success
int mod_inv(ulong_t *result, const ulong_t a, const ulong_t n);

// Encrypts the second argument assigning result
// to the first argument using RSAConfig.
//
// Returns result status of 'valid_rsa'.
int encrypt(ulong_t *, const ulong_t, const struct RSACfg *);

// Encrypts the second argument assigning result
// to the first argument using RSAConfig.
// 
// Returns result status of 'valid_rsa'.
int decrypt(ulong_t *, const ulong_t, const struct RSACfg *);

// Returns bit field of RSA codes.
int valid_rsa(const struct RSACfg *);
