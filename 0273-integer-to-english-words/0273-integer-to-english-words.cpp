// class Solution {
// public:
//     unordered_map<int, string> belowTen = {
//         {0, ""}, {1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"},
//         {5, "Five"}, {6, "Six"}, {7, "Seven"}, {8, "Eight"}, {9, "Nine"}};

//     unordered_map<int, string> belowTwenty = {
//         {10, "Ten"}, {11, "Eleven"}, {12, "Twelve"}, {13, "Thirteen"},
//         {14, "Fourteen"}, {15, "Fifteen"}, {16, "Sixteen"}, {17, "Seventeen"},
//         {18, "Eighteen"}, {19, "Nineteen"}};

//     unordered_map<int, string> belowHundred = {
//         {2, "Twenty"}, {3, "Thirty"}, {4, "Forty"}, {5, "Fifty"},
//         {6, "Sixty"}, {7, "Seventy"}, {8, "Eighty"}, {9, "Ninety"}};

//     string solve(int num) {
//         if (num < 10) return belowTen[num];
//         if (num < 20) return belowTwenty[num];
//         if (num < 100)
//             return belowHundred[num / 10] + (num % 10 != 0 ? " " + belowTen[num % 10] : "");
//         if (num < 1000)
//             return solve(num / 100) + " Hundred" + (num % 100 != 0 ? " " + solve(num % 100) : "");
//         if (num < 1000000)
//             return solve(num / 1000) + " Thousand" + (num % 1000 != 0 ? " " + solve(num % 1000) : "");
//         if (num < 1000000000)
//             return solve(num / 1000000) + " Million" + (num % 1000000 != 0 ? " " + solve(num % 1000000) : "");
//         return solve(num / 1000000000) + " Billion" + (num % 1000000000 != 0 ? " " + solve(num % 1000000000) : "");
//     }

//     string numberToWords(int num) {
//         if (num == 0) return "Zero";
//         return solve(num);
//     }
// };







// ============================================================
// LeetCode 273 - Integer to English Words
// Pattern: RECURSION + PROBLEM DECOMPOSITION (chunking by scale)
// Difficulty: Hard (but the "hard" part is edge-case bookkeeping,
// NOT the core algorithmic idea)
// ============================================================

class Solution {
public:

