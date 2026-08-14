class Solution {
public:
    int maxProduct(vector<int>& nums) {
        /*
        This problem is a variation of Kadane's Algorithm.

        Normal Kadane's Algorithm tracks only:
            - The maximum sum ending at the current index

        But for maximum product, we must track TWO values:
            1. max_so_far = maximum product of a subarray ending at current index
            2. min_so_far = minimum product of a subarray ending at current index

        Why do we need the minimum?

        Because multiplying by a negative number reverses the sign:

            positive maximum × negative = negative
            negative minimum × negative = positive maximum

        Example:
            max_so_far = 3
            min_so_far = -10
            current number = -2

            3 × -2   = -6
            -10 × -2 = 20  ← the previous minimum becomes the new maximum
            -2       = -2

        Therefore, ignoring min_so_far would cause us to miss the answer.
        */

        /*
        LeetCode guarantees that nums contains at least one element.

        If the input could be empty in another problem, we would first handle:
            if (nums.empty()) return 0;
        */

        int n = nums.size();

        /*
        Initially, the only subarray available is:
            [nums[0]]

        Therefore, both the maximum and minimum product ending at index 0
        are simply nums[0].

        We cannot initialize these values to 0 because nums[0] might be:
            - Negative
            - Positive
            - The actual maximum answer
        */
        int max_so_far = nums[0];
        int min_so_far = nums[0];

        /*
        ans stores the best product found anywhere in the array.

        max_so_far only represents the best product that MUST end at
        the current index.

        But the final answer may have ended at an earlier index, so we
        maintain a separate global answer.
        */
        int ans = nums[0];

        /*
        Process every element from left to right.

        At every index, we ask:

        "What is the maximum/minimum product of a contiguous subarray
         that ends exactly at nums[i]?"
        */
        for (int i = 1; i < n; i++) {
            /*
            Store the previous values before changing them.

            We need the old maximum and old minimum because both are possible
            starting points for multiplication with nums[i].

            It is especially important that min_so_far is not accidentally
            updated before max_so_far is calculated.

            Using old_min makes the logic completely explicit and easier to
            understand during revision.
            */
            int old_max = max_so_far;
            int old_min = min_so_far;

            /*
            We have THREE choices for the new maximum product ending at nums[i]:

            Choice 1:
                Continue the previous maximum subarray:
                    old_max × nums[i]

            Choice 2:
                Continue the previous minimum subarray:
                    old_min × nums[i]

                This is essential because if nums[i] is negative,
                a large negative product may become a large positive product.

            Choice 3:
                Start a new subarray at nums[i]:
                    nums[i]

                We choose this when carrying the previous product would make
                the result worse. This is the same "start fresh" decision
                used in Kadane's Algorithm.

            Example:
                Previous product = 0
                Current number = 5

                Continuing gives:
                    0 × 5 = 0

                Starting fresh gives:
                    5

                So starting a new subarray is better.
            */
            max_so_far = max({
                old_max * nums[i],
                old_min * nums[i],
                nums[i]
            });

            /*
            We use the same THREE choices to calculate the new minimum.

            Why is the minimum important?

            Suppose:
                old_max = 4
                old_min = -6
                nums[i] = -3

            Then:
                old_max × -3 = -12  ← new minimum
                old_min × -3 = 18
                -3             = -3

            The previous maximum can become the new minimum after
            multiplication by a negative number.
            */
            min_so_far = min({
                old_max * nums[i],
                old_min * nums[i],
                nums[i]
            });

            /*
            max_so_far is the best product of a subarray ending at index i.

            Update ans because the best subarray could end at this index.

            We do not update ans using min_so_far because the answer we want
            is the maximum product, not the minimum product.
            */
            ans = max(ans, max_so_far);
        }

        /*
        After processing the complete array, ans contains the maximum product
        among all contiguous subarrays.
        */
        return ans;
    }
};


