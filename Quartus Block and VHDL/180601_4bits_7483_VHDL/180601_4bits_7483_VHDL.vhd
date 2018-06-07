--關於Usb-blaster驅動安裝
--https://blog.csdn.net/chengbozhe/article/details/47335391
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
------------------------------------
entity 180601_4bits_7483_VHDL is
	port(A,B:in std_logic_vector(3 downto 0);
		Ci,AS:in std_logic;
		D:out std_logic_vector(3 downto 0);
		Co:out std_logic;
	)
end 180601_4bits_7483_VHDL;