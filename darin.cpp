//
//  Darin Nelson
//  Homework #6
//  3/26/15
//  CIVL 7903
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

using namespace std;

void open_input(ifstream &IF, string IF2)
{
    IF.open(IF2.c_str());
    if ( !IF.is_open() )
    {
        cout << "Cannot open input file: "
             << IF2
             << endl;
        exit(EXIT_FAILURE);
    }
}

void open_log_output(ofstream &LF, ofstream &OF, string LFname, string OFname)
{
    LF.open(LFname.c_str());
    OF.open(OFname.c_str());
}

void DateLengthFail(ofstream &logfile)
{
    cout    << "Invalid Date Length\n";
    logfile << "Invalid Data Length\n";
    exit(EXIT_FAILURE);
}

void DateSeparatorFail(ofstream &logfile)
{
    cout    << "Invalid Separator\n";
    logfile << "Invalid Separator\n";
    exit(EXIT_FAILURE);
}

void DateCharacterFail(ofstream &logfile)
{
    cout    << "Error: Non-number in Date\n";
    logfile << "Error: Non-number in Date\n";
    exit(EXIT_FAILURE);
}

void DifferentDateSeparators(ofstream &logfile)
{
    cout    << "Error: Inconsistent date separators\n";
    logfile << "Error: Inconsistent date separators\n";
    exit(EXIT_FAILURE);
}

int main()
{
    string EventID, Date;
    
    string   inputfilename, outputfilename, logfilename;
    ifstream inputfile;
    ofstream logfile, outputfile;
    
    cout << "Enter inputfile name: ";
    cin  >> inputfilename;
    open_input(inputfile, inputfilename);
    open_log_output(logfile, outputfile, "darin.log", "darin.out");
    
    inputfile >> EventID;
    inputfile >> Date;
    
    if (Date.length() != 10)
    {
        DateLengthFail(logfile);
    }
    
    for (int i = 0; i <= 9; i++)
    {
        if (i == 2 || i == 5)
        {
            string tempString = Date.substr(i,1);
            if (tempString.compare("/") != 0 && tempString.compare("-") != 0)
            {
                DateSeparatorFail(logfile);
            }
        } else if ((!isdigit(Date[i])))
        {
            DateCharacterFail(logfile);
        }
    }
    if (Date[2] != Date[5])
    {
        DifferentDateSeparators(logfile);
    }

    return 0;

}
