#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

using namespace std;

class Solution {
public:
    string arrangeWords(string text) {
        if (text.empty()) {
            return text;
        }

        text.front() = std::tolower(text.front());

        std::regex reg(R"(\s+)");
        std::sregex_token_iterator first{text.begin(), text.end(), reg, -1}, last;
    
        std::vector<std::string> spliResult{first, last};

        std::stable_sort(spliResult.begin(),
                         spliResult.end(),
                         [] (const std::string &firstEle, const string &secondEle) {
                            return firstEle.length() < secondEle.length();}
                        );

        std::string result;
        std::for_each(spliResult.begin(),
                      spliResult.end(),
                      [&result] (const std::string &word) {
                          result += (result.empty() ? "" : " ") + word;}
                     );

        result.front() = std::toupper(result.front());
        return std::move(result);
    }
};

void PrintResult(const string &expect, const string &actual)
{
    std::cout << (expect == actual ? "Correct" : "Wrong") << "\n";
}

int main(int argc, char *argv[])
{
    Solution solution1451;

    std::cout << "==========BeginFunc1Test==========\n";
    PrintResult("Is cool leetcode", solution1451.arrangeWords("Leetcode is cool"));
    PrintResult("On and keep calm code", solution1451.arrangeWords("Keep calm and code on"));
    PrintResult("To be or to be not", solution1451.arrangeWords("To be or not to be"));
    std::cout << "===========EndFunc1Test===========\n";

    return 0;
}

