// class Solution {
// public:
//     typedef long long ll;

//     ll getSumByFormula(ll count, ll x) {
//         return (count * x) - (count * (count + 1) / 2);
//     }

//     int maxValue(int n, int index, int maxSum) {
//         ll left = 1;
//         ll right = maxSum;
//         int result = 0;

//         while (left <= right) {
//             ll mid_val = left + (right - left) / 2;

//             // -----------------------Left-----------
//             ll left_count = min((ll)index, mid_val - 1);
//             ll left_sum = getSumByFormula(left_count, mid_val);
//             left_sum += max((ll)0, index - (mid_val - 1)); // extra ones if any

//             // -----------------------Right-----------
//             ll right_count = min((ll)n - index - 1, mid_val - 1);
//             ll right_sum = getSumByFormula(right_count, mid_val);
//             right_sum += max((ll)0, n - index - 1 - (mid_val - 1)); // extra ones if any

//             // -----------------------Calculation-----------
//             ll total_sum = left_sum + mid_val + right_sum;

//             if (total_sum <= maxSum) {
//                 result = max(result, (int)mid_val);
//                 left = mid_val + 1;
//             } else {
//                 right = mid_val - 1;
//             }
//         }

//         return result;
//     }
// };








// ============================================================================
// LeetCode 1802: Maximum Value at a Given Index in a Bounded Array
// PATTERN: Binary Search on the ANSWER (same skeleton as LC 1552, 2141, 875, 2656)
//        + Math Formula for Sum of Arithmetic Sequence (no loops!)
// ============================================================================
//
// PROBLEM RECAP (the "story"):
// You're building an array of length n, filled with positive integers only
// (every element >= 1). There's one rule: adjacent elements can differ by
// AT MOST 1 (so |nums[i] - nums[i+1]| <= 1 for all i). You're also given
// a budget: the sum of the entire array must be <= maxSum.
//
// Your goal? Make the element at a specific index as LARGE as possible,
// while obeying all the rules.
//
// Imagine you're a city planner designing a "mountain skyline" along a
// straight road of n plots. Each plot must have a building at least 1 story
// tall. Neighboring buildings can't have a height difference of more than
// 1 story (so the skyline looks smooth, like a gentle mountain range, not
// a jagged cliff). You have a fixed budget (maxSum) proportional to the
// total number of stories built across all plots. You want to maximize the
// height of the building at one specific plot (index), while staying within
// budget and keeping the skyline smooth.
//
// The optimal shape? A "pyramid" (or "tent") centered at your target index:
// heights decrease by exactly 1 as you move left or right from the peak,
// until they hit 1 (the minimum allowed), then stay flat at 1 for the
// remaining plots. Any other shape would either waste budget or fail to
// maximize the peak.

class Solution {
public:
    typedef long long ll;
    // Using long long because sums can easily overflow 32-bit int when
    // n and maxSum are large (up to 10^9 in some versions of this problem).

    // ------------------------------------------------------------------
    // getSumByFormula(count, x)
    // ------------------------------------------------------------------
    // STORY: Imagine you're standing at the peak of your mountain (height = x),
    // and you look to one side (left or right). As you walk away from the
    // peak, each step down reduces the building height by exactly 1, until
    // you hit the ground floor (height = 1). After that, all remaining
    // buildings are just 1 story tall (flat line).
    //
    // This function calculates the TOTAL number of stories (sum of heights)
    // for a sequence of 'count' buildings that descend from height x,
    // decreasing by 1 each step, but NEVER going below 1.
    //
    // MATH DERIVATION (memorize this formula pattern):
    //   The descending sequence from x looks like:
    //     x-1, x-2, x-3, ..., x-count
    //   (We use x-1, x-2, ... because the peak itself (x) is handled
    //   separately in total_sum = left_sum + mid_val + right_sum.)
    //
    //   This is an arithmetic sequence with:
    //     - First term: x - 1
    //     - Last term: x - count
    //     - Number of terms: count
    //
    //   Sum of an arithmetic sequence = (number of terms) * (first + last) / 2
    //     = count * ((x - 1) + (x - count)) / 2
    //     = count * (2x - 1 - count) / 2
    //     = count * x - count * (count + 1) / 2   [after algebra]
    //
    //   That's exactly what this function returns.
    //
    // WHY NO LOOP? Because a loop would be O(count), and count can be up
    // to O(n), making the feasibility check O(n) — which is fine, but the
    // formula is O(1), cleaner, and less error-prone once you internalize
    // the arithmetic sequence sum pattern.
    // ------------------------------------------------------------------
    ll getSumByFormula(ll count, ll x) {
        return (count * x) - (count * (count + 1) / 2);
    }

