class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        // step 1 -> finding pivot index
        int idx = -1;
        for(int i = n-2;i>=0;i--){
            if(nums[i]<nums[i+1]){
                idx = i;
                break;
            }
        }
        if(idx == -1){    // if array is already greatest
            reverse(nums.begin(),nums.end());
            return;
        }

        // step 2 -> sorting/reverse after pivot
        reverse(nums.begin()+idx+1, nums.end());
        // step 3 -> finding just greater element than idx
        int j = -1;
        for(int i = idx+1;i<n;i++){
            if(nums[i]>nums[idx]){
                j = i;
                break;
            }
        }
        // step 4 -> swapping idx and j
        int temp = nums[idx];
        nums[idx] = nums[j];
        nums[j] = temp;
        return;
    }
};