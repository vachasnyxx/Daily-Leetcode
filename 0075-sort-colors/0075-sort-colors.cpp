// class Solution {
// public:
//     void sortColors(vector<int>& nums) {
//         // We use three pointers: low, mid, high
//         // low → boundary for 0s (red)
//         // mid → current element being checked
//         // high → boundary for 2s (blue)
//         // The idea: partition the array into three regions [0s | 1s | 2s]

//         int low = 0;                  // Start boundary for 0s
//         int mid = 0;                  // Current index to process
//         int high = nums.size() - 1;   // End boundary for 2s

//         // Process elements until mid crosses high
//         while (mid <= high) {
//             if (nums[mid] == 0) {
//                 // Case 1: Current element is 0 (red)
//                 // → Put it in the front region by swapping with nums[low]
//                 swap(nums[low], nums[mid]);
//                 low++;   // Expand the 0s region
//                 mid++;   // Move forward to check next element
//             } else if (nums[mid] == 1) {
//                 // Case 2: Current element is 1 (white)
//                 // → Already in the correct middle region
//                 // → Just move mid forward
//                 mid++;
//             } else {
//                 // Case 3: Current element is 2 (blue)
//                 // → Put it in the back region by swapping with nums[high]
//                 swap(nums[mid], nums[high]);
//                 high--;  // Shrink the 2s region
//                 // Notice: we do NOT increment mid here
//                 // because the swapped element at nums[mid] needs to be checked again
//             }
//         }
//     }
// };


/*
Dutch National Flag Algorithm (LeetCode 75):

Think of the array as a row of colored balls:
- Red (0), White (1), Blue (2).
We want them grouped in order: [Red | White | Blue].

We use three pointers:
- low → boundary for reds (0s)
- mid → current ball we are checking
- high → boundary for blues (2s)

Steps:
1. If mid points to a red (0), swap it to the front (low), then move both low and mid forward.
2. If mid points to a white (1), it’s already in the middle, just move mid forward.
3. If mid points to a blue (2), swap it to the back (high), then move high backward.
   (Do not move mid yet, because the swapped element must be checked.)

Analogy:
Imagine sorting laundry:
- Put red shirts in the left basket (low).
- Put white shirts in the middle basket (leave them).
- Put blue shirts in the right basket (high).
You keep checking one shirt at a time (mid), and place it in the correct basket.

Result:
All 0s grouped at the start, 1s in the middle, 2s at the end.
This is done in ONE PASS with CONSTANT extra space.
*/





// class Solution {
// public:
//     void sortColors(vector<int>& nums) {
//         int low = 0, mid = 0;
//         int high = nums.size() - 1;

//         while (mid <= high) {
//             if (nums[mid] == 0) {
//                 swap(nums[low], nums[mid]);
//                 low++;
//                 mid++;
//             } else if (nums[mid] == 1) {
//                 mid++;
//             } else { // nums[mid] == 2
//                 swap(nums[mid], nums[high]);
//                 high--;
//             }
//         }
//     }
// };


// ============================================================
// LEETCODE 75: SORT COLORS  (Dutch National Flag Algorithm)
// Pattern: Three Pointers / Partitioning (a specialized two-pointer variant)
// ============================================================

