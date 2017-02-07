#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int main (char argc,char **argv){
//printf("\nuid=%d  euid=%d\n",getuid(),geteuid());
//execve("./cmd",NULL,NULL);
//printf("%s\n",strerror(errno));
   int i=10 ,j ;
   if(argc > 1)
   j=strtol(argv[1],NULL,0);

   printf("input cmd %d\n",j);
   
   for (i=0;i<10;i++){

	switch(j){
	 case 1:
		printf("input 1\n");
	 break ;
         case 2:
		printf("input 2\n");
	 break;
         case 3:
		printf("input 3\n");
	 break;
	
	}
	printf("circle %d\n",i);
   }
   

}
