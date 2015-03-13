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

void MonthRangeError(ofstream &logfile)
{
    cout    << "Error: Month Out of Range\n";
    logfile << "Error: Month out of Range\n";
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

void Month_to_Num(string M, int &monthnumm)
{
    if (M == "01") monthnumm = 1;
    if (M == "02") monthnumm = 2;
    if (M == "03") monthnumm = 3;
    if (M == "04") monthnumm = 4;
    if (M == "05") monthnumm = 5;
    if (M == "06") monthnumm = 6;
    if (M == "07") monthnumm = 7;
    if (M == "08") monthnumm = 8;
    if (M == "09") monthnumm = 9;
    if (M == "10") monthnumm = 10;
    if (M == "11") monthnumm = 11;
    if (M == "12") monthnumm = 12;
}

void monthtostring(int M, string &MM)
{
    if (M == 1) MM  = "January";
    if (M == 2) MM  = "February";
    if (M == 3) MM  = "March";
    if (M == 4) MM  = "April";
    if (M == 5) MM  = "May";
    if (M == 6) MM  = "June";
    if (M == 7) MM  = "July";
    if (M == 8) MM  = "August";
    if (M == 9) MM  = "September";
    if (M == 10) MM = "October";
    if (M == 11) MM = "November";
    if (M == 12) MM = "December";

}

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

struct inputs {
    string inp[300][5];
};

enum NetworkCode {
    CE,
    CI,
    FA,
    NP,
    WR
};

enum BandTypes {
    LONGPERIOD,
    SHORTPERIOD,
    BROADBAND
};

enum InstrumentTypes {
    HIGHGAIN,
    LOWGAIN,
    ACCELEROMETER
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

void changetoupper(string &temp2)
{
    for (int i = 0; i <= temp2.size(); i++)
    {
        temp2[i] = toupper(temp2[i]);
    }
}

void get_eqMag_Type(ifstream &IF, earthquake &eq, string temp)
{
    IF >> temp;
    changetoupper(temp);
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

bool checkNC(inputs &in, int k)
{
    if(in.inp[k][0] == "CE")
    {
        in.inp[k][0] = CE;
        return true;
    } else if (in.inp[k][0] == "CI")
    {
        in.inp[k][0] = CI;
        return true;
    } else if (in.inp[k][0] == "FA")
    {
        in.inp[k][0] = FA;
        return true;
    } else if (in.inp[k][0] == "NP")
    {
        in.inp[k][0] = NP;
        return true;
    } else if (in.inp[k][0] == "WR")
    {
        in.inp[k][0] = WR;
        return true;
    } else {
        return false;
    }
};

void BadEntryNC(ofstream &LF, int z, int &change)
{
    if (change == 0) change++;
    z++;
    cout << "Entry # " << right << setw(3) << z << " ignored. Invalid network code.";
    LF   << "Entry # " << right << setw(3) << z << " ignored. Invalid network code.";
}

bool checkSC(inputs &in, int k)
{
    if(in.inp[k][1].length() != 3 && in.inp[k][1].length() != 5)
    {
        return false;
    } else
    {
        if (in.inp[k][1].length() == 5)
        {
            int num = 4;
            for (int w = 0; w <= num; w++)
            {
                if(!isdigit(in.inp[k][1][w]))
                {
                    return false;
                } 
            }
        } else
        {
            int num = 2;
            for (int w = 0; w <= num; w++)
            {
                if(!isalpha(in.inp[k][1][w]))
                {
                    return false;
                }
                
                string temp = in.inp[k][1];
                string temp1 = temp;
                changetoupper(temp);
                
                if (temp != temp1)
                {
                    return false;
                }
                
            }
        }
        return true;
    }
};

void BadEntrySC(ofstream &LF, int z, int &change)
{
    z++;
    if (change == 0)
    {
        change++;
        cout << "Entry # " << right << setw(3) << z << " ignored.";
        LF   << "Entry # " << right << setw(3) << z << " ignored.";
    }
    cout << " Invalid station code.";
    LF   << " Invalid station code.";
}

bool checkBT(inputs &in, int k)
{
    if(in.inp[k][0] == "CE")
    {
        in.inp[k][0] = CE;
        return true;
    } else if (in.inp[k][0] == "CI")
    {
        in.inp[k][0] = CI;
        return true;
    } else if (in.inp[k][0] == "FA")
    {
        in.inp[k][0] = FA;
        return true;
    } else if (in.inp[k][0] == "NP")
    {
        in.inp[k][0] = NP;
        return true;
    } else if (in.inp[k][0] == "WR")
    {
        in.inp[k][0] = WR;
        return true;
    } else {
        return false;
    }
};

void BadEntryBT(ofstream &LF, int z, int &change)
{
    if (change == 0) change++;
    z++;
    cout << "Entry # " << right << setw(3) << z << " ignored. Invalid band type.";
    LF   << "Entry # " << right << setw(3) << z << " ignored. Invalid band type.";
}

void get_eqMag(ifstream &IF, earthquake &eq)
{
    IF >> eq.magnitude;
}

void ZeroEntries(ofstream &LF2)
{
    cout << "There are no entries to read\n";
    LF2  << "There are no entries to read\n";
//    LF2.flush();
//    exit(EXIT_FAILURE);
}

void Read_Entries(ifstream &IF, ofstream &LF, inputs &in, int &k)
{
    while (IF >> in.inp[k][0])
    {
        IF >> in.inp[k][1];
        IF >> in.inp[k][2];
        IF >> in.inp[k][3];
        IF >> in.inp[k][4];
        k++;
    }
    if (k == 0)
    {
        ZeroEntries(LF);
    }
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
    
    string M = eq.date.substr(0,2);
    
    months month;
    int monthnum;
    Month_to_Num(M, monthnum);
    
    if (monthnum < 0 || monthnum > 12)
    {
        MonthRangeError(logfile);
    }
    
    month = (months)monthnum;
    string monthstring;
    monthtostring(month, monthstring);
    
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

    inputs in;
    int j = 0;
    Read_Entries(inputfile, logfile, in, j);
    j--;
    
    for (int y = 0; y <= j; y++)
    {
        int changer = 0;
        if(checkNC(in, y) == false)
        {
            BadEntryNC(logfile, y, changer);
        } else {
            
        }
        
        if(checkSC(in, y) == false)
        {
            BadEntrySC(logfile, y, changer);
        } else {
            
        }
        
        if(checkBT(in, y) == false)
        {
            BadEntryBT(logfile, y, changer);
        } else {
            
        }
   
        if (changer !=0)
        {
            cout << "\n";
        }
    }
    
    
    
    
    
    
    int k = 1;
    k++;
    

    return 0;

}
