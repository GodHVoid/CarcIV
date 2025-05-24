#include "arcIV.h"
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <unistd.h>

#define F fflush(stdout)

// print hex dump
void printbin(int8 *input, const int16 size) {
  int16 i;
  int8 *p;
  //
  assert(size > 0);

  for (i = size, p = input; i; i--, p++) {
    if (!(i % 2)) {
      printf(" ");
    }
    printf("%.02x", *p);
  }

  printf("\n");
  return;
}

int main() {
  // keep internal state
  arcIV *rc4;
  int16 skey, stext;
  char *key, *from, *encrypted, *decrypted;

  key = "tomates";
  skey = strlen(key);
  from = "Shall I compare thee to a summer's day?";
  stext = strlen(from);

  printf("Initializeing Encryption....\n");
  rc4 = rc4init((int8 *)key, skey);
  printf("done\n");

  printf("'%s'\n ->", from);
  encrypted = rc4encrypt((int8 *)from, stext);

  return 0;
}
