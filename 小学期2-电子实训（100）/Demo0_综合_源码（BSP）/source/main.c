/******************  STCBSP测试 综合Demo程序说明：STC_DemoV3.6 *************************** 
本STC_DemoV3示例程序（源程序由main.c及function.c、song.c三部分组成）功能描述如下：		 
		1，按键Key2切换"显示"和"按键操作"模式。模式值在LED上显示（二进制数）。模式有：
					 模式1：实时时钟（年月日）
					 模式2：实时时钟（时分秒）
					 模式3：温度、光照测量
					 模式4：音乐播放
					 模式5：FM收音机
					 模式6：超声波测距（需要在EXT上接超声波测距模块）
					 模式7：电子秤    （需要在EXT上接电子秤模块）
    2，数码管显示、导航按键功能：
		       在模式1下：数码管显示实时时钟RTC   "年年-月月-日日"，导航按键 "中"键 进入或退出"设置年月日"；"上、下、左、右"设置
		       在模式2下：数码管显示实时时钟RTC   "时时-分分-秒秒"，导航按键 "中"键 进入或退出"设置时分秒"；"上、下、左、右"设置
		       在模式3下：数码管显示温度、光照AD值"温温温  光光光", 导航按键无操作
					 在模式4下：数码管显示      "节拍率  音调音高  音符"，导航按键 "中"键 暂停/播放，"上、下"调整音调，"左、右"调整节拍率
           在模式5下：数码管显示      "音量   收音频率（MHz）"，导航按键 "中"键 保存当前收音参数到NVM（下次上电时，用该参数收音）
					                                                               "上、下"调整音亮，"左、右"调整收音频率
					 在模式6下：数码管显示       "       距离值（cm）"  ，导航按键无操作 
           在模式7下：数码管显示       "称重ADC值（符号数）"  ，导航按键无操作  
     3，按键1（按下时）：红外向外发送 "大家好！"。其它"STC-B学习板"（如用本程序）用串口助手（设置波特率1200bps，文本接收方式）可看到接收到的"大家好！"文本		
        按键3（抬起时）：串口1(参数：115200bps,8,N,1)向计算机发送 Hello！	 （串口助手、文本接收可方式）
		 4，振动传感器：（如果有音乐播放）控制音乐播放"暂停/继续"
		 5，霍尔传感器：有磁场接近时，（如果蜂鸣器空闲）发声报警（1350Hz，发1秒时间）
		 6，串口1：与计算机双向通信（波特率115200bps）
		           如果收到一个"AA 55"开头、大小8字节数据包，则将第7字节+1，再以波特率2400bps向串口2（485、EXT可选）转发此数据包
							 如果红外接口收到数据包（引导码+数据+结束码），则向串口1转发
		 7，串口2：可选择485（双向单工）、EXT（TTL Uart，双向双工）两个位置，工作波特率2400bps
		           如果收到一个"AA 55"开头、大小8字节数据包，则将第7字节+2，再向红外Ir口转发此数据包（NEC_R05d编码协议）
		 8，红外收发接口：
							 如果红外接口收到数据包（引导码+数据+结束码），则蜂鸣器发声（1000Hz，300mS），并向串口1转发；
               如果数据包包头为"AA 55"，并：第3字节为 F1，则调整收音频率（第4、5字节，BCD码，收音频率值，0.1MHz）（数据需有效：887～1080），
							                                                      音量（第6字节数据）（数据需有效：0～15）       ，第7字节+4
							                              第3字节为 F2，则调整RTC时分秒（第4、5、6字节数据，BCD码）（数据需有效），第7字节+4
																						第3字节为 F3，则调整RTC年月日（第4、5、6字节数据，BCD码）（数据需有效），第7字节+4
																				调整值存入NVM，
																				蜂鸣器发声（1000Hz，600mS）
																				并向串口1转发；

设计：徐成（电话：18008400450）    2021年9月5日，2022年6月20日更新
***************************************************************************************************************************/

