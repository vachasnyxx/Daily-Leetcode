class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();

        int l = 0;

        int h = n - 1;

        while (l < h) {
            int mid = l + (h - l) / 2;
            // right side mein even hai ya odd

            bool is_even;

            if ((h - mid) % 2 == 0) {
                is_even = true;
            } else {
                is_even = false;
            }

            // check your bagal wala element (mid+1)

            if (nums[mid] == nums[mid + 1]) {
                if (is_even) {
                    l = mid + 2;
                } else {
                    h = mid - 1;
                }
            } else { // nums[mid] != nums[mid+1]   {,.,.,.,.,.a,b,b,c}
                if (is_even) {
                    h = mid;
                } else {
                    l = mid + 1;
                }
            }
        }
        return nums[h];
    }
};