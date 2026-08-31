// // approach 2
// class Solution {
// public:
//     vector<vector<int>> result;

//     void solve(int start, int& n, int k, vector<int>& temp) {
//         if (k == 0) {
//             result.push_back(temp);
//             return;
//         }

//         for (int i = start; i <= n; i++) {
//             temp.push_back(i);
//             solve(i+ 1, n, k - 1, temp);
//             temp.pop_back();
//         }
//     }
//     vector<vector<int>> combine(int n, int k) {
//         vector<int> temp;

//         solve(1, n, k, temp);

//         return result;
//     }
// };






class Solution {
public:
    vector<vector<int>> result;   // Collects every valid k-sized combination.

    // 'start' = the smallest number we're ALLOWED to pick from at this level.
    // This is the KEY mechanism that prevents duplicates and enforces
    // "order doesn't matter" — once we pick a number, we're only allowed
    // to pick from numbers GREATER than it in deeper levels, never smaller
    // or equal. This guarantees combinations like [1,2] and [2,1] can
    // never both appear — only the sorted-order version [1,2] is ever built.
    void solve(int start, int& n, int k, vector<int>& temp) {

        // BASE CASE: we've successfully picked exactly k numbers.
        // temp now holds one complete, valid combination of size k.
        // No need to check anything else — the loop bounds and 'start'
        // parameter already prevented invalid or duplicate combinations
        // from ever being constructed.
        if (k == 0) {
            result.push_back(temp);
            return;
        }

        // Try every valid candidate from 'start' up to n.
        // Each iteration:
        //   - picks i as the NEXT element in this combination
        //   - recurses to pick the remaining (k-1) elements from
        //     numbers strictly greater than i (i+1, i+2, ..., n)
        //   - backtracks by popping i, so the NEXT iteration can
        //     try the next candidate in this position.
        for (int i = start; i <= n; i++) {
            temp.push_back(i);                // CHOOSE: include i in this combination
            solve(i + 1, n, k - 1, temp);     // EXPLORE: pick remaining k-1 from {i+1..n}
            temp.pop_back();                  // UN-CHOOSE: remove i, try next candidate
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<int> temp;
        // Start from 1 (problem uses 1-based numbers: 1, 2, ..., n)
        solve(1, n, k, temp);
        return result;
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Given n and k, return all possible ways to choose k distinct numbers from
{1, 2, ..., n} where order DOES NOT matter (i.e., [1,2] is the same as
[2,1], so only one should appear).

ANALOGY — "Picking a team from a lineup, left to right":
Imagine n people standing in a line, numbered 1 to n. You need to pick a
team of exactly k people. To avoid counting the same team multiple times
in different orders, you impose a simple rule: once you pick someone, you
can ONLY pick from people standing to their RIGHT for the rest of this
team. So if you pick person 3 first, your next pick can only be from
{4,5,...,n}, never from {1,2,3} again. This guarantees every team is
recorded in exactly one order — the sorted order — and no duplicate teams
ever appear.

WHY THIS DIFFERS FROM PERMUTATIONS (LC 46/47):
In permutations, order MATTERS — [1,2] and [2,1] are two different
outcomes, so you try EVERY unused element at EVERY position (often using
a visited[] array or swap technique). In combinations, order DOESN'T
matter — [1,2] and [2,1] represent the same set, so you enforce a
"always pick in increasing order" rule via the `start` parameter, which
prunes away any branch that would try to pick a smaller number after a
larger one.

DRY RUN (n = 4, k = 2, abbreviated):
solve(start=1, k=2)
├─ i=1: temp=[1], solve(start=2, k=1)
│   ├─ i=2: temp=[1,2], k=0 → RECORD [1,2]
│   ├─ i=3: temp=[1,3], k=0 → RECORD [1,3]
│   └─ i=4: temp=[1,4], k=0 → RECORD [1,4]
├─ i=2: temp=[2], solve(start=3, k=1)
│   ├─ i=3: temp=[2,3], k=0 → RECORD [2,3]
│   └─ i=4: temp=[2,4], k=0 → RECORD [2,4]
└─ i=3: temp=[3], solve(start=4, k=1)
    └─ i=4: temp=[3,4], k=0 → RECORD [3,4]

Final result: [1,2], [1,3], [1,4], [2,3], [2,4], [3,4] — exactly C(4,2)=6
combinations, matching the expected output.

TIME COMPLEXITY: O(C(n,k) * k), where C(n,k) is the binomial coefficient
"n choose k" — there are exactly C(n,k) valid combinations, and each one
takes O(k) time to copy into result via push_back(temp).
SPACE COMPLEXITY: O(k) for the recursion depth and temp vector (excluding
the output storage itself, which is inherently O(C(n,k) * k)).

TRIGGER WORDS for this pattern:
- "all combinations," "choose k elements," "subsets of size k," "order
  doesn't matter" → backtracking with a `start` parameter that increments
  on each recursive call to enforce increasing order and prevent duplicates.
- If the problem instead asks for "all subsets" (any size, LC 78), you
  remove the `k == 0` base case and instead record temp at EVERY node of
  the recursion tree (every partial combination is a valid subset).
- If it asks for "subsets with duplicates" (LC 90), you add a per-level
  seen-set (like Permutations II) to skip duplicate values at the same
  depth.

COMMON MISTAKES:
1. Starting the inner loop from 1 instead of `start` — this would allow
   picking the same number multiple times (e.g., [1,1]) or picking
   smaller numbers after larger ones (e.g., [2,1]), both of which violate
   the "distinct, increasing order" requirement for combinations.
2. Forgetting to decrement `k` in the recursive call (`k - 1`) — without
   this, the base case `k == 0` is never reached, and the recursion runs
   until `i > n`, producing only partial or incorrect results.
3. Not backtracking with `temp.pop_back()` — this causes temp to keep
   accumulating elements across sibling branches, so later recorded
   "combinations" end up far longer than k elements and completely wrong.

WHERE THIS SHOWS UP:
Combinations (LC 77) is a frequently asked backtracking warm-up at Amazon,
Microsoft, and Adobe — often used to test whether a candidate understands
the distinction between permutations (order matters) and combinations
(order doesn't), and can enforce that distinction with the `start`
parameter trick rather than generating everything and filtering duplicates
afterward.
================================================================================
*/













// aprroach one
//  class Solution {
//  public:
//      vector<vector<int>> result;

//     void solve(int start, int& n, int k, vector<int>& temp) {
//         if (k == 0) {
//             result.push_back(temp);
//             return;
//         }

//         if (start > n)
//             return;

//         temp.push_back(start);
//         solve(start + 1, n, k - 1, temp);

//         temp.pop_back();

//         solve(start + 1, n, k, temp);
//     }
//     vector<vector<int>> combine(int n, int k) {
//         vector<int> temp;

//         solve(1, n, k, temp);

//         return result;
//     }
// };