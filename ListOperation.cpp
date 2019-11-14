#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "ArgumentManager.h"
#include "DynamicString.h"
#include "Book.h"
using namespace std;

#define totalBook 1000
#define totolCmd 100
#define maxID 99999
#define minID 10000

//sortby Params
#define BookID 1 //to sort by book_id
#define BookName 2 // to sort by book_name
#define AuthorName 3 //to sort by author_name

#define MaxPosWidth 4 //since 1000 is maxmimum records, position can be from 0-1000

void AppendBook(DynamicString);
void RunCommand(DynamicString);
int FindPosInLine(string str);
string GetValue(string, string);

Book lib;
const string constbookid = "book_id";
const string constbookname = "book_name";
const string constbookauthor = "book_author";
const string constaddcmd = "add";
const string constremovecmd = "remove";
const string constsortcmd = "sort";
const string constpos = "pos";
int Book::libSize = 0;

int main(int argc, char *argv[]) {
    // string a = "sort position sort";
    // cout<<a.find("ion");
    // cout<<string::npos;
    //cout<<GetValue("add pos:2 book_id:12456, book_name:Programming and Data Structures, book_author:xxx","book_author");
    if (argc < 2) {
        cout << "Invalid parameters" << endl;
        return -1;
    }

    int scount; //string counter

    ArgumentManager am(argc, argv);
    
    string infilename = am.get("input");// get the input filename
    string cmdfilename = am.get("command");// get the command filename
    string outfilename = am.get("output"); // get the output filename
    
    ifstream infile;

    infile.open(infilename);
    string line = "";

    // count no of lines in file
    while (getline(infile, line)){
        if (line != "") scount++;
    }

    if(scount > totalBook){
        cout<<"Total Number of Lines in Input File exceeded the limit!";
        return -1;
    }

    infile.clear();
    infile.seekg(0, ios::beg);

    DynamicString inpbooklist(scount);
    scount = 0;

    while (getline(infile, line))
    {
        if (line != ""){
            inpbooklist.AddLine(line);
        }
    }

    infile.close();

    infile.open(cmdfilename);
    line = "";

    // count no of lines in file
    while (getline(infile, line)){
        if (line != "") scount++;
    }

    if(scount > totalBook){
        cout<<"Total Number of command exceeded the limit!";
        return -1;
    }

    infile.clear();
    infile.seekg(0, ios::beg);
    
    DynamicString cmd(scount);
    scount = 0;

    while (getline(infile, line))
    {
        if (line != ""){
            cmd.AddLine(line);
        }
    }

    AppendBook(inpbooklist);
    
    RunCommand(cmd);

    lib.PrintBook(outfilename);

    return 0;
}

void AppendBook(DynamicString ds){
    for(int i= 0; i< ds.getStringSize(); i++){
        string line = ds.GetLine(i);
        int id = stoi(GetValue(line,constbookid));
        if(id < minID || id > maxID){
            cout<<endl<<"Invalid ID in one or more Books!"<<endl;
            exit(1);
        }
        string name = GetValue(line,constbookname);
        string author = GetValue(line,constbookauthor);
        bool search = lib.Search(id);

        if (!search){
            lib.Insert(id, name, author);
        }
    }
}

void RunCommand(DynamicString ds){
    for(int i= 0; i< ds.getStringSize(); i++ ){
        string line = ds.GetLine(i);

        if (line.find(constsortcmd) != string::npos) {
            if(line.find(constbookid) != string::npos){
                lib.Sort(BookID);
            }else if (line.find(constbookname) != string::npos){
                lib.Sort(BookName);
            }else if (line.find(constbookauthor) != string::npos){
                lib.Sort(AuthorName);
            }
        }

        else if(line.find(constaddcmd) != string::npos) {

            int index = line.find(constbookid);
            int pos = FindPosInLine(line);

            line = line.substr(index, line.length());

            int id = stoi(GetValue(line,constbookid));
            if(id < minID || id > maxID){
                cout<<"Invalid ID in one or more Books in Command File!"<<endl;
               exit(1);
            }

            string name = GetValue(line,constbookname);
            string author = GetValue(line,constbookauthor);
            bool search = lib.Search(id);
            
            if (!search){
                lib.Add(pos, id, name, author);
            }
        }
        else if(line.find(constremovecmd) != string::npos) {

            if(line.find(constpos) != string::npos){
                line = line.substr(constremovecmd.length() + constpos.length() + 2, line.length());
                lib.Delete(atoi(line.c_str()), -1, "", "");
            }else if(line.find(constbookid) != string::npos){
                line = line.substr(constremovecmd.length() + constbookid.length() + 2, line.length());
                lib.Delete(-1,atoi(line.c_str()), "", "");
            }else if (line.find(constbookname) != string::npos){
                line = line.substr(constremovecmd.length() + constbookname.length() + 2, line.length());
                lib.Delete(-1, -1, line, "");
            }else if (line.find(constbookauthor) != string::npos){
                line = line.substr(constremovecmd.length() + constbookauthor.length() + 2, line.length());
                lib.Delete(-1, -1, "", line);
            }
        }
    }
}

int FindPosInLine(string str){
    int idxPOS = str.find(constpos);
    int idxBookID = str.find(constbookid);
    string temp = str.substr(idxPOS+4, MaxPosWidth);
    int i = stoi(temp);
    return i;
}


string GetValue(string src, string key){
    DynamicString myDS(1);
    istringstream iss(src);
    string token;
    
    // get each attribute book_id, name and author
    while(getline(iss, token, ',')) {
        myDS.AddLine(token);
    }
    
    string id = myDS.GetLine(0);
    string name = myDS.GetLine(1);
    string author = myDS.GetLine(2);
    myDS.removeAll();
    if (key == constbookid){
        return id.substr(id.find(constbookid) + constbookid.length() + 1, id.length()).c_str();
    }
    else if(key == constbookname){
        return name.substr(name.find(constbookname) + constbookname.length() + 1, name.length()).c_str();
    }
    else if (key == constbookauthor){
        return author.substr(author.find(constbookauthor) + constbookauthor.length() + 1, author.length()).c_str();
    }
    return "";
}