#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main() {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  pid_t pid;

  while (1) {
    printf("Enter programs to run: \n");
    nread = getline(&line, &len, stdin);

    if (nread == -1) {
      perror("error: getline failed\n");
      free(line);
      exit(EXIT_FAILURE);
    }
    line[nread - 1] = '\0';

    pid = fork();
    if (pid == -1) {
      printf("fork failed\n");
    } else if (pid == 0) {
      if (execl(line, line, NULL) == -1) {
        printf("Exec failure\n");
      }
    } else {
      int wstatus = 0;
      if (waitpid(pid, &wstatus, 0) == -1) {
        printf("waitpid failed\n");
      }
    }
  }
  free(line);
}
