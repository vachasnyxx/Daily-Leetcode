// class Solution {
// public:
//     int firstStableIndex(vector<int>& nums, int k) {
//         int n = nums.size();

//         vector<int> minFromIndex(n);

//         int minEl = INT_MAX;

//         for (int i = n - 1; i >= 0; i--) {
//             minEl = min(minEl, nums[i]);
//             minFromIndex[i] = minEl;
//         }

//         int maxEl = INT_MIN;

//         for (int i = 0; i < n; i++) {
//             maxEl = max(maxEl, nums[i]);
//             if (maxEl - minFromIndex[i] <= k) {
//                 return i;
//             }
//         }
//         return -1;
//     }
// };






class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        // PATTERN RECOGNITION:
        // We need, for every index i, two things simultaneously:
        //   1) max(nums[0..i])   -> a PREFIX max (grows as we move left to right)
        //   2) min(nums[i..n-1]) -> a SUFFIX min (needs to look ahead into the future)
        // Since the suffix min at index i depends on elements to the RIGHT of i,
        // we can't compute it in the same left-to-right pass as the prefix max.
        // Trick: precompute the suffix array FIRST (in a separate backward pass),
        // store it, then do one clean forward pass for the prefix part.
        // This "precompute one direction, scan the other" is a very common
        // pattern for problems needing info from "the rest of the array".

        vector<int> minFromIndex(n);
        // minFromIndex[i] = minimum of nums[i], nums[i+1], ..., nums[n-1]
        // i.e., the smallest value from index i onward (inclusive).

        int minEl = INT_MAX; // running minimum, built up as we walk backward

        // BACKWARD PASS: build suffix minimums
        // Why backward? Because minFromIndex[i] needs to know about everything
        // to the RIGHT of i — the only way to know "the future" cheaply is to
        // compute it before you need it, walking from the end toward the start.
        for (int i = n - 1; i >= 0; i--) {
            minEl = min(minEl, nums[i]);   // include nums[i] itself in the "range so far"
            minFromIndex[i] = minEl;       // lock in the answer for this index
        }
        // ATOMIC DETAIL: minFromIndex[i] includes nums[i] itself, not just elements
        // strictly after it. Off-by-one errors here (using i+1 instead of i) are
        // the #1 bug source in this pattern — always ask yourself "inclusive of
        // current index or not?" before coding the loop.

        int maxEl = INT_MIN; // running maximum, built up as we walk forward

        // FORWARD PASS: build prefix maximums ON THE FLY (no array needed for this
        // side, because we consume it immediately — this saves O(n) extra space).
        for (int i = 0; i < n; i++) {
            maxEl = max(maxEl, nums[i]);
            // maxEl right now = max(nums[0..i])  -> prefix max up to and including i
            // minFromIndex[i] = min(nums[i..n-1]) -> suffix min from i onward
            // Both "windows" share index i, which is the whole point: we're
            // checking "is index i itself a valid split/stable point?"

            if (maxEl - minFromIndex[i] <= k) {
                // First index where the "instability" (max so far minus min ahead)
                // shrinks to within k. Because we scan left to right and return
                // immediately, this is guaranteed to be the FIRST such index.
                return i;
            }
        }
        // ATOMIC DETAIL: no early return happened -> no stable index exists at all.
        return -1;
    }
};

// =====================================================================
// REVISION SUMMARY (read this and you should be able to rebuild the
// whole solution from scratch, no need to re-read the code above)
// =====================================================================
//
// PROBLEM IN ONE LINE:
// Find the smallest index i such that (max of everything up to i) minus
// (min of everything from i to the end) is <= k.
//
// ANALOGY — "Two people meeting in the middle with flashlights":
// Imagine person A starts at the left edge of the array walking right,
// and at every step shouts out the BIGGEST number they've seen so far.
// Person B has ALREADY walked the array from right to left, ahead of
// time, and written down the SMALLEST number seen from each spot to
// the end, taping that note at every position.
// Now person A walks forward again, and at each step peeks at B's note
// taped at that spot. The moment (A's biggest-so-far) - (B's note) is
// small enough (<= k), A stops — that's your answer.
// B had to finish their entire walk BEFORE A could start peeking,
// because B's note at position i depends on stuff further ahead that
// A hasn't reached yet — hence two passes, not one.
//
// WHY TWO PASSES AND NOT ONE:
// A prefix quantity (max so far, growing left→right) and a suffix
// quantity (min from here to the end, depends on right→left) can't
// both be computed in a single direction sweep. Precompute the one
// that depends on "the future" first, store it, then sweep normally
// for the one that depends on "the past."
//
// TIME COMPLEXITY: O(n)
// - One backward pass: O(n) — visits every element once.
// - One forward pass: O(n) — visits every element once.
// - Total: O(n) + O(n) = O(n). No nested loops, no repeated scanning of
//   the same range, so it's linear, not quadratic. In an interview,
//   say: "we touch each element a constant number of times (twice),
//   so it's O(n)."
//
// SPACE COMPLEXITY: O(n)
// - The minFromIndex array stores one value per index -> O(n) extra space.
// - maxEl and minEl are just single integers -> O(1) each, negligible.
// - Total: O(n) auxiliary space (dominated by the suffix array).
// - INTERVIEW TALKING POINT: You could mention this is the "extra
//   space to avoid recomputation" tradeoff — trading O(n) space to
//   avoid an O(n^2) brute force (checking every i against every j > i).
//
// COMMON MISTAKES WITH THIS PATTERN:
// 1. Off-by-one on inclusivity: forgetting whether minFromIndex[i]
//    includes nums[i] or starts from i+1. Always decide this explicitly
//    before writing the loop, and match it to what the problem asks.
// 2. Trying to compute prefix max and suffix min in the SAME single
//    pass — impossible, because suffix min needs future data. Beginners
//    often try to be "clever" and merge loops, then get stuck.
// 3. Forgetting to initialize running trackers correctly: minEl must
//    start at INT_MAX (so any real number replaces it) and maxEl at
//    INT_MIN, not 0 — if your array has negative numbers, starting at
//    0 silently breaks the logic.
//
// TRIGGER WORDS to recognize this pattern in a NEW unseen problem:
// - "max of one side, min of other side" (or vice versa) at a split point
// - "smallest window where a condition holds across the whole array"
// - Anything needing "info from the rest of the array to the right" ->
//   immediately think: precompute a suffix array first.
//
// COMPANIES that test this prefix/suffix precompute pattern:
// - Amazon and Microsoft like this as a "clean up your first O(n^2)
//   idea into O(n)" follow-up question.
// - Google sometimes wraps it inside array-partitioning or
//   "balance point" style questions.