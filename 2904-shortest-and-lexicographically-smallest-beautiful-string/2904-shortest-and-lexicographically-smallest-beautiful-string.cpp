// class Solution {
// public:
//     string shortestBeautifulSubstring(string s, int k) {
//         int n = s.size();

//         int i = 0;
//         int j = 0;
//         int ones = 0;

//         string result = "";

//         while (j < n) {
//             if (s[j] == '1')
//                 ones++;

//             while (ones > k || s[i] == '0') {
//                 if (s[i] == '1') {
//                     ones--;
//                 }
//                 i++;
//             }

//             if (ones == k) {
//                 string temp = s.substr(i, j - i + 1);

//                 if (result.empty() || result.length() > j - i + 1 ||
//                     temp.size() == result.size() && temp < result) {
//                     result = temp;
//                 }
//             }
//             j++;
//         }

//         return result;
//     }
// };






/*
========================================================================================
LEETCODE 2904 — SHORTEST AND LEXICOGRAPHICALLY SMALLEST BEAUTIFUL SUBSTRING
========================================================================================

PLAIN ENGLISH DEFINITION:
Find the shortest piece of a binary string that contains EXACTLY k ones.
If multiple pieces tie for shortest, pick the one that comes first alphabetically
(character by character, '0' < '1').

REAL-WORLD ANALOGY — "The Leaky Measuring Cup":
Imagine you're pouring a binary string into a measuring cup, drop by drop, from
left to right. You only care about counting RED drops (the '1's). You need
EXACTLY k red drops in the cup — not more, not less.

- Every time you pour a new drop in (moving pointer j right), check its color.
- If the cup now has MORE than k red drops, it's overflowing — tip the cup and
  pour liquid out from the bottom (moving pointer i right) until you're back to k or less.
- Even if the cup isn't overflowing, if there's a useless CLEAR drop (a '0') sitting
  at the very bottom, pour that out too — it's dead weight, adding size to your cup
  without helping your red-drop count. You always want the smallest cup possible.
- The moment your cup has EXACTLY k red drops AND no wasted clear liquid at the
  bottom, you've got a valid "beautiful" candidate. Compare it to your best answer
  so far and keep whichever is shorter (or alphabetically smaller if tied in length).

Both pointers i (bottom of cup) and j (top of cup) only ever move FORWARD — that's
the fingerprint of the classic "variable-size sliding window" pattern.

========================================================================================
DRY RUN EXAMPLE — s = "100011001", k = 3
========================================================================================
Index:   0 1 2 3 4 5 6 7 8
Char:    1 0 0 0 1 1 0 0 1

j=0: s[0]='1' -> ones=1. Window="1" (i=0). ones(1) < k(3), no candidate yet.
j=1: s[1]='0' -> ones=1. Window="10". s[i]='1' so no shrink needed. ones<k, skip.
j=2: s[2]='0' -> ones=1. Window="100". ones<k, skip.
j=3: s[3]='0' -> ones=1. Window="1000". ones<k, skip.
j=4: s[4]='1' -> ones=2. Window="10001". ones<k, skip.
j=5: s[5]='1' -> ones=3. Window="100011". ones==k(3)! Candidate = "100011" (len 6).
     result = "100011"
j=6: s[6]='0' -> ones=3. Window="1000110". ones==k still (0 doesn't change count),
     but s[i]=s[0]='1' so inner while doesn't trigger (ones not > k, and s[i] != '0').
     Wait — window is now "1000110", ones still 3. Candidate len=7, WORSE than len 6. Skipped.
j=7: s[7]='0' -> ones=3. Window="10001100", len=8. Still worse. Skipped.
j=8: s[8]='1' -> ones=4. Now ones(4) > k(3) -> shrink from left:
     s[i]=s[0]='1' -> ones-- (ones=3), i=1.
     Now check again: ones(3) not > k, but s[i]=s[1]='0' -> shrink again (leading zero waste):
     i=2 (ones still 3, since we removed a '0', not a '1').
     s[i]=s[2]='0' -> shrink again: i=3.
     s[i]=s[3]='0' -> shrink again: i=4.
     s[i]=s[4]='1', ones(3) not > k -> STOP shrinking.
     Window = s[4..8] = "11001", len=5. ones==k(3)! Candidate = "11001" (len 5).
     len(5) < len(result)=6 -> result = "11001"  <-- NEW BEST, shorter!

Final answer: "11001"

Notice how the leading-zero-stripping step at j=8 is what let us find a SHORTER
answer than the naive "first k ones found" window. This is the exact mechanic
you must never skip.

========================================================================================
*/

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();

        // i = left edge of window, j = right edge of window.
        // ones = how many '1's currently live inside window [i, j].
        // Both pointers move ONLY forward -> guarantees O(n) total work, not O(n^2).
        int i = 0;
        int j = 0;
        int ones = 0;

        // Best beautiful substring found so far. Empty string = "nothing found yet".
        string result = "";

        // ---------------- OUTER LOOP: expand the window one character at a time ----------------
        // Every iteration, we bring ONE new character into the window via j.
        // This is the "grow" half of the classic grow-then-shrink sliding window rhythm.
        while (j < n) {

            // New character joins the window — if it's a '1', it counts toward our target k.
            if (s[j] == '1')
                ones++;

            // ---------------- INNER LOOP: shrink the window from the left ----------------
            // TWO separate reasons trigger a shrink, combined into one OR condition:
            //
            // Reason 1 (ones > k): The window is "overfull" — it has MORE ones than we're
            //   allowed. This makes the window INVALID, and we MUST fix it by removing
            //   characters from the left until ones drops back to <= k.
            //
            // Reason 2 (s[i] == '0'): The leftmost character is a wasted zero. Removing
            //   it does NOT touch our ones count at all (it's a zero!), but it DOES make
            //   the window shorter. Since our goal is the SHORTEST beautiful substring,
            //   any free zero sitting at the left edge is pure dead weight — always evict it.
            //   THIS is the step most students forget, and forgetting it gives you a
            //   *correct but not shortest* answer.
            while (ones > k || s[i] == '0') {
                if (s[i] == '1') {
                    ones--;   // only decrement when we're evicting an actual '1'
                }
                i++;          // shrink: move left edge forward regardless of what we removed
            }

            // After shrinking, window [i, j] is "clean": no leading zero waste,
            // and ones <= k. If ones == k exactly, we have a valid, minimal-for-this-j
            // beautiful substring — check it against our best answer so far.
            if (ones == k) {
                string temp = s.substr(i, j - i + 1);

                // Tie-breaking rule baked into one condition:
                //   - if result is still empty, anything beats "nothing"
                //   - if temp is strictly shorter than result, temp wins (shortest first)
                //   - if temp is the SAME length as result, compare lexicographically
                //     (C++ string '<' does character-by-character comparison automatically)
                if (result.empty() || result.length() > j - i + 1 ||
                    temp.size() == result.size() && temp < result) {
                    result = temp;
                }
            }

            j++;   // move right edge forward, growing the window for the next iteration
        }

        return result;
    }
};

