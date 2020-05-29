#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <limits>
// #include <string>
// #include <set>
// #include <functional>

using namespace std;

class Solution {
public:
    int numPoints(vector<vector<int>>& points, int r) {
        const auto problemSize = points.size();
        std::vector<std::vector<int>> dpArray(problemSize, std::vector<int>(problemSize, 0));

        std::sort(points.begin(),
                  points.end(),
                  [] (const std::vector<int> &firstElem, const std::vector<int> &secondElem) {
                      return firstElem[0] < secondElem[0]|| ((firstElem[0] == secondElem[0])  && firstElem[1] < secondElem[1]);
                  });

        int maxCount = 0;
        for (size_t i = 0; i < problemSize; i++) {
            for (size_t j = i+1; j < problemSize; j++) {
                std::vector<std::vector<double>> circleCenter;
                GetCircleCenter(points[i], points[j], r, circleCenter);
                if (circleCenter.empty()) {
                    break;
                }
                dpArray[i][j] = dpArray[j][i] = GetMaxCount(circleCenter, points, r);
                maxCount = maxCount > dpArray[i][j] ? maxCount : dpArray[i][j];
            }
        }
        return maxCount > 0 ? maxCount : 1;
    }
private:
    double CalculateDistance(const std::vector<double> &firstPoint, const std::vector<double> &secondPoint) {
        const auto disX = firstPoint[0] - secondPoint[0];
        const auto disY = firstPoint[1] - secondPoint[1];
        return std::sqrt(disX*disX*1.0 + disY*disY*1.0);
    }

    void GetCircleCenter(const std::vector<int> &firstPoint, const std::vector<int> &secondPoint,
                         const int radius, std::vector<std::vector<double>> &circleCenter) {

        double distance = CalculateDistance(std::vector<double>{firstPoint[0]*1.0, firstPoint[1]*1.0},
                                            std::vector<double>{secondPoint[0]*1.0, secondPoint[1]*1.0});

        if (std::fabs(distance-2.0*radius) < 1.0e-4) {
            circleCenter.push_back({(firstPoint[0]+secondPoint[0])/2.0, (firstPoint[1]+secondPoint[1])/2.0});
            return;
        }

        if (distance > (2.0*radius + 1.0e-4) || distance < 1.0e-4) {
            return;
        }

        double midX = (firstPoint[0]+secondPoint[0]) / 2.0;
        double midY = (firstPoint[1]+secondPoint[1]) / 2.0;

        double baseX = std::sqrt(std::pow(radius, 2)-std::pow((distance/2), 2))*(firstPoint[1]-secondPoint[1])/distance; //calculate once
        double baseY = std::sqrt(std::pow(radius, 2)-std::pow((distance/2), 2))*(secondPoint[0]-firstPoint[0])/distance; //calculate once

        circleCenter.push_back({midX+baseX, midY+baseY});

        circleCenter.push_back({midX-baseX, midY-baseY});
    }

    int GetMaxCount(const std::vector<std::vector<double>> &circleCenter, const vector<vector<int>>& points, const int radius) {
        auto centerSize = circleCenter.size();
        std::vector<int> resultCount(centerSize, 0);
    
        for (size_t i = 0; i < centerSize; i++) {
            auto &oneCenter = circleCenter[i];
            for (auto &point : points) {
                auto tmpDistance = CalculateDistance(oneCenter, std::vector<double>{point[0]*1.0, point[1]*1.0});
                if (tmpDistance < radius + 1.0e-4) {
                    ++resultCount[i];
                }
            }
        }
        return *std::max_element(resultCount.begin(), resultCount.end());
    }
};


void PrintResult(const int expect, const int actual)
{
    std::cout << (expect == actual ? "Correct" : "Wrong") << "\n";
}

int main(int argc, char *argv[])
{
    typedef std::pair<std::vector<std::vector<int>>, int> TEST_PAIR;

    TEST_PAIR testCase1{{{-2,0},{2,0},{0,2},{0,-2}}, 2};
    int result1{4};

    TEST_PAIR testCase2{{{-3,0},{3,0},{2,6},{5,4},{0,9},{7,8}}, 5};
    int result2{5};

    TEST_PAIR testCase3 = {{{-2,0},{2,0},{0,2},{0,-2}}, 1};
    int result3{1};

    TEST_PAIR testCase4{{{1,2},{3,5},{1,-1},{2,3},{4,1},{1,3}}, 2};
    int result4{4};

    Solution solution1453;
    std::cout << "==========BeginFunc1Test==========\n";
    PrintResult(result1, solution1453.numPoints(testCase1.first, testCase1.second));
    PrintResult(result2, solution1453.numPoints(testCase2.first, testCase2.second));
    PrintResult(result3, solution1453.numPoints(testCase3.first, testCase3.second));
    PrintResult(result4, solution1453.numPoints(testCase4.first, testCase4.second));
    std::cout << "===========EndFunc1Test===========\n";

    // std::cout << "\n\n";

    // std::cout << "==========BeginFunc2Test==========\n";
    // PrintResult(result1, solution1452.numPoints(testCase1));
    // PrintResult(result2, solution1452.numPoints(testCase2));
    // PrintResult(result3, solution1452.numPoints(testCase3));
    // PrintResult(result4, solution1452.numPoints(testCase4));
    // std::cout << "===========EndFunc2Test===========\n";
    return 0;
}