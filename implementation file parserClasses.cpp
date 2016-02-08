#include "parserClasses.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include <cstdlib>

using namespace std;
//****TokenList class function definitions******
//           function implementations for append have been provided and do not need to be modified
//Creates a new token for the string input, str
//Appends this new token to the TokenList
//On return from the function, it will be the last token in the list
void TokenList::append(const string &str) {
        Token *token = new Token(str);
        append(token);
}
//Appends the token to the TokenList if not null
//On return from the function, it will be the last token in the list
void TokenList::append(Token *token) {
        if (!head) {
                head = token;
                tail = token;
        }
        else {
                tail->setNext(token);
                token->setPrev(tail);
                tail = token;
        }
}
//Complete the implementation of the following member functions:
//****Tokenizer class function definitions******
//Computes a new tokenLength for the next token
//Modifies: size_t tokenLength, and bool complete
//(Optionally): may modify offset
//Does NOT modify any other member variable of Tokenizer
void Tokenizer::prepareNextToken(){
if (str == nullptr||offset>=str->length())//if string is empty or current position is at end of length of string then complete is true
{
complete = true;
//offset = 0;
}
else
{
    while(str->find_first_of(" \t\b\r",offset)==offset)//if found space or tab in current pos then offset increments adds 1
        {
            offset++;
        }
        if (offset==str->length())
        {
            complete = true;
        }

        if(comment==true)//comment is true if it exists in the string
        {
                tokenLength=str->length()-offset;
        }
    else
    {
    tokenLength = str->find_first_of(delimALL, offset) - offset;//finds the nearest delimiter

     if (str->find_first_of(delimALL, offset)==str->find("\'",offset) && str->find_first_of(compOp, offset)==offset+tokenLength+1)// finds the compliments
    {
        tokenLength=tokenLength+1;
    }
    if (str->find_first_of(delimALL, offset)==str->find("\'",offset) && str->find("\'", offset)+1==str->length())//compliment with nothing after it, not even a space
    {
        tokenLength=tokenLength+1;
    }
        if (str->find_first_of(delimALL, offset)==str->find("\'",offset) && str->find_first_of("Ee", offset)==offset+tokenLength+1)// clk'event only
    {
        tokenLength=tokenLength+6;
    }


     if(str->find_first_of(delimALL,offset)==str->find("\"",offset) && str->find_first_of("XBOxbo",offset)==offset+tokenLength-1)//finds the xquote
        {

             tokenLength=str->find("\"",offset+2)-offset+1;
        }


    if (tokenLength==0)
    {

        if(str->find_first_of(checkDel,offset) == offset)//(";",offset)==offset||str->find(":",offset)==offset||str->find("(",offset)==offset||str->find(")",offset)==offset||str->find("=",offset)==offset||str->find("*",offset)==offset||str->find("/",offset)==offset||str->find("[",offset)==offset||str->find("]",offset)==offset||str->find("|",offset)==offset||str->find("<",offset)==offset||str->find(">",offset)==offset)
        {
        tokenLength=1;//tokenlength is 1 because these delmiters have only length of 1

        }

        if(str->find("<=",offset)==offset||str->find(">=",offset)==offset||str->find("=<",offset)==offset||str->find("=>",offset)==offset||str->find(":=",offset)==offset||str->find("**",offset)==offset)//delimiters with length of 2
            {
                tokenLength=2;
            }

        if(str->find("--")==offset)//sets tokenLength to 2 for the -- syntax and comment exists
        {
        tokenLength=2;
        comment=true;
        }
        if(str->find("\"",offset)==offset)//finds the bit vectors
        {

            tokenLength=str->find_first_of("\"",offset+1)-offset+1;


        }
        if(str->find("\'",offset)==offset)//finds single bits
        {
                tokenLength=str->find_first_of("\'",offset+1)-offset+1;


        }

    }

}
}
}