    // ------------------------------------------------------------
    // LOOKUP TABLES (the "vocabulary" of our translator)
    // ------------------------------------------------------------
    // belowTen: words for digits 0-9.
    // Note: 0 maps to "" (empty string) on purpose -- because 0
    // never needs to be SPOKEN on its own inside a bigger number
    // (e.g., we don't say "One Hundred Zero", we say "One Hundred").
    // The empty string acts as a "silent" placeholder.
    unordered_map<int, string> belowTen = {
        {0, ""}, {1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"},
        {5, "Five"}, {6, "Six"}, {7, "Seven"}, {8, "Eight"}, {9, "Nine"}};

    // belowTwenty: the awkward "teen" words (10-19) that don't
    // follow the tens+ones pattern (e.g., you can't build "Eleven"
    // from "Ten" + "One" the way you build "Twenty-One" from
    // "Twenty" + "One"). English is irregular here, so we just
    // hardcode this irregular zone as its own lookup table.
    unordered_map<int, string> belowTwenty = {
        {10, "Ten"}, {11, "Eleven"}, {12, "Twelve"}, {13, "Thirteen"},
        {14, "Fourteen"}, {15, "Fifteen"}, {16, "Sixteen"}, {17, "Seventeen"},
        {18, "Eighteen"}, {19, "Nineteen"}};

    // belowHundred: words for the TENS DIGIT only (20, 30, ..., 90),
    // keyed by that digit (2 for Twenty, 3 for Thirty, etc.)
    // Notice keys start at 2 -- because 0 and 1 in the tens place
    // are handled by belowTen/belowTwenty already, never by this map.
    unordered_map<int, string> belowHundred = {
        {2, "Twenty"}, {3, "Thirty"}, {4, "Forty"}, {5, "Fifty"},
        {6, "Sixty"}, {7, "Seventy"}, {8, "Eighty"}, {9, "Ninety"}};

    // ------------------------------------------------------------
    // solve(num) -- the recursive "translator engine"
    // Converts ANY number (0 to ~999,999,999) into English words.
    // ------------------------------------------------------------
    //
    // CORE INTUITION -- "Read the number the way you SAY it out loud":
    // When you read 1,234,567 aloud, you naturally break it into
    // chunks: "one million" + "two hundred thirty-four thousand"
    // + "five hundred sixty-seven". Each chunk is a number from
    // 0-999, followed by a SCALE WORD (Thousand / Million / Billion).
    // This function encodes exactly that mental process:
    // 1) Peel off the biggest scale chunk you can.
    // 2) Recursively solve the "coefficient" of that scale
    //    (e.g., for 1,234,567 -> the "1" before Million).
    // 3) Recursively solve whatever number is LEFT OVER after
    //    removing that chunk.
    // 4) Glue it all together with spaces.
    string solve(int num) {

        // ---- BASE CASE 1: single digit (0-9) ----
        // Directly look up the word. No recursion needed --
        // this is the "floor" of our recursive descent.
        if (num < 10) return belowTen[num];

        // ---- BASE CASE 2: teens (10-19) ----
        // These are irregular in English, so we short-circuit
        // straight to the lookup table instead of trying to
        // decompose them into tens+ones (which would break,
        // since e.g. "Ten" + "Three" != "Thirteen").
        if (num < 20) return belowTwenty[num];

        // ---- CASE: 20-99 (two-digit, regular tens+ones) ----
        // num/10 gives the tens digit (2 for 20s, 9 for 90s) --
        // used to fetch "Twenty".."Ninety" from belowHundred.
        // num%10 gives the ones digit -- fetched from belowTen.
        // We only append the ones-word if it's non-zero (to avoid
        // producing "Twenty " with a trailing space or "Twenty Zero").
        if (num < 100)
            return belowHundred[num / 10] + (num % 10 != 0 ? " " + belowTen[num % 10] : "");

        // ---- CASE: 100-999 (hundreds) ----
        // solve(num/100) gets the WORD for the hundreds digit
        // (e.g., for 234, num/100 = 2 -> recursion returns "Two").
        // We append the literal word "Hundred".
        // Then, IF there's a nonzero remainder (num % 100 != 0),
        // we recursively solve THAT remainder and append it too.
        // This is the same pattern that repeats at every scale level:
        //   [word for the leading chunk] + [SCALE NAME] + [word for the rest, if any]
        if (num < 1000)
            return solve(num / 100) + " Hundred" + (num % 100 != 0 ? " " + solve(num % 100) : "");

        // ---- CASE: 1000-999,999 (thousands) ----
        // Same exact pattern as hundreds, just at a bigger scale.
        // num/1000 = the part that will be read as "___ Thousand"
        // (this part itself can be up to 3 digits, e.g., 999 Thousand,
        // so we recursively call solve() on it -- it will bottom out
        // through the earlier base cases).
        // num%1000 = whatever is left after removing full thousands.
        if (num < 1000000)
            return solve(num / 1000) + " Thousand" + (num % 1000 != 0 ? " " + solve(num % 1000) : "");

        // ---- CASE: 1,000,000-999,999,999 (millions) ----
        // Identical pattern, scaled up again.
        if (num < 1000000000)
            return solve(num / 1000000) + " Million" + (num % 1000000 != 0 ? " " + solve(num % 1000000) : "");

        // ---- CASE: billions (up to INT_MAX, which is ~2.1 billion) ----
        // No upper "if" guard needed here since this is the LAST
        // possible scale for a 32-bit int -- anything that reaches
        // this line must be >= 1,000,000,000.
        return solve(num / 1000000000) + " Billion" + (num % 1000000000 != 0 ? " " + solve(num % 1000000000) : "");
    }

    // ------------------------------------------------------------
    // numberToWords(num) -- the entry point LeetCode calls
    // ------------------------------------------------------------
    // Special-cases ZERO separately because solve() has NO clean
    // path for num==0: belowTen[0] = "" (empty string), and
    // returning an empty string would be WRONG -- the expected
    // output for 0 is literally the word "Zero". Every other
    // branch of solve() assumes num > 0, so this guard must exist
    // before we ever call solve().
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        return solve(num);
    }
};