/********************************** STCBSP Ver3.6 说明 ********************************************************************
STCBSP提供的底层支持和应用层函数支持以下"STC-B学习板"功能同时工作：
     1，数码管显示
		 2，LED指示灯显示
		 3，实时时钟
		 4，温度光照测量
		 5，音乐播放
		 6，FM收音机
		 7，EXT扩展接口（电子秤、超声波测距、旋转编码器、PWM控制，4选1工作）
		 8，振动传感器
		 9，霍尔传感器
		 10，步进电机控制
		 11，串口1通信
		 12，串口2通信（485、485上ModBus、EXT扩展接口，3选1）
		 13，红外遥控
		 14，红外收发通信
		 15，非易失性NVM存储（DS1302提供31字节，M24C02提供256字节）
具体使用方法请参见各模块头文件。

  (1) 系统工作时钟频率可以在main.c中修改 SysClock赋值（单位Hz）。
      如：code long SysClock=11059200; 定义系统工作时钟频率为11059200Hz（也即11.0592MHz）		
      系统工作频率必须与实际工作频率（下载时选择的）一致，以免与定时相关的所有功能出现误差或错误。
	(2) 使用方法：
	        1，在工程中加载main.c文件和STC_BSP.lib库文件
					2，在main.c中选择包含以下头文件（如果要使用可选模块提供的函数和方法，就必须包含其头文件）	：
								#include "STC15F2K60S2.H"        //必须，"STC-B学习板"使用MCU指定的头文件
								#include "sys.H"                 //必须，sys（MySTC_OS调度程序）头文件
								#include "display.H"             //可选，display（显示模块）头文件。          
								#include "key.H"                 //可选，key（按键模块）头文件。
								#include "hall.H"                //可选，hall（霍尔传感器模块）头文件。
								#include "Vib.h"	               //可选，Vib（振动传感器模块）头文件。								 
								#include "beep.H"                //可选，beep（蜂鸣器模块）头文件。					
								#include "music.h"               //可选，music（音乐播放）头文件。	
								#include "adc.h"                 //可选，adc（热敏、光敏、导航按键、扩展接口ADC功能）头文件。	
								#include "uart1.h"               //可选，uart1（串口1通信）头文件。
								#include "uart2.h"               //可选，uart2（串口2通信）头文件。
							  #include "stepmotor.h"           //可选，步进电机      
                #include "DS1302.h"              //可选，DS1302实时时钟
                #include "M24C02.h"              //可选，24C02非易失性存储器
                #include "FM_Radio.h"	           //可选，FM收音机
                #include "EXT.h"                 //可选，EXT扩展接口（电子秤、超声波测距、旋转编码器、PWM输出控制电机快慢和正反转）
                #include "IR.h"	                 //可选，38KHz红外通信
								
					3，MySTC_Init()是sys初始化函数，必须执行一次；
					   MySTC_OS()是sys调度函数，应置于while（1）循环中；
					4，各可选模块如果选用，必须在使用模块其它函数和方法前执行一次模块所提供的驱动函数（设置相关硬件、并在sys中加载其功能调度）：
						    DisplayerInit();      //显示模块驱动 
								KeyInit();            //按键模块驱动
								BeepInit();	          //蜂鸣器模块驱动
								MusicPlayerInit();    //蜂鸣器播放音乐驱动
	              HallInit();           //霍尔传感器模块驱动                      
	              VibInit();            //振动传感器模块驱动          
	              AdcInit();            //模数转换ADC模块驱动（含温度、光照、导航按键与按键Key3、EXT扩展接口上的ADC）
	              StepMotorInit();      //步进电机模块驱动	                  
    	          DS1302Init();         //DS1302实时时钟驱动
	              FMRadioInit();	      //FM收音机驱动           
                EXTInit();            //扩展接口驱动（含电子秤、超声波测距、旋转编码器、PWM输出，但不含EXT上Uart2和与之相关应用）
	              Uart1Init();          //Uart1（串口1）驱动：USB上（与计算机通信）              
                Uart2Init();          //Uart2（串口2）驱动：485接口UART、485接口上ModBus、或EXT扩展接口（多机通信、Uart方式模块如蓝牙模块）   （2022年5月2日修改）
	              IrInit();             //38KHz红外通信模块驱动
								
							说明：有部分模块不需要驱动；驱动函数有些有参数。（具体见各模块头文件说明）
								
          5，sys和各模块共提供以下事件：
					      numEventSys1mS:              1mS事件                        （"1毫秒时间间隔到"事件）
					      enumEventSys10mS:            10mS事件                       （"10毫秒时间间隔到"事件）
				        enumEventSys100mS:           100mS事件                      （"100毫秒时间间隔到"事件）
								enumEventSys1S:              1S事件                         （"1秒时间间隔到"事件）
								enumEventKey:                按键事件                       （K1、K2、K3 三个按键有"按下"或"抬起"操作）
								enumEventHall:               霍尔传感器事件                 （霍尔传感器有"磁场接近"或"磁场离开"事件）
 								enumEventVib:                振动传感器事件                 （振动感器检测到"振动"事件）
								enumEventNav:                导航按键事件                   （导航按键5个方向、或按键K3 有"按下"或"抬起"操作）
								enumEventXADC:               扩展接口上完成一次ADC转换事件  （P1.0、P1.1采取到一组新数据）
								enumEventUart1Rxd            串口1上收到一个符合格式定义的数据包事件。串口1：USB上与PC机通信
								enumEventUart2Rxd            串口2上收到一个符合格式定义的数据包事件。串口2：485上UART、EXT上UART、或485上ModBus协议         （2022年5月2日修改）
	              enumEventIrRxd:              红外接收器Ir上收到一个数据包						
								
								对这些事件，应采用"回调函数"方法响应（即用sys提供的SetEventCallBack()设置用户回调函数），以提高系统性能。
								
					6，各可选模块提供的其它函数和具体使用方法请参见：
					      各模块头文件中的说明；
								main.c提供的推荐程序框架和部分示例；
								其它可能技术文档或应用示例
						
编写：徐成（电话18008400450）   2021年2月26日设计，2022年5月1日更新
**************************************************************************/

