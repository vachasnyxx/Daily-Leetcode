class Solution {
public:
    int findRightMost(vector<int>& nums, int target, int n) {
        int l = 0, r = n - 1;
        int right_most = -1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) {
                right_most = mid;   // candidate
                l = mid + 1;        // search further right
            } else if (nums[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return right_most;
    }

    int findLeftMost(vector<int>& nums, int target, int n) {
        int l = 0, r = n - 1;
        int left_most = -1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) {
                left_most = mid;   // candidate
                r = mid - 1;       // search further left
            } else if (nums[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return left_most;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        int left_most = findLeftMost(nums, target, n);
        int right_most = findRightMost(nums, target, n);

        return {left_most, right_most};  // ✅ return the pair
    }
};






// class Solution {
// public:
//     vector<int> searchRange(vector<int>& nums, int target) {
//         int n = nums.size();
//         if (n == 0) return {-1, -1};

//         int first = findFirst(nums, target);
//         int last = findLast(nums, target);

//         return {first, last};
//     }

// private:
//     int findFirst(vector<int>& nums, int target) {
//         int low = 0, high = nums.size() - 1, ans = -1;
//         while (low <= high) {
//             int mid = low + (high - low) / 2;
//             if (nums[mid] == target) {
//                 ans = mid;       // candidate
//                 high = mid - 1;  // keep searching left
//             } else if (nums[mid] < target) {
//                 low = mid + 1;
//             } else {
//                 high = mid - 1;
//             }
//         }
//         return ans;
//     }

//     int findLast(vector<int>& nums, int target) {
//         int low = 0, high = nums.size() - 1, ans = -1;
//         while (low <= high) {
//             int mid = low + (high - low) / 2;
//             if (nums[mid] == target) {
//                 ans = mid;       // candidate
//                 low = mid + 1;   // keep searching right
//             } else if (nums[mid] < target) {
//                 low = mid + 1;
//             } else {
//                 high = mid - 1;
//             }
//         }
//         return ans;
//     }
// };
