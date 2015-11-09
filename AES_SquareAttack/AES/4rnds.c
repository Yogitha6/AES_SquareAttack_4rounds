#include "rijndael-alg-fst.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#if (INT_MAX != 0x7fffffff)
#error -- Assumes 4-byte int
#endif

typedef unsigned char block[16];

#define AES_ROUNDS 4
#define AES_KEY_BITLEN  128

unsigned rek[1024];   /* main AES encryption key  */


void print_hex_string(char* buf, int len);


void print_hex_string(char* buf, int len)
{
    int i;

    if (len==0) { printf("<empty string>"); return; }
    if (len>=40) {
        for (i = 0; i < 10; i++)
             printf("%02x", *((unsigned char *)buf + i));
        printf(" ... ");
        for (i = len-10; i < len; i++)
             printf("%02x", *((unsigned char *)buf + i));
        printf(" [%d bytes]", len);
        return;
    }
    for (i = 0; i < len; i++)
        printf("%02x", *((unsigned char *)buf + i));
}


main() {
    static unsigned char key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    static unsigned char pt[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned char ct[16];
    int i;

    for(i = 0; i< 16; i ++)
            {
             key[i] = (unsigned char)i;
            }
    printf("key: ");
    print_hex_string(key,16);printf("\n");

    /* first init rijndael for underlying key */
    rijndaelKeySetupEnc(rek, (unsigned char *)key, 128);


    for (i=0; i < 256; i++)
    {
        pt[0] = (unsigned char)i;

	//print_hex_string(pt,16); printf("\n");
	rijndaelEncrypt(rek, AES_ROUNDS, pt, ct);
	print_hex_string(ct, 16);  printf("\n");
    }
}
