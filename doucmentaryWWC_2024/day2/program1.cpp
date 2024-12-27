#include <iostream>
#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* helper(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr; // Base case

        // Choose the middle element as the root
        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[mid]);

        // Recursively construct the left and right subtrees
        root->left = helper(nums, left, mid - 1);
        root->right = helper(nums, mid + 1, right);

        return root;
    }
};

// Function to print the tree using in-order traversal
void inOrderTraversal(TreeNode* root) {
    if (!root) return;
    inOrderTraversal(root->left);
    cout << root->val << " ";
    inOrderTraversal(root->right);
}

int main() {
    vector<int> nums;
    int n;

    // Input: size of the array
    cout << "Enter the number of elements: ";
    cin >> n;

    // Input: sorted array
    cout << "Enter the sorted array elements: ";
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // Convert sorted array to height-balanced BST
    Solution solution;
    TreeNode* root = solution.sortedArrayToBST(nums);

    // Output: in-order traversal of the BST
    cout << "In-order Traversal of BST: ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}



/**************************************************************************************************

Output:
  
In-order Traversal of BST: -10 -3 0 5 9


******************************************************************************************************/
