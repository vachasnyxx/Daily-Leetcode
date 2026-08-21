// class Solution {
// public:
//     int waysToSplitArray(vector<int>& nums) {
//         int n = nums.size();

//         long long sum = 0;
//         for(int i = 0; i<n; i++){
//             sum += nums[i];
//         }

//         long long leftsum = 0;
//         long long rightsum = 0;
//         int split = 0;

//         for(int i = 0; i < n-1; i++){
//             leftsum += nums[i];
//             rightsum = sum - leftsum;
//             if(leftsum >= rightsum){
//                 split++;
//             }
//         }
//         return split;
//     }
// };




// ============================================================================
// LeetCode 2574: Left and Right Sum Differences (Ways to Split Array)
// PATTERN: Prefix Sums (running left sum + total sum trick)
// ============================================================================
//
// PROBLEM RECAP: Given an array nums, count the number of indices i (0 <= i
// < n-1) such that the sum of elements to the left of i (inclusive) is
// greater than or equal to the sum of elements to the right of i (exclusive).
// In other words, count valid split points where leftSum >= rightSum.

class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        int n = nums.size();

        // ------------------------------------------------------------
        // STEP 1: Compute the TOTAL sum of the array in one pass.
        // WHY: We'll need the right sum for every split point, and
        // rightSum = totalSum - leftSum. Computing total once lets us
        // get rightSum in O(1) for each index instead of re-scanning.
        // ------------------------------------------------------------
        long long sum = 0;
        for(int i = 0; i < n; i++){
            sum += nums[i];
        }

        // ------------------------------------------------------------
        // STEP 2: Walk through the array maintaining a RUNNING left sum.
        // At each index i (from 0 to n-2), we consider splitting BETWEEN
        // i and i+1. The left part is nums[0..i], the right part is
        // nums[i+1..n-1].
        //
        // WHY stop at n-2 (i < n-1)? Because a valid split must leave at
        // least ONE element on the right side. If i == n-1, the right
        // part would be empty, which is not allowed by the problem.
        // ------------------------------------------------------------
        long long leftsum = 0;
        long long rightsum = 0;
        int split = 0;

        for(int i = 0; i < n - 1; i++){
            // Add the current element to the left partition.
            leftsum += nums[i];

            // Derive the right partition sum in O(1) using the total sum.
            rightsum = sum - leftsum;

            // Check the condition: left part sum >= right part sum.
            if(leftsum >= rightsum){
                split++;
            }
            // If false, we simply move on — this split point is invalid.
        }

        return split;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: Count how many ways you can cut the array into two non-empty
// parts so that the left part's sum is at least as big as the right part's.
//
// ANALOGY — "Cutting a chocolate bar":
// Imagine a long chocolate bar with nuts of different sizes embedded along
// it. You want to snap it at some point so that the left piece has at least
// as much "nutty goodness" as the right piece. You first weigh the whole bar
// (total sum), then walk along it, keeping a running tally of how much you've
// passed so far (left sum). At each potential snap point, the right piece's
// weight is just "total minus what you've already passed". Count every snap
// where left >= right. That's it.
//
// WHY THIS IS A PREFIX-SUM PATTERN:
//   - We need sums of prefixes (left parts) and suffixes (right parts) at
//     many different split points.
//   - Instead of recomputing sums from scratch for each split (O(n^2)), we
//     precompute the total once, then maintain a running left sum. Right sum
//     becomes a simple subtraction: right = total - left.
//   - This reduces the problem to O(n) time, O(1) extra space.
//
// TRIGGER WORDS for this pattern:
//   "count split points", "prefix sum vs suffix sum", "left part sum >= right
//   part sum", "number of ways to divide array into two parts with some sum
//   condition" => Think: Prefix Sums + running cumulative sum.
//
// TWO-STEP TEMPLATE (memorize this shape for all prefix-sum split problems):
//   1. Compute totalSum in one pass: O(n).
//   2. Iterate i from 0 to n-2:
//        leftSum += nums[i]
//        rightSum = totalSum - leftSum
//        if (condition on leftSum vs rightSum) count++
//   Return count.
//
// COMPLEXITY:
//   - Time: O(n) — two linear passes (one for total, one for splits).
//   - Space: O(1) extra — just a few scalar variables.
//
// COMMON MISTAKES (why they happen):
//   1. Looping i up to n-1 instead of n-2 — this would allow an empty right
//      partition, which violates the problem's "non-empty parts" rule.
//   2. Using int for sums when nums can be large or n is large — sums can
//      overflow 32-bit int, so always use long long for prefix sums in
//      competitive programming unless constraints guarantee safety.
//   3. Recomputing right sum from scratch for each split (nested loop) —
//      this turns an O(n) problem into O(n^2), which TLEs on large inputs.
//
// COMPANIES: Prefix-sum split problems are staples in Amazon, Google, and
// Microsoft OA rounds, and pair naturally with problems like:
//   - LC 1712: Ways to Split Array Into Three Subarrays (similar prefix-sum
//     logic, but with two split points and modulo arithmetic).
//   - LC 1013: Partition Array Into Three Parts With Equal Sum (check if
//     total is divisible by 3, then find split points).
//   - LC 1431: Kids With the Greatest Number of Candies (prefix max + sum
//     trick, though simpler).
// Once you see "split the array into parts with sum conditions", your brain
// should immediately reach for prefix sums and the total-minus-left trick.
// ============================================================================