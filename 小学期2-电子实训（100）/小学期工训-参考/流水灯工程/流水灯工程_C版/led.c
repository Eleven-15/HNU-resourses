#include <STC15F2K60S2.H>
#define uchar unsigned char
#define uint unsigned int
sbit led_sel = P2 ^ 3; // P2^3----E3
uchar led;

void Init()
{

	P0M1 = 0x00;
	P0M0 = 0xff;

	P2M1 = 0x00;
	P2M0 = 0x08;

	led_sel = 1;
}

// 延时函数可以在STC-ISP中通过“软件延时计算器”功能自动生成指定演示时间的延时函数代码
// 下为生成1ms的延时函数，通过传入参数n，函数可以延时n毫秒
void delay_ms(uint n)
{
	while (n)
	{
		uchar i, j;
		i = 11;
		j = 190;
		do
		{
			while (--j)
				;
		} while (--i);
		n--;
	}
}

void Delay200ms() //@11.0592MHz
{
	unsigned char i, j, k;

	//_nop_();
	//_nop_();
	i = 9;
	j = 104;
	k = 139;
	do
	{
		do
		{
			while (--k)
				;
		} while (--j);
	} while (--i);
}

void main()
{
	Init();
	led = 0x01;
	while (1)
	{
		P0 = led;
		// delay_ms(200);
		Delay200ms(); // 延时200ms
		if (led == 0x80)
			led = 0x01;
		else
			led = led << 1;
	}
}
