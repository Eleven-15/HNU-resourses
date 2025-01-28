//输入端口为控制信号和时钟信号，输出端口为pos，表示位置
module fsm_example(
    input clk;
    input a,b,c,d,e,f,g,
    output reg [1:0] pos
)

//使用4位16进制数表示所有状态
parameter s0=4'h0,s1=4'h1,s2=4'h2,s3=4'h3,s4=4'h4,s5=4'h5,s6=4'h6,s7=4'h7,s8=4'h8,s9=4'h9,s10=4'ha,s11=4'hb,s12=4'hc,s13=4'hd,s14=4'he,s15=4'hf;
reg [3:0] state,next_state;

//下一状态判断
always @(*) begin
    case (state)
        s0: next_state=s1;
        s1: if(a) next_state=s2;
            else next_state=s3;
        s2: if(b) next_state=s4;
            else next_state=s5;
        s3: if(b) next_state=s4;
            else next_state=s5;
        s4: next_state=s6;
        s5: next_state=s6;
        s6: if(c) next_state=s8;
            else next_state=s7;
        s7: if(d) next_state=s9;
            else next_state=s10;
        s8: if(d) next_state=s9;
            else next_state=s10;
        s9: if(e) next_state=s11;
            else begin
                if(f) next_state=s12;
                else next_state=s13;
            end
        s10: if(e) next_state=s11;
            else begin
                if(f) next_state=s12;
                else next_state=s13;
            end
        s11: next_state=s14;
        s12: next_state=s14;
        s13: next_state=s14;
        s14: if(g) next_state=15;
             else next_state=s0;
        s15: next_state=s0;
        default: next_state=s0;
    endcase
end

//状态更新与输出
always @(posedge clk) state<=next_state;

always @(*) begin
    case (state)
        s0: pos=2'b00;
        s1: pos=2'b00;
        s2: pos=2'b01;
        s3: pos=2'b01;
        s4: pos=2'b01;
        s5: pos=2'b01;
        s6: pos=2'b00;
        s7: pos=2'b00;
        s8: pos=2'b01;
        s9: pos=2'b01;
        s10: pos=2'b11;
        s11: pos=2'b01;
        s12: pos=2'b10;
        s13: pos=2'b01;
        s14: pos=2'b00;
        s15: pos=2'b01;
        default: pos=2'b00;
    endcase
end

endmodule
