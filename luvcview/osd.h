#ifndef   _OSD_H_
#define   _OSD_H_
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/queue.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/wait.h> 
#include <sys/stat.h>

#define  BMP_FILE_NAME		"/usr/bin/picture.bmp"

#define  BITMAP_USE_FILE
#define   FBIOPUT_GE2D_BLEND			 0x4700
/**blend op relative macro*/
#define OPERATION_ADD           0    //Cd = Cs*Fs+Cd*Fd
#define OPERATION_SUB           1    //Cd = Cs*Fs-Cd*Fd
#define OPERATION_REVERSE_SUB   2    //Cd = Cd*Fd-Cs*Fs
#define OPERATION_MIN           3    //Cd = Min(Cd*Fd,Cs*Fs)
#define OPERATION_MAX           4    //Cd = Max(Cd*Fd,Cs*Fs)
#define OPERATION_LOGIC         5

#define COLOR_FACTOR_ZERO                     0
#define COLOR_FACTOR_ONE                      1
#define COLOR_FACTOR_SRC_COLOR                2
#define COLOR_FACTOR_ONE_MINUS_SRC_COLOR      3
#define COLOR_FACTOR_DST_COLOR                4
#define COLOR_FACTOR_ONE_MINUS_DST_COLOR      5
#define COLOR_FACTOR_SRC_ALPHA                6
#define COLOR_FACTOR_ONE_MINUS_SRC_ALPHA      7
#define COLOR_FACTOR_DST_ALPHA                8
#define COLOR_FACTOR_ONE_MINUS_DST_ALPHA      9
#define COLOR_FACTOR_CONST_COLOR              10
#define COLOR_FACTOR_ONE_MINUS_CONST_COLOR    11
#define COLOR_FACTOR_CONST_ALPHA              12
#define COLOR_FACTOR_ONE_MINUS_CONST_ALPHA    13
#define COLOR_FACTOR_SRC_ALPHA_SATURATE       14

#define ALPHA_FACTOR_ZERO                     0
#define ALPHA_FACTOR_ONE                      1
#define ALPHA_FACTOR_SRC_ALPHA                2
#define ALPHA_FACTOR_ONE_MINUS_SRC_ALPHA      3
#define ALPHA_FACTOR_DST_ALPHA                4
#define ALPHA_FACTOR_ONE_MINUS_DST_ALPHA      5
#define ALPHA_FACTOR_CONST_ALPHA              6
#define ALPHA_FACTOR_ONE_MINUS_CONST_ALPHA    7

#define LOGIC_OPERATION_CLEAR       0
#define LOGIC_OPERATION_COPY        1
#define LOGIC_OPERATION_NOOP        2
#define LOGIC_OPERATION_SET         3
#define LOGIC_OPERATION_COPY_INVERT 4
#define LOGIC_OPERATION_INVERT      5
#define LOGIC_OPERATION_AND_REVERSE 6
#define LOGIC_OPERATION_OR_REVERSE  7
#define LOGIC_OPERATION_AND         8
#define LOGIC_OPERATION_OR          9
#define LOGIC_OPERATION_NAND        10
#define LOGIC_OPERATION_NOR         11
#define LOGIC_OPERATION_XOR         12
#define LOGIC_OPERATION_EQUIV       13
#define LOGIC_OPERATION_AND_INVERT  14
#define LOGIC_OPERATION_OR_INVERT   15 

