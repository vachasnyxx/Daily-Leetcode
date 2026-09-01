// class Solution {
// public:
//     char kthCharacter(int k) {
//         int shift = __builtin_popcount(k-1);

//         return 'a' + shift;
//     }
// };



// ============================================================
// Problem: K-th Character in a Recursively Doubled String
// (Variant where EVERY expansion step applies operation type 1:
//  shift each character by +1, wrapping z->a)
// Pattern: BIT MANIPULATION INSIGHT (popcount = number of set bits)
// Difficulty: Medium (but the solution is deceptively short once
// you see the binary pattern)
// ============================================================

class Solution {
public:

    // ------------------------------------------------------------
    // kthCharacter(k)
    // Returns: the k-th character (1-indexed) in a string that
    // starts as "a" and doubles at each step, where the second
    // half is ALWAYS a shifted copy (+1 to each char, z->a) of
    // the first half.
    // ------------------------------------------------------------
    //
    // CORE INTUITION -- "Every position k has a binary fingerprint":
    // Let's trace how the string grows:
    //   Step 0: "a"                           (length 1)
    //   Step 1: "ab"                          (length 2, second half = first half + 1)
    //   Step 2: "abbc"                        (length 4, second half = first half + 1)
    //   Step 3: "abbcbccd"                    (length 8, second half = first half + 1)
    //   Step 4: "abbcbccdbccddeccf"           (length 16, ...)
    //
    // Now let's look at the character at each position k (1-indexed)
    // and see how many shifts it underwent to become what it is:
    //   k=1: 'a' (0 shifts from base 'a')
    //   k=2: 'b' (1 shift: was 'a' at step 1, then shifted once)
    //   k=3: 'b' (1 shift: was 'a' at step 2, then shifted once)
    //   k=4: 'c' (2 shifts: was 'a' at step 2, shifted at step 2, then shifted again at step 3)
    //   k=5: 'b' (1 shift)
    //   k=6: 'c' (2 shifts)
    //   k=7: 'c' (2 shifts)
    //   k=8: 'd' (3 shifts)
    //
    // THE PATTERN: The number of shifts for position k equals the
    // number of 1-bits (popcount) in the binary representation of (k-1).
    //
    // WHY (k-1) and not k?
    // Because positions are 1-indexed, but binary representations
    // are naturally 0-indexed. Position k=1 corresponds to index 0
    // in 0-indexed terms, k=2 corresponds to index 1, etc. So we
    // use (k-1) to align with 0-indexed binary counting.
    //
    // WHY DOES POPCOUNT WORK?
    // Each bit set to 1 in (k-1)'s binary form represents a step
    // where position k was in the SECOND HALF of the doubling string,
    // meaning it got shifted by +1 at that step. Each bit set to 0
    // means it was in the FIRST HALF (no shift at that step).
    //
    // Example: k=8 (1-indexed) -> k-1=7 (0-indexed) -> binary: 111
    //   - Bit 0 (rightmost) = 1: at step 1, position 8 was in second half -> +1 shift
    //   - Bit 1 = 1: at step 2, position 8 was in second half -> +1 shift
    //   - Bit 2 = 1: at step 3, position 8 was in second half -> +1 shift
    //   Total shifts: 3, so character = 'a' + 3 = 'd' (matches our trace above)
    //
    // Example: k=5 (1-indexed) -> k-1=4 (0-indexed) -> binary: 100
    //   - Bit 0 = 0: at step 1, position 5 was in first half -> no shift
    //   - Bit 1 = 0: at step 2, position 5 was in first half -> no shift
    //   - Bit 2 = 1: at step 3, position 5 was in second half -> +1 shift
    //   Total shifts: 1, so character = 'a' + 1 = 'b' (matches our trace)
    //
    // This is why the solution is just: return 'a' + popcount(k-1)
    char kthCharacter(int k) {

        // ---- COUNT THE NUMBER OF SHIFTS ----
        // __builtin_popcount(x) is a GCC/Clang built-in that returns
        // the number of 1-bits (set bits) in the binary representation
        // of x. This is also called the "Hamming weight" or "population
        // count" of x.
        //
        // For this problem:
        //   - k-1 converts from 1-indexed to 0-indexed position
        //   - popcount(k-1) counts how many times position k was in
        //     the second half during the doubling process
        //   - Each such occurrence means +1 shift from the base 'a'
        int shift = __builtin_popcount(k - 1);

        // ---- RETURN THE CHARACTER ----
        // Starting from 'a', we add the total number of shifts to get
        // the final character. Since the problem guarantees k is small
        // enough that we never wrap around the alphabet (or if we do,
        // it's handled by the problem constraints), we don't need
        // explicit modulo 26 here.
        return 'a' + shift;
    }
};

