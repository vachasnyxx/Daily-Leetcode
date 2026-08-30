// class Solution {
// public:
//     int n;
//     vector<vector<int>> result;

//     void solve(vector<int>& nums, int idx) {

//         if (idx == n) {
//             result.push_back(nums); // O(n);
//             return;
//         }

//         unordered_set<int> uniqueset;

//         for (int i = idx; i < n; i++) { // try all possible i >= idx to swap with nums[idx]

//             if(uniqueset.find(nums[i]) != uniqueset.end()){
//                 continue;
//             }

//             uniqueset.insert(nums[i]);
//             swap(nums[i], nums[idx]);

//             solve(nums, idx + 1);

//             swap(nums[i], nums[idx]);
//         }
//     }

//     vector<vector<int>> permuteUnique(vector<int>& nums) {
//         n = nums.size();

//         solve(nums,0);

//         return result;
//     }
// };








class Solution {
public:
    int n;
    vector<vector<int>> result;

    void solve(vector<int>& nums, int idx) {

        if (idx == n) {
            result.push_back(nums); // O(n) copy of a complete permutation
            return;
        }

        // CRUCIAL DETAIL: this set is declared INSIDE solve(), meaning a
        // BRAND NEW, EMPTY set is created every single time this function
        // is called — i.e., once per recursion level (once per value of
        // idx, per branch). It does NOT persist across sibling branches
        // or across different calls at the same depth in different parts
        // of the tree. This local scoping is what makes the whole dedup
        // trick correct.
        unordered_set<int> uniqueset;

        for (int i = idx; i < n; i++) { // try all possible i >= idx to swap with nums[idx]

            // DEDUP CHECK: have we already tried placing this exact VALUE
            // at position idx, earlier in this same loop (this same level)?
            // If yes, skip it — trying it again would produce a permutation
            // IDENTICAL to one we've already fully explored, since the
            // final output only cares about the VALUE at each position,
            // not which original array index it came from.
            if (uniqueset.find(nums[i]) != uniqueset.end()) {
                continue;
            }

            // Record that this value has now been "tried" at this position
            // for this level of recursion, so no later 'i' in this same
            // loop repeats it.
            uniqueset.insert(nums[i]);

            // Same swap-based CHOOSE / EXPLORE / UN-CHOOSE structure as
            // the duplicate-free Permutations problem.
            swap(nums[i], nums[idx]);

            solve(nums, idx + 1);

            swap(nums[i], nums[idx]);  // backtrack: restore original order
                                       // so the NEXT iteration of this loop
                                       // (or the caller above) sees a clean,
                                       // correctly-ordered array.
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        n = nums.size();
        solve(nums, 0);
        return result;
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Given a list of integers that MAY contain duplicate values, return every
distinct permutation (no repeated arrangements in the output), using the
swap-in-place backtracking technique.

ANALOGY — "Photo lineup with identical twins":
Same photo-lineup analogy as before, but now imagine some friends are
identical twins wearing the exact same outfit (duplicate values). If you
try Twin A first in position idx and take a photo, then later try Twin B
(who looks IDENTICAL) in that same position idx, the resulting photo looks
EXACTLY the same either way — it's a wasted, duplicate photo. So for each
position, you keep a checklist (the uniqueset) of which "looks" (values)
you've already photographed in that slot, and skip re-trying any look
you've already covered. Crucially, this checklist is a FRESH blank sheet
every time you move to a NEW position — a look you skipped at position 0
might still be perfectly valid and untried at position 1.

WHY THIS DIFFERS FROM THE "SORT + SKIP" TRICK YOU MAY HAVE SEEN ELSEWHERE:
The most common dedup technique for permutations relies on FIRST sorting
the array, then skipping `nums[i] == nums[i-1]` when `i` hasn't been
"used" yet — but that trick fundamentally depends on duplicates sitting
NEXT TO each other in a stable, sorted order. Swap-based permutation
generation constantly shuffles the array's order mid-recursion, so by the
time you're deep in the recursion tree, equal values are NOT guaranteed to
be adjacent anymore — the sort-based trick simply breaks here. The
per-level `unordered_set` sidesteps this entirely by checking VALUES
directly, regardless of their position or order in the array at that moment.

DRY RUN (nums = [1,1,2], showing duplicates skipped):
solve([1,1,2], idx=0), uniqueset={}
  i=0: nums[0]=1, not seen → insert 1. swap(0,0) no-op → solve(idx=1)
      uniqueset={} (fresh)
      i=1: nums[1]=1, not seen → insert 1. no-op swap → solve(idx=2)
          uniqueset={} (fresh)
          i=2: nums[2]=2 → insert 2 → no-op swap → solve(idx=3) → RECORD [1,1,2]
      i=2: nums[2]=2, not seen at THIS level → insert 2 → swap(2,1)→[1,2,1]
          → solve(idx=2) → eventually RECORD [1,2,1] → swap back →[1,1,2]
  i=1: nums[1]=1 → ALREADY in uniqueset {1} at THIS level → SKIP entirely
       (this is what prevents generating a duplicate of the i=0 branch)
  i=2: nums[2]=2, not seen → insert 2 → swap(2,0)→[2,1,1] → solve(idx=1)
      → eventually RECORD [2,1,1] → swap back →[1,1,2]

Final result: [1,1,2], [1,2,1], [2,1,1] — exactly 3 unique permutations,
matching the correct count of 3!/2! = 3 (dividing by 2! because the two
1's are indistinguishable from each other).

TIME COMPLEXITY: Bounded above by O(n! * n) same as the duplicate-free
version, but in practice significantly less whenever duplicates exist,
since the `continue` skip prunes entire duplicate subtrees before they're
ever explored. Each unordered_set insert/lookup is O(1) average, adding
negligible overhead.
SPACE COMPLEXITY: O(n) for recursion depth, plus O(n) worst case for the
uniqueset at any single level (bounded by the number of distinct values
remaining).

TRIGGER WORDS for this pattern:
- "permutations with duplicate elements," "return only unique/distinct
  arrangements" → need explicit dedup logic layered on top of standard
  permutation backtracking.
- Specifically, if you're using the SWAP-based permutation technique (not
  the visited[]-array or sorted-array technique), the sort+skip trick won't
  work — reach for a per-recursion-level seen-set instead.

COMMON MISTAKES:
1. Declaring `uniqueset` as a class member (like `result`) instead of a
   LOCAL variable inside `solve()` — this would make it persist across
   completely unrelated branches and recursion depths, wrongly blocking
   valid values from being tried elsewhere in the tree. The local
   declaration is what scopes the dedup correctly to "this one position,
   this one loop."
2. Trying to apply the classic sorted-array "skip if nums[i]==nums[i-1] and
   not used" trick here without realizing swapping destroys the sorted
   invariant — a very common and confusing bug when transferring the
   dedup idea from the array-building style of permutation generation to
   this swap-based style.
3. Believing the dedup check alone means "check if this exact permutation
   was already generated" — it's actually much cheaper than that: it only
   ever checks "have I tried this VALUE at this SPECIFIC position before,"
   which is a local, per-level check, not a global "has this whole
   permutation been seen" check (which would require storing and comparing
   entire permutations — far more expensive).

WHERE THIS SHOWS UP:
Permutations II (LC 47) is a common follow-up to LC 46 at Microsoft and
Amazon interviews specifically to see if a candidate can independently
adapt their dedup strategy to whichever permutation-generation style they
originally chose, rather than blindly pattern-matching a memorized
"sort then skip adjacent duplicates" snippet that doesn't actually fit the
swap-based approach.
================================================================================
*/


















// class Solution {
// public:
//     int n;
//     vector<vector<int>> result;

//     void solve(unordered_map<int, int> mp, vector<int> temp){

//         if(temp.size() == n){
//             result.push_back(temp);   // O(n);
//             return;
//         }

//         for(auto& [num,count] : mp){
//             if(count == 0){
//                 continue;
//             }
//             // do something
//             temp.push_back(num);
//             mp[num]--;

//             // explore
//             solve(mp, temp); // trust

//             // undo it
//             temp.pop_back();
//             mp[num]++;

//         }

//     }

//         vector<vector<int>> permuteUnique(vector<int>& nums) {
//         n = nums.size();
//         unordered_map<int, int> mp;

//         for (int& num : nums) {
//             mp[num]++;
//         }

//         vector<int> temp;

//         solve(mp, temp);

//         return result;
//     }
// };