//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer:repareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str) {
this->str=str;
complete = false;
offset = 0;
tokenLength = 0;
comment=0;
line++;
prepareNextToken();
/*Fill in implementation */ }
//Returns the next token. Hint: consider the substr function
//Updates the tokenizer state
//Updates offset, resets tokenLength, updates processingABC member variables
//Calls Tokenizer:repareNextToken() as the last statement before returning.
string Tokenizer::getNextToken()
{

(tokenstr)=str->substr(offset,tokenLength);//gives tokenstr partial string of the line

offset=offset+tokenLength;//updates current position

prepareNextToken();
return tokenstr;
//complete=true;
}
 //Set's the tokenDetails given a string type and optional vector width
  //Allocates tokenDetails if it doesn't already exist
  // COPY CONSTRUCTOR

  Token::Token(const Token &token)
  {
      prev = token.prev; //previous is now the other tokens previous
      next = token.next; // next is now the other tokens next

      setStringRep(token.stringRep); // Copy of stringRep variable we can use
      setTokenType(token.type); // set token type to that of the other token
      _isKeyword = token._isKeyword; // if token is keyword it will set it as a keyword

        if(token.details)
           {
                details = new tokenDetails; // pointer to tokenDetails struct so it can be acessed later
                details ->type = token.details ->type;//pointer to tokenDetails struct  string type, //boolean, std_logic, std_logic_vector, integer etc
                details -> width = token.details -> width; // pointer to tokenDetails struct string  width
           }


  }

  Token:: ~Token() // DEstroyer
  {
     if(details)
    {
        delete details; // deletes details pointer when function exits scops
     }
  }

void Token:: operator =(const Token& token)
    {
        if(details && token.details) // case for if both tokens have structures
        {
            setStringRep(token.stringRep); // sets stringRep to that of the token on the right
            setTokenType(token.type); // sets type to that of the token on the right
           // setKeyword(token._isKeyword);
           _isKeyword = token._isKeyword; // sets isKeyword to true if  the token on the right iskeyword
            setPrev(token.prev); // sets prev to that of the token on the right
            setNext(token.next); // sets next to that of the token on the right

            details -> type = token.details -> type;
            details -> width = token.details -> width;
        }
       else if(details) // if token  passing through has a structure attached to it
        {
            delete details; // first delete ths structure so that the two can be equal
            details = nullptr; //structure points to null
            setStringRep(token.stringRep); // sets stringRep to that of the token on the right
            setTokenType(token.type);// sets type to that of the token on the right
           // setKeyword(token._isKeyword);
           _isKeyword = token._isKeyword;
            setPrev(token.prev);
            setNext(token.next);
        }
        else// this is if the left hand side has no details but the right hand side does
        {

            details = new tokenDetails; // creates new details  for left hand side
            details -> type = token.details -> type; // sets a type pointer
            details -> width = token.details -> width; // sets a width pointer
            setStringRep(token.stringRep); // sets stringRep to that of the token on the right
            setTokenType(token.type);// sets type to that of the token on the right
           _isKeyword = token._isKeyword;
            setPrev(token.prev);
            setNext(token.next);

        }
    }

void Token:: setTokenDetails(const string &type, int width )
{
    if(isLiteral()||isIdentifier()) // For literals and identifiers only settokens details
    {
        details = new tokenDetails; // creates details structure
        details -> type = type; // string type points at it
        details -> width = width; // points to int width
    }

}


