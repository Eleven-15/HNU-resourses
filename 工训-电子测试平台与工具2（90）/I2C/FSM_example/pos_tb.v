`timescale 1ns/100ps
module xpos_tb();

parameter s0=4'h0,s1=4'h1,s2=4'h2,s3=4'h3,s4=4'h4,s5=4'h5,s6=4'h6,s7=4'h7,s8=4'h8,s9=4'h9,s10=4'ha,s11=4'hb,s12=4'hc,s13=4'hd,s14=4'he,s15=4'hf;

reg [3:0] state,next_state;
reg a,b,c,d,e,f,g;
wire [1:0] pos;
pos xpos(clk,a,b,c,d,e,f,g,pos);
initial clk=0;
always #50 clk=~clk;
initial begin
    a=0;b=0;c=0;d=0;e=0;f=0;g=0;
    #1
    #400
    a=1;
    b=1;
    c=1;
    d=0;
    e=0;
    f=1;
    g=0;
    #
    repeat(1024) @(posedge clk);
    $stop;
end
endmodule
