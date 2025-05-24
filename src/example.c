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
  char *key, *from;
  int8 *encrypted, *decrypted;

  key = "tomatoes";
  skey = strlen(key);
  from = "Shall I compare thee to a summer's day?";
  stext = strlen(from);

  printf("Initializeing Encryption....");
  rc4 = rc4init((int8 *)key, skey);
  printf("done\n");

  printf("'%s'\n ->", from);
  encrypted = rc4encrypt(rc4, (int8 *)from, stext);
  printbin(encrypted, stext);

  rc4uninit(rc4);

  printf("Initializeing Decyption....");
  rc4 = rc4init((int8 *)key, skey);
  printf("done\n");

  decrypted = rc4decrypt(rc4, encrypted, stext);
  printf("  ->'%s'", decrypted);
  rc4uninit(rc4);

  return 0;
}
