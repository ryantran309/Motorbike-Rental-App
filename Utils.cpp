#include <ctime>

int calculateDateDifference(tm& date1, tm& date2)
{
    // Calculates difference between two time components and returns the difference
    // converted in number of days

    time_t time1 = mktime(&date1);
    time_t time2 = mktime(&date2);

    double difference = difftime(time1, time2);

    int daysDifference = static_cast<int>(difference / (24 * 60 * 60));

    return daysDifference;
}