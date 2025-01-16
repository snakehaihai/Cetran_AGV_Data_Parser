/**
    \file TimeStamp.cpp
*/
#include "TimeStamp.h"
#include <ctime>
#include <array>
#include <iomanip>
#include <sstream>

namespace cereal_log
{

const TimeStamp::duration TimeStamp::UNIX_TIME_EPOCH = std::chrono::system_clock::from_time_t(0).time_since_epoch();

TimeStamp::TimeStamp(void)
: mSystemClockTimePoint(UNIX_TIME_EPOCH)
{

}

TimeStamp::~TimeStamp(void)
{
}

TimeStamp TimeStamp::now(void)
{
    TimeStamp tTimeStamp;
    tTimeStamp.mSystemClockTimePoint = std::chrono::system_clock::now();
    return tTimeStamp;
}

std::chrono::nanoseconds TimeStamp::getRelativeTime() const
{
    const auto tRelativeTime = mSystemClockTimePoint.time_since_epoch() - UNIX_TIME_EPOCH;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(tRelativeTime);
}



} // cereal_log
