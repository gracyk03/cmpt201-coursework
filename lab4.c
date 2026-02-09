#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

int main(void) {
  void *startad = sbrk(0);
  printf("first program break address: %p\n", startad);

  void *block = sbrk(256);
  if (block == (void *)-1) {
    perror("sbrk failed");
    free(startad);
    free(block);
    exit(EXIT_FAILURE);
  }
  struct header *headB1 = (struct header *)block;
  headB1->size = 128;
  headB1->next = NULL;

  struct header *headB2 = (struct header *)(block + 256);
  headB2->size = 128;
  headB2->next = headB1;

  printf("first block: %p\n", headB1);
  printf("second block: %p\n", headB2);
  printf("first block size: %p\n", headB1->size);
  printf("first block next: %p\n", headB1->next);
  printf("second block size: %p\n", headB2->size);
  printf("second block next: %p\n", headB2->next);

  void *dataB1 = (void *)(headB1 + sizeof(struct header));
  void *dataB2 = (void *)(headB2 + sizeof(struct header));

  memset(dataB1, 0, 128 - sizeof(struct header));
  memset(dataB2, 1, 128 - sizeof(struct header));
}
