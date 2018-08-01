library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
------------------------------------------------
entity divide_frequency_180622 is 
	port(
	GCKP18,RSTP61:in std_logic;
	--GCKP18為板子上石英晶體的接腳編號
	--RSTP61為板子上暫停石英晶體的按鈕接腳
	f1,f2:out std_logic);
end divide_frequency_180622;
-------------------------------------------------
architecture QwQ of divide_frequency_180622 is
signal FrequencyDivider:std_logic_vector(25 downto 0);
--除頻器FrequencyDivider課本簡稱FD，後面的25 downto 0是代表該除頻器有26之輸出Pin腳
--每隻輸出Pin腳的輸出頻率都不一樣;
constant Fs1:integer range 0 to 32:=6;--在第六支接腳擷取頻率
constant Fs2:integer range 0 to 32:=22;--在第22支接腳擷取頻率
begin 
	f1 <= FrequencyDivider(Fs1);--把第Fs1隻腳的輸出頻率丟給f1輸出腳
	f2 <= FrequencyDivider(Fs2);--把第Fs2隻腳的輸出頻率丟給f2輸出腳
	process(GCKP18,RSTP61)
	begin 
		if RSTP61 = '0' then 
		--這句if的意思是
		--當暫停按鈕被按下
			FrequencyDivider <= (FrequencyDivider'range => '0');
			--就停止除頻器，讓除頻器暫停
		elsif rising_edge(GCKP18) then
		--rising_edge(石英晶體接腳)
		--上述的rising_edge() 是個特殊函式
		--會把石英晶體的震盪頻率除2丟給定義好的FD接腳
			FrequencyDivider <= FrequencyDivider+1;
			--總共定義幾隻輸出接腳，就依序把頻率除2的n次方，輸出給除頻器接腳
		end if;
	end process;
end QwQ;
	
	
	

	
	
	
	
	
	