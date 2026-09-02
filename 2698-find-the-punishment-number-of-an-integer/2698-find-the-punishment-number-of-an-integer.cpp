// Approach 2 using recursion 
// class Solution {
// public:
//     bool check(int sq, int currsum, int num) {

//         if (sq == 0) {
//             return currsum == num;
//         }

//         return check(sq / 10, currsum + sq % 10, num) ||
//                check(sq / 100, currsum + sq % 100, num) ||
//                check(sq / 1000, currsum + sq % 1000, num) || check(sq / 10000, currsum + sq % 10000, num);
//     }
//     int punishmentNumber(int n) {
//         int punish = 0;

//         for (int num = 1; num <= n; num++) {
//             int sq = num * num;

//             if (check(sq, 0, num) == true) {
//                 punish += sq;
//             }
//         }

//         return punish;
//     }
// };





class Solution {
public:

    // --------------------------------------------------------------------
    // Function: check
    //
    // Purpose:
    // Check whether the digits of `sq` can be divided into contiguous
    // groups whose sum is exactly equal to `num`.
    //
    // Example:
    // sq = 1296, num = 36
    //
    // One possible partition is:
    // 1 | 2 | 9 | 6
    // Sum = 1 + 2 + 9 + 6 = 18  -> not equal to 36
    //
    // Another possible partition is:
    // 12 | 9 | 6
    // Sum = 12 + 9 + 6 = 27     -> not equal to 36
    //
    // Another possible partition is:
    // 1 | 29 | 6
    // Sum = 1 + 29 + 6 = 36     -> valid
    //
    // Parameters:
    //
    // sq:
    // The remaining part of the square that we still need to process.
    //
    // currsum:
    // The sum of the digit-groups that we have already removed.
    //
    // num:
    // The target number. The final sum of all groups must become num.
    // --------------------------------------------------------------------
    bool check(int sq, int currsum, int num) {

        // ----------------------------------------------------------------
        // BASE CASE
        //
        // If sq becomes 0, there are no digits left to process.
        //
        // This means we have successfully consumed all digits of the
        // square. Now we check whether the sum of all selected groups
        // is exactly equal to the original number.
        //
        // Example:
        // sq = 0
        // currsum = 10
        // num = 10
        //
        // Since currsum == num, this partition is valid.
        //
        // Recursion always needs a stopping condition.
        // Without this base case, the recursive calls would continue
        // indefinitely or eventually cause a stack overflow.
        // ----------------------------------------------------------------
        if (sq == 0) {
            return currsum == num;
        }

        // ----------------------------------------------------------------
        // RECURSIVE / BACKTRACKING PART
        //
        // At every step, we remove a group from the RIGHT side of sq.
        //
        // We try four possibilities:
        //
        // 1. Remove the last 1 digit
        // 2. Remove the last 2 digits
        // 3. Remove the last 3 digits
        // 4. Remove the last 4 digits
        //
        // The `||` operator means:
        //
        // "If even one of these choices eventually gives a valid
        // partition, return true."
        //
        // This is a depth-first search over all possible partitions.
        // We try one choice completely, and if it fails, we try the
        // next choice.
        // ----------------------------------------------------------------


        // ================================================================
        // CHOICE 1: Take the last 1 digit
        // ================================================================
        //
        // `sq % 10` extracts the last digit.
        //
        // Example:
        // sq = 1296
        // sq % 10 = 6
        //
        // `sq / 10` removes the last digit.
        //
        // 1296 / 10 = 129
        //
        // So this branch:
        //
        // check(129, currsum + 6, num)
        //
        // means:
        // "Take 6 as one group and recursively process 129."
        //
        return check(sq / 10, currsum + sq % 10, num)

        ||

        // ================================================================
        // CHOICE 2: Take the last 2 digits
        // ================================================================
        //
        // `sq % 100` extracts the last two digits.
        //
        // Example:
        // sq = 1296
        // sq % 100 = 96
        //
        // `sq / 100` removes the last two digits.
        //
        // 1296 / 100 = 12
        //
        // So this branch:
        //
        // check(12, currsum + 96, num)
        //
        // means:
        // "Take 96 as one group and recursively process 12."
        //
        check(sq / 100, currsum + sq % 100, num)

        ||

        // ================================================================
        // CHOICE 3: Take the last 3 digits
        // ================================================================
        //
        // `sq % 1000` extracts the last three digits.
        //
        // Example:
        // sq = 1296
        // sq % 1000 = 296
        //
        // `sq / 1000` removes the last three digits.
        //
        // 1296 / 1000 = 1
        //
        // So this branch:
        //
        // check(1, currsum + 296, num)
        //
        // means:
        // "Take 296 as one group and recursively process 1."
        //
        check(sq / 1000, currsum + sq % 1000, num)

        ||

        // ================================================================
        // CHOICE 4: Take the last 4 digits
        // ================================================================
        //
        // `sq % 10000` extracts the last four digits.
        //
        // Example:
        // sq = 1296
        // sq % 10000 = 1296
        //
        // `sq / 10000` removes the last four digits.
        //
        // 1296 / 10000 = 0
        //
        // So this branch:
        //
        // check(0, currsum + 1296, num)
        //
        // means:
        // "Take the complete remaining number as one group."
        //
        // This fourth branch is important. Without it, your code would
        // not try partitions containing a group of four digits.
        //
        // For example, if sq = 10000, this branch can take 10000 as a
        // single group.
        //
        check(sq / 10000, currsum + sq % 10000, num);
    }


