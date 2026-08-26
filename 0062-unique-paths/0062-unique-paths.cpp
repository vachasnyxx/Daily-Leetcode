// class Solution {
// public:

//     int t[101][101];
//     int solve(int i, int j,int m, int n) // using two parameters instead of four
//     {
//         if (i >= m || j >= n) {
//             return 0;
//         }
//         if(i == m-1 && j == n-1)
//         return 1;

//         if(t[i][j] != -1){
//             return t[i][j];
//         }

//         int rightways = solve(i, j + 1, m, n);
//         int downways = solve(i+1, j, m, n);
//         return  t[i][j] =  rightways  + downways;
//     }
//     int uniquePaths(int m, int n) {
//         memset(t,-1,sizeof(t));
//         return solve(0,0,m,n);
//     }
// };





/*
========================================================================================
LEETCODE 62 — UNIQUE PATHS (Top-Down Recursion + Memoization)
========================================================================================

PLAIN ENGLISH DEFINITION:
You're standing at the top-left corner of an m x n grid. You can only move RIGHT
or DOWN. Count how many distinct paths get you to the bottom-right corner.

REAL-WORLD ANALOGY — "Asking Your Two Neighbors":
Imagine you're standing at cell (i, j) and you ask: "How many ways can I reach
the finish line from HERE?" You realize you don't need to figure this out from
scratch — you just need to ask your neighbor to the RIGHT and your neighbor
BELOW the same question, then add their answers together. Whoever reaches the
finish cell directly gets a free pass (1 way — just stand there, you're done).
Anyone who steps off the grid entirely gets 0 ways (dead end, illegal move).

The MEMOIZATION part is like each neighbor writing their answer on a sticky
note taped to their cell BEFORE you ask again. So if two different paths both
happen to pass through cell (2,3), the second time someone asks (2,3) "how many
ways from here?", it just reads the sticky note instead of re-doing all the
asking-around work. This is DP's core promise: "fill out a memory notebook so
you never solve the same sub-problem twice."

========================================================================================
DRY RUN — m = 3, n = 3 (a tiny 3x3 grid)
========================================================================================
Grid coordinates (i = row, j = col), target = reach (2,2):

  (0,0) (0,1) (0,2)
  (1,0) (1,1) (1,2)
  (2,0) (2,1) (2,2)  <- finish

We call solve(0, 0, 3, 3). Let's trace the recursion tree bottom-up (what
actually gets COMPUTED first, since recursion dives all the way down before
returning):

solve(2,2) -> i==m-1(2) && j==n-1(2) -> return 1  (base case: you're already home)
solve(2,1) -> right=solve(2,2)=1, down=solve(3,1) -> i>=m(3>=3) -> return 0
              total = 1 + 0 = 1  -> t[2][1] = 1
solve(1,2) -> right=solve(1,3) -> j>=n(3>=3) -> return 0
              down=solve(2,2)=1 (already computed, but not memo-read here since
              it's a base case, recomputed cheaply anyway)
              total = 0 + 1 = 1  -> t[1][2] = 1
solve(2,0) -> right=solve(2,1) -> MEMO HIT! t[2][1] already = 1, instant return
              down=solve(3,0) -> i>=m -> return 0
              total = 1 + 0 = 1  -> t[2][0] = 1
solve(0,2) -> right=solve(0,3) -> j>=n -> return 0
              down=solve(1,2) -> MEMO HIT! t[1][2] = 1
              total = 0 + 1 = 1  -> t[0][2] = 1
solve(1,1) -> right=solve(1,2) -> MEMO HIT! = 1
              down=solve(2,1) -> MEMO HIT! = 1
              total = 1 + 1 = 2  -> t[1][1] = 2
solve(1,0) -> right=solve(1,1) -> MEMO HIT! = 2
              down=solve(2,0) -> MEMO HIT! = 1
              total = 2 + 1 = 3  -> t[1][0] = 3
solve(0,1) -> right=solve(0,2) -> MEMO HIT! = 1
              down=solve(1,1) -> MEMO HIT! = 2
              total = 1 + 2 = 3  -> t[0][1] = 3
solve(0,0) -> right=solve(0,1) -> MEMO HIT! = 3
              down=solve(1,0) -> MEMO HIT! = 3
              total = 3 + 3 = 6  -> t[0][0] = 6

FINAL ANSWER: 6 unique paths from (0,0) to (2,2) in a 3x3 grid.
(Sanity check: this matches the known formula C(m+n-2, m-1) = C(4,2) = 6.)

Notice how many "MEMO HIT!" lines appear — without memoization, solve(0,1) and
solve(1,0) would each independently re-explore solve(1,1) and solve(2,1) from
scratch, and this blowup gets exponentially worse as the grid grows. That's
EXACTLY the problem memoization kills.
========================================================================================
*/

class Solution {
public:
    // Memo table: t[i][j] stores "number of unique paths from cell (i,j) to the
    // finish line." Sized 101x101 because LeetCode's constraint caps m, n at 100.
    int t[101][101];

