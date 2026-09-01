// class Solution {
// public:

//     int Count(long curr,long next, int n){
//         int countNum = 0;

//         while(curr <= n){
//             countNum += (next - curr);

//             curr *= 10;
//             next *= 10;

//             next = min(next, long(n+1));
//         }

//         return countNum;
//     }
//     int findKthNumber(int n, int k) {
//         int curr = 1;

//         k -= 1;// since we start from the first number(1) , we need k - 1 more number

//         while(k > 0){
//             int count = Count(curr, curr+1, n);
//             if(count <= k){
//                 curr++;
//                 k -= count;// skipping the elements under curr prefix tree

//             }
//             else{
//                 curr *= 10;
//                 k -= 1;
//             }
//         }
//         return curr;
//     }
// };






// ============================================================
// LeetCode 440 - K-th Smallest in Lexicographical Order
// Pattern: PREFIX COUNTING + GREEDY NAVIGATION IN IMPLICIT TRIE
// Difficulty: Hard (but the "hard" part is the Count() insight,
// NOT the main loop logic)
// ============================================================

class Solution {
public:

    // ------------------------------------------------------------
    // Count(curr, next, n)
    // Returns: how many integers in [1, n] have a lexicographical
    // representation that starts with the prefix `curr` (i.e., how
    // many numbers live in the "subtree" rooted at `curr` in our
    // virtual trie from LC 386).
    // ------------------------------------------------------------
    //
    // CORE INTUITION -- "Counting nodes level-by-level in a virtual trie":
    // Recall from LC 386 that numbers in lexicographical order form
    // a virtual trie where:
    //   - Node "1" has children "10", "11", ..., "19"
    //   - Node "10" has children "100", "101", ..., "109"
    //   - Node "100" has children "1000", "1001", ..., "1009"
    //   - ... and so on.
    //
    // The "subtree" of node `curr` includes:
    //   - `curr` itself (1 number)
    //   - All numbers starting with `curr` followed by one more digit
    //     (e.g., if curr=1, then 10, 11, ..., 19 -- up to 10 numbers)
    //   - All numbers starting with `curr` followed by TWO more digits
    //     (e.g., if curr=1, then 100, 101, ..., 199 -- up to 100 numbers)
    //   - ... and so on, until we exceed n.
    //
    // Instead of generating all these numbers (which would be O(n) and
    // defeat the purpose of this optimization), we COUNT them
    // level-by-level using pure math.
    //
    // HOW IT WORKS:
    // - `curr` represents the START of the current level's range
    //   (e.g., at level 1: curr=1, at level 2: curr=10, at level 3: curr=100)
    // - `next` represents the END of the current level's range (exclusive)
    //   (e.g., at level 1: next=2, at level 2: next=20, at level 3: next=200)
    // - The number of valid nodes at this level is: min(next, n+1) - curr
    //   (we use n+1 because the range is [curr, next), and we must not
    //   count anything > n)
    // - We then move to the next level by multiplying both by 10
    //   (curr *= 10, next *= 10), which shifts us from "1" to "10" to
    //   "100", etc.
    //
    // WHY THIS IS O(log n):
    // Each iteration multiplies by 10, so we only loop ~log₁₀(n) times
    // (at most 10 iterations for n up to 10^9). This is vastly faster
    // than actually generating all numbers under the prefix.
    int Count(long curr, long next, int n) {
        int countNum = 0;

        // ---- LOOP: count nodes level-by-level until we exceed n ----
        while (curr <= n) {
            // At this level, the valid numbers are in the range [curr, next).
            // But we must not count anything > n, so we cap `next` at n+1.
            // The count of valid numbers at this level is: (capped_next - curr)
            // which equals: min(next, n+1) - curr
            //
            // BUT: the code does this in two steps:
            //   1. countNum += (next - curr)  [add the raw range size]
            //   2. next = min(next, n+1)      [cap next for the NEXT iteration]
            //
            // This works because on the FIRST iteration, next is guaranteed
            // to be <= n+1 (since next = curr + 1 initially, and curr <= n).
            // On subsequent iterations, next might exceed n+1, so we cap it
            // BEFORE using it in the next loop's subtraction.
            countNum += (next - curr);

            // Move to the next level of the trie (append one more digit)
            curr *= 10;
            next *= 10;

            // Cap `next` so we don't count numbers > n in future iterations.
            // We use n+1 (not n) because the range [curr, next) is exclusive
            // on the right, so next = n+1 means "up to and including n".
            next = min(next, long(n + 1));
        }

        return countNum;
    }

