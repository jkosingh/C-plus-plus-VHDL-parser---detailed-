#ifndef PARSERCLASSES_H_
#define PARSERCLASSES_H_

//Use only the string library DO NOT add any other libraries
#include <string>
#include<vector>

using namespace std;

enum tokenType {T_Operator, T_Identifier, T_Literal, T_CommentBody, T_Other};

struct tokenDetails {
  string type; //boolean, std_logic, std_logic_vector, integer etc.
  int width; //bit width for vector types
};

//Declare your variables for storing delimiters here:

//Token class for a doubly-linked list of string tokens
class Token {
private:
	Token *next; //Next pointer for doubly linked list
	Token *prev; //Previous pointer for doubly linked list
	string stringRep; //Token value
	string OPerator = "operator";
    int OpSize = 29;
    void TokenParse();
    bool _isKeyword; //true if token is a reserved keyword
    tokenType type; //enum that holds the type of the token
    tokenDetails *details; //pointer to tokenDetails struct, owned by this token, only valid if type is T_Literal or  is a T_Identifier and is a variable/signal.  Lazy allocation, only allocated when needed (see setTokenDetails function declaration).

	//Allow TokenList class to access Token member variables marked private
  //https://en.wikipedia.org/wiki/Friend_class
	friend class TokenList;

public:
     vector <int> numLineofToken = {}; // used in verbose mode of typematch to get the line number of the token by assigning the number of the line the token is on to each token
	//Default Constructor, pointers initialized to NULL, and other variable initialization
  //tokenDetails should NOT be allocated here
	Token(): next(nullptr), prev(nullptr) { };

	//Constructor with string initialization
	Token(const string &stringRep) : next(nullptr), prev(nullptr), stringRep(stringRep) { };

  //Copy constructor
  Token(const Token &token);

  //Token(const string &type, int width); //NEW*********

  //Destructor, free any memory owned by this object
  ~Token();

  //Assignment operator
  void operator =(const Token& token);

	//Returns the Token's *next member
	Token* getNext ( ) const {  return next; }

	//Sets the Token's *next member
	void setNext (Token* next ) { this->next = next; }

	//Returns the Token's *prev member
	Token* getPrev ( ) const { return prev; }

	//Sets the Token's *prev member
	void setPrev (Token* prev ){ this->prev = prev; }

	//Returns a reference to the Token's stringRep member variable
	const string& getStringRep ( ) const { return stringRep; }

	//Sets the token's stringRep variable
	void setStringRep (const string& stringRep ) { this->stringRep = stringRep; }

  //Returns true if token is a keyword
  bool isKeyword () const { return _isKeyword; }

  //Sets isKeyword to true
  void setKeyword() { _isKeyword = true; }

  //Returns the token type
  tokenType getTokenType() const { return type; }

  //Set's the token type
  void setTokenType(tokenType type) { this->type = type; }

  //Returns true if token matches this type
  bool isOperator() const { return (type == T_Operator); }
  //Returns true if token matches this type
  bool isIdentifier() const { return (type == T_Identifier); }
  //Returns true if token matches this type
  bool isLiteral() const { return (type == T_Literal); }
  //Returns true if token matches this type
  bool isComment() const { return (type == T_CommentBody); }
  //Returns true if token matches this type
  bool isOther() const { return (type == T_Other); }

  //Returns a pointer to tokenDetails
  tokenDetails* getTokenDetails() const { return details; }

  //Set's the tokenDetails given a string type and optional vector width
  //Allocates tokenDetails if it doesn't already exist
  void setTokenDetails(const string &type, int width = 0);



};

