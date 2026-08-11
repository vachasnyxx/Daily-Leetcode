// LeetCode 560 - Subarray Sum Equals K
// Pattern: Prefix Sum + Hash Map (frequency counting)
// ---------------------------------------------------------------------------

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

        // WHY A HASH MAP AT ALL?
        // Brute force checks every (i, j) pair of subarray boundaries -> O(n^2).
        // We want O(n). The trick: instead of re-summing every subarray,
        // track the RUNNING TOTAL (prefix sum) as we scan left to right,
        // and ask a smarter question at each step: "has some EARLIER running
        // total already occurred such that current - earlier = k?"
        // If yes, the elements BETWEEN that earlier point and now form a
        // subarray that sums exactly to k. The hash map lets us answer
        // "has this value occurred, and how many times" in O(1).
        unordered_map<int, int> freq;
        // freq[x] = number of prefix sums seen so far that equal x.
        // We store COUNTS, not just true/false, because the SAME prefix sum
        // value can repeat at multiple indices (e.g. a zero or negative
        // number brings the running total back to a value seen before).
        // Each repeat represents a DIFFERENT valid subarray ending at the
        // current index, so we must add ALL of them, not just detect one.

        freq[0] = 1;
        // CRITICAL BASE CASE. This represents the "empty prefix" -
        // i.e., the state of the array BEFORE we've read any elements,
        // where the running total is naturally 0.
        // Why we need it: if the very first few elements themselves sum to
        // k (a subarray starting at index 0), then prefixsum - k will
        // equal 0 at that point. Without freq[0] = 1 pre-loaded, that
        // valid subarray would never be counted because "0" would look
        // like it never occurred. This single line is the most commonly
        // forgotten part of this pattern - forgetting it silently drops
        // every valid subarray that starts at index 0.

        int prefixsum = 0;
        // Running total of all elements read so far (from index 0 up to
        // and including the current element). Think of this as an
        // odometer reading on a road trip - it only ever reflects
        // "how far have I travelled since the start," never a segment.

        int count = 0;
        // Total number of valid subarrays found so far, summed across
        // every index where a match was found.

        for (int num : nums) {

            prefixsum += num;
            // Step the odometer forward by the current element's value.
            // After this line, prefixsum = sum(nums[0..currentIndex]).

            // THE CORE INSIGHT OF THIS PATTERN:
            // We want to know: does there exist some earlier index i such
            // that sum(nums[i+1..currentIndex]) == k ?
            // Since sum(nums[i+1..currentIndex]) = prefixsum(current) - prefixsum(i),
            // setting that equal to k and rearranging gives:
            //     prefixsum(i) = prefixsum(current) - k
            // So instead of searching for a SUBARRAY, we just search for
            // whether a specific PAST PREFIX SUM VALUE has occurred.
            // That's why checking freq.find(prefixsum - k) works -
            // it converts a subarray-sum question into a simple lookup.
            if (freq.find(prefixsum - k) != freq.end()) {
                count += freq[prefixsum - k];
                // Add ALL past occurrences of this target value, because
                // EACH occurrence corresponds to a DISTINCT valid subarray
                // ending at the current index (they started at different
                // earlier positions but all satisfy the sum == k condition).
            }

            // ORDERING MATTERS HERE - THIS LINE COMES AFTER THE CHECK ABOVE.
            // We record the CURRENT prefix sum into the map only AFTER
            // checking for a match. If we recorded it BEFORE checking,
            // and k happened to be 0, we would incorrectly count the
            // current index against itself (a zero-length "subarray"),
            // inflating the answer. Always check first, then update.
            freq[prefixsum]++;
        }

        return count;
    }
};

// ===========================================================================
// REVISION SUMMARY - READ THIS FIRST WHEN YOU COME BACK IN A FEW MONTHS
// ===========================================================================
//
// THE ANALOGY:
// You're on a road trip and your car's odometer only ever counts UP from
// when you started (it never resets). At every town you pass, you jot
// down the odometer reading in a notebook, along with how many times
// you've seen that exact reading before (in case your trip loops back
// on itself). Now, at any new town, you ask: "if I subtract k kilometers
// from today's odometer reading, does that number appear in my notebook?"
// If it does, it means there was some earlier town exactly k kilometers
// behind you on the odometer - meaning the road BETWEEN that town and
// here covered exactly k kilometers. That's your subarray of sum k.
//
// THE ALGEBRA IN ONE LINE:
// subarray(i+1, j) sums to k  <=>  prefixSum(j) - prefixSum(i) = k
//                              <=>  prefixSum(i) = prefixSum(j) - k
// So at every index j, just check: "has prefixSum(j) - k occurred before,
// and how many times?" That count IS the number of valid subarrays
// ending at j.
//
// WHY A HASH MAP (not a set, not an array):
// - We need O(1) lookups            -> hash map beats linear search.
// - We need to know MULTIPLICITY    -> a set only tells us yes/no, but
//   the same prefix sum can occur at multiple earlier indices, each one
//   giving a separate valid subarray, so we need COUNTS, not booleans.
//
// THE ONE LINE EVERYONE FORGETS:
// freq[0] = 1 before the loop starts. This accounts for subarrays that
// start right at index 0. Skip it, and you undercount.
//
// THE ONE ORDERING RULE EVERYONE GETS WRONG:
// Check freq[prefixsum - k] BEFORE doing freq[prefixsum]++. Reversing
// the order causes the current index to be able to match against
// itself when k == 0, corrupting the count.
//
// COMPLEXITY:
// Time  = O(n) - single pass, O(1) average hash map operations.
// Space = O(n) - worst case, every prefix sum is distinct, so the map
//                grows to hold n+1 entries (including the base case).
//
// WHEN TO REACH FOR THIS PATTERN AGAIN:
// Any time you see "count subarrays/substrings with sum/property X" AND
// the array can contain negative numbers, zero, or you need an exact
// target (not just "maximum" or "minimum"). If sliding window suddenly
// feels broken because shrinking the window doesn't make sense with
// negative numbers present - that's your signal to switch to this
// prefix sum + hash map pattern instead.










// class Solution {
// public:
//     int subarraySum(vector<int>& nums, int k) {
//         unordered_map<int, int> freq; 
//         // freq[prefixsum] = how many times this prefix sum has occurred
//         // This helps us quickly check if (prefixsum - k) existed before

//         freq[0] = 1; // base case: prefix sum = 0 occurs once

//         int prefixsum = 0; // running sum of elements
//         int count = 0;     // number of valid subarrays

//         for (int num : nums) {
//             prefixsum += num; // update running sum

//             // If prefixsum - k exists, it means there’s a subarray ending here with sum = k
//             if (freq.find(prefixsum - k) != freq.end()) {
//                 count += freq[prefixsum - k];
//             }

//             // Record this prefix sum occurrence
//             freq[prefixsum]++;
//         }

//         return count;
//     }
// };




/// Brute force approach
// class Solution {
// public:
//     int subarraySum(vector<int>& nums, int k) {
//         int count = 0;
//         for(int l = 0; l<nums.size(); l++){
//             int sum =0;
//             for(int r = l; r < nums.size(); r++){
//                 sum+= nums[r];
//                 if(sum == k){
//                     count++;
//                 }
//             }
//         }
//         return count;
//     }
// };