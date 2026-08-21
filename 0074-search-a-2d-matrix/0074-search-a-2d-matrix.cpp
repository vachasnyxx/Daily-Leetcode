// class Solution {
// public:
//     bool searchMatrix(vector<vector<int>>& matrix, int target) {
//         int m = matrix.size();
//         int n = matrix[0].size();

//         int start = 0;
//         int end = m * n-1;

//         while ( start <= end){
//             int mid = start + ( end - start)/2;

//             int row = mid/n;
//             int col = mid%n;
//             if(matrix[row][col] > target){
//                 end = mid - 1;
//             }
//             else if(matrix[row][col] < target){
//                 start = mid + 1;
//             }
//             else{
//                 return true;
//             }
//         }
//         return false;
//     }
// };





// ============================================================================
// LeetCode 74: Search a 2D Matrix I
// PATTERN: Binary Search on a "Flattened" 1D View of the Matrix
// ============================================================================
//
// PROBLEM RECAP: You're given an m x n matrix with TWO key properties:
//   1. Each ROW is sorted in ascending order (left to right).
//   2. The FIRST element of each row is GREATER THAN the LAST element of
//      the previous row.
//
// This second property is CRUCIAL — it means the ENTIRE matrix, if you
// "unrolled" it row-by-row into a single 1D array, would be fully sorted
// from start to finish. That global sorted order is what allows us to
// binary search as if we had a 1D array, even though we're working with
// a 2D structure.
//
// NOTE: This is DIFFERENT from LC 240 (Search a 2D Matrix II), where only
// rows and columns are individually sorted but there's NO global sorted
// order. In LC 240, you MUST use the staircase two-pointer walk. Here,
// binary search is valid and optimal.

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();    // number of rows
        int n = matrix[0].size(); // number of columns

        // ------------------------------------------------------------
        // THINK OF THE MATRIX AS A 1D ARRAY OF LENGTH m * n:
        //   Indices: 0, 1, 2, ..., m*n - 1
        //   Value at index k corresponds to matrix[k / n][k % n]
        //     - k / n gives the row (integer division)
        //     - k % n gives the column (remainder)
        //
        // This mapping is the KEY INSIGHT that lets us binary search
        // without actually flattening the matrix (which would cost O(m*n)
        // extra space and time).
        // ------------------------------------------------------------
        int start = 0;
        int end = m * n - 1;

        // ------------------------------------------------------------
        // STANDARD BINARY SEARCH on the virtual 1D array [start, end].
        // At each step:
        //   1. Compute mid index in the virtual 1D space.
        //   2. Convert mid to 2D coordinates: row = mid / n, col = mid % n.
        //   3. Compare matrix[row][col] with target and shrink the range.
        // ------------------------------------------------------------
        while (start <= end) {
            int mid = start + (end - start) / 2;

            // Convert 1D index 'mid' back to 2D (row, col).
            int row = mid / n;  // integer division gives the row
            int col = mid % n;  // remainder gives the column

            if (matrix[row][col] > target) {
                // Target must be in the left half of the virtual 1D array.
                end = mid - 1;
            }
            else if (matrix[row][col] < target) {
                // Target must be in the right half of the virtual 1D array.
                start = mid + 1;
            }
            else {
                // Found the target!
                return true;
            }
        }

        // If we've exhausted the search space without finding target, it's not here.
        return false;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: Search for a target in a matrix that's globally sorted
// (each row sorted, and each row's first element > previous row's last
// element) by pretending it's a 1D sorted array and running standard
// binary search, converting 1D indices back to 2D coordinates on the fly.
//
// ANALOGY — "Reading a book page by page":
// Imagine a book where every page has n lines, and the lines are numbered
// consecutively from 1 to m*n. Even though the content is physically on
// different pages (rows), the numbering is continuous — line k is always
// after line k-1 and before line k+1, no matter which page it's on. If you
// want to find a specific line number, you don't need to think in terms of
// "page X, line Y" — you can just think of it as position k in a single
// long list. To convert back, page = k / n, line = k % n. That's exactly
// what we're doing with the matrix: treating it as one long sorted list,
// then converting the 1D index back to (row, col) when we peek at a value.
//
// WHY THIS IS A "FLATTENED BINARY SEARCH" PATTERN:
//   - The matrix has a GLOBAL sorted order (unlike LC 240), so we can
//     treat indices 0 to m*n-1 as a single sorted array.
//   - We never actually allocate a flattened array — we just map 1D indices
//     to 2D coordinates mathematically: row = mid / n, col = mid % n.
//   - This gives O(log(m*n)) time, which is optimal for a sorted structure.
//
// TRIGGER WORDS for this pattern:
//   "matrix where each row is sorted AND the first element of each row is
//   greater than the last element of the previous row", "search in a
//   globally sorted 2D matrix", "treat 2D matrix as 1D sorted array" =>
//   Think: Binary search with row = mid / n, col = mid % n.
//
// KEY FORMULA (memorize this conversion forever):
//   Given a matrix with n columns:
//     - 1D index k  =>  2D coordinates: row = k / n, col = k % n
//     - 2D (r, c)   =>  1D index: k = r * n + c
//   This bidirectional mapping is the heart of "flattened" binary search
//   on any 2D grid that's globally sorted.
//
// COMPLEXITY:
//   - Time: O(log(m * n)) — standard binary search over m*n elements.
//   - Space: O(1) extra — just a few integer variables, no extra arrays.
//
// COMMON MISTAKES (why they happen):
//   1. Confusing LC 74 with LC 240 — students try to use staircase search
//      (two pointers) on LC 74, or try flattened binary search on LC 240.
//      The key difference: LC 74 has GLOBAL sorted order (first of row i >
//      last of row i-1); LC 240 does NOT, only row/column-wise sorted.
//   2. Forgetting the row/col conversion formula — trying to binary search
//      directly on 2D indices without mapping mid to (row, col) leads to
//      out-of-bounds errors or wrong comparisons.
//   3. Off-by-one in end = m * n - 1 — students sometimes write end = m * n
//      (forgetting that indices are 0-based), causing out-of-bounds access
//      when mid = m * n - 1 and row = (m*n-1)/n = m-1 (valid), but if
//      end = m*n, mid could be m*n, row = m (invalid).
//
// COMPANIES: This exact "flattened binary search" pattern is a staple in
// Google, Amazon, and Microsoft OA/onsite rounds, and pairs naturally with:
//   - LC 240: Search a 2D Matrix II (staircase two-pointer search, NO
//     global sorted order).
//   - LC 378: Kth Smallest Element in a Sorted Matrix (uses min-heap or
//     binary search on answer, but same sorted-rows structure).
//   - LC 1351: Count Negative Numbers in a Sorted Matrix (can use staircase
//     walk or binary search per row, depending on constraints).
// Once you see "globally sorted 2D matrix", your brain should immediately
// reach for the 1D index => (row, col) conversion and binary search.
// ============================================================================













//linear approavh
// class Solution {
// public:
//     bool searchMatrix(vector<vector<int>>& matrix, int target) {
//         int m = matrix.size();
//         int n = matrix[0].size();

//         int i = 0;
//         int j = n-1;

//         while( i < m && j >= 0){

//             if(matrix[i][j] > target){
//                 j--;
//             }
//             else if(matrix[i][j] < target){
//                 i++;
//             }
//             else{
//                 return true;
//             }

//         }
//         return false;
//     }
// };