//******* 用户程序段1：用户程序包含文件 *************
#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "displayer.H" 
#include "key.h"
#include "hall.h"
#include "Vib.h"
#include "beep.h"
#include "music.h"
#include "adc.h"
#include "uart1.h"
#include "uart2.h"
#include "stepmotor.h"
#include "DS1302.h"
#include "M24C02.h"
#include "FM_Radio.h"	
#include "EXT.h"
#include "IR.h"   

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致
#ifdef _displayer_H_                          //显示模块选用时必须。（数码管显示译码表，用戶可修改、增加等） 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* 序号:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* 显示:   0   1    2    3    4     5    6    7   8    9  (无)   下-  中-  上-  上中-  中下-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* 带小数点     0         1         2         3         4         5         6         7         8         9        */
#endif
//******* 用户程序段2：用户自定义函数声明 *************//


//******* 用户程序段3：用户程序全局变量定义 *************//
#include "song.c"                              //举例。song.c中编写了音乐（同一首歌）编码

struct_DS1302_RTC t={0x30,0,9,0x06,9,1,0x21};  //举例。 实时时钟数据结构：秒、分、时、日、月、周、年。初值：2021年9月6日，周一，9：00：30
struct_FMRadio    FM;                          //举例。 FM收音机数据结构：收音频率、音量、GP1、GP2、GP3。初值：95.5MHz，音量5，灭、灭、亮
struct_SysPerF    SysPer;                      //举例。 系统性能数据结构：每秒主循环次数4字节、每秒轮询丢失次数1字节
struct_ADC        ADCresult;                   //举例。 热敏、光敏测量AD值           
unsigned char Music_tone,Music_PM;             //举例。 音乐播放音调、节凑（每分钟节拍数）

unsigned char rxd[8];                         //举例。通信（串口1、串口2、红外共用）缓冲区8字节
code unsigned char rxdhead[2]={0xaa,0x55};      //举例。通信（串口1、串口2）接收包头匹配字符2字节：（0xAA，0x55）    
// unsigned char rxdhead[1]={0x1};               //举例。串口2接收ModBus协议帧，第一字节ID=1示例  

