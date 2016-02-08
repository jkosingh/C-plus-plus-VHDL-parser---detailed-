--gfgfhfh
Library ieee;
Use ieee.std_logic_1164.all;
			ghdu;
\t
Entity Fcount is
port (D : in std_logic_vector(3 downto 0);
clock : in std_logic;
Y : out std_logic_vector (5 downto 0));

END Fcount;

	Architecture behavior of Fcount is 
signal ff1 : std_logic;
				signal ff2 : std_logic; 
 TYPE my_type IS reset;
signal ff3,ff4,ff5,ff6 : std_logic;--coments
signal C,Z,W,H : std_logic_vector(4 downto 0);
constant BUS_WIDTH : integer := 8;
constant FOUR_ONES : std_logic_vector(3 downto 0):= "1111";
SIGNAL state : my_state;
SIGNAL two_bit : BIT_VECTOR (0 TO 1);
Legal
    state <= reset;
Illegal
    state <= "00";
    state <= two_bit;

constant PERIOD : time := 10 ns;
constant MAX_SIM_TIME : time:= 50 * PERIOD;
Begin

C(0) <= D(0) and ff1;
C(1) <= D(1) and ff2;
C(2) <= D(2) and ff3;
C(3) <= D(3) and ff4;
C(4) <= C(3) and ff5;
ff1 <= D(0) xor ff1 when clock = '1' else ff1;
ff2 <= (D(1) xor ff2) xor C(0) when clock = '1' else ff2;
ff3 <= (D(2) xor ff3) xor C(1) when clock = '1' else ff3;
