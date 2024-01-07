/**
 * @file VisitorCounter.cpp
 * @brief Implementation of the VisitorCounter class methods.
 */

#include "VisitorCounter.h"

 /**
  * @brief Converts hours and minutes to total minutes.
  * @param hours The hours component.
  * @param minutes The minutes component.
  * @return Total minutes.
  */
int VisitorCounter::convertToMinutes(int hours, int minutes)
{
    return hours * 60 + minutes;
}

/**
 * @brief Parses a time string into total minutes.
 * @param timeStr The time string in "hh:mm" format.
 * @return Total minutes.
 */
int VisitorCounter::parseTime(const string& timeStr) {
    int hours, minutes;
    char colon;
    istringstream stream(timeStr);
    stream >> hours >> colon >> minutes;
    return convertToMinutes(hours, minutes);
}

/**
 * @brief Converts total minutes to hours and minutes.
 * @param inputMinutes Total minutes.
 * @param hours Output parameter for hours.
 * @param minutes Output parameter for minutes.
 */
void VisitorCounter::ConvertMinutesToHoursAndMinutes(int inputMinutes, int& hours, int& minutes) {

    hours = inputMinutes / 60;
    minutes = inputMinutes % 60;
}

/**
 * @brief Maps entering and leaving times of visitors to visitor actions.
 * @param filePath The path to the input file containing visitor times.
 * @return A map where the key is the minute and the value is the visitor count to increment or decrement.
 * @throw std::invalid_argument if the input file cannot be opened.
 */
map<int, int> VisitorCounter::MapTimeToVisitorAction(const string& filePath)
{
    map<int, int> mapTimeToVisitorAction; // Key: minute, Value: visitor count to increment or decrement

    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {

        throw invalid_argument("Error: Unable to open input file.");
        return mapTimeToVisitorAction;
    }

    string line;
    while (getline(inputFile, line)) {
        string start, end;
        istringstream ss(line);
        getline(ss, start, ',');
        getline(ss, end);

        int startTime = parseTime(start);
        int endTime = parseTime(end);

        // Increment count for start time and decrement count for end time + 1
        auto it = mapTimeToVisitorAction.find(startTime);
        if (it != mapTimeToVisitorAction.end())
        {
            ++mapTimeToVisitorAction[startTime];
        }
        else
        {
            mapTimeToVisitorAction[startTime] = 1;
        }

        int endTimeEffectTime = endTime + 1;
        it = mapTimeToVisitorAction.find(endTimeEffectTime);
        if (it != mapTimeToVisitorAction.end())
        {
            --mapTimeToVisitorAction[endTimeEffectTime];
        }
        else
        {
            mapTimeToVisitorAction[endTimeEffectTime] = -1;
        }
    }

    inputFile.close();

    return mapTimeToVisitorAction;
}

/**
 * @brief Finds the time period with the maximum number of visitors.
 * @param mapTimeToVisitorAction The map of visitor actions over time.
 * @param maxVisitorCount Output parameter for the maximum number of visitors.
 * @param maxVisitorRanges Output parameter for the time ranges with the maximum number of visitors.
 */
void VisitorCounter::FindMaxVisitors(
    const map<int, int>& mapTimeToVisitorAction,
    int& maxVisitorCount,
    vector<pair<int, int>>& maxVisitorRanges)
{
    maxVisitorRanges.clear();
    maxVisitorCount = -1;

    // Find the time period with the maximum number of visitors
    int currentVisitors = 0;
    vector<int> maxTimes;

    for (const auto& entry : mapTimeToVisitorAction) {
        currentVisitors += entry.second;
        if (currentVisitors > maxVisitorCount)
        {
            maxVisitorCount = currentVisitors;
            maxTimes.clear();
            maxTimes.push_back(entry.first);
        }
        else if (currentVisitors == maxVisitorCount)
        {
            maxTimes.push_back(entry.first);
        }
    }

    for (int startTime : maxTimes)
    {
        auto it = mapTimeToVisitorAction.find(startTime);
        int endTime{ -1 };
        if (it != mapTimeToVisitorAction.end())
        {
            endTime = ((++it)->first - 1);
        }
        maxVisitorRanges.push_back({ startTime, endTime });
    }
}

/**
 * @brief Finds the time period with the maximum number of visitors.
 * @param visitorLogPath The path to the input file containing visitor times.
 * @param maxVisitorCount Output parameter for the maximum number of visitors.
 * @param maxVisitorRanges Output parameter for the time ranges with the maximum number of visitors.
 */
void VisitorCounter::FindMaxVisitors(
    const string& visitorLogPath,
    int& maxVisitorCount,
    vector<pair<int, int>>& maxVisitorRanges)
{
    map<int, int> mapTimeToVisitorAction{ MapTimeToVisitorAction(visitorLogPath) };  // Key: minute, Value: visitor count
    FindMaxVisitors(mapTimeToVisitorAction, maxVisitorCount, maxVisitorRanges);
}
