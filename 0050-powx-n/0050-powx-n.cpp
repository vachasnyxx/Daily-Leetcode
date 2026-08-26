// class Solution {
// public:
//     double myPow(double x, int n) {
//         long expo = n;
//         if (expo < 0) {
//             x = 1 / x;
//             expo = -expo;
//         }
//         return power(x,expo,1);
//     }

//     double power(double x, long n, double ans){
//         if(n == 0){
//             return ans;
//         }

//         if(n%2 != 0){
//             ans *= x;
//         }
//         return power(x*x, n/2, ans);
//     }
// };




// ============================================================================
// LeetCode 50: Pow(x, n)
// PATTERN: Recursion — Fast/Binary Exponentiation (Divide and Conquer)
// ============================================================================
//
// PROBLEM RECAP: Implement pow(x, n), which calculates x raised to the power
// n (x^n), where n can be a NEGATIVE integer, ZERO, or POSITIVE integer.
//
// THE NAIVE APPROACH (what NOT to do): Multiply x by itself n times in a
// loop. This is O(n) time. For n as large as 2^31 - 1 (int max), that's over
// 2 BILLION multiplications — way too slow for large inputs. We need
// something smarter: FAST EXPONENTIATION, which computes x^n in O(log n)
// time using a "divide the exponent in half" trick.

class Solution {
public:
    double myPow(double x, int n) {
        // ------------------------------------------------------------
        // HANDLE NEGATIVE EXPONENTS FIRST:
        // x^(-n) = 1 / (x^n). So if n is negative, we flip x to its
        // reciprocal (1/x) and flip n to positive, then compute normally.
        //
        // WHY 'long expo'? Because n is an int, and int's range is
        // [-2^31, 2^31 - 1]. If n = -2^31 (INT_MIN), then -n would OVERFLOW
        // a 32-bit int (since +2^31 is out of int's positive range). Using
        // 'long' (or long long) to store the exponent avoids this overflow
        // trap before we negate it.
        // ------------------------------------------------------------
        long expo = n;
        if (expo < 0) {
            x = 1 / x;      // flip base to reciprocal
            expo = -expo;   // now safely negate, since expo is a wider type
        }

        // Kick off the recursive fast-exponentiation helper.
        // 'ans' starts at 1 (the multiplicative identity — multiplying by
        // 1 changes nothing, so it's a safe starting accumulator).
        return power(x, expo, 1);
    }