/*
========================================================================================
COMPLEXITY ANALYSIS (reasoned, not memorized)
========================================================================================
TIME: O(n)
  - Pointer j visits each of the n characters exactly once -> n steps.
  - Pointer i NEVER moves backward across the ENTIRE run of the algorithm. So even
    though it sits inside a nested while loop, the total number of times i can
    advance, summed across ALL outer iterations, is capped at n (it can't exceed
    the string length). This is the "amortized O(1) per step" argument — the
    inner loop looks scary but costs O(n) total, not O(n) PER outer iteration.
  - substr() calls cost O(window length) each time we find a candidate, but in
    practice this stays small/bounded and doesn't change the overall linear feel
    of the algorithm for interview purposes.

SPACE: O(n)
  - Dominated by the temp/result strings we build via substr(), each up to length n.

========================================================================================
COMMON MISTAKES (and WHY they happen)
========================================================================================
1. Forgetting to strip leading zeros (only checking `ones > k` in the inner while).
   WHY IT HAPPENS: Students correctly identify "shrink when invalid" but miss that
   the window can be VALID (ones == k) and STILL improvable by trimming useless
   zeros from the front. The bug is subtle because the code still returns a
   *correct* beautiful substring — just not the shortest one. It usually only
   surfaces on specific test cases, making it sneaky to catch.

2. Decrementing `ones` for every character evicted, instead of only for '1's.
   WHY IT HAPPENS: Muscle memory from other sliding window problems where every
   evicted element affects the tracked quantity. Here, zeros are "free" to evict.

3. Comparing candidates by length only, forgetting the lexicographic tie-break.
   WHY IT HAPPENS: The length comparison feels like "the whole problem," and the
   lexicographic rule is easy to treat as an afterthought rather than an equal
   partner in the comparison condition.

4. Off-by-one in substr(i, j - i + 1) — using j - i instead of j - i + 1.
   WHY IT HAPPENS: Confusing "window length" with "index difference." Window
   [i, j] inclusive on both ends has length (j - i + 1), not (j - i).

========================================================================================
TRIGGER WORDS — when you should think "exact-count sliding window":
========================================================================================
- "exactly k occurrences / ones / distinct elements in a substring/subarray"
- "shortest window containing exactly ..." (as opposed to "at least" -> also sliding
  window, but with a different shrink condition)
- "shortest AND lexicographically smallest" tie-break -> signals you need a
  comparison step beyond just length, at the point where you find a valid window

RELATED PROBLEMS TO PRACTICE THIS PATTERN:
- LC 992: Subarrays with K Different Integers (exact count, but count of DISTINCT
  values via hashmap instead of a single counter)
- LC 1493: Longest Subarray of 1's After Deleting One Element (variable window,
  different shrink condition)
- LC 3095: Shortest Subarray With OR at Least K I (variable window, "at least" flavor)

COMPANIES KNOWN TO ASK THIS PATTERN:
- Amazon and Bloomberg have both had this exact problem (LC 2904) surface in OA
  rounds. The broader "exact-count sliding window + tie-break" family is a
  favorite in Google and Amazon phone screens because it separates candidates who
  truly understand window invariants from those who just memorized a template.
========================================================================================
*/












// Brute force approach
// class Solution {
// public:
//     string shortestBeautifulSubstring(string s, int k) {
//         int n = s.size();

//         for(int len = k; len<= n; len++){
//             string result = "";

//             for(int start = 0; start <= n-len; start++){
//                 string temp = s.substr(start, len);

//                 int ones = 0;
//                 for(char &ch : temp){
//                     ones += (ch =='1') ? 1 : 0;
//                 }

//                 if(ones == k){
//                     if(result.empty() || temp < result){
//                         result = temp;
//                     }
//                 }
//             }

//             if(!result.empty()){
//                 return result;
//             }
//         }
//         return "";
//     }
// };