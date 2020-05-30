#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        if (s.size() <= 0 || k <= 0) {
            return 0;
        }
        std::set<char> vowelSet{'a', 'e', 'i', 'o', 'u'};
        std::vector<int> dpArray(s.size(), 0);
        int maxResult = 0;
        int maxvowels = 0;
        for (size_t i = 0; i < s.size(); i++) {
            if (vowelSet.find(s[i]) != vowelSet.end()) {
                ++maxvowels;
            }
            if (i+1 > k) {
                if (vowelSet.find(s[i-k]) != vowelSet.end()) {
                    --maxvowels;
                }
            }
            dpArray[i] = maxvowels;
            maxResult = maxResult > maxvowels? maxResult : maxvowels;
        }
        return maxResult;
    }
};

void PrintResult(const int expect, const int actual)
{
    std::cout << (expect == actual ? "Correct" : "Wrong") << "\n";
}

int main(int argc, char *argv[])
{
    typedef std::pair<std::string, int> TEST_PAIR;

    TEST_PAIR testCase1{"abciiidef", 3};
    int result1{3};

    TEST_PAIR testCase2{"aeiou", 2};
    int result2{2};

    TEST_PAIR testCase3 = {"leetcode", 3};
    int result3{2};

    TEST_PAIR testCase4{"rhythms", 4};
    int result4{0};

    TEST_PAIR testCase5{"tryhard", 4};
    int result5{1};

    TEST_PAIR testCase6{"novowels", 1};
    int result6{1};

    Solution solution1456;
    std::cout << "==========BeginFunc1Test==========\n";
    PrintResult(result1, solution1456.maxVowels(testCase1.first, testCase1.second));
    PrintResult(result2, solution1456.maxVowels(testCase2.first, testCase2.second));
    PrintResult(result3, solution1456.maxVowels(testCase3.first, testCase3.second));
    PrintResult(result4, solution1456.maxVowels(testCase4.first, testCase4.second));
    PrintResult(result5, solution1456.maxVowels(testCase5.first, testCase5.second));
    PrintResult(result6, solution1456.maxVowels(testCase6.first, testCase6.second));
    std::cout << "===========EndFunc1Test===========\n";

    return 0;
}