#define BLENDOP_ADD           0    //Cd = Cs*Fs+Cd*Fd
#define BLENDOP_SUB           1    //Cd = Cs*Fs-Cd*Fd
#define BLENDOP_REVERSE_SUB   2    //Cd = Cd*Fd-Cs*Fs
#define BLENDOP_MIN           3    //Cd = Min(Cd*Fd,Cs*Fs)
#define BLENDOP_MAX           4    //Cd = Max(Cd*Fd,Cs*Fs)
#define BLENDOP_LOGIC         5    //Cd = Cs op Cd
#define BLENDOP_LOGIC_CLEAR       (BLENDOP_LOGIC+0 )
#define BLENDOP_LOGIC_COPY        (BLENDOP_LOGIC+1 )
#define BLENDOP_LOGIC_NOOP        (BLENDOP_LOGIC+2 )
#define BLENDOP_LOGIC_SET         (BLENDOP_LOGIC+3 )
#define BLENDOP_LOGIC_COPY_INVERT (BLENDOP_LOGIC+4 )
#define BLENDOP_LOGIC_INVERT      (BLENDOP_LOGIC+5 )
#define BLENDOP_LOGIC_AND_REVERSE (BLENDOP_LOGIC+6 )
#define BLENDOP_LOGIC_OR_REVERSE  (BLENDOP_LOGIC+7 )
#define BLENDOP_LOGIC_AND         (BLENDOP_LOGIC+8 )
#define BLENDOP_LOGIC_OR          (BLENDOP_LOGIC+9 )
#define BLENDOP_LOGIC_NAND        (BLENDOP_LOGIC+10)
#define BLENDOP_LOGIC_NOR         (BLENDOP_LOGIC+11)
#define BLENDOP_LOGIC_XOR         (BLENDOP_LOGIC+12)
#define BLENDOP_LOGIC_EQUIV       (BLENDOP_LOGIC+13)
#define BLENDOP_LOGIC_AND_INVERT  (BLENDOP_LOGIC+14)
#define BLENDOP_LOGIC_OR_INVERT   (BLENDOP_LOGIC+15) 






//macro used by this lib 
#define  FBIOPUT_GE2D_STRETCHBLIT_NOALPHA   	0x4702
#define   FBIOPUT_GE2D_BLEND			 0x4700
#define  FBIOPUT_GE2D_BLIT    			 0x46ff
#define  FBIOPUT_GE2D_STRETCHBLIT   	0x46fe
#define  FBIOPUT_GE2D_FILLRECTANGLE   	0x46fd
#define  FBIOPUT_GE2D_SRCCOLORKEY   	0x46fc
#define  FBIOPUT_OSD_SRCCOLORKEY		0x46fb
#define  FBIOPUT_OSD_SRCKEY_ENABLE	0x46fa
#define  FBIOPUT_GE2D_CONFIG			0x46f9
#define VB_SIZE         0x100000

#define  U32   		unsigned int 
#define  U16   		unsigned short 
#define  U8			unsigned char
#define  INT32		int
#define	INT16		short
#define  INT8S		char	
#define  UINT8 		U8
#define  UINT16		U16
#define  UINT32		U32
	
#define  swap(x,y,t)     {(t)=(x);(x)=(y);(y)=(t);}
#ifndef min
#define	min(a,b)	(((a) < (b)) ? (a) : (b))
#endif
#define 	ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))



typedef struct {
     int            x;   /* X coordinate of its top-left point */
     int            y;   /* Y coordinate of its top-left point */
     int            w;   /* width of it */
     int            h;   /* height of it */
}osd_rectangle_t;

typedef  struct {
	U32   color ;
	osd_rectangle_t src1_rect;
	osd_rectangle_t src2_rect;
	osd_rectangle_t dst_rect;
}osd_para_t ;

typedef   struct {
	U32	 disp_start_x;
	U32	 disp_start_y;
}disp_offset_t;


typedef  enum {
	OSD_TYPE_16_565 =16,
	OSD_TYPE_16_844 =10,
	OSD_TYPE_16_6442 =11 ,
	OSD_TYPE_16_4444_R = 12,
	OSD_TYPE_16_4642_R = 13,
	OSD_TYPE_16_1555_A=14,
	OSD_TYPE_16_4444_A = 15,
	OSD_TYPE_16_655 =9,
	
	OSD_TYPE_24_6666_A=19,
	OSD_TYPE_24_6666_R=20,
	OSD_TYPE_24_8565 =21,
	OSD_TYPE_24_5658 = 22,
	OSD_TYPE_24_888_B = 23,
	OSD_TYPE_24_RGB = 24,

	OSD_TYPE_32_BGRA=29,
	OSD_TYPE_32_ABGR = 30,
	OSD_TYPE_32_ARGB=32,
	OSD_TYPE_32_RGBA=31,

	OSD_TYPE_YUV_422=33,
}osd_disp_type_t;
typedef enum  	
{
		OSD0_OSD0 =0,
		OSD0_OSD1,	 
		OSD1_OSD1,
		OSD1_OSD0,
		TYPE_INVALID,
}ge2d_src_dst_t;

