class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {           // T.C = O(n)   S.C = O(n)
        deque<int> dq;
        vector<int> res;

        // ist window

        for (int i = 0; i < k; i++) {                // T.C = O(k)
            while (dq.size() > 0 && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }

        for(int i=k; i<nums.size(); i++){               // T.C = O(n-k)
            res.push_back(nums[dq.front()]);

            // remove not part of current window

            while(dq.size() > 0 && dq.front() <= i-k){
                dq.pop_front();
            }

            //remove the smaller values
            while (dq.size() > 0 && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);
        }

        res.push_back(nums[dq.front()]);

        return res;
    }
};