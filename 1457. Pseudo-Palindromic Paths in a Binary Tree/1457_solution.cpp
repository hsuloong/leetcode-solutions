#include <iostream>
#include <vector>
#include <queue>
// #include <string>
// #include <utility>
// #include <set>

using namespace std;

/**
 * Definition for a binary tree node.
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        this->pseudoPathCount = 0;
        if (root == nullptr) {
            return 0;
        }
        std::vector<int> hashCounter(10, 0);
        DFS(root, hashCounter);
        return this->pseudoPathCount;
    }

private:
    void DFS(TreeNode* root, std::vector<int> &hashCounter) {
        if (root->left == nullptr && root->right == nullptr) {
            ++hashCounter[root->val];
            JudgePseudo(hashCounter);
            --hashCounter[root->val];
            return;
        }
        
        if (root->left != nullptr) {
            ++hashCounter[root->val];
            DFS(root->left, hashCounter);
            --hashCounter[root->val];
        }
        if (root->right != nullptr) {
            ++hashCounter[root->val];
            DFS(root->right, hashCounter);
            --hashCounter[root->val];
        }
    }
    void JudgePseudo(const std::vector<int>& hashCounter) {
        int oddCount = 0;
        for (int i = 0; i < 10; i++) {
            if (hashCounter[i] % 2 != 0) {
                ++oddCount;
            }
        }

        if (oddCount <= 1) {
            ++(this->pseudoPathCount);
        }
    }
    int pseudoPathCount;
};

void PrintResult(const int expect, const int actual)
{
    std::cout << (expect == actual ? "Correct" : "Wrong") << "\n";
}

TreeNode *BuildTestTree(const std::vector<char> &srcData)
{
    if (srcData.size() <= 0 || srcData.front() == 'N') {
        return nullptr;
    }
    auto rootNode = new TreeNode(srcData[0]-'0');
    std::queue<TreeNode *> nodeQueue;
    nodeQueue.push(rootNode);
    size_t index = 1;
    while (index < srcData.size()) {
        if (srcData[index] != 'N') {
            auto leftNode = new TreeNode(srcData[index]-'0');
            nodeQueue.front()->left = leftNode;
            nodeQueue.push(leftNode);
        }
        ++index;
        if (index < srcData.size() && srcData[index] != 'N') {
            auto rightNode = new TreeNode(srcData[index]-'0');
            nodeQueue.front()->right = rightNode;
            nodeQueue.push(rightNode);
        }
        ++index;
        nodeQueue.pop();
    }
    return rootNode;
}

void DeleteTestTree(TreeNode *root)
{
    if (root == nullptr) {
        return;
    }
    DeleteTestTree(root->left);
    DeleteTestTree(root->right);
    delete root;
}

int main(int argc, char *argv[])
{
    typedef TreeNode * TEST_TYPE;
    typedef int        RESULT_TYPE;

    TEST_TYPE   testCase1{BuildTestTree({'2', '3', '1', '3', '1', 'N', '1'})};
    RESULT_TYPE result1{2};

    TEST_TYPE   testCase2{BuildTestTree({'2', '1', '1', '1', '3', 'N', 'N', 'N', 'N', 'N', '1'})};
    RESULT_TYPE result2{1};

    TEST_TYPE   testCase3 = {BuildTestTree({'9'})};
    RESULT_TYPE result3{1};

    Solution solution1457;
    std::cout << "==========BeginFunc1Test==========\n";
    PrintResult(result1, solution1457.pseudoPalindromicPaths(testCase1));
    PrintResult(result2, solution1457.pseudoPalindromicPaths(testCase2));
    PrintResult(result3, solution1457.pseudoPalindromicPaths(testCase3));
    std::cout << "===========EndFunc1Test===========\n";

    DeleteTestTree(testCase1);
    DeleteTestTree(testCase2);
    DeleteTestTree(testCase3);
    return 0;
}