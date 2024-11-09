module con_signal(mova,movb,movc,add,sub,and1,not1,rsr,rsl,jmp,jz,z,jc,c,in1,out1,nop,halt,ir,sm,reg_ra,reg_wa,
 	madd,alu_s,pc_ld,pc_inc,reg_we,ram_xl,ram_dl,alu_m,shi_fbus,shi_frbus,shi_flbus,ir_ld,cf_en,zf_en,sm_en,in_en,out_en);
 	input [7:0]ir;
 	input mova,movb,movc,add,sub,and1,not1,rsr,rsl,jmp,jz,z,jc,c,in1,out1,nop,halt,sm;
 	output reg [1:0] reg_ra;
 	output reg [1:0]reg_wa;
 	output reg [1:0]madd;
 	output reg [3:0]alu_s;
 	output reg pc_ld,pc_inc,reg_we,ram_xl,ram_dl,alu_m,shi_fbus,shi_frbus,shi_flbus,ir_ld,cf_en,zf_en,sm_en,in_en,out_en;
 	always@(*)
	begin
		sm_en<=!halt;
		//寄存器组
		reg_we<=!(mova||movc||add||sub||and1||not1||rsl||rsr||in1)||!sm;
		reg_wa<=ir[3:2];
		reg_ra<=ir[1:0];
		//ALU
		alu_m<=add||sub||and1||not1;
		cf_en<=add||sub||rsr||rsl;
		zf_en<=add||sub;
		alu_s<=ir[7:4];
		//移位逻辑
		shi_fbus<=mova||movb||add||sub||and1||not1||out1;
		shi_frbus<=rsr;
		shi_flbus<=rsl;
		
		//计数器PC
		pc_ld<=jmp||(jz&&z)||(jc&&c);
		pc_inc<=(jz&&!z)||(jc&&!c)||!sm;
		//选择器MADD
		if(movb&&sm) 
			madd<=2'b10;
		else if(movc&&sm) 
			madd<=2'b01;	
		else 
			madd<=2'b00;
		//RAM
		ram_dl<=movc||jmp||(jz&&z)||(jc&&c)||!sm;
		ram_xl<=movb;
		
		//指令寄存器
		ir_ld<=!sm;
		//输入输出设备
		in_en<=in1;
		out_en<=out1;
 	end
endmodule