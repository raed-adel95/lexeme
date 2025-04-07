#include <iostream>
#include <cstring>

using namespace std;

char nextChar;
int charClass;
char lexeme[100];
int lexLen = 0;
int nextToken;
char inputBuffer[100];
int inputPos = 0;

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define EOF_TOKEN -1

#define INT_LIT 10
#define IDENT 11
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

void addChar() 
{
    if (lexLen < 99) 
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
}

void getChar() 
{
    if (inputBuffer[inputPos] != '\0') 
    {
        nextChar = inputBuffer[inputPos++];
        if ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z'))
            charClass = LETTER;
        else if (nextChar >= '0' && nextChar <= '9')
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } 
    else 
    {
        charClass = EOF_TOKEN;
    }
}

void getNonBlank() 
{
    while (nextChar == ' ' || nextChar == '\t' || nextChar == '\n') getChar();
}

int lookup(char ch) 
{
    switch (ch) {
        case '(': nextToken = LEFT_PAREN; break;
        case ')': nextToken = RIGHT_PAREN; break;
        case '+': nextToken = ADD_OP; break;
        case '-': nextToken = SUB_OP; break;
        case '*': nextToken = MULT_OP; break;
        case '/': nextToken = DIV_OP; break;
        default: nextToken = EOF_TOKEN; break;
    }
    addChar();
    return nextToken;
}

int lex() 
{
    lexLen = 0;
    getNonBlank();
    if (charClass == LETTER) 
    {
        addChar(); getChar();
        while (charClass == LETTER || charClass == DIGIT) 
        {
            addChar(); getChar();
        }
        nextToken = IDENT;
    } 
    else if (charClass == DIGIT)
    {
        addChar(); getChar();
        while (charClass == DIGIT) 
        {
            addChar(); getChar();
        }
        nextToken = INT_LIT;
    } 
    else if (charClass == UNKNOWN) 
    {
        lookup(nextChar);
        getChar();
    } 
    else 
    {
        nextToken = EOF_TOKEN;
        strcpy(lexeme, "EOF");
    }
    cout << "Next token: " << nextToken << " Lexeme: " << lexeme << endl;
    return nextToken;
}

int main() 
{
    cout << "Enter an expression: ";
    cin.getline(inputBuffer, 100);
    inputPos = 0;
    getChar();
    while (nextToken != EOF_TOKEN)
    {
        lex();
    }
    return 0;
}