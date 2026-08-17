// class Solution {
// public:
//     int peakIndexInMountainArray(vector<int>& arr) {
//         int n = arr.size();
//         int low = 0;
//         int high = n - 1;

//         while (low < high) {
//             int mid = low + (high - low) / 2;

//             if (arr[mid] < arr[mid + 1]) {
//                 low = mid + 1;
//             } else {
//                 high = mid;
//             }
//         }
//         // return low;
//         return high;
//     }
// };




// ============================================================
// LEETCODE 852 - PEAK INDEX IN A MOUNTAIN ARRAY
// Pattern: Binary Search on "Slope" / Binary Search on Answer
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// You're given a "mountain array" — an array that strictly
// increases up to a single peak, then strictly decreases after it.
// Find the INDEX of that peak in O(log n) time.
//
// THE ANALOGY (for permanent memory):
// Imagine you're hiking up a perfectly shaped mountain in fog.
// You can only feel whether the ground under your feet is sloping
// UP or DOWN compared to one step ahead. If it's sloping up,
// common sense says "keep walking uphill, the summit is ahead."
// If it's sloping down, you've already passed the summit — it's
// behind you. You never need to see the whole mountain to find
// the peak; you just keep following the uphill slope until you
// can't go up anymore.
//
// WHY BINARY SEARCH WORKS HERE (even though array isn't "sorted"):
// This isn't sorted data, but it still has a property binary search
// can exploit: at any point, comparing a value to its neighbor tells
// you which HALF of the array is guaranteed to contain the peak.
// That's the real requirement for binary search to work — not
// "sortedness," but "the comparison at mid reliably eliminates one
// whole half."
// ============================================================

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size();
        int low = 0;
        int high = n - 1;

        // ------------------------------------------------------
        // VARIANT USED HERE: "look at mid vs mid+1" (right neighbor)
        // ------------------------------------------------------
        // This is the "right-neighbor" variant from LC 162.
        // It uses standard floor-mid division because it always
        // looks FORWARD (mid+1), so mid never needs to be low itself
        // when high shrinks — no infinite loop risk.
        while (low < high) {
            int mid = low + (high - low) / 2;

            // If arr[mid] < arr[mid+1], the slope is going UP as we
            // move right from mid. That means the peak must be strictly
            // to the RIGHT of mid (mid itself can't be the peak here
            // since its right neighbor is higher). So we can safely
            // discard mid and everything left of it: low = mid + 1.
            if (arr[mid] < arr[mid + 1]) {
                low = mid + 1;
            } else {
                // arr[mid] >= arr[mid+1] means the slope is going DOWN
                // (or flat-down) as we move right from mid. That means
                // the peak is at mid or somewhere to its LEFT. We keep
                // mid in the search space (since it could be the peak),
                // so high = mid (NOT mid - 1).
                high = mid;
            }
        }

        // Loop ends when low == high --> converged on the peak index.
        // return low;   // works — low and high are equal here anyway
        return high;     // also works, for the same reason
    }
};

// ============================================================
// SUMMARY BLOCK FOR REVISION (read this first when revisiting)
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// Find the index of the single peak in a "mountain array" — an
// array that strictly increases up to a peak, then strictly
// decreases after it — using O(log n) time instead of scanning
// the whole array.
//
// THE ANALOGY (for permanent memory):
// You're hiking up a perfectly shaped mountain in fog and can only
// feel the slope under your feet. Uphill slope --> summit is ahead
// of you, keep going that direction. Downhill slope --> summit is
// behind you, turn back. You never need to see the whole range;
// local slope alone guarantees you'll find the peak, because the
// terrain can't rise forever within a bounded array.
//
// THE CORE TRICK:
// Binary search doesn't strictly require a SORTED array — it just
// needs a comparison at "mid" that reliably tells you which half
// still contains a valid answer. Here, comparing a neighbor's
// height does exactly that.
//
// STEP-BY-STEP MENTAL CHECKLIST:
//   1. low = 0, high = n - 1.
//   2. While low < high:
//        a. mid = low + (high - low) / 2   (standard floor division)
//        b. If arr[mid] < arr[mid+1] --> low = mid + 1   (climbing up, discard mid)
//        c. Else --> high = mid               (climbing down or at peak, keep mid)
//   3. Return low (or high — they're equal at this point).
//
// COMPLEXITY:
//   Time  -> O(log n): each step halves the search window.
//   Space -> O(1): only integer pointers used.
//
// COMMON MISTAKES TO AVOID:
//   1. Using "high = mid - 1" in the else-branch instead of "high = mid".
//      This can skip over the actual peak since mid itself might BE the
//      peak (when arr[mid] > arr[mid+1] but arr[mid] is still the highest).
//   2. Checking arr[mid] < arr[mid+1] but accessing mid+1 when mid could
//      be the LAST index (index out of bounds). This is why the loop bound
//      is "low < high" (never lets mid touch an edge where the neighbor
//      access would go out of bounds) — always double check this boundary
//      reasoning during a dry run.
//   3. Assuming there's only ONE peak in a general array. This problem
//      guarantees a single peak in a mountain array, but the general
//      "find peak element" problem (LC 162) can have multiple peaks —
//      you only need to return ANY one, not all of them.
//
// TRIGGER WORDS TO RECOGNIZE THIS PATTERN INSTANTLY:
//   "mountain array", "peak element", "element greater than its neighbors",
//   "local maximum in O(log n)" --> think binary search on slope direction,
//   not sortedness.
//
// WHERE THIS SHOWS UP IN INTERVIEWS:
//   Common at Amazon, Google, and Microsoft as a "binary search on answer"
//   warm-up. Related/likely follow-ups:
//   - LeetCode 162: Find Peak Element (general version, multiple peaks possible)
//   - LeetCode 1901: Find a Peak Element II (2D grid version)
// ============================================================







// // linear search but not here cuz we need O(logn)
// // class Solution {
// // public:
// //     int peakIndexInMountainArray(vector<int>& arr) {
// //         int n = arr.size();
// //         int i = 0;
// //         while(arr[i] < arr[i+1]){
// //             i++;
// //         }
// //         return i;
// //     }
// // };