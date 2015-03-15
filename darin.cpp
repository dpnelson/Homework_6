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

void open_outputfiles(ofstream &file, string file2, string file3)
{
    file.open(file3.c_str());
    if ( !file.is_open() )
    {
        cout << "Cannot open " << file2 << "file: " << file3;
        file.flush();
        exit(EXIT_FAILURE);
    } 
}

void Fail(ofstream &logfile, string failtype)
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

string MagTypefromNum(earthquake eq)
{
    if (eq.magnitude_type == ML) return "ML";
    if (eq.magnitude_type == MS) return "MS";
    if (eq.magnitude_type == MB) return "MB";
    if (eq.magnitude_type == MW) return "MW";
    return false;
}


void get_eqID(ifstream &IF, earthquake &eq)
{
    IF >> eq.id;
}

void get_eqDate(ifstream &IF, earthquake &eq)
{
    IF >> eq.date;
}

void GetDateSubStr(earthquake eq, int ii, string &tempS)
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
    if (day < 1 || day > 31) return false;
    return true;
}

bool CheckYearRange(int year)
{
    if (year > 2015) return false;
    return true;
}

bool CheckDateSeperators(string tempS)
{
    if (tempS.compare("/") != 0 && tempS.compare("-") != 0)
    {
        return false;
    }
    return true;
}

bool CheckDateValidity(earthquake eq, int place)
{
    if (!isdigit(eq.date[place])) return false;
    return true;
}

bool CheckDateSeperators2(earthquake eq, int aa, int bb)
{
    if (eq.date[aa] != eq.date[bb]) return false;
    return true;
}

void get_eqTime(ifstream &IF, earthquake &eq)
{
    IF >> eq.time;
}

void GetTimeSubStr(earthquake eq, int ii, string &tempS)
{
    tempS = eq.time.substr(ii,1);
}

bool CheckTimeLength(earthquake eq)
{
    if (eq.time.length() != 12) return false;
    return true;
}

bool CheckTimeSeperators(string &tempS)
{
    if (tempS.compare(":") != 0) return false;
    return true;
}

bool CheckTimeValidity(earthquake eq, int place)
{
    if (!isdigit(eq.time[place])) return false;
    return true;
}

bool CheckTimeSeperators2(string &tempS)
{
    if (tempS.compare(".") != 0) return false;
    return true;
}

