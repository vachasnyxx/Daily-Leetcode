// class Solution {
// public:
//     vector<int> solve(string expression) {
//         vector<int> result;

//         for (int i = 0; i < expression.size(); i++) {
//             if (expression[i] == '+' || expression[i] == '-' ||
//                 expression[i] == '*') {
//                 vector<int> left_results = solve(expression.substr(0, i));
//                 vector<int> right_results = solve(expression.substr(i + 1));

//                 for (int& x : left_results) {
//                     for (int& y : right_results) {
//                         if (expression[i] == '+') {
//                             result.push_back(x + y);
//                         } else if (expression[i] == '-') {
//                             result.push_back(x - y);
//                         } else {
//                             result.push_back(x * y);
//                         }
//                     }
//                 }
//             }
//         }
//         if (result.empty()) {
//                 result.push_back(stoi(expression));
//             }
//             return result;
//     }
//     vector<int> diffWaysToCompute(string expression) {
//         return solve(expression);
//     }
// };






// ============================================================
// LeetCode 241 - Different Ways to Add Parentheses
// Pattern: DIVIDE AND CONQUER over ALL POSSIBLE SPLIT POINTS
// (a cousin of Matrix Chain Multiplication / Catalan Number problems)
// Difficulty: Medium (often FELT as Hard because of the recursion
// branching factor and lack of an obvious base case at first glance)
// ============================================================

class Solution {
public:

    // ------------------------------------------------------------
    // solve(expression) -- returns ALL possible results you can
    // get by placing parentheses in every possible valid way
    // around the operators in this expression string.
    // ------------------------------------------------------------
    //
    // CORE INTUITION -- "Try being the LAST operator to fire, one at a time":
    // Any fully-parenthesized version of an expression like "2-1-1"
    // has exactly ONE operator that gets evaluated LAST (the
    // outermost operation, e.g., in (2-1)-1 the last "-" is the
    // second one; in 2-(1-1) the last "-" is the first one).
    // So instead of trying to guess how to place parentheses, we
    // ask: "For EACH operator in this string, WHAT IF this one
    // was the last one to be evaluated?" That splits the string
    // into a LEFT half and a RIGHT half around that operator.
    // We then recursively ask the same question of each half
    // (they have their own "last operator" choices to make too),
    // and combine every possible left result with every possible
    // right result using that operator.
    vector<int> solve(string expression) {

        // This will collect EVERY possible numeric outcome for
        // this expression, across all valid parenthesizations.
        vector<int> result;

        // ---- TRY EVERY CHARACTER AS "the operator that fires last" ----
        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == '+' || expression[i] == '-' ||
                expression[i] == '*') {

                // This character is a candidate for "last operator".
                // Split the string into everything BEFORE it (left
                // sub-expression) and everything AFTER it (right
                // sub-expression), and recursively find ALL possible
                // results for each side independently.
                //
                // WHY THIS WORKS: whatever operator combination
                // produced the LEFT half's value doesn't affect
                // what combination produced the RIGHT half's value
                // -- they're independent sub-problems, so we can
                // solve them separately and later combine every
                // pairing (this is the "divide" and "conquer" of
                // divide-and-conquer).
                vector<int> left_results = solve(expression.substr(0, i));
                vector<int> right_results = solve(expression.substr(i + 1));

                // ---- COMBINE: cartesian product of left x right ----
                // For every possible left value and every possible
                // right value, apply THIS operator (since we assumed
                // it fires last) and record the outcome.
                // This nested loop is exactly why the result set
                // can grow large: it's every combination of every
                // way to compute the left, times every way to
                // compute the right.
                for (int& x : left_results) {
                    for (int& y : right_results) {
                        if (expression[i] == '+') {
                            result.push_back(x + y);
                        } else if (expression[i] == '-') {
                            result.push_back(x - y);
                        } else {
                            result.push_back(x * y);
                        }
                    }
                }
            }
        }

        // ---- BASE CASE: no operator found in this substring ----
        // If the loop above never found a '+', '-', or '*', it
        // means `expression` is a PURE NUMBER (e.g., "12", "3").
        // There's nothing left to split -- this substring IS a
        // leaf of our recursion tree. Convert it directly to an
        // integer and treat it as the (only) possible result.
        //
        // NOTE: this check happens AFTER the loop, using the fact
        // that `result` would still be empty if no operator was
        // ever found (since the loop only pushes into `result`
        // when it hits an operator character).
        if (result.empty()) {
                result.push_back(stoi(expression));
            }
        return result;
    }

    // ------------------------------------------------------------
    // diffWaysToCompute(expression) -- the LeetCode entry point.
    // Just kicks off the recursion on the full expression string.
    // ------------------------------------------------------------
    vector<int> diffWaysToCompute(string expression) {
        return solve(expression);
    }
};

