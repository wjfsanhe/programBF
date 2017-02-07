/*******************************************************************************
#	 	luvcview: Sdl video Usb Video Class grabber           .        #
#This package work with the Logitech UVC based webcams with the mjpeg feature. #
#All the decoding is in user space with the embedded jpeg decoder              #
#.                                                                             #
# 		Copyright (C) 2005 2006 Laurent Pinchart &&  Michel Xhaard     #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 2 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program; if not, write to the Free Software                  #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA    #
#                                                                              #
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>
#include <pthread.h>
#include <linux/videodev.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include "v4l2uvc.h"
#include "osd.h"

#define VB_SIZE 0x100000

struct vdIn *videoIn;
static  int  g_exit=0;
static   int osd1,osd2,videoPort;
static int signal_handler(int num)
{
	g_exit=1;
	return 1;
}
static int alarm_handler(int num)
{
	osdOff(osd1);
    	osdOn(osd2);
}
int main(int argc, char *argv[])
{
	const char *videodevice = NULL;
	const char *mode = NULL;
	int format = V4L2_PIX_FMT_YUYV;
	int i;
	int grabmethod = 1;
	int width = 352;
	int height = 288;
	float fps = 15;			// Requested frame rate
	int queryformats = 0;
	int querycontrols = 0;
	int readconfigfile = 0;
	char *separateur;
	char *sizestring = NULL;
	char *fpsstring  = NULL;
	int enableRawStreamCapture = 0;
	int enableRawFrameCapture = 0;
  

	for (i = 1; i < argc; i++) {
		/* skip bad arguments */
		if (argv[i] == NULL || *argv[i] == 0 || *argv[i] != '-') {
			continue;
		}
		if (strcmp(argv[i], "-d") == 0) {
			if (i + 1 >= argc) {
				printf("No parameter specified with -d, aborting.\n");
				exit(1);
			}
			videodevice = strdup(argv[i + 1]);
		}
		if (strcmp(argv[i], "-g") == 0) {
			/* Ask for read instead default  mmap */
			grabmethod = 0;
		}
		if (strcmp(argv[i], "-f") == 0) {
			if (i + 1 >= argc) {
				printf("No parameter specified with -f, aborting.\n");
				exit(1);
			}
			mode = argv[i + 1];

			if (strcasecmp(mode, "yuv") == 0 || strcasecmp(mode, "YUYV") == 0) {
				format = V4L2_PIX_FMT_YUYV;
			} else if (strcasecmp(mode, "jpg") == 0 || strcasecmp(mode, "MJPG") == 0) {
				format = V4L2_PIX_FMT_MJPEG;
			} else {
				printf("Unknown format specified. Aborting.\n");
				exit(1);
			}
		}
		if (strcmp(argv[i], "-s") == 0) {
			if (i + 1 >= argc) {
				printf("No parameter specified with -s, aborting.\n");
				exit(1);
			}

			sizestring = strdup(argv[i + 1]);

			width = strtoul(sizestring, &separateur, 10);
			if (*separateur != 'x') {
				printf("Error in size use -s widthxheight\n");
				exit(1);
			} else {
				++separateur;
				height = strtoul(separateur, &separateur, 10);
				if (*separateur != 0)
					printf("hmm.. dont like that!! trying this height\n");
			}
		}
		if (strcmp(argv[i], "-i") == 0){
			if (i + 1 >= argc) {
				printf("No parameter specified with -i, aborting.\n");
				exit(1);
			}
			fpsstring = argv[i + 1];
			fps = strtof(fpsstring, &separateur);
			if(*separateur != '\0') {
				printf("Invalid frame rate '%s' specified with -i. "
						"Only numbers are supported. Aborting.\n", fpsstring);
				exit(1);
			}
		}
		if (strcmp(argv[i], "-S") == 0) {
			/* Enable raw stream capture from the start */
			enableRawStreamCapture = 1;
		}
		if (strcmp(argv[i], "-c") == 0) {
			/* Enable raw frame capture for the first frame */
			enableRawFrameCapture = 1;
		}
		if (strcmp(argv[i], "-C") == 0) {
			/* Enable raw frame stream capture from the start*/
			enableRawFrameCapture = 2;
		}
		if (strcmp(argv[i], "-L") == 0) {
			/* query list of valid video formats */
			queryformats = 1;
		}
		if (strcmp(argv[i], "-l") == 0) {
			/* query list of valid video formats */
			querycontrols = 1;
		}

		if (strcmp(argv[i], "-r") == 0) {
			/* query list of valid video formats */
			readconfigfile = 1;
		}
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			printf("usage: uvcview [-h -d -g -f -s -i -c -o -C -S -L -l -r]\n");
			printf("-h   print this message\n");
			printf("-d   /dev/videoX       use videoX device\n");
			printf("-g   use read method for grab instead mmap\n");
			printf("-f   choose video format (YUYV/yuv and MJPG/jpg are valid, MJPG is default)\n");
			printf("-i   fps           use specified frame rate\n");
			printf("-s   widthxheight      use specified input size\n");
			printf("-c   enable raw frame capturing for the first frame\n");
			printf("-C   enable raw frame stream capturing from the start\n");
			printf("-S   enable raw stream capturing from the start\n");
			printf("-L   query valid video formats\n");
			printf("-l   query valid controls and settings\n");
			printf("-r   read and set control settings from luvcview.cfg (save/restore with F1/F2)\n");
			exit(0);
		}
	}

	if (videodevice == NULL || *videodevice == 0) {
		videodevice = "/dev/video0";
	}

	videoIn = (struct vdIn *) calloc(1, sizeof(struct vdIn));
	if ( queryformats ) {
		/* if we're supposed to list the video formats, do that now and go out */
		check_videoIn(videoIn,(char *) videodevice);
		free(videoIn);
		exit(1);
	}
	if (init_videoIn
			(videoIn, (char *) videodevice, width, height, fps, format,
			 grabmethod, NULL) < 0) {
		printf("init_videoIn failed.\n");
		exit(1);
	}
	/* if we're supposed to list the controls, do that now */
	if ( querycontrols )
		enum_controls(videoIn->fd);

	/* if we're supposed to read the control settings from a configfile, do that now */
	if ( readconfigfile )
		load_controls(videoIn->fd);

	if (enableRawStreamCapture) {
		videoIn->captureFile = fopen("stream.raw", "wb");
		if(videoIn->captureFile == NULL) {
			perror("Unable to open file for raw stream capturing");
		} else {
			printf("Starting raw stream capturing to stream.raw ...\n");
		}
	}
	if (enableRawFrameCapture)
		videoIn->rawFrameCapture = enableRawFrameCapture;

    osd1=osdOpen(0);
    osd2=osdOpen(1);
    osdOff(osd1);
    osdOn(osd2);

	osd_obj_t  *osd ;
 	int   src_fd;
	short   *src,*dst,tmp,*dst1;
	void	*ori;
	struct stat buf;
	int  j,k=0; 
        FILE * fd;
        void   *ori1;

