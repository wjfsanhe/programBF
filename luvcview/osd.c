#include  "osd.h"
#define   CONFIG_OSD_ANTIFLICKER   0


INT32  osdUpdateRegion(osd_obj_t *osd_this,U16 x0,U16 y0,U16 x1,U16 y1)//anti_flick
{
	config_para_t ge2d_config;
	ge2d_op_para_t  op_para;
	U16 tmp;

	if(x0>x1) 
	swap(x0,x1,tmp);
	if(y0>y1)
	swap(y0,y1,tmp);
	
	if(osd_this->osd_index==1)
	{
		ge2d_config.op_type=OSD1_OSD1;
	}
	else
	{
		ge2d_config.op_type=OSD0_OSD0;
	}
	ge2d_config.alu_const_color=0xff0000ff;
	ioctl( osd_this->ge2d_fd, FBIOPUT_GE2D_CONFIG, &ge2d_config) ;
	op_para.src1_rect.x=x0;
	op_para.src1_rect.y+=osd_this->vinfo->yres  ;
	op_para.src1_rect.w=x1-x0;
	op_para.src1_rect.h=y1-y0;

	op_para.dst_rect.x=x0;
	op_para.dst_rect.y=y0;
	op_para.dst_rect.w=op_para.src1_rect.w;
	op_para.dst_rect.h=op_para.src1_rect.h;
	ioctl( osd_this->ge2d_fd, FBIOPUT_GE2D_STRETCHBLIT, &op_para) ;
	
}
int  osd_show(void *para)
{
	osd_obj_t *this_osd=para;
	printf("bitmap loading...\r\n");
	show_bitmap(this_osd->fbp,this_osd->line_width,this_osd->vinfo->xres, \
					this_osd->vinfo->yres,this_osd->bpp);
#if CONFIG_OSD_ANTIFLICKER	
	osdUpdateRegion(this_osd,0 ,0,this_osd->vinfo->xres,this_osd->vinfo->yres);//anti_flick
#endif	
	return 0;
}

