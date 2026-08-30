class Solution {
public:
    vector<vector<string>> result;  // store all solutions
    int N;

    bool isValid(vector<string>& board, int row, int col) {
        // check column upwards
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }
        // check left diagonal upwards
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }
        // check right diagonal upwards
        for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }
        return true;
    }

    void solve(vector<string>& board, int row) {
        if (row == N) {  // base case: placed queens in all rows
            result.push_back(board);
            return;
        }

        for (int col = 0; col < N; col++) {
            if (isValid(board, row, col)) {
                board[row][col] = 'Q';       // place queen
                solve(board, row + 1);       // recurse
                board[row][col] = '.';       // backtrack
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        N = n;
        vector<string> board(n, string(n, '.'));
        solve(board, 0);
        return result;
    }
};
