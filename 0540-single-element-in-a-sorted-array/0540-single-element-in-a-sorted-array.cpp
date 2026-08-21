// class Solution {
// public:
//     int singleNonDuplicate(vector<int>& nums) {
//         int n = nums.size();

//         int l = 0;

//         int h = n - 1;

//         while (l < h) {
//             int mid = l + (h - l) / 2;
//             // right side mein even hai ya odd

//             bool is_even;

//             if ((h - mid) % 2 == 0) {
//                 is_even = true;
//             } else {
//                 is_even = false;
//             }

//             // check your bagal wala element (mid+1)

//             if (nums[mid] == nums[mid + 1]) {
//                 if (is_even) {
//                     l = mid + 2;
//                 } else {
//                     h = mid - 1;
//                 }
//             } else { // nums[mid] != nums[mid+1]   {,.,.,.,.,.a,b,b,c}
//                 if (is_even) {
//                     h = mid;
//                 } else {
//                     l = mid + 1;
//                 }
//             }
//         }
//         return nums[h];
//     }
// };






// ============================================================================
// LeetCode 540: Single Element in a Sorted Array
// PATTERN: Binary Search Exploiting INDEX PARITY (pairing invariant)
// ============================================================================
//
// PROBLEM RECAP: You're given a sorted array where every element appears
// EXACTLY TWICE, except for one element that appears ONLY ONCE. Find that
// single element. Must run in O(log n) time — so linear scan is out, and
// we need binary search, but the array isn't "sorted by value comparison
// to target" in the usual sense. Instead, we exploit a PARITY invariant.

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();

        int l = 0;
        int h = n - 1;

        // ------------------------------------------------------------
        // THE CORE INVARIANT (memorize this):
        // If there were NO single element, every duplicate pair would sit
        // at index positions (even, odd) — like (0,1), (2,3), (4,5), etc.
        // The single element BREAKS this pattern: everything to its LEFT
        // still pairs as (even, odd), but everything to its RIGHT flips to
        // pairing as (odd, even) — because the lone element shifted every
        // subsequent index by one.
        //
        // Example: [1,1,2,3,3,4,4,8,8]  (single = 2 at index 2)
        //   Index:   0 1 2 3 4 5 6 7 8
        //   Value:   1 1 2 3 3 4 4 8 8
        //   Left of single (indices 0-1):  pair starts at EVEN index (0).
        //   Right of single (indices 3-8): pairs start at ODD index (3,5,7).
        //
        // So our job boils down to: binary search for the BOUNDARY where
        // "pair starts at even index" flips to "pair starts at odd index".
        // The single element sits exactly at that boundary.
        // ------------------------------------------------------------

        while (l < h) {
            int mid = l + (h - l) / 2;

            // right side mein even hai ya odd
            // (Checking whether 'mid' is at an EVEN-style offset relative
            // to the current right boundary 'h'. This tells us how to
            // INTERPRET the mid/mid+1 comparison below, because the
            // "correct" pairing parity depends on where we are relative
            // to the still-shrinking search window, not the original array.)
            bool is_even;

            if ((h - mid) % 2 == 0) {
                is_even = true;
            } else {
                is_even = false;
            }

            // check your bagal wala element (mid+1)
            // (Compare mid with its right neighbor to see if they form a pair.)

            if (nums[mid] == nums[mid + 1]) {
                // mid and mid+1 ARE a pair. Now the question is: is this
                // pair sitting in the "correct" (pre-single) parity zone,
                // or has the parity already flipped (meaning the single
                // element is actually somewhere INSIDE this pair's region,
                // which would contradict them being equal — so it must be
                // that the single element is elsewhere)?
                if (is_even) {
                    // This pair is exactly where a normal pair SHOULD be
                    // (parity intact) => everything up to mid+1 is "clean",
                    // single element must be to the RIGHT of this pair.
                    // Skip past both paired elements.
                    l = mid + 2;
                } else {
                    // Parity already broken here, yet nums[mid]==nums[mid+1]
                    // still holds => the single element must be to the LEFT,
                    // shrink from the right side, excluding this pair.
                    h = mid - 1;
                }
            } else { // nums[mid] != nums[mid+1]   {,.,.,.,.,.a,b,b,c}
                // mid and mid+1 do NOT match — either mid IS the single
                // element, or the single element lies within [l, mid].
                if (is_even) {
                    // Parity says a pair SHOULD have started at mid, but it
                    // didn't (values differ) => the single element caused
                    // this mismatch and lies at or before mid. Keep mid in
                    // range (don't exclude it yet) — shrink h to mid.
                    h = mid;
                } else {
                    // Odd-parity zone with a mismatch => single element is
                    // strictly to the right of mid. Move l past mid.
                    l = mid + 1;
                }
            }
        }

        // When l == h, we've converged onto the single element's index.
        return nums[h];
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: In a sorted array where everything is paired up except one
// lone element, find that lone element in O(log n) by tracking how the
// "pair starts at even index" pattern shifts to "pair starts at odd index"
// right at the point where the single element sits.
//
// ANALOGY — "A dance floor pairing check":
// Imagine a line of dancers, sorted by height, where everyone has a partner
// standing right next to them — EXCEPT one person who came alone. Before
// the lone dancer, partners always start at even positions in the line
// (1st & 2nd, 3rd & 4th, ...). After the lone dancer, because they threw off
// the count by one, partners start at odd positions instead. You don't need
// to check every single pair — you can jump to the middle of the line, check
// if the pairing at that point still "looks normal" for where you are, and
// use that single check to decide whether to search the left half or the
// right half. That's exactly what the is_even flag encodes.
//
// WHY THIS IS BINARY SEARCH (not linear scan):
//   - At every step, checking nums[mid] vs nums[mid+1] combined with the
//     parity of the position tells us DEFINITIVELY which half the single
//     element is in — we NEVER need to check both halves.
//   - This "one comparison eliminates half the search space" property is
//     the defining signature of binary search, even though we're not
//     comparing against a target VALUE like classic binary search — we're
//     comparing against a STRUCTURAL invariant (parity of pairing).
//
// TRIGGER WORDS for this pattern:
//   "sorted array, every element appears twice except one", "find the
//   single/unique element in O(log n)" => Think: Binary search on index
//   PARITY, not value. This is a smaller, more specific cousin of general
//   binary-search-on-answer — the "answer space" here is just "left half or
//   right half of the array", determined by a parity check.
//
// SIMPLER MENTAL SHORTCUT (alternative framing, good for revision):
//   Force mid to always be EVEN (if mid is odd, decrement it by 1 first).
//   Then: if nums[mid] == nums[mid+1], the single element is to the RIGHT
//   (l = mid + 2); otherwise it's to the LEFT or AT mid (h = mid).
//   This avoids the is_even bookkeeping entirely and is often easier to
//   remember, though your version (checking parity relative to 'h') works
//   identically and is a valid alternative implementation.
//
// COMPLEXITY:
//   - Time: O(log n) — classic binary search halving.
//   - Space: O(1) extra.
//
// COMMON MISTAKES (why they happen):
//   1. Forgetting that the pairing parity is relative to the CURRENT search
//      window, not the ORIGINAL array indices — students sometimes hardcode
//      "even index = start of pair" globally, which breaks once the window
//      shrinks and the boundary logic (is_even here) is what fixes this.
//   2. Off-by-one when narrowing bounds — using h = mid - 1 or l = mid + 1
//      in the wrong branch collapses the search space too aggressively and
//      skips over the actual single element.
//   3. Forgetting the base invariant only holds while accessing mid+1 — if
//      mid = n-1, mid+1 is out of bounds, but since l < h in the loop
//      condition and mid is always < h, mid+1 is always safely <= h,
//      so this specific implementation is safe, but it's a mistake to
//      watch for when writing similar array-pairing problems from scratch.
//
// COMPANIES: This exact "index parity binary search" pattern shows up in
// Amazon and Google interview rounds, and pairs conceptually with:
//   - LC 1150-style "majority/frequency" array problems (different trick,
//     but same spirit of exploiting structural invariants instead of raw
//     value comparison).
//   - Any "find the odd one out in a sorted array of pairs" variant.
// Once you see "sorted array, all duplicates except one, O(log n)", your
// brain should immediately reach for parity-based binary search, not a
// linear XOR scan (which is O(n), valid for UNSORTED arrays but wasteful
// here since sorting gives us the parity structure for free).
// ============================================================================





