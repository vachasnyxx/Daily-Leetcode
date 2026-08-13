// class Solution {
// public:
//     bool isPalindrome(string s) {
//         int n = s.size();
//         int left = 0;
//         int right = n - 1;

//         while (left < right) {

//             if (!isalnum(s[left])) {
//                 left++;
//             } else if (!isalnum(s[right])) {
//                 right--;
//             } else {
//                 if (tolower(s[left]) != tolower(s[right])) {
//                     return false;
//                 }
//                 left++;
//                 right--;
//             }
//         }
//         return true;
//     }
// };

// ============================================================
// LEETCODE 125 - VALID PALINDROME
// Pattern: TWO POINTERS (converging pointers from both ends)
// ============================================================

class Solution {
public:
    bool isPalindrome(string s) {

        int n = s.size();

        // -----------------------------------------------------------
        // INTUITION FOR TWO POINTERS HERE:
        // A palindrome reads the same forwards and backwards.
        // Instead of building a NEW cleaned string (extra O(n) space)
        // and then comparing it to its reverse, we can check
        // "mirror positions" directly on the ORIGINAL string.
        //
        // Think of it like two people starting at opposite ends of
        // a bookshelf and walking towards each other, checking if
        // the book at their current position matches the other
        // person's book. The moment they disagree -> not a match.
        // If they meet in the middle without disagreeing -> it's a match.
        //
        // This is the classic "converging pointers" version of the
        // two-pointer pattern (as opposed to the "same direction,
        // different speed" version used in things like removing
        // duplicates or fast/slow pointer cycle detection).
        // -----------------------------------------------------------

        int left = 0;       // pointer starting from the FRONT of the string
        int right = n - 1;  // pointer starting from the BACK of the string

        // -----------------------------------------------------------
        // WHY left < right and not left <= right?
        // If left == right, both pointers are on the SAME character
        // (the middle character in an odd-length string). A single
        // character always matches itself, so there's nothing to
        // compare -> loop can safely stop.
        // -----------------------------------------------------------
        while (left < right) {

            // ---------------------------------------------------
            // STEP 1: Skip non-alphanumeric characters.
            // The problem says we should IGNORE spaces, punctuation,
            // symbols etc. and only compare letters/digits.
            //
            // isalnum(c) returns true if c is a letter (a-z, A-Z)
            // or a digit (0-9).
            //
            // If s[left] is NOT alphanumeric (e.g. ',', ' ', '!'),
            // it's "junk" from the perspective of a palindrome check,
            // so we just slide 'left' one step to the right and
            // re-check on the next loop iteration WITHOUT comparing
            // anything yet.
            // ---------------------------------------------------
            if (!isalnum(s[left])) {
                left++;
            }

            // Same idea but from the other side: if s[right] is junk,
            // slide 'right' one step to the LEFT (towards left pointer).
            else if (!isalnum(s[right])) {
                right--;
            }

            // ---------------------------------------------------
            // STEP 2: Both s[left] and s[right] are valid
            // alphanumeric characters at this point, so now we
            // actually COMPARE them.
            //
            // tolower() is used because the palindrome check should
            // be CASE-INSENSITIVE ('A' should equal 'a').
            // ---------------------------------------------------
            else {
                if (tolower(s[left]) != tolower(s[right])) {
                    // Mismatch found -> the moment two mirrored
                    // characters disagree, the string CANNOT be a
                    // palindrome. No need to check anything else,
                    // so we exit immediately (early termination,
                    // this is what keeps two-pointer solutions fast).
                    return false;
                }

                // Characters matched! Move BOTH pointers inward,
                // one step closer to the center, and continue
                // checking the next mirrored pair.
                left++;
                right--;
            }
        }

        // -----------------------------------------------------------
        // If we exit the while loop naturally (without hitting the
        // early "return false"), it means left and right pointers
        // crossed or met WITHOUT ever finding a mismatch.
        // That means every mirrored pair matched -> valid palindrome.
        // -----------------------------------------------------------
        return true;
    }
};

