$include(STC15F2K60S2.H)  

ORG   0000H  //伪指令
        LJMP   START  //地址符号

;---------------------------------------主程序----------------------------
ORG   0100H     
//初始化，设置推挽输出
START:  MOV    P0M1, #00000000B            ;00——准双向口   01——推挽   10——高阻输入	 11——OC
        MOV    P0M0, #11111111B 
        MOV    P2M1, #00000000B
	    MOV    P2M0, #00001000B
		MOV    P2,   #00001000B
		
MAINLOOP:
//循环点亮led灯
        MOV    P0,   #00000001B
		CALL   DELAY   //调用delay函数
        MOV    P0,   #00000010B
		CALL   DELAY
		MOV    P0,   #00000100B
		CALL   DELAY
		MOV    P0,   #00001000B
		CALL   DELAY
		MOV    P0,   #00010000B
		CALL   DELAY
		MOV    P0,   #00100000B
		CALL   DELAY
		MOV    P0,   #01000000B
		CALL   DELAY
		MOV    P0,   #10000000B
		CALL   DELAY
        JMP    MAINLOOP  

DELAY:  MOV    R0,   #0fFH
L1:     MOV    R1,   #04FH
L2:		MOV    R2,   #20H
L3:     NOP
        DJNZ   R2,   L3
		DJNZ   R1,   L2
		DJNZ   R0,   L1
		RET        

        END           //程序结束

