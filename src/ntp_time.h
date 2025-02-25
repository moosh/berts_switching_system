/*******************************************************************************

    ntp_time.h

    Copyright (c) 2025 Mooshwerks
    All Rights Reserved
    
*******************************************************************************/

#pragma once

#include <string>
#include <algorithm>
#include <time.h>

const int GMT = 0;
const int UTC = 0;
const int ECT = 1.00;
const int EET = 2.00;
const int ART = 2.00;
const int EAT = 3.00;
const int MET = 3.30;
const int NET = 4.00;
const int PLT = 5.00;
const int IST = 5.30;
const int BST = 6.00;
const int VST = 7.00;
const int CTT = 8.00;
const int JST = 9.00;
const int ACT = 9.30;
const int AET = 10.00;
const int SST = 11.00;
const int NST = 12.00;
const int MIT = -11.00;
const int HST = -10.00;
const int AST = -9.00;
const int PST = -8.00;
const int PNT = -7.00;
const int MST = -7.00;
const int CST = -6.00;
const int CDT = -5.00;
const int EST = -5.00;
const int IET = -5.00;
const int PRT = -4.00;
const int CNT = -3.30;
const int AGT = -3.00;
const int BET = -3.00;
const int CAT = -1.00;

const int SECONDS_PER_HOUR = 3600;
const int EPOCH_1_1_2019 = 1546300800; //1546300800 =  01/01/2019 @ 12:00am (UTC)
const char *DAYS_OF_WEEK[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char *DAYS_OF_WEEK_3[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

class NTPTime
{
    std::string mTimeServer;
    int mTimeZone = UTC;

public:
    NTPTime(void)
    {
    }

    virtual ~NTPTime(void)
    {
    }

    std::string default_time_server()
    {
        return std::string("pool.ntp.org");
    }

    int init(int inTimeZone)
    {
        return init(inTimeZone, default_time_server());
    }

    int init(int inTimeZone, std::string inTimeServer)
    {
        int err = 0;
        mTimeZone = inTimeZone;
        mTimeServer = inTimeServer;
        configTime(mTimeZone * SECONDS_PER_HOUR, 0, (const char*)(mTimeServer.c_str()));

        time_t now = 0;
        while (now < EPOCH_1_1_2019)
        {
            now = time(nullptr);
            delay(500);
        }

        return err;
    }

    int year()
    {
        time_t now;
        time(&now);
        struct tm *timeinfo = localtime(&now);
        return  timeinfo->tm_year + 1900;
    }

    int month()
    {
        time_t now;
        time(&now);
        struct tm *timeinfo = localtime(&now);
        return timeinfo->tm_mon + 1; // +1 because tm_mon is number of months since January.
    }


    int day()
    {
        time_t now;
        time(&now);
        struct tm *timeinfo = localtime(&now);
        return timeinfo->tm_mday;
    }


    int hour()
    {
        time_t now;
        time(&now);
        struct tm *timeinfo = localtime(&now);
        return timeinfo->tm_hour;
    }


    int min()
    {
        time_t now;
        time(&now);
        struct tm *timeinfo = localtime(&now);
        return timeinfo->tm_min;
    }


    int sec()
    {
        time_t now;
        time(&now);
        struct tm *timeinfo = localtime(&now);
        return timeinfo->tm_sec;
    }


    int day_of_week()
    {
        time_t now;
        time(&now);
        struct tm *timeinfo = localtime(&now);
        return timeinfo->tm_wday;
    }


    std::string day_of_week_string()
    {
        return std::string(DAYS_OF_WEEK[day_of_week()]);
    }


    std::string day_of_week_string_short()
    {
        return std::string(DAYS_OF_WEEK_3[day_of_week()]);
    }


    std::string now_formatted()
    {
        // Outputs the form YYYY:MM:DD:HH:MM:SS
        std::string outStr;

        outStr += std::to_string(year());
        outStr += std::string(":") + pad_with_characters(month(), '0', 2);
        outStr += std::string(":") + pad_with_characters(day(), '0', 2);
        outStr += std::string(":") + pad_with_characters(hour(), '0', 2);
        outStr += std::string(":") + pad_with_characters(min(), '0', 2);
        outStr += std::string(":") + pad_with_characters(sec(), '0', 2);

        return outStr;
    }


    std::string pad_with_characters(int inValue, char inPadChar, size_t inPadCount)
    {
        std::string valString = std::to_string(inValue);
        return pad_with_characters(valString, inPadChar, inPadCount);
    }


    std::string pad_with_characters(std::string inStr, char inPadChar, size_t inPadCount)
    {
        return std::string(inPadCount - std::min(inPadCount, inStr.length()), inPadChar) + inStr;
    }

};