bool CheckDateSeperators3(earthquake eq, int aa, int bb)
{
    if (eq.time[aa] != eq.time[bb]) return false;
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

bool CheckTimeZoneEntries(earthquake eq)
{
    for (int i = 0; i < 3; i++)
    {
        if(!isalpha(eq.timezone[i])) return false;
    }
    return true;
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

bool Check_MagTypeLength(string MT)
{
    if (MT.length() != 2) return false;
    return true;
}

bool get_MagType(earthquake &eq, string mag)
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

void get_Mag(ifstream &IF, earthquake &eq)
{
    IF >> eq.magnitude;
}

bool Check_Mag(earthquake &eq)
{
    if (eq.magnitude < 0) return false;
    return true;
}

void MDY(earthquake eq, string &MM, string &DD, string &YY)
{
    MM = eq.date.substr(0,2);
    DD = eq.date.substr(3,2);
    YY = eq.date.substr(6,4);
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
    return false;
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

months Month_to_Num(int M)
{
    if (M == 1)  return January;
    if (M == 2)  return February;
    if (M == 3)  return March;
    if (M == 4)  return April;
    if (M == 5)  return May;
    if (M == 6)  return June;
    if (M == 7)  return July;
    if (M == 8)  return August;
    if (M == 9)  return September;
    if (M == 10) return October;
    if (M == 11) return November;
    if (M == 12) return December;
    return January;
}

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
    return false;
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

struct entries {
    NetworkCode NC[300];
    string SC[300];
    BandTypes BT[300];
    InstrumentTypes IT[300];
    string OR[300];
};

bool checkNC(entries &in, int k, string check)
{
    if(check == "CE")
    {
        in.NC[k] = CE;
        return true;
    } else if (check == "CI")
    {
        in.NC[k] = CI;
        return true;
    } else if (check == "FA")
    {
        in.NC[k] = FA;
        return true;
    } else if (check == "NP")
    {
        in.NC[k] = NP;
        return true;
    } else if (check == "WR")
    {
        in.NC[k] = WR;
        return true;
    } else {
        return false;
    }
};

string NCtoString(entries &in, int k)
{
    if (in.NC[k] == CE )  return  "CE";
    if (in.NC[k] == CI )  return  "CI";
    if (in.NC[k] == FA )  return  "FA";
    if (in.NC[k] == NP )  return  "NP";
    if (in.NC[k] == WR )  return  "WR";
    return false;
};

void BadEntryNC(ofstream &LF, int z, int &change)
{
    if (change == 0) change++;
    cout << "Entry # " << right << setw(3) << z << " ignored. Invalid network code.";
    LF   << "Entry # " << right << setw(3) << z << " ignored. Invalid network code.";
}


bool checkSC(entries &in, int k, string StatCode)
{
    if(StatCode.length() != 3 && StatCode.length() != 5)
    {
        return false;
    } else
    {
        if (StatCode.length() == 5)
        {
            int num = 4;
            for (int w = 0; w <= num; w++)
            {
                if(!isdigit(StatCode[w]))
                {
                    return false;
                } 
            }
        } else
        {
            int num = 2;
            for (int w = 0; w <= num; w++)
            {
                if(!isalpha(StatCode[w]))
                {
                    return false;
                }
                
                string temp = StatCode;
                string temp1 = temp;
                changetoupper(temp);
                
                if (temp != temp1)
                {
                    return false;
                }
                
            }
        }
        in.SC[k] = StatCode;
        return true;
    }
};

void BadEntrySC(ofstream &LF, int z, int &change)
{
    if (change == 0)
    {
        change++;
        cout << "Entry # " << right << setw(3) << z << " ignored.";
    }
    cout << " Invalid station code.";
    LF   << " Invalid station code.";
}


void Remove_Non_Letters(entries &in, int y, string &BandInst)
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

bool checkBT(entries &in, int k, string TB)
{
    if(TB == "LONGPERIOD")
    {
        in.BT[k] = LONGPERIOD;
        return true;
    } else if (TB == "SHORTPERIOD")
    {
        in.BT[k] = SHORTPERIOD;
        return true;
    } else if (TB == "BROADBAND")
    {
        in.BT[k] = BROADBAND;
        return true;
    } else
    {
        return false;
    }
};


void BadEntryBT(ofstream &LF, int z, int &change)
{
    if (change == 0)
    {
        change++;
        cout << "Entry # " << right << setw(3) << z << " ignored.";
        LF   << "Entry # " << right << setw(3) << z << " ignored.";
    }
    cout << " Invalid band type.";
    LF   << " Invalid band type.";
}

bool checkIT(entries &in, int k, string INST)
{
    if(INST == "HIGHGAIN")
    {
        in.IT[k] = HIGHGAIN;
        return true;
    } else if (INST == "LOWGAIN")
    {
        in.IT[k] = LOWGAIN;
        return true;
    } else if (INST == "ACCELEROMETER")
    {
        in.IT[k] = ACCELEROMETER;
        return true;
    } else
    {
        return false;
    }
};


void BadEntryIT(ofstream &LF, int z, int &change)
{
    if (change == 0)
    {
        change++;
        cout << "Entry # " << right << setw(3) << z << " ignored.";
        LF   << "Entry # " << right << setw(3) << z << " ignored.";
    }
    cout << " Invalid instrument type.";
    LF   << " Invalid instrument type.";
}

bool checkOR(entries &in, int k, string ORE)
{
    if(ORE.length() < 1 || ORE.length() > 3)
    {
        return false;
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
            return false;
        }
    }
    if (alphacount != ORE.length() && numbercount != ORE.length())
    {
        return false;
    }
    
    if (alphacount != 0)
    {
        changetoupper(ORE);
        for (int c = 1; c <= ORE.length(); c++)
        {
            string tempString = ORE.substr(c-1,1);
            if (tempString.compare("N") && tempString.compare("E") && tempString.compare("Z"))
            {
                return false;
            }
        }
    }
    
    if (numbercount != 0)
    {
        for (int c = 1; c <= in.OR[k].length(); c++)
        {
            string tempString = in.OR[k].substr(c-1,1);
            if (tempString.compare("1") && tempString.compare("2") && tempString.compare("3"))
            {
                return false;
            }
        }
    }
    in.OR[k] = ORE;
    return true;
};


void BadEntryOR(ofstream &LF, int z, int &change)
{
    if (change == 0)
    {
        change++;
        cout << "Entry # " << right << setw(3) << z << " ignored.";
        LF   << "Entry # " << right << setw(3) << z << " ignored.";
    }
    cout << " Invalid orientation.";
    LF   << " Invalid orientation.";
}

void HeaderOutput(ofstream &OF, string DD, string MM, string YY, earthquake eq, string MT)
{
    OF <<  "# " << DD << " " << MM << " " << YY << " " << eq.time << " " << eq.timezone << " ";
    OF << MT << " " << eq.magnitude << " " << eq.earthquake_name << " ";
    OF << "[" << eq.id << "] " << "(" << eq.longitude << ", " << eq.latitude << ", " << eq.depth << ")\n";
}

void printout(ofstream &OF, string SN, earthquake &eq, int entry, string NetC, int &signals, string SCab, string ITab, string O)
{
    OF << eq.id << "." << NetC << "." << SN << "." << SCab << ITab << O << "\n";
}

void printout2(ofstream &OF, int zero)
{
    OF << zero;
}

string getAbbevBT(earthquake eq, entries &in, int y)
{
    if (in.BT[y] == LONGPERIOD)  return "L";
    if (in.BT[y] == SHORTPERIOD) return "B";
    if (in.BT[y] == BROADBAND)   return "H";
    return false;
}

string getAbbevIT(earthquake eq, entries &in, int y)
{
    if (in.IT[y] == HIGHGAIN)       return "H";
    if (in.IT[y] == LOWGAIN)        return "L";
    if (in.IT[y] == ACCELEROMETER)  return "N";
    return false;
}

int NumSigs(entries &in, int k)
{
    int i = 0;
    while (isalpha(in.OR[k][i]) || isdigit(in.OR[k][i]))
    {
        i++;
    }
    return i;
}

string getOR(entries in, int k, int b)
{
    string end = in.OR[k].substr(b,1);
    return end;
}

string RetrieveStatName(entries &in, int y)
{
    string last = in.SC[y];
    return last;
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
    
    string M, D, Y;
    MDY(eq, M,D,Y);
    int NumberMonth = MonthtoInteger(M);

    months month;
    month = (months)NumberMonth;
    
    temp = "Invalid Month Range";
    if (CheckMonthRange(month) == false) Fail(logfile, temp);
    
    string monthstring = monthtostring(month);
    
    string tempstring;
    for (int i = 0; i <= 9; i++)
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
    
    get_eqTime(inputfile, eq);
    
    temp = "Invalid Time Length";
    if (CheckTimeLength(eq) == false) Fail(logfile, temp);
        
    for (int i = 0; i <= 11; i++)
    {
        if (i == 2 || i == 5)
        {
            temp = "Invalid Time Seperator";
            GetTimeSubStr(eq, i, tempstring);
            if(CheckTimeSeperators(tempstring) == false) Fail(logfile, temp);
        } else if (i == 8)
        {
            temp = "Invalid Time Seperator";
            GetTimeSubStr(eq, i, tempstring);
            if(CheckTimeSeperators2(tempstring) == false) Fail(logfile, temp);
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
    
    temp = "Invalid Time Zone Entry";
    if (CheckTimeZoneEntries(eq) == false) Fail(logfile, temp);

    string Name, Ename;
    int check = 1, check2 = 1;
    
    get_eqName(inputfile, eq, Name, Ename, check, check2);
    
    string Longitude, Latitude, Depth;
    
    get_eqLongitude(inputfile, eq);
    get_eqLatitude(inputfile, eq);
    get_eqDepth(inputfile, eq);
    
    string magtype;
    inputfile >> magtype;
    temp = "Invalid Magnitude Type Length";
    if( Check_MagTypeLength(magtype) == false) Fail(logfile, temp);
    
    string StrMagType = MagTypefromNum(eq);
    
    temp = "Invalid Magnitude Type";
    if (get_MagType(eq, magtype) == false) Fail(logfile, temp);
    
    get_Mag(inputfile, eq);
    temp = "Negative Magnitude";
    if (Check_Mag(eq) == false) Fail(logfile, temp);
    
    cout << "Header read correctly!\n";
    logfile << "Header read correctly!\n";

    entries in;
    
    HeaderOutput(outputfile, D, monthstring, Y, eq, StrMagType);
    
    int countbad = 0;
    int totsignals = 0;
    int numentries = 0;
    string NetCode, StatCode, TypeBand, TypeInst, Orient;
    string NetworkCode[900], StationName[900], NCabbrev[900], ITabbrev[900], ORspot[900];
    while (inputfile >> NetCode)
    {
        numentries++;
        int changer = 0;

        if(checkNC(in, numentries-1, NetCode) == false)
        {
            BadEntryNC(logfile, numentries, changer);
        }
        
        inputfile >> StatCode;
        
        if(checkSC(in, numentries-1, StatCode) == false)
        {
            BadEntrySC(logfile, numentries, changer);
        }
        
        inputfile >> TypeBand;
        Remove_Non_Letters(in, numentries, TypeBand);
        
        if(checkBT(in, numentries-1, TypeBand) == false)
        {
            BadEntryBT(logfile, numentries, changer);
        }
        
        inputfile >> TypeInst;
        Remove_Non_Letters(in, numentries-1, TypeInst);
        
        if(checkIT(in, numentries-1, TypeInst) == false)
        {
            BadEntryIT(logfile, numentries, changer);
        }
        
        inputfile >> Orient;
        
        if(checkOR(in, numentries-1, Orient) == false)
        {
            BadEntryOR(logfile, numentries, changer);
        } 
   
        if (changer !=0)
        {
            cout << "\n";
            logfile << "\n";
            countbad++;
        } else
        {
            int index = numentries - 1;
            int newsignals = NumSigs(in, index);
            
            for (int i = 0; i < newsignals ; i++)
            {
                NetworkCode[totsignals+i] = NCtoString(in, numentries-1);
                StationName[totsignals+i] = RetrieveStatName(in, numentries-1);
                NCabbrev[totsignals+i] = getAbbevBT(eq, in, numentries-1);
                ITabbrev[totsignals+i] = getAbbevIT(eq, in, numentries-1);
                ORspot[totsignals+i] = getOR(in, numentries-1, i);
            }
            
            totsignals += newsignals;
        }
    }
    
    if (numentries == 0) printout2(outputfile, numentries);
    outputfile << totsignals << "\n";
    
    for (int i = 0; i < totsignals; i++)
    {
         printout(outputfile, StationName[i], eq, numentries-1, NetworkCode[i], totsignals, NCabbrev[i], ITabbrev[i], ORspot[i]);
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
