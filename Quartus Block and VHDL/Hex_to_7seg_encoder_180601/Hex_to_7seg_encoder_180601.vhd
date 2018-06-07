library IEEE;
use IEEE.std_logic_1164.all;
-------------------------------------------
entity Hex_to_7seg_encoder_180601 is
	port(input:in std_logic_vector(3 downto 0);
		segOutput:out std_logic_vector(7 downto 0);
		COM:out std_logic	);
end Hex_to_7seg_encoder_180601;
-------------------------------------------
architecture Encoder of Hex_to_7seg_encoder_180601 is
begin
with input select
segOutput<= "00000011" when "0000" ,
			"10011111" when "0001" ,
			"00100101" when "0010" ,
			"00001101" when "0011" ,
			"10011001" when "0100" ,
			"01001001" when "0101" ,
			"01000001" when "0110" ,
			"00011011" when "0111" ,
			"00000001" when "1000" ,
			"00001001" when "1001" ,
			"00010000" when "1010" ,
			"00000000" when "1011" ,
			"01100010" when "1100" ,
			"00000010" when "1101" ,
			"01100000" when "1110" ,
			"01110000" when "1111" ,
			"11111111" when others;
COM <= '0';
end Encoder;
	













