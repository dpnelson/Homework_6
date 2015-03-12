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
#include <math.h>
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

int main()
{
 //   string EventID, Date, Time, TimeZone, word, Name, Ename;
 //   string MagType;
 //   string E[4];
 //   double Longitude, Latitude, Depth;
 //   float MagSize;
    
    string   inputfilename, outputfilename, logfilename;
    ifstream inputfile;
    ofstream logfile, outputfile;
    
    cout << "Enter inputfile name: ";
    cin  >> inputfilename;
    open_input(inputfile, inputfilename);
    open_log_output(logfile, outputfile, "darin.log", "darin.out");

    return 0;

}
