// class Solution {
// public:
//     int t[21][21];

//     bool solve(int i, int j, string &s, string &p) {
//         if (j == p.size()) {
//             return i == s.size(); // ✅ comparison, not assignment
//         }

//         if (t[i][j] != -1) { // ✅ check against -1
//             return t[i][j];
//         }

//         bool first_char_matched = (i < s.size() && (p[j] == s[i] || p[j] == '.'));

//         if (j + 1 < p.size() && p[j + 1] == '*') {
//             bool not_take = solve(i, j + 2, s, p);
//             bool take = first_char_matched && solve(i + 1, j, s, p);
//             return t[i][j] = (not_take || take);
//         }

//         return t[i][j] = (first_char_matched && solve(i + 1, j + 1, s, p));
//     }

//     bool isMatch(string s, string p) {
//         memset(t, -1, sizeof(t));
//         return solve(0, 0, s, p);
//     }
// };








class Solution {
public:
    int t[21][21];   // Memoization table: t[i][j] stores the result of
                     // "does s[i:] match p[j:]?" so we never recompute
                     // the same subproblem twice.
                     // Dimensions 21x21 because problem constraints say
                     // s and p are at most 20 characters long.
                     // Values: -1 = not computed yet, 0 = false, 1 = true.

    // Recursive function with memoization (top-down DP).
    // Returns true if the SUFFIX of s starting at index i matches
    // the SUFFIX of p starting at index j.
    bool solve(int i, int j, string &s, string &p) {

        // BASE CASE 1: pattern is fully consumed (j == p.size()).
        // If pattern is exhausted, the ONLY way we have a valid match is
        // if the string is ALSO exhausted (i == s.size()).
        // If string still has leftover characters but pattern is empty,
        // we can't match them — return false.
        if (j == p.size()) {
            return i == s.size();   // true if both empty, false if s still has chars
        }

        // BASE CASE 2: we've already solved this exact subproblem before.
        // If t[i][j] is not -1, we've already computed whether s[i:]
        // matches p[j:], so just return the stored result immediately.
        // This turns an exponential recursion tree into O(n*m) time.
        if (t[i][j] != -1) {
            return t[i][j];
        }

        // STEP 1: Check if the CURRENT character pair matches.
        // This is ONLY about the single character at s[i] and p[j] —
        // it does NOT look ahead at '*' or anything else yet.
        // Conditions:
        //   - i < s.size(): we must still have a character in s to match;
        //     if i == s.size(), there's nothing left to match against p[j].
        //   - p[j] == s[i] OR p[j] == '.': exact match or '.' wildcard.
        bool first_char_matched = (i < s.size() && (p[j] == s[i] || p[j] == '.'));

        // STEP 2: Look ahead to see if the NEXT pattern character is '*'.
        // This is the CRUCIAL branching point that makes this problem
        // fundamentally different from a simple character-by-character match.
        // '*' means: "the preceding character (p[j]) can repeat 0 or more times."
        if (j + 1 < p.size() && p[j + 1] == '*') {

            // CHOICE A — "Skip the 'x*' pattern entirely" (match 0 occurrences):
            // We ignore both p[j] (the character) and p[j+1] (the '*')
            // and move directly to j+2 in the pattern, keeping i unchanged
            // (we consume NO characters from s).
            // Example: s="ab", p="x*ab" → skip "x*" completely, match "ab" with "ab".
            bool not_take = solve(i, j + 2, s, p);

            // CHOICE B — "Use the 'x*' pattern to consume ONE character from s"
            // (match 1 or more occurrences):
            // This is ONLY allowed if the current character actually matches
            // (first_char_matched is true). If it matches, we consume ONE
            // character from s (i+1) but STAY at the same pattern position j
            // (not j+2), because '*' allows us to reuse p[j] again and again
            // for subsequent characters.
            // Example: s="aaa", p="a*" → first call consumes one 'a' but
            // stays at "a*", allowing the next call to consume another 'a', etc.
            bool take = first_char_matched && solve(i + 1, j, s, p);

            // If EITHER choice leads to a full match, this subproblem is true.
            // Store and return the result.
            return t[i][j] = (not_take || take);
        }

        // STEP 3: No '*' ahead — simple one-to-one match required.
        // If current characters match, advance BOTH pointers by 1.
        // If they don't match, this branch fails immediately (false).
        return t[i][j] = (first_char_matched && solve(i + 1, j + 1, s, p));
    }