// ============================================================
// ============ REVISION SUMMARY (READ THIS FIRST) ============
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// Two pointers start at the two opposite ends of the string and
// walk towards each other, comparing characters as they go, while
// skipping over any character that isn't a letter or digit.
//
// ANALOGY (for permanent memory):
// Picture two friends standing at opposite ends of a long hallway
// lined with picture frames (some frames are empty - those are your
// punctuation/spaces). Both friends start walking toward the middle.
// Whenever a friend reaches an EMPTY frame, they just skip past it
// without saying anything. Whenever BOTH friends are standing in
// front of a REAL picture, they shout out what they see. If their
// shouts ever disagree -> the hallway isn't symmetric -> NOT a
// palindrome. If they meet in the middle (or cross paths) without
// ever disagreeing -> the hallway IS symmetric -> IS a palindrome.
//
// STEP-BY-STEP DRY RUN on a tiny example: s = "a,b:c c-b,a"
// (After removing junk mentally, this is "abccba")
//
//   index:  0   1   2   3   4   5   6   7   8   9  10
//   char:   a   ,   b   :   c       c   -   b   ,   a
//
//   left=0 (a), right=10 (a)          -> both alnum, 'a'=='a' -> match
//                                          left=1, right=9
//   left=1 (,)  -> not alnum          -> left=2
//   left=2 (b), right=9 (,)  -> right not alnum -> right=8
//   left=2 (b), right=8 (b)           -> both alnum, 'b'=='b' -> match
//                                          left=3, right=7
//   left=3 (:)  -> not alnum          -> left=4
//   left=4 (c), right=7 (-)  -> right not alnum -> right=6
//   left=4 (c), right=6 (c)           -> both alnum, 'c'=='c' -> match
//                                          left=5, right=5
//   left==right (5) -> loop condition left<right fails -> STOP
//
//   Result: true (valid palindrome) -- notice we never built any
//   new string, we just walked inward on the original one.
//
// TIME COMPLEXITY: O(n)
//   Each character is visited AT MOST ONCE by either the left or
//   right pointer combined. The two pointers together sweep across
//   the string exactly once, never revisiting a position, so the
//   total work is linear in string length.
//
// SPACE COMPLEXITY: O(1)
//   We only use two integer variables (left, right) regardless of
//   input size -- no new string, no array, no recursion stack.
//   This is the BIG win of two pointers over the "clean the string
//   then reverse and compare" approach, which costs O(n) extra space.
//
// COMMON MISTAKES STUDENTS MAKE:
// 1. Using "while (left <= right)" instead of "left < right".
//    This can cause you to compare the middle character with itself
//    unnecessarily -- harmless here since it always matches, but it
//    signals a shaky mental model of WHY the loop should stop early.
//
// 2. Forgetting tolower() and treating 'A' and 'a' as different
//    characters, causing valid palindromes to be wrongly rejected.
//
// 3. Using "if / if / if" (three separate if statements) instead of
//    "if / else if / else". Without the else-if chaining, after
//    skipping a junk character with left++, the code might ALSO try
//    to evaluate the comparison in the same iteration using a stale
//    right pointer, leading to subtle bugs. The else-if ensures only
//    ONE action happens per loop iteration.
//
// 4. Not realizing this is "converging two pointers" and confusing
//    it with "same-direction two pointers" (like in remove duplicates
//    from sorted array). Converging pointers move TOWARD each other;
//    same-direction pointers move in the SAME direction at different
//    speeds. Different trigger, different pattern.
//
// TRIGGER WORDS THAT SHOULD MAKE YOU THINK "TWO POINTERS (CONVERGING)":
//   - "palindrome"
//   - "reverse and compare"
//   - "check symmetry"
//   - "ignore case / ignore non-alphanumeric characters"
//   - Any problem asking you to compare a string/array to its
//     mirror image without extra space.
//
// COMPANIES THAT COMMONLY ASK PALINDROME + TWO POINTER VARIANTS:
//   Amazon, Microsoft, Facebook/Meta, Bloomberg -- often as a warm-up
//   question before a harder follow-up like "Valid Palindrome II"
//   (LeetCode 680, where you're allowed to delete ONE character).
// ============================================================