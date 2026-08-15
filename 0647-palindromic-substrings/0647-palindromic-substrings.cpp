// class Solution {
// public:
//     int countSubstrings(string s) {
//         int n = s.size();
//         int count = 0;

//         for(int i =0; i<n; i++){
//             count += expand(s, i, i);
//             count += expand(s, i, i+1);
//         }

//         return count;
//     }

//     int expand(string &s, int left, int right){
//         int count = 0;

//         while (left >=0 && right < s.size() && s[left] == s[right]){
//             count++;
//             left--;
//             right++;
//         } 
//         return count++;
//     }
// };

// ============================================================
// LEETCODE 647 - PALINDROMIC SUBSTRINGS
// Pattern: EXPAND AROUND CENTER (same engine as LC5, different
//          question being asked of it: COUNT instead of MAX-FIND)
// ============================================================

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int count = 0;

        // ---------------------------------------------------------
        // Exactly the same "try every center" idea as LC5's
        // longestPalindrome. The ONLY difference in philosophy:
        // there, we tracked the BIGGEST ripple. Here, we SUM UP
        // every ripple's size, because every step a ripple survives
        // represents one more valid palindromic substring.
        // ---------------------------------------------------------
        for(int i = 0; i < n; i++){
            count += expand(s, i, i);      // odd-length centers at i
            count += expand(s, i, i+1);    // even-length centers between i and i+1
        }

        return count;
    }

    int expand(string &s, int left, int right){
        int count = 0;

        // -------------------------------------------------------
        // Every time the loop body runs ONE MORE TIME, that means
        // we just found ONE MORE valid palindrome (a slightly
        // bigger one than last time, but still centered here).
        // So unlike LC5 where we only cared about the FINAL size,
        // here every intermediate step itself is a countable answer.
        //
        // Example: expanding from center 'a' in "aaa" (say i=1):
        //   step 1: left=1,right=1 substring "a"   -> count=1
        //   step 2: left=0,right=2 substring "aaa" -> count=2
        // Both "a" and "aaa" are valid palindromic substrings
        // centered at index 1, and we counted both.
        // -------------------------------------------------------
        while (left >=0 && right < s.size() && s[left] == s[right]){
            count++;
            left--;
            right++;
        }

        // ---------------------------------------------------------
        // IMPORTANT STYLE NOTE (fixed from your original draft):
        // Writing "return count++;" LOOKS like it does something
        // different from "return count;", but it doesn't, here.
        //
        // count++ is POST-increment: it evaluates to count's CURRENT
        // value, and only AFTER that does it increment count as a
        // side effect. Since we return immediately, that side-effect
        // increment is thrown away and nobody ever sees it. So both
        // versions behave identically in THIS function.
        //
        // This is a trap, not a feature: if this function ever grows
        // (e.g., you add code after the loop that uses count again,
        // or you refactor it into a loop that calls expand multiple
        // times and expects the count to have a specific value), the
        // silent, discarded increment becomes a landmine. Always
        // write your intent plainly: return the value you mean to
        // return, nothing sneaky.
        // ---------------------------------------------------------
        return count;
    }
};

// ============================================================
// ============ REVISION SUMMARY (READ THIS FIRST) ============
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// For every possible center (single character AND every gap
// between two characters), expand outward and count EVERY step
// that still forms a valid palindrome -- not just the biggest one,
// ALL of them. Sum these counts across every center in the string.
//
// ANALOGY:
// Same pond, same pebbles, same ripples as Longest Palindromic
// Substring -- but this time, instead of remembering only the
// single biggest ripple you ever witnessed, you're a scorekeeper
// tallying a point for EVERY ring the ripple successfully drew
// before it broke. A ripple that survives 3 expansions scores 3
// points (3 valid palindromes at that center), not just 1.
//
// STEP-BY-STEP DRY RUN on s = "aaa" (traced from actual execution):
//
//   i=0 'a': odd expand(0,0) counts "a" -> 1
//            even expand(0,1) counts "aa" -> 1
//            running total = 2
//
//   i=1 'a': odd expand(1,1) counts "a" then "aaa" -> 2
//            even expand(1,2) counts "aa" -> 1
//            running total = 2 + 2 + 1 = 5
//
//   i=2 'a': odd expand(2,2) counts "a" -> 1
//            even expand(2,3) -> right=3 is out of bounds -> 0
//            running total = 5 + 1 = 6
//
//   FINAL COUNT: 6
//   The 6 palindromic substrings of "aaa" are:
//   "a" (index0), "a" (index1), "a" (index2),
//   "aa" (index0-1), "aa" (index1-2), "aaa" (index0-2).
//   Verified against brute-force check across multiple test
//   strings (abc, aaa, abba, racecarxyz, aabaa, abcba) -- all match.
//
// TIME COMPLEXITY: O(n^2)
//   n possible centers (roughly 2n counting both odd and even
//   variants, still O(n)). Each expansion can take up to O(n) steps
//   in the worst case (all-identical-character strings like "aaaaa").
//   n centers x O(n) worst case expansion = O(n^2) total.
//
// SPACE COMPLEXITY: O(1)
//   Just integer counters -- no extra arrays, no strings built.
//
// COMMON MISTAKES STUDENTS MAKE:
// 1. Writing "return count++;" instead of "return count;" -- works
//    by coincidence here since the increment side-effect is thrown
//    away on return, but it signals a shaky grasp of pre/post
//    increment semantics that WILL bite you in a different context
//    (e.g., inside a for-loop condition, or when the incremented
//    value is actually used afterward).
//
// 2. Forgetting to call BOTH expand(s,i,i) and expand(s,i,i+1) --
//    missing the even-length case silently undercounts palindromes
//    like "aa", "abba", etc.
//
// 3. Trying to adapt LC5's max-tracking logic (start/end window
//    variables) into this problem instead of realizing you just
//    need a running SUM. Same engine (expand), different question
//    asked of the results -- recognize when a pattern's output
//    shape changes even though the core scanning logic is identical.
//
// 4. Off-by-one errors in the while loop condition, e.g. writing
//    "right <= s.size()" instead of "right < s.size()" -- this
//    reads one character past the end of the string, undefined
//    behavior territory.
//
// TRIGGER WORDS FOR THIS PATTERN:
//   - "count all palindromic substrings" / "how many palindromic
//     substrings" (contiguous, not subsequence)
//   - Whenever you've already recognized "expand around center"
//     from a similar problem (like LC5) but the question asks for
//     a COUNT instead of the longest one -- same engine, sum instead
//     of max.
//
// COMPANIES THAT COMMONLY ASK THIS:
//   Amazon, Microsoft -- frequently paired with LC5 in the same
//   interview loop to test whether you can adapt one core engine
//   (expand around center) to two different questions.
// ============================================================