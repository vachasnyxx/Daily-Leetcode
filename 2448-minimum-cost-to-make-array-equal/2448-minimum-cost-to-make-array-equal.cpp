// class Solution {
// public:
//     typedef long long ll;

//     ll findCost(vector<int>& nums,vector<int>& cost,int target){
//         ll result = 0;

//         for(int i = 0; i< nums.size(); i++){
//             result += (ll) abs(nums[i] - target) * cost[i];
//         }
//         return result;
//     }

//     long long minCost(vector<int>& nums, vector<int>& cost) {
//         ll answer = INT_MAX;


//         ll left = *min_element(begin(nums),end(nums));
//         ll right = *max_element(begin(nums),end(nums));


//         while(left <= right){
//             int mid = left + (right - left)/2;

//             ll cost1 = findCost(nums, cost,mid);
//             ll cost2 = findCost(nums, cost,mid+1);

//             answer = min(cost1,cost2);

//             if(cost2 > cost1){
//                 right  = mid - 1;
//             }
//             else{
//                 left = mid + 1;
//             }
//         }
//         return answer == INT_MAX ? 0 : answer;
//     }
// };


// ============================================================================
// LeetCode 2448: Minimum Cost to Make Array Equal
// PATTERN: Ternary Search via Binary Search Logic (searching on a CONVEX function)
//        + Weighted Absolute Difference Sum (cost function)
// ============================================================================
//
// PROBLEM RECAP (the "story"):
// You're given an array nums and a parallel array cost, where cost[i] is the
// price to change nums[i] by 1 unit (up or down). You want to pick a SINGLE
// target value T such that if you change EVERY element nums[i] to T, the
// TOTAL cost (sum of |nums[i] - T| * cost[i] for all i) is MINIMIZED.
//
// Imagine you're a city planner again, but this time you're choosing where
// to build a SINGLE central warehouse (the target value T) along a straight
// highway. Each house (nums[i]) is located at some position on the highway,
// and each house has a different "delivery frequency" (cost[i]) — how often
// trucks need to travel between the warehouse and that house. The cost to
// serve a house is proportional to the DISTANCE from the warehouse times
// the delivery frequency. You want to place the warehouse at the position
// that MINIMIZES the total delivery cost across all houses.
//
// THE KEY INSIGHT (memorize this):
// The total cost function f(T) = sum(|nums[i] - T| * cost[i]) is a CONVEX
// function (U-shaped, or more precisely, V-shaped with possible flat regions).
// It decreases as T approaches the "weighted median" of the nums, reaches
// a minimum at (or near) that median, then increases as T moves away.
//
// WHY CONVEX? Because each term |nums[i] - T| * cost[i] is itself a V-shaped
// function (absolute value scaled by cost[i]), and the sum of convex functions
// is always convex. This U-shape is what allows us to use a ternary-search-
// like approach (or binary search on the derivative, which is what comparing
// cost1 vs cost2 effectively does).

class Solution {
public:
    typedef long long ll;
    // Using long long because total cost can easily overflow 32-bit int
    // when nums and cost values are large (up to 10^6 or 10^9).

    // ------------------------------------------------------------------
    // findCost(nums, cost, target)
    // ------------------------------------------------------------------
    // STORY: You've picked a candidate warehouse location (target). Now
    // calculate the total delivery cost: for each house, multiply its
    // distance from the warehouse (|nums[i] - target|) by its delivery
    // frequency (cost[i]), and sum all these up.
    //
    // WHY O(n)? Because you have to visit every house once to compute its
    // contribution to the total cost. No clever formula can skip houses
    // here — this is the brute-force cost evaluation, but it's cheap enough
    // to run inside a binary/ternary search (O(n log(range))).
    // ------------------------------------------------------------------
    ll findCost(vector<int>& nums, vector<int>& cost, int target){
        ll result = 0;

        for(int i = 0; i < nums.size(); i++){
            // Cost for house i = distance * frequency.
            // Cast to long long to prevent overflow during multiplication.
            result += (ll) abs(nums[i] - target) * cost[i];
        }
        return result;
    }

