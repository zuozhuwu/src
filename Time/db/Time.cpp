#include "Time.h"
#include <iostream>
#include <algorithm>

std::string Time::timeFormat_ = "YYYY-MM-DD hh:mm:ss";

Time::Time():delimiter_ (" ")
{
    intTime_ = time(0);
    formatTime(intTime_);
}

Time::Time(std::string t) : delimiter_ (" ")
{
    // size check
    if(t.size() < timeFormat_.size())
    {
        char separator = getSeparator(timeFormat_);
        std::string appendStr = "00" + std::string(1, separator) + "00" + std::string(1, separator) + "00";

        if(timeFormat_.size() == t.size() + appendStr.size() + 1)
        {
            t = t + " " + appendStr;
        }
        else if(timeFormat_.size() == t.size() + appendStr.size())
        {
            t = t + appendStr;
        }
        else 
        {
            std::cout<<"error in class Time, in function Time::Time(std::string t), variable error!"<<std::endl;
            exit(-1);
        }
    }

    formatTime(t);
}

Time::Time(time_t t) : delimiter_(" ")
{
    formatTime(t);
}

bool Time::formatTime(std::string strTime)
{
    if(!isTimeFormatRight(strTime))
    {
        std::cout<<"the input time format does not match defined time format in function bool Time::formatTime(std::string strTime)"<<std::endl;
        exit(-1);
        return false;
    }

    struct tm  ltm;

    size_t pos_Y = timeFormat_.find('Y');
    size_t nY = nCharsInString(timeFormat_, 'Y');
    ltm.tm_year = atoi(strTime.substr(pos_Y, nY).c_str()) - 1900;

    size_t pos_M = timeFormat_.find('M');
    size_t nM = nCharsInString(timeFormat_, 'M');
    ltm.tm_mon = atoi(strTime.substr(pos_M, nM).c_str()) - 1;

    size_t pos_D = timeFormat_.find('D');
    size_t nD = nCharsInString(timeFormat_, 'D');
    ltm.tm_mday = atoi(strTime.substr(pos_D, nD).c_str());

    size_t pos_h = timeFormat_.find('h');
    size_t nh = nCharsInString(timeFormat_, 'h');
    ltm.tm_hour = atoi(strTime.substr(pos_h,nh).c_str());

    size_t pos_m = timeFormat_.find('m');
    size_t nm = nCharsInString(timeFormat_, 'm');
    ltm.tm_min = atoi(strTime.substr(pos_m,nm).c_str());

    size_t pos_s = timeFormat_.find('s');
    size_t ns = nCharsInString(timeFormat_, 's');
    ltm.tm_sec = atoi(strTime.substr(pos_s,ns).c_str());

    intTime_ = mktime(&ltm);
    strTime_ = strTime;

    return true;
}

bool Time::formatTime(time_t t)
{
    struct tm  ltm;
    localtime_s(&ltm,&t);

    strTime_ = timeFormat_;

    size_t pos_Y = timeFormat_.find('Y');
    size_t nY = nCharsInString(timeFormat_, 'Y');
    std::string strYear = std::to_string(1900 + ltm.tm_year);
    if(nY == 2)
    {
        strYear = strYear.substr(2, -1);
    }
    strTime_.replace(pos_Y, nY, strYear);

    size_t pos_M = timeFormat_.find('M');
    size_t nM = nCharsInString(timeFormat_, 'M');
    std::string strMonth = std::to_string(1 + ltm.tm_mon);
    prefixStr(strMonth);
    strTime_.replace(pos_M, nM, strMonth);

    size_t pos_D = timeFormat_.find('D');
    size_t nD = nCharsInString(timeFormat_, 'D');
    std::string strDay = std::to_string(ltm.tm_mday);
    prefixStr(strDay);
    strTime_.replace(pos_D, nD, strDay);


    size_t pos_h = timeFormat_.find('h');
    size_t nh = nCharsInString(timeFormat_, 'h');
    std::string strHour = std::to_string(ltm.tm_hour);
    prefixStr(strHour);
    strTime_.replace(pos_h, nh, strHour);


    size_t pos_m = timeFormat_.find('m');
    size_t nm = nCharsInString(timeFormat_, 'm');
    std::string strMin = std::to_string(ltm.tm_min);
    prefixStr(strMin);
    strTime_.replace(pos_m, nm, strMin);


    size_t pos_s = timeFormat_.find('s');
    size_t ns = nCharsInString(timeFormat_, 's');
    std::string strSec = std::to_string(ltm.tm_sec);
    prefixStr(strSec);
    strTime_.replace(pos_s, ns, strSec);

    intTime_ = mktime(&ltm);

    return true;
}

