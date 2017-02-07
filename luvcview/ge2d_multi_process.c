#include "osd.h"
#include <linux/input.h>
#include <sys/poll.h>
#include	<pthread.h>
#include <sys/time.h> 
#include <signal.h>
#define  OSD0_INDEX		0
#define  OSD1_INDEX		1


#define  SCREEN_W		(osd->vinfo->xres)
#define  SCREEN_H		(osd->vinfo->yres)
#define  OSD0_BACKGROUND_COLOR   0x222222ff
#define  OSD1_BACKGROUND_COLOR	 0x444444ff

#define  TRANSPARENT_COLOR	  0x00000000
#define  OSD0_BUTTON_COLOR     0x0000ffff

#define  OSD1_BUTTON_COLOR	  0xff0000ff
#define  OSD2_BUTTON_COLOR	  0x006600ff
#define  OSD3_BUTTON_COLOR	  0xff00ffff

#define  BUTTON_START_X		50
#define  BUTTON_START_Y		50
#define  OSD0_BUTTON_WIDTH		100
#define  OSD0_BUTTON_HEIGHT		50
#define  OSD1_BUTTON_WIDTH		OSD0_BUTTON_HEIGHT
#define  OSD1_BUTTON_HEIGHT	OSD0_BUTTON_WIDTH
#define  OSD2_BUTTON_WIDTH		OSD1_BUTTON_WIDTH
#define  OSD2_BUTTON_HEIGHT	OSD1_BUTTON_HEIGHT
#define  OSD3_BUTTON_WIDTH		OSD0_BUTTON_WIDTH
#define  OSD3_BUTTON_HEIGHT	OSD0_BUTTON_HEIGHT




typedef void (*sighandler_t)(int); 