/*
================================================================================
REVISION SUMMARY — MAXIMUM PRODUCT SUBARRAY
LeetCode 152
================================================================================

ONE-LINE IDEA:
    Track both the maximum and minimum product ending at the current position,
    because a negative number can turn the minimum into the maximum.

--------------------------------------------------------------------------------
THE ANALOGY
--------------------------------------------------------------------------------

Imagine that at every index you have two runners:

    1. The "Best Positive Runner"
       This stores the largest product of a subarray ending here.

    2. The "Worst Negative Runner"
       This stores the smallest product of a subarray ending here.

Normally, the best runner seems more important. However, a negative number
can reverse their positions.

Example:

    max_so_far = 5
    min_so_far = -8
    current number = -2

After multiplying:

    5 × -2  = -10
    -8 × -2 = 16

The worst negative runner suddenly becomes the best positive runner.

That is why tracking only the maximum is not enough.

--------------------------------------------------------------------------------
THE KADANE'S ALGORITHM CONNECTION
--------------------------------------------------------------------------------

Normal Kadane's Algorithm for maximum subarray sum asks:

    Should I:
        1. Extend the previous subarray?
        2. Start a new subarray from the current element?

For maximum product, we ask the same question, but there are two states:

    new_max = max(
        old_max × current,
        old_min × current,
        current
    )

    new_min = min(
        old_max × current,
        old_min × current,
        current
    )

The "current" option means:

    "Forget everything before this element and start fresh."

This is the Kadane-style reset decision.

--------------------------------------------------------------------------------
THE THREE CHOICES AT EVERY ELEMENT
--------------------------------------------------------------------------------

For every nums[i], the subarray ending at nums[i] can be:

    1. old_max × nums[i]
       Extend the previous maximum product.

    2. old_min × nums[i]
       Extend the previous minimum product.
       This is crucial when nums[i] is negative.

    3. nums[i]
       Start a brand-new subarray at the current element.

We calculate the maximum of these three values for max_so_far
and the minimum of these three values for min_so_far.

--------------------------------------------------------------------------------
SMALL DRY RUN
--------------------------------------------------------------------------------

Input:
    nums = [2, 3, -2, 4]

Initial state:
    max_so_far = 2
    min_so_far = 2
    ans = 2

Process 3:

    Candidates:
        2 × 3 = 6
        2 × 3 = 6
        3     = 3

    max_so_far = 6
    min_so_far = 3
    ans = 6

Process -2:

    Candidates:
        6 × -2 = -12
        3 × -2 = -6
        -2     = -2

    max_so_far = -2
    min_so_far = -12
    ans = 6

Notice that the maximum became -2, but the minimum became -12.
That minimum may become useful if a later negative number appears.

Process 4:

    Candidates:
        -2 × 4  = -8
        -12 × 4 = -48
        4       = 4

    max_so_far = 4
    min_so_far = -48
    ans = 6

Final answer:
    6

The maximum-product subarray is:
    [2, 3]

--------------------------------------------------------------------------------
WHY ZERO WORKS NATURALLY
--------------------------------------------------------------------------------

Suppose the array is:

    [2, 3, 0, 4, 5]

Before zero:
    Best product may be 6.

At zero:
    Any product carried from the left becomes 0.

The algorithm compares:

    old_max × 0
    old_min × 0
    0

So both states become 0.

At 4, it compares:

    0 × 4 = 0
    0 × 4 = 0
    4     = 4

Therefore, it automatically starts a new subarray after zero.

No special zero-handling code is required.

--------------------------------------------------------------------------------
WHY WE STORE old_max AND old_min
--------------------------------------------------------------------------------

The new maximum and new minimum must both be calculated from the
previous state.

If we update max_so_far first and then use the updated value to calculate
min_so_far, we would accidentally mix values from different time steps.

The correct transition is:

    new_max = calculated from old_max and old_min
    new_min = calculated from old_max and old_min

That is why we save:

    old_max = max_so_far
    old_min = min_so_far

before updating either variable.

--------------------------------------------------------------------------------
COMPLEXITY
--------------------------------------------------------------------------------

Time Complexity:
    O(n)

Why?

    We visit every element exactly once.
    At each element, we perform a constant number of operations.

Space Complexity:
    O(1)

Why?

    We use only a few integer variables:
        max_so_far
        min_so_far
        ans
        old_max
        old_min

--------------------------------------------------------------------------------
COMMON MISTAKES
--------------------------------------------------------------------------------

1. Tracking only the maximum product

   This fails because a negative minimum can become the maximum after
   multiplication by another negative number.

2. Forgetting the "start fresh" option

   We must compare against nums[i] itself. Otherwise, we are forced to
   include earlier elements even when they make the product worse.

3. Updating max_so_far before calculating min_so_far

   Both new values must use the previous maximum and previous minimum.
   Updating one too early can produce an invalid transition.

4. Initializing everything to zero

   This can fail when all numbers are negative. For example:

       [-3]

   The correct answer is -3, not 0.

   Therefore, initialize all states using nums[0].

--------------------------------------------------------------------------------
TRIGGER WORDS
--------------------------------------------------------------------------------

When you see:

    "maximum product"
    "contiguous subarray"
    "negative numbers"
    "product can change sign"
    "subarray ending at each index"

Think:

    "This may be a two-state Kadane problem."

For maximum sum:
    Track only the best state.

For maximum product:
    Track both the best and worst states.

--------------------------------------------------------------------------------
MEMORY FORMULA
--------------------------------------------------------------------------------

At every number x:

    new_max = max(old_max × x, old_min × x, x)

    new_min = min(old_max × x, old_min × x, x)

    answer = max(answer, new_max)

Remember:

    Maximum + negative number → may become minimum
    Minimum + negative number → may become maximum
    Current number alone       → may start a fresh subarray
================================================================================
*/









