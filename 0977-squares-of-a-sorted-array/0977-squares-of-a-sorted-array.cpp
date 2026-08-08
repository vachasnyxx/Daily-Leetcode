class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> neg;
        vector<int> pos;

        // Split negatives and positives
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 0) pos.push_back(nums[i]);
            else neg.push_back(nums[i]);
        }

        // Square negatives and reverse (to make them increasing)
        for (int i = 0; i < neg.size(); i++) {
            neg[i] = neg[i] * neg[i];
        }
        reverse(neg.begin(), neg.end());

        // Square positives
        for (int i = 0; i < pos.size(); i++) {
            pos[i] = pos[i] * pos[i];
        }

        // Merge two sorted arrays
        int low = 0, high = 0, id = 0;
        int l = neg.size(), m = pos.size();
        vector<int> res(l + m);

        while (low < l && high < m) {
            if (neg[low] <= pos[high]) {
                res[id++] = neg[low++];
            } else {
                res[id++] = pos[high++];
            }
        }
        while (low < l) res[id++] = neg[low++];
        while (high < m) res[id++] = pos[high++];

        return res;
    }
};
