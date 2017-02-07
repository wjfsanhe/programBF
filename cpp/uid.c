#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int main (char argc,char **argv){
int a=0xffff, b=0xffffffff ;
printf("\nuid=%d  euid=%d\n",getuid(),geteuid());

//seteuid(0);
printf("%s\n",strerror(errno));
execve("./ttt",NULL,NULL);
printf("%s\n",strerror(errno));
printf("~a =0x%x ~b=0x%x \n",~a&0xffff0000,~b);
}
