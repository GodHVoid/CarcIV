#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define rc4decrypt(x, y) rc4encrypt(x, y);

struct s_arcIV {
  int x;
};

typedef struct s_arcIV arcIV;
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

arcIV *rc4init(int8 *, int16);
int8 rc4byte(void);
int8 *rc4encrypt(int8 *, int16);
