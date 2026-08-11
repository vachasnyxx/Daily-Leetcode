// LeetCode 974 - Subarray Sums Divisible by K
// Pattern: Prefix Sum + Hash Map (frequency counting) - same family as
// LeetCode 560 (Subarray Sum Equals K), but with a MODULO twist.
// ---------------------------------------------------------------------------

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {

        // SAME CORE FAMILY AS LC 560, DIFFERENT QUESTION BEING ASKED.
        // In 560 we asked: "does prefixSum(j) - prefixSum(i) == k ?"
        // Here we ask a DIVISIBILITY question instead: "is
        // (prefixSum(j) - prefixSum(i)) divisible by k ?"
        // A sum is divisible by k exactly when its REMAINDER when divided
        // by k is 0. So instead of tracking raw prefix sums, we track
        // prefix sum REMAINDERS (prefixSum % k). Two indices with the
        // SAME remainder mean everything between them sums to a multiple
        // of k - i.e. a subarray divisible by k.
        unordered_map<int, int> map;
        // map[r] = how many prefix sums seen so far have remainder r
        // when divided by k. Again we store COUNTS (not booleans) because
        // multiple earlier indices can share the same remainder, and each
        // one gives a distinct valid subarray ending at the current index.

        map[0] = 1;
        // BASE CASE, same reasoning as LC 560's freq[0] = 1.
        // Represents the "empty prefix" before any elements are read,
        // which has remainder 0. Needed so subarrays starting at index 0
        // that are themselves divisible by k get counted correctly.

        int count = 0;
        // Running total of subarrays found so far whose sum is divisible by k.

        int prefixsum = 0;
        // Running total of all elements read so far (the odometer).

        for (int num : nums) {

            prefixsum += num;
            // Advance the running total by the current element.

            int rem = prefixsum % k;
            // Compute the remainder of the running total when divided by k.
            // This remainder is what we actually track in the map - NOT
            // the raw prefixsum - because we only care about divisibility,
            // and infinitely many different prefixsum values can share the
            // exact same remainder (e.g. 7 % 5 == 2 and 12 % 5 == 2).
            // Grouping by remainder is what makes this pattern work in
            // O(n) instead of checking every pair of indices directly.

            if (rem < 0) {
                rem += k;
            }
            // C++ SPECIFIC GOTCHA: the % operator in C++ can return a
            // NEGATIVE result when prefixsum is negative (unlike Python,
            // where % always returns a non-negative result matching the
            // sign of the divisor). For example, -7 % 5 in C++ gives -2,
            // not 3. Mathematically, -7 and 3 belong to the SAME remainder
            // class mod 5 (both are "3 more than a multiple of 5"), so we
            // normalize by adding k whenever the result is negative. Skip
            // this step and negative-sum arrays will silently undercount,
            // because -2 and 3 would be treated as different remainder
            // buckets when they should be the same bucket.

            if (map.count(rem)) {
                count += map[rem];
                // Same logic as LC 560's lookup: every PAST index that
                // shares this same remainder tells us that the subarray
                // between that earlier index and now sums to a multiple
                // of k. Add ALL such earlier occurrences, since each is a
                // distinct valid subarray ending at the current index.
            }

            map[rem]++;
            // Record the CURRENT remainder AFTER checking for matches -
            // same ordering rule as LC 560, to avoid the current index
            // incorrectly matching against itself.
        }

        return count;
    }
};

// ===========================================================================
// REVISION SUMMARY - READ THIS FIRST WHEN YOU COME BACK IN A FEW MONTHS
// ===========================================================================
//
// THE ANALOGY:
// Imagine a clock with only k hours on its face (instead of the usual 12).
// As you walk further and further along your road trip, your odometer
// keeps climbing, but you only care WHICH HOUR the clock hand is
// currently pointing to (that's your remainder mod k). Every time the
// clock hand returns to an hour it has pointed to before, it means the
// distance travelled since the LAST time it was at that hour is an exact
// multiple of k kilometers - i.e., a subarray whose sum is divisible by k.
// You don't care about the raw odometer number anymore, only which "hour"
// it lands on.
//
// THE ALGEBRA IN ONE LINE:
// subarray(i+1, j) is divisible by k
//   <=>  (prefixSum(j) - prefixSum(i)) % k == 0
//   <=>  prefixSum(j) % k == prefixSum(i) % k
// So instead of matching exact prefix sum VALUES (like in LC 560), we
// match prefix sum REMAINDERS. Same skeleton, different bucket key.
//
// WHY THIS IS THE SAME FAMILY AS LC 560:
// LC 560:  bucket key = prefixSum itself       -> look for (sum - k)
// LC 974:  bucket key = prefixSum % k          -> look for (same remainder)
// Both use: hash map of "how many times have I seen this bucket key
// before," checked BEFORE updating, with a base case of 1 pre-loaded for
// the empty prefix. Once you see this skeleton, you can adapt it to any
// "count subarrays satisfying property X" question by just changing what
// you use as the bucket key.
//
// THE ONE LINE EVERYONE FORGETS:
// map[0] = 1 before the loop - accounts for subarrays starting at index 0.
//
// THE C++-SPECIFIC GOTCHA UNIQUE TO THIS PROBLEM:
// C++'s % operator can return negative values for negative operands.
// Always normalize with "if (rem < 0) rem += k;" whenever prefix sums can
// go negative. This bug is invisible on all-positive test cases and only
// shows up once negative numbers enter the array - a classic way to pass
// half the test cases and then silently fail the rest.
//
// COMPLEXITY:
// Time  = O(n) - single pass, O(1) average hash map operations.
// Space = O(k) - at most k distinct remainder buckets exist (0 to k-1),
//                which is actually BETTER space than LC 560's O(n) worst
//                case, since remainders are bounded by k regardless of
//                array size.
//
// WHEN TO REACH FOR THIS VARIANT:
// Any time the question says "divisible by k" or "same remainder" instead
// of an exact target sum - that's your signal to track prefixSum % k as
// the bucket key instead of the raw prefix sum, and to remember the
// negative-modulo normalization step.














// class Solution {
// public:
//     int subarraysDivByK(vector<int>& nums, int k) {
//         unordered_map<int, int> map;
//         map[0] = 1;
//         int count =  0;
//         int prefixsum = 0;

//         for(int num : nums){
//             prefixsum += num;

//             int rem = prefixsum % k;

//             if(rem < 0){
//                 rem += k;
//             }

//             if(map.count(rem)){
//                 count += map[rem];
//             }

//             map[rem]++;
//         }
//         return count;
//     }
// };







// Brute force
// class Solution {
// public:
//     int subarraysDivByK(vector<int>& nums, int k) {
//         int count =0;

//         for(int i=0; i< nums.size(); i++){
//             int sum = 0;

//             for( int j = i; j<nums.size(); j++){
//                 sum += nums[j];
//                 if(sum % k ==0){
//                     count++;
//                 }
//             }
//         }
//         return count;
//     }
// };