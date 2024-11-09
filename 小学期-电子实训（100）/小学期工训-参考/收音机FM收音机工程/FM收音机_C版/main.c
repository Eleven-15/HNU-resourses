#include "KEY.H"
//#include "led.h"
#include "Delay.h"
#include "FM.h"
														  
unsigned char Radio_Write_Data[8]={					 
	0xc0,0x11,          //02H:音频输出，静音禁用，12MHZ，启用状态
	0x1a,0x50,          //03H:97500KHZ,频率使能87-108M(US/Europe)，步进100KHZ
	0x40,0x02,		    //04H:1-0为GPIO1(10为低，灯亮；11为高，灯灭)，...
	0x88,0xa5 };	    //a5中的5为初始音量
unsigned long frequency=0;
unsigned int chan=0;
unsigned char volume; 
/*系统初始化函数
*初始化系统的A/D,IO口以及收音机芯片（RDA5807P）
*/
void Init()
{ 
	Init_KEY();		
	Config_LED();
		
	/*FM硬件初始化*/
	 P4M0=0x00;
   P4M1=0x00;
	
	 P5M0=0xff;
	 P5M1=0x00;
	
	 Init_Radio();
	P2_3 = 0;
}

/*主函数
*初始化系统，然后循环调用按键监听函数以及数码管显示函数
*/
void main()
{
	Init();	
	while(1)
	{
		Frequency_Display();
		Search_Keyscan();
		KeyScan();			
	}
}