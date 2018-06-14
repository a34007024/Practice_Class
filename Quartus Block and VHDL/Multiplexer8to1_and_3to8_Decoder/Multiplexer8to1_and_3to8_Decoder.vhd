library IEEE;
use IEEE.std_logic_1164.all;
-------------------------------------------------
entity Multiplexer8to1_and_3to8_Decoder is
	
	port(	selectSeg:in std_logic_vector(3 downto 1);
			--use to input which 7seg should blink
			inputData:in std_logic_vector(4 downto 1);
			--use switches to input data
			seg:out std_logic_vector(6 downto 0);
			-- 6~0 => a~g
			segCom:out std_logic_vector(144 downto 137)
			);
	
end Multiplexer8to1_and_3to8_Decoder;
-------------------------------------------------
architecture main of Multiplexer8to1_and_3to8_Decoder is
begin

with inputData select
seg <=	"0000001" when not("0000"), --0
		"1001111" when not("0001"), --1
		"0010010" when not("0010"), --2
		"0000110" when not("0011"), --3
		"1001100" when not("0100"), --4
		"0100100" when not("0101"), --5
		"0100000" when not("0110"), --6
		"0001111" when not("0111"), --7
		"0000000" when not("1000"), --8
		"0000100" when not("1001"), --9
		"1111111" when others;

with selectSeg select
segCom <=	"11111110" when not("000"),
			"11111101" when not("001"),
			"11111011" when not("010"),
			"11110111" when not("011"),
			"11101111" when not("100"),
			"11011111" when not("101"),
			"10111111" when not("110"),
			"01111111" when not("111");

end main;