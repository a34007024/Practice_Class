library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity adder_and_sub is
	port(
	A,B:in std_logic_vector(7 downto 0);
	Ci,ADDSUB:in std_logic;
	Co:out std_logic;
	result:out std_logic_vector(7 downto 0)
	);
end entity;
--=============================
architecture main of adder_and_sub is
begin
	process(Ci,A,B,ADDSUB) --偵測()內的訊號是否產生改變，若有，就執行process裡面的程式碼
	variable cache:std_logic_vector(8 downto 0);
	-- :=、<= (assign a value和C語言裡的=一樣是給值的意思)
	begin
		--=====detect to add numbers or sub numbers
		if ADDSUB = '1' then
			cache := '0' & (A + B + Ci);
		elsif ADDSUB = '0' then
			cache := '0' & (A - B - Ci);
		end if;
		--=====detect to add numbers or sub numbers
		--output the result=========
		result <= cache(7 downto 0);
		Co <= cache(8);
		--output the result=========
	end process;
end architecture;