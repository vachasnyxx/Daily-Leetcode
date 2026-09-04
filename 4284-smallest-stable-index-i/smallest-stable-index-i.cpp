class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> suffMin(n);
        
        // Step 1: Precompute suffix minimums
        suffMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffMin[i] = min(suffMin[i + 1], nums[i]);
        }
        
        // Step 2: Traverse with prefix maximum
        int prefMax = nums[0];
        for (int i = 0; i < n; ++i) {
            prefMax = max(prefMax, nums[i]);
            int instability = prefMax - suffMin[i];
            if (instability <= k) {
                return i;  // return smallest stable index
            }
        }
        return -1;
    }
};
