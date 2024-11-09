module simple(a,b,s,m,t,cf,zf);
	input [7:0] a;
	input [7:0] b;
	input m;
	input [3:0] s;						
	output cf,zf;
	output [7:0] t;
	reg cf,zf;
	reg [7:0] t;						
	always@(m,s,a,b)
	begin
		t=8'b00000000;							
		cf=1'b0;
		zf=1'b0;
		if(m==1)
		begin
			if(s==4'b1001) 
				begin
					{cf,t}=a+b;
					if(t==0) zf=1'b1;
					else zf=1'b0;
				end
			else if(s==4'b0110) 
				begin
					{cf,t}=b-a;
					if(t==0) zf=1'b1;
					else zf=1'b0;
				end
			else if(s==4'b1011) t=a&b;
			else if(s==4'b0101) t=~b;
			else ;
		end
		else
		begin
			if(s==4'b1010) t=b;
			else if (s==4'b1100 || s==4'b0100) t=a;
			else ;
		end
	end
endmodule