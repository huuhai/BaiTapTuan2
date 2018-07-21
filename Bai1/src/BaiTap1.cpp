#include <iostream>
#include <fstream>
#include <string.h>
#include <stack>
using namespace std;

#define MAX 200

void writeOutFile(int *countParentheses, int *countCloseParentheses, stack<char> Stack1, stack<char> Stack2);
void readInputFile();
void inputStack(char *str);

void readInputFile()
{
    char str[MAX];
    fstream readInputFile;

    readInputFile.open("BRACKET.INP", fstream::in);

    while(!(readInputFile.eof()))
    {
        readInputFile>> str;
    }
    int len = strlen(str);
    for(int i=0; i< len; i++)
    {
        cout<<str[i];
    }
    readInputFile.close();

    inputStack(str);
}

void inputStack(char *str)
{
    stack<char> Stack1;
    stack<char> Stack2;
    int countParentheses=0;
    int countCloseParentheses=0;

    int len = strlen(str);
    for(int i=0; i< len; i++)
    {
        if(str[i]=='(')
        {
            Stack1.push(str[i]);
            countParentheses++;
        }
        else if(str[i]==')')
        {
            Stack2.push(str[i]);
            countCloseParentheses++;
        }
    }
    writeOutFile(&countParentheses, &countCloseParentheses, Stack1, Stack2);
}

void writeOutFile(int *countParentheses, int *countCloseParentheses, stack<char> Stack1, stack<char> Stack2)
{
    fstream writeOutputFile;

    writeOutputFile.open("BRACKET.OUT", fstream::out);
    if(*countParentheses==*countCloseParentheses)
    {
        writeOutputFile<<*countCloseParentheses-*countParentheses<< endl;
    }
    else if(*countParentheses>*countCloseParentheses)
    {
        writeOutputFile<<*countParentheses-*countCloseParentheses<< endl;
        writeOutputFile<< Stack2.top();
    }
    else if(*countCloseParentheses>*countParentheses)
    {
        writeOutputFile<<*countCloseParentheses-*countParentheses<< endl;
        writeOutputFile<< Stack1.top();
    }
    cout<<endl<<"Luu file thanh cong !!!";
    writeOutputFile.close();
}

int main()
{
    readInputFile();
}

