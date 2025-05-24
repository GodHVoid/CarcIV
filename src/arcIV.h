#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ms 500
#define export __attribute__((visibility("default")))
#define rc4decrypt(x, y, z) rc4encrypt(x, y, z)
#define rc4uninit(x) free(x)
#define rc4whitewash(x, y)                                                     \
  for (x = 0; x < (ms * 1000000); x++) {                                       \
    (volatile int8) rc4byte(y);                                                \
  }

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct s_arcIV {
  int16 i, j, k;
  int8 s[256];
};
typedef struct s_arcIV arcIV;

export arcIV *rc4init(int8 *, int16);
int8 rc4byte(arcIV *);
export int8 *rc4encrypt(arcIV *, int8 *, int16);
