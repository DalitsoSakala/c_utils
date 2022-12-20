#include <modular.h>
#include<stdio.h>

int main(){
  const long m = 13;
  const struct RSACfg cfg = { e:7, p: 3, q:11  };
  long M = 0;
  long m1;

  encrypt(&M, m, &cfg);
  printf("Encryption:\nm: %ld, M: %ld\n", m, M);

  decrypt(&m1, M, &cfg);
  printf("Decryption\nM: %ld, m: %ld\n", M, m1);

}
