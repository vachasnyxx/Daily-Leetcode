// class Solution {
// public:
//     const int M = 1e9+7;
//     int findpower(long long a , long long b){
//         if(b == 0){
//             return 1;
//         }

//         long long half = findpower(a, b /2);
//         long long result = (half * half ) % M;

//         if(b % 2 == 1){
//             result = (result * a) % M;
//         } 

//         return result;
//     }
    
//     int countGoodNumbers(long long n) {
//         return (long long)findpower(5, (n+1)/2) * findpower(4, n/2) % M;
//     }
// };



class Solution {
public:
    const int M = 1e9 + 7;  // The standard "answer might be huge" modulus.
                             // Whenever a problem says "return answer mod 1e9+7,"
                             // that's your signal: the true answer is astronomically
                             // large (exponential), so we must reduce at every
                             // multiplication step to avoid overflow.

    // FAST (BINARY) EXPONENTIATION — computes (a^b) % M in O(log b) time
    // instead of the naive O(b) time of multiplying 'a' by itself b times.
    //
    // CORE IDEA: a^b = (a^(b/2))^2       when b is even
    //            a^b = (a^(b/2))^2 * a   when b is odd
    // Each recursive call HALVES the exponent, so instead of b multiplications,
    // you only ever do about log2(b) of them.
    int findpower(long long a, long long b) {

        // BASE CASE: anything to the power 0 is 1.
        if (b == 0) {
            return 1;
        }

        // Recurse on HALF the exponent (integer division automatically
        // floors, which is exactly what we want for both even and odd b).
        long long half = findpower(a, b / 2);

        // Squaring the half-result reconstructs a^(2*(b/2)).
        // If b is even, 2*(b/2) == b exactly, so we're done.
        // If b is odd, 2*(b/2) == b-1, so we're short by one factor of 'a'.
        long long result = (half * half) % M;

        // Patch the "short by one factor of a" gap when b was odd.
        if (b % 2 == 1) {
            result = (result * a) % M;
        }

        return result;
    }

    int countGoodNumbers(long long n) {
        // COUNTING SETUP (this is the real "aha" of the problem, separate
        // from the fast-power trick):
        // A "good number" is a digit string where:
        //   - every EVEN index (0, 2, 4, ...) holds an EVEN digit
        //     → 5 valid choices: {0, 2, 4, 6, 8}
        //   - every ODD index (1, 3, 5, ...) holds a PRIME digit
        //     → 4 valid choices: {2, 3, 5, 7}
        //
        // In a string of length n (0-indexed):
        //   number of even indices = ceil(n / 2) = (n + 1) / 2
        //   number of odd indices  = floor(n / 2) = n / 2
        //
        // By the multiplication principle (each position's choice is
        // independent of every other position's choice), the total count is:
        //   5^(even index count) * 4^(odd index count)
        //
        // We compute each factor with fast exponentiation (since n can be
        // up to 10^15, a naive loop would never finish), then combine mod M.
        return (long long)findpower(5, (n + 1) / 2) * findpower(4, n / 2) % M;
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Count how many digit-strings of length n are "good" (even digit at every even
index, prime digit at every odd index), returned modulo 1e9+7.

ANALOGY — "Folding a giant sheet of paper in half, again and again":
Computing a^b the naive way is like measuring a giant field one footstep at
a time — b steps, painfully slow if b is a billion. Fast exponentiation is
like folding a huge stack of paper in half repeatedly: after just ~30 folds,
you've effectively "covered" over a billion units, because each fold DOUBLES
your coverage instead of adding one unit at a time. That's why the recursion
uses b/2 — it's folding the exponent in half every single call, turning a
problem that would take a billion steps into one that takes about 30.

WHY TWO SEPARATE POWER CALLS (5^x and 4^y) INSTEAD OF ONE:
The digit-string alternates between two independent "rulebooks" — even
positions follow the "must be even digit" rule (5 options), odd positions
follow the "must be prime digit" rule (4 options). Since these choices don't
interact with each other, you count each family of positions separately as
its own power, then multiply the two counts together (multiplication
principle — same logic as "if you have 3 shirts and 4 pants, you have 3*4
outfits").

DRY RUN (tiny example, n = 4):
Even index count = (4+1)/2 = 2   (indices 0, 2)
Odd index count  = 4/2 = 2       (indices 1, 3)
Answer = 5^2 * 4^2 = 25 * 16 = 400

Now trace findpower(5, 2) to see the halving in action:
  findpower(5, 2):
    half = findpower(5, 1)
      half = findpower(5, 0) = 1                (base case)
      result = (1 * 1) % M = 1
      b=1 is odd → result = (1 * 5) % M = 5
      returns 5
    half = 5
    result = (5 * 5) % M = 25
    b=2 is even → no extra multiply
    returns 25                                   ✓ matches 5^2 = 25

TIME COMPLEXITY: O(log n) per findpower call, since the exponent halves each
recursive step — two calls total, so still O(log n) overall.
SPACE COMPLEXITY: O(log n) for the recursion call stack depth (each halving
step is one stack frame).

TRIGGER WORDS for this pattern:
- "n can be up to 10^9 / 10^15" combined with "return answer mod 1e9+7" →
  scream "fast exponentiation," because a naive loop of that many iterations
  will always TLE (time limit exceeded).
- "count the number of valid X of length n satisfying position-based rules"
  → alternating/independent position constraints → multiplication principle,
  split into separate counts per position-type, then combine.

COMMON MISTAKES:
1. Forgetting to apply "% M" after EVERY multiplication (not just the final
   answer) — even with `long long`, intermediate products of two numbers each
   near 10^9 can overflow or at least drift out of the range you expect,
   corrupting the whole computation.
2. Swapping which digit set (even digits vs. prime digits) goes with which
   index parity — a classic off-by-one/off-by-category slip. Always
   sanity-check with n=1: only index 0 exists (even index), so the answer
   must be exactly 5, not 4.
3. Forgetting the base case check `b == 0` returns 1, not 0 — without it, the
   recursion either infinite-loops or silently returns a wrong power of zero.

WHERE THIS SHOWS UP:
Fast/binary exponentiation itself is one of the most universally tested
low-level techniques — it shows up disguised inside harder problems at
Google and Amazon (matrix exponentiation for counting problems, modular
inverse for combinatorics-heavy questions). This specific problem (LC 1922)
is commonly used in OA (online assessment) rounds to check whether you
instinctively reach for binary exponentiation the moment you see a huge
exponent with a modulo requirement, rather than writing a doomed O(n) loop.
================================================================================
*/