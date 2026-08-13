// class Solution {
// public:
//     bool validPalindrome(string s) {
//         int left = 0;
//         int right = s.size() - 1;
//         while (left < right) {
//             if (s[left] != s[right]) {
//                 return isPalindrome(s, left + 1, right) ||
//                        isPalindrome(s, left, right - 1);
//             }
//             left++;
//             right--;
//         }
//         return true;
//     }

// private:
//     bool isPalindrome(string& s, int left, int right) {
//         while (left < right) {
//             if (s[left] != s[right]) {
//                 return false;
//             }
//             left++;
//             right--;
//         }
//         return true;
//     }
// };





// ============================================================
// LEETCODE 680 - VALID PALINDROME II
// Pattern: TWO POINTERS (converging) + "greedy one-mistake-allowed" twist
// ============================================================
//
// PROBLEM IN PLAIN ENGLISH:
// You're given a string. You're allowed to delete AT MOST ONE
// character from it. After that one optional deletion, can the
// string become a palindrome?

class Solution {
public:
    bool validPalindrome(string s) {

        int left = 0;
        int right = s.size() - 1;

        // -----------------------------------------------------------
        // Same converging two-pointer walk as Valid Palindrome I.
        // We move inward comparing mirrored characters, EXACTLY like
        // before, as long as they keep matching.
        // -----------------------------------------------------------
        while (left < right) {

            if (s[left] != s[right]) {

                // ---------------------------------------------------
                // THE KEY NEW IDEA (this is what makes it "II"):
                // The moment we hit our FIRST mismatch, we are not
                // allowed to just say "false" like in Palindrome I.
                // We get ONE free deletion. So we ask:
                //
                //   "What if I deleted the LEFT character?"
                //     -> then the rest of the string must already be
                //        a palindrome from (left+1) to (right).
                //
                //   "What if I deleted the RIGHT character instead?"
                //     -> then the rest of the string must already be
                //        a palindrome from (left) to (right-1).
                //
                // NOTE THE DIRECTION: both recursive checks shrink
                // the window by exactly ONE position. We NEVER grow
                // the window bigger — that would mean "un-deleting"
                // something, which makes no sense. This is the exact
                // spot where a common bug creeps in: writing
                // (left, right+1) instead of (left, right-1). Always
                // double check: deleting a character means the new
                // window is SMALLER than before, never bigger.
                //
                // We only need ONE of these two options to work
                // (that's why it's ||, logical OR) — we're allowed
                // only one deletion total, and we're testing both
                // possible places to spend it.
                // ---------------------------------------------------
                return isPalindrome(s, left + 1, right) ||
                       isPalindrome(s, left, right - 1);
                //                              ^^^^^^^
                //  CORRECTED: this must shrink the window (right-1),
                //  not grow it (right+1). Growing it reads memory
                //  past the end of the string once right was already
                //  at s.size()-1 -> undefined behavior / crash risk.
            }

            // Characters matched, so far still looking good, keep
            // converging inward exactly like Palindrome I.
            left++;
            right--;
        }

        // -----------------------------------------------------------
        // If we NEVER hit a mismatch, the string was ALREADY a
        // palindrome with zero deletions needed. Trivially valid.
        // -----------------------------------------------------------
        return true;
    }

private:
    // -----------------------------------------------------------
    // This is just the PLAIN Valid Palindrome I checker (no
    // deletions allowed here) — used as a helper to verify
    // "is everything from left to right already symmetric?"
    // once we've committed to a specific deletion choice.
    // -----------------------------------------------------------
    bool isPalindrome(string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false; // still a mismatch even after deleting -> give up on this branch
            }
            left++;
            right--;
        }
        return true;
    }
};

