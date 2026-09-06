//T.C : O(m*n)
//S.C : O(m + n)
class Solution {
public:
    typedef unsigned long long ull;
    
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();

        vector<ull> curr(n+1, 0); //Replace dp[i] with curr
        vector<ull> prev(n+1, 0); //Replace dp[i-1] with prev
        
        prev[0] = curr[0] = 1;
        
        for(int i = 1; i<m+1; i++) {
            
            for(int j = 1; j<n+1; j++) {
                
                if(s[i-1] == t[j-1])
                    curr[j] = prev[j-1] + prev[j];
                else
                    curr[j] = prev[j];
            }
            prev = curr;
        }

        return prev[n];
    }
};