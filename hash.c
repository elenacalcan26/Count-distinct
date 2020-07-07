// Copyright 2020 Calcan Elena-Claudia
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HMAX 101

struct info {
  char *key;
  int value;
};

// implementare functie strdup
char *my_strdup(const char *s) {
  char *p = malloc(strlen(s) + 1);
  if (p == NULL) {
    exit(1);
  }
  if (p != NULL) {
    snprintf(p, strlen(s) + 1, "%s", s);
  }
  return p;
}

// functie hash pentru char
unsigned int hashing(char *a) {
  unsigned char *puchar_a = (unsigned char *)a;
  unsigned int hash = 5381;
  int c;
  while ((c = *puchar_a++)) {
    hash = ((hash << 5u) + hash) + c;
  }
  return hash;
}

int main() {
  struct info *ht;
  char strKey[HMAX];
  int index;
  ht = calloc(HMAX, sizeof(struct info));
  if (ht == NULL) {
    fprintf(stderr, "Calloc failed\n");
    exit(1);
  }
  // citire string
  while (fscanf(stdin, "%s", strKey) != EOF) {
    // determinare index bucket
    index = hashing(strKey) % HMAX;
    // verifica daca bucket-ul este ocupat sau nu
    if (ht[index].value == 0) {
      ht[index].value = 1;
      ht[index].key = my_strdup(strKey);
    } else {
      ht[index].value++;
    }
  }
  // afisare string si numarul de aparitii
  for (int i = 0; i < HMAX; i++) {
    if (ht[i].value != 0) {
      printf("%s %d\n", ht[i].key, ht[i].value);
      free(ht[i].key);
    }
  }
  free(ht);
  return 0;
}
