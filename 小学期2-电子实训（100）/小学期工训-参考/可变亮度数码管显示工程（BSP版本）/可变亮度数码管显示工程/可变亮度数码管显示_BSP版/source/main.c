#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "displayer.H" 
#include "key.H" 

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致
#ifdef _displayer_H_                          //显示模块选用时必须。（数码管显示译码表，用戶可修改、增加等） 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* 序号:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* 显示:   0   1    2    3    4     5    6    7   8    9  (无)   下-  中-  上-  上中-  中下-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* 带小数点     0         1         2         3         4         5         6         7         8         9        */
#endif

char scannum=7;

void myKey_callback()
{ char k;
	k=GetKeyAct(enumKey1);
	if( k == enumKeyPress ) scannum++;
	k=GetKeyAct(enumKey2);
	if( k == enumKeyPress ) scannum--;
}

void my100mS_callback()
{ LedPrint(scannum);
	SetDisplayerArea(0,scannum);
  Seg7Print(1,2,10,3,4,10,5,6);	
}

void main() 
{ DisplayerInit();  
	KeyInit();
	SetEventCallBack(enumEventSys100mS, my100mS_callback);
	SetEventCallBack(enumEventKey, myKey_callback);
  MySTC_Init();	    
	while(1)             	
		{ MySTC_OS();    
		}	             
}                 