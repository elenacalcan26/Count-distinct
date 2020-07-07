// Copyright 2020 Calcan Elena-Claudia
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define m 2048
#define BIT_SIZE 32

// functie hash pentru int
unsigned int hash(int *a) {
  unsigned int x = *((unsigned int *)a);
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return x;
}

// tranforma numarul in decimal in binar
void dec_to_bin(int n, int *bin) {
  for (int i = BIT_SIZE - 1; i >= 0; i--) {
    if (n >> i & 1) {
      bin[i] = 1;
    } else {
      bin[i] = 0;
    }
  }
}

// extrage primii k biti, incepand cu pozitia p
int bit_extracted(int number, int k, int p) {
  return (((1 << k) - 1) & (number >> (p - 1)));
}

// numara bitii 0
int count_zeros(int *binary) {
  int cnt = 0;
  for (int i = BIT_SIZE - 1; i > 11; i--) {
    if (binary[i] == 1) {
      return cnt;
    } else {
      cnt++;
    }
  }
  return cnt;
}

// calculeaza 2 la puterea n
int pow_of_2(int n) {
  int pow = 1;
  while (n) {
    pow = pow * 2;
    n--;
  }
  return pow;
}

int main(int argc, char *argv[]) {
  int n, binary[BIT_SIZE], j, x, E, used_buckets = 0;
  float alpha_m, z = 0;
  FILE *fin;
  if (argc != 2) {
    fprintf(stderr, "Wrong number of arguments\n");
  }
  fin = fopen(argv[1], "rt");
  if (fin == NULL) {
    fprintf(stderr, "Cannot open %s\n", argv[1]);
    exit(1);
  }
  int *M = calloc(m, sizeof(int));
  if (M == NULL) {
    fprintf(stderr, "Calloc failed\n");
    exit(1);
  }
  while (!feof(fin)) {
    // citire numar
    fscanf(fin, "%d", &n);
    memset(binary, 0, BIT_SIZE * sizeof(int));
    // transformam in binar rezulatul intors de hash
    dec_to_bin(hash(&n), binary);
    // aflam bucket-ul
    j = bit_extracted(hash(&n), 11, 1) % m;
    // aflam numarul de biti 0
    x = count_zeros(binary) + 1;
    // determinam maximul dintre valoare de pe pozitia j si x
    if (M[j] < x) {
      M[j] = x;
    }
  }
  fclose(fin);
  // calculam z si aflam numarul de bucket-uri folosite
  for (int i = 0; i < m; i++) {
    if (M[i] != 0) {
      z = z + 1.0 / (float)pow_of_2(M[i]);
      used_buckets++;
    }
  }
  z = 1 / z;
  // alpha_m se afla in cazul m >= 128 si il aflam dupa formula
  alpha_m = 0.7213 / (1 + (1.079 / used_buckets));
  // calculez E dupa formula
  E = alpha_m * m * m * z;
  printf("%d\n", E);
  free(M);
  return 0;
}
