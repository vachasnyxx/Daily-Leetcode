// #include <bits/stdc++.h>
// using namespace std;

// class Solution {
// public:
//     int solve(vector<int>& nums, int target, int i, int currsum, unordered_map<string, int>& mp) {
//         // Base case
//         if (i == nums.size()) {
//             return (currsum == target) ? 1 : 0;
//         }

//         // Create key for memoization
//         string key = to_string(i) + "_" + to_string(currsum);

//         if (mp.count(key)) {
//             return mp[key];
//         }

//         // Recursive case
//         int plus = solve(nums, target, i + 1, currsum + nums[i], mp);
//         int minus = solve(nums, target, i + 1, currsum - nums[i], mp);

//         return mp[key] = plus + minus;
//     }

//     int findTargetSumWays(vector<int>& nums, int target) {
//         unordered_map<string, int> mp;
//         return solve(nums, target, 0, 0, mp);
//     }
// };





#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // ---- PATTERN: "Include/Exclude" recursion (same skeleton as Subsets!)
    // but now EACH element has exactly 2 choices too: add it (+nums[i])
    // or subtract it (-nums[i]) — instead of "take/skip" like in Subsets.
    // We're not building a subset this time, we're building a RUNNING SUM,
    // and we only care whether that sum equals `target` once we've used
    // every element.
    int solve(vector<int>& nums, int target, int i, int currsum, unordered_map<string, int>& mp) {

        // BASE CASE: we've assigned a sign to every element.
        // Check: did our accumulated sum land exactly on target?
        // If yes, this ONE path through the recursion tree counts as
        // 1 valid way. If no, this path contributes 0 ways.
        if (i == nums.size()) {
            return (currsum == target) ? 1 : 0;
        }

        // ---- MEMOIZATION KEY ----
        // Why do we need memo at all? Because different sign-assignment
        // paths can arrive at the SAME (i, currsum) state. Example:
        // nums=[1,1,1,1], target=0 → +1-1... and -1+1... can both land
        // on the same (i, currsum) pair. Without memo, we'd recompute
        // the entire remaining subtree for that state again — wasteful.
        // This is EXACTLY why plain "include/exclude" recursion (like
        // Subsets) becomes DP: the states start REPEATING, so we cache them.
        string key = to_string(i) + "_" + to_string(currsum);

        // If we've already solved "from index i, with currsum so far,
        // how many ways to reach target" — reuse that answer instantly
        // instead of re-exploring the whole subtree. This is the "memory
        // notebook" trick: never redo work you've already done.
        if (mp.count(key)) {
            return mp[key];
        }

        // ---- BRANCH 1: assign '+' sign to nums[i] ----
        int plus = solve(nums, target, i + 1, currsum + nums[i], mp);

        // ---- BRANCH 2: assign '-' sign to nums[i] ----
        int minus = solve(nums, target, i + 1, currsum - nums[i], mp);

        // Total ways from this state = ways through the '+' branch
        // PLUS ways through the '-' branch. Store it in the notebook
        // before returning, so any future call landing on this exact
        // (i, currsum) state gets an instant answer.
        return mp[key] = plus + minus;
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<string, int> mp;
        return solve(nums, target, 0, 0, mp);
    }
};

/*
==================== REVISION SUMMARY ====================

ONE-LINE INTUITION:
Every number can either add to or subtract from your running total. You want
to count how many of the 2^n possible +/- sign combinations make the total
land exactly on target — but many of those combinations pass through
identical (position, running-sum) states, so cache the answer for each state
instead of recomputing it.

ANALOGY — "The Memory Notebook at a Fork in the Road":
Picture yourself walking through a maze where at every junction you can only
go LEFT (+nums[i]) or RIGHT (-nums[i]). Many different starting paths can
end up standing at the exact same junction with the exact same "distance
walked so far" — from that junction onward, the rest of the maze looks
IDENTICAL no matter how you got there. So the first time you reach a
junction, you write in a notebook: "from here, there are X ways to finish."
Next time any other path reaches that same junction, you just read the
notebook instead of re-walking the whole rest of the maze.

WHY THIS IS DP AND NOT JUST RECURSION:
Plain recursion (like your Subsets code) has no OVERLAPPING STATES — each
(i, temp) combination is visited exactly once, so there's nothing to cache.
Here, state = (i, currsum), and this SAME state gets revisited by different
sign-paths, which is the formal definition of "overlapping subproblems" —
the trigger that turns recursion into memoized DP.

TIME COMPLEXITY: O(n * S)
  - n = nums.size(), S = number of distinct possible currsum values
    (bounded by 2 * sum(nums), since sum ranges from -sum(nums) to +sum(nums)).
  - There are at most n * S distinct (i, currsum) states, and each is
    computed once thanks to memoization, O(1) work per cached lookup.

SPACE COMPLEXITY: O(n * S)
  - The map stores up to n * S entries, plus O(n) recursion stack depth.

TOP 3 MISTAKES / INEFFICIENCIES TO WATCH:
1. Using a STRING key (to_string(i) + "_" + to_string(currsum)) — this
   works but is genuinely slow: string concatenation + hashing a string is
   much more expensive than hashing two integers. Better: use
   unordered_map<int, int> per recursion depth level, OR encode the state
   as a single long (i * OFFSET + (currsum + BIAS)), OR use
   map<pair<int,int>, int>. On large inputs this string-key version can
   TLE where an int-key version wouldn't — worth fixing as a habit now.
2. Forgetting the currsum can go NEGATIVE — some students clamp it to
   an array index without an offset/bias and get out-of-bounds bugs when
   converting from map-based memo to array-based memo (a very common
   next-step optimization for this exact problem).
3. Recomputing base case incorrectly by checking `currsum == 0` instead of
   `currsum == target` — an easy copy-paste slip when adapting this
   skeleton from a plain "partition into equal subsets" template.

TRIGGER WORDS for this pattern:
"number of ways to assign +/- signs", "count ways to reach a target sum",
"ways to partition into two subsets with sum difference" — these scream
"include/exclude recursion + memoize on (index, running value)".

COMPANIES:
Target Sum (494) itself is a known Facebook/Meta and Amazon medium-round
question; the underlying "count ways with overlapping states" pattern
appears heavily in Google and Microsoft OA rounds under different disguises
(coin change variants, subset sum counting).
=============================================================
*/