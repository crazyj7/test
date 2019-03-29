#include <stdio.h>
#include <string.h>
#include <stdint.h>

//#include "aes.h"
// aes test
#include "aesw.h"


void adump_bin(unsigned char* b, int len) {
	int i=0; 
	for (i=0; i<len; i++) {
		printf("%02x", b[i]) ;
	}
	printf("\n") ;
}

// aes256
// key size ; 32 bytes
// iv size ; 16 bytes
/*
int aesenc(uint8_t *key, uint8_t *iv, char *inbuf, int insize, char *outbuf) {
	int blockcnt = (int) insize/16 ;
	int encsize = 0 ;

	blockcnt++ ;
	encsize = blockcnt * 16 ;
	memset(outbuf, 0x00, encsize) ;
	memcpy(outbuf, inbuf, insize) ;

	// padding pkcs5
	int padsize = encsize - insize ;
	printf("padsize=%d\n", padsize) ;
	memset(outbuf+insize, padsize, padsize) ;

	struct AES_ctx ctx ;
	AES_init_ctx_iv(&ctx, key, iv) ;
	AES_CBC_encrypt_buffer(&ctx, (uint8_t*)outbuf, encsize) ;

	return encsize ;
}

int aesdec(uint8_t *key, uint8_t *iv, char *inbuf, int insize, char *outbuf) {
	struct AES_ctx ctx ;
	AES_init_ctx_iv(&ctx, key, iv) ;
	memcpy(outbuf, inbuf, insize) ;
	AES_CBC_decrypt_buffer(&ctx, (uint8_t*)outbuf, insize) ;
	// get padsize
	int padsize = outbuf[insize-1] ;
	printf("padsize=%d\n", padsize) ;
	return insize-padsize ;
}
*/



int main()
{
	uint8_t key[32] ;	// aes 256
	memset(key, 0x00, sizeof key) ;
	char data[4096];
	char encdata[4096];
	char decdata[4096];
	uint8_t iv[16] ;
	
	memset(data, 0, sizeof(data)) ;
	memset(iv, 0, sizeof(iv)) ;
	memset(key, 0, sizeof(key)) ;

	int blocksize=16 ;
	int encsize=0; 
	int decsize=0 ;
	int insize=0 ;
	strncpy((char*)key, "12345678901234567890123456789012", 32) ;

	char datas[][4096] = { "hello world", 
		"hello world hel",
		"hello world hell",
		"hello world hello world hello world hello world",
		"hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world\
		hello world hello world hello world hello world"
	};

	for (int i=0; i<5; i++) {
		printf("\n\nTEST [%d]\n", i) ;

//	strcpy(data, "hello world" ) ;
//	strcpy(data, "hello world hel" ) ; // 15bytes
//	strcpy(data, "hello world hell" ) ; // 16bytes
	strcpy(data, datas[i]) ;
	insize= strlen(data) ;
	printf("plain=\n") ;
	adump_bin((unsigned char*)data, insize) ;

	encsize=aesw_enc256(key, iv, data, insize, encdata) ;
	printf("enc result:\n") ;
	adump_bin( (unsigned char*)encdata, encsize) ;

	decsize=aesw_dec256(key, iv, encdata, encsize, decdata) ;
	printf("dec result:\n") ;
	adump_bin( (unsigned char*)decdata, decsize) ;
	if ( memcmp(data, decdata, decsize)== 0 && insize==decsize ) {
		printf("match ok!\n") ;
	} else 
		printf("no match FAIL!\n") ;
	}

	//blocksize=16 ;
	//strcpy(data, "hello world" ) ;
/*	// 2 block. end 0x09. pad size=09. it's ok. 
	blocksize=16*2 ;
	strcpy(data, 
"hello world hello worl" ) ;
	data[strlen(data)]=0x09 ;
*/

/* 
   // block completed case : end 0x01 ; not pad size but data.
   // then. append 1 block.
	blocksize=16 ;
	strcpy(data, 
"hello world hel" ) ;
	data[strlen(data)]=0x01 ; // data not pad.
	printf("plain\n") ;
	blocksize=16*2 ; 
*/

	// decrypt with pad...
	// last block end bytes -> pad size.
	// remove pad size.

	// padding
	/*
	int contentsize = strlen(data) ;
	int padsize = blocksize-contentsize ;
	memset(data+contentsize, padsize, padsize) ;
	printf("content size=%d pad size=%d\n", contentsize, padsize) ;

	adump_bin( (unsigned char*)data, blocksize) ;

	printf("key\n") ;
	adump_bin( (unsigned char*)key, 32) ;

	struct AES_ctx ctx ;
	AES_init_ctx_iv(&ctx, key, iv) ;

	printf("AES256 CBC encryption...\n") ;
	AES_CBC_encrypt_buffer(&ctx, (uint8_t*)data, blocksize) ;

	printf("encrypt=\n") ;
	adump_bin( (unsigned char*)data, blocksize) ;
	printf("\n") ;


	// decrypt
	char decbuf[1024]={0,} ;
	AES_init_ctx_iv(&ctx, key, iv) ;
	AES_CBC_decrypt_buffer(&ctx, (uint8_t*)data, blocksize) ;

	printf("decrypt=\n") ;
	adump_bin( (unsigned char*)data, blocksize) ;
	printf("\n") ;
	*/



	return 0 ;
}

