#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "displayer.H" 
#include "hall.h"

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致
#ifdef _displayer_H_                          //显示模块选用时必须。（数码管显示译码表，用戶可修改、增加等） 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* 序号:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* 显示:   0   1    2    3    4     5    6    7   8    9  (无)   下-  中-  上-  上中-  中下-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* 带小数点     0         1         2         3         4         5         6         7         8         9        */
#endif
unsigned char a=0x0f;
unsigned char b=0x00;												 
												 
void myHall_callback()
{ 
	if( GetHallAct() == enumHallGetClose) b=0xff;
	else b=0x00;
	if( GetHallAct() == enumHallGetAway) b=0x00;
}

void my100mS_callback()
{ if (a == 0xf0) a=0xe1;
	else if (a == 0xe1) a=0xc3;
	else if (a == 0xc3) a=0x87;
	else if (a == 0x87) a=0x0f;
	else a=(a<<1);
	LedPrint(a&b);
}

void main() 
{ 
	HallInit();
	displayerInit();
	SetEventCallBack(enumEventHall,myHall_callback);
	SetEventCallBack(enumEventSys100mS,my100mS_callback);

  MySTC_Init();	    
	while(1)             	
		{ MySTC_OS();    
		}	             
}                 