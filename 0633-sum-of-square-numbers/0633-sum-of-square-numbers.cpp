// ============================================================
// LEETCODE 633 - SUM OF SQUARE NUMBERS
// Pattern: Two Pointers Converging (a from 0 up, b from sqrt(c) down)
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// Given a non-negative integer c, determine if there exist two
// integers a and b such that a*a + b*b == c.
//
// THE ANALOGY (for permanent memory):
// Imagine a seesaw where the left end starts at 0 and the right
// end starts at the highest possible square root (sqrt(c)). You
// compute the total weight on the seesaw (a^2 + b^2). If it's too
// light, you nudge the left end up (increase a). If it's too heavy,
// you nudge the right end down (decrease b). You keep doing this
// until the total exactly matches c (success) or the two ends cross
// each other (failure — no such pair exists).
//
// WHY THIS IS OPTIMAL:
// This is the standard, interview-expected solution. It runs in
// O(sqrt(c)) time, which is optimal because you must at least
// examine values up to sqrt(c) in the worst case. It uses O(1)
// extra space and is trivial to explain out loud on a whiteboard.
// ============================================================

class Solution {
public:
    bool judgeSquareSum(int c) {
        // Use long to avoid overflow when computing a*a + b*b.
        // Even though c fits in int (up to 2^31-1), a*a or b*b
        // individually can exceed INT_MAX when a or b approach 46341,
        // and their sum can overflow a 32-bit signed int.
        long a = 0;
        long b = (long)sqrt(c);

        // Two pointers converging from opposite ends:
        // a starts at 0, b starts at floor(sqrt(c)).
        // Loop ends when they cross (a > b) — no valid pair left.
        while (a <= b) {
            long sum = a * a + b * b;

            if (sum == c) {
                // Found a valid pair (a, b) such that a^2 + b^2 = c.
                return true;
            } else if (sum < c) {
                // Sum is too small — need to increase it.
                // Since b is already at its maximum reasonable value,
                // the only way to grow the sum is to increase a.
                a++;
            } else {
                // Sum is too big — need to decrease it.
                // Decreasing b (the larger contributor) is the safe
                // way to shrink the sum without overshooting.
                b--;
            }
        }

        // Loop exited because a > b — the two pointers crossed without
        // ever hitting a sum exactly equal to c. No such pair exists.
        return false;
    }
};

// ============================================================
// SUMMARY BLOCK FOR REVISION (read this first when revisiting)
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// Check if a number c can be written as the sum of two perfect
// squares: a^2 + b^2 = c.
//
// THE ANALOGY (for permanent memory):
// Two ends of a seesaw: left end starts at 0, right end starts at
// sqrt(c). If the total weight (a^2 + b^2) is too light, nudge the
// left end up (a++). If too heavy, nudge the right end down (b--).
// Stop when the total exactly matches c (success) or when the ends
// cross (failure).
//
// STEP-BY-STEP MENTAL CHECKLIST:
//   1. a = 0, b = floor(sqrt(c)).
//   2. While a <= b:
//        a. Compute sum = a*a + b*b.
//        b. If sum == c --> return true.
//        c. If sum < c  --> a++ (need more weight).
//        d. If sum > c  --> b-- (need less weight).
//   3. If loop exits via a > b, return false.
//
// COMPLEXITY:
//   Time  -> O(sqrt(c)): in the worst case, a and b traverse the
//            entire range from 0 to sqrt(c), one step at a time.
//   Space -> O(1): just two integer variables.
//
// COMMON MISTAKES TO AVOID:
//   1. Using int for a, b, or sum — this can silently overflow when
//      c is near INT_MAX (2^31-1). For example, 46340^2 = 2,147,395,600
//      which already exceeds INT_MAX. Always use long/long long for
//      the running sum and the pointers to stay safe.
//   2. Starting b at c instead of sqrt(c) — that would make the loop
//      run O(c) times instead of O(sqrt(c)), which is wildly inefficient.
//   3. Forgetting the equality case (a == b) in the loop condition —
//      this matters for cases like c = 2 = 1^2 + 1^2, where the only
//      valid pair has a == b.
//
// TRIGGER WORDS TO RECOGNIZE THIS PATTERN INSTANTLY:
//   "sum of two squares", "a^2 + b^2 = c", "can this number be
//   expressed as sum of squares" --> think two pointers converging
//   from 0 and sqrt(c), adjusting based on whether the current sum
//   is too big or too small.
//
// WHERE THIS SHOWS UP IN INTERVIEWS:
//   Occasionally asked at Google and Bloomberg as a light number-theory
//   + two-pointer hybrid question. Related problems:
//   - LeetCode 279: Perfect Squares (DP variant of squares reasoning)
//   - LeetCode 367: Valid Perfect Square (the isPerfectSquare() helper
//     alone, as its own standalone problem)
// ============================================================




// class Solution {
// public:
//     bool isPerfectSquare(int n) {
//         int root = sqrt(n);
//         if (root * root == n)
//             return true;
//         else
//             return false;
//     }
//     bool judgeSquareSum(int c) {
//         int x = 0;
//         int y = c;
//         while (x <= y) {
//             if (isPerfectSquare(x) && isPerfectSquare(y)) {
//                 return true;
//             } else if (!isPerfectSquare(y)) {
//                 y = (int)sqrt(y) * (int)sqrt(y);
//                 x = c - y;
//             } else { // yaha pe x is not perfect
//                 x = ((int)sqrt(x) + 1) * ((int)sqrt(x) + 1);
//                 y = c - x;
//             }
//         }
//         return false;
//     }
// };