//A doubly-linked list class consisting of Token elements
class TokenList {
private:
	Token *head; //Points to the head of the token list (doubly linked)
	Token *tail; //Points to the tail of the function list (doubly linked)
	bool keywordparse=false;// used to find if token is of type keyword in findAndSetTokenDetails as well as to test keyword against indentifiers
	bool OpParse=false;// used to find if token is of type operators in findAndSetTokenDetails
	bool CommentFind = false; // used to find if token is of type comment in findAndSetTokenDetails
	string Alpha = "abcdefghijklmnopqrstuvwxyz";//all alphanumeric used when seeing if it is an identifier
	string Alpha_Num = "1234567890abcdefghijklmnopqrstuvwxyz_"; // all string of alphanumeric used when seeing if it is an identifier
	 vector <string> strOP = {"**", "abs", "not", "*", "/", "mod", "rem", "+", "-", "&", "sll", "srl", "sla", "sra", "rol", "ror", "=|", "/=", "<", "<=", ">", ">=", "and", "or", "nand", "nor", "xor", "xnor", "=" };
     vector <string> KeyWord = {"abs","access","after","alias","all","and","architecture","array","assert","attribute","begin","block",
                     "body","buffer","bus","case","component","configuration","constant","disconnect","downto","else","elsif",
                     "end","entity","exit","file","for","function","generate","generic","group","guarded","if","impure","in",
                     "inertial","inout","is","label","library","linkage","literal","loop","map","mod","nand","new","next","nor",
                     "not","null","of","on","open","or","others","out","package","port","postponed","procedure","process","pure",
                     "range","record","register","reject","rem","report","return","rol","ror","select","severity","signal",
                     "shared","sla","sll","sra","srl","subtype","then","to","transport","type","unaffected","units","until",
                     "use","variable","wait","when","while","with","xnor","xor"};//total 97 all keyword in vhdl could've made a hash table but this was easier




    vector <string> VariableNames = {}; // used for signal and varable declarations to hold the names of identifiers that are variables for comparison later on in vhdl
    vector <string> VariableType ={};// used for signal and varable declarations to hold the types of identifiers that are variables for comparison later on in vhdl
    vector <int> VariableWidth ={};// used for signal and varable declarations to hold the widths of identifiers that are variables for comparison later on in vhdl


    string literaldef= "\'\""; // used for checking for literal.. for ex first symbol is "
    string num="0123456789_"; // used when checking for integers
    string unda ="_"; // string holding only underscore symbol;

    int returntype (string type, Token *token);


public:

	//Default Constructor, Empty list with pointers initialized to NULL
	TokenList() : head(nullptr), tail(nullptr) { }

	//Returns a pointer to the head of the list
	Token* getFirst() const { return head; }

	//Returns a pointer to the tail of the list
	Token* getLast() const { return tail; }

	//Creates a new token for the string input, str
	//Appends this new token to the TokenList
	//On return from the function, it will be the last token in the list
	void append(const string &str); //example comment

	//Appends the token to the TokenList if not null
	//On return from the function, it will be the last token in the list
	void append(Token *token);

  //Removes the token from the linked list if it is not null
	//Deletes the token
	//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
	void deleteToken(Token *token);

  //find token details and type and update token.  May require examining properties of neighbouring tokens
  void findAndSetTokenDetails(Token *token);

};

//A class for tokenizing a string of VHDL  code into tokens
class Tokenizer {
private:
		/*State tracking variables for processing a single string*/
	bool complete; //True if finished processing the current string
	size_t offset; //Current position in string
	size_t tokenLength; //Current token length
	string *str; //A pointer to the current string being processed
    string tokenstr;
    string delimALL =" :;()<>=-+*/\'\"\"[]|,\t,\n,\r,\b"; // number of delimeters including space case used to seperate tokens from assignment 3
    string checkDel = ":;()<>=-+*/\'\"\"[]|,"; // number of delimeters not including space case used to seperate tokens from assignment 3
    string compOp = " ;:+*)],\r,\t,\n,\b"; // operator list used when finding compliments
    //string num = "01"; ?? DON"T NEED!!!!
    bool comment;
    int line=0;
    //for when identifier set equal to literal
	//Include any helper functions here
	//e.g. trimming whitespace, comment processing

	//Computes a new tokenLength for the next token
	//Modifies: size_t tokenLength, and bool complete
	//(Optionally): may modify offset
	//Does NOT modify any other member variable of Tokenizer
	void prepareNextToken();

public:
	//Default Constructor- YOU need to add the member variable initializers.
	Tokenizer()
	{
         offset=0;
	    tokenLength=0;
	    complete=false;
	    comment = false;
	}
	    ///
	//Sets the current string to be tokenized
	//Resets all Tokenizer state variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	void setString(string *str);