enum   GE2D_OP_TYPE{
	GE2D_OP_FILL_RECT=1,
	GE2D_OP_BLIT,
	GE2D_OP_STRETCH_BLIT,
	GE2D_OP_BLEND,
	GE2D_OP_MUL_PROCESS,
	GE2D_MAX_OP_NUMBER
};

typedef struct {
	unsigned long  addr;
	unsigned int	w;
	unsigned int	h;
}config_planes_t;
typedef    struct {
	int  op_type;
	int  alu_const_color;
	unsigned int src_format;
	unsigned int dst_format ; //add for src&dst all in user space.

	config_planes_t src_planes[4];
	config_planes_t dst_planes[4];
}config_para_t;


typedef  struct {
	config_para_t  config;
	void  *pt_osd ;
}ge2d_op_ctl_t;



typedef struct {
     int            x;   /* X coordinate of its top-left point */
     int            y;   /* Y coordinate of its top-left point */
     int            w;   /* width of it */
     int            h;   /* height of it */
}rectangle_t;
typedef  struct {
	unsigned int   color ;
	rectangle_t src1_rect;
	rectangle_t src2_rect;
	rectangle_t	dst_rect;
	int op;
}ge2d_op_para_t ;

typedef  int	(*func_test_t)(void *);

typedef  struct {
	int	(*fill_rect)(void* para);
	int	(*blit)(void* para);
	int	(*stretch_blit)(void* para);
	int	(*blend)(void *para);
}ge2d_op_func_t;

typedef  struct {
	char 	name[40];
	char 	osd_index;
	int		bpp;
	int		line_width;
	int 		screen_size;
	int 		fbfd ;
	int		ge2d_fd;
	char		*fbp;
	struct fb_var_screeninfo *vinfo ;
	struct fb_var_screeninfo *save_vinfo;
	struct fb_fix_screeninfo *finfo ;
	int	(*draw)(void* para);
	int 	(*show)(void *para);
	ge2d_op_func_t  ge2d_op_func;
	void  *para ;
}osd_obj_t ;

typedef  struct {
	INT32	handle;
	U8*		ptr;
	U32		fix_line_length;
	U32		xres;
	U32		yres;
	U32		bpp;
}osd_info_t ;

typedef struct T_DEC_PARAMETER
{
	INT32    			i32DecoderID;	 
	UINT8 			u8StreamType;	 
 	UINT32 			u32ACodeType;	 
 	UINT32 			u32VCodeType;	 
	UINT16 			u16VPID;		 
	UINT16 			u16APID;		 
}T_DEC_PARA;
enum   STREAM_TYPE{
	STREAM_ES,
	STREAM_TS,
	STREAM_PS
	};
enum  AUDIO_TYPE{
	A_MPG=1,
	};
enum  VIDEO_TYPE{
	V_MPG1=1,
	V_MPG2,
	V_MPG4,	
	};
#pragma pack(1)
typedef struct tagBITMAPFILEHEADER
{
	U16	bfType;  //BM
	U32 bfSize;   //file size 
	U16	bfReserved1;  //0
	U16	bfReserved2;  //0
	U32 bfOffBits;  	//bitmap data offset to  file header	
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	U32 biSize;  //this structure occupy size 
	U32	biWidth; //bitmap width (pixel unit)
	U32 biHeight; //bitmap height (pixel unit)
	U16 biPlanes; // 1
	U16 biBitCount;//bits of erery pixel . must be one of follow values 1(double color)
			// 4(16color) 8(256 color) 24(true color)
	U32 biCompression; // bitmap compresstion type must be one of 0 (uncompress)
					  // 1(BI_RLE8) 2(BI_RLE4)
	U32 biSizeImage; 	// bitmap size 
	U32	biXPelsPerMeter; //bitmap horizontal resolution.
	U32	biYPelsPerMeter; //bitmap vertical resolution.
	U32 biClrUsed;	//bitmap used color number.
	U32 biClrImportant;//bitmap most important color number during display process.
} BITMAPINFOHEADER;
#pragma pack()
/****************************************************
*
*     func name 	:  DecInit   
*     	 desp  	:  send data to decoder 
*     	 para  	:  i32DecoderID    decoder handle   
*				   pData  data pointer 
*				   nLen    data length.  
*					
*	return value	:    >0   write data success  ,return write byte.
*			   	     <0   fail 
*
*****************************************************/
 INT32 DecData(INT32 i32DecoderID, UINT8* pData, INT32 nLen) ;
