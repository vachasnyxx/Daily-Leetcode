// class Solution {
// public:
//     int maxAbsoluteSum(vector<int>& nums) {
//         int n  = nums.size();

//         int maxSum = nums[0];
//         int minSum = nums[0];

//         int currSumMax = nums[0];
//         int currSumMin = nums[0];

//         for(int i =0; i<n; i++){
//             currSumMax = max(nums[i], currSumMax + nums[i]);
//             maxSum = max(maxSum, currSumMax);


//             currSumMin = min(nums[i], currSumMin + nums[i]);
//             minSum = min(minSum, currSumMin);
//         }

//         return max(maxSum , abs(minSum));
//     }
// };


// class Solution {
// public:
//     int maxAbsoluteSum(vector<int>& nums) {
//         int n  = nums.size();

//         int currSubSum = nums[0];
//         int maxSubSum = nums[0];


//         // Kadane's Algo for finding max subarray sum
//         for(int i = 1; i<n; i++){
//             currSubSum = max(nums[i], currSubSum + nums[i]);
//             maxSubSum = max(maxSubSum, currSubSum);
//         }

        
//         // Kadane's Algo for finding min subarray sum
//         int minSubSum = nums[0];
//         currSubSum = nums[0];
//         for(int i = 1; i<n; i++){
//             currSubSum = min(nums[i], currSubSum + nums[i]);
//             minSubSum = min(minSubSum, currSubSum);
//         }

//         return max(maxSubSum, abs(minSubSum));
//     }
// };


class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        
        // 'maxSum' = the trophy plaque for maximum sum subarray
        // This tracks the LARGEST (most positive) subarray sum we've seen so far
        // Initialize with nums[0] because with one element, that's the only possible subarray
        int maxSum = nums[0];
        
        // 'minSum' = the trophy plaque for minimum sum subarray
        // This tracks the SMALLEST (most negative) subarray sum we've seen so far
        // Why do we need this? Because absolute value of a large negative number
        // can be larger than the maximum positive sum!
        // Example: If max positive sum is 10, but min negative sum is -15,
        // then abs(-15) = 15 > 10, so the answer is 15, not 10.
        int minSum = nums[0];
        
        // 'currSumMax' = the running maximum sum of a subarray that MUST END at current index i
        // Not "best overall" — specifically the one ending HERE at this position
        // This is the "extend vs. restart" decision variable for maximum sum
        int currSumMax = nums[0];
        
        // 'currSumMin' = the running minimum sum of a subarray that MUST END at current index i
        // Same as currSumMax, but for minimum sum (most negative)
        // This is the "extend vs. restart" decision variable for minimum sum
        int currSumMin = nums[0];
        
        // Start from index 0 (your code starts at i=0, but since we initialized with nums[0],
        // the first iteration at i=0 will just recompute the same values — harmless but redundant)
        // Could optimize by starting at i=1, but this is fine for clarity
        for(int i = 1; i < n; i++){
            // STANDARD KADANE'S FOR MAXIMUM SUM:
            // At each index, decide: extend the previous best-ending subarray by including
            // current element, OR start a FRESH subarray at current element?
            // We pick max of these two because we're greedy — always want the richer option
            // Analogy: "Is my past baggage helping or hurting me? If it's dragging me down, cut it loose."
            currSumMax = max(nums[i], currSumMax + nums[i]);
            
            // Update the maximum trophy plaque — compare this index's best-ending-here value
            // against the best we've seen ANYWHERE so far, and keep the larger one
            // This is what lets 'maxSum' capture a maximum subarray that might have
            // ended several steps ago, not necessarily at the current index
            maxSum = max(maxSum, currSumMax);
            
            // REVERSE KADANE'S FOR MINIMUM SUM:
            // Same logic as above, but reversed — we want the MOST NEGATIVE subarray
            // At each index, decide: extend the previous best-ending (most negative) subarray,
            // OR start fresh at current element?
            // We pick min of these two because we want the deepest valley (most negative result)
            // Analogy: "Is my past baggage making me more negative? If yes, keep it. If it's
            // making me less negative (more positive), maybe I should restart."
            currSumMin = min(nums[i], currSumMin + nums[i]);
            
            // Update the minimum trophy plaque — keep track of the most negative
            // subarray we've found anywhere so far
            minSum = min(minSum, currSumMin);
        }
        
        // THE KEY INSIGHT OF THIS PROBLEM:
        // We want the MAXIMUM ABSOLUTE SUM of any subarray.
        // Absolute value means we care about magnitude, not sign.
        // So the answer is the LARGER of:
        // 1. The maximum positive sum (maxSum)
        // 2. The absolute value of the minimum negative sum (abs(minSum))
        //
        // Example 1: nums = [1, -3, 2, 3, -4]
        // - maxSum = 5 (subarray [2, 3])
        // - minSum = -4 (subarray [-4])
        // - abs(minSum) = 4
        // - Answer = max(5, 4) = 5
        //
        // Example 2: nums = [-7, -1, -2, -3]
        // - maxSum = -1 (subarray [-1])
        // - minSum = -13 (subarray [-7, -1, -2, -3])
        // - abs(minSum) = 13
        // - Answer = max(-1, 13) = 13 ← the deep negative wins!
        //
        // This is why we need BOTH Kadane's for max AND min — you can't just
        // run standard Kadane's and assume the answer is the maximum sum.
        return max(maxSum, abs(minSum));
    }
};

