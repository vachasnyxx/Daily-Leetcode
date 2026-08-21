// class Solution {
// public:
//     bool possibleToPlace(int force, vector<int>& position, int m) {
//         int prev = position[0];
//         int countBalls = 1;

//         for (int i = 1; i < position.size(); i++) {
//             int curr = position[i];

//             if ((curr - prev) >= force) {
//                 countBalls++;
//                 prev = curr;
//             }
//             if (countBalls == m)
//                 break;
//         }
//         return countBalls == m;
//     }

//     int maxDistance(vector<int>& position, int m) {
//         int n = position.size();
//         sort(begin(position), end(position));

//         int minForce = 1;
//         int maxForce = position[n - 1] - position[0];
//         int result = 0;
//         while (minForce <= maxForce) {
//             int midForce = minForce + (maxForce - minForce) / 2;

//             if (possibleToPlace(midForce, position, m)) {
//                 result = midForce;
//                 minForce = midForce + 1;
//             } else {
//                 maxForce = midForce - 1;
//             }
//         }
//         return result;
//     }
// };




// ============================================================================
// LeetCode 1552: Magnetic Force Between Two Balls
// PATTERN: Binary Search on the ANSWER (not on the array itself)
// ============================================================================

class Solution {
public:

    // ------------------------------------------------------------------
    // possibleToPlace(force, position, m)
    // ------------------------------------------------------------------
    // GOAL: Check if we CAN place all m balls into the sorted 'position'
    //       array such that every pair of ADJACENT placed balls is
    //       AT LEAST 'force' apart.
    //
    // WHY GREEDY WORKS: To place the maximum number of balls for a given
    // minimum gap, always place a ball as EARLY as possible (leftmost
    // valid basket), then jump to the next basket that is >= force away.
    // Placing greedily-early never hurts you — it only leaves MORE room
    // for the remaining balls, never less. This greedy correctness is
    // what makes this helper function trustworthy inside binary search.
    // ------------------------------------------------------------------
    bool possibleToPlace(int force, vector<int>& position, int m) {

        // Always place the FIRST ball at the first basket (leftmost point).
        // This is a safe greedy choice — no reason to skip the leftmost slot.
        int prev = position[0];

        // We've placed 1 ball already (the one above).
        int countBalls = 1;

        // Walk through the remaining sorted positions looking for the
        // next basket that is far enough (>= force) from the last placed ball.
        for (int i = 1; i < position.size(); i++) {
            int curr = position[i];

            // If current basket is far enough from the last placed ball,
            // place a new ball here and update 'prev' to this new position.
            if ((curr - prev) >= force) {
                countBalls++;
                prev = curr;
            }
            // NOTE: if the gap is NOT enough, we simply skip this basket
            // and move to the next one — we don't place a ball, and 'prev'
            // stays unchanged (still points to the last successfully placed ball).

            // Early exit optimization: once we've managed to place all m
            // balls, there's no need to keep scanning further baskets.
            if (countBalls == m)
                break;
        }

        // If we managed to fit all m balls with this minimum gap, force works.
        return countBalls == m;
    }


