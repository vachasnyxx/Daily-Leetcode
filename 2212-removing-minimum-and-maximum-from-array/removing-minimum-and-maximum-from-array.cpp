// class Solution {
// public:
//     int minimumDeletions(vector<int>& nums) {
//         int n = nums.size();

//         int minElIdx = min_element(begin(nums), end(nums)) -  begin(nums);
//         int maxElIdx = max_element(begin(nums), end(nums)) -  begin(nums);

//         int left = min(minElIdx,maxElIdx);
//         int right = max(minElIdx,maxElIdx);

//         return min({left + 1 + n - right,  right + 1, n - left});
//     }
// };



class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        // Step 1: Locate WHERE (not what) the minimum and maximum values live.
        // We only care about their POSITIONS because deletions in this problem
        // are only allowed from the FRONT or the BACK of the array (like peeling
        // a rope from both ends) — never from the middle.
        int minElIdx = min_element(begin(nums), end(nums)) - begin(nums);
        int maxElIdx = max_element(begin(nums), end(nums)) - begin(nums);

        // Step 2: Normalize so we don't care which one (min or max) came first
        // in the array. 'left' is whichever of the two indices is smaller,
        // 'right' is whichever is bigger. This collapses 2 cases into 1 logic path.
        int left  = min(minElIdx, maxElIdx);
        int right = max(minElIdx, maxElIdx);

        // Step 3: There are exactly THREE physically possible ways to remove
        // both the min and max using only front/back trims. We compute the
        // deletion cost of each strategy and pick the cheapest.

        // Strategy A — "Trim only from the FRONT":
        // To remove both target elements by chopping from the front only,
        // you must chop everything up to and including the LATER index (right).
        // Cost = right + 1  (indices 0..right, that's right+1 elements)

        // Strategy B — "Trim only from the BACK":
        // To remove both by chopping from the back only, you must chop
        // everything from the EARLIER index (left) to the end.
        // Cost = n - left  (indices left..n-1, that's n-left elements)

        // Strategy C — "Trim a bit from BOTH ends":
        // Chop the front up through 'left' (left+1 elements) AND
        // chop the back from 'right' to the end (n-right elements).
        // These two chunks never overlap because left < right, so it's safe to add them.
        // Cost = (left + 1) + (n - right)

        return min({ left + 1 + n - right,   // Strategy C: both ends
                      right + 1,             // Strategy A: front only
                      n - left });           // Strategy B: back only
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
You can only delete from the front or the back of the array (never the middle).
Find the minimum deletions needed so that BOTH the overall minimum and overall
maximum value get deleted.

ANALOGY — "Trimming a candle from both ends":
Imagine the array is a candle, and the min-value element and max-value element
are two wax markings drawn on it at certain positions. You're only allowed to
burn (trim) the candle from the LEFT tip or the RIGHT tip. You want both markings
burned away using the least total wax. You have exactly 3 burning strategies:
  1. Burn only from the left, until you pass the farther marking.
  2. Burn only from the right, until you pass the farther marking.
  3. Burn a little from BOTH tips — just enough on each side to reach its
     nearer marking.
You try all 3 and keep the cheapest.

WHY 'left' AND 'right' MATTER, NOT THE VALUES:
The moment you find WHERE the min and max sit (their indices), the actual
values become irrelevant — the rest of the problem is pure INDEX ARITHMETIC.
This is the biggest "aha" of this problem: it looks like an array-values
problem but is actually a positions/geometry problem.

DRY RUN (tiny example):
nums = [5, 3, 2, 4, 1, 7]   (n = 6)
min value = 1 at index 4        max value = 7 at index 5
left = min(4,5) = 4              right = max(4,5) = 5

Strategy A (front only):  right + 1        = 5 + 1 = 6
Strategy B (back only):   n - left         = 6 - 4 = 2
Strategy C (both ends):   (left+1)+(n-right) = 5 + 1 = 6

Answer = min(6, 2, 6) = 2
Check: deleting the last 2 elements {1, 7} removes both the min and max. Correct!

TIME COMPLEXITY: O(n) — one linear scan each for min_element and max_element
(each is a single pass, so still O(n) total, not O(n^2)).
SPACE COMPLEXITY: O(1) — only a handful of index variables, no extra array/map.

TRIGGER WORDS for this pattern (index-based front/back trimming):
- "remove elements only from the front or back"
- "delete a prefix and/or suffix"
- "minimum deletions to remove specific elements" when deletions are restricted
  to array ends (this rules out plain hashing/two-pointer sweep patterns and
  should make you think: "convert values to INDICES, then it's pure arithmetic
  over 3 fixed cases").

COMMON MISTAKES:
1. Forgetting min_element/max_element return ITERATORS, not values — forgetting
   the "- begin(nums)" to convert to an index is the #1 bug here.
2. Trying to handle "min comes before max" and "max comes before min" as two
   separate code branches instead of just normalizing with min()/max() into
   left/right — this doubles your code for no reason.
3. Miscounting Strategy C by forgetting that removing index 'left' from the
   front already deletes it, so the back removal should start strictly AFTER
   'right', giving (n - right) elements, not (n - right - 1). Off-by-one here
   is extremely common — always sanity check with a tiny dry run like above.

WHERE THIS TYPE OF QUESTION SHOWS UP:
This exact problem (LC 2091) has been reported in interview experience threads
for Amazon and in general OA (online assessment) rounds for product-based
companies — it's a favorite because it LOOKS like a two-pointer/sliding-window
problem but is actually solved with plain index math and case analysis, which
tests whether you jump to a "fancy" pattern too early instead of just reasoning
from first principles.
================================================================================
*/