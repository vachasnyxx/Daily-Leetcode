// class Solution {
// public:
//     int climbStairs(int n) {
//         if (n <= 2) return n;
//         int a = 1, b = 2;
//         for (int i = 3; i <= n; i++) {
//             int c = a + b;
//             a = b;
//             b = c;
//         }
//         return b;
//     }
// };




// ============================================================================
// LeetCode 70: Climbing Stairs
// PATTERN: 1D Dynamic Programming (Fibonacci Recurrence, Space-Optimized)
// ============================================================================
//
// PROBLEM RECAP: You're climbing a staircase with n steps. Each time you can
// climb EITHER 1 step OR 2 steps. Find the number of DISTINCT ways to reach
// the top (step n).

class Solution {
public:
    int climbStairs(int n) {

        // ------------------------------------------------------------
        // BASE CASES:
        //   n = 1: only ONE way to reach step 1 — take a single 1-step move.
        //   n = 2: TWO ways — either two 1-step moves, or one 2-step move.
        // For n <= 2, the answer IS n itself (1 way for n=1, 2 ways for n=2).
        // This is a happy coincidence of the Fibonacci-like structure, not
        // a general rule — always verify base cases explicitly rather than
        // assuming a pattern holds.
        // ------------------------------------------------------------
        if (n <= 2) return n;

        // ------------------------------------------------------------
        // THE CORE RECURRENCE (the heart of this whole problem):
        //   ways(n) = ways(n-1) + ways(n-2)
        //
        // WHY? To reach step n, your LAST move was either:
        //   - A 1-step move FROM step (n-1), meaning all the ways to reach
        //     step (n-1) can be extended by one more 1-step move to reach n.
        //   - A 2-step move FROM step (n-2), meaning all the ways to reach
        //     step (n-2) can be extended by one more 2-step move to reach n.
        // Since these are the ONLY two possible last moves, and they lead
        // to DIFFERENT paths (no double-counting), the total ways to reach
        // step n is simply the SUM of ways to reach the two steps before it.
        // This is EXACTLY the Fibonacci recurrence: F(n) = F(n-1) + F(n-2).
        // ------------------------------------------------------------

        // 'a' tracks ways(1), 'b' tracks ways(2) — our two "previous" values.
        int a = 1, b = 2;

        // ------------------------------------------------------------
        // SPACE-OPTIMIZED ITERATIVE DP:
        // Instead of storing an entire array dp[0..n] (O(n) space), we only
        // ever need the LAST TWO values to compute the next one. So we keep
        // rolling 'a' and 'b' forward, discarding older values we no longer
        // need. This is the standard "rolling variables" optimization for
        // any DP where the recurrence only depends on a fixed small window
        // of previous states.
        // ------------------------------------------------------------
        for (int i = 3; i <= n; i++) {
            int c = a + b;   // ways(i) = ways(i-1) + ways(i-2)
            a = b;           // shift window forward: old 'b' becomes new 'a'
            b = c;           // new computed value becomes the new 'b'
        }

        // After the loop, 'b' holds ways(n) — the answer.
        return b;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: Count the number of distinct ways to climb n stairs, taking
// either 1 or 2 steps at a time. The answer follows the Fibonacci sequence.
//
// ANALOGY — "Counting paths up a staircase, one memory notebook page at a time":
// Imagine you're climbing a staircase and at every step, you write down in a
// notebook: "how many ways were there to get HERE?" To figure out how many
// ways lead to step n, you don't need to re-walk every possible path from
// scratch — you just look at your notebook entries for step (n-1) and step
// (n-2), because your last move to reach step n was EITHER a single step
// from (n-1) OR a double step from (n-2). Add those two notebook entries
// together, write the sum for step n, and move on. You never redo work you've
// already done — that's the essence of Dynamic Programming: "fill out a
// memory notebook so you never repeat the same calculation twice."
//
// WHY THIS IS DYNAMIC PROGRAMMING (not just "a formula"):
//   - The problem has OVERLAPPING SUBPROBLEMS: computing ways(5) requires
//     ways(4) and ways(3), which themselves require ways(3), ways(2), etc.
//     A naive recursive solution would recompute ways(3) multiple times.
//   - The problem has OPTIMAL SUBSTRUCTURE: the answer for step n can be
//     built directly and correctly from answers to smaller subproblems
//     (ways(n-1) and ways(n-2)), with no need to reconsider larger problems.
//   - DP exploits both properties by computing each subproblem ONCE and
//     reusing (memoizing) the result, rather than recomputing from scratch.
//
// WHY THIS SPECIFIC IMPLEMENTATION IS "SPACE-OPTIMIZED" DP:
//   - A more naive DP solution would use an array dp[0..n] to store every
//     value, costing O(n) space.
//   - Since the recurrence ways(i) = ways(i-1) + ways(i-2) only ever looks
//     back TWO steps, we don't need the entire array — just the last two
//     values. Rolling them forward in two variables (a, b) reduces space
//     from O(n) to O(1), while keeping time at O(n).
//
// TRIGGER WORDS for this pattern:
//   "number of distinct ways to reach step n", "each step you can move by
//   1 or 2 (or a small fixed set of choices)", "count ways / combinations
//   to reach a target using limited step sizes" => Think: 1D DP, often
//   reducible to a Fibonacci-style recurrence, often space-optimizable to
//   O(1) using rolling variables.
//
// GENERAL DP TEMPLATE (memorize this shape for ALL 1D DP problems):
//   1. Identify the recurrence: how does the answer for state i relate to
//      answers for smaller states (i-1, i-2, etc.)?
//   2. Identify base cases: what are the answers for the smallest states
//      (usually i=0 or i=1) that can't be derived from smaller states?
//   3. Decide: top-down (recursion + memoization) or bottom-up (iterative,
// %      filling a table from smallest to largest state)?
//   4. Optimize space if the recurrence only depends on a fixed small
// %      window of previous states (like here, depending on just i-1, i-2).
//
// COMPLEXITY:
//   - Time: O(n) — single loop from 3 to n, each iteration O(1) work.
//   - Space: O(1) extra — only two rolling variables (a, b), no array.
//   (Compare to naive recursion WITHOUT memoization: O(2^n) time, because
//   the same subproblems get recomputed exponentially many times — a classic
//   mistake that DP is specifically designed to avoid.)
//
// COMMON MISTAKES (why they happen):
//   1. Writing naive recursion without memoization — students sometimes
//      write climbStairs(n) { return climbStairs(n-1) + climbStairs(n-2); }
//      directly, which is CORRECT but catastrophically slow (O(2^n)) because
//      it recomputes the same subproblems over and over. Always ask "am I
// %      solving the same subproblem multiple times?" — if yes, memoize or
// %      go iterative.
//   2. Forgetting the base cases for n=1 or n=2 — since the loop starts at
// %      i=3, if you don't handle n<=2 explicitly, you'd either get wrong
// %      answers or access invalid array indices in an array-based version.
// //   3. Confusing "combinations" with "permutations" — this problem counts
// %      ORDERED sequences of 1s and 2s that sum to n (permutations of move
// %      choices), not unordered combinations. This affects the recurrence
// %      structure if the problem statement changes slightly (e.g., allowing
// %      3-step moves too, which changes the recurrence to ways(n-1) +
// %      ways(n-2) + ways(n-3)).
// //
// // COMPANIES: This exact "1D DP / Fibonacci recurrence" pattern is one of the
// // most common WARM-UP DP questions in Amazon, Microsoft, and Adobe interviews
// // (often used to gauge whether a candidate can even recognize DP structure
// // before moving to harder problems). It pairs directly with:
// //   - LC 746: Min Cost Climbing Stairs (same recurrence shape, but with
// %      costs to minimize instead of ways to count).
// //   - LC 509: Fibonacci Number (the literal, unadorned recurrence).
// //   - LC 91: Decode Ways (same 1D DP shape, but with string decoding rules
// %      instead of step counts).
// // Once you see "ways to reach step n using steps of size 1 or 2", your brain
// // should immediately reach for the Fibonacci-style 1D DP recurrence, and then
// // ask yourself "can I space-optimize this to O(1) with rolling variables?"
// // ============================================================================