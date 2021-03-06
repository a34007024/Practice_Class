library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity BCDtoSEG_decoder is
port(
	bcdIn:in std_logic_vector(3 downto 0);
	segOut:out std_logic_vector(7 downto 0)
	);
end entity;

architecture main of BCDtoSEG_decoder is
begin
	with bcdIn select
		segOut <= 	"00000011" when "0000",
					"10011111" when "0001",
					"00100101" when "0010",
					"00001101" when "0011",
					"10011001" when "0100",
					"01001001" when "0101",
					"01000001" when "0110",
					"00011111" when "0111",
					"00000001" when "1000",
					"00011001" when "1001",
					"11111111" when others;
end architecture;