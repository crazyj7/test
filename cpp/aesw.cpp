#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "aes.h"

// aes256
// key size ; 32 bytes
// iv size ; 16 bytes
int aesw_enc256(uint8_t *key, uint8_t *iv, char *inbuf, int insize, char *outbuf) {
	int blockcnt = (int) insize/16 ;
	int encsize = 0 ;

	blockcnt++ ;
	encsize = blockcnt * 16 ;
	memset(outbuf, 0x00, encsize) ;
	memcpy(outbuf, inbuf, insize) ;

	// padding pkcs5
	int padsize = encsize - insize ;
//	printf("padsize=%d\n", padsize) ;
	memset(outbuf+insize, padsize, padsize) ;

	struct AES_ctx ctx ;
	AES_init_ctx_iv(&ctx, key, iv) ;
	AES_CBC_encrypt_buffer(&ctx, (uint8_t*)outbuf, encsize) ;

	return encsize ;
}

int aesw_dec256(uint8_t *key, uint8_t *iv, char *inbuf, int insize, char *outbuf) {
	struct AES_ctx ctx ;
	AES_init_ctx_iv(&ctx, key, iv) ;
	memcpy(outbuf, inbuf, insize) ;
	AES_CBC_decrypt_buffer(&ctx, (uint8_t*)outbuf, insize) ;
	// get padsize
	int padsize = outbuf[insize-1] ;
//	printf("padsize=%d\n", padsize) ;
	return insize-padsize ;
}


