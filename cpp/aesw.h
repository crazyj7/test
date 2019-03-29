#ifndef _AESW_H_
#define _AESW_H_

// AES256bit CBS mode , PKCS5 zero padding

#include "aes.h"


int aesw_enc256(uint8_t *key, uint8_t *iv, char *inbuf, int insize, char *outbuf);
int aesw_dec256(uint8_t *key, uint8_t *iv, char *inbuf, int insize, char *outbuf);


#endif

