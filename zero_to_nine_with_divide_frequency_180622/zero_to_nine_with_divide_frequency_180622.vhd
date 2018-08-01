library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
-------------------------------------------------
entity zero_to_nine_with_divide_frequency_180622 is 
	port(GCKP18,RSTP61:in std_logic;
		SEG,D:out std_logic_vector(7 downto 0));
end zero_to_nine_with_divide_frequency_180622;
-------------------------------------------------
architecture Main of zero_to_nine_with_divide_frequency_180622 is
constant N7:integer range 0 to 9:=2;
constant N6:integer range 0 to 9:=0;
constant N5:integer range 0 to 9:=1;
constant N4:integer range 0 to 9:=8;
constant N3:integer range 0 to 9:=0;
constant N2:integer range 0 to 9:=6;
constant N1:integer range 0 to 9:=2;
constant N0:integer range 0 to 9:=2;
signal bcd:integer range 0 to 9;
signal SCAN:integer range 0 to 9:=0;
signal SCAN_f:std_logic;
signal FD:std_logic_vector(25 downto 0);
begin
--除頻器-----------------------------------------------------
	SCAN_f <= FD(23);--選擇除頻器接腳使用，數字越大頻率越低
	process(GCKP18,RSTP61)
	begin 
		if RSTP61='0' then
			FD <=(FD'range => '0');
		elsif rising_edge(GCKP18) then
			FD <= FD+1;
		end if;
	end process;
--依據除頻器改變SCAN值的電路(類似Timer)--------------------------------------
	process(SCAN_f)
	begin
		if rising_edge(SCAN_f)	then
			SCAN <= SCAN+1;
		end if;
	end process;
--轉跳數字的部分可以使用wait語法(類似delay)
--BCD丟數字電路-----------------------------------------------------------
bcd <= 	0 when SCAN = 0 else
		1 when SCAN = 1 else
		2 when SCAN = 2 else
		3 when SCAN = 3 else
		4 when SCAN = 4 else
		5 when SCAN = 5 else
		6 when SCAN = 6 else
		7 when SCAN = 7 else
		8 when SCAN = 8 else
		9 when SCAN = 9 else
		0;
	
--BCD對七段顯示器--------------------------------------------
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
-------------------------------------------------------------
D <= "11111110"; --固定讓第0顆七段顯示器亮
-------------------------------------------------------------



		















end Main;