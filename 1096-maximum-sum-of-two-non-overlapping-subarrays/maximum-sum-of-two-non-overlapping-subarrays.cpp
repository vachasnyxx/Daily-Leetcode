class Solution {
public:

    /*
    This helper solves only one arrangement:

        [leftLen subarray] [rightLen subarray]

    For example, if we call:

        helper(nums, firstLen, secondLen)

    then the firstLen subarray must appear before the secondLen subarray.

    We will call this helper twice in the main function:

        1. helper(nums, firstLen, secondLen)
        2. helper(nums, secondLen, firstLen)

    This handles both possible arrangements.
    */
    int helper(
        vector<int>& nums,
        int leftLen,
        int rightLen
    ) {
        int n = nums.size();

        /*
        Build the prefix-sum array.

        prefix[i] stores the sum of elements from index 0
        up to index i - 1.

        Example:

            nums   = [1, 2, 3, 4]
            prefix = [0, 1, 3, 6, 10]

        So the sum of any subarray nums[left ... right] is:

            prefix[right + 1] - prefix[left]

        Example: sum of [2, 3]:

            prefix[3] - prefix[1]
            = 6 - 1
            = 5
        */
        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        /*
        bestLeftSum represents:

            The maximum sum of any leftLen subarray
            that ends before the current rightLen subarray begins.

        This is the key optimization.

        Instead of trying every possible left subarray again for every
        right subarray, we remember the best left subarray seen so far.

        Initially, no valid left subarray has been processed.
        Since nums contains non-negative values in this problem,
        starting with 0 is safe.
        */
        int bestLeftSum = 0;

        /*
        answer stores the maximum combined sum found so far.

            answer = best valid left subarray
                   + current right subarray
        */
        int answer = 0;

        /*
        rightStart is the starting index of the current right subarray.

        The current right subarray is:

            nums[rightStart ... rightStart + rightLen - 1]

        We start rightStart from leftLen because the left subarray must
        have leftLen elements before the right subarray begins.

        Example:

            leftLen = 2

        The earliest possible right subarray starts at index 2 because
        indices 0 and 1 can be used by the left subarray.
        */
        for (
            int rightStart = leftLen;
            rightStart + rightLen <= n;
            rightStart++
        ) {
            /*
            The latest possible left subarray before rightStart is:

                nums[rightStart - leftLen ... rightStart - 1]

            Its length is exactly leftLen.

            Example:

                rightStart = 5
                leftLen = 2

                left subarray:
                    nums[3 ... 4]

            It ends at index 4, immediately before the right subarray
            starts at index 5.

            Calculate its sum using prefix sums:
            */
            int currentLeftSum =
                prefix[rightStart] -
                prefix[rightStart - leftLen];

            /*
            Update the best left subarray seen so far.

            Why do we do this before calculating the right sum?

            Because currentLeftSum is the left window that ends immediately
            before the current right window.

            Therefore, it is a valid candidate and should be included in
            bestLeftSum before forming the combined answer.
            */
            bestLeftSum = max(bestLeftSum, currentLeftSum);

            /*
            Calculate the sum of the current right subarray:

                nums[rightStart ... rightStart + rightLen - 1]

            Prefix-sum formula:

                prefix[rightStart + rightLen] - prefix[rightStart]
            */
            int currentRightSum =
                prefix[rightStart + rightLen] -
                prefix[rightStart];

            /*
            Combine the best valid left subarray with the current right
            subarray.

            These two subarrays cannot overlap because:

                - The left subarray ends before rightStart.
                - The right subarray begins at rightStart.

            Update the global answer.
            */
            answer = max(
                answer,
                bestLeftSum + currentRightSum
            );
        }

        return answer;
    }


    int maxSumTwoNoOverlap(
        vector<int>& nums,
        int firstLen,
        int secondLen
    ) {
        /*
        First possible arrangement:

            [firstLen subarray] [secondLen subarray]

        Here, the firstLen subarray appears on the left.
        */
        int firstOrder =
            helper(nums, firstLen, secondLen);

        /*
        Second possible arrangement:

            [secondLen subarray] [firstLen subarray]

        Here, the secondLen subarray appears on the left.
        */
        int secondOrder =
            helper(nums, secondLen, firstLen);

        /*
        The answer may come from either arrangement.

        Therefore, return the larger result.
        */
        return max(firstOrder, secondOrder);
    }
};


