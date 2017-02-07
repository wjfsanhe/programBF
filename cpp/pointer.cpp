#include  <stdio.h>
#include <stdlib.h>
#define uint32_t unsigned int
int main (int argc ,char **argv){
	uint32_t ct=100;
	uint32_t *val=&ct;
	uint32_t &p=*val;

	p=101;
	printf("ct[100]=%d\n",ct);
	return 0; 
	
}