unsigned char funcmode;                  //举例。定义显示、按键功能模式
enum funcname {RTC_YMD=1,                      //举例。功能模式命名。实时时钟：年月日
               RTC_HMS,                        //                    实时时钟：时分秒
               Rt_Rop,                         //                    热敏光敏测量
               Music,                          //                    音乐播放
               FMradio,                        //                    FM收音机
               UltroSonic,                     //                    超声波测距
               Weight};                        //                    电子秤
unsigned char tempadj;                   //举例。程序变量。调整时钟时用：=1 调年或时；=2 调月或分 =3 调日 或秒

//******* 用户程序段4：用户自定义函数原型 *************//

#include "function.c"                          //举例。用户定义其它函数

void myUart1Rxd_callback()                    //举例。串口1收到合法数据包回调函数。（合法数据包：AA，55，......。共8字节）
{ if ( GetUart2TxStatus() == enumUart2TxFree )                  
	  {	(*(rxd+6)) += 1;                                          //第7字节加1
	     Uart2Print(&rxd, sizeof(rxd));                           //将数据包从串口2(485、或EXT扩展接口上)发送出去
    }			
}

// void myUart2Rxd_callback()                    //举例。串口2收到合法数据包回调函数。（合法数据包：AA，55，......。共8字节）
// { if ( GetUart1TxStatus() == enumUart1TxFree ) 
// 	 { (*(rxd+6)) += 2;                                             //第7字节加2
// 	   Uart1Print(&rxd, sizeof(rxd));                                  //将数据包从串口1发送出去
// 	 }
// }

// void myUart2Rxd_callback()                    //举例。串口2收到ModBus协议包回调函数。（合法数据包：ModBus协议帧，ID匹配）
// { if ( GetUart1TxStatus() == enumUart1TxFree ) 
// 	 { (*(rxd+6)) += 2;                                             //第7字节加2
// 	   Uart1Print(&rxd, sizeof(rxd));                               //将接收缓冲区从串口1发送出去（ModBus数据帧大小未判断，CRC未校验）
// 	 }
// }

void myUart2Rxd_callback()                    //举例。串口2收到合法数据包回调函数。（合法数据包：AA，55，......。共8字节）
{ if ( GetIrStatus() == enumIrFree ) 
	 { (*(rxd+6)) += 2;                                             //第7字节加2
	   IrPrint(&rxd, sizeof(rxd));                                  //将数据包从红外发送出去
	 }
}

void myIrRxd_callback()                      //举例。红外收到数据包回调函数。（有红外前导+数据+结束，NEC_R05d编码）  
{ dealwithIrRxd();	
}

void my1mS_callback()			                  //举例。1mS事件回调函数
{  
}
	
void my10mS_callback()			                //举例。10mS事件回调函数
{ 
}

void my100mS_callback()			                //举例。100mS事件回调函数
{ dealwithDisp();                          
}			 
							 
void my1S_callback()				               //举例。1S事件回调函数
{ 	
}

void myADC_callback()                      //举例。ADC事件回调函数
{ 
}

void myKN_callback()			               	                                                        //举例。导航按键事件回调函数
{ dealwithmyKN();		
}

void mykey_callback()		                            // 按键（Key1、Key2）事件回调函数
{	dealwithmykey();	  
}

void myhall_callback()		                                                                //示例。有hall事件回调函数：发声报警
{	if(GetHallAct() == enumHallGetClose) SetBeep(1350,100);		
}

void mySV_callback()		                                                                  //示例: 振动事件回调函数：控制音乐播放/暂停
{	if(GetVibAct())
	if (GetPlayerMode() == enumModePause) SetPlayerMode(enumModePlay); 
			else  SetPlayerMode(enumModePause);			
}

