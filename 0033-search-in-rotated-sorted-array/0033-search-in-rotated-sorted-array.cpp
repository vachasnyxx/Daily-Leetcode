// class Solution {
// public:
//     int findPivot(vector<int>& nums, int n) {
//         int l = 0;
//         int r = n - 1;

//         while (l < r) {
//             int mid = l + (r - l) / 2;

//             if (nums[mid] > nums[r]) {
//                 l = mid + 1;
//             }

//             else {
//                 r = mid;
//             }
//         }
//         return r;
//     }

//     int binarySearch(int l, int r, vector<int>& nums, int target) {
//         int idx = -1;

//         while (l <= r) {
//             int mid = l + (r - l) / 2;
//             if (nums[mid] == target) {
//                 idx = mid;
//                 break;
//             } else if (nums[mid] < target) {
//                 l = mid + 1;
//             } else {
//                 r = mid - 1;
//             }
//         }
//         return idx;
//     }

//     int search(vector<int>& nums, int target) {
//         int n = nums.size();

//         int pivot_index = findPivot(nums, n);

//         int idx = binarySearch(0, pivot_index - 1, nums,target); // left side of pivot index

//         if (idx != -1)
//             return idx;

//         idx = binarySearch(pivot_index, n - 1, nums,target); // rigth side icluding  pivot index

//         return idx;
//     }
// };



// ============================================================
// LEETCODE 33 - SEARCH IN ROTATED SORTED ARRAY
// Pattern: Binary Search (Modified) on a "broken" sorted array
// ============================================================

class Solution {
public:

    // --------------------------------------------------------
    // FUNCTION 1: findPivot()
    // --------------------------------------------------------
    // INTUITION:
    // A rotated sorted array is basically a normal sorted array
    // that got "cut" at some point and the front piece was
    // attached to the back. Example:
    //   Original: [0,1,2,4,5,6,7]
    //   Rotated:  [4,5,6,7,0,1,2]
    //
    // The "pivot" is the index of the SMALLEST element — this is
    // exactly the point where the rotation break happens.
    // Once we know this index, the array splits cleanly into
    // TWO individually sorted halves:
    //   Left half  = [0 ... pivot-1]   (the "tail end" values, still large)
    //   Right half = [pivot ... n-1]   (the "wrapped around" small values)
    //
    // WHY BINARY SEARCH WORKS HERE:
    // Even though the whole array isn't sorted, at every mid point
    // we can still tell WHICH side is sorted by comparing nums[mid]
    // with nums[r]. That's the key trick that makes O(log n) possible
    // instead of a dumb O(n) linear scan.
    // --------------------------------------------------------
    int findPivot(vector<int>& nums, int n) {
        int l = 0;
        int r = n - 1;

        while (l < r) {
            int mid = l + (r - l) / 2;

            // CASE A: nums[mid] > nums[r]
            // Meaning: mid is still "large" (part of the untouched
            // original tail), and somewhere AFTER mid, values drop
            // suddenly (that's the wraparound). So the minimum
            // (pivot) must be strictly to the right of mid.
            // => discard left half including mid, move l forward.
            if (nums[mid] > nums[r]) {
                l = mid + 1;
            }

            // CASE B: nums[mid] <= nums[r]
            // Meaning: from mid to r, the segment is already sorted
            // in increasing order (no break in between). So the
            // minimum is either mid itself, or somewhere to its left.
            // We CANNOT do r = mid - 1 here because mid might BE
            // the answer — shrinking past it would lose the pivot.
            else {
                r = mid;
            }
        }

        // Loop ends when l == r --> both pointers have converged
        // exactly on the index of the minimum element (the pivot).
        return r;
    }

