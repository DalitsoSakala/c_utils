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
	      n=p*q,
	      t=(p-1)*(q-1);

	for(long i=1; i<n;i++)
	  if(i*e%t==1 /*&&gcd(i,n)==1*/)
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
	     n = *p *(*q),
	     m = (*p - 1)*(*q - 1);
	int pass_1 = gcd(*p, *q) == 1,
	    pass_2 = gcd(m, *e) == 1,
	    pass_3 = gcd(n, *e) == 1,
	    pass_4 = *e>0 && *e<(*p * (*q)),
	    pass_5 = 1;

	if(c->d)
		pass_5 = gcd(c->d,n) == 1;

	return pass_1 & pass_2 & pass_3 & pass_4 & pass_5;
}




int encrypt(long *M, const long m, const struct RSACfg* r) {
	if(!valid_rsa(r)) return 1;
	*M = ((long)pow(m, r->e)) % (r->p * r->q);
	return 0;
}


int decrypt(long *m, const long M, const struct RSACfg* r) {
	long d = r->d;
	const long *p = &r->p, *q = &r->q, *e = &r->e;
	if(!valid_rsa(r)) return 1;
	if(!d)
	if(mod_inv(&d, *e, (*p - 1)*(*q - 1)))
		return 2;
	*m = ((long)pow(M, d)) % (*p * (*q));
	return 0;
}


