class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {   // T.C = O(n), S.C = O(n)
        deque<int> dq;   // stores indices of useful elements in current window
        vector<int> res; // stores final maximums of each window

        // Step 1: Process the first window of size k
        for (int i = 0; i < k; i++) {
            // Remove all indices whose corresponding values are <= current value
            // because they can never be maximum if current value is larger
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i); // push current index
        }

        // Step 2: Process the rest of the array
        for (int i = k; i < nums.size(); i++) {
            // Front of deque always holds index of maximum element for previous window
            res.push_back(nums[dq.front()]);

            // Remove indices that are out of this window (i-k is left boundary)
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // Remove all indices whose values are <= current value
            // because current value dominates them
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i); // push current index
        }

        // Step 3: Add maximum for the last window
        res.push_back(nums[dq.front()]);

        return res;
    }
};