/*****************************************************
*
*	16bit mode 6442 : rgba 
*
******************************************************/
int  default_draw_func(void *para)
{
	osd_obj_t *this_osd=para;

	//osdDispRect(this_osd,0x40000000,0,0,720,700);
	osdDispRect(this_osd,0x80ff0000,100,200,500,500);	
	osdDispRect(this_osd,0x8000ff00,100,300,500,500);	
	osdDispRect(this_osd,0x800000ff,100,400,500,500);	
	osdDispRect(this_osd,0x80ffffff,100,50,500,150); 
	return 0;
}
int  draw_func_16bpp_844(void *para)
{
	osd_obj_t *this_osd=para;

	osdDispRect(this_osd,0x40000000,0,0,720,700);
	osdDispRect(this_osd,0x40ff0000,100,200,500,676);	
	osdDispRect(this_osd,0x4000ff00,100,300,500,700);	
	osdDispRect(this_osd,0x400000ff,100,400,500,700);	
	osdDispRect(this_osd,0x40ffffff,100,50,500,150); 
	return 0;
}
int  draw_func_16bpp_4444_r(void *para)
{
	osd_obj_t *this_osd=para;

	osdDispRect(this_osd,0x40000000,0,0,720,700);
	osdDispRect(this_osd,0x40ff0000,100,200,500,676);	
	osdDispRect(this_osd,0x4000ff00,100,300,500,700);	
	osdDispRect(this_osd,0x400000ff,100,400,500,700);	
	osdDispRect(this_osd,0x40ffffff,100,50,500,150); 
	return 0;
}
int  draw_func_16bpp(void *para)
{
	osd_obj_t *this_osd=para;

	osdDispRect(this_osd,0x80ff0000,100,100,320,400);	
	
	return 0;
}
int  draw_func_24bpp(void *para)
{
	osd_obj_t *this_osd=para;

	osdDispRect(this_osd,0x80200020,0,0,720,200);	
	osdDispRect(this_osd,0x80200020,0,300,720,400);
	return 0;
}
int draw_func_32bpp(void *para)
{
	osd_obj_t *this_osd=para;

	osdDispRect(this_osd,0x03ff00ff,0,0,720,700);	
	osdDispRect(this_osd,0x83ff00ff,0,300,720,400);
	
	return 0;
}
static void _fill_rect (U8 *p, U32 line_width, U32 x0, U32 y0,U32 x1,U32 y1, U32 bpp,U32 color)
{
    INT32  x, y;
    U8 *wp = p;
    INT32 count =0;

	if (bpp <= OSD_TYPE_32_ARGB && bpp >= OSD_TYPE_32_BGRA )
	{
		printf("input 32 bpp\r\n")	;
		 for (y = y0; y < y1; y++) {
      		  wp = &p[y * line_width + x0*4 ];
           	  for (x = x0; x <=x1 ; x++) {
            			*wp++ = color&0xff;  
               		*wp++ = color>>8&0xff;   
                		*wp++ = color>>16&0xff;  
				*wp++ = color>>24&0xff;  		
              	}
        	}
	}
	if (bpp <= OSD_TYPE_24_RGB && bpp >=OSD_TYPE_24_6666_A ) {
	     printf("input 24 bpp\r\n")	;
	     for (y = y0; y < y1; y++) {
      		  wp = &p[y * line_width + x0*3 ];
           	  for (x = x0; x <=x1 ; x++) {
            			*wp++ = color&0xff;  
               		*wp++ = color>>8&0xff;   
                		*wp++ = color>>16&0xff;   
              	}
        	}
    	}
   	 else if (bpp >=OSD_TYPE_16_655 && bpp <=OSD_TYPE_16_565) {
	 	
	 	printf("input 16 bpp: index%d\r\n",bpp)	;
	     for (y = y0; y <y1; y++) {
            wp = &p[y * line_width + x0*2] ;
            for (x = x0; x < x1; x++) {
			*wp++ = color&0xff;		
           	 	*wp++ = color>>8&0xff;
             }
			
        }
    	}
	
	
	 
}
/****************************************************
*
*     func name 	:  osdSetColorKey   
*     	 desp  	:  set osd color key 
*     	 para  	:  osdHandle   
*				   iColorKey  	   		: in 16bit or 24bit mode it is color key
*				   ColorKey                  a|color
*									a [b32..24]
*									color [b23..0]  bpp 24 mode
*									color [b15..0]  bpp 16 mode
*	return value	:    0   success  		 
*			   	   -1   fail 
*
*****************************************************/
INT32 osdSetColorKey(osd_obj_t* osd_this,INT32 iColorKey)
{
	 INT32  	enable=1;
	 U8 		osd_index;
	 
	if(osd_this->fbfd<=0) return -1;
	
	switch(osd_this->vinfo->bits_per_pixel)
	{
			case OSD_TYPE_24_RGB:
			case OSD_TYPE_16_655:
			case OSD_TYPE_16_565:
			case OSD_TYPE_16_844:
			case OSD_TYPE_24_888_B:
			if (ioctl(osd_this->fbfd, FBIOPUT_OSD_SRCKEY_ENABLE, &enable)) 
	  		return -1;
			if (ioctl(osd_this->fbfd, FBIOPUT_OSD_SRCCOLORKEY, &iColorKey))
			return -1;
			return  0;
			default :
			break;	
	}
	return  -1;
}
/*****************************************************
* func name	: init_osd
* para 	 	:  
*			vinfo:         varible screen information 
*			finfo	:		fix screen information
* return value: 
*			success :   return osd handle
*			fail	     :	   return value <0	
*****************************************************/

int  init_osd(int bpp,int osd_index,struct fb_var_screeninfo *vinfo, struct fb_fix_screeninfo *finfo, \
							struct fb_var_screeninfo *save_vinfo)
{
	int fbfd ;
	char osd_name[30];

