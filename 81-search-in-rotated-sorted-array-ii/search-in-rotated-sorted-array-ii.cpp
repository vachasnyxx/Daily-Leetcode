// // ============================================================
// // LEETCODE 81 - SEARCH IN ROTATED SORTED ARRAY II
// // Pattern: Binary Search (Modified) on a "broken" sorted array WITH DUPLICATES
// // ============================================================
// //
// // PLAIN ENGLISH DEFINITION:
// // Same as LC 33, but now the array can contain duplicates.
// // Return true if the target exists, false otherwise.
// // Duplicates break the "compare mid to boundary" trick sometimes,
// // so we need an extra step: skip identical values from both ends
// // before deciding which half to discard.
// //
// // THE ANALOGY (for permanent memory):
// // Imagine the same circular running track from LC 33/153, but now
// // some mile-markers are repainted with the SAME number (duplicates).
// // When you stand at mid and look at the right end, sometimes both
// // show the same number — you can't tell if you're on the "high"
// // side or the "low" side anymore. So before making any decision,
// // you first walk inward from both ends, skipping over repeated
// // numbers, until you see distinct values again. Only then can you
// // safely use the old "nums[mid] > nums[r]" rule to find the seam.
// //
// // WHY BINARY SEARCH STILL WORKS HERE (with a small tweak):
// // Duplicates can make nums[mid] == nums[r] even when the seam is
// // on either side. The fix: shrink the window from both ends by
// // skipping equal neighbors until you hit a difference (or until
// // l == r). After that, the classic pivot-finding logic works again.
// // ============================================================

// class Solution {
// public:
//     // --------------------------------------------------------
//     // FUNCTION 1: findpivot()
//     // --------------------------------------------------------
//     // INTUITION:
//     // Same as LC 153, but now we must handle duplicates.
//     // Before comparing nums[mid] to nums[r], we skip identical
//     // values from both the left and right ends. This ensures
//     // that when we do the comparison, we're actually comparing
//     // distinct values that give us a reliable signal about which
//     // half contains the seam (minimum element).
//     // --------------------------------------------------------
//     int findpivot(vector<int>& nums, int l, int r) {
//         while (l < r) {
//             // Skip duplicates from the left end:
//             // If nums[l] == nums[l+1], we can't trust l as a
//             // boundary for comparison, so move l forward.
//             while (l < r && nums[l] == nums[l + 1]) {
//                 l++;
//             }

//             // Skip duplicates from the right end:
//             // If nums[r] == nums[r-1], we can't trust r as a
//             // boundary for comparison, so move r backward.
//             while (l < r && nums[r] == nums[r - 1]) {
//                 r--;
//             }

//             // After skipping duplicates, l and r might have met.
//             // If so, we've converged on the minimum — return it.
//             if (l >= r) {
//                 break;
//             }

//             int mid = l + (r - l) / 2;

//             // Now the classic LC 153 logic applies:
//             // If nums[mid] > nums[r], the seam (minimum) is
//             // strictly to the RIGHT of mid.
//             if (nums[mid] > nums[r]) {
//                 l = mid + 1;
//             } else {
//                 // Otherwise, the seam is at mid or to the LEFT.
//                 r = mid;
//             }
//         }
//         return l; // pivot index (index of minimum element)
//     }

//     // --------------------------------------------------------
//     // FUNCTION 2: binarySearch()
//     // --------------------------------------------------------
//     // This is your bread-and-butter, textbook binary search.
//     // It only works correctly because we ALWAYS call it on a
//     // range [l, r] that is guaranteed to be fully sorted
//     // (either the left half or the right half from findpivot).
//     // --------------------------------------------------------
//     bool binarySearch(vector<int>& nums, int l, int r, int target) {
//         while (l <= r) {
//             int mid = l + (r - l) / 2;
//             if (nums[mid] == target) {
//                 return true;
//             } else if (nums[mid] < target) {
//                 l = mid + 1;
//             } else {
//                 r = mid - 1;
//             }
//         }
//         return false;
//     }

