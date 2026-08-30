// class Solution {
// public:
//     vector<vector<int>> merge(vector<vector<int>>& intervals) {
//         int n = intervals.size();

//         sort(begin(intervals), end(intervals));

//         vector<vector<int>> result;

//         result.push_back(intervals[0]);

//         for (int i = 1; i < n; i++) {
//             if (intervals[i][0] < result.back()[1]) { // overlapping
//                 result.back()[1] = max(result.back()[1], intervals[i][1]);
//             } else {
//                 result.push_back(intervals[i]);
//             }
//         }
//         return result;
//     }
//     bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
//         // x axis
//         vector<vector<int>> hor;
//         // y axis
//         vector<vector<int>> vert;

//         for (auto& coordinates : rectangles) {
//             int x1 = coordinates[0];
//             int y1 = coordinates[1];
//             int x2 = coordinates[2];
//             int y2 = coordinates[3];

//             hor.push_back({x1, x2});
//             vert.push_back({y1, y2});
//         }

//         vector<vector<int>> result1 = merge(hor);
//         if (result1.size() >= 3)
//             return true;
//         vector<vector<int>> result2 = merge(vert);

//         return result1.size() >= 3 || result2.size() >= 3;
//     }
// };




class Solution {
public:
    // ---- Reused helper: same skeleton as LC 56 Merge Intervals ----
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();

        sort(begin(intervals), end(intervals));

        vector<vector<int>> result;
        result.push_back(intervals[0]);

        for (int i = 1; i < n; i++) {

            // IMPORTANT DEVIATION FROM CLASSIC MERGE INTERVALS:
            // Here we use STRICT '<' instead of '<=' for the overlap check.
            // This is NOT a bug — it's a deliberate adaptation, and it's the
            // whole crux of solving THIS problem correctly.
            //
            // In classic Merge Intervals, touching endpoints (e.g. [1,3] and
            // [3,5]) are treated as "overlapping" and get merged, because a
            // real-world interval like a meeting from 1-3 and one from 3-5
            // conceptually share that boundary moment.
            //
            // But here, the intervals represent a RECTANGLE'S projection
            // (shadow) onto the x-axis or y-axis. If one rectangle's shadow
            // ends exactly where another's begins (touching, not overlapping
            // in area), a straight cut CAN still be drawn right through that
            // exact touching coordinate without slicing through either
            // rectangle. So touching projections must be counted as
            // SEPARATE groups, not merged into one — hence strict '<'.
            if (intervals[i][0] < result.back()[1]) { // overlapping
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            } else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }

    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        // THE CORE INSIGHT OF THIS PROBLEM:
        // Forget the 2D grid entirely for a moment. Project every rectangle
        // straight down onto the x-axis (its horizontal footprint) and
        // straight sideways onto the y-axis (its vertical footprint).
        // A valid vertical cut line exists at any x-coordinate that ISN'T
        // covered by any rectangle's x-projection. Same logic for horizontal
        // cuts using y-projections.
        //
        // So the whole 2D "can I slice the grid into 3 sections" question
        // collapses into a 1D "how many disjoint merged groups do these
        // intervals form" question — which is EXACTLY the Merge Intervals
        // problem you already know.

        vector<vector<int>> hor;   // x-axis footprints [x1, x2] of each rectangle
        vector<vector<int>> vert;  // y-axis footprints [y1, y2] of each rectangle

        for (auto& coordinates : rectangles) {
            int x1 = coordinates[0];
            int y1 = coordinates[1];
            int x2 = coordinates[2];
            int y2 = coordinates[3];

            hor.push_back({x1, x2});
            vert.push_back({y1, y2});
        }

        // Merge the x-projections. If they collapse into 3 or more separate
        // (non-touching) groups, that means there are at least 2 clean gaps
        // between them — i.e., 2 valid vertical cuts, splitting the grid
        // into 3 sections, each guaranteed to contain at least one rectangle.
        vector<vector<int>> result1 = merge(hor);
        if (result1.size() >= 3)
            return true;   // early exit — no need to even check the y-axis

