// class Solution {
// public:

//     int kadanesMax(vector<int> &nums, int n){
//         int sum = nums[0];
//         int maxSum = nums[0];

//         for(int i = 1; i<n; i++ ){
//             sum = max(sum + nums[i], nums[i]);
//             maxSum = max(maxSum, sum);
//         }
//         return maxSum;
//     }
//     int kadanesMin(vector<int> &nums, int n){
//         int sum = nums[0];
//         int minSum = nums[0];

//         for(int i = 1; i<n; i++ ){
//             sum = min(sum + nums[i], nums[i]);
//             minSum = min(minSum, sum);
//         }
//         return minSum;
//     }

//     int maxSubarraySumCircular(vector<int>& nums) {
//         int n = nums.size();

//         // 1 point of story

//         int sum = accumulate(begin(nums), end(nums), 0);

//         //2

//         int minSum = kadanesMin(nums, n);

//         //3
//         int maxSum = kadanesMax(nums, n);

//         //4

//         int circular_sum = sum - minSum;

//         if(maxSum > 0){
//             return max(maxSum, circular_sum);
//         }

//         return maxSum;
//     }
// };



class Solution {
public:
    // STANDARD KADANE'S ALGORITHM - finds maximum sum contiguous subarray
    // This solves "Case 1": the maximum subarray does NOT wrap around
    // Intuition: At each index, we decide whether to extend the previous subarray
    // or start a fresh one. We greedily pick whichever gives us a larger sum.
    int kadanesMax(vector<int> &nums, int n){
        // 'sum' = the best (maximum) sum of a subarray that MUST END at current index i
        // Not "best overall" — specifically the one ending HERE at this position
        // Initialize with nums[0] because with one element, that's the only possible subarray
        int sum = nums[0];
        
        // 'maxSum' = the trophy plaque — the best sum we've seen ANYWHERE so far
        // This is what we'll return as the answer for the non-wrapping case
        // Also starts at nums[0] since that's the only option with one element
        int maxSum = nums[0];
        
        // Start from index 1 because index 0 is already "used up" in initialization
        for(int i = 1; i < n; i++ ){
            // THE CORE DECISION OF KADANE'S ALGORITHM:
            // Option 1: sum + nums[i] → extend the previous best-ending subarray by including current element
            // Option 2: nums[i] → abandon everything before, start a FRESH subarray at current element
            // We pick max of these two because we're greedy — always want the richer option at THIS instant
            // Analogy: "Is my past baggage helping or hurting me? If it's dragging me down, cut it loose."
            sum = max(sum + nums[i], nums[i]);
            
            // Update the trophy plaque — compare this index's best-ending-here value
            // against the best we've seen ANYWHERE so far, and keep the larger one
            // This is what lets 'maxSum' capture a maximum subarray that might have
            // ended several steps ago, not necessarily at the current index
            maxSum = max(maxSum, sum);
        }
        return maxSum;  // Return the global maximum found
    }
    
    // REVERSE KADANE'S ALGORITHM - finds minimum sum contiguous subarray
    // This solves part of "Case 2": we need the minimum middle part to subtract from total
    // Intuition: Exact mirror of kadanesMax, but we want the MOST NEGATIVE subarray
    // Why? Because if we're wrapping around, the part we SKIP is in the middle
    // To maximize what we KEEP (wrapping sum), we minimize what we SKIP (middle part)
    int kadanesMin(vector<int> &nums, int n){
        // 'sum' = the best (minimum) sum of a subarray that MUST END at current index i
        // "Best" here means "most negative" — the deepest valley we can find
        int sum = nums[0];
        
        // 'minSum' = the trophy plaque for minimum — the smallest (most negative)
        // sum we've seen ANYWHERE so far. This represents the middle part we'd skip
        // in the wrapping case.
        int minSum = nums[0];
        
        for(int i = 1; i < n; i++ ){
            // Same decision structure as kadanesMax, but reversed:
            // Option 1: sum + nums[i] → extend the previous best-ending (most negative) subarray
            // Option 2: nums[i] → start fresh at current element
            // We pick min of these two because we want the MOST NEGATIVE result
            // Analogy: "Is my past baggage making me more negative? If yes, keep it. If it's
            // making me less negative (more positive), maybe I should restart."
            sum = min(sum + nums[i], nums[i]);
            
            // Update the minimum trophy plaque — keep track of the most negative
            // subarray we've found anywhere so far
            minSum = min(minSum, sum);
        }
        return minSum;  // Return the global minimum found
    }
    
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        
        // STEP 1: Calculate the total sum of the entire array
        // This is needed for Case 2 (wrapping subarray)
        // Formula: wrapping_sum = total_sum - middle_part_we_skip
        // We use accumulate() from <numeric> header — it's just a clean way to sum everything
        int sum = accumulate(begin(nums), end(nums), 0);
        
