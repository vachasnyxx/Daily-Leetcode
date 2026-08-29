class Solution {
public:
    int solve(vector<int>& nums, int target, int i, int currsum) {
        // Base case: if we've processed all elements
        if (i == nums.size()) {
            return (currsum == target) ? 1 : 0;
        }

        // Recursive case: try adding and subtracting nums[i]
        int plus = solve(nums, target, i + 1, currsum + nums[i]);
        int minus = solve(nums, target, i + 1, currsum - nums[i]);

        return plus + minus; // total ways
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        return solve(nums, target, 0, 0);
    }
};
