#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "displayer.H" 
#include "Key.h"
#include "beep.h"
#include "music.h"

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��
#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* ��С����     0         1         2         3         4         5         6         7         8         9        */
#endif

unsigned char tone[]={0x11,0x10,0x12,0x10,0x13,0x10,0x14,0x10,0x15,0x10};
												 
void main() 
{
	BeepInit();
	displayerInit();
	MusicPlayerInit();
	SetDisplayerArea(4,7);
	SetMusic(100,0xFA,&tone,sizeof(tone),enumMscDrvSeg7andLed);
	//ABCDEFG���ֱ��Ӧ 0xFA 0xFB 0xFC 0xFD 0xFE 0xFF 0xF9
	SetPlayerMode(enumModePlay);
	
  MySTC_Init();	    
	while(1)             	
		{ MySTC_OS();    
		}	             
}                 