#include "../include/modular.h"
#include <stdio.h>
#include <unistd.h>

enum Task { Encrypt = 1, Decrypt } task;

int do_encrypt(ulong_t *, const ulong_t, const struct RSACfg *);

int do_decrypt(ulong_t *, const ulong_t, struct RSACfg *);

int main(int argc, char **argv) {
  struct RSACfg cfg = {.e = 61, .p = 29, .q = 113, .d = 0};
  ulong_t M, m, e, d, p, q;
  int opt;
  opterr = e = p = q = d = 0;

  while ((opt = getopt(argc, argv, ":hHDEe:p:q:m:M:")) != -1) {
    switch (opt) {
    case 'h':
      printf("Usage: %s [-hH] [-DE] [-d] [-e x -p y -q z] arg\n", argv[0]);
      return 0;
    case 'H':
      printf(
          "Default values:\ne=%lld\np=%lld\nq=%lld\n\n\t(Specify your own with options with: -e\
 evalue -p pvalue -q qvalue)\n",
          cfg.e, cfg.p, cfg.q);
      return 0;
    case 'D':
      task = Decrypt;
      break;
    case 'E':
      task = Encrypt;
      break;
    case 'e':
      e = atol(optarg);
      break;
    case 'd':
      d = atol(optarg);
      break;
    case 'p':
      p = atol(optarg);
      break;
    case 'q':
      q = atol(optarg);
      break;
    case ':':
      fprintf(stderr, "'-%c' option missing a value\n", optopt);
      return -1;
    case '?':
      fprintf(stderr, "Unrecognized option '-%c'\n", optopt);
      return 1;
    }
  }

  if (!task) {
    fprintf(stderr, "Specify a task with -E or -D option\n");
    return 3;
  }

  if ((d && task == Decrypt) || (e || p || q)) {
    if (!(p && q && e)) {
      fprintf(stderr, "error: Make sure you set a complete update on p, q and "
                      "e when you set any of the options (e,p,q)\n");
      return 4;
    }
    cfg.e = e;
    cfg.p = p;
    cfg.q = q;
  }
  if (optind < argc) {
    if (task == Decrypt) {
      M = atol(argv[optind]);
      if (d)
        cfg.d = d;
      if (do_decrypt(&m, M, &cfg)) {
        fprintf(stderr, "error: Decryption failed (%s:%d)\n", __FILE__,
                __LINE__);
        return 6;
      }
      printf("Decryption\nM: %lld\nResult(m): %lld\n", M, m);
    } else if (task == Encrypt) {
      m = atol(argv[optind]);
      if (do_encrypt(&M, m, &cfg)) {
        fprintf(stderr, "error: Encryption failed (%s:%d)\n", __FILE__,
                __LINE__);
        return 7;
      }
      printf("Encryption\nm: %lld\nResult(M): %lld\n", m, M);
    }
  } else {

    fprintf(stderr, "error: An argument was expected\n");
    return 5;
  }
}

int do_encrypt(ulong_t *M, const ulong_t m, const struct RSACfg *c) {
#ifdef DEBUG
  printf("Encrypting with pub key(%lld,%lld)\n", c->p * c->q, c->e);
#endif
  return encrypt(M, m, c);
}

int do_decrypt(ulong_t *m, const ulong_t M, struct RSACfg *c) {
  if (!c->d)
    make_d(&c->d, c);

#ifdef DEBUG
  printf("Decrypting with priv key (%lld, %lld, %lld)\n", c->d, c->p, c->q);
#endif
  return decrypt(m, M, c);
}
