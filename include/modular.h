#define ERRNOT_INVERTIBLE 2
#define ERRPQ_COPRIME 3

// RSA Encryption integers
struct RSACfg {
	long d;
	long e;
	long p;
	long q;
};

// Generates d by iteration
int make_d(long *d, const struct RSACfg* cfg);


// Returns the GCD of the arguments
long gcd(long, long);

// Calculates modular inverse of a under 
// modulus n assigning the inverse to result.
// Returns 2 if a is not invertible and 0
// on success
int mod_inv(long*result,const long a,const long n);

// Encrypts the second argument assigning result
// to the first argument using RSAConfig.
int encrypt(long*, const long, const struct RSACfg*);

// Encrypts the second argument assigning result
// to the first argument using RSAConfig.
// Returns error
int decrypt(long*, const long, const struct RSACfg*);


// Returns 0 when c is invalid 
// that is (GCD of p, q and e is not 1) or 1 if 
// GCD is valid.
int valid_rsa(const struct RSACfg* c);
