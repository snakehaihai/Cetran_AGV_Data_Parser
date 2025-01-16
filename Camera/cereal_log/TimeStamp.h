#ifndef AISG_TIMESTAMP_H
#define AISG_TIMESTAMP_H

#include <cereal/access.hpp>
#include <chrono>
#include <cstdint>
#include <string>

namespace cereal_log
{

class TimeStamp
{
public:

    typedef std::chrono::system_clock::duration duration;
    typedef std::chrono::system_clock::rep rep;
    typedef std::chrono::system_clock::period period;

    /// This constructor will create a default date/time.
    TimeStamp(void);

    template<class _Rep, class _Period>
    explicit TimeStamp(const std::chrono::duration<_Rep, _Period>& aDuration);

    /// non-virtual destructor. Please do not inherit from this class
    ~TimeStamp(void);

    /**
        \brief This static function will return a date/time based on the system clock.
    
        \return a timestamp containing current Date/Time
    */
    static TimeStamp now(void);

    /**
        \brief This method returns the relative time since epoch as the reference.
    
        \note Epoch is implementation-defined, This class uses std::chrono's system clock as the basis of calculation.
        std::chrono implements this clock using GetSystemTimeAsFileTime() in Windows, which corresponds to a epoch
        of January 1, 1601 0000 UTC. It is converted to Unix epoch (January 1, 1970 0000 UTC) using std::chrono.
    
        \note This function returns values the number of nanoseconds since epoch.
    
        \warning Although you get nanosecond accuracy, do not assume it is accurate to that precision.
    
        \return relative time
    */
    std::chrono::nanoseconds getRelativeTime() const;
private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const;

	template <class Archive>
	void load(Archive& ar);

    /// Timestamps are stored as std.chrono's system_clock
    std::chrono::system_clock::time_point mSystemClockTimePoint;
    
    static const duration UNIX_TIME_EPOCH;
}; // class TimeStamp

/// left-shift operator to print the relative time.
/// To get actual date time, please use getDateTime() method
std::ostream& operator<<(std::ostream& aOS, const TimeStamp& aTs);

template<class _Rep, class _Period>
TimeStamp::TimeStamp(const std::chrono::duration<_Rep, _Period>& aDuration)
	: mSystemClockTimePoint(UNIX_TIME_EPOCH + std::chrono::duration_cast<duration>(aDuration))
{
 
}

template <class Archive>
void
TimeStamp::save(Archive& ar) const
{
	long long t = getRelativeTime().count();

	ar(t);
}

template <class Archive>
void
TimeStamp::load(Archive& ar)
{
	long long t;
	ar(t);

	mSystemClockTimePoint = std::chrono::system_clock::time_point(UNIX_TIME_EPOCH + std::chrono::duration_cast<duration>(std::chrono::nanoseconds(t)));
}

} // cereal_log

#endif // TIMESTAMP_H
