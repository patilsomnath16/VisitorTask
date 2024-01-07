Algorithm Overview:
The algorithm maintains a running count of visitors as it iterates through the minutes. It dynamically updates the maximum visitor count and keeps track of the corresponding time ranges

MapTimeToVisitorAction:
Input: Path to the input file containing visitor times.
Output: A map where the key is the minute, and the value is the visitor count to increment or decrement.
Algorithm:
Open the input file.
Read each line from the file, which represents the entering and leaving times of a visitor.
Parse the start and end times into total minutes.
For each visitor entry, increment the count for the start time and decrement the count for the end time + 1.
Close the input file.
Return the generated map.
cpp
map<int, int> VisitorCounter::MapTimeToVisitorAction(const string& filePath);

FindMaxVisitors:
Input: A map of visitor actions over time.
Output: The maximum number of visitors and the time ranges with the maximum number of visitors.
Algorithm:
Initialize variables for tracking the maximum visitor count, current visitor count, and time ranges.
Iterate over the map entries, updating the current visitor count based on the action.
If the current count surpasses the maximum count, update the maximum count and clear the time ranges.
If the current count equals the maximum count, add the current time to the time ranges.
For each start time in the time ranges, find the corresponding end time and add the range to the output.
Return the maximum visitor count and time ranges.
void VisitorCounter::FindMaxVisitors(
    const map<int, int>& mapTimeToVisitorAction,
    int& maxVisitorCount,
    vector<pair<int, int>>& maxVisitorRanges);

ConvertMinutesToHoursAndMinutes:
Input: Total minutes.
Output: Hours and minutes components.
Algorithm:
Calculate the hours by dividing the total minutes by 60.
Calculate the remaining minutes by taking the modulus of the total minutes.
Return the calculated hours and minutes.
cpp
void VisitorCounter::ConvertMinutesToHoursAndMinutes(int inputMinutes, int& hours, int& minutes);

Usage in Main:
Main Function:
Input: Command-line arguments or a hardcoded file path.
Output: Display the time ranges with the maximum number of visitors.
Algorithm:
Call FindMaxVisitors using the provided visitor log file path.
Display the calculated time ranges along with the maximum visitor count.
cpp
int main(int argc, char* argv[]);

