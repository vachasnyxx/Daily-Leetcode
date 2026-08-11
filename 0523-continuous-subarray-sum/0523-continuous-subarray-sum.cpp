class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp; 
        mp[0] = -1; // handle case when prefix sum itself is divisible by k

        int prefixSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            prefixSum += nums[i];
            
            // take modulo to reduce large sums
            int mod = (k == 0) ? prefixSum : prefixSum % k;

            // if this mod was seen before, check subarray length
            if (mp.find(mod) != mp.end()) {
                if (i - mp[mod] >= 2) return true;
            } else {
                // store first occurrence of this mod
                mp[mod] = i;
            }
        }
        return false;
    }
};






// Brute force
// class Solution {
// public:
//     bool checkSubarraySum(vector<int>& nums, int k) {
//         int n  = nums.size();

//         for(int i=0; i < n-1; i++){
//             int sum  = nums[i];
//             for(int j = i+1; j<n; j++){
//                 sum += nums[j];
//                 if(sum % k == 0) return true;
//             }
//         }
//         return false;
//     }
// };