    // ------------------------------------------------------------------
    // minCost(nums, cost)
    // ------------------------------------------------------------------
    // GOAL: Find the target value T that MINIMIZES the total weighted
    //       absolute difference cost.
    // ------------------------------------------------------------------
    long long minCost(vector<int>& nums, vector<int>& cost) {
        ll answer = INT_MAX;

        // ------------------------------------------------------------
        // SEARCH SPACE for the target T:
        //   - Lower bound (left): the smallest nums value — no reason to
        //     place the warehouse left of all houses; that would only
        //     increase distances unnecessarily.
        //   - Upper bound (right): the largest nums value — same logic,
        //     no reason to place it right of all houses.
        //   The optimal T is guaranteed to lie somewhere in [min(nums),
        //   max(nums)], inclusive.
        // ------------------------------------------------------------
        ll left = *min_element(begin(nums), end(nums));
        ll right = *max_element(begin(nums), end(nums));

        // ------------------------------------------------------------
        // TERNARY SEARCH VIA BINARY SEARCH LOGIC:
        // Normally, ternary search uses TWO midpoints (mid1 and mid2) to
        // decide whether to discard the left third, right third, or middle
        // third of the search space. Here, we use a clever shortcut:
        //   - Compute cost at mid and mid+1 (two adjacent points).
        //   - If cost(mid+1) > cost(mid), the function is INCREASING at
        //     mid, so the minimum must lie to the LEFT (including mid).
        //   - If cost(mid+1) <= cost(mid), the function is DECREASING or
        //     flat at mid, so the minimum must lie to the RIGHT (including
        //     mid+1).
        //
        // This works because the function is CONVEX — it has a single
        // global minimum (or a contiguous flat region of minima), and no
        // local minima to trap us. Comparing two adjacent points tells us
        // which "slope" we're on: descending toward the minimum, or
        // ascending away from it.
        // ------------------------------------------------------------
        while(left <= right){
            int mid = left + (right - left) / 2;

            ll cost1 = findCost(nums, cost, mid);
            ll cost2 = findCost(nums, cost, mid + 1);

            // Track the best (minimum) cost seen so far.
            answer = min(cost1, cost2);

            if(cost2 > cost1){
                // Function is INCREASING at mid (cost goes up as we move
                // right from mid to mid+1). The minimum must be to the
                // LEFT (or at mid itself). Discard the right half.
                right = mid - 1;
            }
            else{
                // Function is DECREASING or FLAT at mid (cost goes down or
                // stays same as we move right). The minimum must be to the
                // RIGHT (or at mid+1 itself). Discard the left half.
                left = mid + 1;
            }
        }

        // If answer was never updated (edge case: empty or single-element
        // arrays), return 0. Otherwise return the minimum cost found.
        return answer == INT_MAX ? 0 : answer;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: Find the target value T that minimizes the total weighted
// absolute difference cost, where each element nums[i] has a weight cost[i].
// The cost function is convex (U-shaped), so you can ternary-search (or
// binary-search-on-the-derivative) to find its minimum.
//
// THE FULL STORY (visualize this every time):
// You're placing a warehouse on a straight highway to minimize total
// delivery cost. Each house (nums[i]) is at some position on the highway,
// and each has a delivery frequency (cost[i]). The cost to serve a house
// is distance × frequency. The total cost function f(T) is convex: it
// decreases as you approach the "weighted median" of the houses, hits a
// minimum there, then increases as you move away. You binary/ternary search
// over possible warehouse positions, comparing costs at adjacent points to
// decide whether you're on the descending or ascending slope of the U-curve.
//
// WHY THIS IS TERNARY SEARCH (not classic binary search):
//   - Classic binary search requires a boolean monotonic property (true/false
//     boundary). Here, there's no true/false — we're minimizing a continuous
//     convex function.
//   - Ternary search is the standard technique for finding the minimum (or
//     maximum) of a unimodal/convex function: compare two points, discard
//     the third of the search space that can't contain the optimum.
//   - This implementation is a "binary search on the derivative" shortcut:
//     comparing f(mid) vs f(mid+1) tells us the sign of the slope at mid,
//     which is equivalent to deciding which half to discard in ternary
//     search. It's slightly cleaner to code than full ternary search with
//     two midpoints.
//
// TRIGGER WORDS for this pattern:
//   "minimize sum of weighted absolute differences", "find optimal target
//   value to minimize cost function", "convex / U-shaped cost function" =>
//   Think: Ternary search (or binary search on derivative), evaluating
//   cost at candidate points.
//
// KEY INSIGHT (memorize this forever):
//   The function f(x) = sum(|a[i] - x| * w[i]) is always CONVEX, where
//   a[i] are positions and w[i] are weights. Its minimum occurs at the
//   WEIGHTED MEDIAN of the a[i] values (the point where cumulative weight
//   from the left reaches half the total weight). You can either:
//     1. Ternary search over x (O(n log(range))), or
//     2. Sort by a[i], compute prefix sums of weights, and find the weighted
//        median directly (O(n log n) for sorting, then O(n) scan).
//   Method 1 (ternary search) is easier to code and less error-prone in
//   contests; Method 2 (weighted median) is more optimal theoretically
//   but requires careful handling of edge cases.
//
// COMPLEXITY:
//   - findCost(): O(n) — one linear pass to sum weighted distances.
//   - minCost(): O(log(range)) iterations, each O(n) => Total: O(n log(range)),
//     where range = max(nums) - min(nums).
//   - Space: O(1) extra — just a few scalar variables.
//
// COMMON MISTAKES (why they happen):
//   1. Forgetting to use long long for total cost — sum of |nums[i] - T| *
//      cost[i] can overflow 32-bit int easily, leading to silent wrong
//      answers.
//   2. Confusing this with classic binary search on answer — students
//      sometimes try to frame this as "is cost <= K?" feasibility, but
//      there's no monotonic true/false property here; it's a convex
//      minimization, not a feasibility boundary.
//   3. Using the arithmetic mean (average) instead of the weighted median —
//      the average minimizes sum of SQUARED differences (least squares),
//      NOT sum of absolute differences. For absolute differences, the
//      optimum is always the (weighted) median, never the mean.
//   4. Off-by-one in the search bounds — using left = 0 or right = 1e9
//      instead of [min(nums), max(nums)] works but wastes iterations;
//      tightening the bounds to the actual data range is both faster and
//      less prone to overflow.
//
// COMPANIES: This exact "convex cost minimization via ternary search"
// pattern shows up in Google, Amazon, and Microsoft OA/onsite rounds, and
// pairs naturally with:
//   - LC 2656: Minimize Maximum of Array (binary search on answer with
//     cascade simulation).
//   - LC 1802: Maximum Value at a Given Index (binary search on answer
//     with arithmetic sequence formula).
//   - Classic "weighted median" problems in competitive programming (e.g.,
//     Codeforces "Warehouse" or "Post Office" variants).
// Once you see "minimize sum of weighted |a[i] - x|" or "convex cost
// function", your brain should immediately reach for ternary search (or
// weighted median if you're comfortable with prefix sums of weights).
// ============================================================================