	if (vinfo==NULL || finfo==NULL) return -1;
	osd_index=osd_index>0?1:0;
	sprintf(osd_name,"/dev/graphics/fb%d",osd_index);
	fbfd = open(osd_name, O_RDWR);
	 if (!fbfd) {
        printf("Error: cannot open framebuffer device.\n");
        return (-1);
   	 }
   	 printf("The framebuffer device was opened successfully.\n");
	 /* Get fixed screen information */
	 int j;
   	if (j = ioctl(fbfd, FBIOGET_FSCREENINFO, finfo)) {
        close(fbfd);
        printf("Error reading fixed information. %d\n", j);
        return (-2);
   	 }
    
    /* Get variable screen information */
    	if (ioctl(fbfd, FBIOGET_VSCREENINFO, vinfo)) {
        close(fbfd);
        printf("Error reading variable information.\n");
        return (-3);
    	}
	//memcpy(save_vinfo,vinfo,sizeof(struct fb_var_screeninfo));
	*save_vinfo=*vinfo;
        printf("xres:%d,yres:%d\n", vinfo->xres,vinfo->yres);
	printf("+++bpp is %d\r\n",bpp);
    	vinfo->bits_per_pixel=bpp;  //16bit 6442 mode                          	   
    	vinfo->activate=FB_ACTIVATE_FORCE ;
	printf("before put vscreen information\r\n");
    	if (ioctl(fbfd, FBIOPUT_VSCREENINFO, vinfo)) {     /* Figure out the size of the screen in bytes */
       close(fbfd);                                     //screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
       printf("Error setting variable information.\n"); 
	return -3;
    }
      	if (ioctl(fbfd, FBIOGET_FSCREENINFO, finfo)) {//maybe line length has changed
        close(fbfd);
        printf("Error reading fixed information.\n");
        return (-2);
   	 }	

	return  fbfd ;
}


