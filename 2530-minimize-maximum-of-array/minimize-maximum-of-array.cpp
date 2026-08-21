// class Solution {
// public:
//     bool isValid(vector<int>& nums, int mid_max, int n) {
//         vector<long long> arr(begin(nums), end(nums));

//         for (int i = 0; i < n - 1; i++) {
//             if (arr[i] > mid_max) {
//                 return false;
//             }

//             long long buffer = mid_max - arr[i];
//             arr[i + 1] = arr[i + 1] - buffer;
//         }
//         return arr[n - 1] <= mid_max;
//     }

//     int minimizeArrayValue(vector<int>& nums) {
//         int n = nums.size();

//         int maxL = 0;
//         int maxR = *max_element(begin(nums), end(nums));

//         int result = 0;

//         while (maxL <= maxR) {
//             int mid_max = maxL + (maxR - maxL) / 2;

//             if (isValid(nums, mid_max, n)) {
//                 result = mid_max;
//                 maxR = mid_max - 1;
//             } else {
//                 maxL = mid_max + 1;
//             }
//         }
//         return result;
//     }
// };







// ============================================================================
// LeetCode 2656: Maximum Sum With Exactly K Elements (actually 2656 is
// something else — this is LC 2656: Minimum Possible Maximum of an Array
// after Operations, sometimes titled "Minimize Maximum of Array")
// PATTERN: Binary Search on the ANSWER (same skeleton as LC 1552, 2141, 875)
// ============================================================================
//
// PROBLEM RECAP: You're given an array nums. You can perform the following
// operation any number of times: choose an index i (0 <= i < n-1), decrease
// nums[i] by some amount x, and increase nums[i+1] by the SAME amount x.
// In other words, you can shift value from left to right, but never from
// right to left. Find the MINIMUM possible value of the MAXIMUM element in
// the array after any number of such operations.
//
// NOTE: This is NOT the same as LC 2656 (which is a different problem about
// picking K elements). This one is often titled "Minimize Maximum of Array"
// or similar — the key is the left-to-right transfer operation.

class Solution {
public:
    // ------------------------------------------------------------------
    // isValid(nums, mid_max, n)
    // ------------------------------------------------------------------
    // GOAL: Check whether it's possible to make EVERY element in the array
    //       <= mid_max by only shifting values from left to right.
    //
    // WHY THIS WORKS (the key insight):
    //   - You can only move value from i to i+1 (left to right), never
    //     backwards. So the only way to "fix" an element that's too big
    //     is to push its excess to the right neighbor, which may then
    //     become too big and need to push further right, and so on.
    //   - This creates a "cascade" effect: if nums[0] is too big, we dump
    //     its excess into nums[1]; if nums[1] then exceeds mid_max, we
    //     dump its excess into nums[2], etc. If at any point an element
    //     already exceeds mid_max BEFORE receiving any excess from the
    //     left, it's impossible — return false immediately.
    //   - The last element (nums[n-1]) has no right neighbor to dump into,
    //     so it must end up <= mid_max after all cascades reach it.
    //
    // WHY WE COPY TO long long:
    //   - During the cascade, intermediate values can become negative or
    //     very large (if we push a lot of excess rightward), potentially
    //     overflowing a 32-bit int. Using long long for the working array
    //     avoids silent overflow bugs.
    // ------------------------------------------------------------------
    bool isValid(vector<int>& nums, int mid_max, int n) {
        // Work on a copy so we don't mutate the original array.
        // Using long long to prevent overflow during buffer arithmetic.
        vector<long long> arr(begin(nums), end(nums));

        for (int i = 0; i < n - 1; i++) {
            // If the current element already exceeds mid_max BEFORE we can
            // push anything from it to the right, this candidate is dead.
            if (arr[i] > mid_max) {
                return false;
            }

            // Compute how much "buffer" (spare capacity) this element has
            // relative to mid_max. This is the amount we can safely push
            // to the right neighbor without violating the constraint here.
            long long buffer = mid_max - arr[i];

            // Push the buffer to the right neighbor: decreasing arr[i+1]
            // by buffer is equivalent to saying "we moved buffer amount
            // from arr[i] to arr[i+1]". If buffer is positive, arr[i+1]
            // gets smaller (good); if buffer is negative (arr[i] was
            // already below mid_max), arr[i+1] gets larger (potentially
            // bad, but that's the only direction allowed).
            arr[i + 1] = arr[i + 1] - buffer;
        }

        // After cascading all the way to the last element, check if it
        // ended up within the allowed bound. If yes, mid_max is feasible.
        return arr[n - 1] <= mid_max;
    }

