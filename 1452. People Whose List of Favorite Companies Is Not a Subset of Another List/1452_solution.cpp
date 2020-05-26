#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> peopleIndexes(const vector<vector<string>>& favoriteCompanies) {
        auto problemSize = favoriteCompanies.size();
        std::vector<std::vector<int>> dpArray(problemSize, std::vector<int>(problemSize, 0));
        std::vector<bool> resultArray(problemSize, false);

        std::vector<std::set<std::string>> setFormat;
        Convert2Set(favoriteCompanies, setFormat);

        for (size_t i = 0; i < problemSize; i++) {
            for (size_t j = 0; j < problemSize; j++) {
                if (dpArray[i][j] != 0) {
                    continue;
                }
                if (i == j) {
                    dpArray[i][j] = 5;
                    continue;
                }
                if (resultArray[i]) {
                    continue;
                }
                // 1:NotSubSizeSmaller 2:NotSubSizeEqual 3:NotSubSizeLarger
                // 4:SubSizeSmaller    5:SubSizeEqual(Equal)
                auto subFlag = SubSetCalc(setFormat[j], setFormat[i]);
                dpArray[i][j] = subFlag;
                switch (subFlag) {
                    case 1: dpArray[j][i] = 3; break;
                    case 2: dpArray[j][i] = 2; break;
                    case 3: break;
                    case 4: dpArray[j][i] = 3; resultArray[i] = true; break;
                    case 5: dpArray[j][i] = 5; resultArray[i] = true; resultArray[j] = true; break;
                    default: break;
                }
            }
        }

        std::vector<int> result;
        for (size_t i = 0; i < resultArray.size(); i++) {
            if (!resultArray[i]) {
                result.push_back(int(i));
            }
        }
        return std::move(result);
    }
    vector<int> peopleIndexes2(const vector<vector<string>>& favoriteCompanies) {
        auto problemSize = favoriteCompanies.size();
        std::vector<std::vector<int>> dpArray(problemSize, std::vector<int>(problemSize, 0));
        std::vector<bool> resultArray(problemSize, false);

        std::vector<std::set<size_t>> numberFormat;
        Convert2Number(favoriteCompanies, numberFormat);

        for (size_t i = 0; i < problemSize; i++) {
            for (size_t j = 0; j < problemSize; j++) {
                if (dpArray[i][j] != 0) {
                    continue;
                }
                if (i == j) {
                    dpArray[i][j] = 5;
                    continue;
                }
                if (resultArray[i]) {
                    continue;
                }
                // 1:NotSubSizeSmaller 2:NotSubSizeEqual 3:NotSubSizeLarger
                // 4:SubSizeSmaller    5:SubSizeEqual(Equal)
                auto subFlag = SubSetCalc(numberFormat[j], numberFormat[i]);
                dpArray[i][j] = subFlag;
                switch (subFlag) {
                    case 1: dpArray[j][i] = 3; break;
                    case 2: dpArray[j][i] = 2; break;
                    case 3: break;
                    case 4: dpArray[j][i] = 3; resultArray[i] = true; break;
                    case 5: dpArray[j][i] = 5; resultArray[i] = true; resultArray[j] = true; break;
                    default: break;
                }
            }
        }

        std::vector<int> result;
        for (size_t i = 0; i < resultArray.size(); i++) {
            if (!resultArray[i]) {
                result.push_back(int(i));
            }
        }
        return std::move(result);
    }