/*
================================================================================
REVISION NOTES — LEETCODE 1031
MAXIMUM SUM OF TWO NON-OVERLAPPING SUBARRAYS
================================================================================

ONE-LINE DEFINITION:

    Find two fixed-length, non-overlapping subarrays whose combined sum
    is as large as possible.

--------------------------------------------------------------------------------
MAIN ANALOGY
--------------------------------------------------------------------------------

Imagine two trains moving on a railway track.

    - The first train has length leftLen.
    - The second train has length rightLen.
    - The trains cannot occupy the same track section.

We move the right train from left to right.

Before placing the right train at a particular position, we ask:

    "What is the best left train that could have been placed before it?"

We store the answer to that question in:

    bestLeftSum

Then for every right train position:

    total = bestLeftSum + currentRightSum

This prevents us from repeatedly checking every possible left train.

--------------------------------------------------------------------------------
WHY PREFIX SUMS?
--------------------------------------------------------------------------------

We need to calculate the sum of many fixed-length windows.

Instead of adding every element again and again, construct:

    prefix[i + 1] = prefix[i] + nums[i]

Then:

    sum of nums[left ... right]
    = prefix[right + 1] - prefix[left]

For a window starting at start with length length:

    windowSum = prefix[start + length] - prefix[start]

This gives every window sum in O(1) time.

--------------------------------------------------------------------------------
THE IMPORTANT STATE
--------------------------------------------------------------------------------

The most important variable is:

    bestLeftSum

At any point in the loop, it means:

    The maximum sum of a leftLen window that finishes before
    the current rightLen window begins.

This guarantees that the two selected windows do not overlap.

--------------------------------------------------------------------------------
WHY DOES bestLeftSum WORK?
--------------------------------------------------------------------------------

Suppose:

    rightStart = 5
    leftLen = 2

The current right window begins at index 5.

The latest valid left window is:

    nums[3 ... 4]

But any earlier length-2 window is also valid:

    nums[0 ... 1]
    nums[1 ... 2]
    nums[2 ... 3]
    nums[3 ... 4]

Instead of checking all of them every time, we keep the largest one
inside bestLeftSum.

So when we calculate:

    bestLeftSum + currentRightSum

we already know that bestLeftSum is the best possible partner for
the current right window.

--------------------------------------------------------------------------------
WHY DO WE RUN THE LOGIC TWICE?
--------------------------------------------------------------------------------

The subarrays can appear in two orders:

Order 1:

    [firstLen subarray] [secondLen subarray]

Order 2:

    [secondLen subarray] [firstLen subarray]

The helper handles only the order:

    [leftLen subarray] [rightLen subarray]

Therefore, the main function calculates:

    helper(nums, firstLen, secondLen)
    helper(nums, secondLen, firstLen)

Then it returns the larger value.

--------------------------------------------------------------------------------
DRY RUN
--------------------------------------------------------------------------------

Input:

    nums = [1, 2, 3, 4, 5]
    firstLen = 2
    secondLen = 1

Consider the order:

    [length-2 subarray] [length-1 subarray]

The prefix array is:

    nums:   [1, 2, 3, 4, 5]
    prefix: [0, 1, 3, 6, 10, 15]

Initial values:

    bestLeftSum = 0
    answer = 0

rightStart = 2:

    Current left window:
        [1, 2]
        sum = 3

    Current right window:
        [3]
        sum = 3

    bestLeftSum = max(0, 3) = 3
    answer = max(0, 3 + 3) = 6


rightStart = 3:

    Current left window:
        [2, 3]
        sum = 5

    Current right window:
        [4]
        sum = 4

    bestLeftSum = max(3, 5) = 5
    answer = max(6, 5 + 4) = 9


rightStart = 4:

    Current left window:
        [3, 4]
        sum = 7

    Current right window:
        [5]
        sum = 5

    bestLeftSum = max(5, 7) = 7
    answer = max(9, 7 + 5) = 12

The answer for this ordering is:

    12

The chosen subarrays are:

    [3, 4] and [5]

Then we run the helper in the opposite order as well.

--------------------------------------------------------------------------------
VISUAL LOOP STRUCTURE
--------------------------------------------------------------------------------

For every right window:

    1. Find the latest left window that can be valid.
    2. Add it to bestLeftSum if it is better.
    3. Calculate the current right window sum.
    4. Combine bestLeftSum and currentRightSum.
    5. Update answer.

In short:

    update best left
    calculate current right
    combine them
    update answer

--------------------------------------------------------------------------------
COMPLEXITY
--------------------------------------------------------------------------------

Prefix-sum construction:

    O(n)

Each helper scans the array once:

    O(n)

The helper is called twice:

    O(n) + O(n) = O(n)

Final complexity:

    Time Complexity:  O(n)
    Space Complexity: O(n)

The extra space is used by the prefix array.

--------------------------------------------------------------------------------
COMMON MISTAKES
--------------------------------------------------------------------------------

1. Checking only one ordering

   Wrong idea:

       [firstLen] before [secondLen]

   The best answer may have:

       [secondLen] before [firstLen]

   That is why the helper is called twice.

2. Updating bestLeftSum using an invalid window

   The left window must finish before rightStart.

   The correct left window is:

       [rightStart - leftLen ... rightStart - 1]

3. Allowing the windows to overlap

   If the left window ends at index rightStart or later,
   it overlaps with the right window.

4. Calculating every window sum from scratch

   Prefix sums make each window sum O(1).

5. Thinking bestLeftSum means the best left window anywhere

   It does not mean the best window in the entire array.

   It means:

       The best left window among only those windows that are already
       completely before the current right window.

--------------------------------------------------------------------------------
PATTERN TRIGGER WORDS
--------------------------------------------------------------------------------

When a problem says:

    - Two subarrays
    - Fixed lengths
    - Non-overlapping
    - Maximum combined sum
    - Contiguous subarrays

Think:

    Prefix Sum + Sliding Window + Running Maximum

--------------------------------------------------------------------------------
BRUTE FORCE TO OPTIMIZED TRANSITION
--------------------------------------------------------------------------------

Brute force asks:

    For every right window, check every possible left window.

Optimized approach asks:

    Can I remember the best valid left window while moving right?

Yes.

That remembered value is:

    bestLeftSum

This removes one complete loop and changes:

    O(n²) → O(n)

================================================================================
*/