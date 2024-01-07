#pragma once

#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <vector>

using namespace std;

/**
 * @class VisitorCounter
 * @brief Class for finding the time period with the most visitors.
 */
class VisitorCounter {

public:
     /**
     * @brief Finds the time period with the maximum number of visitors.
     * @param visitorLogPath The path to the input file containing visitor times.
     * @param maxVisitorCount Output parameter for the maximum number of visitors.
     * @param maxVisitorRanges Output parameter for the time ranges with the maximum number of visitors.
     */
    static void FindMaxVisitors(
        const string& visitorLogPath,
        int& maxVisitorCount,
        vector<pair<int, int>>& maxVisitorRanges);
     /**
     * @brief Converts total minutes to hours and minutes.
     * @param inputMinutes Total minutes.
     * @param hours Output parameter for hours.
     * @param minutes Output parameter for minutes.
     */
    static void ConvertMinutesToHoursAndMinutes(
        int inputMinutes,
        int& hours,
        int& minutes);

private:
    /**
     * @brief Finds the time period with the maximum number of visitors.
     * @param mapTimeToVisitorAction The map of visitor actions over time.
     * @param maxVisitorCount Output parameter for the maximum number of visitors.
     * @param maxVisitorRanges Output parameter for the time ranges with the maximum number of visitors.
     */
    static void FindMaxVisitors(
        const map<int, int>& mapTimeToVisitorAction,
        int& maxVisitorCount,
        vector<pair<int, int>>& maxVisitorRanges);

    /**
     * @brief Converts hours and minutes to total minutes.
     * @param hours The hours component.
     * @param minutes The minutes component.
     * @return Total minutes.
     */
    static int convertToMinutes(
        int hours,
        int minutes);

    /**
     * @brief Parses a time string into total minutes.
     * @param timeStr The time string in "hh:mm" format.
     * @return Total minutes.
     */
    static int parseTime(const string& timeStr);

    /**
     * @brief Maps entering and leaving times of visitors to visitor actions.
     * @param filePath The path to the input file containing visitor times.
     * @return A map where the key is the minute and the value is the visitor count to increment or decrement.
     * @throw std::invalid_argument if the input file cannot be opened.
     */
    static map<int, int> MapTimeToVisitorAction(const string& filePath);

};
