#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <execinfo.h>

void print_trace_opt(void)
{
    int i;
    const int NTRACE = 32; // Maximum call stack depth.
    void *traceback[NTRACE]; // Will hold instruction pointers

    // Use a shell command to lookup addresses.
    // Ref. addr2line(1), which is part of binutils.
    char cmd[128] = "addr2line -f -e ";
    // Use the symlink /proc/self/exe to get the name of the executable.
    // This prevents us from having to keep a copy of argv[0] somewhere.
    char *prog = cmd + strlen(cmd);
    int r = readlink("/proc/self/exe",prog,sizeof(cmd)-(prog-cmd)-1);
    printf("cmd: %s\n", cmd);
    // ... error checking omitted for brevity
    // Run the shell command - ref. popen(3)
    FILE *fp = popen(cmd, "w");
    // ... error checking omitted for brevity
    int depth = backtrace(traceback, NTRACE);
    for (i = 0; i < depth; i++)
    {
        // Send the addresses to addr2line.
        // addr2line prints to stdout.
	printf("----addr :%p\n",traceback[i]);
        fprintf(fp, "%p\n", traceback[i]);
        // ... error checking omitted for brevity
    }
    fclose(fp);
}

/* Obtain a backtrace and print it to stdout. */
void
print_trace (void)
{
  void *array[10];
  size_t size;
  char **strings;
  size_t i;

  size = backtrace (array, 10);
  strings = backtrace_symbols (array, size);

  printf ("Obtained %zd stack frames.\n", size);

  for (i = 0; i < size; i++)
     printf ("%s\n", strings[i]);

  free (strings);
}
int myfunc(void){
	int i ;
	i +=1;
	print_trace_opt();
    
}
int main (char argc,char* argv){
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s, sfd;

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
  hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
  hints.ai_flags = AI_PASSIVE;     /* All interfaces */
  for (rp = result; rp != NULL; rp = rp->ai_next)
  {
	printf("%d \n",rp->ai_addr);	
  }
  myfunc();  
}
