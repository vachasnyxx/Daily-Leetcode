class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> freq; 
        // freq[prefixsum] = how many times this prefix sum has occurred
        // This helps us quickly check if (prefixsum - k) existed before

        freq[0] = 1; // base case: prefix sum = 0 occurs once

        int prefixsum = 0; // running sum of elements
        int count = 0;     // number of valid subarrays

        for (int num : nums) {
            prefixsum += num; // update running sum

            // If prefixsum - k exists, it means there’s a subarray ending here with sum = k
            if (freq.find(prefixsum - k) != freq.end()) {
                count += freq[prefixsum - k];
            }

            // Record this prefix sum occurrence
            freq[prefixsum]++;
        }

        return count;
    }
};




/// Brute force approach
// class Solution {
// public:
//     int subarraySum(vector<int>& nums, int k) {
//         int count = 0;
//         for(int l = 0; l<nums.size(); l++){
//             int sum =0;
//             for(int r = l; r < nums.size(); r++){
//                 sum+= nums[r];
//                 if(sum == k){
//                     count++;
//                 }
//             }
//         }
//         return count;
//     }
// };