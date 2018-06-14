library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
---------------------------------------------
entity Divider_with_switch_7seg_180608 is
	port(	GCKP18,RSTP61:in std_logic;
			SEG,D:out std_logic_vector(7 downto 0)
			);
end Divider_with_switch_7seg_180608;
---------------------------------------------
architecture main of Divider_with_switch_7seg_180608 is
-----------------------------------------------------
------define the variable----------------------------
constant N7:integer range 0 to 9:=2;
constant N6:integer range 0 to 9:=0;
constant N5:integer range 0 to 9:=1;
constant N4:integer range 0 to 9:=8;
constant N3:integer range 0 to 9:=0;
constant N2:integer range 0 to 9:=6;
constant N1:integer range 0 to 9:=0;
constant N0:integer range 0 to 9:=8;
signal bcd:integer range 0 to 9;
signal SCAN:integer range 0 to 7:=0;
signal SCAN_f:std_logic;
signal FD:std_logic_vector(30 downto 0);
------define the variable----------------------------
-----------------------------------------------------
begin
--除頻器
	SCAN_f <= FD(25);
	process(GCKP18,RSTP61)
	begin
		if RSTP61 = '0' then
			FD <= (FD'range => '0');
		elsif rising_edge(GCKP18) then
			FD <= FD+1;
		end if;
	end process;
----------------------------------------------
--掃描電路
	process(SCAN_f)
	begin
		if rising_edge(SCAN_f) then
			SCAN <= SCAN+1;
		end if;
	end process;	
----------------------------------------------
--8對1多工器
	bcd <=	N0 when SCAN = 0 else
			N1 when SCAN = 1 else
			N2 when SCAN = 2 else
			N3 when SCAN = 3 else
			N4 when SCAN = 4 else
			N5 when SCAN = 5 else
			N6 when SCAN = 6 else
			N7;
----------------------------------------------
--BCD對七段顯示器之解碼器
with bcd select
SEG <=	"00000011" when 0, --0
		"10011111" when 1, --1
		"00100101" when 2, --2
		"00001101" when 3, --3
		"10011001" when 4, --4
		"01001001" when 5, --5
		"01000001" when 6, --6
		"00011111" when 7, --7
		"00000001" when 8, --8
		"00001001" when 9, --9
		"11111111" when others;
------------------------------------------------------
--3對8解碼器
with SCAN select
D <=	"11111110" when 0, --D0
		"11111101" when 1, --D1
		"11111011" when 2, --D2
		"11110111" when 3, --D3
		"11101111" when 4, --D4
		"11011111" when 5, --D5
		"10111111" when 6, --D6
		"01111111" when 7, --D7
		"11111111" when others;
-------------------------------------------------
		
end main;