        // Only reached if horizontal cuts didn't work — try vertical cuts
        // (i.e., merge the y-projections and check the same condition).
        vector<vector<int>> result2 = merge(vert);

        return result1.size() >= 3 || result2.size() >= 3;
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Given non-overlapping rectangles placed on an n x n grid, determine if you
can make 2 horizontal cuts OR 2 vertical cuts (straight lines across the
whole grid) such that every one of the 3 resulting strips contains at least
one full rectangle.

ANALOGY — "Sunlight shadows and a guillotine":
Imagine shining a flashlight straight down onto the grid from directly
above — each rectangle casts a shadow strip onto the x-axis (its horizontal
span). Now imagine another flashlight shining sideways, casting shadows onto
the y-axis. A vertical guillotine blade can drop cleanly through any x
position that has NO shadow covering it. If the x-axis shadows merge into 3
or more separate, non-touching shadow-blocks, that means there are at least
2 clean gaps between them where the blade can drop — giving you your 2 cuts
and 3 sections. Same logic sideways for horizontal cuts using y-shadows.

WHY '<' INSTEAD OF '<=' — THE MOST IMPORTANT DETAIL HERE:
If two rectangles' shadows just TOUCH (one ends exactly where the next
begins) but don't actually overlap in area, the guillotine can still drop
right at that touching point — it doesn't need to slice through anything.
Using '<=' (classic Merge Intervals behavior) would incorrectly treat
touching shadows as one continuous block, hiding a perfectly valid cut spot
and potentially causing you to wrongly return false.

DRY RUN (tiny example showing why '<' matters):
Three rectangles whose x-projections TOUCH but don't overlap:
hor = [[0,2], [2,4], [4,6]]     (already sorted)

result = [[0,2]]
i=1: [2,4] → is 2 < result.back()[1]=2? NO (2 is not less than 2)
     → separate group → result = [[0,2],[2,4]]
i=2: [4,6] → is 4 < result.back()[1]=4? NO
     → separate group → result = [[0,2],[2,4],[4,6]]

Final: 3 separate groups → checkValidCuts returns true.
(If we'd used '<=' here instead, both merges would have fired, collapsing
everything into one group of size 1, and the function would have wrongly
returned false — a real cut opportunity would've been missed.)

TIME COMPLEXITY: O(m log m), where m = number of rectangles — dominated by
the sort inside merge(), called at most twice (once for x, once for y,
skipped if the x-check already returns true).
SPACE COMPLEXITY: O(m) for the hor, vert, and result vectors.

TRIGGER WORDS for this pattern:
- "rectangles don't overlap" + "make horizontal/vertical cuts" + "sections
  each containing at least one rectangle" → project each rectangle onto
  1D intervals per axis, then it's just Merge Intervals in disguise.
- Whenever a problem reduces a 2D geometry constraint to independent
  1D projections on each axis, think "can I just solve this with interval
  merging separately per axis and combine with OR/AND?"

COMMON MISTAKES:
1. Copy-pasting the standard '<=' Merge Intervals logic here without
   realizing touching (not truly overlapping) projections must be counted
   as separate groups in this specific problem — this is the #1 way to fail
   this exact question after having "known" Merge Intervals already.
2. Using AND instead of OR when combining the horizontal-groups check and
   vertical-groups check — the problem only needs ONE valid cut direction
   (horizontal OR vertical) to succeed, not both.
3. Checking for >= 2 merged groups instead of >= 3 — 2 cuts always produce
   3 sections, so the group count threshold must be 3, not 2 (an easy
   off-by-one since "2 cuts" and "3 groups" are easy to conflate).

WHERE THIS SHOWS UP:
LC 3394 is a fairly recent (2024-2025) Weekly Contest problem, and this
"project 2D rectangles onto two independent 1D interval sets, then merge"
reduction is a favorite technique in geometry-flavored OA (online
assessment) questions at companies like Google and Amazon, where recognizing
that a 2D constraint decomposes into two independent 1D interval problems is
exactly the kind of pattern-spotting these rounds are designed to test.
================================================================================
*/