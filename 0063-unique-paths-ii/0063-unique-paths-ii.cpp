#include <vector>

class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        
        // Use a 1D vector to store path counts for the current row
        std::vector<long long> dp(n, 0);
        
        // Starting point
        dp[0] = (obstacleGrid[0][0] == 0) ? 1 : 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0; // Obstacle blocks the path
                } else if (j > 0) {
                    dp[j] += dp[j - 1]; // Add paths coming from the left
                }
            }
        }
        
        return dp[n - 1];
    }
};
