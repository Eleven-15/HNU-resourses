$include(STC15F2K60S2.H)  

KEY1   BIT   P3.2
KEY2   BIT   P3.3
KEY3   BIT   P1.7

LED1   BIT   P0.0
LED2   BIT   P0.1
LED3   BIT   P0.2

ORG   0000H
        LJMP   START

;---------------------------------------主程序----------------------------
ORG   0030H            	 
START:  MOV    P0M1, #00000000B        ;设P0、P2工作方式  
        MOV    P0M0, #11111111B 	        ;00——准双向口   01——推挽   10——高阻输入	 11——OC
        MOV    P2M1, #00000000B
	    MOV    P2M0, #00001000B
		MOV    P2,   #00001000B		   ;选择LED灯工作
		MOV    P0,   #00000000B		   ;关闭所以LED灯
MAINLOOP:
		JB     KEY1,  L1		  ;查看KEY1
		SETB   LED1
		JMP    L2
L1:     CLR    LED1

L2:		JB     KEY2,  L3		  ;查看KEY2
		SETB   LED2
		JMP    L4
L3:     CLR    LED2

L4:	   	JB     KEY3,  L5		  ;查看KEY3
		SETB   LED3
		JMP    L6
L5:     CLR    LED3

L6:	    JMP    MAINLOOP 

        END           

