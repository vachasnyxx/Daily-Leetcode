// Approach one
//  class Solution {
//  public:
//      vector<vector<string>> result;  // store all solutions
//      int N;

//     bool isValid(vector<string>& board, int row, int col) {
//         // check column upwards
//         for (int i = 0; i < row; i++) {
//             if (board[i][col] == 'Q') return false;
//         }
//         // check left diagonal upwards
//         for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
//             if (board[i][j] == 'Q') return false;
//         }
//         // check right diagonal upwards
//         for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
//             if (board[i][j] == 'Q') return false;
//         }
//         return true;
//     }

//     void solve(vector<string>& board, int row) {
//         if (row == N) {  // base case: placed queens in all rows
//             result.push_back(board);
//             return;
//         }

//         for (int col = 0; col < N; col++) {
//             if (isValid(board, row, col)) {
//                 board[row][col] = 'Q';       // place queen
//                 solve(board, row + 1);       // recurse
//                 board[row][col] = '.';       // backtrack
//             }
//         }
//     }

//     vector<vector<string>> solveNQueens(int n) {
//         N = n;
//         vector<string> board(n, string(n, '.'));
//         solve(board, 0);
//         return result;
//     }
// };





class Solution {
public:
    vector<vector<string>> result;  // Every valid board configuration found,
                                     // each as a vector of strings (rows).
    int N;                          // Board size and queen count (n x n board, n queens).

    // Checks: if I place a queen at (row, col) right now, will it be
    // attacked by any queen ALREADY placed in rows above it?
    //
    // KEY INSIGHT: we only ever check UPWARD (rows < current row), never
    // downward or in the current row itself. That's because queens are
    // placed strictly one per row, going top to bottom — by the time we're
    // considering row 'row', rows below it are still completely empty, so
    // there's nothing there to conflict with yet.
    bool isValid(vector<string>& board, int row, int col) {

        // Check the COLUMN going straight up: is there already a queen
        // sitting directly above in the same column?
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // Check the LEFT diagonal going up (like the "\" but read upward,
        // i.e. up-and-to-the-left): row decreases, col decreases together.
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }

        // Check the RIGHT diagonal going up (up-and-to-the-right):
        // row decreases, col increases together.
        for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }

        // No conflicts found in column-above, left-diagonal-above, or
        // right-diagonal-above — this spot is safe.
        return true;
    }

    // The backtracking engine: try to place ONE queen per row, moving
    // downward row by row. This is the smart trick that makes N-Queens
    // fast compared to a naive "try queens anywhere on the grid" approach —
    // by construction, we NEVER even need to check for two queens sharing a
    // row, because we only ever place exactly one queen while working on
    // each row.
    void solve(vector<string>& board, int row) {

        // BASE CASE: we've successfully placed a queen in every row (0 to
        // N-1) without conflicts — this board is a complete valid solution.
        if (row == N) {
            result.push_back(board);
            return;
        }

        // Try placing a queen in EVERY column of the current row, one at
        // a time — this is the "branching" step of backtracking.
        for (int col = 0; col < N; col++) {

            if (isValid(board, row, col)) {
                board[row][col] = 'Q';   // CHOOSE: place the queen here.

                solve(board, row + 1);   // EXPLORE: recurse into the next
                                          // row, trying to build on top of
                                          // this choice.

                board[row][col] = '.';   // UN-CHOOSE (backtrack): remove
                                          // the queen so the NEXT column
                                          // we try in this same row starts
                                          // from a clean board — otherwise
                                          // leftover queens from a failed
                                          // branch would corrupt every
                                          // future attempt in this row.
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        N = n;
        // Build an empty n x n board, every cell starts as '.' (empty).
        vector<string> board(n, string(n, '.'));
        solve(board, 0);   // Start placing from row 0.
        return result;
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Place N queens on an N x N chessboard so that no two queens attack each
other (same row, same column, or same diagonal), and return every possible
arrangement.

ANALOGY — "Walking into a room row by row, picking a seat with no eye contact":
Imagine N rows of a theater, and you must seat exactly one guest (queen) per
row, one row at a time from front to back. Queens "attack" in straight lines
and diagonals — like having direct eye contact with someone. Before seating
a guest in row R, you glance UP the column and both UP-diagonals to check if
anyone already seated can see this exact spot. If someone can, you skip that
seat. If you seat someone and later discover NO valid seat exists in some
future row, you walk back to the previous row, ask that guest to get up
(backtrack), and try the next available seat over — repeating until you
either fill every row or exhaust every option.

WHY WE ONLY CHECK "UPWARD" IN isValid — THE KEY EFFICIENCY TRICK:
Because we place queens strictly one per row, in row order, rows below the
current one are guaranteed empty at the moment we're deciding — there's
nothing there yet to conflict with. This single design choice (one queen
per row, row-by-row) automatically eliminates the entire "same row" conflict
case for free, and cuts the search space dramatically compared to trying
queens at arbitrary (row, col) pairs across the whole grid.

DRY RUN (N = 4, showing the shape of the search, abbreviated):
Row 0: try col 0 → place Q at (0,0). Move to row 1.
  Row 1: col 0 blocked (same column). col 1 blocked (diagonal). col 2 → valid!
    Place Q at (1,2). Move to row 2.
    Row 2: col 0 blocked (diagonal from (0,0)... let's check col1,2,3 — ALL
    columns end up blocked by either (0,0) or (1,2)'s lines of attack.
    → Dead end. Backtrack out of row 2, back to row 1.
  Row 1: try col 3 → valid! Place Q at (1,3). Move to row 2.
    Row 2: col 1 → valid! Place Q at (2,1). Move to row 3.
      Row 3: col... eventually col of choice leads to full valid board:
      ".Q..", "...Q", "Q...", "..Q."  ← one full solution recorded!
    Backtrack row 3, row 2 tries other columns, eventually row 1 exhausts
    all columns, backtrack to row 0, try col 1 next...
(Full N=4 run eventually finds exactly 2 solutions, mirror images of each
other — this matches the known answer for N=4.)

TIME COMPLEXITY: Roughly O(N!) in the worst case (loosely bounded) — the
first queen has N column choices, the second has fewer valid choices due to
pruning, and so on, but formally we bound it as N! since column-conflict
alone eliminates one choice per row without even considering diagonals.
In practice the diagonal checks prune the search far more aggressively than
this loose bound suggests.
SPACE COMPLEXITY: O(N^2) for the board itself, plus O(N) for the recursion
call stack depth (one frame per row).

TRIGGER WORDS for this pattern:
- "N queens," "no two attack each other," "same row/column/diagonal
  constraint" → row-by-row backtracking placement with a validity check
  function scanning only previously-placed rows.
- Any "place one item per row/column with constraints against everything
  placed so far" phrasing → this exact one-per-row backtracking template,
  which also shows up in Sudoku Solver (LC 37) and various scheduling
  puzzles.

COMMON MISTAKES:
1. Checking the diagonal loops in the wrong direction (e.g. incrementing
   row instead of decrementing) — since we only place queens going
   downward, checking anything below or in the current row is both
   unnecessary AND can introduce index-out-of-bounds bugs if not careful.
2. Forgetting to reset `board[row][col] = '.'` after the recursive call
   returns — without this backtrack step, leftover 'Q' characters from a
   failed branch silently corrupt every subsequent column attempt in that
   same row.
3. Re-checking the same row for a queen conflict (e.g. scanning
   `board[row]` for an existing 'Q') — this is redundant and reveals a
   misunderstanding of the row-by-row invariant: since we only ever place
   one queen per row before moving to the next, no same-row conflict can
   ever occur by construction.

WHERE THIS SHOWS UP:
N-Queens (LC 51) and its counting variant N-Queens II (LC 52) are
long-standing classic backtracking interview questions, frequently seen at
Google, Amazon, and Bloomberg to test whether a candidate can design an
efficient constraint-checking function and correctly manage the
place-recurse-backtrack cycle without hand-holding.
================================================================================
*/