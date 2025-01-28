#include <stdio.h>
#include "com.h"
#include "com.c"
 
int main(void)
{
	unsigned char tmp[15] = {0}; //用于存放读取出来的数据的缓冲区
	int rl; //读取数据的长度（单位：字节）
	int i;
 
	fd = openSerial("/dev/ttyUSB0"); //打开串口，ttyUSB0是串口文件
	
	if(fd < 0)
	{
		printf("open com fail!\n");
		return 0;
	}
	
	EpollInit(fd); //初始化终端事件触发函数epoll,设置要监听的事件及相关参数等
	
	while(1)
	{
		bzero(tmp,sizeof(tmp)); //把tmp对应的内存块的前sizeof(tmp)个字节置零
		
		rl = ComRead(tmp,13);//读取13个字节放到缓存
         
		//打印读到的数据
		printf("read_len = %d\n", rl);
		tmp[rl] = '\0';
		for(i = 0; i < rl; i++)
			printf(" %02x", tmp[i]);
		printf("\n\n");
	
	
	}
	
	close(epid);
	close(fd);
	
	return 0;
}
