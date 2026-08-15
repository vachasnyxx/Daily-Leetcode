// class Solution {
// public:
//     bool solve(string &s, int i, int j) {
//         if (i >= j) return true;

//         if (s[i] == s[j]) {
//             return solve(s, i + 1, j - 1);
//         } else {
//             return false;
//         }
//     }

//     string longestPalindrome(string s) {
//         int n = s.size();
//         int maxlen = 0;
//         int sp = 0;

//         for (int i = 0; i < n; i++) {
//             for (int j = i; j < n; j++) {
//                 if (solve(s, i, j)) {
//                     if (j - i + 1 > maxlen) {
//                         maxlen = j - i + 1;
//                         sp = i;
//                     }
//                 }
//             }
//         }
//         return s.substr(sp, maxlen);
//     }
// };

// class Solution {
// public:
//     string longestPalindrome(string s) {
//         int n = s.size();
//         int start = 0;
//         int end = 0;

//         for (int i = 0; i < n; i++) {
//             int len1 = expand(s, i, i);
//             int len2 = expand(s, i, i + 1);
//             int len = max(len1, len2);

//             if (len > (end - start)) {
//                 start = i - (len - 1) / 2;
//                 end = i + len / 2;
//             }
//         }

//         return s.substr(start, end - start + 1);
//     }

//     int expand(string& s, int left, int right) {
//         while (left >= 0 && right < s.size() && s[left] == s[right]) {
//             left--;
//             right++;
//         }
//         return right - left - 1;
//     }
// };

// ============================================================
// LEETCODE 5 - LONGEST PALINDROMIC SUBSTRING
// Pattern: EXPAND AROUND CENTER (two-pointer family, but pointers
//          start TOGETHER at a center and move APART, instead of
//          starting apart and converging)
// ============================================================

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        int start = 0;  // left edge of best palindrome found so far
        int end = 0;    // right edge of best palindrome found so far
        // NOTE: start=0, end=0 as init means "the single first
        // character" is our starting assumption for best answer,
        // since ANY single character is trivially a palindrome
        // of length 1.

        // ---------------------------------------------------------
        // Try EVERY index as a potential "center" of a palindrome.
        // There are two kinds of centers to check at each index i:
        //   1) ODD-length center: single character at i
        //      e.g. "aba" is centered ON the 'b'
        //   2) EVEN-length center: the gap BETWEEN i and i+1
        //      e.g. "abba" is centered BETWEEN the two 'b's
        // We must check BOTH types at every index, otherwise we'd
        // miss all even-length palindromes.
        // ---------------------------------------------------------
        for (int i = 0; i < n; i++) {

            int len1 = expand(s, i, i);      // odd-length palindrome centered at i
            int len2 = expand(s, i, i + 1);  // even-length palindrome centered between i and i+1
            int len = max(len1, len2);       // best palindrome centered at/around i

            // -------------------------------------------------
            // Is this palindrome bigger than our best so far?
            // (end - start) is the length-1 of our current best
            // window, so we compare len against that.
            // -------------------------------------------------
            if (len > (end - start)) {

                // -------------------------------------------------
                // Convert "length centered at i" into actual
                // [start, end] indices in the original string.
                //
                // Why (len - 1) / 2 for start?
                // If len is ODD (say 3), the center IS at i, so we
                // need to step back (len-1)/2 = 1 position to the left.
                //
                // If len is EVEN (say 4), there's no single center
                // character -- but because of HOW expand(s, i, i+1)
                // measures length relative to i, this same formula
                // still lands on the correct left edge. Trust the
                // arithmetic here; it's been proven correct, but if
                // you want to convince yourself, trace it by hand
                // once with a len=4 example.
                //
                // Why i + len / 2 for end?
                // Symmetric reasoning on the right side, using
                // integer division (which rounds down) instead of
                // (len-1)/2.
                // -------------------------------------------------
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }
        }

        // Extract the actual substring using the winning window.
        // substr(start, length) needs a LENGTH not an end index,
        // so we compute (end - start + 1) to get the count of
        // characters in the window.
        return s.substr(start, end - start + 1);
    }

    // ---------------------------------------------------------
    // THE CORE ENGINE: given a starting pair (left, right),
    // keep expanding outward (left--, right++) as long as:
    //   1) both indices are still inside the string bounds, AND
    //   2) the characters at those positions still match.
    //
    // This is the "opposite direction" two-pointer move compared
    // to Valid Palindrome: there, pointers started FAR APART and
    // moved TOWARD each other. Here, pointers start TOGETHER (or
    // one apart) and move AWAY from each other. Same family,
    // mirrored direction.
    //
    // Called TWICE per index i:
    //   expand(s, i, i)   -> checks odd-length palindromes
    //   expand(s, i, i+1) -> checks even-length palindromes
    // ---------------------------------------------------------
    int expand(string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        // Loop stops the MOMENT characters stop matching (or we
        // hit a string boundary). At this point, left and right
        // have gone ONE STEP TOO FAR (they point past the actual
        // palindrome's edges), so the true palindrome length is
        // (right - 1) - (left + 1) + 1, which simplifies to:
        return right - left - 1;
    }
};

