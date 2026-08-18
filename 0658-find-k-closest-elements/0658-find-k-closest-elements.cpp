class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // S.C = O(K)
        // T.C = O(logn + KlogK)
        int n = arr.size();
        vector<int> ans(k); // k elements insert larenge
        if (x < arr[0]) {
            for (int i = 0; i < k; i++) {
                ans[i] = arr[i];
            }
            return ans;
        }

        if (x > arr[n - 1]) {
            int i = n - 1;
            int j = k - 1;
            while (j >= 0) {
                ans[j] = arr[i];
                j--;
                i--;
            }
            return ans;
        }
        int low = 0;
        int high = n - 1;
        bool flag = false; // if x is present in arr or not
        int t = 0;         // ans arr mein traverse krne ke liye t use kr lenge
        int mid = -1;
        // binary search
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (arr[mid] == x) {
                flag = true; // present
                ans[t] = arr[mid];
                t++;
                break;
            } else if (arr[mid] > x) {
                high = mid - 1;
            } else
                low = mid + 1;
        }

        int lb = high; // lower bound
        int ub = low;  // upper bound
        if (flag == true) {
            lb = mid - 1;
            ub = mid + 1;
        }
        while (t < k && lb >= 0 && ub <= n - 1) {
            int d1 = abs(x - arr[lb]);
            int d2 = abs(x - arr[ub]);
            if (d1 <= d2) {
                ans[t] = arr[lb];
                // t++; isko bahar likh denge cuz ye dono if and else mein chal
                // rha hai
                lb--;
            } else //(d1 <= d2)
            {
                ans[t] = arr[ub];
                // t++; isko bahar likh denge cuz ye dono if and else mein chal
                // rha hai
                ub++;
            }
            t++;
        }
        if (lb < 0) {
            while (t < k) {
                ans[t] = arr[ub];
                ub++;
                t++;
            }
        }
        if (ub > n-1) {
            while (t < k) {
                ans[t] = arr[lb];
                lb--;
                t++;
            }
        }
        sort(ans.begin(), ans.end());   // WORST CASE MEIN = O(KlogK)
        return ans;
    }
};