    // --------------------------------------------------------------------
    // Function: punishmentNumber
    //
    // Purpose:
    // Calculate the punishment number of n.
    //
    // For every number `num` from 1 to n:
    //
    // 1. Calculate its square.
    // 2. Check whether the square's digits can be partitioned into groups
    //    whose sum equals num.
    // 3. If yes, add the square to the answer.
    // --------------------------------------------------------------------
    int punishmentNumber(int n) {

        // Stores the final sum of squares of all valid numbers.
        int punish = 0;


        // Try every number from 1 through n.
        for (int num = 1; num <= n; num++) {

            // Calculate the square of the current number.
            //
            // Example:
            // num = 9
            // sq = 81
            int sq = num * num;


            // Start checking from:
            //
            // sq       = the complete square
            // currsum  = 0, because no digit-group has been selected yet
            // num      = the target sum
            //
            // If at least one valid partition exists, add the square
            // to the punishment number.
            if (check(sq, 0, num) == true) {
                punish += sq;
            }
        }


        // Return the sum of squares of all valid punishment numbers.
        return punish;
    }
};


/*
===============================================================================
LEETCODE 2698 — PUNISHMENT NUMBER OF AN INTEGER
DETAILED REVISION NOTES
===============================================================================

1. PROBLEM IN SIMPLE ENGLISH
--------------------------------

For every number `num` from 1 to n:

- Calculate `num * num`.
- Look at the digits of that square.
- Split those digits into contiguous groups.
- Add the groups.
- If their sum equals `num`, add the square to the answer.

The groups must:

- Maintain their original order.
- Use every digit exactly once.
- Be contiguous.
- Not skip any digit.
- Not rearrange the digits.

Example:

num = 9
square = 81

Possible partitions:

8 | 1  -> 8 + 1 = 9

Therefore, 9 is valid and 81 is added to the answer.


Another example:

num = 10
square = 100

Possible partition:

10 | 0  -> 10 + 0 = 10

Therefore, 10 is valid and 100 is added.


2. MAIN PATTERN
-------------------------------

This problem uses:

- Recursion.
- Backtracking.
- Digit manipulation.
- Partitioning.
- Depth-first search.

The central question is:

"At the current position, how many digits should I include in
the current group?"

In your implementation, instead of processing digits from left to right,
you process them from right to left.

At every recursive call, you make four choices:

- Take 1 digit.
- Take 2 digits.
- Take 3 digits.
- Take 4 digits.

Then you recursively process the remaining prefix.


3. ANALOGY
-------------------------------

Imagine that the square is written on a paper strip:

    1296

You stand at the RIGHT side of the strip.

At every step, you can cut off:

- 1 digit: 6
- 2 digits: 96
- 3 digits: 296
- 4 digits: 1296

After cutting one group, you move left and repeat the same process.

For example, if you choose:

    1296
       ^

Take 1 digit:

    129 | 6

Now process 129.

From 129, you can choose:

    12 | 9
    1  | 29
    0  | 129

Every sequence of cuts represents one possible partition.

The algorithm succeeds if at least one sequence of cuts produces a
sum equal to `num`.

That is why the recursive calls are connected using `||`.


4. UNDERSTANDING THE PARAMETERS
--------------------------------

The helper function is:

    check(sq, currsum, num)

Meaning:

- `sq`: digits still remaining.
- `currsum`: sum of groups already removed.
- `num`: target sum.

Example:

    check(1296, 0, 36)

This means:

- The remaining digits are 1296.
- We have selected nothing yet, so the current sum is 0.
- We want the final sum to be 36.

Suppose we choose the last digit 6:

    check(129, 6, 36)

Now:

- Remaining digits: 129.
- Current sum: 6.
- Target: 36.

Suppose next we choose 29:

    check(1, 35, 36)

Now:

- Remaining digits: 1.
- Current sum: 6 + 29 = 35.
- Target: 36.

Finally choose 1:

    check(0, 36, 36)

Now all digits are consumed and the sum equals the target.
The function returns true.


5. HOW DIGIT EXTRACTION WORKS
--------------------------------

C++ integer arithmetic is being used to remove digits.

For:

    sq = 1296

Last 1 digit:

    sq % 10 = 6
    sq / 10 = 129

Last 2 digits:

    sq % 100 = 96
    sq / 100 = 12

Last 3 digits:

    sq % 1000 = 296
    sq / 1000 = 1

Last 4 digits:

    sq % 10000 = 1296
    sq / 10000 = 0

The `%` operator extracts the suffix.

The `/` operator removes the suffix.

General rule:

    suffix = sq % 10^digits
    remaining = sq / 10^digits


6. WHY THE FOURTH BRANCH MATTERS
--------------------------------

Your updated code contains this branch:

    check(sq / 10000, currsum + sq % 10000, num)

This tries taking the last 4 digits as one group.

It matters because the square may contain four digits, and a valid
partition may require all four digits to stay together.

Example:

    sq = 1296

The fourth branch tries:

    1296

as one complete group.

Without this branch, the algorithm would only try groups of size
1, 2, or 3. It would never explicitly try a four-digit group.

Important caution:

For the original LeetCode 2698 constraints, `n <= 1000`, so the square
can have up to 7 digits. Your code tries groups of size only 1 to 4,
which is enough for the usual accepted solution because the target
number is at most 1000 and a group larger than the target cannot help
create a positive target sum.

However, the general partition approach would normally try every
possible group length, not only four fixed lengths. Your code is written
for the given problem constraints and accepted recursive pattern.


7. BASE CASE
--------------------------------

The base case is:

    if (sq == 0) {
        return currsum == num;
    }

It means:

- No digits are left.
- Every digit has been included in some group.
- Now compare the calculated sum with the target.

There are only two possibilities:

    currsum == num  -> valid partition
    currsum != num  -> invalid partition

Example:

    check(0, 10, 10) -> true
    check(0, 12, 10) -> false


8. COMPLETE DRY RUN
--------------------------------

Take:

    num = 9
    sq = 81

Initial call:

    check(81, 0, 9)

The first branch takes the last digit:

    81 % 10 = 1
    81 / 10 = 8

So:

    check(8, 1, 9)

Again, take the last digit:

    8 % 10 = 8
    8 / 10 = 0

So:

    check(0, 9, 9)

Now `sq == 0`.

Check:

    currsum == num
    9 == 9

Therefore:

    return true

The remaining branches are not evaluated because `||` stops as soon
as it finds true.


9. ANOTHER DRY RUN WITH BACKTRACKING
--------------------------------

Take:

    num = 10
    sq = 100

Initial call:

    check(100, 0, 10)

The function tries several possibilities.

One successful path is:

    Take last 2 digits: 00
    Remaining part: 1
    Current sum: 0

Then:

    Take last 1 digit: 1
    Remaining part: 0
    Current sum: 1

This path gives 1, not 10.

Another path is:

    Take last 1 digit: 0
    Remaining part: 10
    Current sum: 0

Then:

    Take last 2 digits: 10
    Remaining part: 0
    Current sum: 10

Now:

    check(0, 10, 10)

This returns true.

The corresponding partition, viewed from left to right, is:

    10 | 0

Its sum is:

    10 + 0 = 10

Therefore, square 100 is added.


10. WHY THIS IS BACKTRACKING
--------------------------------

Backtracking means:

- Make a choice.
- Recursively explore that choice.
- If it fails, return and try another choice.

Your code makes choices about how many digits to include in the next
group.

For every `sq`, it explores:

    1-digit choice
    2-digit choice
    3-digit choice
    4-digit choice

The algorithm does not manually undo `currsum` because `currsum` is
passed by value.

Each recursive call receives its own copy.

For example:

    check(129, 6, num)

If another branch is tried, it receives its own separate value of
`currsum`. This prevents one branch from corrupting another branch.


11. WHY `||` IS USED
--------------------------------

The problem asks whether ANY valid partition exists.

Therefore, logical OR is exactly the correct operation.

    true || anything = true
    false || true = true
    false || false = false

Interpretation:

- If one partition works, return true.
- If all partitions fail, return false.

Because C++ uses short-circuit evaluation, once one branch returns
true, later branches are skipped.

This improves practical performance.


12. TIME COMPLEXITY
--------------------------------

Let d be the number of digits in `num * num`.

At each recursive level, the function can make up to 4 recursive calls:

- Remove 1 digit.
- Remove 2 digits.
- Remove 3 digits.
- Remove 4 digits.

The worst-case recursion tree is approximately:

    4^d

For every number from 1 to n, we perform this search.

Therefore, the general time complexity is:

    O(n * 4^d)

where:

- n is the number of candidate values.
- d is the number of digits in the square.

For LeetCode 2698, n <= 1000.

The square is at most:

    1000 * 1000 = 1,000,000

So d is at most 7.

Therefore, the recursive part is bounded by a small constant for this
problem, making the practical performance very fast.

Interview explanation:

"For each number from 1 to n, I calculate its square and perform a
bounded backtracking search over its digits. At every step I try
taking 1 to 4 digits as the next group. If d is the number of digits
in the square, the search takes O(4^d), so the total complexity is
O(n * 4^d). Since d is at most 7 under the constraints, this is
effectively efficient for the problem."

Important honesty:

Do not simply say the time complexity is O(n). That hides the recursive
search. The more accurate answer is:

    O(n * 4^d)

Then explain that d is very small because the constraints are small.


13. SPACE COMPLEXITY
--------------------------------

The deepest recursive path removes at least one digit at a time.

Therefore, the maximum recursion depth is O(d), where d is the number
of digits in the square.

No array, vector, map, or string is created.

So:

    Space complexity = O(d)

For this problem, d is at most 7, so it is effectively O(1) under
the fixed constraints.

Interview explanation:

"The algorithm uses no auxiliary data structures. The only extra space
is the recursion call stack, whose depth is at most the number of digits
in the square, so the space complexity is O(d), effectively constant
for the given constraints."


14. COMMON MISTAKES
--------------------------------

Mistake 1:
Thinking that `sq % 100` gives the second-last digit.

It gives the last two digits as one number.

    1296 % 100 = 96

Mistake 2:
Forgetting that groups must be contiguous.

You cannot rearrange digits or skip digits.

Valid:

    1 | 29 | 6

Invalid:

    1 | 6 | 29

Mistake 3:
Forgetting the base case.

The recursion must stop when all digits have been consumed.

Mistake 4:
Using only one recursive branch.

A single partition choice is not enough. You must explore all possible
group sizes.

Mistake 5:
Not understanding why `currsum` is passed by value.

Each branch needs its own independent sum. Passing by value automatically
keeps branches separate.

Mistake 6:
Giving an incomplete complexity answer.

The recursion creates a branching tree. Mention both:

    O(n * 4^d) time
    O(d) recursion space


15. TRIGGER WORDS FOR THIS PATTERN
--------------------------------

When you see these clues, think about recursion and backtracking:

- Split digits into groups.
- Partition a number or string.
- Sum of partitions.
- Try every possible cut.
- Preserve the order of digits.
- Determine whether any valid decomposition exists.
- Explore all possible ways to divide a sequence.


16. ONE-LINE MEMORY FORMULA
--------------------------------

"At every step, remove 1, 2, 3, or 4 digits from the right, add that
group to the running sum, and recursively check whether the remaining
digits can complete the target."


17. INTERVIEW-READY ANSWER
--------------------------------

"I iterate from 1 to n and calculate each number's square. For every
square, I use recursive backtracking to partition its digits into
contiguous groups. The helper tries taking the last 1, 2, 3, or 4
digits, adds that group to the current sum, and recursively processes
the remaining prefix. When no digits remain, the partition is valid if
the accumulated sum equals the original number. The time complexity is
O(n * 4^d), where d is the number of digits in the square, and the
space complexity is O(d) for the recursion stack."


18. FINAL MENTAL MODEL
--------------------------------

Think of the square's digits as a chocolate bar.

At every turn, you may break off:

    1 piece
    2 pieces
    3 pieces
    4 pieces

You add the value of the piece to your running total and continue with
the chocolate that remains.

If one sequence of breaks produces exactly the original number, the
square qualifies.

That is the complete idea behind this solution:

    Try every possible cut.
    Recursively solve the remaining digits.
    Accept the first successful partition.
===============================================================================
*/






















// class Solution {
// public:
//     bool check(int i, int currsum, string s, int num, vector<vector<int>>&
//     t){
//         if(i == s.size()){
//             return currsum == num;
//         }

//         if(currsum > num){
//             return false;
//         }

//         if(t[i][currsum] != -1){
//             return t[i][currsum];
//         }

//         bool possible = false;

//         for(int j = i; j<s.size(); j++){
//             string sub = s.substr(i, j-i+1);

//             int val = stoi(sub);

//             possible = possible || check(j+1, currsum+val,s,num,t);

//             if(possible == true){
//                 return true;
//             }
//         }

//         return  t[i][currsum] = possible;
//     }
//     int punishmentNumber(int n) {
//         int punish = 0;

//         for(int num  = 1; num <= n; num++){
//             int sq = num * num;

//             string s = to_string(sq);

//             vector<vector<int>> t(s.length(), vector<int> (num+1, -1));

//             if(check(0,0,s,num,t) == true){
//                 punish += sq;
//             }
//         }

//         return punish;
//     }
// };
