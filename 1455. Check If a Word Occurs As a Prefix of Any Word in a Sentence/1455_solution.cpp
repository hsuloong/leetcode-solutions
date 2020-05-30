#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        if (sentence.empty()) {
            return -1;
        }

        size_t findIndex = 0;
        do {
            findIndex = sentence.find(searchWord, findIndex);
            if (findIndex != std::string::npos && (findIndex == 0 || sentence[findIndex-1] == ' ')) {
                break;
            }
            if (findIndex != std::string::npos) {
                findIndex += searchWord.size();
            }
        } while(findIndex != std::string::npos);

        if (findIndex == std::string::npos) {
            return -1;
        }

        int wordIndex = 0;
        size_t index = 0;
        if (sentence.front() == ' ') {
            while (index < sentence.size() && sentence[index] == ' ') {
                ++index;
            }
            wordIndex;
        }
        ++wordIndex;
        if (index == findIndex) {
            return wordIndex;
        }

        while (index != std::string::npos) {
            index = sentence.find(" ", index);
            if (index != std::string::npos) {
                while (index < sentence.size() && sentence[index] == ' ') {
                    ++index;
                }
            }
            ++wordIndex;
            if (index == findIndex) {
                return wordIndex;
            }
        }

        return -1;
    }
};


void PrintResult(const int expect, const int actual)
{
    std::cout << (expect == actual ? "Correct" : "Wrong") << "\n";
}

int main(int argc, char *argv[])
{
    typedef std::pair<std::string, std::string> TEST_PAIR;

    TEST_PAIR testCase1{"i love eating burger", "burg"};
    int result1{4};

    TEST_PAIR testCase2{"this problem is an easy problem", "pro"};
    int result2{2};

    TEST_PAIR testCase3 = {"i am tired", "you"};
    int result3{-1};

    TEST_PAIR testCase4{"i use triple  pillow", "pill"};
    int result4{4};

    TEST_PAIR testCase5{"hello from the other side", "they"};
    int result5{-1};

    TEST_PAIR testCase6{"hellohello hellohellohello", "ell"};
    int result6{-1};

    Solution solution1455;
    std::cout << "==========BeginFunc1Test==========\n";
    PrintResult(result1, solution1455.isPrefixOfWord(testCase1.first, testCase1.second));
    PrintResult(result2, solution1455.isPrefixOfWord(testCase2.first, testCase2.second));
    PrintResult(result3, solution1455.isPrefixOfWord(testCase3.first, testCase3.second));
    PrintResult(result4, solution1455.isPrefixOfWord(testCase4.first, testCase4.second));
    PrintResult(result5, solution1455.isPrefixOfWord(testCase5.first, testCase5.second));
    PrintResult(result6, solution1455.isPrefixOfWord(testCase6.first, testCase6.second));
    std::cout << "===========EndFunc1Test===========\n";

    return 0;
}