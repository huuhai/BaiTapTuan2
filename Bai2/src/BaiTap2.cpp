#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>
using namespace std;

void readFile();
bool checkFile(fstream &file, char *fileName);
void select(fstream &file, char *fileName);
void Search(fstream &file, char *fileName);
void Replace(fstream &file, char *fileName);

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
            cout<<endl<< "Nhap vao ten file: ";
            cin>> fileName;
            if(!checkFile(file, fileName))
            {
                cout<<endl<<endl<< "File khong ton tai !!!"<< endl;
            }
            else
            {
                while(getline(file, str))
                {
                    cout<< str;
                }
                cout<<endl<<endl<< "File ton tai !!!"<< endl;
                break;
            }
        }
        while(!file);
        writeFile.open("output.txt", fstream::out|fstream::in|fstream::app);
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
    int choice;
    while(true)
    {
        cout<< "\n\n\t\tChon chuc nang:"<<endl;
        cout<< "\t\t\t"<<"1. Search"<<endl;
        cout<< "\t\t\t"<<"2. Replace"<<endl;
        cout<< "\t\t\t"<<"3. Exit"<<endl;

        cin>>choice;

        switch(choice)
        {
        case 1:
            system("cls");
            Search(file,fileName);
            break;
        case 2:
            system("cls");
            Replace(file, fileName);
            break;
        case 3:
            system("cls");
            cout<< "Da thoat !!!"<<endl;
            cout<<endl<< "An mot phim bat ky de quay lai nhap FILE"<<endl;
            getch();
            system("cls");
            break;
        default:
            system("cls");
            cout<< "Khong co chuc nang nay !!!"<<endl;
            break;
        }
        if(choice==3)
        {
            break;
        }
    }
}

void Search(fstream &file, char *fileName)
{
    string keyWord;
    fstream writeFile;
    string str;
    int toTal=0;
    int line=0;
    size_t position;

    cout<< "Nhap vao tu khoa: ";
    cin>>keyWord;
    file.open(fileName,fstream::in);

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
            }
            position = str.find(keyWord, ++position);
        }
    }
    cout<<endl<< "Total "<< toTal;
    file.close();
    writeFile.open("output.txt", fstream::out|fstream::app);
    writeFile<<"Context 1: search keyword"<<endl<<"\t\t"<<"Keyword: "<<keyWord<<endl
             <<"Total position(s): "<<toTal<<endl<<"\t\tLn " << line << ", Col " << position + 1<<endl;
}


void Replace(fstream &file, char *fileName)
{
    string Replace;
    string str;
    string keyWord;
    int line=0;
    int toTal=0;
    size_t position;
    cout<< "Nhap vao tu khoa: ";
    cin>>keyWord;
    cout<< "Nhap vao tu thay the: ";
    cin>>Replace;
    file.open(fileName, fstream::in);
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
            }
            position = str.find(keyWord, ++position);
        }
    }
    cout<<endl<< "Total "<< toTal;
    while (!file.eof())
    {
        getline(file, str);
        while ((position = str.find(keyWord, position)) != string::npos)
        {
            str.replace(position, keyWord.length(), Replace);
            position += Replace.length();
        }
        cout<<str;
    }
    cout<<endl<<"Replace "<<keyWord<<" by "<<Replace<<" Successfully"<<endl;
    file.close();
}

main()
{
    readFile();
    return 0;
}


