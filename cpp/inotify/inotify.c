#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <sys/inotify.h>

/*
#define IN_ACCESS 0x00000001
#define IN_MODIFY 0x00000002
#define IN_ATTRIB 0x00000004
#define IN_CLOSE_WRITE 0x00000008
#define IN_CLOSE_NOWRITE 0x00000010
#define IN_OPEN 0x00000020
#define IN_MOVED_FROM 0x00000040
#define IN_MOVED_TO 0x00000080
#define IN_CREATE 0x00000100
#define IN_DELETE 0x00000200
#define IN_DELETE_SELF 0x00000400
#define IN_MOVE_SELF 0x00000800
#define IN_UNMOUNT 0x00002000
#define IN_Q_OVERFLOW 0x00004000
#define IN_IGNORED 0x00008000
#define IN_CLOSE (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE)
#define IN_MOVE (IN_MOVED_FROM | IN_MOVED_TO)
#define IN_ONLYDIR 0x01000000
#define IN_DONT_FOLLOW 0x02000000
#define IN_EXCL_UNLINK 0x04000000
#define IN_MASK_ADD 0x20000000
#define IN_ISDIR 0x40000000
#define IN_ONESHOT 0x80000000
#define IN_ALL_EVENTS (IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE |   IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM |   IN_MOVED_TO | IN_DELETE | IN_CREATE | IN_DELETE_SELF |   IN_MOVE_SELF)
#define IN_CLOEXEC O_CLOEXEC
#define IN_NONBLOCK O_NONBLOCK
*/

char * event_array[] = {
	"File was accessed",
	"File was modified",
	"File attributes were changed",
	"writtable file closed",
	"Unwrittable file closed",
	"File was opened",
	"File was moved from X",
	"File was moved to Y",
	"Subfile was created",
	"Subfile was deleted",
	"Self was deleted",
	"Self was moved",
	"",
	"Backing fs was unmounted",
	"Event queued overflowed",
	"File was ignored"
};

static int  init(){
	printf("init inotify\n");
 	return inotify_init();	
}

static void* observe_thread(void *para){
	
	int a;
	int fd=*(int*)para;
	printf("start monitor thread\n");
	char event_buf[512];
	struct inotify_event *event;
	while(1){
		int event_pos = 0;
        	int num_bytes = read(fd, event_buf, sizeof(event_buf));
		int i ;	
            	printf("***** ! got a  event!\n");
		if (num_bytes < (int)sizeof(*event))
        	{
            		if (errno == EINTR)
                	continue;

            		printf("***** ERROR! got a short event!\n");
            		return;
        	}
		while (num_bytes >= (int)sizeof(*event))
		{
			int event_size;
			event = (struct inotify_event *)(event_buf + event_pos);

			char* path = NULL;

			if (event->len > 0)
			{
				path = event->name;
			}
			//printf("got event: %s,[mask]0x%x,[wd]%d\n",event->path,event->mask,event->wd);
			int mask=event->mask;
			for ( i = 0; mask > 0 ; i++  ) {
				if ( mask & 0x1 )	
				printf("-----%s,[%s],[wd]%d\n",event->name,event_array[i],event->wd);
				mask>>=1;
			}

			event_size = sizeof(*event) + event->len;
			num_bytes -= event_size;
			event_pos += event_size;
		}	

	}

}

static int  start_watching(int fd,char *path ,int mask) {

	return inotify_add_watch(fd, path, mask);

}
int main (char argc,char **argv) {
	
	int mfd;
	pthread_t t_handle;
	static char notify_path[100];
	mfd = init();
	if (argc > 1){
		strcpy(notify_path, argv[1]);
	} else {
		strcpy(notify_path, "/tmp/b");
	}
	int mask=IN_ALL_EVENTS; 
	start_watching(mfd,notify_path,mask);
	pthread_create(&t_handle,NULL,observe_thread,&mfd);
	pthread_join(t_handle,NULL);




}