//     // --------------------------------------------------------
//     // FUNCTION 3: search()  -- the orchestrator / main driver
//     // --------------------------------------------------------
//     // STRATEGY:
//     // 1. Find the pivot (index of minimum element) --> O(log n)
//     //    (with duplicate-skipping to handle the LC 81 twist)
//     // 2. This pivot splits the array into two sorted zones:
//     //      Left zone  : [0, pivot - 1]
//     //      Right zone : [pivot, n - 1]
//     // 3. Run a normal binary search on EACH zone until we find
//     //    the target. If either returns true, the target exists.
//     //
//     // NOTE: We don't need to figure out "which half is the target
//     // actually in" using range comparisons (though that's another
//     // valid single-pass approach) — here we just brute-force check
//     // both sorted halves with two clean binary searches. Simpler
//     // to reason about, same O(log n) complexity overall.
//     // --------------------------------------------------------
//     bool search(vector<int>& nums, int target) {
//         int n = nums.size();
//         if (n == 0) {
//             return false;
//         }

//         int pivot = findpivot(nums, 0, n - 1);

//         // Search both halves to be safe
//         return binarySearch(nums, 0, pivot - 1, target) ||
//                binarySearch(nums, pivot, n - 1, target);
//     }
// };

// // ============================================================
// // SUMMARY BLOCK FOR REVISION (read this first when revisiting)
// // ============================================================
// //
// // PLAIN ENGLISH DEFINITION:
// // You're given a sorted array that got "rotated" — like a deck
// // of cards cut at some point and the bottom half placed on top —
// // but now it can contain duplicates. Return true if the target
// // exists, false otherwise, in O(log n) average time (worst case
// // O(n) when all elements are identical).
// //
// // THE ANALOGY (for permanent memory):
// // Imagine the same circular running track from LC 33/153, but now
// // some mile-markers are repainted with the SAME number (duplicates).
// // When you stand at mid and look at the right end, sometimes both
// // show the same number — you can't tell if you're on the "high"
// // side or the "low" side anymore. So before making any decision,
// // you first walk inward from both ends, skipping over repeated
// // numbers, until you see distinct values again. Only then can you
// // safely use the old "nums[mid] > nums[r]" rule to find the seam.
// //
// // THE CORE TRICK (why binary search still works with duplicates):
// // Duplicates can make nums[mid] == nums[r] even when the seam is
// // on either side. The fix: shrink the window from both ends by
// // skipping equal neighbors until you hit a difference (or until
// // l == r). After that, the classic pivot-finding logic works again.
// //
// // STEP-BY-STEP MENTAL CHECKLIST:
// //   1. If array is empty, return false.
// //   2. Find the pivot (minimum element index) using the duplicate-
// //      skipping binary search above.
// //   3. That pivot cuts the array into two clean sorted zones.
// //   4. Binary search zone 1 (left of pivot). If found, return true.
// //   5. Otherwise binary search zone 2 (pivot to end). Return result.
// //
// // COMPLEXITY:
// //   Time  -> O(log n) average, but O(n) worst case when all
// //            elements are identical (you have to skip them all).
// //   Space -> O(1): just a few integer pointers, no extra arrays.
// //
// // COMMON MISTAKES TO AVOID:
// //   1. Forgetting to skip duplicates from BOTH ends before comparing
// //      nums[mid] to nums[r]. Skipping only one side can still leave
// //      you with ambiguous boundaries.
// //   2. Not checking "l >= r" after the duplicate-skipping loops.
// //      Without this early exit, you can compute mid on a shrunken
// //      window where l == r, then still move l or r and break the
// //      pivot guarantee.
// //   3. Assuming O(log n) worst-case time. With all duplicates, the
// //      algorithm degrades to O(n) — this is unavoidable and expected.
// //
// // TRIGGER WORDS TO RECOGNIZE THIS PATTERN INSTANTLY:
// //   "rotated sorted array with duplicates", "search in O(log n) in a
// //   shifted sorted array that may have repeats"
// //   --> Immediately think: modified binary search with duplicate-
// //       skipping from both ends, then classic seam-finding logic.
// //
// // WHERE THIS SHOWS UP IN INTERVIEWS:
// //   Frequently asked at Amazon, Microsoft, and Flipkart as a follow-up
// //   to LC 33. Related/likely follow-ups:
// //   - LeetCode 33: Search in Rotated Sorted Array (no duplicates)
// //   - LeetCode 153/154: Find Minimum in Rotated Sorted Array (I & II)
// // ============================================================




class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // Found target
            if (nums[mid] == target) return true;

            // Handle duplicates: shrink search space
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;
                right--;
            }
            // Left half is sorted
            else if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1; // target in left half
                } else {
                    left = mid + 1;  // target in right half
                }
            }
            // Right half is sorted
            else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;  // target in right half
                } else {
                    right = mid - 1; // target in left half
                }
            }
        }
        return false;
    }
};
