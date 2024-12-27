#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0; // Handle empty array case

        int uniqueIndex = 0; // Pointer for the position of unique elements

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[uniqueIndex]) {
                ++uniqueIndex;           // Move the unique pointer forward
                nums[uniqueIndex] = nums[i]; // Update the unique position
            }
        }

        return uniqueIndex + 1; // Number of unique elements
    }
};

int main() {
    vector<int> nums = {1, 1, 2, 3, 3, 4, 5, 5, 6};

    Solution solution;
    int uniqueCount = solution.removeDuplicates(nums);

    // Output the results
    cout << "Number of unique elements: " << uniqueCount << endl;
    cout << "Array after removing duplicates: ";
    for (int i = 0; i < uniqueCount; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}