	//Returns true if all possible tokens have been extracted from the current string (string *str)
	bool isComplete() const { return complete; }

	//Returns the next token. Hint: consider the substr function
	//Updates the tokenizer state
	//Updates offset, resets tokenLength, updates processingABC member variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	string getNextToken();
	int Getline(){return line;};
};


//Removes all comments from the tokenList including the -- marker
//Returns the number of comments removed
int removeComments(TokenList &tokenList);

//Removes all tokens of the given tokenType
//Returns the number of tokens removed
int removeTokensOfType(TokenList &tokenList, tokenType type);

//Pass an arguement of type string
//tolowers every character in that string
// returns the string in lower case form
string LowerString(string myString);

// Creates a counter that counts the number of tokens in the tokenlist
//while a created pointer is pointed at a token in the tokenlist the counter adds one and moves onto the next link in the list
int TokensCounter(const TokenList &tokenList); // Non verbose number of tokens accounted for

// Creates non-verbose version for typematch that passes by reference the number of occurances of the error
//Searches for identifiers set equal to each other by a list of operators in conditional statements and see if it matches in width and type syntactically
//Format is as follows:
//Each token is dealt with sequentially as the function runs through the tokenlist see if it meets any of the counter conditions before moving onto the next token
//if conditions are met then it adds one to its conditions counter and the counter along with the error is couted in the main for non-verbose mode.
void TypeMatch(const TokenList &tokenlist, int &noMisMatch,int &TypeMatchNotWidth, int &WidthMatchNotType, int &NoWidthNoType);
///
 // Creates verbose version for typematch that passes by reference the line number of the errors and error line
//Searches for identifiers set equal to each other by a list of operators in conditional statements and see if it matches in width and type syntactically
//Format is as follows:
//Each token is dealt with sequentially as the function runs through the tokenlist see if it meets any of the counter conditions before moving onto the next token
//if conditions are met it sets a bool that represents the error to true and sets the number of that line to that of the current error line to cout in the main as both these parameters are passed by reference.
void TypeMatch(const Token *token, int &errorline,unsigned int ii,bool &error1,bool &error2,bool &error3);

// Creates verbose version for endif that passes by reference the line missing the endif
//Searches for if's that have an end before it and those that have no end before it and compares those two numbers as well as passing the lines and line number of where the missing end if should be for
//Format is as follows:
//Each token is dealt with token by token as it looks a the line that a certain token is on and pushes it back into a vector
//if conditions are met it sets a bool that represents the error to true and sets the number of that line to that of the current error line to cout in the main and the number of missing endifs are all passed by reference
void MissingEndIf(const Token *token,unsigned int ii,int &LineOfIf,int &LineOfEnd,bool &If,bool &EndIf);

// Creates non-verbose version for typematch that passes by reference the total of missing then's or endif in the vhdl file
//Searches for number of total endifs, ifs, elsifs, thens, then uses the formula missingThen=numif+numelsif-numthen and  missingEnd=numif-numEnd
//Format is as follows:
//Each token is dealt with sequentially as the function runs through the tokenlist see if it meets any of the counter conditions before moving onto the next token
//if conditions are met  then it adds one to its conditions counter and the counter along with the error is couted in the main for non-verbose mode.
void CompletePairing(TokenList &tokenList,int &missingThen,int &missingEnd, int &CondExp);




//Creates a new TokenList, and returns a pointer to this list
//Searches for all conditional expressions in tokenList and appends them to the new list
//Format is as follows:
//Each token that is part of a condtional expression is appended sequentially
//At the end of a conditional expression a newline character is appened
   //Example: if (a = true) then
   //Your list should include "(", "a", "=", "true", ")" and "\n"
//tokenList is NOT modified
TokenList* findAllConditionalExpressions(const TokenList &tokenList);

#endif /* PARSERCLASSES_H_ */
