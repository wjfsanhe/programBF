#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <unistd.h>
#include <stdint.h>
#include <memory.h>
//#include <openssl/rsa.h>
//#include <openssl/pem.h>
#include <openssl/evp.h>



char *base64_enc(uint8_t *input, int length) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64()); 
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buf = (char *)malloc(bptr->length);
    if (bptr->length) {
        memcpy(buf, bptr->data, bptr->length-1);
        buf[bptr->length-1] = 0;
    }

    BIO_free_all(bmem);
    printf("encode :%s\n",buf);
    return buf;
}
char *base64_dec(uint8_t *input,int *retlen)
{
   int length = strlen(input);
   printf("dec in:%s\n",input);
   BIO *bmem,*b64;//we could create two direction.
   BUF_MEM *bptr;
   b64=BIO_new(BIO_f_base64());
   BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
   bmem=BIO_new(BIO_s_mem());
//   BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
   b64=BIO_push(b64,bmem);
   BIO_write(bmem,input,length);
   BIO_flush(bmem);
   length=length*3/4 + 1;
   printf("len:%d\n",length);
   char *buf = (char *)malloc(length);
   *retlen=BIO_read(b64,buf,length);
   BIO_free_all(bmem);
   printf("dec :%s``````\n",buf);
   return buf;

}
int main (char argc,char**argv)
{
    uint8_t str[]="Hello my friends";
    int len;
    printf("input %s\n",str);
    printf("base64_enc:%s,  base64_dec:%s\n",base64_enc(str,strlen(str)),base64_dec(base64_enc(str,strlen(str)),&len));	
    return 0;	
}
