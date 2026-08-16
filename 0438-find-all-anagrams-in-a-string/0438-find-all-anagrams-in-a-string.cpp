class Solution {
public:
    bool allZero(vector<int>& counter) {
        for (int& i : counter) {
            if (i != 0) return false;
        }
        return true;
    }

    vector<int> findAnagrams(string txt, string pat) {
        int n = txt.size();
        int k = pat.size();
        vector<int> counter(26, 0);
        vector<int> ans;

        // count the freq of each char in pat
        for (char ch : pat) {
            counter[ch - 'a']++;
        }

        int i = 0, j = 0;
        while (j < n) {
            counter[txt[j] - 'a']--;

            if (j - i + 1 == k) {
                if (allZero(counter)) {
                    ans.push_back(i); // store starting index
                }
                counter[txt[i] - 'a']++; // slide window
                i++;
            }
            j++;
        }
        return ans;
    }
};