    bool isMatch(string s, string p) {
        // Initialize the entire memo table to -1 (uncomputed) before starting.
        memset(t, -1, sizeof(t));
        // Start the recursion from the very beginning of both strings.
        return solve(0, 0, s, p);
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Given a string s and a pattern p containing '.' (matches any single char)
and '*' (matches 0 or more of the preceding element), determine if the
ENTIRE string matches the ENTIRE pattern (no partial matches allowed).

ANALOGY — "Reading a pattern with optional repeat buttons":
Imagine the pattern is a sequence of instruction cards laid out on a table.
Most cards say "match this exact letter" or "match any letter" ('.'). But
some cards come in pairs: a letter card followed immediately by a special
"REPEAT" card ('*'). When you see a REPEAT card, you have two options:
  1. Ignore both the letter and the REPEAT entirely (match zero copies),
     and jump straight to the next card after the pair.
  2. If the current letter on your string matches the letter on the card,
     consume ONE letter from your string, but STAY on this same card pair
     (because the REPEAT lets you use it again and again).
You keep doing this until either you run out of cards (pattern exhausted) —
in which case you only win if you've also used up your entire string — or
you hit a mismatch with no REPEAT to save you, in which case you lose.

ATOMIC BREAKDOWN — HOW TO THINK ABOUT THIS PROBLEM FROM SCRATCH:
1. Ask: "What decision do I face at each step?"
   Answer: Either I'm looking at a normal character/'.' (must match exactly
   one character and move on), OR I'm looking at a character followed by
   '*' (must decide: skip it entirely, or use it to consume one char and
   stay here for potential reuse).
2. Ask: "What defines my state?"
   Answer: Two indices — i (where I am in s) and j (where I am in p).
   Everything before i and j is already decided; everything after is the
   remaining subproblem.
3. Ask: "What are my base cases?"
   Answer: Pattern exhausted → success only if string also exhausted.
   (String exhausted but pattern not necessarily failure — "a*" can still
   match an empty string by choosing 0 repetitions.)
4. Ask: "Do subproblems repeat?"
   Answer: Yes — many different paths through the recursion can land on
   the exact same (i, j) pair, so memoization is essential to avoid
   exponential blowup.

DRY RUN (s = "aab", p = "c*a*b"):
solve(0,0): p[0]='c', p[1]='*' → '*' present
  not_take = solve(0,2)  (skip "c*")
    solve(0,2): p[2]='a', p[3]='*' → '*' present
      not_take = solve(0,4)  (skip "a*")
        solve(0,4): p[4]='b', no '*' → match 'a' vs 'b'? NO → false
      take = ('a' matches 'a') && solve(1,2)
        solve(1,2): p[2]='a', p[3]='*'
          not_take = solve(1,4) → 'a' vs 'b'? NO → false
          take = ('a' matches 'a') && solve(2,2)
            solve(2,2): p[2]='a', p[3]='*'
              not_take = solve(2,4) → 'b' vs 'b'? YES → solve(3,5)
                solve(3,5): j==p.size() && i==s.size() → TRUE
              take = ('b' vs 'a'? NO) → false
              → returns true
          → returns true
      → returns true
  take = ('a' vs 'c'? NO) → false
  → returns true (via not_take branch)
Final: true — "aab" matches "c*a*b" correctly.

TIME COMPLEXITY: O(n * m), where n = s.length(), m = p.length().
Each (i, j) pair is computed at most once (stored in t[i][j]), and there
are n*m such pairs. Each computation does O(1) work (constant number of
recursive calls and checks).
SPACE COMPLEXITY: O(n * m) for the memoization table, plus O(n + m) for
the recursion call stack depth in the worst case.

TRIGGER WORDS for this pattern:
- "pattern matching with '.' and '*'," "wildcard matching," "regex match"
  → almost always DP or memoized recursion, with state = (index in text,
  index in pattern).
- Whenever a problem involves "optional repetition" or "0 or more of
  something" combined with matching, think: "do I have a choice here —
  skip it entirely, or use it and stay/advance?" — that branching structure
  is the hallmark of this DP pattern.

COMMON MISTAKES:
1. Forgetting to check `i < s.size()` before accessing `s[i]` in
   `first_char_matched` — when i == s.size() (string exhausted but pattern
   still has characters), accessing s[i] is out-of-bounds and causes
   undefined behavior or runtime errors.
2. Mishandling the '*' case by advancing j to j+1 instead of j+2 in the
   "skip" branch — remember, '*' is a TWO-character unit (the character
   plus the star), so skipping it means jumping past BOTH.
3. In the "take" branch, advancing j to j+1 instead of keeping it at j —
   this would incorrectly treat '*' as "exactly one repetition" instead of
   "zero or more," breaking cases like "aaa" vs "a*" where multiple
   repetitions are needed.
4. Not initializing the memo table with memset (or equivalent) before
   calling solve — leftover values from previous test cases (in an
   interview setting where you reuse the same class) can silently corrupt
   results.

WHERE THIS SHOWS UP:
Regular Expression Matching (LC 10) is a canonical hard DP question at
Google, Meta, and Amazon — often used specifically to test whether a
candidate can derive the state definition and transition logic from first
principles rather than memorizing a solution. It's also a direct precursor
to Wildcard Matching (LC 44), which uses a similar DP structure but with
different rules for '*' (matching any sequence instead of just the
preceding character).
================================================================================
*/
