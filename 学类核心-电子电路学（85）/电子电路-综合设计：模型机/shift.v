module shift(fbus,flbus,frbus,a,w,cf);
	input fbus,flbus,frbus;
    input [7:0] a;
	output [7:0] w;
    output cf;
    reg [7:0] w;
    reg cf;
	always@(*)
	begin
        if (fbus==1 && flbus==0 && frbus==0)
        begin
            w=a;
            cf=0;
        end
        else if (fbus==0 && flbus==1 && frbus==0)
        begin
            w={a[6:0],a[7]};
            cf=a[7];
        end
        else if (fbus==0 && flbus==0 && frbus==1)
        begin
            w={a[0],a[7:1]};
            cf=a[0];
        end
        else 
        begin
			w=8'hZZ;
			cf=0;
		end
    end
	
    
endmodule