#include "VisitorCounter.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    //if (argc != 2) {
    //    cerr << "Usage: " << argv[0] << " <input_file>" << endl;
    //    return 1;
    //}

    
    //map<int, int> mapTimeToVisitorAction{ MapTimeToVisitorAction(argv[1])};  // Key: minute, Value: visitor count

    string logFilePath{ "C:\\1\\VisitorTask\\VisitorTask\\visitors 1.txt" };
    int maxVisitorCount{ -1 };
    vector<pair<int, int>> maxVisitorRange;

    VisitorCounter::FindMaxVisitors(logFilePath, maxVisitorCount, maxVisitorRange);

    cout << "Time ranges : " << endl;

    for (const auto& range : maxVisitorRange)
    {
        int startHours{ -1 };
        int startMinutes{ -1 };
        VisitorCounter::ConvertMinutesToHoursAndMinutes(range.first, startHours, startMinutes);

        int endHours{ -1 };
        int endMinutes{ -1 };
        VisitorCounter::ConvertMinutesToHoursAndMinutes(range.second, endHours, endMinutes);
        cout << startHours << ":" << startMinutes << "-" << endHours << ":" << endMinutes << ";" << maxVisitorCount << endl;
    }
    return 0;
}
