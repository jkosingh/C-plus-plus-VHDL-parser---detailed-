#include "parserClasses.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
int main() {
        ifstream sourceFile;
        TokenList tokens;

  //Lists for types of tokens
  TokenList operatorTokens;
  TokenList identifierTokens;
  TokenList literalTokens;
  TokenList commentBodyTokens;
  TokenList otherTokens;

        Tokenizer tokenizer;
        //Read in a file line-by-line and tokenize each line
        vector <int> filler = {};
        vector <string> printLine={};
        sourceFile.open("ifelsif.vhd");
        if (!sourceFile.is_open()) {
                cout << "Failed to open file" << endl;
                return 1;
        }

        while(!sourceFile.eof()) {
                string line;
                getline(sourceFile, line);
        printLine.push_back(line);
                tokenizer.setString(&line);

                 //int myLine = tokenizer.Getline();
                // cout<<myLine <<endl;
                while(!tokenizer.isComplete()) {
            //    cout<<"hell";
                        tokens.append(tokenizer.getNextToken());
                          filler.push_back( tokenizer.Getline()) ;

                }
        }


        /*Test your tokenization of the file by traversing the tokens list and printing out the tokens*/
        //removeComments(tokens);

          /*Test your tokenization of the file by traversing the tokens list and printing out the tokens*/
          ////////ORIGINAL////////////////////////////////////////////////////////////////////////////////////////
       Token *t = tokens.getFirst();
         cout<<"orignal list"<<endl;
        while(t) {

                cout << t->getStringRep() << " ";
               // tokens.findAndSetTokenDetails(t);
     // tokens.findAndSetTokenDetails(t);
                t = t->getNext();
        }
       // removeTokensOfType(tokens, T_CommentBody);

////////////////////////PART1TESTING///////////////////////////////////////////////////////////////////////////////////
//        Token *t = tokens.getFirst();
 //      Token *t = tokens.getFirst();
//        Token *t = tokens.getFirst();
        TokenList Copy(tokens); // Using copy contructor
        t = Copy.getFirst();
         cout<<"copied list"<<endl;
        while(t) {

                cout << t->getStringRep() << " ";
                tokens.findAndSetTokenDetails(t);
                t = t->getNext();

        }
      /*  removeTokensOfType(Copy, T_CommentBody);
        cout<<endl;
        t = Copy.getFirst();
        while(t) {

                cout << t->getStringRep() << " ";
                t = t->getNext();
        }*/

        cout<<endl<<endl;

        t = Copy.getFirst();
        while(t)
        {
            if(t->isOperator())
            {operatorTokens.append(t->getStringRep());}

            else if(t->isComment())
            { commentBodyTokens.append(t->getStringRep());}

            else if(t->isOther())
            {otherTokens.append(t->getStringRep());}

            else if(t->isLiteral())
            {literalTokens.append(t->getStringRep());}

            else if(t->isIdentifier())
            {identifierTokens.append(t->getStringRep());}

            cout<<t->getStringRep()<<" type: "<< t->getTokenType()<<" keyword: "<<t->isKeyword();
            if(t->getTokenDetails())
            {
                  cout <<" string type: "<< t->getTokenDetails()->type<< " the width is: " << t->getTokenDetails()-> width <<endl;
            }

            else
            {
                cout << endl;
            }

            t = t->getNext();
       }
       //////////////////////////////PART2TESTING//////////////////////////////////////////////////////////////////////////////////////////////
        cout<<"My conditional statements are: ";
        //Token *cursor = operatorTokens.getFirst();
        Token *stuff=findAllConditionalExpressions(Copy)->getFirst();
        while(stuff)
        {
            cout << stuff->getStringRep() << " ";
                stuff= stuff->getNext();
        }
        cout<<endl;

  cout<<endl;
    cout<<endl;
      cout<<endl;
        cout<<endl;

       t = tokens.getFirst();
         cout<<"orignal list"<<endl;
        while(t) {

                cout << t->getStringRep() << " ";
               // tokens.findAndSetTokenDetails(t);
     // tokens.findAndSetTokenDetails(t);
                t = t->getNext();
        }
       // removeTokensOfType(tokens, T_CommentBody);


        string mode;
        cout<<endl;
        cout<< "Do you want verbose or non-verbose mode or BONUS!?: " << endl;
        cin >> mode;

       /////////////////////////////NON VERBOSE MODE TESTING//////////////////////////////////////////////////////
       if( LowerString(mode) == "non-verbose")
       {

        cout<<endl<<endl;
        t = Copy.getFirst();
        cout << "THE TOTAL AMOUNT OF TOKENS IN THIS VHDL IS : " << TokensCounter(Copy) << endl; //Part A
        int missingThen;
        int missingEnd;
        int CondExp;
        CompletePairing(Copy,missingThen,missingEnd,CondExp);
        cout<<"TOTAL NUMBER OF MISSING THENS: "<<missingThen<<endl;
        cout<<"TOTAL NUMBER OF MISSING END IFS: "<<missingEnd<<endl;
         cout<<"TOTAL NUMBER OF CONDITIONAL EXPRESSIONS: "<<CondExp<<endl;

        //removeComments(tokens);
        int noMisMatch = 0;
        int TypeMatchNotWidth = 0;
        int WidthMatchNotType = 0;
        int NoWidthNoType = 0;

        TypeMatch(Copy,noMisMatch, TypeMatchNotWidth, WidthMatchNotType, NoWidthNoType);
            cout << "MATCH NO ERROR " << " " << noMisMatch<<endl;
           cout <<"TYPE MATCHES BUT WIDTH DOES NOT ERROR"<<" " << TypeMatchNotWidth<<endl;
            cout <<"WIDTH MATCHES BUT TYPE DOES NOT ERROR"<<" " << WidthMatchNotType << endl;
            cout << "WIDTH AND TYPE BOTH DO NOT MATCH ERROR"<<" " << NoWidthNoType << endl;


       }



////////////////////////////////////VERBOSE TESTING///////////////////////////////////////////////////////////////////////
if( LowerString(mode) == "verbose")
{
      cout<<endl<<endl;
        t = Copy.getFirst();
        cout << "THE TOTAL AMOUNT OF TOKENS IN THIS VHDL IS : " << TokensCounter(Copy) << endl; //Part A
        int missingThen;
        int missingEnd;
        int CondExp;
        CompletePairing(Copy,missingThen,missingEnd,CondExp);
        cout<<"TOTAL NUMBER OF MISSING THENS: "<<missingThen<<endl;
        cout<<"TOTAL NUMBER OF MISSING END IFS: "<<missingEnd<<endl;
       //  cout<<"TOTAL NUMBER OF CONDITIONAL EXPRESSIONS: "<<CondExp<<endl;

        //removeComments(tokens);
        int noMisMatch = 0;
        int TypeMatchNotWidth = 0;
        int WidthMatchNotType = 0;
        int NoWidthNoType = 0;

        TypeMatch(Copy,noMisMatch, TypeMatchNotWidth, WidthMatchNotType, NoWidthNoType);
            cout << "MATCH NO ERROR " << " " << noMisMatch<<endl;
           cout <<"TYPE MATCHES BUT WIDTH DOES NOT ERROR"<<" " << TypeMatchNotWidth<<endl;
            cout <<"WIDTH MATCHES BUT TYPE DOES NOT ERROR"<<" " << WidthMatchNotType << endl;
            cout << "WIDTH AND TYPE BOTH DO NOT MATCH ERROR"<<" " << NoWidthNoType << endl;







    CompletePairing(Copy,missingThen,missingEnd,CondExp);
   // cout << "THE TOTAL NUMBER OF AMOUNT OF TOKENS IN THE VHDL FILE IS: " << TokensCounter(Copy) << endl; //Part A
t=Copy.getFirst();
unsigned i=0;
vector <int> errorlines = {};

while(t)
    {
        if(i<filler.size())
        {
                        t->numLineofToken.push_back(filler[i]);
                        t=t->getNext();
                        i++;
        }
    }


unsigned int ii=0;
  int errorline=0; // which line has error it holds
  t=Copy.getFirst(); // starts at first token
  int preverrorline=0; // line in which previous error is on
  bool error1=false; // type match width does not
  bool error2=false; // width match typ does not
  bool error3=false; // type and width both don't match
  bool noerror=true;
 noMisMatch = 0;
TypeMatchNotWidth = 0;
WidthMatchNotType = 0;
NoWidthNoType = 0;

        TypeMatch(Copy,noMisMatch, TypeMatchNotWidth, WidthMatchNotType, NoWidthNoType);
while(t)
{
  if(errorline!=0 && errorline!=preverrorline)
        {
            if(error1==true){
            errorlines.push_back(errorline);
            cout << "TYPE MATCHES BUT WIDTH DOES NOT, ERROR. "<< "Number of errors: "<< TypeMatchNotWidth << " ERROR IS ON LINE: " << errorline<<" THE LINE WHICH CONTAINS THE ERROR IS: "<<printLine[errorline-1] << endl<< endl;
            error1=false;
            noerror=false;
            }
            else if(error2==true)
            {
            errorlines.push_back(errorline);
            cout <<"WIDTH MATCHES BUT TYPE DOES NOT, ERROR. "<< "Number of errors: "<< WidthMatchNotType << " ERROR IS ON LINE: " << errorline<<" THE LINE WHICH CONTAINS THE ERROR IS: "<<printLine[errorline-1] << endl<< endl;
            error2=false;
            noerror=false;
            }
            else if(error3==true)
            {
            errorlines.push_back(errorline);
             cout << "WIDTH AND TYPE BOTH DO NOT MATCH, ERROR. "<< "Number of errors: "<< NoWidthNoType << " ERROR IS ON LINE: " << errorline<<" THE LINE WHICH CONTAINS THE ERROR IS: "<<printLine[errorline-1]<<endl<< endl;
              error3=false;
              noerror=false;
            }
        }

    preverrorline=errorline; // moves the line so now it is on token for next line

    TypeMatch(t, errorline, ii,error1,error2,error3);
   // cout<<errorline<<" ";

    t=t->getNext();
}
if(noerror==true)
{
    cout<<"THERE ARE NO ERRORS IN TYPE OR WIDTH. " << endl<< endl;
}


/*
            cout <<"Type matches but width does not ERROR"<<" " << TypeMatchNotWidth<<endl;
            cout <<"Width matches but type does not ERROR"<<" " << WidthMatchNotType << endl;
            cout << "Width does not match and Type does not Match"<<" " << NoWidthNoType << endl;

  /* For your testing purposes only */
  /* Ensure that tokens have all type information set*/
  /* Create operator,identifier,literal, etc. tokenLists from the master list of tokens */
cout << endl ;
  t=Copy.getFirst();
bool then=false;
bool complete=true;
 ii=0;
int LineOfIf=0;
int LineOfEnd=0;
vector <int> vecIf;
vector <int> vecEnd;
bool If=false;
bool EndIf=false;

while(t)
{
    if(t->getPrev() == nullptr)
    {

    if(LowerString(t->getStringRep())=="if" || LowerString(t->getStringRep())=="elsif" || complete==false)
    {
        cout<<t->getStringRep()<<" ";
        complete =false;

        if  (t->getStringRep()==";" && then == false)
        {
            cout<< " MISSING 1 THEN. "<<endl<< endl;
            complete =true;
            then=false;
        }
        else if  (t->getStringRep()==";" && then == true)
        {
            cout<<" MISSING 0 THEN. "<<endl<< endl;
            complete =true;
            then=false;
        }

        if  (LowerString(t->getStringRep())=="then")
        {
            then =true;
        }

       }
    }

else if((LowerString(t->getStringRep())=="if" &&LowerString(t->getPrev()-> getStringRep()) != "end") || LowerString(t->getStringRep())=="elsif" || complete==false)
    {
        cout<<t->getStringRep()<<" ";
        complete =false;

        if  (t->getStringRep()==";" && then == false)
        {
            cout<< " MISSING 1 THEN. "<<endl<< endl;
            complete =true;
            then=false;
        }
        else if  (t->getStringRep()==";" && then == true)
        {
            cout<<" MISSING 0 THEN. "<<endl<< endl;
            complete =true;
            then=false;
        }

        if  (LowerString(t->getStringRep())=="then")
        {
            then =true;
        }

    }
      MissingEndIf(t,ii,LineOfIf,LineOfEnd,If,EndIf);
    if(If==true)
    {
    vecIf.push_back(LineOfIf);
    If=false;
    }
    if(EndIf==true)
    {
    vecEnd.push_back(LineOfEnd);
    EndIf=false;
    }


t=t->getNext();
}
int IfmissingEnd=0;
if(vecIf.size()!=vecEnd.size())
{
    IfmissingEnd=vecIf.size()-vecEnd.size();
    for(unsigned i=0;i<IfmissingEnd;i++)
    {
    cout<<"LINE "<<vecIf[i]<< " IS MISSING AN END IF."<<"THE LINE WHICH CONTAINS THE ERROR IS: " <<printLine[vecIf[i]-1] << endl<< endl;

    }

}
else
{
    cout << "THERE IS NO MISSING END IFS IN THIS VHD FILE. " << endl<< endl;
}
    cout << "THE NUMBER OF CONDITIONAL EXPRESSIONS ARE: " << CondExp<< endl;

}
cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


if(LowerString(mode) == "bonus")
{
t=Copy.getFirst();
unsigned int ii=0;
int LineOfIf=0;
int LineOfEnd=0;
vector <int> vecIf;
vector <int> vecEnd;
bool If=false;
bool EndIf=false;

while (t)
{
    MissingEndIf(t,ii,LineOfIf,LineOfEnd,If,EndIf);
    if(If==true)
    {
    vecIf.push_back(LineOfIf);
    If=false;
    }
    if(EndIf==true)
    {
    vecEnd.push_back(LineOfEnd);
    EndIf=false;
    }
t=t->getNext();
}

int IfmissingEnd=0;
if(vecIf.size()!=vecEnd.size())
{
    IfmissingEnd=vecIf.size()-vecEnd.size();
    for(unsigned i=0;i<IfmissingEnd;i++)
    {
    cout<<"LINE "<<vecIf[i]<< " IS MISSING AN END IF."<<"THE LINE WHICH CONTAINS THE ERROR IS: " <<printLine[vecIf[i]-1]<<endl << endl;

    }

}
else
{
    cout << "NO MISSING END IF IN THIS VHD FILE. " << endl<< endl;
}
int NumSemiC;
int NumSymbol;
int NumEndif;
bool noprob = true;

for(unsigned ii=0;ii<printLine.size();ii++)
{
    NumSymbol=0;
    NumSemiC=0;
    NumEndif=0;

    NumSymbol=printLine[ii].find("<=",0);
    NumSemiC=printLine[ii].find(";",0);
    NumEndif=printLine[ii].find("end",0);

    if((NumSymbol!=-1 && NumEndif==-1) || (NumSymbol==-1 && NumEndif!=-1))
    {
        if(NumSemiC==-1)
        {
        cout<<"LINE "<<ii<<" \""<<printLine[ii]<<"\" IS MISSING A SEMICOLON."<<endl<< endl;
        noprob = false;
        }
        else
        {
            //do nothing
        }
    }
    else
    {

    }
 }
 if(noprob == true)
    {
         cout << "THERE IS NO MISSING SEMICOLON IN THIS VHD FILE. " << endl<< endl;
    }
}

return 0;
    }