char*	get_osd_buffer_pointer(int fbfd,struct fb_var_screeninfo *vinfo, struct fb_fix_screeninfo *finfo)
{
	char *buf_ptr;
	long int screensize = 0;//anti_flick
	printf("----xres_vir:%d,yres:%d,bpp:%d,fbfd %d\r\n",vinfo->xres_virtual,vinfo->yres,vinfo->bits_per_pixel,fbfd);
	screensize = vinfo->xres_virtual* vinfo->yres_virtual*vinfo->bits_per_pixel/8;
	buf_ptr=(char *)mmap(0, screensize, PROT_READ | PROT_WRITE,
        MAP_SHARED, fbfd, 0);
#if CONFIG_OSD_ANTIFLICKER	
	buf_ptr+=vinfo->xres_virtual*vinfo->yres*vinfo->bits_per_pixel/8;
#endif 
	return buf_ptr;
}
osd_obj_t*  create_osd_obj(int mode,int osd_index)
{
	osd_obj_t  *osd_obj;
	char*  fbp;
	int fbfd;
	char  ge2d_name[10];
	 struct fb_var_screeninfo 	 *vinfo,*save_vinfo ;
	 struct fb_fix_screeninfo 	 *finfo  ;
	 
	
	vinfo=(struct fb_var_screeninfo*)malloc(sizeof(struct fb_var_screeninfo)) ;
	finfo= (struct fb_fix_screeninfo*)malloc(sizeof(struct fb_fix_screeninfo));
	save_vinfo=(struct fb_var_screeninfo*)malloc(sizeof(struct fb_var_screeninfo)) ;
	printf("select mode is %d %d\r\n",mode, osd_index);
	fbfd = init_osd(mode,osd_index,vinfo,finfo,save_vinfo);
	if(fbfd <0) 
	{
		printf("open osd device error\r\n");
		return NULL ;
	}
	fbp = get_osd_buffer_pointer(fbfd,vinfo,finfo);
	printf("----fbp:0x%x\r\n",fbp);
   	if((int)fbp < 0)
	{
		printf("get framebuffer pointer error\r\n");
		return NULL;
   	}
	osd_obj=(osd_obj_t *)malloc(sizeof(osd_obj_t));
	if(NULL==osd_obj)  
	{
		printf("error alloc osd object\r\n");
		return NULL;
	}
	sprintf(osd_obj->name,"osd_%dbpp",vinfo->bits_per_pixel);
	printf("osd name is %s\r\n",osd_obj->name);
	osd_obj->bpp=mode;
    	osd_obj->line_width=finfo->line_length;
	printf("+++line width=>%d\r\n",osd_obj->line_width);
	osd_obj->screen_size= osd_obj->line_width * vinfo->yres;
	osd_obj->finfo=finfo ;
	osd_obj->vinfo=vinfo;
	osd_obj->fbfd=fbfd;
	osd_obj->save_vinfo=save_vinfo;
	osd_obj->fbp=fbp;
	osd_obj->osd_index=osd_index;
	osd_obj->ge2d_op_func.fill_rect=ge2d_op_fill_rect;
	osd_obj->ge2d_op_func.blit=ge2d_op_blit;
	osd_obj->ge2d_op_func.stretch_blit=ge2d_op_stretch_blit;
	osd_obj->ge2d_op_func.blend=ge2d_op_blend;
	osd_obj->para=NULL;
	osd_obj->show=osd_show;
	switch (osd_obj->bpp)
	{
		case OSD_TYPE_16_655:
		osd_obj->draw=default_draw_func ;	
		break;	
		case OSD_TYPE_16_844:
		osd_obj->draw=default_draw_func;	
		break;
		case OSD_TYPE_16_4444_R:
		osd_obj->draw=default_draw_func;	
		break;
		case OSD_TYPE_16_6442:
		osd_obj->draw=default_draw_func;
		break;
		case OSD_TYPE_24_RGB:
		osd_obj->draw=default_draw_func ;	
		break;
		case OSD_TYPE_32_ARGB:
		osd_obj->draw=draw_func_32bpp ;
		break;
		default :
		osd_obj->draw=default_draw_func ;	
		break;
	}
	strcpy(ge2d_name,"/dev/ge2d");
	fbfd = open(ge2d_name, O_RDWR);
	if (!fbfd) {
      		printf("Error: cannot open ge2d device.\n");
		osd_obj->ge2d_fd=-1;	
			
   	}else{
   		printf("create ge2d_device success\n");
		osd_obj->ge2d_fd=fbfd;
      	}
	return osd_obj;
}