// ============================================================
// ============ REVISION SUMMARY (READ THIS FIRST) ============
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// Walk two pointers inward like normal palindrome checking. The
// FIRST time you find a mismatch, you get exactly one "free pass"
// -- try skipping the left character OR skipping the right
// character, and see if either choice makes the rest symmetric.
//
// ANALOGY (different from Valid Palindrome I's analogies):
// Imagine you're proofreading a sentence for a typo that would ruin
// its symmetry, and your editor says "you're allowed to cross out
// ONE word, pick wisely." The moment you spot the first place where
// the sentence stops mirroring itself, you have two candidate words
// to cross out: the one on the left side of the clash, or the one
// on the right side of the clash. You try crossing out each one
// separately and check if EITHER choice fixes the whole sentence.
// If YES to either -- you win. If NO to both -- no single crossed-out
// word can save this sentence.
//
// STEP-BY-STEP DRY RUN on s = "abcdcbea" (8 chars)
//
//   index:  0   1   2   3   4   5   6   7
//   char:   a   b   c   d   c   b   e   a
//
//   left=0(a), right=7(a) -> match, left=1, right=6
//   left=1(b), right=6(e) -> MISMATCH!
//
//     Try deleting LEFT (index1='b'):
//       check isPalindrome(s, 2, 6) -> substring "cdcbe"
//       left=2(c),right=6(e) -> mismatch -> return false
//
//     Try deleting RIGHT (index6='e'):
//       check isPalindrome(s, 1, 5) -> substring "bcdcb"
//       left=1(b),right=5(b) -> match, left=2,right=4
//       left=2(c),right=4(c) -> match, left=3,right=3 -> stop, true!
//
//   Since option2 (delete right) returned true, overall answer: TRUE.
//   (Deleting the 'e' at index 6 turns "abcdcbea" into "abcdcba",
//    which IS a palindrome.)
//
// TIME COMPLEXITY: O(n)
//   The main loop walks inward at most n/2 times. The moment we hit
//   a mismatch, we call the helper TWICE, but each helper call scans
//   AT MOST the remaining unscanned portion of the string once. So
//   total work across the main loop + both helper calls is still
//   bounded by O(n) -- we never rescan the same successfully-matched
//   outer pairs.
//
// SPACE COMPLEXITY: O(1)
//   Just a handful of integer pointers, no new strings, no arrays.
//   Recursion isn't used here either (isPalindrome is a plain loop,
//   not a recursive call), so there's no extra call-stack space to
//   worry about beyond the fixed helper frame.
//
// COMMON MISTAKES STUDENTS MAKE:
// 1. THE BUG YOU JUST WROTE: writing (left, right+1) instead of
//    (left, right-1) for the "delete right character" branch.
//    Rule of thumb: deleting a character always SHRINKS the window.
//    If your window is growing after a "deletion," something's wrong.
//
// 2. Calling isPalindrome on BOTH branches even when the first one
//    already returns true (should short-circuit with ||, which C++
//    does automatically -- but some students manually check both and
//    then OR the booleans together, which does unnecessary work).
//
// 3. Forgetting that you only get to use your "one deletion" ONCE.
//    A common wrong instinct is to try to keep deleting on every
//    subsequent mismatch too -- but once you've branched into
//    isPalindrome() (the plain helper), there's no more deletion
//    budget left; any mismatch found inside it is a hard "false."
//
// 4. Confusing this with something requiring DP or recursion with
//    memoization. It doesn't need either -- it's a normal two-pointer
//    scan that, upon ONE special event (first mismatch), branches
//    into two plain O(n) checks. Total work stays linear.
//
// TRIGGER WORDS THAT SHOULD MAKE YOU THINK "TWO POINTERS + ONE
// SKIP/DELETE ALLOWED":
//   - "at most one deletion / removal / change"
//   - "almost a palindrome"
//   - "can become a palindrome after removing exactly one character"
//
// COMPANIES THAT COMMONLY ASK THIS:
//   Facebook/Meta (very frequently -- it's one of their signature
//   "looks easy, has a subtle edge case" interview questions),
//   Amazon, Bloomberg.
// ============================================================