// ============================================================
// ============ REVISION SUMMARY (READ THIS FIRST) ============
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// Try every position (and every gap between positions) in the
// string as a potential "center," and grow outward from each one
// as long as both sides keep mirroring each other. Keep track of
// the biggest mirror-match you ever find.
//
// ANALOGY:
// Drop a pebble into a pond at every single spot along a straight
// riverbank -- including the spots BETWEEN stones, not just on top
// of them. Each pebble creates a ripple expanding outward in both
// directions. The ripple keeps growing as long as the riverbank on
// its left mirrors the riverbank on its right. The instant they stop
// mirroring, that ripple freezes at its current size. After dropping
// a pebble EVERYWHERE, you remember whichever ripple grew the
// biggest -- that's your longest palindrome.
//
// STEP-BY-STEP DRY RUN on s = "babad" (traced from actual execution):
//
//   i=0 'b': odd-len=1, even-len=0 -> best=1 -> window="b"      (updated)
//   i=1 'a': odd-len=3, even-len=0 -> best=3 -> window="bab"    (updated)
//   i=2 'b': odd-len=3, even-len=0 -> best=3 -> window="aba"    (updated, tie recalculated at new center)
//   i=3 'a': odd-len=1, even-len=0 -> best=1 -> NOT > 3, no update
//   i=4 'd': odd-len=1, even-len=0 -> best=1 -> NOT > 3, no update
//
//   Final window: "aba" (length 3). Note "bab" from i=1 was equally
//   valid -- LeetCode accepts any correct longest palindrome, ties
//   are fine.
//
// TIME COMPLEXITY: O(n^2)
//   There are n possible centers (plus n "gap" centers, still O(n)
//   total). For EACH center, expand() can walk outward up to O(n)
//   steps in the worst case (e.g. a string of all identical
//   characters like "aaaaaaa", where every expansion goes all the
//   way to the string's edges). n centers x O(n) worst-case expansion
//   each = O(n^2) total.
//
// SPACE COMPLEXITY: O(1)
//   Only a few integers (start, end, left, right) are tracked. The
//   final substr() call to build the answer string doesn't count
//   against the algorithm's extra working space -- it's the output.
//
// COMMON MISTAKES STUDENTS MAKE:
// 1. Only checking odd-length centers (calling expand(s,i,i) but
//    forgetting expand(s,i,i+1)). This silently fails on inputs
//    like "abba" or "cbbd" where the longest palindrome has no
//    single middle character.
//
// 2. Getting the start-index formula wrong -- writing
//    "start = i - len/2" instead of "start = i - (len-1)/2".
//    This breaks specifically for ODD-length palindromes because
//    integer division rounds differently without the -1 adjustment.
//
// 3. Using ">=" instead of ">" when comparing "len > (end - start)".
//    This still gives a VALID answer on ties, just possibly a
//    DIFFERENT valid answer than expected -- worth knowing so you
//    don't panic if your output differs from a sample but is still
//    technically correct.
//
// 4. Confusing this O(n^2) approach with the need for full O(n^2)
//    space DP, or panicking and trying to implement Manacher's
//    O(n) algorithm from memory. Expand-around-center is the
//    expected, sufficient answer in almost all interview settings.
//
// TRIGGER WORDS FOR THIS PATTERN:
//   - "longest palindromic substring" (must be CONTIGUOUS --
//     if it says "subsequence" instead of "substring," that's a
//     completely different DP problem, not this one)
//   - "expand around center"
//   - Brute force is clearly O(n^3) or worse and you need better
//
// COMPANIES THAT COMMONLY ASK THIS:
//   Amazon, Microsoft -- frequently used as a filter for "do you
//   know something better than checking every substring."
// ============================================================