// class Solution {
// public:
//     vector<vector<int>> generate(int numRows) {
//         vector<vector<int>> v;
//         int m = numRows;
//         for (int i = 1; i <= m; i++) {
//             vector<int> a(i);
//             v.push_back(a);
//         }

//         for (int i = 0; i < m; i++) {
//             for (int j = 0; j <= i; j++) {
//                 if (j == 0 || j == i) {
//                     v[i][j] = 1;
//                 } else {
//                     v[i][j] = v[i - 1][j] + v[i - 1][j - 1];
//                 }
//             }
//         }
//         return v;
//     }
// };


class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> v;   // main container

        for (int i = 0; i < numRows; i++) {
            vector<int> row(i + 1, 1);   // each row has i+1 elements, initialized to 1

            for (int j = 1; j < i; j++) {
                row[j] = v[i - 1][j - 1] + v[i - 1][j];   // recurrence relation
            }

            v.push_back(row);
        }

        return v;
    }
};
