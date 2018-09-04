library IEEE;
use IEEE.std_logic_1164.all;
--use IEEE.std_logic_unsigned.all;
--not needed in this project-----------------
entity encoder_8to3 is 
	port(	A:in std_logic_vector(7 downto 0);
			EN:in std_logic;
			Y:out std_logic_vector(2 downto 0)
		);
	--port();	syntax
	--port(DeclarePin;DeclarePin;DeclarePin);
end entity;
-----------------------------------------
architecture main of encoder_8to3 is
begin
Y <=	"111" when(not EN and A(7)) = '1' else
		"110" when(not EN and A(6)) = '1' else
		"101" when(not EN and A(5)) = '1' else
		"100" when(not EN and A(4)) = '1' else
		"011" when(not EN and A(3)) = '1' else
		"010" when(not EN and A(2)) = '1' else
		"001" when(not EN and A(1)) = '1' else	"000";
end architecture;