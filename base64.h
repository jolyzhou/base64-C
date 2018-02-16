#ifndef CPS_B64_H
#define CPS_B64_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *base64_encode(const unsigned char *in, int in_size);
unsigned char *base64_decode(const unsigned char *in);

#endif
