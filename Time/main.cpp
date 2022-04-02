#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "db/Time.h"
using namespace std;


int main()
{
    // time_t now = time(0);

    // cout << "1970 secs:" << now << endl;

    // struct tm  ltm;
    // localtime_s(&ltm,&now);
    Time t1("2022-05-01");
    cout<<t1.getStrTime()<<endl;

    cout<<Time::getTimeFormat()<<endl;
    Time::setTimeFormat("MM/DD/YYYY hh:mm:ss");


    t1.addHour(2);
    cout<<t1.getStrTime()<<endl;
    cout<<t1.getIntTime()<<endl;


    


    return 0;
}