private:
    void Convert2Set(const vector<vector<string>>& favoriteCompanies, std::vector<std::set<std::string>> &setFormat) {
        for (auto const &vecItem : favoriteCompanies) {
            std::set<std::string> tmpSet;
            for (auto const &strItem : vecItem) {
                tmpSet.insert(strItem);
            }
            setFormat.push_back(std::move(tmpSet));
        }
    }
    int SubSetCalc(const std::set<std::string> &srcSet, std::set<std::string> &judgeSet) {
        // 1:NotSubSizeSmaller 2:NotSubSizeEqual 3:NotSubSizeLarger
        // 4:SubSizeSmaller    5:SubSizeEqual(Equal)
        if (judgeSet.size() > srcSet.size()) {
            return 3;
        }

        bool isSubSet = true;
        for (const auto &item : judgeSet) {
            if (srcSet.find(item) == srcSet.end()) {
                isSubSet = false;
                break;
            }
        }

        // 1:NotSubSizeSmaller 2:NotSubSizeEqual 3:NotSubSizeLarger
        // 4:SubSizeSmaller    5:SubSizeEqual(Equal)
		if (!isSubSet) {
			return srcSet.size() != judgeSet.size() ? 1 : 2;
        }
		else {
			return srcSet.size() != judgeSet.size() ? 4 : 5;
		}
    }
    void Convert2Number(const vector<vector<string>>& favoriteCompanies, std::vector<std::set<size_t>> &numberFormat) {
        static std::hash<std::string> hashFunc;
        for (auto const &vecItem : favoriteCompanies) {
            std::set<size_t> tmpSet;
            for (auto const &strItem : vecItem) {
                tmpSet.insert(hashFunc(strItem));
            }
            numberFormat.push_back(std::move(tmpSet));
        }
    }
    int SubSetCalc(const std::set<size_t> &srcSet, const std::set<size_t> &judgeSet) {
        // 1:NotSubSizeSmaller 2:NotSubSizeEqual 3:NotSubSizeLarger
        // 4:SubSizeSmaller    5:SubSizeEqual(Equal)
        if (judgeSet.size() > srcSet.size()) {
            return 3;
        }

        bool isSubSet = true;
        for (const auto &item : judgeSet) {
            if (srcSet.find(item) == srcSet.end()) {
                isSubSet = false;
                break;
            }
        }

        // 1:NotSubSizeSmaller 2:NotSubSizeEqual 3:NotSubSizeLarger
        // 4:SubSizeSmaller    5:SubSizeEqual(Equal)
		if (!isSubSet) {
			return srcSet.size() != judgeSet.size() ? 1 : 2;
        }
		else {
			return srcSet.size() != judgeSet.size() ? 4 : 5;
		}
    }
};

void PrintResult(const std::vector<int> &expect, const std::vector<int> &actual)
{
    std::cout << (expect == actual ? "Correct" : "Wrong") << "\n";
}

int main(int argc, char *argv[])
{
    typedef std::vector<vector<string>> TEST_VEC;
    typedef std::vector<int> RESULT_VEC;

    TEST_VEC testCase1{{"leetcode","google","facebook"},{"google","microsoft"},{"google","facebook"},{"google"},{"amazon"}};
    RESULT_VEC result1{0,1,4};

    TEST_VEC testCase2{{"leetcode","google","facebook"},{"leetcode","amazon"},{"facebook","google"}};
    RESULT_VEC result2{0,1};

    TEST_VEC testCase3 = {{"leetcode"},{"google"},{"facebook"},{"amazon"}};
    RESULT_VEC result3{0,1,2,3};

    TEST_VEC testCase4{{"nxaqhyoprhlhvhyojanr","ovqdyfqmlpxapbjwtssm","qmsbphxzmnvflrwyvxlc",
                        "udfuxjdxkxwqnqvgjjsp","yawoixzhsdkaaauramvg","zycidpyopumzgdpamnty"},
                       {"nxaqhyoprhlhvhyojanr","ovqdyfqmlpxapbjwtssm","udfuxjdxkxwqnqvgjjsp",
                        "yawoixzhsdkaaauramvg","zycidpyopumzgdpamnty"},
                       {"ovqdyfqmlpxapbjwtssm","qmsbphxzmnvflrwyvxlc","udfuxjdxkxwqnqvgjjsp",
                        "yawoixzhsdkaaauramvg","zycidpyopumzgdpamnty"}};
    RESULT_VEC result4{0};

    Solution solution1452;
    std::cout << "==========BeginFunc1Test==========\n";
    PrintResult(result1, solution1452.peopleIndexes(testCase1));
    PrintResult(result2, solution1452.peopleIndexes(testCase2));
    PrintResult(result3, solution1452.peopleIndexes(testCase3));
    PrintResult(result4, solution1452.peopleIndexes(testCase4));
    std::cout << "===========EndFunc1Test===========\n";

    std::cout << "\n\n";

    std::cout << "==========BeginFunc2Test==========\n";
    PrintResult(result1, solution1452.peopleIndexes2(testCase1));
    PrintResult(result2, solution1452.peopleIndexes2(testCase2));
    PrintResult(result3, solution1452.peopleIndexes2(testCase3));
    PrintResult(result4, solution1452.peopleIndexes2(testCase4));
    std::cout << "===========EndFunc2Test===========\n";
    return 0;
}