    // ------------------------------------------------------------
    // findKthNumber(n, k)
    // Returns: the k-th smallest number in lexicographical order
    // among all integers from 1 to n.
    // ------------------------------------------------------------
    //
    // CORE INTUITION -- "Greedy navigation: skip whole subtrees or dive deeper":
    // We start at the root of our virtual trie (conceptually at node "1",
    // since 1 is the lexicographically smallest number). At each step,
    // we have two choices:
    //
    //   1. SKIP the entire subtree under `curr`:
    //      If the number of nodes under `curr` (including `curr` itself)
    //      is <= k, then the k-th number is NOT in this subtree. We can
    //      safely skip all of it, subtract that count from k, and move
    //      to the next sibling (curr++).
    //
    //   2. DIVE DEEPER into the subtree under `curr`:
    //      If the subtree under `curr` has MORE than k nodes, then the
    //      k-th number IS somewhere inside this subtree. We move to the
    //      first child (curr *= 10) and decrement k by 1 (since we've
    //      "consumed" the current node `curr` itself).
    //
    // This is a GREEDY approach: at each step, we either skip an entire
    // branch (if it's too small to contain the k-th number) or dive
    // deeper (if it's big enough). We never backtrack or re-explore.
    //
    // WHY THIS IS O(log n * log n):
    // - The outer while loop runs at most O(log n) times (we either
    //   increment curr or multiply by 10, and curr never exceeds n).
    // - Each call to Count() takes O(log n) time (level-by-level counting).
    // - Total: O(log n * log n), which is MUCH faster than O(n) for
    //   large n (e.g., n = 10^9).
    int findKthNumber(int n, int k) {
        int curr = 1;  // Start at the lexicographically smallest number

        // ---- ADJUST k to 0-indexed ----
        // We're already standing on the 1st number (curr = 1), so we
        // only need to find (k - 1) more numbers to reach the k-th.
        // This is like saying "I've already counted 1, so I need k-1 more."
        k -= 1;

        // ---- GREEDY NAVIGATION LOOP ----
        while (k > 0) {
            // Count how many numbers are in the subtree rooted at `curr`
            // (including `curr` itself). This tells us how many numbers
            // we'd skip if we decided to move past this entire branch.
            int count = Count(curr, curr + 1, n);

            // ---- DECISION: skip this subtree or dive deeper? ----
            if (count <= k) {
                // CASE 1: The subtree under `curr` has <= k nodes.
                // This means the k-th number is NOT in this subtree --
                // we can safely skip all of it and move to the next
                // sibling (curr++).
                //
                // We subtract `count` from k because we've effectively
                // "skipped over" all those numbers in our lexicographical
                // traversal.
                curr++;
                k -= count;  // skipping the elements under curr prefix tree
            } else {
                // CASE 2: The subtree under `curr` has > k nodes.
                // This means the k-th number IS somewhere inside this
                // subtree. We need to dive deeper to find it.
                //
                // We move to the first child (curr *= 10), which is the
                // lexicographically smallest number in this subtree
                // (e.g., from 1 we go to 10, from 10 we go to 100, etc.).
                //
                // We decrement k by 1 because we've "consumed" the current
                // node `curr` itself -- it's one step closer to our target.
                curr *= 10;
                k -= 1;
            }
        }

        // When k reaches 0, `curr` is exactly the k-th lexicographical number.
        return curr;
    }
};

