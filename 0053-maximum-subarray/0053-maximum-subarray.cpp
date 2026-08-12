class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();

        // 'bestending' = the best (max) sum of a subarray that MUST END at index i.
        // Not "best subarray so far overall" — specifically the one that ends HERE.
        // We initialize it with nums[0] because a subarray ending at index 0
        // can only be [nums[0]] itself — no other choice exists yet.
        int bestending = nums[0];

        // 'ans' = the best sum found across ALL positions we've scanned so far.
        // This is the actual answer we'll return — the global maximum.
        // Starts at nums[0] too, since with one element that's the only answer possible.
        int ans = nums[0];

        // We start the loop from i = 1 because index 0 is already "used up"
        // in the initialization above.
        for (int i = 1; i < n; i++) {

            // v1 = "extend the previous best-ending-subarray by including nums[i]"
            // Intuition: if the running subarray up to i-1 was net positive/useful,
            // dragging it forward and adding nums[i] keeps that momentum going.
            int v1 = bestending + nums[i];

            // v2 = "abandon everything before, start a FRESH subarray at nums[i]"
            // Intuition: if bestending so far was so negative that it's dragging
            // us down, cut our losses — a subarray of just nums[i] is a clean restart.
            int v2 = nums[i];

            // THE CORE DECISION OF KADANE'S ALGORITHM:
            // At every index, ask "is my past baggage helping or hurting me?"
            // If v1 > v2, carrying forward is worth it. Otherwise, restart.
            bestending = max(v1, v2);

            // Now compare this index's best-ending-here value against
            // the best we've seen ANYWHERE so far, and keep the larger one.
            // This is what lets 'ans' capture a maximum subarray that might
            // have ended several steps ago, not necessarily at the current index.
            ans = max(ans, bestending);
        }

        return ans;
    }
};

/*
=========================== REVISION SUMMARY (READ THIS WHEN YOU FORGET EVERYTHING) ===========================

THE ANALOGY — "Your Bank Balance With a Reset Button":
Imagine you track your daily profit/loss (nums[i] can be +ve or -ve, like a stock's daily change).
'bestending' is your RUNNING BALANCE if you started saving from some day and never touched it since.
Every new day, you ask ONE question: "Would I be richer today by continuing to hold my past balance
and adding today's change, OR would I be richer by wiping the slate clean and starting today fresh?"
- If your past balance is positive/helpful → keep it, add today's number (v1).
- If your past balance has gone so negative it's dragging you down → forget it, restart at today's number (v2).
You take max(v1, v2) because you're greedy — you always want the richer of the two options at THIS instant.

Meanwhile 'ans' is a separate scoreboard sitting on the side, taking a photograph of the BEST balance
you've EVER had, at any point in the past — even if your current running balance has since dropped.
That's why 'ans' updates with max(ans, bestending) EVERY iteration, not just at the end.

WHY THIS WORKS (THE INTUITION BEHIND KADANE'S):
A subarray sum can only get WORSE by including elements that make it negative. So the moment your
running sum dips below the value of the current element alone, it means everything before this point
was net-harmful — there's zero reason to drag that baggage forward. You're not "giving up" on the past
subarray, you're recognizing math has already told you it can't win. This greedy local decision
(extend vs. restart) provably leads to the global optimum — that's the "trick" of Kadane's.

DRY RUN — nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]:
i=0: bestending = -2, ans = -2   (init)
i=1: v1 = -2+1=-1, v2=1  → bestending = max(-1,1) = 1   | ans = max(-2,1) = 1
i=2: v1 = 1+(-3)=-2, v2=-3 → bestending = max(-2,-3)=-2 | ans = max(1,-2) = 1
i=3: v1 = -2+4=2, v2=4  → bestending = max(2,4) = 4     | ans = max(1,4) = 4
i=4: v1 = 4+(-1)=3, v2=-1 → bestending = max(3,-1)=3    | ans = max(4,3) = 4
i=5: v1 = 3+2=5, v2=2   → bestending = max(5,2) = 5     | ans = max(4,5) = 5
i=6: v1 = 5+1=6, v2=1   → bestending = max(6,1) = 6     | ans = max(5,6) = 6
i=7: v1 = 6+(-5)=1, v2=-5 → bestending = max(1,-5)=1    | ans = max(6,1) = 6
i=8: v1 = 1+4=5, v2=4   → bestending = max(5,4) = 5     | ans = max(6,5) = 6
Final answer = 6 → correct! (subarray [4,-1,2,1])

TIME COMPLEXITY: O(n) — one single pass, one decision per element, no nested loops, no re-scanning.
SPACE COMPLEXITY: O(1) — only two extra integer variables (bestending, ans), regardless of input size.
This beats the brute force O(n²) (checking every subarray) and even the O(n log n) divide-and-conquer
approach, which is exactly why interviewers love asking this — it tests whether you can spot that a
DP-style "running decision" beats brute enumeration.

TRIGGER WORDS FOR THIS PATTERN:
"Maximum sum of a CONTIGUOUS subarray", "find the subarray with the largest sum", "best contiguous
segment", or any problem about a contiguous run where each element can help or hurt cumulative value
(profit/loss streaks, temperature streaks, etc.) — that's your cue to think Kadane's, not brute force.

COMMON MISTAKES STUDENTS MAKE HERE:
1. Confusing 'bestending' with 'ans' — thinking they're the same variable. They're NOT: bestending can
   legitimately DROP in value; ans NEVER drops, it's a monotonic "best ever" tracker.
2. Forgetting to initialize both with nums[0] instead of 0 — if all numbers are negative (e.g. [-5,-2,-8]),
   initializing to 0 would wrongly return 0 (an empty subarray), when the real answer must be -2.
3. Writing bestending = max(0, bestending + nums[i]) — this is the WRONG variant for THIS problem, because
   it silently assumes an empty subarray (sum 0) is a valid answer, which breaks all-negative arrays.
==================================================================================================
*/









// class Solution {
// public:
//     int maxSubArray(vector<int>& nums) {
//         int n = nums.size();
//         int bestending = nums[0];
//         int ans = nums[0];

//         for(int i = 1; i<n; i++){
//             int v1 = bestending + nums[i];
//             int v2 = nums[i];

//             bestending = max(v1, v2);

//             ans = max(ans, bestending);
//         }

//         return ans;
//     }
// };