/*
============================================================
REVISION SUMMARY (read this when you forget everything else)
============================================================

WHAT IS THIS PROBLEM?
Start with string "a". At each step, double the string: the first
half is a copy of the current string, and the second half is a
SHIFTED copy (+1 to each character, z->a) of the first half.
Given k (1-indexed), return the k-th character in the infinite
string after infinitely many steps (or equivalently, after enough
steps to include position k).

ANALOGY - "Binary representation as a shift counter":
Imagine each position k has a "shift counter" that starts at 0.
Every time the string doubles, if position k lands in the second
half, its counter increments by 1 (because it got shifted). If it
lands in the first half, the counter stays the same. After all
doubling steps, the counter tells you how many shifts from 'a'
the character at position k underwent.

The brilliant insight: this counter is EXACTLY the number of 1-bits
in the binary representation of (k-1). Why? Because each bit in
(k-1)'s binary form corresponds to a doubling step, and a bit set
to 1 means "position k was in the second half at this step" (i.e.,
got shifted), while a bit set to 0 means "position k was in the
first half" (no shift).

THE CORE INSIGHT - "Position k's ancestry is encoded in binary":
Let's trace position k=8 (1-indexed) through the doubling steps:
  Step 0: String = "a" (length 1)
  Step 1: String = "ab" (length 2)
    - Position 8 doesn't exist yet (length < 8)
  Step 2: String = "abbc" (length 4)
    - Position 8 still doesn't exist
  Step 3: String = "abbcbccd" (length 8)
    - Position 8 now exists! It's the last character 'd'.
    - How did it get there?
      - At step 1: position 8 would be in second half (if it existed) -> +1
      - At step 2: position 8 would be in second half -> +1
      - At step 3: position 8 is in second half -> +1
      - Total shifts: 3, so 'a' + 3 = 'd'

Now look at k-1 = 7 in binary: 111 (three 1-bits). Popcount = 3.
Matches exactly!

DRY RUN EXAMPLE: k = 8
- k-1 = 7
- Binary of 7: 111 (three 1-bits)
- popcount(7) = 3
- Return 'a' + 3 = 'd'
  (Matches our manual trace: 8th character is 'd')

DRY RUN EXAMPLE: k = 5
- k-1 = 4
- Binary of 4: 100 (one 1-bit)
- popcount(4) = 1
- Return 'a' + 1 = 'b'
  (Matches manual trace: 5th character is 'b')

DRY RUN EXAMPLE: k = 1
- k-1 = 0
- Binary of 0: 0 (zero 1-bits)
- popcount(0) = 0
- Return 'a' + 0 = 'a'
  (Base case: 1st character is always 'a')

TIME COMPLEXITY: O(1) (or O(log k) depending on how you count)
  - __builtin_popcount is typically implemented as a single CPU
    instruction (e.g., POPCNT on x86), so it's effectively O(1).
  - Even if implemented in software, it's O(number of bits) = O(log k),
    which is still extremely fast (at most ~30 iterations for k up
    to 2^30).

SPACE COMPLEXITY: O(1)
  No recursion, no extra data structures — just a single integer
  operation. This is as efficient as it gets.

COMMON MISTAKES WITH THIS PATTERN:
1. Forgetting to use (k-1) instead of k. Since positions are
   1-indexed but binary counting is naturally 0-indexed, using k
   directly would give the wrong popcount (off by one in the
   binary representation).
2. Assuming the shift wraps around the alphabet (z->a). The
   problem typically guarantees k is small enough that 'a' + shift
   never exceeds 'z', or the problem statement explicitly handles
   wrapping. If wrapping is needed, you'd use: 'a' + (shift % 26).
3. Not recognizing when this pattern applies. The key trigger is
   "string doubles at each step with a consistent transformation"
   (especially shift-by-1). If the transformation varies by step
   (like in the previous problem with operations[]), you can't
   use popcount — you need the recursive unwinding approach.

TRIGGER WORDS TO SPOT THIS PATTERN:
"k-th character in doubled string," "string grows by doubling,"
"each step appends shifted copy," "find character without building
string" — AND the transformation is ALWAYS the same (e.g., always
+1 shift, not varying by step). If the transformation varies,
this popcount trick doesn't work.

WHERE THIS PATTERN SHOWS UP:
This exact problem (or close variants) has appeared in Codeforces
rounds, AtCoder contests, and LeetCode weekly contests as a
"bit manipulation insight" problem. It's a great example of how
recognizing a binary pattern can reduce an apparently complex
recursive structure to a one-liner.
============================================================
*/