static void  handle_term_int(int sig_num)
{
	return ;
}
//color format: ARGB
static int  ge2d_config(osd_obj_t*  osd)
{
	config_para_t  config ;

	switch (osd->osd_index)
	{
		case OSD0_INDEX:
		config.op_type=OSD0_OSD0;	
		break;
		default:
		config.op_type=OSD1_OSD1;	
		break;	
	}
	config.alu_const_color=0xff0000ff;
	ioctl( osd->ge2d_fd, FBIOPUT_GE2D_CONFIG, &config) ;
	return 0;
}
static int  fill_rect(osd_obj_t*  osd,rectangle_t  *rect,int  color)
{
	
	ge2d_op_para_t  op_para;

	ge2d_config(osd);
	op_para.src1_rect.x=rect->x;
	op_para.src1_rect.y=rect->y;
	op_para.src1_rect.w=rect->w;
	op_para.src1_rect.h=rect->h;
	op_para.color=color;
	ioctl( osd->ge2d_fd , FBIOPUT_GE2D_FILLRECTANGLE, &op_para) ;
	return 0;
}
static int  create_osd_canvas(osd_obj_t *osd)
{
	rectangle_t  rect;
	switch (osd->osd_index)
	{
		case 0:
		rect.x=0;
		rect.y=0;
		rect.w=SCREEN_W/2;
		rect.h=SCREEN_H;
		fill_rect(osd,&rect,OSD0_BACKGROUND_COLOR);
		rect.x+=SCREEN_W/2;
		fill_rect(osd,&rect,TRANSPARENT_COLOR);
		rect.x=0;
		rect.y=SCREEN_H/2;
		rect.w=SCREEN_W;
		rect.h=SCREEN_H/2;
		fill_rect(osd,&rect,TRANSPARENT_COLOR);
		break;
		case 1:
		rect.x=SCREEN_W/2;
		rect.y=0;
		rect.w=SCREEN_W/2;
		rect.h=SCREEN_H/2;	
		fill_rect(osd,&rect,OSD1_BACKGROUND_COLOR);
		break;
		case 2:
		rect.x=0;
		rect.y=SCREEN_H/2;
		rect.w=SCREEN_W/2;
		rect.h=SCREEN_H/2;	
		fill_rect(osd,&rect,OSD1_BACKGROUND_COLOR);	
		break;	
		case 3:
		rect.x=SCREEN_W/2;
		rect.y=SCREEN_H/2;
		rect.w=SCREEN_W/2;
		rect.h=SCREEN_H/2;	
		fill_rect(osd,&rect,OSD0_BACKGROUND_COLOR);	
		break;		
	}
	return 0;
}
static int  draw_sample_button(osd_obj_t *osd)
{
	rectangle_t  osd0_rect={BUTTON_START_X,BUTTON_START_Y,OSD0_BUTTON_WIDTH,OSD0_BUTTON_HEIGHT};
	rectangle_t  osd1_rect={SCREEN_W/2+BUTTON_START_X,BUTTON_START_Y,OSD1_BUTTON_WIDTH,OSD1_BUTTON_HEIGHT};
	rectangle_t  osd3_rect={BUTTON_START_X+SCREEN_W/2,BUTTON_START_Y+SCREEN_H/2,OSD0_BUTTON_WIDTH,OSD0_BUTTON_HEIGHT};
	rectangle_t  osd2_rect={BUTTON_START_X,BUTTON_START_Y+SCREEN_H/2,OSD1_BUTTON_WIDTH,OSD1_BUTTON_HEIGHT};
	switch (osd->osd_index )
	{
		case OSD0_INDEX:
		fill_rect(osd,&osd0_rect,OSD0_BUTTON_COLOR);	
		break;
		case OSD1_INDEX:
		fill_rect(osd,&osd1_rect,OSD1_BUTTON_COLOR);	
		break;
		case 2:
		fill_rect(osd,&osd2_rect,OSD2_BUTTON_COLOR);
		break;
		case 3:
		fill_rect(osd,&osd3_rect,OSD3_BUTTON_COLOR);
		break;	
		
	}
	return 0;
}
static int  move_sample_button(osd_obj_t *osd)
{
	rectangle_t  osd0_rect={BUTTON_START_X,BUTTON_START_Y,OSD0_BUTTON_WIDTH,OSD0_BUTTON_HEIGHT};
	rectangle_t  osd1_rect={SCREEN_W/2+BUTTON_START_X,BUTTON_START_Y,OSD1_BUTTON_WIDTH,OSD1_BUTTON_HEIGHT};
	rectangle_t  osd3_rect={BUTTON_START_X+SCREEN_W/2,BUTTON_START_Y+SCREEN_H/2,OSD0_BUTTON_WIDTH,OSD0_BUTTON_HEIGHT};
	rectangle_t  osd2_rect={BUTTON_START_X,BUTTON_START_Y+SCREEN_H/2,OSD1_BUTTON_WIDTH,OSD1_BUTTON_HEIGHT};
	static rectangle_t osd0_last_rect={0,0,0,0};
	static rectangle_t osd1_last_rect={0,0,0,0};
	static rectangle_t osd2_last_rect={0,0,0,0};
	static rectangle_t osd3_last_rect={0,0,0,0};
	
	switch (osd->osd_index )
	{
		case 0:
		if(osd0_last_rect.w!=0)
		{
			fill_rect(osd,&osd0_last_rect,OSD0_BACKGROUND_COLOR);
		}
		osd0_rect.x=rand()%(SCREEN_W/2-OSD0_BUTTON_WIDTH);
		osd0_rect.y=rand()%(SCREEN_H/2-OSD0_BUTTON_HEIGHT);
		if(osd0_rect.x < (OSD0_BUTTON_WIDTH+BUTTON_START_X) && osd0_rect.y < (OSD0_BUTTON_HEIGHT+BUTTON_START_Y))
		{
			osd0_rect.x =OSD0_BUTTON_WIDTH+BUTTON_START_X;
			osd0_rect.y =OSD0_BUTTON_HEIGHT+BUTTON_START_Y;
		}
		fill_rect(osd,&osd0_rect,OSD0_BUTTON_COLOR);	
		osd0_last_rect=osd0_rect;
		break;
		case 1:
		if(osd1_last_rect.w!=0)
		{
			fill_rect(osd,&osd1_last_rect,OSD1_BACKGROUND_COLOR);
		}	
		osd1_rect.x=rand()%(SCREEN_W/2-OSD1_BUTTON_WIDTH) + SCREEN_W/2 ;
		osd1_rect.y=rand()%(SCREEN_H/2-OSD1_BUTTON_HEIGHT); 
		if(osd1_rect.x <  (SCREEN_W/2+OSD1_BUTTON_WIDTH+BUTTON_START_X) && osd1_rect.y < (OSD1_BUTTON_HEIGHT+BUTTON_START_Y))
		{
			osd1_rect.x =SCREEN_W/2+OSD1_BUTTON_WIDTH+BUTTON_START_X;
			osd1_rect.y =OSD1_BUTTON_HEIGHT+BUTTON_START_Y;
		}	
		fill_rect(osd,&osd1_rect,OSD1_BUTTON_COLOR);
		osd1_last_rect=osd1_rect;
		break;
		case 2:
		if(osd2_last_rect.w!=0)
		{
			fill_rect(osd,&osd2_last_rect,OSD1_BACKGROUND_COLOR);
		}
		osd2_rect.x=rand()%(SCREEN_W/2-OSD2_BUTTON_WIDTH) ;
		osd2_rect.y=rand()%(SCREEN_H/2-OSD2_BUTTON_HEIGHT)+SCREEN_H/2; //360 -100
		if(osd2_rect.x < (OSD2_BUTTON_WIDTH+BUTTON_START_X)  && osd2_rect.y < (SCREEN_H/2+OSD2_BUTTON_HEIGHT+BUTTON_START_Y))
		{
			osd2_rect.x =OSD2_BUTTON_WIDTH+BUTTON_START_X;
			osd2_rect.y =SCREEN_H/2+OSD2_BUTTON_HEIGHT+BUTTON_START_Y;
		}
		fill_rect(osd,&osd2_rect,OSD2_BUTTON_COLOR);	
		osd2_last_rect=osd2_rect;
		break;
		case 3:
		if(osd3_last_rect.w!=0)
		{
			fill_rect(osd,&osd3_last_rect,OSD0_BACKGROUND_COLOR);
		}
		osd3_rect.x=rand()%(SCREEN_W/2-OSD3_BUTTON_WIDTH)+SCREEN_W/2;
		osd3_rect.y=rand()%(SCREEN_H/2-OSD3_BUTTON_HEIGHT) + SCREEN_H/2;
		if(osd3_rect.x < (SCREEN_W/2+OSD3_BUTTON_WIDTH+BUTTON_START_X) && osd3_rect.y < (SCREEN_H/2+OSD3_BUTTON_HEIGHT+BUTTON_START_Y))
		{
			osd3_rect.x =SCREEN_W/2+OSD3_BUTTON_WIDTH+BUTTON_START_X;
			osd3_rect.y =SCREEN_H/2+OSD3_BUTTON_HEIGHT+BUTTON_START_Y;
		}
		fill_rect(osd,&osd3_rect,OSD3_BUTTON_COLOR);	
		osd3_last_rect=osd3_rect;
		break;
	}
	return 0;
}
static  int kill_all_child_process(int *child_pid,int count)
{
	int status;
	pid_t  pid;
	int exit=0;
	int i;
	for(i=0;i<count;i++)
	kill(child_pid[i],SIGKILL);
	for(i=0;i<count;i++)
	waitpid(child_pid[i],&status,0);
}
static int  parent_process(int *child_pid,int count)
{
	sigset_t  mask;
	sighandler_t  int_handle,term_handle;

	//install SIGTERM,SIGINT
	term_handle=signal(SIGTERM,handle_term_int);
	int_handle=signal(SIGINT,handle_term_int);
	sigemptyset(&mask);
	sigsuspend(&mask);
	kill_all_child_process(child_pid,count);
	signal(SIGTERM,term_handle);
	signal(SIGINT,int_handle);
	printf("exit multi process");
	return 0 ;
}
static int child_process(osd_obj_t*  osd)
{
	create_osd_canvas(osd);
	draw_sample_button(osd);
	while(1){
		move_sample_button(osd);
	}
	return 0;
}
int   create_one_child(osd_obj_t  * osd)
{
	static  int  index=0;
	int  pid;
	pid=fork();
	if(pid==0)
	{
		child_process(osd);
	}
	index ++;
	return pid;
}
int   multi_process_test(void* para)
{
#define  CHILD_PROCESS_NUM  4
	int  pid[CHILD_PROCESS_NUM],i;
	osd_obj_t  *osd[CHILD_PROCESS_NUM];

	
	for(i=0;i<CHILD_PROCESS_NUM;i++)
	{
		osd[i]=(osd_obj_t*)create_osd_obj(OSD_TYPE_32_ARGB,i);
	}
	for(i=0;i<CHILD_PROCESS_NUM;i++)
	{
		pid[i]=create_one_child(osd[i]);
	}
	parent_process(pid,CHILD_PROCESS_NUM);
	return 0;
}
