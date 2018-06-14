library IEEE;
use IEEE.std_logic_1164.all;
-----------------------------------------
entity Quiz_phone_number_VHDL_180608 is
	port(	inputS:in std_logic_vector(2 downto 0);
			--S1:in std_logic; S2:in std_logic; S3:in std_logic;
			--不能with S1,S2,S3 select QwQ
			segOut:out std_logic_vector(6 downto 0);
			Com:out std_logic);
		
end Quiz_phone_number_VHDL_180608;
-----------------------------------------
architecture show_phone_number_func of Quiz_phone_number_VHDL_180608 is
begin
with inputS select
segOut <= not("1101101") when not("000"),
		  not("1111111") when not("001"),
		  not("1111110") when not("010"),
		  not("0110011") when not("011"),
		  not("0011111") when not("100"),
		  not("1111001") when not("101"),
		  not("0011111") when not("110"),
		  not("1111111") when not("111");
Com <= '0';

end show_phone_number_func;		  
		  