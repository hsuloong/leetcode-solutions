#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int busyStudent(const vector<int> &startTime, const vector<int> &endTime, const int queryTime) {
        int counter = 0;
        for (size_t i = 0; i < startTime.size(); i++) {
            if (queryTime >= startTime[i] && queryTime <= endTime[i]) {
                ++counter;
            }
        }
        return counter;
    }

    int busyStudent2(const vector<int> &startTime, const vector<int> &endTime, const int queryTime) {
        std::map<int, int> counterMap;
        for (size_t i = 0; i < startTime.size(); i++) {
            for (int j = startTime[i]; j <= endTime[i]; j++) {
                ++counterMap[j];
            }
        }
        auto iter = counterMap.find(queryTime);
        return iter == counterMap.end() ? 0 : iter->second;
    }
};

void PrintResult(const int expect, const int actual)
{
    std::cout << (expect == actual ? "Correct" : "Wrong") << "\n";
}

int main(int argc, char *argv[])
{
    Solution solution1450;
    std::cout << "==========BeginFunc1Test==========\n";
    PrintResult(1, solution1450.busyStudent({1,2,3}, {3,2,7}, 4));
    PrintResult(1, solution1450.busyStudent({4}, {4}, 4));
    PrintResult(0, solution1450.busyStudent({4}, {4}, 5));
    PrintResult(0, solution1450.busyStudent({1,1,1,1}, {1,3,2,4}, 7));
    PrintResult(5, solution1450.busyStudent({9,8,7,6,5,4,3,2,1}, {10,10,10,10,10,10,10,10,10}, 5));
    std::cout << "===========EndFunc1Test===========\n";

    std::cout << "\n\n";

    std::cout << "==========BeginFunc2Test==========\n";
    PrintResult(1, solution1450.busyStudent2({1,2,3}, {3,2,7}, 4));
    PrintResult(1, solution1450.busyStudent2({4}, {4}, 4));
    PrintResult(0, solution1450.busyStudent2({4}, {4}, 5));
    PrintResult(0, solution1450.busyStudent2({1,1,1,1}, {1,3,2,4}, 7));
    PrintResult(5, solution1450.busyStudent2({9,8,7,6,5,4,3,2,1}, {10,10,10,10,10,10,10,10,10}, 5));
    std::cout << "===========EndFunc2Test===========\n";
    return 0;
}
