#include "include/modular.h"
#include<math.h>
#include<stdlib.h>

long gcd(long a, long b) {
	if(!b) return labs(a);
	return gcd(b, a%b);
}

int make_d(long *d, const struct RSACfg* cfg){
	if(!valid_rsa(cfg)) return -1;
	const long p=cfg->p,
	      q=cfg->q,
	      e=cfg->e,
	      n=p*q;

	for(long i=2; i<n;i++)
	  if(i*e%((p-1)*(q-1))==1)
	  {
		  *d=i;
		  return 0;
	  }
	return 1;//not invertible
}

int mod_inv(long *inv, const long a, const long n) {
	long t = 0, newt = 1;
	long r = n, newr = a;

	while(newr){
		long quotient = r/newr,
		     tmp = t;
		t = newt;
		newt = tmp - quotient * newt;
		tmp = r;
		r = newr;
		newr = tmp - quotient * newr;
	}

	if(r>1) return 1;

	if(t<0) t += n;

	*inv = t;
	return 0;
}

int valid_rsa(const struct RSACfg* c) {
	const long *e = &c-> e,
	      *p = &c-> p,
	     *q = &c-> q,
	     m = (*p - 1)*(*q - 1);
	int pass_1 = gcd(*p, *q) == 1,
	    pass_2 = gcd(m, *e) == 1,
	    pass_3 = *e>0 && *e<(*p * (*q));

	return pass_1 & pass_2 & pass_3;
}




int encrypt(long *M, const long m, const struct RSACfg* r) {
	if(!valid_rsa(r)) return 1;
	*M = ((long)pow(m, r->e)) % (r->p * r->q);
	return 0;
}


int decrypt(long *m, const long M, const struct RSACfg* r) {
	long d = 0;
	const long *p = &r->p, *q = &r->q, *e = &r->e;
	if(!valid_rsa(r)) return 1;
	if(mod_inv(&d, *e, (*p - 1)*(*q - 1)))
		return 2;
	*m = ((long)pow(M, d)) % (*p * (*q));
	return 0;
}


int decryptd(long *m, const long M, const struct RSACfg* r, const long d) {
	const long *p = &r->p, *q = &r->q, *e = &r->e;
	if(!valid_rsa(r)) return 1;
	*m = ((long)pow(M, d)) % (*p * (*q));
	return 0;
}
