#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/queue.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/wait.h> 
#include <linux/input.h>



void  delay (int i, int type  )
{
	int k,j,z;
	int limit;
	switch (type)
	{
		case 0:
			limit =0xffff;
				break;
		case 1:
			limit =0xff;
			break;
	}
	
	for (j=0;j<i;j++)
	{
		for(k=0;k<limit;k++)
		{
			z++;
			z++;
			z++;
		}
	}
}
static unsigned int 
translate_event( const struct input_event *levt)
{

     switch (levt->type) {
          case EV_KEY:
               return levt->code;

          case EV_REL:
          case EV_ABS:
          default:
	    break ;	  	
               ;
     }

     return -1;
}

int test_key(void *para)
{
	int  intput_fd=-1;
	fd_set rfds,wfds;
	struct timeval tv;
	int retval ;
	int exit_enable=0;
	int lace=0x1000;
	int i,readlen;
	
	 struct input_event levt[64];
	 
	intput_fd=open("/dev/input/event0",O_RDWR);//如果设备节点创建在/dev/input目录下，就是/dev/input/event0
	
	 
	

	while(!exit_enable)
	{
		tv.tv_sec = 0;
		tv.tv_usec = 10;
		FD_ZERO(&rfds);
		FD_SET(intput_fd, &rfds);
		retval = select(intput_fd+1, &rfds, NULL, NULL, &tv);  //wait demux data
		if(retval==-1)
		{
			exit_enable=1;
		}
		else if(retval)
		{
			if(FD_ISSET(intput_fd,&rfds)) 
			{
				printf("new key in \r\n");
				readlen =read(intput_fd,levt, sizeof(levt));
				 for (i=0; i<readlen / sizeof(levt[0]); i++) {
				 	
					printf("----key 0x%x %s @@@\r\n",translate_event(&levt[i]),levt[i].value==2?"repeat":\
															levt[i].value==1?"press":"release");	
				 }
			}
		}
	}	
	
	return 0;
}