/*
============================================================
REVISION SUMMARY (read this when you forget everything else)
============================================================

WHAT IS THIS PROBLEM?
Given integers n and k, return the k-th smallest number in
lexicographical (dictionary) order among all integers from 1 to n.
For example, n=13, k=2 gives 10 (since lex order is:
1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9).

ANALOGY - "Finding the k-th word in a dictionary without reading every page":
Imagine you had a dictionary of all "number-words" from "1" to "n"
sorted alphabetically, and you wanted the k-th entry. You wouldn't
read every single word from the start -- you'd flip through by
sections: "Is the k-th word in the '1' section? If yes, dive
deeper into '10', '11', etc. If no, skip the entire '1' section
and jump to '2'." This solution does exactly that, but for numbers.

THE CORE INSIGHT - "Count subtree size in O(log n) using math, not enumeration":
The "hard" part of this problem is efficiently answering: "How many
numbers start with prefix P?" For example, if n=1000 and P=1, how
many numbers are 1, 10-19, 100-199, 1000? The naive answer is to
generate them all and count -- but that's O(n) and defeats the
purpose of optimization.

The Count() function uses a mathematical trick:
- At level 1 (1-digit prefixes): numbers starting with 1 are just [1, 2) = {1} -> count = 1
- At level 2 (2-digit prefixes): numbers starting with 1 are [10, 20) = {10, 11, ..., 19} -> count = 10
- At level 3 (3-digit prefixes): numbers starting with 1 are [100, 200) = {100, 101, ..., 199} -> count = 100
- At level 4 (4-digit prefixes): numbers starting with 1 are [1000, 2000) capped at n+1 -> count = min(2000, 1001) - 1000 = 1
- Total for prefix 1: 1 + 10 + 100 + 1 = 112 numbers

This is O(log₁₀ n) because we only loop once per digit level.

DRY RUN EXAMPLE: n=13, k=2
- Start: curr=1, k=1 (after k-=1)
- Iteration 1:
  - Count(1, 2, 13):
    - Level 1: curr=1, next=2 -> count += (2-1) = 1
    - Level 2: curr=10, next=20 -> count += min(20, 14) - 10 = 14 - 10 = 4
    - Level 3: curr=100, next=200 -> curr > n, loop exits
    - Total count = 1 + 4 = 5 (numbers: 1, 10, 11, 12, 13)
  - count (5) > k (1), so we dive deeper:
    - curr *= 10 -> curr = 10
    - k -= 1 -> k = 0
- Loop exits (k=0), return curr=10.
  (Matches expected output: 2nd lex number in 1..13 is 10.)

DRY RUN EXAMPLE 2: n=13, k=5
- Start: curr=1, k=4
- Iteration 1:
  - Count(1, 2, 13) = 5 (as above)
  - count (5) <= k (4)? NO, so dive deeper:
    - curr = 10, k = 3
- Iteration 2:
  - Count(10, 11, 13):
    - Level 1: curr=10, next=11 -> count += (11-10) = 1
    - Level 2: curr=100, next=110 -> curr > n, loop exits
    - Total count = 1 (just the number 10 itself)
  - count (1) <= k (3)? YES, so skip this subtree:
    - curr++ -> curr = 11
    - k -= 1 -> k = 2
- Iteration 3:
  - Count(11, 12, 13) = 1 (just 11)
  - count (1) <= k (2)? YES, skip:
    - curr = 12, k = 1
- Iteration 4:
  - Count(12, 13, 13) = 1 (just 12)
  - count (1) <= k (1)? YES, skip:
    - curr = 13, k = 0
- Loop exits, return curr=13.
  (5th lex number in 1..13 is indeed 13: sequence is 1, 10, 11, 12, 13, ...)

TIME COMPLEXITY: O(log n * log n)
  - Outer while loop: at most O(log n) iterations (curr either
    increments or multiplies by 10, and never exceeds n).
  - Each Count() call: O(log n) iterations (level-by-level counting).
  - Total: O(log n * log n), which is extremely efficient even
    for n up to 10^9 (roughly 10 * 10 = 100 operations max).

SPACE COMPLEXITY: O(1)
  No recursion, no extra data structures -- just a few integer
  variables. This is as space-efficient as it gets.

COMMON MISTAKES WITH THIS PATTERN:
1. Forgetting to adjust k to 0-indexed (k -= 1) at the start.
   Since we begin at curr=1 (the 1st number), we need to find
   (k-1) more steps, not k steps.
2. Misunderstanding the Count() range logic: using `next = min(next, n)`
   instead of `next = min(next, n+1)`. The range [curr, next) is
   exclusive on the right, so to include n, we need next = n+1.
3. Confusing when to skip vs. dive: if count <= k, skip (move to
   next sibling); if count > k, dive (move to first child). Mixing
   these up leads to wrong answers or infinite loops.
4. Using `int` for curr/next in Count() when n can be up to 10^9.
   Multiplying by 10 can overflow a 32-bit int, so we use `long`
   (or `long long`) for curr and next to avoid overflow.

TRIGGER WORDS TO SPOT THIS PATTERN:
"k-th smallest/largest in lexicographical order," "k-th in dictionary
order," "find the k-th number without generating all" -- these
should immediately signal: prefix counting + greedy navigation in
an implicit trie. This pattern is closely related to "k-th in a
sorted structure" problems (e.g., k-th smallest in a BST, k-th
largest element in a stream) where you avoid full enumeration by
counting or ranking.

WHERE THIS PATTERN SHOWS UP:
This exact problem has been referenced in interview question banks
for Google, Amazon, and Microsoft as a test of whether a candidate
can recognize "implicit trie" structures and optimize from O(n)
to O(log n * log n) using mathematical counting. It's also a great
example of how greedy navigation + efficient counting can replace
brute-force enumeration.
============================================================
*/