void TokenList:: findAndSetTokenDetails(Token *token)
{
string temptoken=token->getStringRep();
for(unsigned int i = 0 ; i < temptoken.length() ; i++)
{
 //and convert string[i] to lower case with "tolower" function
 temptoken[i]=tolower(temptoken[i]);
}


if(CommentFind == true) //  for when it is a comment to make multiple words one token
    {
        token->setTokenType(T_CommentBody); // sets token of type comment body
        CommentFind = false;
         token->details=nullptr;
    }
else
{
    if(temptoken == "--" )//look at the comment symbol
    {
        token->setTokenType(T_Other);//sets it to type Others
        CommentFind = true;//found comment symbol to true
        token->details=nullptr;
    }

    else
    {
        token->_isKeyword=false;//initialize the variable to false
        OpParse=false;//intialize parsing variable to false
        for (unsigned int i=0; i<KeyWord.size();i++)//check if the token is a keyword
        {
            if (temptoken==KeyWord[i])//is it keyword
            {
                token->setKeyword();
            }

        }
        if (token->isKeyword ())//if its a keyword do this
        {
            for(unsigned int i=0; i<strOP.size();i++)//parse through tokens to see if its operator
            {
                if(temptoken==strOP[i])//is it operator
                {
                    OpParse=true;
                }
            }

            if(OpParse==true)
            {
                token->setTokenType(T_Operator);// set type to operator
                token->details=nullptr;
            }
            if(OpParse==false)
            {
                token->setTokenType(T_Identifier);//set type to identifier
                if(temptoken=="false"||temptoken=="true")// if the token has string of these set its details type to boolean with width 0
                {
                    token->setTokenDetails("boolean",0);
                }

                else
                    {
                        token->details=nullptr;
                    }
                }
                    //token->setTokenDetails("std_logic",tokentemp.length()); // NOT TRUE!!!KLJK
            }



        else //not a keyword
        {
            for (unsigned int i=0; i<strOP.size();i++)//parse through to see if its an operator
            {
                if(temptoken==strOP[i])//is it operator
                {
                    OpParse=true;
                }
            }
            if(OpParse==true)
            {
                token->setTokenType(T_Operator);// set type to operator
                token->details=nullptr;
            }
            if(OpParse==false)
            {
                if(temptoken.find_first_of(literaldef,0)==0 || temptoken.find_first_of("\"",0)==1 || temptoken.find_first_of(num,0)==0)//is it a literal
                {
                token->setTokenType(T_Literal);
                    if(temptoken.find_first_of("\'",0)==0) //single bit case sets name to single bit
                    {
                        token->setTokenDetails("std_logic",temptoken.length()-2);
                    }
                    if(temptoken.find_first_of("\"",0)==0) // vector bit sets name to bit vectors
                    {
                        token->setTokenDetails("std_logic_vector",temptoken.length()-2);
                    }
                    if(temptoken.find_first_of("\"",0)==1 && temptoken.find_first_of("x",0) == 0) // for X,O,B and so on in front of a bit vector
                    {
                        token->setTokenDetails("std_logic_vector",(temptoken.length()-3)*4);
                    }
                     if(temptoken.find_first_of("\"",0)==1 && temptoken.find_first_of("o",0) == 0) // for X,O,B and so on in front of a bit vector
                    {
                        token->setTokenDetails("std_logic_vector",(temptoken.length()-3)*3);
                    }
                     if(temptoken.find_first_of("\"",0)==1 && temptoken.find_first_of("b",0) == 0) // for X,O,B and so on in front of a bit vector
                    {
                        token->setTokenDetails("std_logic_vector",(temptoken.length()-3)*1);
                    }
                    if(temptoken.find_first_of(num,0)==0) // for just a number
                    {
                        token->setTokenDetails("Integer",temptoken.length());
                    }
                }
                else
                {
                    if(temptoken.find_first_of(Alpha,0)==0 && temptoken.find_first_of(num,0)!=0&&temptoken.find_first_of(unda,(temptoken.length()-1)) !=temptoken.length()-1)//conditions to see if the token meets the VHDL variable requirement
                    {
                        bool VariableFound=false;//true if a variable is seen more than twice
                        token -> setTokenType(T_Identifier);//sets token details to identifier
                         for(unsigned ii=0;ii<VariableNames.size();ii++)//parse through the name vector that holds all variable names
                            {
                                if(temptoken==VariableNames[ii])
                                {
                                    token->setTokenDetails(VariableType[ii],VariableWidth[ii]);//sets token details to the same as the one declared before
                                    VariableFound==true;//
                                }
                            }
                        if(LowerString(token->getPrev()->getStringRep())=="signal"||LowerString(token->getPrev()->getStringRep())=="variable"||LowerString(token->getPrev()->getStringRep())=="type")
                        {
                            string strType;//variable that holds the string of the type
                            string vector1;//variables to hold the first number of a vhdl vector
                            string vector2;//variables to hold the second number of a vhdl vector



                            if(token->getNext()->getNext()->getNext()->getStringRep()==";" && VariableFound==false)
                            {
                                strType=token->getNext()->getNext()->stringRep;//sets the variable strType to the string on that location
                                strType=LowerString(strType);
                                token->setTokenDetails(strType,1);
                                VariableNames.push_back(temptoken);
                                VariableType.push_back(strType);
                                VariableWidth.push_back(1);
                            }
                          else if((token->getNext()->getNext()->getNext()->getStringRep()==":=" || token->getNext()->getNext()->getNext()->getStringRep()=="=:") && VariableFound==false)
                          {
                               strType=token->getNext()->getNext()->stringRep;//sets the variable strType to the string on that location
                               strType=LowerString(strType);
                                token->setTokenDetails(strType,atoi(token->getNext()->getNext()->getNext()->getNext()->getStringRep().c_str()));
                                VariableNames.push_back(temptoken);
                                VariableType.push_back(strType);
                                VariableWidth.push_back(atoi(token->getNext()->getNext()->getNext()->getNext()->getStringRep().c_str()));
                          }

                            if(token->getNext()->getNext()->getNext()->getStringRep()=="(" && VariableFound==false)
                            {
                                strType=token->getNext()->getNext()->stringRep;//sets the variable strType to the string on that location
                                strType=LowerString(strType);
                                vector1=token->getNext()->getNext()->getNext()->getNext()->stringRep;
                                vector2=token->getNext()->getNext()->getNext()->getNext()->getNext()->getNext()->stringRep;
                                token->setTokenDetails(strType,(abs(atoi(vector1.c_str())-atoi(vector2.c_str()))+1));
                                VariableNames.push_back(temptoken);
                                VariableType.push_back(strType);
                                VariableWidth.push_back(abs(atoi(vector1.c_str())-atoi(vector2.c_str()))+1);
                            }
                            if(token ->getNext()-> stringRep == "," )
                               {
                                   Token *temp;
                                   temp = token;
                                   while(temp -> getNext() -> stringRep == ",")
                                {
                                    temp = temp->getNext()->getNext();
                                }
                                if(temp -> getNext()->getNext()->getNext()->stringRep == ";")
                                {
                                    token -> setTokenDetails(temp -> getNext()->getNext()-> stringRep, 1);
                                    VariableNames.push_back(temptoken);
                                    VariableType.push_back(temp -> getNext()->getNext()-> stringRep);
                                    VariableWidth.push_back(1);
                                }
                                else if(temp -> getNext()->getNext()->getNext()->stringRep == "(")
                                {
                                    vector1=temp->getNext()->getNext()->getNext()->getNext()->stringRep;
                                    vector2=token->getNext()->getNext()->getNext()->getNext()->getNext()->getNext()->stringRep;
                                    token->setTokenDetails(temp -> getNext()->getNext()-> stringRep,(abs(atoi(vector1.c_str())-atoi(vector2.c_str()))+1));
                                    VariableNames.push_back(temptoken);
                                    VariableType.push_back(temp -> getNext()->getNext()-> stringRep);
                                    VariableWidth.push_back(abs(atoi(vector1.c_str())-atoi(vector2.c_str()))+1);
                                }


                               }
                                if(token -> getPrev()-> stringRep =="," && token -> getPrev() -> getPrev() -> isIdentifier())
                                {
                                    token->setTokenDetails(token->getPrev()->getPrev()->details->type,token->getPrev()->getPrev()->details->width);
                                    VariableNames.push_back(temptoken);
                                    VariableType.push_back(token->getPrev()->getPrev()->details->type);
                                    VariableWidth.push_back(token->getPrev()->getPrev()->details->width);
                                }
                        }
                        else if(LowerString(token->getPrev()->getStringRep())=="(" && LowerString(token->getPrev()->getPrev()->getPrev()->getPrev()->getStringRep())=="type" )
                        {
                            token->setTokenDetails(token->getPrev()->getPrev()->getStringRep(), token->getPrev()->getPrev()->details->width);
                             VariableNames.push_back(temptoken);
                             VariableType.push_back(token->getPrev()->getPrev()->getStringRep());
                             VariableWidth.push_back(token->getPrev()->getPrev()->details->width);

                        }

                        else if(LowerString(token->getPrev()->getStringRep())==",")
                        {
                            token->setTokenDetails(token->getPrev()->getPrev()->details->type,token->getPrev()->getPrev()->details->width);
                            VariableNames.push_back(temptoken);
                            VariableType.push_back(token->getPrev()->getPrev()->details->type);
                            VariableWidth.push_back(token->getPrev()->getPrev()->details->width);


                        }
                        else if(LowerString(token->getPrev()->getStringRep())=="constant" && token->getNext()->getStringRep()==":")
                        {
                            token->setTokenDetails(token->getNext()->getNext()->stringRep,atoi(token->getNext()->getNext()->getNext()->getNext()->stringRep.c_str()));
                            VariableNames.push_back(temptoken);
                            VariableType.push_back(token->getNext()->getNext()->stringRep);
                            VariableWidth.push_back(atoi(token->getNext()->getNext()->getNext()->getNext()->stringRep.c_str()));
                        }
                       //else if(token->getPrev()->stringRep ==")")

                    }
                    else
                    {
                        token->setTokenType(T_Other);
                        token->details=nullptr;
                    }
                }

            }
        }


    }
}
}




 //}ing
