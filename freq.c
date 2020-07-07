// Copyright 2020 Calcan Elena-Claudia
#include <stdio.h>
#include <stdlib.h>

#define NMAX 2000001

int main() {
  int *freq_array, num;
  freq_array = calloc(NMAX, sizeof(int));
  if (freq_array == NULL) {
    fprintf(stderr, "Calloc failed\n");
    exit(1);
  }
  // citire numere
  while (fscanf(stdin, "%d", &num) != EOF) {
    // numarul de aparitii creste
    freq_array[num]++;
  }
  // afisare numar si numarul sau de aparitii
  for (int i = 0; i < NMAX; i++) {
    if (freq_array[i] != 0) {
      printf("%d %d\n", i, freq_array[i]);
    }
  }
  free(freq_array);
  return 0;
}