        // STEP 2: Find the minimum sum subarray using reverse Kadane's
        // This represents the "middle part" we'd skip in the wrapping case
        // Example: If array is [5, -3, 5] and min subarray is [-3], then
        // the wrapping subarray would be [5, (wrap), 5] = total - (-3) = 10
        int minSum = kadanesMin(nums, n);
        
        // STEP 3: Find the maximum sum subarray using standard Kadane's
        // This represents the best non-wrapping subarray (Case 1)
        // Example: If array is [5, -3, 5], max subarray might be [5, -3, 5] = 7
        int maxSum = kadanesMax(nums, n);
        
        // STEP 4: Calculate the wrapping subarray sum
        // This is the key insight for circular arrays:
        // If we wrap around, we're essentially taking everything EXCEPT some middle part
        // So: wrapping_sum = total_sum - (middle part we skip)
        // To maximize wrapping_sum, we minimize the middle part → that's why we calculated minSum
        int circular_sum = sum - minSum;
        
        // EDGE CASE CHECK: All numbers are negative
        // If maxSum < 0, it means even the best subarray is negative
        // In this case, circular_sum would be total_sum - min_sum = 0 (empty subarray)
        // But the problem REQUIRES at least one element — we can't return an empty subarray
        // So if all numbers are negative, just return maxSum (the least negative single element)
        // 
        // YOUR CODE: You wrote "if(maxSum > 0)" which is the same logic, just inverted:
        // - If maxSum > 0, at least one positive number exists, so we can safely compare both cases
        // - If maxSum <= 0, all numbers are negative or zero, so return maxSum
        if(maxSum > 0){
            // Not all negative — we can safely take the maximum of both cases
            // Case 1: Non-wrapping maximum subarray
            // Case 2: Wrapping maximum subarray (total - minimum middle)
            return max(maxSum, circular_sum);
        }
        
        // All numbers are negative (or maxSum is 0 and all are non-positive)
        // Return maxSum because circular_sum would represent an empty subarray (not allowed)
        return maxSum;
    }
};

