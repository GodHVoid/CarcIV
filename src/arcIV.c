#include "arcIV.h"

export arcIV *rc4init(int8 *key, int16 size) {
  int8 tmp1, tmp2;
  arcIV *p;
  int32 n;

  if (!(p = malloc(sizeof(struct s_arcIV)))) {
    assert_perror(errno);
  }

  p->i = p->j = p->k = 0;
  tmp1 = tmp2 = 0;

  for (p->i = 0; p->i < 256; p->i++) {
    p->s[p->i] = p->i;
  }

  for (p->i = 0; p->i < 256; p->i++) {
    // j = (j + s[i] + key[i mod keylength]) mod 256
    tmp1 = p->i % size;
    tmp2 = p->j + p->s[p->i] + key[tmp1];
    p->j = tmp2 % 256;
    // swap s[i] and s[j] values
    tmp1 = p->s[p->i];
    tmp2 = p->s[p->j];
    p->s[p->i] = tmp2;
    p->s[p->j] = tmp1;
  }
  // reset for generating k stream
  p->i = p->j = 0;
  rc4whitewash(n, p);

  return p;
}

int8 rc4byte(arcIV *p) {
  int16 tmp1, tmp2;
  p->i = (p->i + 1) % 256;
  p->j = (p->j + p->s[p->i]) % 256;
  tmp1 = p->s[p->i];
  tmp2 = p->s[p->j];
  p->s[p->i] = tmp2;
  p->s[p->j] = tmp1;
  tmp1 = (p->s[p->i] + p->s[p->j]) % 256;
  p->k = p->s[tmp1];

  return p->k;
}

export int8 *rc4encrypt(arcIV *p, int8 *cleartext, int16 size) {
  int8 *ciphertext;
  int16 x;

  ciphertext = (int8 *)malloc(size + 1);
  if (!ciphertext) {
    assert_perror(errno);
  }

  for (x = 0; x < size; x++) {
    ciphertext[x] = cleartext[x] ^ rc4byte(p);
  }
  return ciphertext;
}
