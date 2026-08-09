class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        int minr = 0, minc = 0;
        int maxr = rows - 1, maxc = cols - 1;
        int tne = rows * cols;   // total number of elements
        int count = 0;

        vector<int> v;

        while (minr <= maxr && minc <= maxc) {
            // right
            for (int j = minc; j <= maxc && count < tne; j++) {
                v.push_back(matrix[minr][j]);
                count++;
            }
            minr++;

            // down
            for (int i = minr; i <= maxr && count < tne; i++) {
                v.push_back(matrix[i][maxc]);
                count++;
            }
            maxc--;

            // left
            if (minr <= maxr) {
                for (int j = maxc; j >= minc && count < tne; j--) {
                    v.push_back(matrix[maxr][j]);
                    count++;
                }
                maxr--;
            }

            // up
            if (minc <= maxc) {
                for (int i = maxr; i >= minr && count < tne; i--) {
                    v.push_back(matrix[i][minc]);
                    count++;
                }
                minc++;
            }
        }
        return v;
    }
};
