// class Solution {
// public:
//     bool searchMatrix(vector<vector<int>>& matrix, int target) {
//         int rows = matrix.size();
//         int cols = matrix[0].size();
//         int i = 0;
//         int j = cols-1;

//         while(i<=rows-1 && j>=0){
//             if(matrix[i][j]==target) return true;
//             else if(matrix[i][j]> target) j--;
//             else i++;
//         }
//         return false;
//     }
// };



// ============================================================================
// LeetCode 240: Search a 2D Matrix II
// PATTERN: Two Pointers on a 2D Grid ("Staircase Search" from Top-Right)
// ============================================================================
//
// PROBLEM RECAP: You're given an m x n matrix where:
//   - Each ROW is sorted in ascending order (left to right).
//   - Each COLUMN is sorted in ascending order (top to bottom).
// Find whether a target value exists in the matrix.
//
// NOTE: This is NOT the same as LC 74 (Search a 2D Matrix I), where the
// entire matrix can be treated as a single sorted 1D array. Here, rows and
// columns are individually sorted, but there's no global sorted order across
// the whole flattened matrix — so binary search on the flattened array won't
// work. Instead, we use a clever two-pointer walk.

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        // ------------------------------------------------------------
        // STARTING POINT: TOP-RIGHT CORNER (row 0, col cols-1)
        // WHY THIS CORNER? Because it gives us a "decision boundary":
        //   - Moving LEFT decreases the value (since rows are sorted).
        //   - Moving DOWN increases the value (since columns are sorted).
        // This lets us eliminate one row or one column at each step,
        // guaranteeing O(rows + cols) time instead of O(rows * cols).
        //
        // You could ALSO start from BOTTOM-LEFT and mirror the logic
        // (move right to increase, up to decrease) — both work equally well.
        // But top-right or bottom-left are the ONLY two corners that work;
        // top-left and bottom-right are "dead ends" because both moves from
        // those corners go in the same direction (both increase or both
        // decrease), giving you no way to decide which path to take.
        // ------------------------------------------------------------
        int i = 0;          // current row index (start at top)
        int j = cols - 1;   // current column index (start at rightmost)

        // ------------------------------------------------------------
        // WALK THE "STAIRCASE":
        // At each step, compare matrix[i][j] with target:
        //   - If equal: found it, return true.
        //   - If matrix[i][j] > target: this entire COLUMN j is too big
        //     for the current row and all rows below (since column is
        //     sorted top-to-bottom). So eliminate this column by moving
        //     LEFT (j--).
        //   - If matrix[i][j] < target: this entire ROW i is too small
        //     for the current column and all columns to the left (since
        //     row is sorted left-to-right). So eliminate this row by
        //     moving DOWN (i++).
        //
        // This is why it's called "staircase search" — you're effectively
        // walking down a staircase of eliminated rows/columns until you
        // either hit the target or fall off the matrix.
        // ------------------------------------------------------------
        while(i <= rows - 1 && j >= 0){
            if(matrix[i][j] == target) return true;
            else if(matrix[i][j] > target) j--;  // eliminate this column
            else i++;                            // eliminate this row
        }

        // If we've walked off the matrix without finding target, it's not here.
        return false;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: Search for a target in a matrix where each row is sorted
// left-to-right and each column is sorted top-to-bottom, by starting at the
// top-right corner and walking like you're descending a staircase: left if
// the current value is too big, down if it's too small.
//
// ANALOGY — "Descending a staircase in a grid-shaped building":
// Imagine a building where each floor (row) has rooms numbered left to right
// in increasing order, and each vertical column of rooms also increases as
// you go down floors. You start in the top-right room. If the room number is
// too high, you know every room below it in that column is also too high —
// so you move left to a smaller-numbered room on the same floor. If the room
// number is too low, you know every room to the left on this floor is also
// too low — so you go down a floor to a larger-numbered room. You keep
// zig-zagging left and down until you either find the right room number or
// walk off the building. That zig-zag path is the "staircase".
//
// WHY THIS IS A TWO-POINTERS-ON-GRID PATTERN:
//   - We maintain two pointers (i, j) representing our current position.
//   - At each step, we eliminate either an entire row or an entire column
//     based on a single comparison, shrinking the search space linearly.
//   - This gives O(rows + cols) time, which is optimal for this problem
//     (you can't do better without additional structure like global sorting).
//
// TRIGGER WORDS for this pattern:
//   "matrix with sorted rows and sorted columns", "search in 2D matrix
//   where rows and columns are individually sorted", "O(m + n) search in
//   grid" => Think: Start at top-right (or bottom-left), walk staircase.
//
// TWO-CORNER RULE (memorize this):
//   - VALID starting corners: TOP-RIGHT or BOTTOM-LEFT.
//   - INVALID starting corners: TOP-LEFT or BOTTOM-RIGHT.
// Why? Because from top-right, left decreases and down increases (opposite
// directions, giving you a decision). From top-left, both right and down
// increase — no way to decide which path eliminates more. Same logic flipped
// for bottom-right (both left and up decrease).
//
// COMPLEXITY:
//   - Time: O(rows + cols) — in the worst case, you walk all the way from
//     top-right to bottom-left, eliminating one row or column per step.
//   - Space: O(1) extra — just two integer pointers.
//
// COMMON MISTAKES (why they happen):
//   1. Starting from top-left or bottom-right — students forget that both
//      moves from those corners go in the same direction (both increase or
//      both decrease), so you can't make a meaningful elimination decision.
//   2. Trying to binary search each row individually — this gives O(rows *
//      log(cols)), which is slower than O(rows + cols) for wide matrices,
//      and misses the elegant linear elimination insight.
//   3. Confusing this with LC 74 (Search a 2D Matrix I) — in LC 74, the
//      entire matrix is globally sorted (last element of row i < first
//      element of row i+1), so you can treat it as a 1D sorted array and
//      binary search. Here, that global order doesn't exist, so binary
//      search on the flattened matrix is invalid.
//
// COMPANIES: This exact "staircase search" pattern is a favorite in Google,
// Amazon, and Microsoft onsite rounds, and pairs naturally with:
//   - LC 74: Search a 2D Matrix I (globally sorted, binary search on 1D view).
//   - LC 378: Kth Smallest Element in a Sorted Matrix (uses a min-heap or
//     binary search on answer, but same sorted-rows-and-columns structure).
//   - LC 1351: Count Negative Numbers in a Sorted Matrix (same staircase
//     walk, but counting instead of searching).
// Once you see "rows sorted, columns sorted, search or count", your brain
// should immediately reach for the top-right staircase walk.
// ============================================================================