/****************************************************
*
*     func name 	:  osdDispRect   
*     	 desp  	:  display rectangle at a giving postion.
*     	 para  	:  osdHandle   
*				    argb		:  32bit mode alpha (the highest byte) blue (the lowest byte)
*							   24bit mode represent  rgb  (red the highest byte)
*							   16bit mode  represent rgb  (red the highest byte)	
*				    x0,y0		: top left point.
*				    x1,y1		: bottom right point.
*					
*	return value	:    0   success  
*			   	   -1   fail 
*
*****************************************************/
INT32 osdDispRect(osd_obj_t* osd_this,U32  argb,U16 x0,U16 y0,U16 x1,U16 y1)
{
	osd_para_t	para;
	U16  		tmp;
	U8			r,g,b,a;
	U32  		index;
	struct fb_var_screeninfo *vinfo=osd_this->vinfo ;
	
      if(x0>vinfo->xres||x1>vinfo->xres||y0>vinfo->yres||y1>vinfo->yres) return -1;
	if(NULL==osd_this)   return -1;
	//adjust rect
	if(x0>x1) 
	swap(x0,x1,tmp);
	if(y0>y1)
	swap(y0,y1,tmp);
	
	//get every component value .
	a=argb>>24 & 0xff ;
	r=argb>>16 & 0xff ;  
	g=argb>>8  & 0xff ;
	b=argb&0xff ;
	
	switch(osd_this->bpp)
	{
		case  OSD_TYPE_32_RGBA:
    		para.color=a|b<<8|g<<16|r<<24;//special order.
    		para.src1_rect.x=x0;
		para.src1_rect.y=y0;
		para.src1_rect.w=x1-x0;
		para.src1_rect.h=y1-y0;
		//index=osd_this->osd_index*2;
	       //ioctl(osd_this->fbfd, 0x46f9, &index)	;
		//return ioctl( osd_this->fbfd, FBIOPUT_GE2D_FILLRECTANGLE, &para) ;
		break;
		case OSD_TYPE_24_RGB:
		para.color=(r<<16|g<<8|b);
		break;
		case OSD_TYPE_16_655:
		para.color=((b>>3&0x1f)|(g>>3&0x1f)<<5|(r>>2&0x3f)<<10);		
		//para.color=((b>>3&0x1f)<<11|(g>>3&0x1f)<<6|(r>>2&0x3f))*1.0/0xff*a;
		break;
		case OSD_TYPE_16_565:
		para.color=((b>>3&0x1f)|(g>>2&0x3f)<<5|(r>>3&0x1f)<<11);		
		//para.color=((b>>3&0x1f)<<11|(g>>3&0x1f)<<6|(r>>2&0x3f))*1.0/0xff*a;
		break;
		case OSD_TYPE_16_6442:
		para.color=(a>>6&0x3|(b>>4&0xf)<<2|(g>>4&0xf)<<6|(r>>2&0x3f)<<10);	
		break;
		case OSD_TYPE_16_844:
		para.color=((b>>4&0xf)<<0|(g>>4&0xf)<<4|(r)<<8);	
		break;	
		case OSD_TYPE_16_4444_R:
		para.color=((a>>4&0xf)|(b>>4&0xf)<<4|(g>>4&0xf)<<8|(r>>4&0xf)<<12);	
		break;	
		case OSD_TYPE_16_4642_R:
		para.color=((a>>6&0x3)|(b>>4&0xf)<<2|(g>>2&0x3f)<<6|(r>>4&0xf)<<12);	
		break;
		case OSD_TYPE_16_1555_A:
		para.color=((a>>7&0x1)<<15|(b>>3&0x1f)|(g>>3&0x1f)<<5|(r>>3&0x1f)<<10);	
		break;
		case OSD_TYPE_16_4444_A:
		para.color=((a>>4&0xf)<<12|(b>>4&0xf)|(g>>4&0xf)<<4|(r>>4&0xf)<<8);	
		break;
		case OSD_TYPE_24_6666_A:
		para.color=((a>>2&0x3f)<<18|(b>>2&0x3f)|(g>>2&0x3f)<<6|(r>>2&0x3f)<<12);	
		break;
		case OSD_TYPE_24_6666_R:
		para.color=((a>>2&0x3f)|(b>>2&0x3f)<<6|(g>>2&0x3f)<<12|(r>>2&0x3f)<<18);	
		break;
		case OSD_TYPE_24_8565:
		para.color=((a)<<16|(b>>3&0x1f)|(g>>2&0x3f)<<5|(r>>3&0x1f)<<11);	
		break;
		case OSD_TYPE_24_5658:
		para.color=((a)|(b>>3&0x1f)<<8|(g>>2&0x3f)<<13|(r>>3&0x1f)<<19);	
		break;
		case OSD_TYPE_24_888_B:
		para.color=((b)<<16|(g)<<8|(r));	
		break;
		case OSD_TYPE_32_BGRA:
		para.color=((a)|(b)<<24|(g)<<16|(r)<<8);	
		break;
		case OSD_TYPE_32_ABGR:
		para.color=((a)<<24|(b)<<16|(g)<<8|(r));	
		break;	
		case OSD_TYPE_32_ARGB:
		para.color=((a)<<24|(b)|(g)<<8|(r)<<16);	
		break;
	}
	_fill_rect(osd_this->fbp,
				osd_this->line_width,
				x0,y0,x1,y1,
				osd_this->bpp,
				para.color);

	//update region
#if CONFIG_OSD_ANTIFLICKER	
	osdUpdateRegion(osd_this,x0,y0,x1,y1); //anti_flick
#endif
		
}