    // ------------------------------------------------------------------
    // maxDistance(position, m)
    // ------------------------------------------------------------------
    // GOAL: Find the MAXIMUM possible value of the MINIMUM magnetic force
    //       (i.e., minimum gap between any 2 adjacent balls) achievable
    //       when placing m balls into the given baskets.
    //
    // WHY BINARY SEARCH ON ANSWER: We are not searching for a value INSIDE
    // the array — we are searching over the SPACE OF POSSIBLE ANSWERS
    // (possible force values from 1 to max_gap). This space has a special
    // MONOTONIC property (proven below), which is the #1 requirement for
    // binary-search-on-answer to be legal.
    // ------------------------------------------------------------------
    int maxDistance(vector<int>& position, int m) {
        int n = position.size();

        // Sorting is MANDATORY: gaps between balls only make sense once
        // positions are ordered left to right. Without sorting, "adjacent"
        // has no meaning.
        sort(begin(position), end(position));

        // ------------------------------------------------------------
        // Define the search space of possible 'force' (answer) values:
        //   - Smallest possible force = 1 (can't have force 0, balls
        //     would need to be at the exact same spot to fail that).
        //   - Largest possible force = position[n-1] - position[0]
        //     (the total span; you can never need a gap bigger than
        //     the whole range, since only 2 balls could achieve that).
        // ------------------------------------------------------------
        int minForce = 1;
        int maxForce = position[n - 1] - position[0];
        int result = 0;

        // ------------------------------------------------------------
        // MONOTONICITY (the CORE reason binary search works here):
        //   - If a force value F works (can place m balls with gap >= F),
        //     then any SMALLER force F' < F also works (easier condition).
        //   - If a force value F does NOT work, any LARGER force F'' > F
        //     also does NOT work (even harder condition).
        //
        // This means the boolean sequence of possibleToPlace(force) as
        // force increases from 1 to maxForce looks like:
        //     true true true true ... true | false false false false
        //                                  ^
        //                         this is the boundary we want —
        //                         the LARGEST force that still returns true.
        //
        // Binary search finds this true/false boundary in O(log(maxForce))
        // instead of checking every force value one by one (O(maxForce)).
        // ------------------------------------------------------------
        while (minForce <= maxForce) {
            int midForce = minForce + (maxForce - minForce) / 2;

            if (possibleToPlace(midForce, position, m)) {
                // midForce WORKS — it's a valid candidate answer.
                // Record it, but don't stop — try to push for an even
                // BIGGER force, since we want the MAXIMUM valid one.
                result = midForce;
                minForce = midForce + 1;   // search the right half (bigger forces)
            } else {
                // midForce is TOO BIG — placing m balls with this much
                // spacing is impossible. Try smaller forces.
                maxForce = midForce - 1;   // search the left half (smaller forces)
            }
        }

        // 'result' holds the last force value that returned true —
        // i.e., the maximum minimum-distance achievable.
        return result;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: We're placing m magnetic balls into baskets (given
// positions) so that the two CLOSEST balls are as FAR APART as possible.
// We want to MAXIMIZE the MINIMUM distance.
//
// ANALOGY — "Setting up chairs in an auditorium":
// Imagine you have m friends and a row of fixed seats (some far apart,
// some close). You want to seat all m friends so that even the two
// friends sitting closest to each other are as far apart as possible
// (nobody wants to sit shoulder-to-shoulder). You guess a "minimum
// comfortable gap" (force), then greedily walk down the row seating a
// friend as soon as you find a seat far enough from the last seated
// friend. If you run out of friends to seat before running out of seats
// — great, that gap was too small, try a BIGGER gap. If you run out of
// seats before seating everyone — that gap was too big, try SMALLER.
// This "guess and check, then adjust" process IS binary search on the answer.
//
// WHY BINARY SEARCH ON THE *ANSWER* (not the array):
// Normally binary search finds a value inside a sorted array. Here, we
// binary search over the space of POSSIBLE ANSWERS (force = 1 to
// max_gap), because that space is monotonic: small forces are always
// achievable, large forces eventually become impossible, and there's a
// single tipping point between "possible" and "impossible". Whenever a
// problem asks for "maximize the minimum" or "minimize the maximum" and
// you can quickly CHECK if a candidate value is feasible, that's your
// trigger to think: Binary Search on Answer.
//
// TRIGGER WORDS to remember for future problems:
//   "maximize the minimum distance/gap" / "minimize the maximum X"
//   + "can you check feasibility of a given value quickly?"
//   => Binary Search on Answer.
//
// TWO-FUNCTION STRUCTURE (this is the template you'll reuse forever):
//   1. A feasibility checker (possibleToPlace) — given a candidate answer,
//      return true/false whether it's achievable. Usually greedy or O(n).
//   2. A binary search driver (maxDistance) — searches over candidate
//      answers [low, high], shrinking the search space based on the
//      checker's true/false result, and tracking the best valid answer.
//
// COMPLEXITY:
//   - possibleToPlace: O(n) — one linear scan through sorted positions.
//   - maxDistance: O(log(maxGap)) binary search iterations, each costing
//     O(n) for the check => Total: O(n log(maxGap)).
//   - Space: O(1) extra (ignoring the sort, which is O(n) or O(log n)
//     depending on implementation; positions sorted in-place).
//
// COMMON MISTAKES (why they happen):
//   1. Forgetting to SORT position first — gaps are meaningless unless
//      points are ordered; leads to wrong/undefined greedy behavior.
//   2. Off-by-one in binary search bounds: writing '<' instead of '<='
//      in the while loop, causing the last candidate to be missed, OR
//      forgetting to save 'result' before moving minForce/maxForce,
//      losing the best answer found so far.
//   3. Confusing "search on the answer" with "search in the array" —
//      students sometimes try to binary search position[] itself,
//      which doesn't make sense since we're not looking for an INDEX,
//      we're looking for the best FORCE value in a range of integers.
//
// COMPANIES: This exact pattern (binary search on answer + greedy
// feasibility check) is a favorite in Google, Amazon, and Microsoft
// onsite rounds, and shows up in twin problems like "Split Array
// Largest Sum" (LC 410), "Koko Eating Bananas" (LC 875), and
// "Capacity To Ship Packages Within D Days" (LC 1011) — all following
// the identical two-function template above.
// ============================================================================