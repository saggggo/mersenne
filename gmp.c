#include<stdio.h>
#include<time.h>
#include<gmp.h>

void mersenne(mpz_t, int);
int prime_test_int(int);
int prime_test_gmp(mpz_t);
int lucas_lermer_test(mpz_t, int);

int main(void) {
  for(int i = 300000;; i++) {
    clock_t begin = clock();
    int is_prime;
    if (prime_test_int(i)) {
      mpz_t x;
      mersenne(x, i);
      is_prime = lucas_lermer_test(x, i);
    } else {
      is_prime = 0;
    }
    clock_t end = clock();
    double sec = (double)(end - begin)/CLOCKS_PER_SEC;
    gmp_printf("%d: 2^%d - 1\t%f seconds.\n", is_prime, i, sec);
  }
}

void mersenne(mpz_t x, int n) {
  mpz_t acc;
  mpz_init_set_ui(acc, 1);
  for(int i = 0; i < n; i++) {
//    mpz_mul_ui(acc, acc, 2);
    mpz_mul_2exp(acc, acc, 1);
  }
  mpz_sub_ui(x, acc, 1);
  return;
}

int prime_test_int(int x) {
  for(int i = 2; i < x; i++) {
    if (x%i == 0) {
      return 0;
    }
  }
  return 1;
}

int prime_test_gmp(mpz_t x) {
//  gmp_printf("x: %Zd\n", x);
  mpz_t i;
  mpz_init_set_ui(i, 2);

  for(; mpz_cmp(x, i); mpz_add_ui(i, i, 1)) {
    mpz_t modulo;
    mpz_init(modulo);
    mpz_mod(modulo, x, i);
    if (mpz_cmp_ui(modulo, 0) == 0) {
      return 0;
    }
  }
  return 1;
}

int lucas_lermer_test(mpz_t mp, int p) {
  mpz_t s;
  mpz_init_set_ui(s, 4);
  for (int i = 2; i < p; i++) {
//   mpz_mul(s, s, s);
//   mpz_sub_ui(s, s, 2);
//   mpz_mod(s, s, mp);
    mpz_t s2, s3, s4;
    mpz_init(s2);
    mpz_init(s3);
    mpz_init(s4);
    mpz_mul(s2, s, s);
    mpz_and(s3, s2, mp);
    mpz_tdiv_q_2exp(s4, s2, p);
    mpz_add(s, s4, s3);
    if(mpz_cmp(s, mp) >= 0) {
      mpz_sub(s, s, mp);
    }
    mpz_sub_ui(s, s, 2);
  }

  if (mpz_cmp_ui(s, 0) == 0) {
    return 1;
  } else {
    return 0;
  }
}