//******* main()函数 *************//	
void main() {         //主函数 main() 开始         //此行必须！！！ 
	
//******* 用户程序段5：用户main()函数内部局部变量定义 *************//
	
//******* 用户程序段6：用户main()函数（初始化类程序） *************//		
//1,加载需要用的模块(由各模块提供加载函数)
    KeyInit();                                      //举例，需要用到的模块及其函数、方法，必须对其初始化（让其准备、就绪和响应做后台服务）
	  HallInit();                                      //举例
	  VibInit();                                       //举例
	  DisplayerInit();                                 //举例
	  BeepInit();	                                     //举例
    MusicPlayerInit();	                             //举例
	  AdcInit(ADCexpEXT);                              //举例，ADC模块初始化，有参数，选择扩展接口EXT上P1.0、P1.1是否也做ADC功能
    StepMotorInit();	                               //举例，步进电机初始化
	  DS1302Init(t);                                   //举例，DS1302初始化
    	
		IrInit(NEC_R05d);                                //举例，红外接口设置
    /******* 以下可4选1：加载EXT接口 ********/    
//    EXTInit(enumEXTWeight);                          //举例，EXT初始化成电子秤功能
// 	  EXTInit(enumEXTPWM);                             //举例，EXT初始化成两路PWM功能
// 	  EXTInit(enumEXTDecode);                          //举例，EXT初始化成增量式编码器解码功能（如：旋转编码器）
// 	  EXTInit(enumEXTUltraSonic);                      //举例，EXT初始化成超声波测距功能
	   Uart1Init(115200);                                //举例，串口1初始化，有参数，设置Uart1通信波特率
    /******* 以下可2选1：加载串口2 ********/    
// 		 Uart2Init(9600,Uart2Usedfor485ModBus);            //举例，串口2初始化到485接口支持ModBus协议（RS485工业现场总线，半双工，ModBus协议包检测）
     Uart2Init(2400,Uart2Usedfor485);                  //举例，串口2初始化到485接口（RS485工业现场总线，半双工）
// 	  Uart2Init(9600,Uart2UsedforEXT);                 //举例，串口2初始化到EXT接口（TTL Uart串行通信口）
		
//2,设置事件回调函数(由sys提供设置函数SetEventCallBack())	
		SetEventCallBack(enumEventKey, mykey_callback);            //举例
		SetEventCallBack(enumEventSys1mS, my1mS_callback);         //举例
		SetEventCallBack(enumEventSys10mS, my10mS_callback);       //举例
		SetEventCallBack(enumEventSys100mS, my100mS_callback);     //举例
		SetEventCallBack(enumEventSys1S, my1S_callback);           //举例
		SetEventCallBack(enumEventHall, myhall_callback);          //举例
		SetEventCallBack(enumEventVib, mySV_callback);             //举例
		SetEventCallBack(enumEventNav, myKN_callback);             //举例，设置导航按键回调函数
    SetEventCallBack(enumEventUart1Rxd, myUart1Rxd_callback);  //举例，设置串口1接收回调函数
		SetEventCallBack(enumEventUart2Rxd, myUart2Rxd_callback);  //举例，设置串口2接收回调函数
		SetEventCallBack(enumEventXADC,myADC_callback);            //扩展接口上新的AD值事件
		SetEventCallBack(enumEventIrRxd,myIrRxd_callback);         //红外Ir上收到一个数据包

//3,用户程序状态初始化 	
		SetDisplayerArea(0,7);                           //举例
	  SetUart1Rxd(&rxd, sizeof(rxd), rxdhead, sizeof(rxdhead));   //设置串口接收方式：数据包条件：接收数据包放置在rxd中，数据包大小rxd大小，数据包头需要与rxdhead匹配，匹配数量rxdhead大小
	  SetUart2Rxd(&rxd, sizeof(rxd), rxdhead, sizeof(rxdhead)); 
		SetIrRxd(&rxd,sizeof(rxd));                                 //举例
		
//4,用户程序变量初始化
    FM=FM_NVMread();                              //举例，FMRadio初始化。
		FMRadioInit(FM);	
		
    Music_PM=90;
		Music_tone=0xFC;
    funcmode = M24C02_Read(0x00);                               
    LedPrint(funcmode);	
		
/*****************  MySTC_OS 初始化与加载开始  ********************************/   
	  MySTC_Init();	    // MySTC_OS 初始化         //此行必须！！！   
	while(1)            // 系统主循环              //此行必须！！！   	
		{ MySTC_OS();     // MySTC_OS 加载           //此行必须！！！
/*****************  MySTC_OS 初始化与加载结束  ********************************/  
			
//******* 用户程序段7：用户main()函数（主循环程序） *************//
			
			
		}	              //主循环while(1)结束         //此行必须！！！ 
}                   //主函数 main() 结束         //此行必须！！！ 