/*
============================================================
REVISION SUMMARY (read this when you forget everything else)
============================================================

WHAT IS THIS PROBLEM?
Given a string like "2-1-1" containing digits and the operators
+, -, *, return ALL possible results you could get by inserting
parentheses in every valid way and evaluating. For "2-1-1" the
two valid parenthesizations are ((2-1)-1) = 0 and (2-(1-1)) = 2,
so the answer is [0, 2] (order doesn't matter).

ANALOGY - "Auditioning every operator for the role of 'last to fire'":
Imagine the expression as a row of dominoes with operators as
hinges between number-tiles. To fully evaluate the expression,
EXACTLY one operator must be the "final blow" -- the last
computation that produces the overall answer. Your code holds
an audition: it walks past every operator in the string and
asks "what if YOU were the last one to fire?" For each candidate,
it slices the string into a left half and a right half around
that operator, and recursively holds the SAME audition inside
each half (because each half has its own "which operator fires
last, locally" question to answer). This is Divide and Conquer:
break the big decision into independent smaller decisions, solve
each independently, then combine every possible pairing.

WHY THIS DIFFERS FROM YOUR LAST TWO PROBLEMS:
- Josephus (LC 1823): recursion builds the answer for `n` using
  ONE known answer for `n-1` -- a single linear chain of calls.
- Integer to Words (LC 273): recursion peels off ONE clear chunk
  (biggest scale) at a time -- also a single, non-branching path
  per call (though multiple sibling calls exist per level).
- THIS problem: recursion BRANCHES at every single operator
  found in the string, and each branch itself branches further.
  This is a fundamentally different shape -- an exploration tree
  of "all possible choices," not a single deterministic path.
  Recognizing this shape (try every choice point, recurse on
  both resulting pieces, combine results) is the real skill here.

DRY RUN EXAMPLE: diffWaysToCompute("2-1-1")
- solve("2-1-1"):
  - i=1, expression[1] = '-' (the FIRST minus). Split into
    left = solve("2") = [2], right = solve("1-1").
      solve("1-1"): i=1 is '-'. left=solve("1")=[1], right=solve("1")=[1].
                    Combine: 1-1 = 0. So solve("1-1") = [0].
    Combine left=[2] with right=[0] using '-': 2 - 0 = 2.
    -> contributes 2 to result.
  - i=3, expression[3] = '-' (the SECOND minus). Split into
    left = solve("2-1"), right = solve("1").
      solve("2-1"): i=1 is '-'. left=solve("2")=[2], right=solve("1")=[1].
                    Combine: 2-1 = 1. So solve("2-1") = [1].
    Combine left=[1] with right=[1] using '-': 1 - 1 = 0.
    -> contributes 0 to result.
  - Final result = [2, 0] (matches expected output {0, 2}, order
    may vary since we don't sort).

TIME COMPLEXITY: Exponential -- roughly O(4^n / n^1.5), tied to
  the nth Catalan number, where n is roughly the number of
  operators in the expression.
  WHY EXPONENTIAL: every operator creates a branching split, and
  the SAME substring can get recomputed multiple times across
  different branches of the recursion tree (e.g., solve("2-1")
  might be recomputed independently in different recursive paths
  for longer expressions). There's no memoization here, so
  overlapping subproblems are solved from scratch every time.
  (You could optimize with a hash map cache keyed by substring
  to avoid recomputation -- a good follow-up exercise: convert
  this into Divide and Conquer + Memoization.)

SPACE COMPLEXITY: Also exponential in the worst case, dominated
  by the number of results being stored across all the vectors
  created at every recursion level (each level's result vector
  can hold up to Catalan(n) entries), plus the recursion call
  stack itself which is O(n) deep at most.

COMMON MISTAKES WITH THIS PATTERN:
1. Trying to find "the base case" by checking string length
   instead of checking "did I find zero operators." A pure
   number can be multi-digit (e.g., "23"), so checking for a
   single character as the base case is WRONG -- the correct
   check is "no operator characters were found at all."
2. Forgetting this problem has NO operator precedence rules to
   worry about -- unlike normal math, you don't need to handle
   "*" before "+"; every possible parenthesization is considered
   equally valid, so you don't special-case operator priority.
3. Not realizing the exponential blowup risk. Some students
   assume this is "just recursion" and don't recognize that
   without memoization, the same substring is being fully
   re-solved many times over -- leading to Time Limit Exceeded
   on very long expressions with many operators.

TRIGGER WORDS TO SPOT THIS PATTERN:
"all possible results," "every way to parenthesize/group," "all
ways to compute," "different orders of evaluation" -- these
scream "Divide and Conquer: split at every choice point, combine
results from both sides." This pattern-family is closely related
to Matrix Chain Multiplication and Catalan Number / "unique BST"
style problems (LC 96), since the branching structure -- trying
every possible split point -- is identical.

WHERE THIS PATTERN SHOWS UP:
This exact problem has been referenced in interview prep material
associated with Google and LinkedIn as a test of whether a
candidate can recognize "branching divide and conquer" versus
plain linear recursion, and whether they proactively spot and
fix the exponential recomputation with memoization when asked
to optimize.
============================================================
*/









