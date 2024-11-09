module sm(clk,sm_en,sm);
input clk,sm_en;
output reg sm;

initial sm=1'b0;

always@(negedge clk)
begin
    if (sm_en) sm<=!sm;
    else sm<=sm;
end
endmodule