void Time::prefixStr(std::string& str)
{
    if (str.size()<2)
    {
        str = "0" + str;
    }    
}


void Time::addDay(int addD)
{
    intTime_ += 24 * 3600 * addD;
    formatTime(intTime_);
}

void Time::addHour(int addH)
{
    intTime_ += 3600 * addH;
    formatTime(intTime_);
}

void Time::addMin(int addM)
{
    intTime_ += 60 * addM;
    formatTime(intTime_);
}

void Time::addSec(int addS)
{
    intTime_ += addS;
    formatTime(intTime_);
}

std::string Time::getDate()
{
    return strTime_.substr(0, strTime_.find(delimiter_));
}

std::string Time::getDateTime()
{
    return strTime_.substr(strTime_.find(delimiter_) + 1, -1);
}

bool Time::operator<(const Time& t)
{
    return intTime_ < t.getIntTime();
}

bool Time::operator<=(const Time& t)
{
    return intTime_ <= t.getIntTime();
}

bool Time::operator>(const Time& t)
{
    return intTime_ > t.getIntTime();
}

bool Time::operator>=(const Time& t)
{
    return intTime_ >= t.getIntTime();
}

size_t Time::operator-(const Time& t)
{
    return intTime_ = t.intTime_;
}

void Time::setTimeFormat(std::string fmt)
{
    size_t nYs = nCharsInString(fmt, 'Y');
    if(nYs != 2 && nYs != 4)
    {
        std::cout<<"error in function \"void Time::setTimeFormat(std::string fmt)\", the count of Y is not 2 or 4"<<std::endl;
        exit(-1);
    }

    size_t nMs = nCharsInString(fmt, 'M');
    if(nMs != 2)
    {
        std::cout<<"error in function \"void Time::setTimeFormat(std::string fmt)\", the count of M is not 2"<<std::endl;
        exit(-1);
    }

    size_t nDs = nCharsInString(fmt, 'D');
    if(nDs != 2)
    {
        std::cout<<"error in function \"void Time::setTimeFormat(std::string fmt)\", the count of D is not 2"<<std::endl;
        exit(-1);
    }

    size_t nhs = nCharsInString(fmt, 'h');
    if(nhs != 2)
    {
        std::cout<<"error in function \"void Time::setTimeFormat(std::string fmt)\", the count of h is not 2"<<std::endl;
        exit(-1);
    }

    size_t nms = nCharsInString(fmt, 'm');
    if(nms != 2)
    {
        std::cout<<"error in function \"void Time::setTimeFormat(std::string fmt)\", the count of m is not 2"<<std::endl;
        exit(-1);
    }

    size_t nss = nCharsInString(fmt, 's');
    if(nss != 2)
    {
        std::cout<<"error in function \"void Time::setTimeFormat(std::string fmt)\", the count of s is not 2"<<std::endl;
        exit(-1);
    }

    timeFormat_ = fmt;
}

size_t Time::nCharsInString(std::string s, char c)
{
    return std::count(s.begin(), s.end(), c);
}

bool Time::isTimeFormatRight(std::string strTime)
{
    char cl = getSeparator(strTime);
    char cr = getSeparator(timeFormat_);
    if( cl != char(0) && cr != char(0) && cl == cr && strTime.size() == timeFormat_.size())
    {
        return true;
    }
    else 
    {
        return false;
    }
}

char Time::getSeparator(std::string str)
{
    std::size_t found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");
    if (found!=std::string::npos)
    {
        return str[found];        
    }
    else 
    {
        return char(0);
    }
}