#define DISPLAY_X   0
#define DISPLAY_Y   0
//        ori1 = (void*)malloc(width*height*2);
        printf("start recording~~~\n");
	//first we must select one color format for each osd device .
	osd=(osd_obj_t*)create_osd_obj(OSD_TYPE_YUV_422, 1);
       // fd = fopen("xxx.yuv", "wb");
//	while (videoIn->signalquit) {
	 signal(SIGINT, signal_handler);
	 signal(SIGALRM,alarm_handler);
	 alarm(3);
	while (!g_exit && k<0x50) {
          
	    usleep(1000000/videoIn->fps);
		k++;
		
		if (uvcGrab(videoIn) < 0) {
			printf("Error grabbing\n");
			break;
		}
		if(videoIn->buf.bytesused){
	            ori=osd->fbp+DISPLAY_X+DISPLAY_Y*osd->finfo->line_length;
	            dst=(short*)osd->fbp ;
		    src = videoIn->mem[videoIn->buf.index];
	            //memset(osd->fbp,0,osd->screen_size);
  //                  dst1=(short*)ori1;
		    for(i=0;i<height;i++){
                        dst=(short*)ori;
					//	printf("i=%d--\n",i);
		        for(j=0;j<width;j++){
				//	printf("j=%d\n",j);
		            tmp=(*src>>8&0xff)|(*src<<8&0xff00);
		            *dst=tmp;
//			    *dst1=tmp;
		            src++;
		            dst++;
//                            dst1++;
		            }

			    ori+=osd->finfo->line_length;
	            }
         //           fwrite(ori1, width*height*2, 1, fd);
		    }

	}
    osdClose(osd1);
    osdClose(osd2);
    signal(SIGALRM,NULL); 
 signal(SIGINT, NULL);	
//free(ori1);
//fclose(fd);
printf("got in\n");
	close_v4l2(videoIn);
printf("got out\n");	
    free(videoIn);
	printf("Cleanup done. Exiting ...\n");
}
