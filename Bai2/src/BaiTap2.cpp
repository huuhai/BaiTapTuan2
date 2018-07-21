#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>
using namespace std;

void readFile();
void menu();
bool checkFile(fstream &file, char *fileName);
void select(fstream &file, char *fileName);
void Search(fstream &file, char *fileName, int *print);
void Replace(fstream &file, char *fileName, int *print);

void readFile()
{
    fstream file;
    fstream writeFile;
    string str;
    char fileName[20];
    while(true)
    {
        do
        {
            cout<<endl<< "Enter file: ";
            cin>> fileName;
            if(!checkFile(file, fileName))
            {
                cout<<endl<<endl<< "Invalid file !!!"<< endl;
            }
        }
        while(!file);
        writeFile.open("output.txt", fstream::out|fstream::app);
        writeFile<<"Input file: "<<fileName<<endl;
        writeFile.close();
        file.close();
        select(file,fileName);
    }
}

bool checkFile(fstream &file,char *fileName)
{
    file.open(fileName, fstream::in);
    if(!file)
    {
        return false;
    }
    else if(file)
    {
        return true;
    }
    return NULL;
}

void select(fstream &file, char *fileName)
{
    int choice=0;
    int print=0;
    do
    {
        if(print==0)
        {
            cout<< "Valid file, please choose file features: "<<endl;
        }
        else
        {
            cout<<endl<<endl<< "Choose the features: "<<endl;
        }
        print++;
        menu();
        cin>>choice;

        switch(choice)
        {
        case 1:
            system("cls");
            Search(file,fileName, &print);
            break;
        case 2:
            system("cls");
            Replace(file, fileName, &print);
            break;
        case 3:
            system("cls");
            cout<< "Exit !!!"<<endl;
            cout<<endl<< "Press any key to return input file..."<<endl;
            getch();
            system("cls");
            break;
        default:
            system("cls");
            cout<< "choose fail !!!"<<endl;
            break;
        }
        if(choice==3)
            break;
    }
    while(true);
}

void menu()
{
    cout<< "\t------------------------------"<<endl;
    cout<< "\t\t"<<"1. Search"<<endl;
    cout<< "\t\t"<<"2. Replace"<<endl;
    cout<< "\t\t"<<"3. Exit"<<endl;
    cout<< "\t------------------------------"<<endl;
}

void Search(fstream &file, char *fileName, int *print)
{
    string keyWord;
    fstream writeFile;
    string str;
    int toTal=0;
    int line=0;
    size_t position;
    writeFile.open("output.txt", fstream::out|fstream::app);

    cout<< "Enter keyword: ";
    cin>>keyWord;
    file.open(fileName,fstream::in);

    writeFile<<"Context "<<*print<<": search keyword"<<endl<<"\t"<<"Keyword: "<<keyWord<<endl;

    while (getline(file, str))
    {
        line++;
        position = str.find(keyWord);
        while (position != string::npos)
        {
            string next = str.substr(position + keyWord.length(), 1),
                   pre = str.substr(position - 1, 1);

            size_t check1 = next.find_first_of(' '),
                   check2 = next.find_first_of(','),
                   check3 = next.find_first_of('.'),
                   check4 = pre.find_first_of(' ');

            if ((check1 == 0 || check3 == 0 || check2 == 0) && check4 == 0)
            {
                cout << "\n\tLn " << line << ", Col " << position + 1;
                toTal++;
                writeFile<<"\n\tLn " << line << ", Col " << position + 1<<endl;
            }
            position = str.find(keyWord, ++position);
        }
    }
    cout<<endl<< "Total appeared time: "<<toTal<<endl;
    file.close();

    writeFile<<"Total position(s): "<<toTal<<endl<<endl;
    writeFile.close();
}

void Replace(fstream &file, char *fileName, int *print)
{
    string Replace;
    string str;
    string keyWord;
    int line=0;
    int toTal=0;
    size_t position;

    fstream WriteFile;
    WriteFile.open("output.txt", fstream::out|fstream::app);

    cout<< "Enter word(s): ";
    cin>>keyWord;
    cout<< "Enter new word(s): ";
    cin>>Replace;

    file.open(fileName, fstream::in);

    WriteFile<< "Context "<<*print<<": replace by new keyword"<<endl<<"\tKeyword: "<<keyWord<<endl<<"\tNew keyword: "<<Replace<<endl;

    while (getline(file, str))
    {
        line++;
        position = str.find(keyWord, 0);
        while (position != string::npos)
        {
            string next = str.substr(position + keyWord.length(), 1),
                   pre = str.substr(position - 1, 1);

            size_t check1 = next.find_first_of(' '),
                   check2 = next.find_first_of(','),
                   check3 = next.find_first_of('.'),
                   check4 = pre.find_first_of(' ');

            if ((check1 == 0 || check3 == 0 || check2 == 0) && check4 == 0)
            {
                cout << "\n\tLn " << line << ", Col " << position + 1;
                toTal++;
                WriteFile<<"\n\tLn " << line << ", Col " << position + 1<<endl;
            }
            position = str.find(keyWord, ++position);
        }
    }
    cout<<endl<< "Total appeared time "<<toTal<<endl;
    WriteFile<<"Total appeared time "<<toTal<<endl;
    while (getline(file, str))
    {
        while ((position = str.find(keyWord, position)) != string::npos)
        {
            str.replace(position, keyWord.length(), Replace);
            position += Replace.length();
        }
        cout<<str;
    }
    file<<str;
    cout<<endl<<"Replace "<<keyWord<<" by "<<Replace<<" Successfully"<<endl;
    file.close();
    WriteFile.close();
}

main()
{
    readFile();
    return 0;
}


