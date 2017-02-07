#include "osd.h"

static inline unsigned blendop(unsigned color_blending_mode,
                               unsigned color_blending_src_factor,
                               unsigned color_blending_dst_factor,
                               unsigned alpha_blending_mode,
                               unsigned alpha_blending_src_factor,
                               unsigned alpha_blending_dst_factor)
{
    return (color_blending_mode << 24) |
           (color_blending_src_factor << 20) |
           (color_blending_dst_factor << 16) |
           (alpha_blending_mode << 8) |
           (alpha_blending_src_factor << 4) |
           (alpha_blending_dst_factor << 0);
}

int ge2d_op_fill_rect(void *para)
{
	ge2d_op_para_t  op_para;
	int r=0xff;
	int a=0xff ;
	ge2d_op_ctl_t *control=(ge2d_op_ctl_t*)para;
	osd_obj_t *this_osd=(osd_obj_t *)control->pt_osd;

	
	ioctl( this_osd->ge2d_fd, FBIOPUT_GE2D_CONFIG, &control->config) ;
	op_para.src1_rect.x=0;
	op_para.src1_rect.y=0;
	op_para.src1_rect.w=1920;
	op_para.src1_rect.h=1080;
	//RBGA
	 op_para.color=a|r<<24;	
	 
	
	ioctl( this_osd->ge2d_fd, FBIOPUT_GE2D_FILLRECTANGLE, &op_para) ;
	return 0;
}
int ge2d_op_blend(void *para)
{
	
	config_para_t ge2d_config;
	osd_obj_t **osd=(osd_obj_t **)para;
	ge2d_op_para_t  op_para;
	osd_obj_t  *osd0=*osd++,*osd1=*osd;

	ge2d_config.op_type=OSD1_OSD0;
	ge2d_config.alu_const_color=0x0000ffff;
	ioctl( osd0->ge2d_fd, FBIOPUT_GE2D_CONFIG, &ge2d_config) ;
	op_para.src1_rect.x=100;
	op_para.src1_rect.y=100;
	op_para.src1_rect.w=380;
	op_para.src1_rect.h=380;

	op_para.src2_rect.x=200;
	op_para.src2_rect.y=200;
	op_para.src2_rect.w=380;
	op_para.src2_rect.h=380;

	op_para.dst_rect.x=600;
	op_para.dst_rect.y=300;
	op_para.dst_rect.w=380;
	op_para.dst_rect.h=380;


	op_para.op=blendop( 
			OPERATION_ADD,
                    /* color blending src factor */
                    COLOR_FACTOR_CONST_COLOR,
                    /* color blending dst factor */
                    COLOR_FACTOR_ONE,
                    /* alpha blending_mode */
                    OPERATION_ADD,
                    /* alpha blending src factor */
                    ALPHA_FACTOR_CONST_ALPHA,
                    /* color blending dst factor */
                    ALPHA_FACTOR_ONE_MINUS_CONST_ALPHA);
	ioctl( osd0->ge2d_fd, FBIOPUT_GE2D_BLEND, &op_para) ;
	return 0;
	
}
int ge2d_op_blit(void *para)
{
	config_para_t ge2d_config;
	osd_obj_t **osd=(osd_obj_t **)para;
	ge2d_op_para_t  op_para;
	int move_mode;
	osd_obj_t  *osd0=*osd++,*osd1=*osd;

	printf("blit type \n"  \
		  "1	move block from osd1 to osd0 \n" \
		  "2	move block from osd0 to osd0 \n" \
		  "please input blit type number: ");
	scanf("%d",&move_mode);
	if(move_mode==1)
	{
		ge2d_config.op_type=OSD1_OSD0;
	}
	else
	{
		ge2d_config.op_type=OSD0_OSD0;
	}
	ge2d_config.alu_const_color=0xff0000ff;
	ioctl( osd0->ge2d_fd, FBIOPUT_GE2D_CONFIG, &ge2d_config) ;

	op_para.src1_rect.x=100;
	op_para.src1_rect.y=100;
	op_para.src1_rect.w=380;
	op_para.src1_rect.h=380;

	op_para.dst_rect.x=200;
	op_para.dst_rect.y=300;
	op_para.dst_rect.w=380;
	op_para.dst_rect.h=380;

	
	ioctl( osd0->ge2d_fd, FBIOPUT_GE2D_BLIT, &op_para) ;
	
	return 0;
}
int ge2d_op_stretch_blit(void *para)
{
	config_para_t ge2d_config;
	osd_obj_t **osd=(osd_obj_t **)para;
	ge2d_op_para_t  op_para;
	int stretch_mode;
	osd_obj_t  *osd0=*osd++,*osd1=*osd;
	
	printf("blit type \n"  \
		  "1	stretch  block from osd1 to osd0 \n" \
		  "2	stretch  block from osd0 to osd0 \n" \
		  "please input blit type number: ");
	scanf("%d",&stretch_mode);
	if(stretch_mode==1)
	{
		ge2d_config.op_type=OSD1_OSD0;
	}
	else
	{
		ge2d_config.op_type=OSD0_OSD0;
	}
	ge2d_config.alu_const_color=0xff0000ff;
	ioctl( osd0->ge2d_fd, FBIOPUT_GE2D_CONFIG, &ge2d_config) ;
	op_para.src1_rect.x=50;
	op_para.src1_rect.y=50;
	op_para.src1_rect.w=200;
	op_para.src1_rect.h=200;

	op_para.dst_rect.x=150;
	op_para.dst_rect.y=150;
	op_para.dst_rect.w=400;
	op_para.dst_rect.h=400;
	ioctl( osd0->ge2d_fd, FBIOPUT_GE2D_STRETCHBLIT, &op_para) ;
	return 0;
}
void  display_ge2d_op_menu(void)
{
	printf("\nge2d_op menu : \n"
	"	1	fill rect, \n" 		\
	"	2	blit\n" 			\
	"	3	stretch blit \n"	\
	"	4	blend	\n"		\
	"	5	multi process	\n"	\
	"please input menu item number: ");
}



