#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool strEqual(char *line, char *comparel) {
  int linelen = strlen(line);
  int comparelen = strlen(comparel);
  if (line[linelen - 1] == '\n') {
    line[linelen - 1] = '\0';
    linelen--;
  }

  if (linelen != comparelen) {
    return false;
  }
  for (int i = 0; i < comparelen; i++) {
    if (line[i] != comparel[i]) {
      return false;
    }
  }
  return true;
}

int detectPrint(char *arr[5], int *counter) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  printf("Enter input: ");
  nread = getline(&line, &len, stdin);
  if (nread == -1) {
    printf("ERROR: getline failed");
    free(line);
    exit(EXIT_FAILURE);
  }
  if (*counter == 5) {
    free(arr[0]);
    for (int i = 1; i < 5; i++) {
      arr[i - 1] = arr[i];
    }
    arr[4] = line;
  } else {
    arr[*counter] = line;
    (*counter)++;
  }
  return strEqual(line, "print");
}

int main() {
  char *arr[5] = {NULL, NULL, NULL, NULL, NULL};
  int counter = 0;
  int pval = 0;

  while (1) {
    pval = detectPrint(arr, &counter);
    if (pval == 1) {
      for (int i = 0; i < counter; i++) {
        printf("%s\n", arr[i]);
      }
    }
  }
  for (int i = 0; i < counter; i++) {
    free(arr[i]);
  }
  return 0;
}
