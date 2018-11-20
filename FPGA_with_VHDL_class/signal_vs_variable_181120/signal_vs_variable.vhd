library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
---------------------------------
entity signal_vs_variable is 
	port(	clk:in std_logic;
			B:out integer range 0 to 15);
end entity;
--此文件用來練習、比較signal 和 variable的差異性
architecture main of signal_vs_variable is
	signal A:integer range 0 to 15 := 0;
begin
	process(clk)
	--variable A:integer range 0 to 15:=0;
	begin
		if rising_edge(clk) then
			A <= A + 1;
			B <= A;
			if A=5 then 
				A <= 0;
			end if;
		end if;
	end process;

end architecture;