int  test_ge2d_op(void* para)
{
	int i,mode;
	osd_obj_t  *osd[2] ;
	int menu_item;
	ge2d_op_ctl_t  ge2d_control;
	
	
	//first we must select one color format for each osd device .
	while(1)
	{
	display_color_mode_list();
	for (i=0;i<2;i++)
	{
		printf("please select one color mode for osd%d:",i);
		scanf("%d",&mode) ;
		if(mode<OSD_TYPE_16_655 || mode>OSD_TYPE_32_ARGB)
		{
			printf("invalid color format for osd device\r\n");
			return -1;
		}
		osd[i]=(osd_obj_t*)create_osd_obj(mode,i);
		if(NULL==osd[i]) 
		{
			printf("can't create osd object for  osd%d\r\n",i);
			return -1;
		}
	}
	//create osd object success ,begin ge2d operation.
	display_ge2d_op_menu();
	scanf("%d",&menu_item) ;
	if(menu_item >= GE2D_MAX_OP_NUMBER || menu_item <=0 )
	{
		printf("invalid input menu item number \r\n");
		return -1;
	}
	
	switch(menu_item)
	{
		case GE2D_OP_FILL_RECT:
		ge2d_control.config.op_type=OSD0_OSD0 ;
		//ge2d_control.config.alu_const_color=0xff0000ff;
		ge2d_control.pt_osd=osd[0] ;
		osd[0]->ge2d_op_func.fill_rect(&ge2d_control);
		sleep(1);
		osd[0]->show(osd[0]);
		sleep(3);
		break ;
		case GE2D_OP_BLEND:
		osd[1]->show(osd[1]);
		osd[0]->show(osd[0]);
		sleep(1);
		osd[0]->ge2d_op_func.blend(osd);	
		sleep(3);
		break;
		break;	
		case GE2D_OP_BLIT:
		osd[1]->show(osd[1]);
		osd[0]->show(osd[0]);
		sleep(1);	
		osd[0]->ge2d_op_func.blit(osd);	
		sleep(3);
		break;
		case GE2D_OP_STRETCH_BLIT:
		osd[1]->show(osd[1]);
		osd[0]->show(osd[0]) ;
		sleep(1);		
		osd[0]->ge2d_op_func.stretch_blit(osd);				
		sleep(3);
		break;	
		case GE2D_OP_MUL_PROCESS:
		multi_process_test(NULL);
		break;
	}
	printf("press Enter to exit\r\n");
	scanf("%c%c",&mode,&mode);
	destroy_osd_obj(osd[0]);
	destroy_osd_obj(osd[1]);
	}
	return 0;
}
