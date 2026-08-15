class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) return false;

        // Maps to track character mappings
        vector<int> mapS(256, -1);
        vector<int> mapT(256, -1);

        for (int i = 0; i < s.size(); i++) {
            char c1 = s[i];
            char c2 = t[i];

            // If mapping already exists, check consistency
            if (mapS[c1] == -1 && mapT[c2] == -1) {
                mapS[c1] = c2;
                mapT[c2] = c1;
            } else {
                if (mapS[c1] != c2 || mapT[c2] != c1) {
                    return false;
                }
            }
        }
        return true;
    }
};