//****Challenge Task Functions******
//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.


void TokenList::deleteToken(Token *token)
{

 if(head==nullptr || token == nullptr){return;}

   if(token == head)// if the token is on the first node
   {
        head = head->next;
        head->prev = nullptr;
   }
   else if(token == tail)//if the token is on the last node
   {
        tail = tail->prev;
        tail->next = nullptr;
   }
   else
   {
        token->prev->next = token->next;
        token->next->prev = token->prev;
   }
   delete token;
}


//Removes all comments from the tokenList including the -- marker

//Returns the number of comments removed

int removeComments(TokenList &tokenList)
{
/*Fill in implementation */
Token *temp, *temp1;
int counter=0;

if(tokenList.getFirst() != nullptr)
{
    temp = tokenList.getFirst();
    while(temp)
    {
    temp1 = temp->getNext();
        if(temp->getStringRep() == "--")//if the comment symbol is found
        {
        counter++;//counts how many comments are removed
            tokenList.deleteToken(temp);//delets the comment symbol
            temp = temp1;
            temp1 = temp->getNext();
            tokenList.deleteToken(temp);//deletes the comment body
            temp= temp1;

        }
        else
        {
            temp = temp->getNext();
        }
    }
}
return counter;// returns the number of comments removed
}


int removeTokensOfType(TokenList &tokenList, tokenType type)
{
Token *temp, *temp1;
int counter=0;
int typenum;
if(type == T_Operator)
{
typenum=0;
}
if(type == T_Identifier)
{
typenum=1;
}
if(type == T_Literal)
{
typenum=2;
}
if(type == T_CommentBody)
{
typenum=3;
}
if(type == T_Other)
{
typenum=4;
}

if(tokenList.getFirst() != nullptr)
{
    temp = tokenList.getFirst();
    while(temp)
    {
    temp1 = temp->getNext();
    //cout<<temp->getTokenType();//<---- this one is wierd if you debug it
        if(temp->getTokenType() == typenum)//if the tokenType has the same element value as typenum
        {
            counter++;
            tokenList.deleteToken(temp);// deletes the token if found
            temp = temp1;


        }
        else
        {
        temp = temp->getNext();
        }
    }
}
return counter;//counts the number of total tokens removed
}

