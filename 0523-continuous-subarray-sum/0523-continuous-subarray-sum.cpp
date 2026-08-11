// ============================================================
// LeetCode 523 - Continuous Subarray Sum
// Pattern: Prefix Sum + Hashmap (Remainder Bucketing)
// ============================================================

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {

        // -----------------------------------------------------------
        // WHY A HASHMAP? 
        // We need to know: "have I seen this exact remainder before,
        // and if so, at what index?" A hashmap gives O(1) lookup for
        // that question instead of re-scanning the array each time.
        //
        // Key   -> the remainder (prefixSum % k)
        // Value -> the EARLIEST index at which that remainder occurred
        // -----------------------------------------------------------
        unordered_map<int, int> mp;

        // -----------------------------------------------------------
        // THE BASE CASE: mp[0] = -1
        //
        // Think of -1 as "before the array even started."
        // This handles the scenario where the prefix sum from index 0
        // up to some index i is ALREADY divisible by k on its own
        // (remainder = 0). Without this entry, we'd have no anchor
        // point to measure the subarray length from, and we'd miss
        // valid answers like nums = [6, 4], k = 6 (subarray [6] alone
        // isn't length>=2, but consider nums=[2,4], prefixSum after
        // index1 = 6, remainder 0, length = 1 - (-1) = 2 -> valid!)
        // -----------------------------------------------------------
        mp[0] = -1;

        int prefixSum = 0;

        for (int i = 0; i < nums.size(); i++) {

            // Running total of everything from index 0 to i (inclusive).
            // This is the "odometer reading" at the current point in
            // our road trip analogy.
            prefixSum += nums[i];

            // -----------------------------------------------------------
            // THE CORE TRICK: modulo instead of raw sum.
            //
            // We don't care about the exact prefixSum value - we only
            // care about its "remainder bucket" when divided by k,
            // because:
            //
            //   If prefixSum[j] % k == prefixSum[i] % k  (for j < i)
            //   then (prefixSum[i] - prefixSum[j]) % k == 0
            //   which means the subarray nums[j+1 ... i] sums to a
            //   multiple of k.
            //
            // This is the "two odometers painted the same color at
            // different distances -> the gap between them is a clean
            // multiple of k" idea.
            // -----------------------------------------------------------
            int remainder = prefixSum % k;

            if (mp.find(remainder) != mp.end()) {
                // We've seen this exact remainder before at mp[remainder].
                // That means everything between that earlier index and
                // now (i) sums to a multiple of k.
                //
                // Why check "i - mp[remainder] >= 2" and not >= 1?
                // Because the problem demands subarray LENGTH >= 2.
                // If the earlier index was, say, 3 and now i = 4,
                // the subarray is nums[4..4] - just ONE element - which
                // is length 1, not allowed. We need at least a 2-gap.
                if (i - mp[remainder] >= 2) return true;

                // IMPORTANT: we do NOT update mp[remainder] = i here,
                // even though we found a match. Why? Because keeping
                // the EARLIEST index for each remainder gives every
                // future match the MAXIMUM possible subarray length.
                // If we overwrote it with a later index, we might
                // shrink future gaps below the length-2 threshold and
                // wrongly return false.
            } else {
                // First time seeing this remainder - lock in this index
                // as the earliest "sighting" so future matches get the
                // longest possible subarray length.
                mp[remainder] = i;
            }
        }

        // If we finish the loop without finding a valid pair, no
        // subarray of length >= 2 with sum divisible by k exists.
        return false;
    }
};

// ============================================================
// REVISION SUMMARY - READ THIS WHEN YOU FORGET EVERYTHING
// ============================================================
//
// THE ONE-LINER:
// "Same remainder at two different prefix-sum checkpoints means
//  the stuff IN BETWEEN those checkpoints is a clean multiple of k."
//
// THE ANALOGY (road trip with painted mile markers):
// Picture a highway where markers repeat their paint color every
// k kilometers (marker 0, k, 2k... = color A; marker 1, k+1... =
// color B; etc). If you see color A at km 10 and color A again at
// km 25, the 15 km you drove in between MUST be a whole multiple
// of k. That's exactly what "same remainder" means for prefix sums.
//
// WHY PREFIX SUM AT ALL?
// Instead of recomputing the sum of every possible subarray
// (O(n^2) brute force), we track a RUNNING total (prefixSum) as we
// walk through the array once. The sum of any subarray [j+1..i] is
// just prefixSum[i] - prefixSum[j]. So subarray-sum questions
// become "index-pair" questions.
//
// WHY MODULO k INSTEAD OF RAW PREFIX SUM?
// We only care about DIVISIBILITY by k, not the actual sum value.
// Two prefix sums that differ by a multiple of k will have the
// SAME remainder when divided by k. So instead of comparing raw
// sums, we bucket them by remainder - shrinking our "seen values"
// from potentially huge numbers down to just k possible buckets
// (0 to k-1).
//
// WHY mp[0] = -1 AT THE START?
// It's a placeholder for "the state of the world before the array
// began." It lets subarrays STARTING at index 0 be detected too,
// since there's no real "index -1" element to compare against
// otherwise.
//
// WHY KEEP FIRST OCCURRENCE, NOT THE LATEST?
// Longer gap = better odds of hitting the length>=2 requirement.
// Keeping the earliest index for each remainder maximizes every
// future subarray length calculation (i - mp[remainder]).
//
// COMPLEXITY:
// Time  -> O(n): one pass, O(1) average hashmap operations.
// Space -> O(min(n, k)): at most k distinct remainders can exist
//          (0 to k-1), or n if the array is shorter than k.
//
// COMMON BUGS TO AVOID:
// 1. Forgetting mp[0] = -1 (misses subarrays starting at index 0).
// 2. Overwriting mp[remainder] on every match (shrinks future gaps).
// 3. Checking "length >= 1" instead of "length >= 2" (problem
//    explicitly requires subarray size of at least 2).
//
// TRIGGER WORDS FOR THIS PATTERN:
// "subarray sum divisible by k", "continuous subarray sum",
// "prefix sum remainder", "subarray sum equals target" ->
// think prefix sum + hashmap bucketing by remainder or exact sum.
// ============================================================

















// class Solution {
// public:
//     bool checkSubarraySum(vector<int>& nums, int k) {
//         unordered_map<int, int> mp; 
//         mp[0] = -1; // handle case when prefix sum itself is divisible by k

//         int prefixSum = 0;
//         for (int i = 0; i < nums.size(); i++) {
//             prefixSum += nums[i];
            
//             // take modulo to reduce large sums

//             int remainder = prefixSum % k;
//             // if this mod was seen before, check subarray length
//             if (mp.find(remainder) != mp.end()) {
//                 if (i - mp[remainder] >= 2) return true;
//             } else {
//                 // store first occurrence of this mod
//                 mp[remainder] = i;
//             }
//         }
//         return false;
//     }
// };






// Brute force
// class Solution {
// public:
//     bool checkSubarraySum(vector<int>& nums, int k) {
//         int n  = nums.size();

//         for(int i=0; i < n-1; i++){
//             int sum  = nums[i];
//             for(int j = i+1; j<n; j++){
//                 sum += nums[j];
//                 if(sum % k == 0) return true;
//             }
//         }
//         return false;
//     }
// };