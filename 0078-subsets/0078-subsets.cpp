// class Solution {
// public:
//     vector<vector<int>> result;

//     void solve(int i , vector<int> &nums, vector<int>& temp){
//         if(i >= nums.size()){
//             result.push_back(temp);
//             return;
//         }

//         temp.push_back(nums[i]); // take ith element

//         solve(i+1,nums,temp);
//         temp.pop_back();  // no take ith element
//         solve(i+1,nums,temp);
//     }

//     vector<vector<int>> subsets(vector<int>& nums) {
//         vector<int> temp ;// store subsets

//         solve(0, nums,temp);

//         return result;
//     }
// };








class Solution {
public:
    // Stores every subset we generate. Since order doesn't matter for LC 78,
    // we don't sort/dedupe — nums has distinct elements anyway.
    vector<vector<int>> result;

    // ---- CORE RECURSION: "Include vs Exclude" decision tree ----
    // At every index i, we face exactly ONE binary decision:
    //   "Do I put nums[i] into my current subset, or not?"
    // This is the SAME pattern as: subset sum, combination sum,
    // partition problems, and even the 0/1 knapsack recursion skeleton.
    void solve(int i, vector<int> &nums, vector<int>& temp){

        // BASE CASE: i has walked past the last index.
        // This means we've made a take/skip decision for EVERY element
        // in nums, so whatever is sitting in `temp` right now is one
        // complete, valid subset. Save a COPY of it (push_back copies
        // the vector by value here, so later mutations to temp won't
        // corrupt what's already stored in result). Then return —
        // there's nothing left to decide.
        if(i >= nums.size()){
            result.push_back(temp);
            return;
        }

        // ---- BRANCH 1: TAKE nums[i] ----
        // We commit to including nums[i] in the subset being built.
        temp.push_back(nums[i]);

        // Recurse to decide the fate of the NEXT element (i+1),
        // carrying forward the fact that nums[i] is now "locked in".
        solve(i+1, nums, temp);

        // BACKTRACK: undo the choice we just made.
        // Why? Because `temp` is a SHARED, REUSED buffer across the
        // whole recursion tree (not a fresh copy per call). If we don't
        // remove nums[i], the next branch (the "skip" branch below)
        // would wrongly still have nums[i] sitting in temp.
        // This pop_back() is what makes backtracking work —
        // it resets state back to how it was BEFORE we tried "take".
        temp.pop_back();

        // ---- BRANCH 2: SKIP nums[i] ----
        // Now explore the other universe: nums[i] is simply left out.
        // temp is currently back to its pre-take state, so this call
        // starts clean, as if nums[i] never existed.
        solve(i+1, nums, temp);

        // No pop_back needed here — we never pushed anything in this
        // branch, so there's nothing to undo before returning control
        // to whoever called this instance of solve().
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> temp; // the "current subset in progress" scratchpad

        // Kick off the decision tree at index 0, with an empty subset.
        solve(0, nums, temp);

        return result;
    }
};

/*
==================== REVISION SUMMARY (read this first next time) ====================

ONE-LINE INTUITION:
For every element, you either put it in your bag or you don't — do this for
all elements, and every possible combination of "in/out" decisions gives you
exactly one subset. 2^n elements decisions → 2^n subsets. That's why the
answer size is always 2^n.

ANALOGY — "The Light Switch Hallway":
Imagine n light switches in a hallway, one per element of nums. Each switch
is either ON (element included) or OFF (element excluded). Walking down the
hallway flipping switches in every possible ON/OFF combination and taking a
photo at the end of the hallway = generating every subset. There are 2^n
possible switch combinations, hence 2^n subsets — including the "all OFF"
combo (the empty set) and "all ON" (the full array).

RECURSION TREE SHAPE (dry run for nums = [1,2]):
                        solve(0, temp=[])
                       /                  \
              take 1                        skip 1
        solve(1, temp=[1])              solve(1, temp=[])
         /            \                   /            \
   take 2          skip 2            take 2          skip 2
solve(2,[1,2])   solve(2,[1])     solve(2,[2])     solve(2,[])
   -> [1,2]         -> [1]           -> [2]           -> []

Every LEAF of this binary tree = one final subset. Depth of tree = n,
branching factor = 2, so total leaves = 2^n. This is IDENTICAL in shape to
every "include/exclude" recursion you'll meet later (subset sum, combination
sum, word break variants).

TIME COMPLEXITY: O(n * 2^n)
  - 2^n leaf nodes (subsets) get generated.
  - Each subset can be up to length n, and copying it into `result` via
    push_back(temp) costs O(length of temp) ≈ O(n) in the worst case.
  - So total = O(2^n) subsets * O(n) copy cost = O(n * 2^n).

SPACE COMPLEXITY: O(n)
  - This is just the RECURSION STACK depth + the `temp` vector size,
    both bounded by n (not counting the O(n * 2^n) space result itself
    needs to store all subsets, which is unavoidable output space).

WHY pop_back() IS THE HEART OF BACKTRACKING:
temp is ONE shared vector reused across the entire recursion tree instead of
creating a new vector per call (which would be wasteful). Every "take"
branch MUST undo itself with pop_back() before the "skip" branch runs,
otherwise skip's version of temp would incorrectly still contain the taken
element. This take -> recurse -> undo -> skip -> recurse rhythm is the exact
template for backtracking problems (permutations, combination sum, N-Queens,
subsets with duplicates, etc.) — you'll see this shape again and again.

TOP 3 MISTAKES STUDENTS MAKE HERE:
1. Forgetting pop_back() after the "take" branch — silently corrupts every
   subsequent "skip" subset with leftover elements. Very hard to spot because
   the code still compiles and runs, just produces wrong/duplicate subsets.
2. Doing result.push_back(temp) but thinking it stores a REFERENCE to temp —
   it doesn't; push_back copies the vector, which is exactly why mutating
   temp afterward is safe. Confusing this leads to fear of "corrupting"
   already-saved subsets (unfounded fear, but common).
3. Writing the base case as `if(i == nums.size())` instead of `i >= `. Works
   fine here since i increments by exactly 1, but it's a fragile habit —
   `>=` is defensive and matches patterns where you might jump indices later.

TRIGGER WORDS for this pattern in future problems:
"all possible subsets/subsequences", "power set", "every combination of
elements", "in or out of the set" — these should immediately make you think
of this take/skip binary recursion tree.

COMPANIES that test this pattern:
Amazon, Microsoft, and Adobe commonly ask Subsets or its variants (Subsets II
with duplicates, Combination Sum) in early SDE rounds — it's a favorite
"can you handle recursion + backtracking cleanly" filter question.
=========================================================================
*/