    // --------------------------------------------------------
    // FUNCTION 2: binarySearch()
    // --------------------------------------------------------
    // This is your bread-and-butter, textbook binary search.
    // It only works correctly because we ALWAYS call it on a
    // range [l, r] that is guaranteed to be fully sorted
    // (either the left half or the right half from findPivot).
    // --------------------------------------------------------
    int binarySearch(int l, int r, vector<int>& nums, int target) {
        int idx = -1;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (nums[mid] == target) {
                idx = mid;   // Found it — record index and stop.
                break;
            } else if (nums[mid] < target) {
                // target is bigger than mid's value, and since this
                // segment is sorted, target can only live to the right.
                l = mid + 1;
            } else {
                // target is smaller than mid's value, so it must be
                // to the left (again, only valid because sorted).
                r = mid - 1;
            }
        }
        return idx;
    }

    // --------------------------------------------------------
    // FUNCTION 3: search()  -- the orchestrator / main driver
    // --------------------------------------------------------
    // STRATEGY:
    // 1. Find the pivot (index of minimum element) --> O(log n)
    // 2. This pivot splits the array into two sorted zones:
    //      Left zone  : [0, pivot_index - 1]
    //      Right zone : [pivot_index, n - 1]
    // 3. Run a normal binary search on EACH zone until we find
    //    the target. Whichever zone contains it will return a
    //    valid index; the other will return -1.
    //
    // NOTE: We don't need to figure out "which half is the target
    // actually in" using range comparisons (though that's another
    // valid single-pass approach) — here we just brute-force check
    // both sorted halves with two clean binary searches. Simpler
    // to reason about, same O(log n) complexity overall.
    // --------------------------------------------------------
    int search(vector<int>& nums, int target) {
        int n = nums.size();

        // Step 1: locate the rotation break point.
        int pivot_index = findPivot(nums, n);

        // Step 2: try the left sorted half first.
        int idx = binarySearch(0, pivot_index - 1, nums, target);

        if (idx != -1)
            return idx;   // Found on the left half, done.

        // Step 3: if not found on the left, try the right sorted
        // half (this range INCLUDES pivot_index itself, since the
        // minimum element is also a valid candidate for the target).
        idx = binarySearch(pivot_index, n - 1, nums, target);

        return idx;   // Either the found index, or -1 if truly absent.
    }
};

// ============================================================
// SUMMARY BLOCK FOR REVISION (read this first when revisiting)
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// You're given a sorted array that got "rotated" — like a deck
// of cards cut at some point and the bottom half placed on top.
// You need to find a target value in O(log n) time, without
// scanning the whole thing.
//
// THE ANALOGY (for permanent memory):
// Imagine a circular running track with numbered mile-markers
// increasing from 0 to 100, but someone erased the "start line"
// paint and repainted it at a random point on the track. You still
// walk in increasing order all the way around, then it suddenly
// drops back down at the NEW start line, then climbs again.
// That "sudden drop" point is the PIVOT — it's the seam where
// the track was "cut and rejoined."
// Once you find that seam, you have two straight, honestly-sorted
// running strips. Searching for a specific mile-marker in either
// strip is just... normal binary search.
//
// THE CORE TRICK (why binary search still works on a "broken" array):
// At any midpoint, compare nums[mid] to nums[r] (the rightmost
// value of the current window):
//   - If nums[mid] > nums[r]  --> the seam (pivot) is to the RIGHT
//     of mid, because values are still "high" here, meaning the
//     drop hasn't happened yet.
//   - If nums[mid] <= nums[r] --> no seam between mid and r, so
//     this side is already sorted; the seam (if it exists) is at
//     mid or somewhere to the LEFT.
//
// STEP-BY-STEP MENTAL CHECKLIST:
//   1. Find the pivot (minimum element index) using the seam-detection
//      binary search above.
//   2. That pivot cuts the array into two clean sorted zones.
//   3. Binary search zone 1 (left of pivot). If found, return.
//   4. Otherwise binary search zone 2 (pivot to end). Return result.
//
// COMPLEXITY:
//   Time  -> O(log n): two independent binary searches, each halving
//            the search space every step.
//   Space -> O(1): just a few integer pointers, no extra arrays.
//
// COMMON MISTAKES TO AVOID:
//   1. Writing "r = mid - 1" in the findPivot else-branch instead of
//      "r = mid". This can skip over the actual minimum since mid
//      itself might BE the pivot.
//   2. Comparing nums[mid] to nums[l] instead of nums[r] when hunting
//      for the pivot. This breaks silently when the array has NO
//      rotation at all (pivot = index 0), because nums[mid] >= nums[l]
//      is trivially true in a normal sorted run, giving no real signal.
//   3. Forgetting that the right-half binary search range must START
//      AT pivot_index (not pivot_index + 1) since the minimum element
//      itself is a valid target candidate.
//
// TRIGGER WORDS TO RECOGNIZE THIS PATTERN INSTANTLY:
//   "rotated sorted array", "sorted array with unknown rotation point",
//   "find element in O(log n) in a shifted sorted array"
//   --> Immediately think: modified binary search comparing mid
//       against the boundary (nums[r] or nums[l]), NOT linear scan.
//
// WHERE THIS SHOWS UP IN INTERVIEWS:
//   Frequently asked at Amazon, Microsoft, and Flipkart as a standalone
//   question, and often as a stepping stone before harder variants:
//   - LeetCode 153/154: Find Minimum in Rotated Sorted Array (I & II)
//   - LeetCode 81: Search in Rotated Sorted Array II (with duplicates)
// ============================================================