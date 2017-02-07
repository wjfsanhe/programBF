#include  <stdlib.h>
#include <fcntl.h>
#include  <stdio.h>

#define MAX_ERRNO	4095

#define u32 unsigned int
#define IS_ERR_VALUE(x) ((x) >= (unsigned long)-MAX_ERRNO)
struct test{
u32  a;
u32  b;
u32  c;
};

void main(char argc,char **argv)
{
	int pid;
	int fds[2];
	char buf[10];
	char pbuf[2];
	char buf2[100];
	char buf3[10];
	short  table[20][6];
	int  var=5;
	int  fd;
	int  *ppp=NULL;
	struct test *ac1,*ac2,*ac3 ;
	unsigned long test= (unsigned long)-4096;
	
	printf("%d\n", 1<<2 +5);
	return ;

	ac1 = malloc(sizeof(struct test));
	ac2 = ac1 ; 
	ac3 = ac2 ;
	printf("1 %p  2 %p 3 %p \n",ac1,ac2,ac3);
	printf("max=%lx\n",(unsigned long)-4095);

	printf("test=%lx\n",test);
	if(IS_ERR_VALUE	(test)){
		printf("error\n");
	}else{
		printf("not error\n");
	}
//	return ;

	
	ppp=&fd;

	printf("addr %%p= %p \n",ppp);
	printf("addr %%px= 0x%px\n",ppp);

	printf("sizeof(long) %d\n",sizeof(long)<<3);
	printf("sizeof(int) %d\n",sizeof(int)<<3);
	printf("sizeof(long long) %d\n",sizeof(long long)<<3);
	printf("sizeof(size_t) %d\n",sizeof(size_t)<<3);
	printf("sizeof table :%d\n",sizeof(table));
	sprintf(pbuf,"%p",ppp);
	printf("===%s\n",pbuf);
	exit(0);
	pipe(fds);
 	fd=open("./test",O_RDWR, S_IRUSR| S_IWUSR ); 
	printf("Hello world\n");
	ppp=&var;
	pid=fork();
	if(pid>0)
	{
		*ppp=6;
		sprintf(buf,"right");
		write(fd,buf,5);
//		sync();
		close(fd);
		dup2(fds[1],1);
//		read(fd,buf3,5);
		//write(fds[1],buf,5);
		        close(fds[0]);
        	close(fds[1]);
		printf("oooooooooh\n");
		printf("child:%d-%d\n",fds[0],fds[1]);
	}else{
		sleep(1);
		read(fds[0],buf2,100);
		if(0> read(fd,buf3,5)) printf("read error\n");
		printf("parent:%d-%d,%s,%d,%s\n",fds[0],fds[1],buf2,*ppp,buf3);
	}
//	return 0;
}