    // ------------------------------------------------------------------
    // maxValue(n, index, maxSum)
    // ------------------------------------------------------------------
    // GOAL: Find the LARGEST possible value at nums[index] such that the
    //       entire array's sum <= maxSum, adjacent differences <= 1, and
    //       all elements >= 1.
    // ------------------------------------------------------------------
    int maxValue(int n, int index, int maxSum) {
        // ------------------------------------------------------------
        // SEARCH SPACE for the answer (the peak height at nums[index]):
        //   - Lower bound (left): 1 (minimum allowed height — every
        //     element must be at least 1).
        //   - Upper bound (right): maxSum (theoretical ceiling — if you
        //     put the entire budget into one element and made everything
        //     else 1, this is the absolute max possible, though usually
        //     unachievable due to the "adjacent diff <= 1" rule).
        // ------------------------------------------------------------
        ll left = 1;
        ll right = maxSum;
        int result = 0;

        // ------------------------------------------------------------
        // MONOTONICITY (why binary search works here):
        //   - If a peak height H is achievable (total sum <= maxSum), then
        //     any SMALLER peak height H' < H is also achievable (less
        //     budget needed, easier constraint).
        //   - If a peak height H is NOT achievable (total sum > maxSum),
        //     then any LARGER peak height H'' > H is also NOT achievable
        //     (more budget needed, harder constraint).
        //   => feasible(H) is: true true true ... true | false false...
        //   We want the LARGEST true (maximize the peak), so we binary
        //   search for the rightmost true in this boolean sequence.
        // ------------------------------------------------------------
        while (left <= right) {
            ll mid_val = left + (right - left) / 2;
            // mid_val is our GUESS for the peak height at nums[index].
            // Now we need to check: can we build a valid mountain skyline
            // with this peak, without exceeding the budget maxSum?

            // ----------------------- LEFT SIDE -----------------------
            // STORY: Standing at the peak (index, height = mid_val), look
            // left. There are 'index' plots to the left (indices 0 to index-1).
            // As you walk left, each plot's height drops by exactly 1, until
            // it hits 1, then stays at 1 for the remaining plots.
            //
            // How many plots actually get the "descending" treatment (heights
            // > 1)? That's min(index, mid_val - 1):
            //   - mid_val - 1 is the number of steps you can take downward
            //     before hitting height 1 (since you start at mid_val - 1
            //     on the first step left).
            //   - index is the total number of plots available to the left.
            //   - Take the minimum — you can't descend more steps than there
            //     are plots, and you can't descend below 1.
            //
            // left_sum = sum of heights for these descending plots.
            // Then, if there are STILL plots left over (index > mid_val - 1),
            // those remaining plots are all height 1 — add them as "extra ones".
            // ------------------------------------------------------------
            ll left_count = min((ll)index, mid_val - 1);
            ll left_sum = getSumByFormula(left_count, mid_val);
            left_sum += max((ll)0, index - (mid_val - 1)); // extra ones if any

            // ----------------------- RIGHT SIDE ----------------------
            // STORY: Same idea, but looking right. There are (n - index - 1)
            // plots to the right (indices index+1 to n-1). Descend by 1 each
            // step until hitting 1, then flat-line at 1 for the rest.
            //
            // right_count = min(n - index - 1, mid_val - 1)
            // right_sum = sum of descending heights
            // Then add "extra ones" for any remaining plots beyond the descent.
            // ------------------------------------------------------------
            ll right_count = min((ll)n - index - 1, mid_val - 1);
            ll right_sum = getSumByFormula(right_count, mid_val);
            right_sum += max((ll)0, n - index - 1 - (mid_val - 1)); // extra ones if any

            // ----------------------- TOTAL BUDGET CHECK --------------
            // Total sum = left side sum + peak itself + right side sum.
            // If this total <= maxSum, the peak mid_val is feasible —
            // record it and try to push for an even HIGHER peak.
            // Otherwise, mid_val is too ambitious — try a smaller peak.
            // ------------------------------------------------------------
            ll total_sum = left_sum + mid_val + right_sum;

            if (total_sum <= maxSum) {
                // mid_val works — save it, but don't get complacent.
                // Try to go HIGHER since we want the MAXIMUM peak.
                result = max(result, (int)mid_val);
                left = mid_val + 1;
            } else {
                // mid_val is too tall for the budget — scale down.
                right = mid_val - 1;
            }
        }

        return result;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: Build a "mountain skyline" of length n where adjacent
// buildings differ by at most 1 story, every building is at least 1 story,
// and the total number of stories (sum of all heights) is <= maxSum. Maximize
// the height of the building at a specific index (the peak).
//
// THE FULL STORY (visualize this every time):
// You're a city planner with a fixed budget (maxSum) and a row of n plots.
// Each plot must have a building at least 1 story tall. Neighboring buildings
// can't have a height difference of more than 1 story (smooth skyline rule).
// You want to make the building at one specific plot as tall as possible.
// The optimal shape is a "pyramid" or "tent" centered at that plot: heights
// decrease by exactly 1 as you move left or right from the peak, until they
// hit 1, then stay flat at 1 for the remaining plots. Binary search over
// possible peak heights, and for each candidate, use the arithmetic sequence
// sum formula to compute the total budget needed in O(1) — no loops required.
//
// WHY THIS IS BINARY SEARCH ON ANSWER:
//   - We're not searching for a value inside an array — we're searching over
//     the SPACE OF POSSIBLE PEAK HEIGHTS (from 1 to maxSum).
//   - This space is monotonic: if a peak height H fits the budget, any
//     smaller H' also fits; if H doesn't fit, any larger H'' also doesn't.
//   - The feasibility check (total_sum <= maxSum) is O(1) thanks to the
//     arithmetic sequence formula, making the whole solution O(log(maxSum)).
//
// TRIGGER WORDS for this pattern:
//   "maximize the minimum" / "minimize the maximum" + "adjacent difference
//   constraint" + "sum constraint" + "can you compute feasibility in O(1) or
//   O(n)?" => Think: Binary Search on Answer, often with a math formula or
//   greedy simulation for the check.
//
// KEY FORMULA (memorize this arithmetic sequence sum pattern forever):
//   Sum of descending sequence from x, taking 'count' steps:
//     S = count * x - count * (count + 1) / 2
//   This comes from: first term = x-1, last term = x-count, count terms.
//   Sum = count * (first + last) / 2 = count * (2x - 1 - count) / 2
//       = count * x - count * (count + 1) / 2   [after algebra]
//   This formula shows up in ANY problem where you're summing a "pyramid"
//   or "tent" shape descending by 1 each step.
//
// COMPLEXITY:
//   - getSumByFormula(): O(1) — pure math, no loops.
//   - maxValue(): O(log(maxSum)) binary search steps, each O(1) => Total:
//     O(log(maxSum)).
//   - Space: O(1) extra — just a few scalar variables.
//
// COMMON MISTAKES (why they happen):
//   1. Forgetting to use long long for sums — mid_val * count can overflow
//      32-bit int easily, leading to silent wrong answers.
//   2. Off-by-one in left_count / right_count — students sometimes use
//      mid_val instead of mid_val - 1, forgetting that the first step away
//      from the peak is already one unit lower.
//   3. Forgetting the "extra ones" term — if the descent doesn't cover all
//      plots on one side (because mid_val is small relative to n), the
//      remaining plots are all height 1 and must be added explicitly.
//   4. Confusing "maximize the peak" with "minimize the peak" — the binary
//      search logic is identical, but for maximize you search right on true
//      (try larger peaks), for minimize you search left on true (try smaller
//      peaks).
//
// COMPANIES: This exact "binary search + arithmetic sequence sum" pattern
// shows up in Google and Amazon OA/onsite rounds, and pairs naturally with:
//   - LC 1552: Magnetic Force Between Two Balls (maximize minimum gap).
//   - LC 2141: Maximum Running Time of N Computers (maximize time with
//     capped-sum feasibility).
//   - LC 875: Koko Eating Bananas (minimize eating speed with O(n) check).
//   - LC 2656: Minimize Maximum of Array (minimize max with left-to-right
//     cascade simulation).
// Once you see "maximize/minimize X subject to sum constraint + smoothness
// or adjacency constraint", your brain should immediately reach for binary
// search on answer — the only thing that changes is whether the feasibility
// check uses a formula (like here) or a simulation/greedy scan (like LC2656).
// ============================================================================