class Solution {
public:
    void sortColors(vector<int>& nums) {

        // ------------------------------------------------------------
        // THE CORE IDEA (read this before anything else):
        // We are partitioning the array into 3 REGIONS using 3 pointers.
        // At any point during the algorithm, the array looks like:
        //
        //   [ 0 0 0 | 1 1 1 | ??????? | 2 2 2 ]
        //     ^low       ^mid          ^high
        //
        // - Everything BEFORE low   -> confirmed 0s (sorted, locked)
        // - Between low and mid     -> confirmed 1s (sorted, locked)
        // - Between mid and high    -> UNKNOWN / unprocessed zone
        // - Everything AFTER high   -> confirmed 2s (sorted, locked)
        //
        // 'mid' is our ACTIVE scanner — it walks through the unknown
        // zone element by element and decides where that element
        // truly belongs, then physically moves it there via swap.
        // ------------------------------------------------------------

        int low = 0, mid = 0;          // low: boundary for 0s, mid: current scanner
        int high = nums.size() - 1;    // high: boundary for 2s (from the right)

        // We stop scanning once mid crosses high — because everything
        // beyond high is already known to be 2, no need to check it.
        while (mid <= high) {

            if (nums[mid] == 0) {
                // Current element is a 0. It belongs in the "0 zone",
                // which ends right at index 'low'.
                // Swap brings the 0 to its rightful place, and whatever
                // was sitting at 'low' comes to 'mid'.
                // IMPORTANT: whatever was at nums[low] can ONLY be a 0 or 1
                // (never a 2) — because mid has already scanned past that
                // position earlier and would've moved any 2 out of the way.
                // That's why it's SAFE to advance mid here too.
                swap(nums[low], nums[mid]);
                low++;   // 0-zone grows by one
                mid++;   // this position is now confirmed correct, move on

            } else if (nums[mid] == 1) {
                // A 1 is already exactly where it should be —
                // right in the middle zone. No swap needed.
                // Just expand the "known" region by moving mid forward.
                mid++;

            } else {
                // nums[mid] == 2
                // This element belongs at the END (2-zone), so we swap
                // it with whatever is at 'high' (the current right edge
                // of the unknown zone), then shrink high by 1.
                //
                // CRITICAL DIFFERENCE from the 0-case:
                // We do NOT increment mid here!
                // Why? Because the element we just swapped in from
                // nums[high] is COMPLETELY UNKNOWN — it could be a 0, 1,
                // or another 2 (we've never looked at it before).
                // So mid must re-examine this new value in the next
                // iteration before deciding to move forward.
                swap(nums[mid], nums[high]);
                high--;  // 2-zone grows by one (from the right side)
                // mid stays the same on purpose — re-check this index next loop
            }
        }
        // Loop ends when mid > high, meaning the entire "unknown zone"
        // has shrunk to nothing — every element has been classified
        // and placed. Array is now fully sorted in one pass.
    }
};

// ============================================================
// REVISION SUMMARY (read this block for a 30-second refresher)
// ============================================================
//
// ANALOGY: Imagine sorting 3 colors of balls — Red(0), White(1), Blue(2) —
// laid out in a single row. You have 3 helpers standing at positions:
//   - "low"  guards the boundary of the Red section (left side)
//   - "high" guards the boundary of the Blue section (right side)
//   - "mid"  is the WORKER walking through the messy middle,
//            picking up each ball and deciding where it truly belongs.
//
// Every time mid finds:
//   - a RED ball  -> hands it to 'low', low's old ball comes to mid
//                    (safe to trust it, so worker moves forward too)
//   - a WHITE ball -> it's already in the right zone, just step forward
//   - a BLUE ball  -> throws it all the way to 'high's position,
//                    but whatever comes back is a MYSTERY ball,
//                    so the worker does NOT move — must inspect it again
//
// WHY THIS WORKS (Loop Invariant):
// [0..low-1] = all 0s | [low..mid-1] = all 1s |
// [mid..high] = unexplored | [high+1..end] = all 2s
// This invariant holds true before AND after every iteration —
// that's the mathematical guarantee the algorithm is correct.
//
// TIME COMPLEXITY: O(n)
//   - Single pass. 'mid' always moves forward or stays (never goes back).
//   - In the worst case, mid and high each traverse at most n elements
//     total across the whole run, so total work is linear, not quadratic.
//
// SPACE COMPLEXITY: O(1)
//   - Only 3 integer pointers used, in-place swaps, no extra array.
//
// COMMON MISTAKES:
//   1. Incrementing mid after the "== 2" swap case.
//      -> WRONG, because the newly swapped-in value from 'high' is
//         unverified and might itself be a 0 or another 2.
//   2. Using mid++ AND high-- together thinking it's symmetric to the
//      0-case. It's NOT symmetric — 0-case swaps with an already-vetted
//      region (before mid), 2-case swaps with an unvetted region
//      (beyond high). That asymmetry is the whole trick of this problem.
//   3. Using `mid < high` instead of `mid <= high` as loop condition —
//      this can leave the last unprocessed element unchecked.
//
// TRIGGER WORDS for this pattern:
//   "sort an array with only 3 distinct values", "in-place, one pass",
//   "partition into 3 groups", "Dutch National Flag", "0s 1s 2s"
//   -> think: 3-pointer partitioning, NOT a generic sorting algorithm.
//
// COMPANIES that ask this:
//   Microsoft, Amazon, Adobe, Meta — often as a quick warm-up question
//   to test if you understand invariants and partitioning logic, or as
//   a building block inside a larger problem (like Quickselect/QuickSort
//   partition step, which uses very similar logic).
// ============================================================