TokenList CopyAndToLower(const TokenList &tokenList)// Copies the token list and lowers the every tokens to lowercase
{
    TokenList Copy(tokenList);
    Token *Point;
    string temp;

    Point = Copy.getFirst();
    //lower all the string in the copied tokenlist
    while(Point)//parse through all tokens
    {
        temp = Point->getStringRep();
        for( int i = 0; i<(Point->getStringRep().length()); i++)//sets each token's string to lowercase
        {
            temp[i] = tolower(temp[i]); // for every character
        }
        Point->setStringRep(temp); // point now points to the lowercase version
        Point = Point->getNext(); // iterate through
    }

    return Copy; // returns the lowercase version
}


TokenList* findAllConditionalExpressions(const TokenList &tokenList)
{
    TokenList Copy = tokenList;//copies the token list
    TokenList *newList = new TokenList;//new list to hold the conditional expressions
    Token *Point;//declares a pointer to parse through all tokens




    Point = Copy.getFirst();//points at the beginning of the token list
    while(Point)
    {
        if(LowerString(Point->getStringRep()) == "if")//if the token is on the word "if" right now
        {
            if(Point->getPrev()!=nullptr && LowerString(Point->getPrev()->getStringRep())=="end")//if the token has the string end before it meaning this if is an "end if"
            {
              //do nothing
            }
            else // when not end if
            {
            Point= Point->getNext();
                while( Point->getNext()!=nullptr && LowerString(Point->getStringRep()) != "then")//searches for the word then when now at end if
                {
                    newList->append(Point->getStringRep());//appends all tokens before the word then
                    Point= Point->getNext();
                }
            newList->append("\\n"); // adds \n to the back of the conditional expression
            }
        }

        if(LowerString(Point->getStringRep()) == "elsif"||LowerString(Point->getStringRep()) == "when")//if the token is on the word elseif or when right now
        {
            if(LowerString(Point->getStringRep()) == "elsif")//if it is elsif do this
            {
                Point =Point-> getNext();
                while(Point->getNext() && LowerString(Point->getStringRep()) != "then")
                {
                    newList->append(Point->getStringRep());//appends all tokens before the word then is seen
                    Point= Point->getNext();
                }
                newList->append("\\n"); // adds \n to the back of the conditional expression
            }

            else if(LowerString(Point->getStringRep()) == "when")// if the token is on the string when right now
            {
                 Point =Point-> getNext();
                while(Point->getNext() && LowerString(Point->getStringRep()) != "else")
                {
                    newList->append(Point->getStringRep());//appends all tokens before the word else is seen
                    Point= Point->getNext();
                }

                newList->append("\\n");// adds \n to the back of the conditional expression
            }

        }

        else
        {
            Point=Point->getNext(); // moves through token list
        }
    }
    return newList;// returns the list that holds all conditional expressions
}


