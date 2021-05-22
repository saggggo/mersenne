#include<stdio.h>
#include<gmp.h>

unsigned long long int mersenne(int);
int prime(unsigned long long int);

int main(void) {
  for(int i = 1; i < 100; i++) {
    unsigned long long int x = mersenne(i);
    printf("%llu: %d\n", x, prime(x));
  }
}

unsigned long long int mersenne(int n) {
  unsigned long long int acc = 1;
  for(int i = 0; i < n; i++) {
    acc = acc * 2;
  }
  return acc - 1;
}

int prime(unsigned long long int x) {
  for(int i = 2; i < x; i++) {
    if (x%i == 0) {
      return 0;
    }
  }
  return 1;
}
