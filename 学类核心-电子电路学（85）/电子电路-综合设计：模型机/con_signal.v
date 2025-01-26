module con_signal(mova,movb,movc,add,sub,and1,not1,rsr,rsl,jmp,jz,z,jc,c,in1,out1,nop,halt,ir,sm,reg_ra,reg_wa,madd,pc_ld,pc_inc,reg_we,ram_xl,ram_dl,alu_m,shi_fbus,shi_flbus,shi_frbus,ir_ld,cf_en,zf_en,sm_en,in_en,out_en,reg_ra,reg_wa,madd,alu_s);
	input mova,movb,movc,add,sub,and1,not1,rsr,rsl,jmp,jz,z,jc,c,in1,out1,nop,halt,sm;
    input [7:0] ir;
	output [1:0] reg_ra,reg_wa,madd;
    output [3:0] alu_s;
    output pc_ld,pc_inc,reg_we,ram_xl,ram_dl,alu_m,shi_fbus,shi_flbus,shi_frbus,ir_ld,cf_en,zf_en,sm_en,in_en,out_en;
    reg pc_ld,pc_inc,reg_we,ram_xl,ram_dl,alu_m,shi_fbus,shi_flbus,shi_frbus,ir_ld,cf_en,zf_en,sm_en,in_en,out_en;
	reg [1:0] reg_ra,reg_wa,madd;
    reg [3:0] alu_s;
	always@(*)
    begin
        //sm翻转控制
		sm_en=!halt;

		//ALU
		alu_m=add || sub || and1 || not1 || rsl || rsr || out1;
        alu_s[3:0]=ir[7:4];
		cf_en=add || sub || rsr || rsl;
		zf_en=add || sub;

		//移位逻辑
		shi_fbus=mova || movb || add || sub || and1 || not1 || out1;
		shi_frbus=rsr;
		shi_flbus=rsl;

		//RAM
        ram_xl=movb;
		ram_dl=movc || jmp || ( z && jz ) || ( c && jc ) || !sm;

		//指令寄存器
		ir_ld=!sm;

		//寄存器组
        reg_ra=ir[1:0];
        reg_wa=ir[3:2];
		reg_we=movb || jmp || ( z && jz ) || ( c && jc ) || out1 || !sm;

		//计数器PC
		pc_ld=jmp || ( z && jz ) || ( c && jc );
		pc_inc=( !z && jz ) || ( !c && jc ) || !sm;

		//选择器MADD
		if( movb && sm ) madd=2'b10;
		else if( movc && sm ) madd=2'b01;	
		else if( !sm ) madd=2'b00;
		else madd=2'b00;

		//输入输出设备
		in_en=in1;
		out_en=out1;

 	end
endmodule