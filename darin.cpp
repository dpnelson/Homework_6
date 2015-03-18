//
//  Darin Nelson
//  Homework #6
//  3/26/15
//  CIVL 7903
//  Github URL: https://github.com/dpnelson/Homework_6
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

void open_input(ifstream &IF, string IF2)      // Opening input file
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

void open_outputfiles(ofstream &file, string file2, string file3)      // Opens log and output files
{
    file.open(file3.c_str());
    if ( !file.is_open() )
    {
        cout << "Cannot open " << file2 << "file: " << file3;
        file.flush();
        exit(EXIT_FAILURE);
    }
}

void Fail(ofstream &logfile, string failtype)     // Handles any error in the header
{
    cout    << "Error: " << failtype << "\n";
    logfile << "Error: " << failtype << "\n";
    logfile.flush();
    exit(EXIT_FAILURE);
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
    TypeofMag magnitude_type;
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

void GetDateSubStr(earthquake eq, int ii, string &tempS)     // Used to ensure only numbers are used in the data
{
    tempS = eq.date.substr(ii,1);
}

bool CheckDateLength(earthquake eq)   
{
    if (eq.date.length() != 10) return false;
    return true;
}

bool CheckMonthRange(int mon)
{
    if (mon < 0 || mon > 12) return false;
    return true;
}

bool CheckDayRange(int day)
{
    if (day < 0 || day > 31) return false;
    return true;
}

bool CheckYearRange(int year)        // This can obviously be changed, but I created this limit
{                                    // because it was the last full year
    if (year > 2014) return false;
    return true;
}

bool MonthDayComboCheck(int day, int month)    // Ensure the day of month/month of year combo is valid
{
    switch (month)
    {
        case 2:
            if (day > 28)
            {
               return false;
                break;
            }
        case 4: case 6: case 9: case 11:
            if (day == 31)
            {
                return false;
                break;
            }
        default:
            return true;
    }
}


bool CheckDateSeperators(string tempS)     // Checks that date seperators are individually valid
{
    if (tempS.compare("/") != 0 && tempS.compare("-") != 0) return false;
    return true;
}

bool CheckDateValidity(earthquake eq, int place)    // Checks that only numbers are used in the date
{
    if (!isdigit(eq.date[place])) return false;
    return true;
}

bool CheckDateSeperators2(earthquake eq, int aa, int bb)     // Checks that date seperators are the same
{
    if (eq.date[aa] != eq.date[bb]) return false;
    return true;
}

void get_eqTime(ifstream &IF, earthquake &eq)
{
    IF >> eq.time;
}

void GetTimeSubStr(earthquake eq, int ii, string &tempS)     // Used to ensure only numbers are used in the data
{
    tempS = eq.time.substr(ii,1);
}

bool CheckTimeLength(earthquake eq)
{
    if (eq.time.length() != 12) return false;
    return true;
}

bool CheckHourRange(int h)
{
    if (h > 23) return false;
    return true;
}

bool CheckMinuteRange(int m)
{
    if (m > 59) return false;
    return true;
}

bool CheckSecondRange(int s)
{
    if (s > 59) return false;
    return true;
}

bool CheckTimeSeperators(string tempS, string VarExp)     // Checks that time seperators are individually valid
{
    if (tempS.compare(VarExp) != 0) return false;
    return true;
}

bool CheckTimeValidity(earthquake eq, int place)     // Checks that only numbers are used in the time
{
    if (!isdigit(eq.time[place])) return false;
    return true;
}

void get_eqTimeZone(ifstream &IF, earthquake &eq)
{
    IF >> eq.timezone;
}

bool CheckTimeZoneLength(earthquake eq)
{
    if (eq.timezone.length() != 3) return false;
    return true;
}

bool CheckTimeZoneEntries(earthquake eq)     // Checks that only letters are used in the time zone
{
    for (int i = 0; i < 3; i++)
    {
        if(!isalpha(eq.timezone[i])) return false;
    }
    return true;
}

void set_eqName(ifstream &IF, earthquake &eq, string Name, string Ename, int check, int check2)
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

double set_eqLongitude(ifstream &IF, earthquake &eq)     // Returns value to compare valid longitude range
{
    IF >> eq.longitude;
    return eq.longitude;
}

double set_eqLatitude(ifstream &IF, earthquake &eq)
{
    IF >> eq.latitude;
    return eq.latitude;
}

double set_eqDepth(ifstream &IF, earthquake &eq)
{
    IF >> eq.depth;
    return eq.depth;
}

bool CheckLongRange(double Long)
{
    if(Long < -180 || Long > 180) return false;
    return true;
}

bool CheckLatRange(double Lat)
{
    if(Lat < -180 || Lat > 180) return false;
    return true;
}

bool CheckDepth(double d)
{
    if(d < 0) return false;
    return true;
}

void changetoupper(string &temp2)
{
    for (int i = 0; i <= temp2.size(); i++)
    {
        temp2[i] = toupper(temp2[i]);
    }
}

bool Check_MagTypeLength(string MT)
{
    if (MT.length() != 2) return false;
    return true;
}

bool set_MagType(earthquake &eq, string mag)     // checks for valid magnitude type
{
    changetoupper(mag);
    if(mag == "ML")
    {
        eq.magnitude_type = ML;
        return true;
    } else if (mag == "MS")
    {
        eq.magnitude_type = MS;
        return true;
    } else if (mag == "MB")
    {
        eq.magnitude_type = MB;
        return true;
    } else if (mag == "MW")
    {
        eq.magnitude_type = MW;
        return true;
    } else
    {
        return false;
    }
}

string getMagType(earthquake eq)                // gets abbreviation of the earthquake magnitude type to output
{
    if (eq.magnitude_type == ML) return "ML";
    if (eq.magnitude_type == MS) return "MS";
    if (eq.magnitude_type == MB) return "MB";
    if (eq.magnitude_type == MW) return "MW";
    exit(EXIT_FAILURE);
}

void set_Mag(ifstream &IF, earthquake &eq)
{
    IF >> eq.magnitude;
}

bool Check_Mag(earthquake &eq)
{
    if (eq.magnitude < 0) return false;
    return true;
};

void MDY(earthquake eq, string &MM, string &DD, string &YY)     // Acquires month, day, and year from earthquake date
{
    MM = eq.date.substr(0,2);
    DD = eq.date.substr(3,2);
    YY = eq.date.substr(6,4);
}

void HMS(earthquake eq, string &H, string &M, string &S)     // Acquires hour, minute, and second from earthquake time
{
    H = eq.time.substr(0,2);
    M = eq.time.substr(3,2);
    S = eq.time.substr(6,2);
}

int MonthtoInteger(string MM)
{
    if (MM == "01") return 1;
    if (MM == "02") return 2;
    if (MM == "03") return 3;
    if (MM == "04") return 4;
    if (MM == "05") return 5;
    if (MM == "06") return 6;
    if (MM == "07") return 7;
    if (MM == "08") return 8;
    if (MM == "09") return 9;
    if (MM == "10") return 10;
    if (MM == "11") return 11;
    if (MM == "12") return 12;
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

string monthtostring(months M)
{
    if (M == January  )  return  "January";
    if (M == February )  return  "February";
    if (M == March    )  return  "March";
    if (M == April    )  return  "April";
    if (M == May      )  return  "May";
    if (M == June     )  return  "June";
    if (M == July     )  return  "July";
    if (M == August   )  return  "August";
    if (M == September)  return  "September";
    if (M == October  )  return  "October";
    if (M == November )  return  "November";
    if (M == December )  return  "December";
    exit(EXIT_FAILURE);
}

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

struct entries {
    NetworkCode NC;
    string SC;
    BandTypes BT;
    InstrumentTypes IT;
    string OR;
} ENTS[300];

void BadEntry(ofstream &LF, int z, int &change, string errortype)    // Prints error in entries to log file and terminal
{
    if (change == 0)
    {
        change++;
        cout << "Entry # " << right << setw(3) << z << " ignored.";
        LF   << "Entry # " << right << setw(3) << z << " ignored.";
    }
    cout << " Invalid " << errortype;
    LF   << " Invalid " << errortype;
}

bool CheckNC(struct entries &in, int k, string check)
{
    if(check == "CE")
    {
        return true;
    } else if (check == "CI")
    {
        return true;
    } else if (check == "FA")
    {
        return true;
    } else if (check == "NP")
    {
        return true;
    } else if (check == "WR")
    {
        return true;
    } else
    {
        return false;
    }
}

void SetNC(struct entries &in, int k, string check)
{
    if(check == "CE")
    {
        ENTS[k].NC = CE;
    } else if (check == "CI")
    {
        ENTS[k].NC = CE;
    } else if (check == "FA")
    {
        ENTS[k].NC = CE;
    } else if (check == "NP")
    {
        ENTS[k].NC = CE;
    } else if (check == "WR")
    {
        ENTS[k].NC = CE;
    }
}

bool CheckSC(struct entries &in, int k, string StatCode)
{
    int check = 0;
    if(StatCode.length() != 3 && StatCode.length() != 5)    // Ensures Station code is either 3 or 5 characters long
    {
        check = 1;
    } else
    {
        if (StatCode.length() == 5)     // Ensures code is all numbers if 5 characters long
        {
            int num = 4;
            for (int w = 0; w <= num; w++)
            {
                if(!isdigit(StatCode[w]))
                {
                    check = 1;
                }
            }
        } else            //// Ensures code is all letters if 3 characters long
        {
            int num = 2;
            for (int w = 0; w <= num; w++)
            {
                if(!isalpha(StatCode[w]))
                {
                    check = 1;
                }
                
                string temp = StatCode;
                string temp1 = temp;
                changetoupper(temp);
                
                if (temp != temp1)
                {
                    check = 1;
                }
            }
        }
    }
    if (check == 1)
    {
        return false;
    } else
    {
        return true;
    }
}

void SetSC(struct entries &in, int k, string check)
{
    ENTS[k].SC = check;
}

bool CheckBT(entries &in, int k, string TB)
{
    if(TB == "LONGPERIOD")
    {
        return true;
    } else if (TB == "SHORTPERIOD")
    {
        return true;
    } else if (TB == "BROADBAND")
    {
        return true;
    } else
    {
        return false;
    }
}

void SetBT(entries &in, int k, string TB)
{
    if(TB == "LONGPERIOD")
    {
        ENTS[k].BT = LONGPERIOD;
    } else if (TB == "SHORTPERIOD")
    {
        ENTS[k].BT = SHORTPERIOD;
    } else if (TB == "BROADBAND")
    {
        ENTS[k].BT = BROADBAND;
    }
}

bool CheckIT(struct entries &in, int k, string INST)
{
    if(INST == "HIGHGAIN")
    {
        return true;
    } else if (INST == "LOWGAIN")
    {
        return true;
    } else if (INST == "ACCELEROMETER")
    {
        return true;
    } else
    {
        return false;
    }
}

void SetIT(struct entries &in, int k, string INST)
{
    if(INST == "HIGHGAIN")
    {
        ENTS[k].IT = HIGHGAIN;
    } else if (INST == "LOWGAIN")
    {
        ENTS[k].IT = LOWGAIN;
    } else if (INST == "ACCELEROMETER")
    {
        ENTS[k].IT = ACCELEROMETER;
    }
}

bool CheckOR(struct entries &in, int k, string ORE)
{
    int check = 0;
    if(ORE.length() < 1 || ORE.length() > 3)    // Ensures orientation  is between 1 and 3 characters long
    {
        check = 1;
    }
    int alphacount = 0, numbercount = 0;
    for (int g = 1; g <= ORE.length(); g++)
    {
        if (isalpha(ORE[g-1]))
        {
            alphacount++;
        } else if (isdigit(ORE[g-1]))
        {
            numbercount++;
        } else
        {
            check = 1;
        }
    }
    
    if (alphacount != ORE.length() && numbercount != ORE.length())
    {
        check = 1;
    }
    
    if (alphacount != 0)    // Ensures Orientation is all letters
    {
        changetoupper(ORE);
        for (int c = 1; c <= ORE.length(); c++)
        {
            string tempString = ORE.substr(c-1,1);
            if (tempString.compare("N") && tempString.compare("E") && tempString.compare("Z"))
            {
                check = 1;
            }
        }
    }
    
    if (numbercount != 0)    // Ensures Orientation is all numbers
    {
        for (int c = 1; c <= ORE.length(); c++)
        {
            string tempString = ORE.substr(c-1,1);
            if (tempString.compare("1") && tempString.compare("2") && tempString.compare("3"))
            {
                check = 1;
            }
        }
    } 
    if (check == 1)
    {
        return false;
    } else
    {
        return true;
    }
}

void SetOR(struct entries &in, int k, string check)
{
    ENTS[k].OR = check;
}

void Remove_Non_Letters(string &BandInst)    // Removes dashs from Instrument type and Band type 
{
    string Altered;
    for (int i = 0; i < BandInst.length(); i++)
    {
        if (isalpha(BandInst[i]))
        {
            Altered += BandInst[i];
        }
    }
    BandInst = Altered;
    changetoupper(BandInst);
}

string getNC(struct entries &in, int k)
{
    if (ENTS[k].NC == CE )  return  "CE";
    if (ENTS[k].NC == CI )  return  "CI";
    if (ENTS[k].NC == FA )  return  "FA";
    if (ENTS[k].NC == NP )  return  "NP";
    if (ENTS[k].NC == WR )  return  "WR";
    exit(EXIT_FAILURE);
}

string getBT(earthquake eq, entries &in, int y)
{
    if (ENTS[y].BT == LONGPERIOD)  return "L";
    if (ENTS[y].BT == SHORTPERIOD) return "B";
    if (ENTS[y].BT == BROADBAND)   return "H";
    exit(EXIT_FAILURE);
}

string getIT(earthquake eq, entries &in, int y)
{
    if (ENTS[y].IT == HIGHGAIN)       return "H";
    if (ENTS[y].IT == LOWGAIN)        return "L";
    if (ENTS[y].IT == ACCELEROMETER)  return "N";
    exit(EXIT_FAILURE);
}

string getOR(entries in, int k, int b)
{
    string end = ENTS[k].OR.substr(b,1);
    return end;
}

string getSN(entries &in, int y)
{
    string last = ENTS[y].SC;
    return last;
}

int NumSigs(entries &in, int k)
{
    int i = 0;
    while (isalpha(ENTS[k].OR[i]) || isdigit(ENTS[k].OR[i]))
    {
        i++;
    }
    return i;
}

bool NumValidEntries(ofstream &LF, int Valentries)
{
    if(Valentries > 300) return false;
    return true;
}

void HeaderOutput(ofstream &OF, string DD, string MM, string YY, earthquake eq)
{
    string StrMagType = getMagType(eq);
    OF <<  "# " << DD << " " << MM << " " << YY << " " << eq.time << " " << eq.timezone << " ";
    OF << StrMagType << " " << eq.magnitude << " " << eq.earthquake_name << " ";
    OF << "[" << eq.id << "] " << "(" << eq.longitude << ", " << eq.latitude << ", " << eq.depth << ")\n";
}

void printout(ofstream &OF, string SN, earthquake &eq, string NetC, string SCab, string ITab, string O)
{
    OF << eq.id << "." << NetC << "." << SN << "." << SCab << ITab << O << "\n";
}


int main()
{
    
    string   inputfilename, outputfilename, logfilename;
    ifstream inputfile;
    ofstream logfile, outputfile;
    
    cout << "Enter inputfile name: ";
    cin  >> inputfilename;
    open_input(inputfile, inputfilename);
    open_outputfiles(logfile, "log file", "darin.log");
    open_outputfiles(outputfile, "output file", "darin.out");
    
    cout    << "\nOpening file: darin.in\n";
    logfile << "Opening file: darin.in\n";
    cout    << "Processing input...\n";
    logfile << "Processing input...\n";
    
    earthquake eq;

    get_eqID(inputfile, eq);
    get_eqDate(inputfile, eq);
    
    string temp = "Invalid Data Length";
    if (CheckDateLength(eq) == false) Fail(logfile, temp);
    
    string tempstring;
    for (int i = 0; i <= 9; i++)    // Checks each position in the data for correct variable type
    {
        if (i == 2 || i == 5)
        {
            temp = "Invalid Date Separators";
            GetDateSubStr(eq, i, tempstring);
            if(CheckDateSeperators(tempstring) == false) Fail(logfile, temp);
        } else
        {
            temp = "Non-Number in Date";
            if(CheckDateValidity(eq, i) == false) Fail(logfile, temp);
        }
    }
    
    temp = "Date Seperators are not the same";
    if(CheckDateSeperators2(eq, 2,5) == false) Fail(logfile, temp);
    
    string M, D, Y;
    MDY(eq, M,D,Y);
    int intmonth = atoi(M.c_str());
    int intday = atoi(D.c_str());
    int intyear = atoi(Y.c_str());
    
    months month;
    month = (months)intmonth;
    
    temp = "Invalid Month";
    if (CheckMonthRange(intmonth) == false) Fail(logfile, temp);
    
    temp = "Invalid Day";
    if (CheckDayRange(intday) == false) Fail(logfile, temp);
    
    temp = "Invalid Year";
    if (CheckYearRange(intyear) == false) Fail(logfile, temp);
    
    string monthstring = monthtostring(month);
    
    temp = "Invalid Day/Month Combination";
    if (MonthDayComboCheck(intday, intmonth) == false) Fail(logfile, temp);
    
    get_eqTime(inputfile, eq);
    
    temp = "Invalid Time Length";
    if (CheckTimeLength(eq) == false) Fail(logfile, temp);
    
    string expVar;
    for (int i = 0; i <= 11; i++)     // Checks each position in the time for correct variable type
    {
        if (i == 2 || i == 5)
        {
            temp = "Invalid Time Seperator";
            GetTimeSubStr(eq, i, tempstring);
            expVar = ":";
            if(CheckTimeSeperators(tempstring, expVar) == false) Fail(logfile, temp);
        } else if (i == 8)
        {
            temp = "Invalid Time Seperator";
            GetTimeSubStr(eq, i, tempstring);
            expVar = ".";
            if(CheckTimeSeperators(tempstring, expVar) == false) Fail(logfile, temp);
        } else
        {
            temp = "Non-Number in Time";
            if(CheckTimeValidity(eq, i) == false) Fail(logfile, temp);
        }
    }
    
    temp = "Time Seperators are not the same";
    if (CheckDateSeperators2(eq, 2,5) == false) Fail(logfile, temp);
    
    temp = "Invalid Time Zone Length";
    get_eqTimeZone(inputfile, eq);
    if (CheckTimeZoneLength(eq) == false) Fail(logfile, temp);
    
    string HH, MM, SS;
    HMS(eq, HH,MM,SS);
    int inthour = atoi(HH.c_str());
    int intminute = atoi(MM.c_str());
    int intsecond = atoi(SS.c_str());
    
    temp = "Invalid Hour";
    if (CheckHourRange(inthour) == false) Fail(logfile, temp);
    
    temp = "Invalid Minute";
    if (CheckMinuteRange(intminute) == false) Fail(logfile, temp);
    
    temp = "Invalid Second";
    if (CheckSecondRange(intsecond) == false) Fail(logfile, temp);
    
    temp = "Invalid Day/Month Combination";
    if (MonthDayComboCheck(intday, intmonth) == false) Fail(logfile, temp);
    
    temp = "Invalid Time Zone Entry";
    if (CheckTimeZoneEntries(eq) == false) Fail(logfile, temp);

    string Name, Ename;
    int check = 1, check2 = 1;
    
    set_eqName(inputfile, eq, Name, Ename, check, check2);
    
    double Longitude, Latitude, Depth;
    
    Longitude = set_eqLongitude(inputfile, eq);
    Latitude = set_eqLatitude(inputfile, eq);
    Depth = set_eqDepth(inputfile, eq);

    temp = "Longitude out of Range";
    if (CheckLongRange(Longitude) == false) Fail(logfile, temp);
    temp = "Latitude out of Range";
    if (CheckLatRange(Latitude) == false) Fail(logfile, temp);
    temp = "Negative depth";
    if (CheckDepth(Depth) == false) Fail(logfile, temp);
    
    string magtype;
    inputfile >> magtype;
    temp = "Invalid Magnitude Type Length";
    if(Check_MagTypeLength(magtype) == false) Fail(logfile, temp);
    
    temp = "Invalid Magnitude Type";
    if (set_MagType(eq, magtype) == false) Fail(logfile, temp);
    
    set_Mag(inputfile, eq);
    temp = "Negative Magnitude";
    if (Check_Mag(eq) == false) Fail(logfile, temp);
    
    cout << "Header read correctly!\n";
    logfile << "Header read correctly!\n";
    
    HeaderOutput(outputfile, D, monthstring, Y, eq);
    
    struct entries in;
    int countbad = 0;
    int totsignals = 0;
    int validentries = 0, numentries = 0, newsignals, changer;
    string NetCode, StatCode, TypeBand, TypeInst, Orient;
    string NetworkCode[900], StationName[900], NCabbrev[900], ITabbrev[900], ORspot[900];
    while (inputfile >> NetCode)
    {
        numentries++;
        changer = 0;
        
        if(CheckNC(in, validentries, NetCode) == false)    // Checks if Network Code is valid
        {
            BadEntry(logfile, numentries, changer, "Network Code.");
        }
        
        inputfile >> StatCode;
        
        if(CheckSC(in, validentries, StatCode) == false)     // Checks if Station Name is valid
        {
            BadEntry(logfile, numentries, changer, "Station Name.");
        }
        
        inputfile >> TypeBand;
        Remove_Non_Letters(TypeBand);
        
        if(CheckBT(in,validentries, TypeBand) == false)     // Checks if Band Type is valid
        {
            BadEntry(logfile, numentries, changer, "Band Type.");
        }
        
        inputfile >> TypeInst;
        Remove_Non_Letters(TypeInst);
        
        if(CheckIT(in, validentries, TypeInst) == false)     // Checks if Instrument Type is valid
        {
            BadEntry(logfile, numentries, changer, "Instrument Type.");
        }
        
        inputfile >> Orient;
        
        if(CheckOR(in, validentries, Orient) == false)     // Checks if Orientation is valid
        {
            BadEntry(logfile, numentries, changer, "Orientation.");
        }
   
        if (changer !=0)
        {
            cout << "\n";
            logfile << "\n";
            countbad++;
        } else
        {
            SetNC(in, validentries, NetCode);     // Stores each variable of valid entries into the required array
            SetSC(in, validentries, StatCode);
            SetBT(in, validentries, TypeBand);
            SetIT(in, validentries, TypeInst);
            SetOR(in, validentries, Orient);
            
            newsignals = NumSigs(in, validentries);
            for (int i = 0; i < newsignals ; i++)
            {
                NetworkCode[totsignals+i] = getNC(in, validentries);    // Stores valid station readings into these array
                StationName[totsignals+i] = getSN(in, validentries);
                NCabbrev[totsignals+i]    = getBT(eq, in, validentries);     // Get necessary abreviations for intstrument and band
                ITabbrev[totsignals+i]    = getIT(eq, in, validentries);
                ORspot[totsignals+i]      = getOR(in, validentries, i);
            }
            validentries++;
            totsignals += newsignals;
        }
    }

    outputfile << totsignals << "\n";
    
    for (int i = 0; i < totsignals; i++)
    {
        printout(outputfile, StationName[i], eq, NetworkCode[i], NCabbrev[i], ITabbrev[i], ORspot[i]);
    }
    
    int countgood = numentries - countbad;
    
    cout    << "Total invalid entries ignored: " << countbad << "\n";
    logfile << "Total invalid entries ignored: " << countbad << "\n";
    cout    << "Total valid entries read: " << countgood << "\n";
    logfile << "Total valid entries read: " << countgood << "\n";
    cout    << "Total signal names processed: " << totsignals << "\n";
    logfile << "Total signal names processed: " << totsignals << "\n";
    
    return 0;

}