/*
============================================================
REVISION SUMMARY (read this when you forget everything else)
============================================================

WHAT IS THIS PROBLEM?
Convert a non-negative integer (0 to 2^31 - 1) into its English
word representation, exactly matching how you'd read it aloud
in standard American English number-naming convention (e.g.,
1234567 -> "One Million Two Hundred Thirty Four Thousand Five
Hundred Sixty Seven").

ANALOGY - "A translator that reads numbers the way commas group them":
Think of how you write large numbers with commas:
1,234,567 -> groups of 3 digits from the right: 1 | 234 | 567.
Each comma-separated group gets read as a number from 0-999,
followed by a "scale announcement" (Thousand, Million, Billion).
Your code is literally a machine that:
  1. Finds the biggest scale group (billions first, then millions,
     then thousands, then hundreds).
  2. Translates that group's leading digits using recursion.
  3. Announces the scale word.
  4. Recursively handles whatever number remains to the right.
It's like reading a cheque amount aloud, chunk by chunk, loudest
(biggest) scale first.

THE CORE INTUITION - "Recursion peels off one scale layer at a time":
Every branch (Hundred / Thousand / Million / Billion) follows the
EXACT same 3-part template:
    solve(bigPart) + " ScaleWord" + (if remainder exists) + solve(remainder)
Once you see this repeating template, the whole function becomes
predictable instead of "hard" -- it's the same idea copy-pasted
at 4 different scales, plus two irregular base cases (single
digits, and the teens 10-19) because English itself is irregular
there, not because the algorithm needs it.

DRY RUN EXAMPLE: numberToWords(1234567)
- num = 1234567, which is < 1,000,000,000 but >= 1,000,000
  -> return solve(1234567 / 1000000) + " Million" + " " + solve(1234567 % 1000000)
  -> solve(1) + " Million" + " " + solve(234567)
  -> "One" + " Million" + " " + solve(234567)

  Now expand solve(234567):
  - 234567 < 1,000,000 but >= 1000
    -> solve(234567/1000) + " Thousand" + " " + solve(234567%1000)
    -> solve(234) + " Thousand" + " " + solve(567)

    Expand solve(234):
    - 234 < 1000, >= 100
      -> solve(234/100) + " Hundred" + " " + solve(234%100)
      -> solve(2) + " Hundred" + " " + solve(34)
      -> "Two" + " Hundred" + " " + solve(34)
      solve(34): 34 is 20-99 -> belowHundred[3] + " " + belowTen[4]
                 -> "Thirty" + " " + "Four" -> "Thirty Four"
      => solve(234) = "Two Hundred Thirty Four"

    Expand solve(567): similarly -> "Five Hundred Sixty Seven"

    => solve(234567) = "Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

  Final: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
  (Matches LeetCode's expected output exactly.)

TIME COMPLEXITY: O(1) (technically, but let's be precise)
  Since num is bounded by a 32-bit int (max ~2.1 billion), there
  are AT MOST 4 "scale levels" (billions, millions, thousands,
  hundreds/tens/ones) to peel through. Each level does a constant
  amount of work (a couple of map lookups and string concatenations).
  So this runs in effectively constant time relative to input SIZE
  (not value) -- it does NOT grow unboundedly with num, because
  32-bit integers have a hard ceiling. If asked in an interview,
  say "O(1) because the number of digits is bounded by a fixed
  constant (10 digits max for a 32-bit int)."

SPACE COMPLEXITY: O(1) (bounded recursion depth)
  Recursion depth is at most ~4-5 levels deep (billion -> million
  -> thousand -> hundred -> tens/ones), so the call stack never
  grows with the input value. String concatenation costs are also
  bounded since the output string has a fixed maximum length.

COMMON MISTAKES WITH THIS PATTERN:
1. Forgetting the num==0 special case. solve(0) would return
   belowTen[0] = "" (empty string) which is WRONG -- LeetCode
   expects the literal word "Zero". This is the #1 silent bug.
2. Extra or missing spaces. Since every branch conditionally
   appends " " + solve(remainder) ONLY when the remainder is
   non-zero, forgetting that "if remainder != 0" check produces
   ugly output like "One Hundred " (trailing space) or "Two
   Hundred Zero" for a number like 200.
3. Mixing up WHERE tens vs hundreds logic applies. A common bug
   is trying to reuse belowHundred[] for teens (10-19) -- but
   belowHundred is ONLY for the "tens digit when it's 2-9"
   (Twenty, Thirty, ...Ninety). Teens are a totally separate,
   irregular lookup (belowTwenty) precisely because "Ten" + "One"
   doesn't spell "Eleven".

TRIGGER WORDS TO SPOT THIS PATTERN:
"convert number to words," "spell out a number," "English
representation of an integer," "digit grouping by
thousand/million/billion" -- these should immediately signal:
recursive decomposition by scale + irregular base-case lookup
tables for 0-19.

WHERE THIS PATTERN SHOWS UP:
This exact problem (Integer to English Words) has been reported
in interview question banks associated with Meta/Facebook and
Amazon, usually as a "string manipulation + recursion" round to
test how cleanly you handle nested edge cases (trailing spaces,
zero-handling, irregular number names) rather than testing raw
algorithmic cleverness.
============================================================
*/