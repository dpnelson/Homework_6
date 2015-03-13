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
#include <math.h>

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

void MagnitudeTypeFail(ofstream &logfile)
{
    cout    << "Error: Magnitude type not acceptable\n";
    logfile << "Error: Magnitude type not acceptable\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void MagSizeFail(ofstream &logfile)
{
    cout    << "Error: Negative Magnitude\n";
    logfile << "Error: Negative Magnitude\n";
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

enum TypeofMag {
    ML,
    MS,
    MB,
    MW
};

struct earthquake {
    string id;
    string date;
    string time;
    string timezone;
    string earthquake_name;
    double longitude;
    double latitude;
    double depth;
    string magnitude_type;
    float magnitude;
};

void get_eqID(ifstream &IF, earthquake &eq)
{
    IF >> eq.id;
}

void get_eqDate(ifstream &IF, earthquake &eq)
{
    IF >> eq.date;
}

void get_eqTime(ifstream &IF, earthquake &eq)
{
    IF >> eq.time;
}

void get_eqTimeZone(ifstream &IF, earthquake &eq)
{
    IF >> eq.timezone;
}

void get_eqName(ifstream &IF, earthquake &eq, string Name, string Ename, int check, int check2)
{
    while(check == 1)
    {
        IF >> Name;
        if (check2 == 1)
        {
            Ename = Name;
            check2 = 0;
        } else
        {
            Ename = Ename + " " + Name;
        }
        if(IF.peek() == '\n') check = 0;
    }
    
    eq.earthquake_name = Ename;
}

void get_eqLongitude(ifstream &IF, earthquake &eq)
{
    IF >> eq.longitude;
}

void get_eqLatitude(ifstream &IF, earthquake &eq)
{
    IF >> eq.latitude;
}

void get_eqDepth(ifstream &IF, earthquake &eq)
{
    IF >> eq.depth;
}

void get_eqMag_Type(ifstream &IF, earthquake &eq, string temp)
{
    IF >> temp;
    for (int i = 0; i <= temp.size(); i++)
    {
        temp[i] = toupper(temp[i]);
    }

    eq.magnitude_type = temp;
}

bool set_MagType(string mag, earthquake &eq)
{
    if(mag == "ML")
    {
        eq.magnitude = ML;
        return true;
    } else if (mag == "MS")
    {
        eq.magnitude = MS;
        return true;
    } else if (mag == "MB")
    {
        eq.magnitude = MB;
        return true;
    } else if (mag == "MW")
    {
        eq.magnitude = MW;
        return true;
    } else
    {
        return false;
    }
};

void get_eqMag(ifstream &IF, earthquake &eq)
{
    IF >> eq.magnitude;
}

int main()
{
    
    string   inputfilename, outputfilename, logfilename;
    ifstream inputfile;
    ofstream logfile, outputfile;
    
    cout << "Enter inputfile name: ";
    cin  >> inputfilename;
    open_input(inputfile, inputfilename);
    open_log_output(logfile, outputfile, "darin.log", "darin.out");
    
    earthquake eq;
    
    get_eqID(inputfile, eq);
    get_eqDate(inputfile, eq);
    
    if (eq.date.length() != 10)
    {
        DateLengthFail(logfile);
    }
    
    for (int i = 0; i <= 9; i++)
    {
        if (i == 2 || i == 5)
        {
            string tempString = eq.date.substr(i,1);
            if (tempString.compare("/") != 0 && tempString.compare("-") != 0)
            {
                DateSeparatorFail(logfile);
            }
        } else if ((!isdigit(eq.date[i])))
        {
            DateCharacterFail(logfile);
        }
    }
    if (eq.date[2] != eq.date[5])
    {
        DifferentDateSeparators(logfile);
    }
    
    get_eqTime(inputfile, eq);
    
    for (int i = 0; i <= 11; i++)
    {
        if (i == 2 || i == 5)
        {
            string tempString = eq.time.substr(i,1);
            if (tempString.compare(":") != 0)
            {
                TimeSeparatorFail(logfile);
            }
        } else if (i == 8)
        {
            string tempString = eq.time.substr(i,1);
            if (tempString.compare(".") != 0)
            {
                TimeSeparatorFail2(logfile);
            }
        } else {
            if (!isdigit(eq.time[i]))
            {
                TimeCharacterFail(logfile);
            }
        }
    }
    
    get_eqTimeZone(inputfile, eq);
    
    if (eq.timezone.length() != 3)
    {
        TimeZoneLengthFail(logfile);
    }
    for (int i = 0; i < 3; i++)
    {
        if (!isalpha(eq.timezone[i]))
        {
            TimeZoneCharacterFail(logfile);
        }
    }
    
    string Name, Ename;
    int check = 1, check2 = 1;
    
    get_eqName(inputfile, eq, Name, Ename, check, check2);
    
    string Longitude, Latitude, Depth;
    
    get_eqLongitude(inputfile, eq);
    get_eqLatitude(inputfile, eq);
    get_eqDepth(inputfile, eq);
    
    string temp;
    get_eqMag_Type(inputfile, eq, temp);
    
    if(set_MagType(eq.magnitude_type, eq) == false)
    {
        MagnitudeTypeFail(logfile);
    }
    
    get_eqMag(inputfile, eq);
    
    if (eq.magnitude < 0)
    {
        MagSizeFail(logfile);
    }

    
    int j = 1;
    j++;
    

    return 0;

}
