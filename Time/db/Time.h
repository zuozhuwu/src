/* used to handle time
 * Time.h
 * zuozhuwu 2022.3.31 
*/

#ifndef TIME_H
#define TIME_H

#include <string>
#include <ctime>

class Time
{
private: 
    // the string time
    std::string strTime_;

    // the present time in secs from 1970
    time_t intTime_; 

    // character to separate day and time
    std::string delimiter_;

    // the time format
    static std::string timeFormat_;  
    
public:
    // the constructors
    // construct with present time
    Time();

    // construct with string
    Time(std::string t);

    // construct from time_t
    Time(time_t t);

    // member functions
    std::string getStrTime()const{return strTime_;}
    int         getIntTime()const{return intTime_;}
    void        setDelemiter(std::string deli) {delimiter_ = deli;}

    // get YYYY-MM-DD string
    std::string getDate();

    // get hh-mm-ss
    std::string getDateTime();

    bool operator<(const Time& t);
    bool operator<=(const Time& t);
    bool operator>(const Time& t);
    bool operator>=(const Time& t);

    // get time divergence in seconds
    size_t operator-(const Time& t);

    void addDay(int addD);
    void addHour(int addH);
    void addMin(int addM);
    void addSec(int addS);

    // static functions
    static void setTimeFormat(std::string fmt);

    static std::string getTimeFormat() {return timeFormat_;}

    // get char occurrent times in string
    static size_t nCharsInString(std::string, char c);    

private:
    // format time
    bool formatTime(std::string);
    bool formatTime(time_t t);

    // format str with prefix 0, egg: 5 -> 05
    void prefixStr(std::string& str);

    // whether the input time matches the time format
    bool isTimeFormatRight(std::string strTime);

    // get the separator in string
    char getSeparator(std::string str);
};

#endif