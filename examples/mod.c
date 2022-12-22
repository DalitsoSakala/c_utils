#include <modular.h>
#include<stdio.h>
#include<unistd.h>


enum Task { Encrypt=1, Decrypt} task;

int do_encrypt(long *, const long,const struct RSACfg*);

int do_decrypt(long *, const long, const struct RSACfg*);

int main(int argc, char**argv){
  struct RSACfg cfg = { .e=7, .p= 3, .q=11  };
  long M, m, e, p, q;
  int opt;
  opterr = e = p = q = 0;
  
  while((opt=getopt(argc, argv,":hDEe:p:q:m:M:"))!=-1){
	switch(opt){
		case 'h': printf("Usage: %s [-h] [-DE] [-e x -p y -q z] arg\n",argv[0]);
			  return 0;
		case 'D': task=Decrypt;
			  break;
		case 'E': task=Encrypt;
			  break;
		case 'e': e=atoi(optarg);
			  break;
		case 'p': p=atoi(optarg);
			  break;
		case 'q': q=atoi(optarg);
			  break;
		case ':': fprintf(stderr,"'-%c' option missing a value\n",optopt);
			return -1;
		case '?': fprintf(stderr,"Unrecognized option '-%c'\n",optopt);
			 return 1;
	}
  }

  if(!task) {
	  fprintf(stderr,"Specify a task with -E or -D option\n");
	  return 3;
  }

  if(e||p||q){
	  if(!(p&&q&&e)){
		  fprintf(stderr, "error: Make sure you set a complete update on p, q and e when you set any of the options (e,p,q)\n");
		  return 4;
	  }
	  cfg.e=e;
	  cfg.p=p;
	  cfg.q=q;
  }
  if(optind<argc){
  if(task==Decrypt) {
	  M=atoi(argv[optind]);
	  do_decrypt(&m, M, &cfg);
	  printf("Decryption\nM: %ld\nResult: %ld\n",M,m);
  } else if(task==Encrypt){
	  m=atoi(argv[optind]);
	  do_encrypt(&M, m, &cfg);
	  printf("Encryption\nm: %ld\nResult: %ld\n",m,M);

  }
  }
  else {
	  fprintf(stderr, "error: An argument was expected\n");
	  return 5;
  }


}


int do_encrypt(long *M, const long m,const struct RSACfg* c){
	printf("Encrypting with pub key(%ld,%ld)\n", c->p*c->q,c->e);
	return encrypt(M, m, c);
}



int do_decrypt(long *m, const long M, const struct RSACfg* c){
	long d;
	make_d(&d, c);
	printf("Decrypting with priv key(%ld, %ld, %ld)\n",d, c->p, c->q);
	return decryptd(m, M, c, d);
}