int TokensCounter(const TokenList &tokenList) // Non verbose number of tokens accounted for
{
    int numtokens=0;//inditialize and declare a variable that counts the token
    Token *Point;//pointer declared
    Point=tokenList.getFirst();//pointer points at the head of the list
    while(Point) // not equal to nullptr
    {
        numtokens++;//adds 1 to the variable token for every token parsed
        Point=Point->getNext();// sets the pointer onto the next
    }


    return numtokens;//returns the total number of tokens
}




void CompletePairing(TokenList &tokenList,int &missingThen,int &missingEnd, int &CondExp)
{
    TokenList Copy(tokenList);// make a copy of the original list

    Token *Pairs = Copy.getFirst();// sets the pointer Pair to the head of the copy list
    int numif=0; // holds num of ifs in list
    int numthen=0; // holds num of thens in list
    int numelsif=0;// holds num of elseifs in list
    int numEnd=0;// holds num of ends in list
    int numWhen =0;// holds num of whens in list

    while(Pairs) // not equal to null-pointer
    {
      if(LowerString(Pairs->getStringRep())=="if")//if the token is on the word if
      {
        if(Pairs->getPrev()!=nullptr && LowerString(Pairs->getPrev()->getStringRep())=="end")//if the word before the token is end
        {
            numEnd++;//end count increase by 1
            Pairs=Pairs->getNext();
        }
        else // it is just an if
        {
        numif++;//if count increases by 1
        }
      }
      else if(LowerString(Pairs->getStringRep())=="then")
      {
        numthen++;//then count increases by 1
      }
      else if(LowerString(Pairs->getStringRep())=="elsif")
      {
        numelsif++;//elsif count increases by 1
      }
    else if(LowerString(Pairs->getStringRep())=="when")
      {
        numWhen++;//when count increases by 1
      }

    Pairs=Pairs->getNext(); // iterate through list
    }
    missingThen=numif+numelsif-numthen;//equation to find the missing then
    missingEnd=numif-numEnd;//equation to find the missing end
    CondExp = numWhen + numthen;//equation to find the number of total condition expression

}


  void TypeMatch(const TokenList &tokenlist, int &noMisMatch,int &TypeMatchNotWidth, int &WidthMatchNotType, int &NoWidthNoType) // when identifier is set equal to identifier
    {
        TokenList Copy=CopyAndToLower(tokenlist); // using copy list not original
        Token *cursor = Copy.getFirst(); // starting from first token
        while(cursor)
        {

          // case for if it is an identifier token followed by a operator of some sort, followed by another identifier
            if(cursor ->isIdentifier() && (cursor -> getNext() -> getNext() != nullptr) && (cursor -> getNext() -> getStringRep() == "=" ||cursor -> getNext() -> getStringRep() == "<=" || cursor -> getNext() -> getStringRep() == "=>"|| cursor -> getNext() -> getStringRep() == "/="|| cursor -> getNext() -> getStringRep() == ">"|| cursor -> getNext() -> getStringRep() == "<"|| cursor -> getNext() -> getStringRep() == ">="|| cursor -> getNext() -> getStringRep() == "<="|| LowerString(cursor -> getNext() -> getStringRep()) == "and"|| LowerString(cursor -> getNext() -> getStringRep()) == "nand"|| LowerString(cursor -> getNext() -> getStringRep()) == "nor"|| LowerString(cursor -> getNext() -> getStringRep()) == "or"|| LowerString(cursor -> getNext() -> getStringRep()) == "xor"|| LowerString(cursor -> getNext() -> getStringRep()) == "xnor") &&( (cursor -> getNext() -> getNext() -> isIdentifier())||  cursor -> getNext() -> getNext() -> isLiteral()))
                {
                if(cursor->getTokenDetails() && cursor->getNext()->getNext()->getTokenDetails()) // making sure both tokens have details set
                    {
                    if((cursor->getTokenDetails()->width ==cursor->getNext()->getNext()->getTokenDetails() ->width) && (cursor ->getTokenDetails()->type== cursor->getNext()->getNext()->getTokenDetails()->type))
                        {

                            noMisMatch++; // number of perfect statements
                             cursor = cursor -> getNext(); // move to next token

                        }
                    else if(cursor->getTokenDetails()->width !=cursor->getNext()->getNext()->getTokenDetails() ->width && cursor ->getTokenDetails()->type== cursor->getNext()->getNext()->getTokenDetails()->type) // if token  passing through has a structure attached to it
                        {

                            TypeMatchNotWidth++; // number of type match but width does not statements
                            cursor = cursor -> getNext();// move to next token

                        }
                    else if(cursor->getTokenDetails()->width ==cursor->getNext()->getNext()->getTokenDetails() ->width && cursor ->getTokenDetails()->type!= cursor->getNext()->getNext()->getTokenDetails()->type)// this is if the left hand side has no details but the right hand side does
                        {

                           WidthMatchNotType++; // number of width match but type does not statements
                            cursor = cursor -> getNext();// move to next token
                        }
                    else
                        {

                           NoWidthNoType++; // completely wrong statements
                            cursor = cursor -> getNext();// move to next token
                        }
                }
                else // if token does not have details or token getnext getnext does not have details
                    {
                        cursor = cursor -> getNext();// move to next token

                    }

            }// if fails original entering case of  if it is an identifier token followed by a operator of some sort, followed by another identifier
            else
            {
                cursor = cursor -> getNext();// move to next token
            }

        }

    }
   void TypeMatch(const Token *token, int &errorline,unsigned int ii,bool &error1,bool &error2,bool &error3)
   {
      unsigned int number=0; // iterator


//            cout<<token->numLineofToken[ii];
            number=token->numLineofToken[ii]; // vector that holds which tokens are on what line i=from append line

            if(token ->isIdentifier() && (token -> getNext() -> getNext() != nullptr) && (token -> getNext() -> getStringRep() == "=" ||token -> getNext() -> getStringRep() == "<=" || token -> getNext() -> getStringRep() == "=>"|| token -> getNext() -> getStringRep() == "/="|| token -> getNext() -> getStringRep() == ">"|| token -> getNext() -> getStringRep() == "<"|| token -> getNext() -> getStringRep() == ">="|| token -> getNext() -> getStringRep() == "<="|| LowerString(token -> getNext() -> getStringRep()) == "and"|| LowerString(token -> getNext() -> getStringRep()) == "nand"|| LowerString(token -> getNext() -> getStringRep()) == "nor"|| LowerString(token -> getNext() -> getStringRep()) == "or"|| LowerString(token -> getNext() -> getStringRep()) == "xor"|| LowerString(token -> getNext() -> getStringRep()) == "xnor") &&( (token -> getNext() -> getNext() -> isIdentifier())||  token -> getNext() -> getNext() -> isLiteral()))
                {
                if(token->getTokenDetails() && token->getNext()->getNext()->getTokenDetails())// making sure both tokens have details set
                    {
                    if(token->getTokenDetails()->width ==token->getNext()->getNext()->getTokenDetails() ->width && token ->getTokenDetails()->type== token->getNext()->getNext()->getTokenDetails()->type)
                        {
                            //cout << "Match no error"<<endl;// no error

                        }
                    else if(token->getTokenDetails()->width !=token->getNext()->getNext()->getTokenDetails() ->width && token ->getTokenDetails()->type== token->getNext()->getNext()->getTokenDetails()->type) // if token  passing through has a structure attached to it
                        {
                            //cout << "Type matches but width does not ERROR"<<endl;
                            errorline=number; // sets number of line to that of an error line
                            error1=true;
                        }
                    else if(token->getTokenDetails()->width ==token->getNext()->getNext()->getTokenDetails() ->width && token ->getTokenDetails()->type!= token->getNext()->getNext()->getTokenDetails()->type)// this is if the left hand side has no details but the right hand side does
                        {
                           // cout <<"Width matches but type does not ERROR"<<endl;
                           errorline=number;// sets number of line to that of an error line
                           error2=true;
                           // tokenlist.errorline[ii]=number;
                        }
                    else
                        {
                           // cout << "Width does not match and Type does not Match"<<endl;
                           errorline=number;// sets number of line to that of an error line
                           error3=true;
                          // tokenlist.errorline[ii]=number;
                        }
                }

            }
            else
            {

            }

    }


string LowerString(string myString)//change each characters of a string to lower case
{
    for( unsigned int i = 0; i< myString.size(); i++)
    {
        myString[i] = tolower(myString[i]); // character by character
    }

    return myString; // string all in lowercase

}

void MissingEndIf(const Token *token,unsigned int ii,int &LineOfIf,int &LineOfEnd,bool &If,bool &EndIf)
{

if(token->getStringRep() == "if")//if the token is on the the string IF
{
    if(token->getPrev()!=nullptr && token->getPrev()->getStringRep()=="end")
        {
            LineOfEnd=token->numLineofToken[ii];//saves the line which if is found into the variable
            EndIf=true;//true if "if" has been found
        }
    else
        {
            LineOfIf=token->numLineofToken[ii];// saves the line which End If is found into the variable

            If=true;//true if "end has been found"
        }
}
else
{
//do nothing

}


}
