#include "rijndael-alg-fst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

    FILE *fp = fopen("output_fed_4rnds.txt","rw+");
    char * line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int j;
    int count = 0;
    static unsigned char key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     while (read != -1)
        {
           for(j = 0; j<16; j++)
           {
               read = getline(&line,&len,fp);
               key[j] = atoi(line);

           }
           count = count + 1;

           if(count == 1537)
           {
               break;
           }

            static unsigned char pt[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static unsigned char pt1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            unsigned char ct[16];
            unsigned char ct1[16];
            int i;

            /* first init rijndael for underlying key */
            rijndaelKeySetupEnc(rek, (unsigned char *)key, 128);

            // generating the plain text given to narrow down the keys - 0102030405060708090a0b0c0d0e0f00

            for(i = 0; i< 16; i ++)
            {
             pt1[i] = (unsigned char)i+1;
            }
            pt1[15] = (unsigned char)0;


            rijndaelEncrypt(rek,AES_ROUNDS, pt1, ct1);

            // generating the integer value of the expected cipher text - 71fae486fafc990d4a44a21a7fac6b75
            // and comparing it with the cipher text we got using current key

            if(ct1[0] == 113 & ct1[1]==250 & ct1[2]==228 & ct1[3]==134 & ct1[4] == 250 & ct1[5] == 252 & ct1[6] == 153 & ct1[15] == 117)
            {
                print_hex_string(key,16); printf("\n");
            }

       }
       fclose(fp);
}