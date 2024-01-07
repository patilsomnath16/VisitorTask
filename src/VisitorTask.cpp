#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <vector>

using namespace std;

int convertToMinutes(
    int hours, 
    int minutes);
int parseTime(const string& timeStr);
void convertMinutesToHoursAndMinutes(
    int inputMinutes, 
    int& hours, 
    int& minutes);
map<int, int> MapTimeToVisitorAction(const string& filePath);
void FindMaxVisitors(
    map<int, int> mapTimeToVisitorAction,
    int& maxVisitorCount,
    vector<pair<int, int>>& maxVisitorRanges);

int main(int argc, char* argv[]) {
    //if (argc != 2) {
    //    cerr << "Usage: " << argv[0] << " <input_file>" << endl;
    //    return 1;
    //}

    //map<int, int> mapTimeToVisitorAction{ MapTimeToVisitorAction(argv[1])};  // Key: minute, Value: visitor count

    map<int, int> mapTimeToVisitorAction{ MapTimeToVisitorAction("C:\\1\\VisitorTask\\VisitorTask\\visitors 1.txt") };  // Key: minute, Value: visitor count

    int maxVisitorCount{ -1 };
    vector<pair<int, int>> maxVisitorRange;
    FindMaxVisitors(mapTimeToVisitorAction, maxVisitorCount, maxVisitorRange);

    cout << "Time ranges : " << endl;

    for (const auto& range : maxVisitorRange)
    {
        int startHours{ -1 };
        int startMinutes{ -1 };
        convertMinutesToHoursAndMinutes(range.first, startHours, startMinutes);

        int endHours{ -1 };
        int endMinutes{ -1 };
        convertMinutesToHoursAndMinutes(range.second, endHours, endMinutes);
        cout << startHours << ":" << startMinutes << "-" << endHours << ":" << endMinutes << ";" << maxVisitorCount <<  endl;
    }
    return 0;
}

int convertToMinutes(int hours, int minutes)
{
    return hours * 60 + minutes;
}

int parseTime(const string& timeStr) {
    int hours, minutes;
    char colon;
    istringstream stream(timeStr);
    stream >> hours >> colon >> minutes;
    return convertToMinutes(hours, minutes);
}

void convertMinutesToHoursAndMinutes(int inputMinutes, int& hours, int& minutes) {

    hours = inputMinutes / 60;
    minutes = inputMinutes % 60;
}

map<int, int> MapTimeToVisitorAction(const string& filePath)
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
}

void FindMaxVisitors(
    map<int, int> mapTimeToVisitorAction, 
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