/*
=========================== REVISION SUMMARY (READ THIS WHEN YOU FORGET EVERYTHING) ===========================

THE BIG PICTURE — TWO CASES FOR CIRCULAR ARRAYS:

In a circular array, any contiguous subarray is either:
1. NON-WRAPPING: A normal subarray somewhere in the middle (doesn't touch the wraparound point)
2. WRAPPING: A subarray that goes from the end back to the beginning (wraps around)

THE KEY INSIGHT — "THE DONUT AND THE HOLE":

Imagine your circular array is a donut. You want to eat the maximum amount of donut (maximum sum),
but you can only eat one contiguous piece.

OPTION 1 (Non-wrapping): Eat a normal piece that doesn't wrap around the hole
→ This is just standard Kadane's algorithm → kadanesMax()

OPTION 2 (Wrapping): Eat a piece that wraps around the hole
→ The part you DON'T eat is a contiguous piece in the middle (the "hole" of your donut bite)
→ To MAXIMIZE what you eat, you need to MINIMIZE what you leave behind
→ Formula: wrapping_sum = total_sum - minimum_middle_part → sum - kadanesMin()

THE ANALOGY — "YOUR BANK ACCOUNT WITH A RESET BUTTON" (for Kadane's):

Imagine you track your daily profit/loss (nums[i] can be +ve or -ve, like a stock's daily change).
'sum' (or 'bestending') is your RUNNING BALANCE if you started saving from some day and never touched it since.

Every new day, you ask ONE question: "Would I be richer today by continuing to hold my past balance
and adding today's change, OR would I be richer by wiping the slate clean and starting today fresh?"

- If your past balance is positive/helpful → keep it, add today's number (extend)
- If your past balance has gone so negative it's dragging you down → forget it, restart at today's number

Meanwhile 'maxSum' (or 'ans') is a separate scoreboard sitting on the side, taking a photograph of the
BEST balance you've EVER had, at any point in the past — even if your current running balance has since dropped.
That's why 'maxSum' updates with max(maxSum, sum) EVERY iteration, not just at the end.

DRY RUN — nums = [5, -3, 5]:

kadanesMax (Case 1 - non-wrapping):
- i=0: sum=5, maxSum=5
- i=1: sum=max(5+(-3), -3)=max(2,-3)=2, maxSum=max(5,2)=5
- i=2: sum=max(2+5, 5)=max(7,5)=7, maxSum=max(5,7)=7
→ Returns 7 (subarray [5, -3, 5])

kadanesMin (for Case 2 - wrapping):
- i=0: sum=5, minSum=5
- i=1: sum=min(5+(-3), -3)=min(2,-3)=-3, minSum=min(5,-3)=-3
- i=2: sum=min(-3+5, 5)=min(2,5)=2, minSum=min(-3,2)=-3
→ Returns -3 (subarray [-3])

total_sum = 5 + (-3) + 5 = 7
circular_sum = total_sum - minSum = 7 - (-3) = 10

Edge case check: maxSum = 7 > 0, so not all negative
Final answer: max(7, 10) = 10 ← correct! (wrapping subarray [5, (wrap), 5])

DRY RUN — ALL NEGATIVE: nums = [-3, -2, -5]:

kadanesMax:
- Returns -2 (the least negative single element, subarray [-2])

kadanesMin:
- Returns -10 (the entire array, subarray [-3, -2, -5])

total_sum = -10
circular_sum = -10 - (-10) = 0 ← this would be an EMPTY subarray (not allowed!)

Edge case check: maxSum = -2 ≤ 0, so all numbers are negative
Final answer: return maxSum = -2 ← correct! (we must pick at least one element)

TIME COMPLEXITY: O(n) — three separate passes through the array:
- One pass for accumulate() → O(n)
- One pass for kadanesMax() → O(n)
- One pass for kadanesMin() → O(n)
Total: O(n) + O(n) + O(n) = O(n)

This beats the brute force O(n³) by a massive margin — for n=3000, that's ~27 billion operations
vs. ~3000 operations. This is why interviewers love this problem — it tests whether you can spot
that a DP-style "running decision" beats brute enumeration, and whether you can adapt it to a twist.

SPACE COMPLEXITY: O(1) — only a handful of integer variables (sum, maxSum, minSum, circular_sum),
regardless of input size. No extra arrays, no recursion stack, no data structures.

TRIGGER WORDS FOR THIS PATTERN:
- "Circular array" + "maximum sum subarray"
- "Wrap around" + "contiguous subarray"
- "Array is circular" + "find max/min subarray sum"
- Any problem where the array is circular and you need max/min subarray sum

COMMON MISTAKES STUDENTS MAKE:
1. Forgetting the all-negative edge case — this is the #1 failure mode. If you don't check
   whether maxSum < 0, you'll return 0 for all-negative arrays, which represents an empty
   subarray and violates the problem constraint.

2. Running Kadane's twice separately when you could do it in one pass — your code is actually
   MORE READABLE by separating kadanesMax and kadanesMin into functions, which is better for
   interviews than cramming everything into one function. Clarity > micro-optimization here.

3. Confusing which case is which — remember:
   - Case 1 (non-wrapping): Standard Kadane's → kadanesMax()
   - Case 2 (wrapping): Total - Minimum → sum - kadanesMin()
   - Answer: max(Case 1, Case 2), unless all negative

WHY THIS WORKS — THE MATHEMATICAL INSIGHT:

Any circular subarray falls into exactly one of these categories:

1. NON-WRAPPING SUBARRAY: Looks like [i, i+1, ..., j] where i ≤ j
   - This is a normal contiguous subarray
   - Standard Kadane's finds the maximum

2. WRAPPING SUBARRAY: Looks like [i, i+1, ..., n-1, 0, 1, ..., j] where i > j
   - This wraps from the end back to the beginning
   - The part NOT included is [j+1, j+2, ..., i-1] — a normal contiguous subarray in the middle
   - If total_sum is the sum of everything, and middle_sum is what we're skipping, then:
   - wrapping_sum = total_sum - middle_sum
   - To maximize wrapping_sum, we minimize middle_sum
   - So: wrapping_sum = total_sum - min_kadane

The edge case (all negative) exists because if all numbers are negative, the "minimum middle part"
would be the entire array itself, making wrapping_sum = 0 (empty subarray). But the problem requires
at least one element, so we can't return 0 — we must return the least negative single element.

YOUR CODE STRUCTURE — WHY IT'S GOOD:

You separated kadanesMax and kadanesMin into reusable functions. This is actually BETTER than
cramming everything into one function because:
- It shows you understand these are reusable patterns (you can use kadanesMax for LeetCode 53, 918, etc.)
- It's more readable and easier to debug
- It's easier to explain in an interview — you can say "I'm using standard Kadane's here" without
  re-explaining the logic
- It's easier to test — you can test kadanesMax and kadanesMin independently

The only micro-optimization you could make is combining all three calculations (total, max, min) into
one pass instead of three, but that sacrifices readability for a tiny speedup. In interviews,
clarity usually wins unless they explicitly ask for optimization.

==================================================================================================
*/