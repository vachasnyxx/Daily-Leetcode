class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        int total = m + n;
        int i = 0;
        int j = 0;

        int prev = 0;
        int curr = 0;

        for (int count = 0; count <= total / 2; count++) {
            prev = curr;
            if (i < m && j < n) {
                if (nums1[i] <= nums2[j]) {
                    curr = nums1[i++];
                } else {
                    curr = nums2[j++];
                }
            } else if (i < m) {
                curr = nums1[i++];
            } else {
                curr = nums2[j++];
            }
        }
        if (total % 2 == 1) {
            return curr;
        } else {
            return (prev + curr) / 2.0;
        }
    }
};