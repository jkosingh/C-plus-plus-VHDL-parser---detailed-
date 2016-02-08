signal a : std_logic := '0';
signal b : std_logic;

signal c : std_logic_vector(0 to 3);
signal d : std_logic_vector(7 downto 0) := "01010100";
signal e : std_logic_vector(7 downto 0);

signal f : integer := "5";
signal g : integer;

signal h : boolean;
signal i : boolean := false;

begin

--396 tokens (with new lines), 314 without, 9 correct conditional expressions, 14 correct/incorrect conditional expresions
--5 missing thens, 2 missing end ifs, no type or width mismatches 
--nothing missing
process (a, b, h)
begin
  if (a = '0') then
    a <= b;
  elsif (h = true) then
    a <= '0';
  elsif (a = b) then
    a <= '1';
  end if;
end process;

--missing then
process (e, d)
begin
  if (e = d) 
    a <= b;
  end if;
end process;

--missing then on first elsif
--also missing end if
process (a, b, h)
begin
  if (b = '0') then
    a <= b;
  elsif (h = false)
    a <= '0';
  elsif (a /= b) then
    a <= '1';
end process;

--two missing "thens" one for each elsif
process (a, i, d)
begin
  if (a = '1') then
    a <= b;
  elsif (i = true) 
    a <= '0';
  elsif (d = e) 
    a <= '1';
  end if;
end process;

--single nested if, missing then for first if
--missing inner end if
process (b, g, i)
begin
  if(g = 5)
    if (b = '1') then
      a <= b;
    elsif (i /= true) then
      a <= '0';
    elsif (g >= 900) then
      a <= '1';
    else
      a <= '0';
  else
    a <= b;
  end if;
end process;


end;