    // ------------------------------------------------------------------
    // minimizeArrayValue(nums)
    // ------------------------------------------------------------------
    // GOAL: Find the SMALLEST mid_max for which isValid() returns true.
    // ------------------------------------------------------------------
    int minimizeArrayValue(vector<int>& nums) {
        int n = nums.size();

        // ------------------------------------------------------------
        // SEARCH SPACE for the answer (mid_max):
        //   - Lower bound (maxL): 0 (or even *min_element*, but 0 is safe
        //     and simpler — the true answer can't be negative anyway).
        //   - Upper bound (maxR): the current maximum element — we can
        //     always achieve at least this value by doing zero operations.
        // ------------------------------------------------------------
        int maxL = 0;
        int maxR = *max_element(begin(nums), end(nums));

        int result = 0;

        // ------------------------------------------------------------
        // MONOTONICITY (why binary search works here):
        //   - If a candidate mid_max is achievable, then any LARGER value
        //     is also achievable (easier constraint — more room to push).
        //   - If a candidate mid_max is NOT achievable, then any SMALLER
        //     value is also NOT achievable (tighter constraint — less room).
        //   => isValid(mid_max) is: true true true ... true | false false...
        //   We want the LARGEST true? No — we want the SMALLEST true,
        //   because we're MINIMIZING the maximum. So we binary search for
        //   the leftmost true in this boolean sequence.
        // ------------------------------------------------------------
        while (maxL <= maxR) {
            int mid_max = maxL + (maxR - maxL) / 2;

            if (isValid(nums, mid_max, n)) {
                // mid_max is feasible — record it, but try to go LOWER
                // since we want the MINIMUM possible maximum.
                result = mid_max;
                maxR = mid_max - 1;   // search left half (smaller candidates)
            } else {
                // mid_max is too ambitious — need to allow a larger max.
                maxL = mid_max + 1;   // search right half (larger candidates)
            }
        }

        return result;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: You can only push value from left to right in the array.
// Find the smallest possible "maximum element" you can achieve by shuffling
// excess leftward values rightward as much as needed.
//
// ANALOGY — "Water flowing downhill in a series of tanks":
// Imagine a row of water tanks connected by one-way pipes that only let
// water flow from left to right. Each tank has some water level (the array
// values). You want all tanks to end up at or below some target height
// (mid_max). If a tank is too full, you can drain its excess into the next
// tank to the right, but never pull water back from right to left. You keep
// doing this tank by tank — if any tank is already over the target BEFORE
// receiving water from the left, you're doomed (impossible for this target).
// At the very end, the last tank must also be at or below the target, since
// it has nowhere else to dump. That's exactly what isValid() simulates.
//
// WHY THIS IS BINARY SEARCH ON ANSWER:
//   - We're not searching for a value inside the array — we're searching
//     over the SPACE OF POSSIBLE ANSWERS (candidate maximums from 0 to
//     max(nums)).
//   - This space is monotonic: if a candidate max works, all larger maxes
//     also work; if it fails, all smaller maxes also fail.
//   - The feasibility check (isValid) is O(n) — a single left-to-right
//     cascade simulation — which is cheap enough to run inside binary
//     search, giving O(n log(max(nums))) total time.
//
// TRIGGER WORDS for this pattern:
//   "minimize the maximum", "maximize the minimum", "can you check if a
//   candidate value is achievable in O(n) or O(n log n)?" => Think: Binary
//   Search on Answer, with a greedy/simulation feasibility check.
//
// TWO-FUNCTION TEMPLATE (same as LC 1552, 2141, 875 — memorize this shape):
//   1. isValid(candidate) — O(n) feasibility checker, usually a greedy
//      simulation or capped-sum argument.
//   2. minimizeArrayValue driver — binary search over [low, high] candidate
//      answers, shrinking the range based on isValid()'s true/false, always
//      saving the best true result found so far (smallest true for "minimize
//      maximum", largest true for "maximize minimum").
//
// COMPLEXITY:
//   - isValid(): O(n) — one linear pass simulating the cascade.
//   - minimizeArrayValue(): O(log(max(nums))) binary search steps, each
//     costing O(n) => Total: O(n log(max(nums))).
//   - Space: O(n) extra for the long long copy in isValid (could be optimized
//     to O(1) with careful in-place arithmetic, but this is safer and clearer).
//
// COMMON MISTAKES (why they happen):
//   1. Forgetting to use long long for the working array — intermediate
//     values during the cascade can overflow 32-bit int, leading to silent
//     wrong answers that are hard to debug.
//   2. Checking arr[i] > mid_max AFTER pushing buffer instead of BEFORE —
//    学生们 sometimes push first, then check, which misses the case where
//    an element was already too big before receiving anything from the left.
//   3. Confusing "minimize maximum" with "maximize minimum" — the binary
//      search logic is identical, but the direction of the search flips:
//      for minimize-maximum, you want the SMALLEST feasible candidate
//      (search left on true); for maximize-minimum, you want the LARGEST
//      feasible candidate (search right on true).
//
// COMPANIES: This exact "binary search + left-to-right cascade" pattern
// shows up in Google and Amazon OA/onsite rounds, and pairs naturally with:
//   - LC 1552: Magnetic Force Between Two Balls (maximize minimum gap).
//   - LC 2141: Maximum Running Time of N Computers (maximize time with
//     capped-sum feasibility).
//   - LC 875: Koko Eating Bananas (minimize eating speed with O(n) check).
//   - LC 1231: Divide Chocolate (maximize minimum sweetness with prefix-sum
//     feasibility).
// Once you see "minimize the maximum" or "maximize the minimum" + "fast
// feasibility check", your brain should immediately reach for binary search
// on answer — the only thing that changes between problems is what the
// feasibility function actually simulates.
// ============================================================================