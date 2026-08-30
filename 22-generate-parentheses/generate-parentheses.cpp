// class Solution {
// public:
//     vector<string> result;

//     void solve(string& curr, int n, int open, int close) {
//         if (curr.length() == 2 * n) {
//             result.push_back(curr);
//             return;
//         }
//         if (open < n) {
//             curr.push_back('(');
//             solve(curr, n,open+1,close);

//             curr.pop_back();
//         }
//         if (close < open) {
//             curr.push_back(')');
//             solve(curr, n,open,close+1);

//             curr.pop_back();
//         }
//     }

//     vector<string> generateParenthesis(int n) {
//         string curr = "";

//         int open = 0;
//         int close = 0;

//         solve(curr, n, open, close);
//         return result;
//     }
// };






class Solution {
public:
    vector<string> result;   // Collects every valid, fully-balanced string.

    // 'open'  = how many '(' characters we've placed so far
    // 'close' = how many ')' characters we've placed so far
    // These two counters are the ENTIRE mechanism that keeps every generated
    // string automatically valid — we never build an invalid string and
    // throw it away later; we simply never ALLOW an invalid move to happen.
    void solve(string& curr, int n, int open, int close) {

        // BASE CASE: the string has reached its final required length
        // (2*n, since a balanced string of n pairs always has exactly
        // n opening + n closing brackets). If we got here, the string
        // is guaranteed already balanced — no extra validity check needed,
        // because the two pruning rules below made that impossible to break.
        if (curr.length() == 2 * n) {
            result.push_back(curr);
            return;
        }

        // RULE 1 — Can we open a new bracket?
        // Only if we haven't used up our total budget of n opening
        // brackets yet. Think of 'open < n' as "do I still have opening
        // brackets left in my pocket to spend?"
        if (open < n) {
            curr.push_back('(');
            solve(curr, n, open + 1, close);
            curr.pop_back();   // backtrack: undo this choice before trying
                                // the other branch (closing), so 'curr'
                                // reflects the correct state going into it.
        }

        // RULE 2 — Can we close a bracket right now?
        // Only if there's currently an UNMATCHED open bracket waiting —
        // i.e., we've opened strictly more than we've closed so far.
        // This is what prevents ever going "negative" (like writing ")("
        // at the very start, which would be invalid).
        if (close < open) {
            curr.push_back(')');
            solve(curr, n, open, close + 1);
            curr.pop_back();   // backtrack: same reasoning as above.
        }

        // Notice: there's no "else" or explicit failure branch. If NEITHER
        // rule fires (both conditions false), the function just falls
        // through and returns naturally — that's the recursion quietly
        // dying off on a dead-end branch, which is fine, because it means
        // we've already fully explored everything reachable from this state.
    }

    vector<string> generateParenthesis(int n) {
        string curr = "";
        int open = 0;
        int close = 0;

        solve(curr, n, open, close);
        return result;
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Generate every possible string of n pairs of balanced parentheses (2n
characters total), where "balanced" means every '(' has a matching ')'
later, and you never have more ')' than '(' at any prefix.

ANALOGY — "Climbing a staircase with a strict step budget":
Think of '(' as a step UP and ')' as a step DOWN. You're given a total
budget of exactly n steps up for the whole climb (that's the 'open < n'
rule — you can't step up once you've spent your whole budget). At any
point, you can only step DOWN if you're currently above ground level —
you can never step below where you started, because that would mean more
')' than '(' so far, which is invalid (that's the 'close < open' rule —
you can only go down as many times as you've already gone up). The
string is only "complete and valid" once you've used your entire step
budget AND returned exactly back to ground level — which is guaranteed by
the time curr.length() == 2*n, since every up-step is eventually matched
by a down-step.

WHY THIS NEVER PRODUCES AN INVALID STRING (no filtering needed):
Every single character we ever push onto 'curr' passes through one of the
two gatekeeper conditions BEFORE being added. There's no path through the
code where we could push a ')' without an unmatched '(' already waiting, or
push more than n total '('. This is "prune as you build" backtracking,
much more efficient than "build everything, then check validity after."

DRY RUN (n = 2, full trace):
solve("", 2, 0, 0)
├─ push '(' → "(" → solve("(", 2, 1, 0)
│   ├─ push '(' → "((" → solve("((", 2, 2, 0)
│   │   └─ push ')' → "(()" → solve("(()", 2, 2, 1)
│   │       └─ push ')' → "(())" → length==4 → RECORD "(())"
│   ├─ push ')' → "()" → solve("()", 2, 1, 1)
│   │   └─ push '(' → "()(" → solve("()(", 2, 2, 1)
│   │       └─ push ')' → "()()" → length==4 → RECORD "()()"

Final result: ["(())", "()()"]  — exactly the 2 valid combinations for n=2,
matching the known LeetCode expected output.

TIME COMPLEXITY: O(4^n / sqrt(n)) — this is exactly the n-th Catalan number
growth rate, which counts how many valid balanced sequences exist; building
each valid string of length 2n costs O(n), so total work is proportional to
(Catalan number) * n.
SPACE COMPLEXITY: O(n) for the recursion depth and the 'curr' string itself
(excluding the space needed to store all the output strings, which is
inherently O(n * Catalan(n)) since that's the total output size).

TRIGGER WORDS for this pattern:
- "generate all valid/balanced parentheses combinations" → backtracking
  with two running counters (open count, close count) and two pruning
  conditions, rather than generating all 2^(2n) strings and filtering.
- Any "generate all combinations satisfying a running balance constraint"
  phrasing (parentheses, valid IP addresses, certain string construction
  problems) → same "counter-based pruning inside backtracking" idea.

COMMON MISTAKES:
1. Using `close < n` instead of `close < open` for Rule 2 — this would
   allow closing a bracket even when there's no unmatched open bracket
   waiting, producing invalid strings like ")(" at the very start.
2. Forgetting `curr.pop_back()` after either recursive call — without it,
   the string keeps accumulating characters across sibling branches, and
   later recorded "solutions" end up far longer than 2n and completely
   wrong.
3. Generating ALL 2^(2n) binary strings of '(' and ')' first and filtering
   for validity afterward — this technically works but wastes enormous time
   on strings that were doomed to be invalid from the very first character;
   the whole point of this pattern is pruning early instead of filtering late.

WHERE THIS SHOWS UP:
Generate Parentheses (LC 22) is a very frequently asked backtracking
question at Meta, Amazon, and Google — often used specifically to test
whether a candidate can invent the "two counters + two pruning conditions"
trick themselves, rather than defaulting to generate-then-filter, which
interviewers usually push back on as an inefficient first attempt.
================================================================================
*/









// approach 1
// class Solution {
// public:
//     vector<string> result;

//     bool isvalid(string& str) {
//         int count = 0;

//         for (char& ch : str) {
//             if (ch == '(')
//                 count++;
//             else
//                 count--;
//             if (count < 0)
//                 return false;
//         }
//         return count == 0;
//     }

//     void solve(string& curr, int n) {
//         if (curr.length() == 2 * n) {
//             if (isvalid(curr)) {
//                 result.push_back(curr);
//             }
//             return;
//         }

//         curr.push_back('(');
//         solve(curr, n);

//         curr.pop_back();

//         curr.push_back(')');
//         solve(curr, n);

//         curr.pop_back();
//     }

//     vector<string> generateParenthesis(int n) {
//         string curr = "";

//         solve(curr, n);
//         return result;
//     }
// };