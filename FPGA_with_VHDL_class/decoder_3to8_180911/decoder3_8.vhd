library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity decoder3_8 is
port(
	A:in std_logic_vector(2 downto 0);
	Y:out std_logic_vector(7 downto 0);
	enable:in std_logic
	);
end entity;
--========================================
architecture main of decoder3_8 is
signal sub:std_logic_vector(3 downto 0);
begin
	sub <= enable & A;
	with sub select
	Y <= "00000001" when "0000",
		 "00000010" when "0001",
		 "00000100" when "0010",
		 "00001000" when "0011",
		 "00010000" when "0100",
		 "00100000" when "0101",
		 "01000000" when "0110",
		 "10000000" when "0111",
		 "00000000" when others;
end architecture;