/****************************************************
*
*     func name 	:  DecInit   
*     	 desp  	:  init one media path. 
*     	 para  	:  i32PlayerID   player id    
*				   pDecoderPara    type is T_DEC_PARA
*				     
*					
*	return value	:    0   success  
*			   	   -1   fail 
*
*****************************************************/
INT32 DecInit(INT32 i32PlayerID, void *pDecoderPara);

/****************************************************
*
*     func name 	:  osdOpen   
*     	 desp  	:  get osd layer handle  
*     	 para  	:  index  0 : osd1  1:osd2 
*	return value	:  >0  osd handle  
*			   	   <0  fail 
*
*****************************************************/
INT32 osdOpen(INT32   index );
/****************************************************
*
*     func name 	:  osdClose   
*     	 desp  	:  close one osd layer by it's handle  
*     	 para  	:  osdHandle   
*	return value	:    0   success  
*			   	   -1   fail 
*
*****************************************************/
INT32 osdClose(INT32   osdHandle );
/****************************************************
*
*     func name 	:  osdOn   
*     	 desp  	:  switch on one osd layer   
*     	 para  	:  osdHandle   
*	return value	:    0   success  
*			   	   -1   fail 
*
*****************************************************/
INT32 osdOn(INT32  osdHandle) ;
/****************************************************
*
*     func name 	:  osdOff   
*     	 desp  	:  switch off one osd layer . 
*     	 para  	:  osdHandle   
*	return value	:    0   success  
*			   	   -1   fail 
*
*****************************************************/
INT32 osdOff(INT32  osdHandle) ;
INT32 osdSetColorKey(osd_obj_t* osd_this,INT32 iColorKey);

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
INT32 osdDispRect(osd_obj_t *  osd_this,U32  argb,U16 x0,U16 y0,U16 x1,U16 y1) ;
/****************************************************
*
*     func name 	:  osdEraseRect   
*     	 desp  	:  erase rectangle at a giving postion.
*     	 para  	:  osdHandle   
*				    x0,y0		: top left point.
*				    x1,y1		: bottom right point.
*					
*	return value	:    0   success  
*			   	   -1   fail 
*
*****************************************************/
INT32 osdEraseRect(INT32 osdHandle,U16 x0,U16 y0,U16 x1,U16 y1) ;

/****************************************************
*
*     func name 	:  osdInit   
*     	 desp  	:  osd layer init   
*     	 para  	:  osdHandle
*	return value	:  0  SUCCESS 
*			   	   <0  fail 
*
*****************************************************/
INT32 osdInit(INT32 osdHandle,U8 bpp);
/****************************************************
*
*     func name 	:  UninitOsd   
*     	 desp  	:  osd layer UNinit   
*     	 para  	:  osdHandle
*	return value	:  0  SUCCESS 
*			   	   <0  fail 
*
*****************************************************/
INT32 UninitOsd(INT32 osdHandle);
extern  int  test_osd_display(void* para);
extern  int  test_ge2d_op(void* para);
extern int 	test_osd_colorkey(void* para);
extern int destroy_osd_obj(osd_obj_t* osd_obj) ;
//ge2d_op
extern int ge2d_op_fill_rect(void *para) ;
extern int ge2d_op_blit(void *para) ;
extern int ge2d_op_stretch_blit(void *para) ;
 extern int ge2d_op_blend(void *para) ;
extern  int   multi_process_test(void* para);
 //key
 extern  int  test_key(void* para);
 //osd
 extern  int  show_bitmap(char *p, unsigned line_width, unsigned xres, unsigned yres, unsigned bpp);
#endif

