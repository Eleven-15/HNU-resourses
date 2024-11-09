#include"IRC.c"
#include"interupt.c"
/*********配置函数***********/
void configinIt()
{
 	P2M0=0xff;
  P2M1=0x00;
  P0M0=0xff;
  P0M1=0x00;
	P3M0|=0xA0;
	P3M1|=0x80;
	IR_OUT=0;
	P2=0x00;
	P0=0x00;
	IE|=0x80;
}
void main(void){
	uint8 openORClose=0;
	uint8 temperature=16;
	uint8 adcResult=0;
	configinIt();
	Timer0Init();
	Timer1Init();
	keyInit();
	while(1)
	{
		digitalTubeData[0]=openORClose;
	  digitalTubeData[6]=temperature/10;
		digitalTubeData[7]=temperature%10;
		digScan();
		keyScan();
		if(keygroup.state[0]==1)
		{
			while(P32==0);
			keygroup.state[0]=0;
			openORClose=1-openORClose;
		}
		if(keygroup.state[1]==1)
		{
			while(P33==0);
			keygroup.state[1]=0;
			SendInstructions(openORClose,temperature);
		}
		if(keygroup.state[7]==1)
		{
			if(ADC_CONTR&0x10)
				{						//数模转换完成，则重新进行转换
					ADC_CONTR&=~0x10;
					ADC_CONTR|=0x08;
					adcResult=ADC_RES>>5;
				}
			while(adcResult!=0x07)
			{
				if(ADC_CONTR&0x10)
				{						//数模转换完成，则重新进行转换
					ADC_CONTR&=~0x10;
					ADC_CONTR|=0x08;
					adcResult=ADC_RES>>5;
				}
			}
			keygroup.state[7]=0;
			temperature++;
			if(temperature>30)
				temperature=30;
		}
		if(keygroup.state[4]==1)
		{
			if(ADC_CONTR&0x10)
				{						//数模转换完成，则重新进行转换
					ADC_CONTR&=~0x10;
					ADC_CONTR|=0x08;
					adcResult=ADC_RES>>5;
				}
			while(adcResult!=0x07)
			{
				if(ADC_CONTR&0x10)
				{						//数模转换完成，则重新进行转换
					ADC_CONTR&=~0x10;
					ADC_CONTR|=0x08;
					adcResult=ADC_RES>>5;
				}
			}
			keygroup.state[4]=0;
			temperature--;
			if(temperature<16)
				temperature=16;
		}
	}
}