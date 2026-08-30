// class Solution {
// public:
//     int n;
//     vector<vector<int>> result;

//     void solve(int idx, vector<int>& nums) {
//         if (idx == n) {
//             result.push_back(nums);
//             return;
//         }

//         for (int i = idx; i < n; i++) {

//             swap(nums[i], nums[idx]);

//             solve(idx + 1, nums);

//             swap(nums[i], nums[idx]);
//         }
//     }

//     vector<vector<int>> permute(vector<int>& nums) {
//         n = nums.size();

//         solve(0, nums);

//         return result;
//     }
// };




class Solution {
public:
    int n;
    vector<vector<int>> result;   // Every complete permutation found.

    // idx = the POSITION we're currently trying to fill (0-indexed).
    // Everything from index 0 to idx-1 is already "locked in" — those
    // positions were decided by earlier recursive calls and won't change
    // again in this branch. Positions idx to n-1 are the "remaining pool"
    // of elements still available to place here.
    void solve(int idx, vector<int>& nums) {

        // BASE CASE: every position (0 through n-1) has been filled —
        // 'nums' currently holds one complete, valid permutation.
        if (idx == n) {
            result.push_back(nums);   // COPY nums into result (push_back
                                       // on a vector<int> copies the data,
                                       // so future swaps won't corrupt
                                       // this saved permutation).
            return;
        }

        // Try EVERY element still in the remaining pool (indices idx to
        // n-1) as the candidate for THIS position.
        for (int i = idx; i < n; i++) {

            // CHOOSE: swap the candidate element (at position i) into the
            // current position (idx). If i == idx, this is a "self-swap"
            // (no actual change) — that represents the valid choice of
            // "leave whatever's already at idx right where it is."
            swap(nums[i], nums[idx]);

            // EXPLORE: recurse to fill the NEXT position, now that idx's
            // slot is locked in with this candidate.
            solve(idx + 1, nums);

            // UN-CHOOSE (backtrack): swap back to UNDO the placement,
            // restoring nums to exactly the state it was in before this
            // iteration. This is critical — without it, the NEXT value
            // of 'i' in this loop would be operating on an already-shuffled
            // array instead of the original pool, producing wrong results.
            swap(nums[i], nums[idx]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        n = nums.size();
        solve(0, nums);
        return result;
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Given n distinct integers, return every possible ordering (permutation) of
them.

ANALOGY — "Lining up friends for a photo, one position at a time":
You're arranging n friends into a lineup for a photo, deciding positions
left to right. To decide who stands in position idx, you try each friend
still available (everyone from idx to n-1 in the pool — friends already
placed in positions 0 to idx-1 are locked in and done) by physically
pulling them forward into slot idx (the swap), snapping the "photo" for
this partial arrangement (recursing deeper), and then putting that friend
back where they were (the second swap) before trying the NEXT candidate for
that same slot. This in-place swapping means you never need a separate
"who's still available" list — the array itself, split at index idx, always
represents "locked in" (left of idx) vs. "still available" (right of idx).

WHY THE SELF-SWAP (i == idx) ISN'T A BUG:
When i equals idx, `swap(nums[i], nums[idx])` swaps an element with itself
— nothing visibly changes. But this iteration still matters: it represents
the valid choice of "keep the element that's currently sitting at position
idx exactly where it is" as one of the candidates for this slot, rather than
pulling in someone from further down the pool. Skipping this iteration
would mean the original relative ordering could never appear in the output.

DRY RUN (n = 3, nums = [1,2,3], full trace):
solve(0, [1,2,3])
├─ i=0: swap(0,0) no-op [1,2,3] → solve(1,[1,2,3])
│   ├─ i=1: swap(1,1) no-op → solve(2,[1,2,3]) → RECORD [1,2,3]
│   └─ i=2: swap(2,1)→[1,3,2] → solve(2,[1,3,2]) → RECORD [1,3,2]
│            swap back →[1,2,3]
├─ i=1: swap(1,0)→[2,1,3] → solve(1,[2,1,3])
│   ├─ i=1: no-op → solve(2,...) → RECORD [2,1,3]
│   └─ i=2: swap(2,1)→[2,3,1] → RECORD [2,3,1] → swap back →[2,1,3]
│   swap back (undo i=1's outer swap) →[1,2,3]
└─ i=2: swap(2,0)→[3,2,1] → solve(1,[3,2,1])
    ├─ i=1: no-op → solve(2,...) → RECORD [3,2,1]
    └─ i=2: swap(2,1)→[3,1,2] → RECORD [3,1,2] → swap back →[3,2,1]
    swap back →[1,2,3]  (array restored to original at the very end)

Final result: [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,2,1], [3,1,2]
— all 3! = 6 permutations, matching the expected output exactly.

TIME COMPLEXITY: O(n! * n) — there are n! total permutations, and each one
costs O(n) to copy into 'result' via push_back(nums).
SPACE COMPLEXITY: O(n) for the recursion depth (excluding the output
storage itself, which is inherently O(n! * n) since that's the total size
of all permutations combined).

TRIGGER WORDS for this pattern:
- "generate all permutations/orderings/arrangements of n distinct elements"
  → backtracking, either via swap-in-place (this style) or via a separate
  `used[]` boolean array + building a new temporary array (the other common
  style — functionally equivalent, just different space tradeoffs).
- If the elements have DUPLICATES (like LC 47, Permutations II), this exact
  swap technique needs an extra "skip duplicate value at this level" check
  to avoid generating the same permutation multiple times — worth revisiting
  when you get to that problem.

COMMON MISTAKES:
1. Forgetting the SECOND swap (the backtrack/undo step) after the recursive
   call — without it, the array stays shuffled from the previous iteration,
   and the next value of `i` in the loop operates on corrupted data,
   producing wrong or duplicate permutations.
2. Starting the inner loop from 0 instead of idx — this would let already
   "locked in" earlier positions get shuffled again, generating massive
   numbers of duplicate permutations instead of n! unique ones.
3. Mistaking the i == idx self-swap as dead code and trying to "optimize"
   it away with an `if (i != idx)` guard — this actually breaks correctness,
   since skipping it removes the choice of keeping the current element in
   its current position, which is silently needed to generate a complete
   set of permutations.

WHERE THIS SHOWS UP:
Permutations (LC 46) is one of the most common entry-level backtracking
interview questions at Amazon, Microsoft, and Adobe, frequently used as a
warm-up before its harder follow-up, Permutations II (LC 47), which adds
duplicate-value handling and tests whether you can extend a known template
correctly rather than just reproducing memorized code.
================================================================================
*/














// Approach 1
// class Solution {
// public:
//     int n;
//     vector<vector<int>> result;
//     unordered_set<int> st;

//     void solve(vector<int>& temp,vector<int>& nums){
//         if(temp.size() == n){
//             result.push_back(temp);
//             return;
//         }

//         for(int i = 0; i<n ; i++){

//             if(st.find(nums[i]) == st.end()){

//                 temp.push_back(nums[i]);
//                 st.insert(nums[i]);

//                 solve(temp,nums);

//                 temp.pop_back();
//                 st.erase(nums[i]);
//             }
//         }
//     }

//     vector<vector<int>> permute(vector<int>& nums) {
//         n  = nums.size();
//         vector<int> temp;
//         solve(temp,nums);

//         return result;
//     }
// };