    // solve(i, j, m, n): "how many distinct paths exist from current position
    // (i,j) to the bottom-right corner (m-1, n-1)?"
    // NOTE on your comment "using two parameters instead of four": you're using
    // absolute position (i, j) rather than an alternative formulation using
    // REMAINING distance (m-i, n-j) — both work, but yours is more intuitive
    // since t[i][j] directly maps to "grid cell (i,j)'s answer."
    int solve(int i, int j, int m, int n)
    {
        // BASE CASE 1 — Illegal move / fell off the grid.
        // If you've stepped past the last row or last column, this path is
        // invalid — it contributes ZERO valid paths. This is the "dead end."
        if (i >= m || j >= n) {
            return 0;
        }

        // BASE CASE 2 — Reached the destination.
        // You're standing exactly at the bottom-right corner. There's exactly
        // ONE way to be here: you just arrived. Stop recursing, return 1.
        // IMPORTANT: this check must come AFTER the out-of-bounds check,
        // otherwise you'd be checking equality on indices that might not
        // even be valid — order matters here.
        if (i == m - 1 && j == n - 1)
            return 1;

        // MEMOIZATION CHECK — "Read the sticky note before doing the work again."
        // If we've already solved solve(i, j, ...) before (in ANY branch of the
        // recursion tree, not just this one), don't recompute it — just return
        // the cached answer. This is what turns exponential recursion into
        // linear-in-grid-size work.
        if (t[i][j] != -1) {
            return t[i][j];
        }

        // RECURSIVE CASE — Ask your two neighbors (right and down) how many
        // ways THEY can reach the finish, then add their answers together.
        // This works because every path to the finish from (i,j) must take its
        // very first step EITHER right OR down — no other option exists. So the
        // total paths from (i,j) is simply the sum of paths-from-the-right-neighbor
        // and paths-from-the-down-neighbor. This additive breakdown is the
        // textbook definition of a valid DP recurrence relation.
        int rightways = solve(i, j + 1, m, n);
        int downways  = solve(i + 1, j, m, n);

        // Before returning, WRITE the sticky note (store in memo table) so any
        // future call to solve(i,j,...) gets an instant answer instead of
        // re-triggering this whole recursive branch.
        return t[i][j] = rightways + downways;
    }

    int uniquePaths(int m, int n) {
        // -1 means "not computed yet" — a fresh, blank notebook.
        // memset works here because -1 in every byte still reads as -1 for ints
        // (all bits set), which is a special property of -1 specifically —
        // this trick would NOT work for other sentinel values like -2 or 5.
        memset(t, -1, sizeof(t));
        return solve(0, 0, m, n);
    }
};

/*
========================================================================================
COMPLEXITY ANALYSIS (reasoned, not memorized)
========================================================================================
TIME: O(m * n)
  - There are exactly m*n distinct (i,j) pairs possible in the grid.
  - Thanks to memoization, solve(i,j,...) does its REAL work (the two recursive
    calls + addition) only the FIRST time it's called. Every subsequent call
    with the same (i,j) is an O(1) memo lookup.
  - So total real work = O(1) work per unique cell x (m*n) unique cells = O(m*n).
  - WITHOUT memoization, this would be O(2^(m+n)) — exponential, because the
    same sub-grids get fully re-explored over and over (classic overlapping
    subproblems, which is DP's whole reason for existing).

SPACE: O(m * n) for the memo table, plus O(m + n) for the recursion call stack
  depth (you can go at most (m-1)+(n-1) steps before hitting a base case).

========================================================================================
COMMON MISTAKES (and WHY they happen)
========================================================================================
1. Forgetting to initialize the memo table to a sentinel value (like -1) before
   use. WHY: memset with garbage/zero defaults makes t[i][j] == 0 look
   indistinguishable from "0 paths computed" vs "not computed yet," silently
   corrupting answers for cells that genuinely have 0 valid paths... though in
   THIS problem 0 paths never legitimately happens for in-bounds cells, so it's
   a smaller risk here — but it WILL bite you in problems where 0 is a valid answer.

2. Checking the memo BEFORE the base cases instead of after (or in the wrong
   order relative to bounds checks). WHY: it feels more "efficient" to check
   memo first, but if t[i][j] was never initialized for illegal (i,j) that
   exceed array bounds, you risk reading garbage or even an out-of-bounds
   array access, since t is only sized 101x101 and i or j could technically
   exceed that during the bounds-check branch if you're not careful with order.

3. Adding the two recursive calls in the wrong place — i.e., forgetting to
   ALSO store the result in t[i][j] (just returning rightways + downways
   directly without the assignment). WHY: this compiles fine and even gives
   correct answers, but silently DISABLES memoization for that path, turning
   your solution back into slow exponential recursion without any error message.

========================================================================================
TRIGGER WORDS — when you should think "Grid DP / path counting recursion":
========================================================================================
- "count the number of ways/paths from top-left to bottom-right"
- "can only move right or down (or similar restricted directions)"
- "minimum cost path" / "maximum sum path" through a grid (same recurrence
  shape, just replace + with min/max)

RELATED PROBLEMS TO PRACTICE THIS EXACT PATTERN:
- LC 63: Unique Paths II (same problem + obstacles — tests if you handle a
  THIRD base case: "blocked cell -> return 0")
- LC 64: Minimum Path Sum (same recurrence shape, swap sum-of-paths for
  min-of-costs)
- LC 120: Triangle (diagonal grid variant of the same idea)

COMPANIES KNOWN TO ASK THIS PATTERN:
Grid DP is a staple in Amazon, Microsoft, and Adobe interview loops — often as
a warm-up DP question before moving to harder variants like Unique Paths II or
Minimum Path Sum in the same interview.
========================================================================================
*/