// class Solution {
// public:
//     int maxProduct(vector<int>& nums) {
//         int n = nums.size();
        
//         // Initialize both max and min with the first element
//         // Why both? Because a negative number can flip min to max
//         int max_so_far = nums[0];
//         int min_so_far = nums[0];
//         int ans = nums[0];  // This is our "trophy plaque" - best answer seen so far
        
//         for (int i = 1; i < n; i++) {
//             // CRITICAL: Store the old max before updating it
//             // Because we need BOTH old max AND old min to calculate new values
//             // If we update max_so_far first, we lose the old value needed for min calculation
//             int old_max = max_so_far;
            
//             // THREE CHOICES for new maximum:
//             // 1. Extend previous max by multiplying with current number
//             // 2. Extend previous min by multiplying (negative flip could make this the new max!)
//             // 3. Start fresh with just the current number (abandon all baggage)
//             max_so_far = max({old_max * nums[i], min_so_far * nums[i], nums[i]});
            
//             // THREE CHOICES for new minimum:
//             // Same logic, but we want the smallest (most negative) result
//             // A big positive × negative = big negative (new minimum)
//             // A big negative × negative = big positive (probably not the new minimum)
//             min_so_far = min({old_max * nums[i], min_so_far * nums[i], nums[i]});
            
//             // Update the trophy plaque with the best we've seen anywhere so far
//             ans = max(ans, max_so_far);
//         }
        
//         return ans;
//     }
// };










// class Solution {
// public:
//     int maxProduct(vector<int>& nums) {
//         int n = nums.size();

//         int maxending = nums[0];
//         int minending = nums[0];
//         int res = nums[0];


//         for(int i = 1; i<n; i++){
//             int v1 = nums[i];
//             int v2 = minending * nums[i];
//             int v3 = maxending * nums[i];

//             maxending = max(nums[i], max(v2, v3));
//             minending = min(nums[i], min(v2, v3));

//             res = max(res, max(maxending, minending));

//         }
//         return res;
//     }
// };




// BRute force approach
// class Solution {
// public:
//     int maxProduct(vector<int>& nums) {
//         int n = nums.size();

//         int maxprod = -10;

//         for(int i =0; i<n; i++){
//             int product = 1;

//             for(int j = i; j<n; j++){
//                 product *= nums[j];

//                 maxprod = max(maxprod, product);
//             }
//         }
//         return maxprod;
//     }
// };