    // ------------------------------------------------------------------
    // power(x, n, ans)
    // ------------------------------------------------------------------
    // GOAL: Compute x^n, accumulating the result into 'ans' as we go,
    //       using the "divide the exponent in half each recursive call"
    //       trick to achieve O(log n) time instead of O(n).
    //
    // THE CORE IDEA (memorize this):
    //   x^n can be broken down based on whether n is even or odd:
    //     - If n is EVEN: x^n = (x^2)^(n/2)
    // //       (e.g., x^8 = (x^2)^4 — squaring the base, halving the exponent)
    // //     - If n is ODD:  x^n = x * (x^2)^(n/2)   [integer division, so n/2
    // %                                                drops the remainder]
    // %       (e.g., x^9 = x * (x^2)^4 — pull out one factor of x first, since
    // %       9 doesn't split evenly, then handle the even remainder the same way)
    // //
    // //   Each recursive call HALVES the exponent (n -> n/2), so instead of
    // //   n recursive calls (like naive multiplication), we only need
    // //   log2(n) calls. That's the entire speedup, in one sentence.
    // ------------------------------------------------------------------
    double power(double x, long n, double ans){

        // ------------------------------------------------------------
        // BASE CASE: when the exponent hits 0, x^0 = 1, and everything
        // we've already multiplied into 'ans' IS the final answer. Return it.
        // ------------------------------------------------------------
        if(n == 0){
            return ans;
        }

        // ------------------------------------------------------------
        // ODD EXPONENT CHECK:
        // If n is odd, we can't split it evenly in half (n/2 would lose a
        // factor of x due to integer division). So we "pull out" one factor
        // of the CURRENT base x and multiply it into ans RIGHT NOW, before
        // continuing to halve the (now effectively even) remaining exponent.
        // //
        // // Example: x^9 -> ans *= x (captures the "extra" factor), then we
        // // continue recursing with x*x and n/2 = 4, which correctly computes
        // % (x^2)^4 = x^8, and combined with the ans *= x we already did, gives
        // % x * x^8 = x^9. Checks out!
        // ------------------------------------------------------------
        if(n % 2 != 0){
            ans *= x;
        }

        // ------------------------------------------------------------
        // THE RECURSIVE STEP (this is the "divide and conquer" magic):
        //   - Square the base: x becomes x*x (so x^2, ready for the next level).
        //   - Halve the exponent: n becomes n/2 (integer division, drops
        //     any remainder — but we already accounted for oddness above).
        //   - Pass 'ans' along, carrying forward whatever we've accumulated.
        //
        // This is a TAIL-RECURSIVE call (the recursive call is the LAST
        // operation, with no pending work after it returns) — which means
        // it could theoretically be converted into a simple loop without
        // changing behavior, since there's nothing left to do after the
        // recursive call returns except pass its result straight back up.
        // ------------------------------------------------------------
        return power(x*x, n/2, ans);
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: Compute x raised to the power n efficiently by repeatedly
// squaring the base and halving the exponent, instead of multiplying x by
// itself n times one by one.
//
// ANALOGY — "Doubling your money by folding, not counting":
// // Imagine you want to know the value of folding a piece of paper in half
// // n times, where each fold doubles its thickness. Instead of tracking each
// % individual LAYER one at a time (linear counting — slow), you just track
// % how many times you've FOLDED (halving your remaining folds needed each
// % time you double the thickness). To fold 8 times, you don't count to 8 one
// % by one — you can think "fold twice to get 4x thickness, do that twice more
// % to get 16x" — you're always working in halves. That's exactly what fast
// % exponentiation does: x^8 isn't "multiply by x, eight separate times" — it's
// % "square x to get x^2, square THAT to get x^4, square THAT to get x^8" —
// % just 3 squaring operations instead of 8 multiplications. This is why the
// % time drops from O(n) to O(log n): each recursive call HALVES the exponent,
// % so you only need about log2(n) calls to shrink n down to 0.
// //
// // WHY THIS IS RECURSION (divide and conquer flavor):
// %   - Each call reduces the problem (compute x^n) into a SMALLER version of
// %     the SAME problem (compute x^(n/2), but with a squared base) — this is
// %     the defining trait of divide-and-conquer recursion.
// %   - Unlike tree recursion (Fibonacci, Climbing Stairs) which branches into
// %     TWO recursive calls per invocation, this is SINGLE-BRANCH recursion —
// %     only one recursive call per invocation, making it easier to reason
// %     about and trace (no branching tree to draw, just a straight chain).
// %   - It's also TAIL RECURSIVE: the recursive call is the very last thing
// %     that happens, with no leftover computation after it returns. Some
// %     compilers can optimize tail recursion into a loop automatically
// %     (though C++ doesn't guarantee this optimization the way functional
// %     languages like Scheme do).
// //
// // DRY RUN EXAMPLE — computing 2^10:
// %   power(2, 10, 1)
// %     n=10 (even) -> ans stays 1, recurse: power(4, 5, 1)
// %   power(4, 5, 1)
// %     n=5 (odd) -> ans = 1*4 = 4, recurse: power(16, 2, 4)
// %   power(16, 2, 4)
// %     n=2 (even) -> ans stays 4, recurse: power(256, 1, 4)
// %   power(256, 1, 4)
// %     n=1 (odd) -> ans = 4*256 = 1024, recurse: power(65536, 0, 1024)
// %   power(65536, 0, 1024)
// %     n=0 -> return ans = 1024
// %   Final answer: 1024, and indeed 2^10 = 1024. Correct!
// %   Notice: only 4 recursive calls were needed instead of 10 multiplications
// %   — that's the O(log n) speedup in action.
// //
// // TRIGGER WORDS for this pattern:
// %   "compute x^n efficiently", "power function", "exponentiation" +
// %   "n can be very large (up to 2^31)" => Think: Fast/Binary Exponentiation,
// %   recursion (or iteration) that halves the exponent each step.
// //
// % GENERAL TEMPLATE (memorize this shape for ALL fast exponentiation problems):
// %   1. Handle negative exponents by flipping the base to its reciprocal and
// %      negating the exponent (watch for INT_MIN overflow — use a wider type).
// %   2. Base case: exponent == 0 returns the accumulated result (identity 1).
// %   3. If exponent is odd, multiply the accumulator by the current base
// %      ONCE (to capture the "extra" factor that doesn't split evenly).
// %   4. Recurse with base squared and exponent halved (integer division).
// %   This EXACT template also solves "fast modular exponentiation" (common in
// %   cryptography and modular arithmetic problems) — just add a "% MOD" after
// %   every multiplication to keep numbers bounded.
// //
// // COMPLEXITY:
// %   - Time: O(log n) — the exponent is halved every recursive call, so the
// %     recursion depth (and total work) is proportional to log2(n).
// %   - Space: O(log n) for the recursion call stack (each recursive call adds
// %     a stack frame). This could be converted to O(1) space with an iterative
// %     version using a while loop instead of recursion, since the recursion
// %     here is tail-recursive and has no pending work after each call.
// %   (Compare to naive O(n) multiplication loop: for n = 2^31, naive would
// %   need ~2 billion operations; fast exponentiation needs only ~31 — a
// %   MASSIVE practical speedup.)
// //
// // COMMON MISTAKES (why they happen):
// %   1. Forgetting to handle negative n — students often only handle positive
// %      exponents and crash or get wrong answers for pow(2, -3), which should
// %      be 1/8 = 0.125.
// %   2. INT_MIN overflow when negating n — if n = INT_MIN (-2147483648) and
// %      you write "n = -n" directly on an int, this OVERFLOWS because +n would
// %      exceed int's max positive value. Always widen to long/long long BEFORE
// %      negating, exactly as this code does with 'long expo = n'.
// %   3. Forgetting the odd-exponent multiply — some students only do the
// %      recursive squaring step and forget "ans *= x" for odd n, silently
// %      producing wrong answers for any odd exponent (e.g., computing x^9 as
// %      if it were x^8).
// %   4. Confusing this with LINEAR recursion — students sometimes write
// %      power(x, n) { return x * power(x, n-1); }, which is CORRECT but O(n)
// %      time, missing the entire point of "fast" exponentiation (the halving
// %      trick is what makes it fast, not just "recursion" by itself).
// //
// // COMPANIES: Fast exponentiation is a VERY common warm-up recursion/math
// % question in Amazon, Microsoft, Adobe, and Flipkart interviews — often used
// % to test whether a candidate can spot an O(n) -> O(log n) optimization via
// % divide and conquer. It pairs directly with:
// %   - Modular exponentiation problems (common in cryptography-flavored DSA
// %     questions, e.g., "compute (a^b) % m efficiently").
// %   - LC 372: Super Pow (extends this idea with modular arithmetic and large
// %     exponents represented as arrays).
// %   - Matrix exponentiation (used to solve linear recurrences like Fibonacci
// %     in O(log n) time — a more advanced extension of this exact idea).
// % Once you see "compute x^n" or "a^b mod m" with LARGE exponents, your brain
// % should immediately reach for binary/fast exponentiation — halve the
// % exponent, square the base, repeat.
// // ============================================================================










// class Solution {
// public:
//     double myPow(double x, int n) {
//         long expo = n;
//         if (expo < 0) {
//             x = 1 / x;
//             expo = -expo;
//         }

//         double ans =1;

//         while(expo > 0){
//             if(expo%2 != 0){
//                 ans *= x;
//             }

//             x *= x;
//             expo /=2;
//         }
//         return ans;
//     }
// };