int  deinit_osd(osd_obj_t* osd_obj)
{
	struct fb_var_screeninfo 	*vinfo=osd_obj->save_vinfo;
	int  fbfd=osd_obj->fbfd;

	printf("reset osd mode in deinit_osd\r\n ");
	vinfo->activate=FB_ACTIVATE_FORCE ;
 	ioctl(fbfd, FBIOPUT_VSCREENINFO, vinfo) ;
	printf("close file descriptor\r\n ");
	if(fbfd>0)
      close(fbfd);
	if(osd_obj->ge2d_fd >0)  
	close(osd_obj->ge2d_fd);   
	return  0 ;
}



int	release_osd_buffer_pointer(osd_obj_t* osd_obj)
{
#if CONFIG_OSD_ANTIFLICKER
	struct fb_var_screeninfo 	 *vinfo=osd_obj->vinfo;//anti_flick
	osd_obj->fbp-=vinfo->xres_virtual*vinfo->yres*vinfo->bits_per_pixel/8;
#endif
	return munmap(osd_obj->fbp,osd_obj->screen_size);
}
int destroy_osd_obj(osd_obj_t* osd_obj)
{
	release_osd_buffer_pointer(osd_obj);
	deinit_osd(osd_obj);
	if(osd_obj->vinfo ) free(osd_obj->vinfo);
	if(osd_obj->finfo) free(osd_obj->finfo) ;
	if(osd_obj->save_vinfo) free(osd_obj->save_vinfo) ;
	if(osd_obj) free(osd_obj) ;
	return 0;
}
/****************************************************
*
*     func name 	:  osdOn   
*     	 desp  	:  switch on one osd layer   
*     	 para  	:  osdHandle   
*	return value	:    0   success  
*			   	   -1   fail 
*
*****************************************************/
INT32 osdOn(INT32  osdHandle)
{
	U32  on_off=0;
	if(osdHandle <=0) return -1;
	return  ioctl(osdHandle, FBIOBLANK, on_off) ;
}
/****************************************************
*
*     func name 	:  osdOff   
*     	 desp  	:  switch off one osd layer . 
*     	 para  	:  osdHandle   
*	return value	:    0   success  
*			   	   -1   fail 
*
*****************************************************/
INT32 osdOff(INT32  osdHandle)
{
	U32  on_off=1;
	if(osdHandle <=0) return -1;
	return  ioctl(osdHandle, FBIOBLANK, on_off) ;
}

static  osd_info_t  osd_array[2]={
    {-1,0,0,0,0,0},
    {-1,0,0,0,0,0}
    } ; 
INT32 osdOpen(INT32   index )
{
    U8  dev_name[20];
    INT32    fbfd ;
    if (index >2) 
        return -1;
    if(osd_array[index].handle != -1)
        return -1 ;//has been opened 
    switch (index)	{
        case  0: //osd1
        sprintf((char *)dev_name,"/dev/graphics/fb0");
        break;
        case  1: //osd2
        sprintf((char *)dev_name,"/dev/graphics/fb1");
        break;
        }
    fbfd=open(dev_name, O_RDWR);
    if(!fbfd){
        return fbfd;
        }
    osd_array[index].handle=fbfd;
    return fbfd;
}

/*****************************************************
*      func name 	:  osdClose   
*     	 desp  	:  close one osd layer by it's handle  
*     	 para  	:  osdHandle   
*	return value	:    0   success  
*			   	   -1   fail 
******************************************************/
INT32 osdClose(INT32   osdHandle )
{
    int  i;	
    for (i=0;i<2;i++){
        if(osdHandle==osd_array[i].handle)	{
            munmap((void*)osdHandle, osd_array[i].fix_line_length*osd_array[i].yres);
            if( close(osdHandle) < 0 )
                return -1;
            osd_array[i].fix_line_length= 0;
            osd_array[i].handle=-1;
            osd_array[i].xres=0;
            osd_array[i].yres=0;
            osd_array[i].bpp=0;
            return 0;
            }
        }
    return  -1;
} 
