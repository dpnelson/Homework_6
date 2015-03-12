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
    logfile.flush();
    exit(EXIT_FAILURE);
}

void DateSeparatorFail(ofstream &logfile)
{
    cout    << "Invalid Separator\n";
    logfile << "Invalid Separator\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void DateCharacterFail(ofstream &logfile)
{
    cout    << "Error: Non-number in Date\n";
    logfile << "Error: Non-number in Date\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void DifferentDateSeparators(ofstream &logfile)
{
    cout    << "Error: Inconsistent date separators\n";
    logfile << "Error: Inconsistent date separators\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void TimeSeparatorFail(ofstream &logfile)
{
    cout    << "Error: Invalid Time Separator\n";
    logfile << "Error: Invalid Time Separator\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void TimeSeparatorFail2(ofstream &logfile)
{
    cout    << "Error: No period between seconds and milliseconds\n";
    logfile << "Error: No period between seconds and milliseconds\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void TimeCharacterFail(ofstream &logfile)
{
    cout    << "Error: Non-number in Time\n";
    logfile << "Error: Non-number in Time\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void TimeZoneLengthFail(ofstream &logfile)
{
    cout    << "Error: Invalid Time Zone Length\n";
    logfile << "Error: Invalid Time Zone Length\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void TimeZoneCharacterFail(ofstream &logfile)
{
    cout    << "Error: Non-Letter in Time Zone\n";
    logfile << "Error: Non-Letter in Time Zone\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

enum months {
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

int main()
{
    string EventID, Date, Time, TimeZone;
    
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
    
    inputfile >> Time;
    
    for (int i = 0; i <= 11; i++)
    {
        if (i == 2 || i == 5)
        {
            string tempString = Time.substr(i,1);
            if (tempString.compare(":") != 0)
            {
                TimeSeparatorFail(logfile);
            }
        } else if (i == 8)
        {
            string tempString = Time.substr(i,1);
            if (tempString.compare(".") != 0)
            {
                TimeSeparatorFail2(logfile);
            }
        } else {
            if (!isdigit(Time[i]))
            {
                TimeCharacterFail(logfile);
            }
        }
    }
    
    inputfile >> TimeZone;
    
    if (TimeZone.length() != 3)
    {
        TimeZoneLengthFail(logfile);
    }
    for (int i = 0; i < 3; i++)
    {
        if (!isalpha(TimeZone[i]))
        {
            TimeZoneCharacterFail(logfile);
        }
    }
    
    string Name, Ename;
    int check = 1, check2 = 1;
    
    while(check == 1)
    {
        inputfile >> Name;
        if (check2 == 1)
        {
            Ename = Name;
            check2 = 0;
        } else
        {
            Ename = Ename + " " + Name;
        }
        if(inputfile.peek() == '\n') check = 0;
    }
    
    double Longitude, Latitude, Depth;
    string MagType;
    float  MagSize;
    
    inputfile >> Longitude;
    inputfile >> Latitude;
    inputfile >> Depth;
    inputfile >> MagType;
    inputfile >> MagSize;
    

    return 0;

}
