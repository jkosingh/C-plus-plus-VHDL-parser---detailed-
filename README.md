# C++-VHDL-parser---detailed-

implementation of a basic parser for VHDL that can split a file into a set of
tokens and then perform some simple processing on those tokens.

A token is defined as the smallest number of consecutive characters that can be separated by whitespace without changing the functionality of the code.

delimiters were used to make boundaries between tokens.

program will start by categorizing tokens into several broad categories along with storing the type for identifiers
and literals. Then it will find all conditional expressions within the code and then check for certain
kinds of errors in the input files.

Parser functionality includes:

- Function that returns true if token is a keyword of VHDL language
- Function that returns true if token is a operator of VHDL language
- Function that returns true if token is a identifier of VHDL language
- Function that returns true if token is a literal of VHDL language
- Function that returns true if token is a comment of VHDL language
- Function that returns true if token is a other type of VHDL language
- Function that will append tokens into the list
- delete tokens from the list
- remove comments all together from the token list 
- remove tokens of any type from the token list
- count the number of tokens in the VHDL file
- error checking between type matching in the VHDL syntax and prints out what line and what mistake has been made in verbose mode
- error checking between missing syntax in VHDL statements and prints out what line and what mistake has been made in verbose mode
- counts the number of correct statments in the file
- finds all the conditional expressions in the file


-program will prompt user with a verbose or non-verbose mode.

In non-verbose mode:
- the number of tokens
- The number of conditional expressions
- The number of missing “end if”s
- The number of missing “then”s
- The number of type mismatches
- The number of width mismatches

In verbose mode:
- All of the non-verbose counts.
- For all error cases print out the line(s) on which the error occurs along with its type
- Any additional details you wish to include

Plus some bonus features