/*
=========================== REVISION SUMMARY (READ THIS WHEN YOU FORGET EVERYTHING) ===========================

THE BIG PICTURE — WHAT THIS PROBLEM IS ASKING:

"Maximum Absolute Sum of Any Subarray" means: find the subarray (contiguous segment) whose sum has
the LARGEST MAGNITUDE, regardless of whether it's positive or negative.

In other words:
- If the maximum positive sum subarray is 10, and the minimum negative sum subarray is -15,
  then abs(-15) = 15 > 10, so the answer is 15.
- If the maximum positive sum subarray is 20, and the minimum negative sum subarray is -5,
  then abs(-5) = 5 < 20, so the answer is 20.

THE KEY INSIGHT — "TWO TROPHY PLAQUES":

We need to track TWO separate "trophy plaques" throughout the array:
1. maxSum — the largest (most positive) subarray sum we've seen so far
2. minSum — the smallest (most negative) subarray sum we've seen so far

At the end, the answer is max(maxSum, abs(minSum)) — whichever has the larger magnitude.

WHY WE NEED BOTH — THE "DEEP VALLEY" TRAP:

Many students make the mistake of thinking "just run standard Kadane's for maximum sum and return it."
This fails because a deeply negative subarray can have a larger absolute value than the maximum positive sum.

Example: nums = [-7, -1, -2, -3]
- Standard Kadane's (maxSum) = -1 (the least negative single element)
- Reverse Kadane's (minSum) = -13 (the entire array)
- abs(minSum) = 13 > abs(maxSum) = 1
- Answer = 13 ← the deep negative wins!

If you only ran standard Kadane's, you'd return -1, which is completely wrong.

THE ANALOGY — "YOUR BANK ACCOUNT WITH A RESET BUTTON" (for Kadane's):

Imagine you track your daily profit/loss (nums[i] can be +ve or -ve, like a stock's daily change).

'currSumMax' is your RUNNING BALANCE if you started saving from some day and never touched it since,
always trying to MAXIMIZE your balance.

'currSumMin' is your RUNNING BALANCE if you started saving from some day and never touched it since,
but this time you're trying to MINIMIZE your balance (find the deepest debt).

Every new day, you ask ONE question for each:
- For currSumMax: "Would I be richer today by continuing to hold my past balance and adding today's
  change, OR would I be richer by wiping the slate clean and starting today fresh?"
- For currSumMin: "Would I be in more debt today by continuing to hold my past balance and adding
  today's change, OR would I be in more debt by wiping the slate clean and starting today fresh?"

'maxSum' and 'minSum' are separate scoreboards sitting on the side, taking photographs of the BEST
(largest and smallest) balances you've EVER had, at any point in the past — even if your current
running balances have since changed.

DRY RUN — nums = [1, -3, 2, 3, -4]:

Initialization:
- maxSum = 1, minSum = 1
- currSumMax = 1, currSumMin = 1

i=0 (num=1):
- currSumMax = max(1, 1+1) = max(1, 2) = 2
- maxSum = max(1, 2) = 2
- currSumMin = min(1, 1+1) = min(1, 2) = 1
- minSum = min(1, 1) = 1

i=1 (num=-3):
- currSumMax = max(-3, 2+(-3)) = max(-3, -1) = -1
- maxSum = max(2, -1) = 2
- currSumMin = min(-3, 1+(-3)) = min(-3, -2) = -3
- minSum = min(1, -3) = -3

i=2 (num=2):
- currSumMax = max(2, -1+2) = max(2, 1) = 2
- maxSum = max(2, 2) = 2
- currSumMin = min(2, -3+2) = min(2, -1) = -1
- minSum = min(-3, -1) = -3

i=3 (num=3):
- currSumMax = max(3, 2+3) = max(3, 5) = 5
- maxSum = max(2, 5) = 5 ← new maximum!
- currSumMin = min(3, -1+3) = min(3, 2) = 2
- minSum = min(-3, 2) = -3

i=4 (num=-4):
- currSumMax = max(-4, 5+(-4)) = max(-4, 1) = 1
- maxSum = max(5, 1) = 5
- currSumMin = min(-4, 2+(-4)) = min(-4, -2) = -4
- minSum = min(-3, -4) = -4 ← new minimum!

Final calculation:
- maxSum = 5 (subarray [2, 3])
- minSum = -4 (subarray [-4])
- abs(minSum) = 4
- Answer = max(5, 4) = 5 ← correct!

DRY RUN — ALL NEGATIVE: nums = [-7, -1, -2, -3]:

Initialization:
- maxSum = -7, minSum = -7
- currSumMax = -7, currSumMin = -7

i=1 (num=-1):
- currSumMax = max(-1, -7+(-1)) = max(-1, -8) = -1
- maxSum = max(-7, -1) = -1
- currSumMin = min(-1, -7+(-1)) = min(-1, -8) = -8
- minSum = min(-7, -8) = -8

i=2 (num=-2):
- currSumMax = max(-2, -1+(-2)) = max(-2, -3) = -2
- maxSum = max(-1, -2) = -1
- currSumMin = min(-2, -8+(-2)) = min(-2, -10) = -10
- minSum = min(-8, -10) = -10

i=3 (num=-3):
- currSumMax = max(-3, -2+(-3)) = max(-3, -5) = -3
- maxSum = max(-1, -3) = -1
- currSumMin = min(-3, -10+(-3)) = min(-3, -13) = -13
- minSum = min(-10, -13) = -13

Final calculation:
- maxSum = -1 (subarray [-1])
- minSum = -13 (subarray [-7, -1, -2, -3])
- abs(minSum) = 13
- Answer = max(-1, 13) = 13 ← correct! (the deep negative wins)

TIME COMPLEXITY: O(n) — one single pass through the array, constant work per element.
This beats the brute force O(n²) (checking every subarray) by a massive margin — for n=3000,
that's ~9 million operations vs. ~3000 operations.

SPACE COMPLEXITY: O(1) — only four integer variables (maxSum, minSum, currSumMax, currSumMin),
regardless of input size. No extra arrays, no recursion stack, no data structures.

TRIGGER WORDS FOR THIS PATTERN:
- "Maximum absolute sum of any subarray"
- "Largest magnitude subarray sum"
- "Maximum of |sum| for any subarray"
- Any problem asking for the maximum absolute value of a subarray sum

COMMON MISTAKES STUDENTS MAKE:
1. Only running standard Kadane's for maximum sum — this is the #1 failure mode. People forget
   that a deeply negative subarray can have a larger absolute value than the maximum positive sum.

2. Starting the loop at i=0 when initialization already uses nums[0] — your code does this, and
   while it's harmless (the first iteration just recomputes the same values), it's slightly
   redundant. Could optimize by starting at i=1, but this is fine for clarity.

3. Forgetting to take abs(minSum) at the end — the answer is max(maxSum, abs(minSum)), not
   max(maxSum, minSum). The absolute value is crucial!

YOUR CODE STRUCTURE — WHY IT'S GOOD:

You combined both Kadane's (max and min) into a single loop, which is efficient and clean.
This is better than running two separate loops because:
- It's one pass instead of two — O(n) either way, but half the constant factor
- It's easier to see the symmetry between max and min calculations
- It's interview-ready — you can explain "I'm tracking both the maximum and minimum subarray
  sums simultaneously because the answer could come from either"

The only thing to watch out for is the loop starting at i=0 — since you initialized with nums[0],
the first iteration at i=0 will just recompute the same values. This is harmless and doesn't
affect correctness, but starting at i=1 would be slightly more efficient. However, your current
code is more symmetric and easier to read, which is often better in interviews.

==================================================================================================
*/