// class Solution {
// public:

//     int canMakeMBouq(vector<int>& bloomDay,int mid , int k){
//         int bouqCount = 0;
//         int consecutive_count = 0;

//         for(int i = 0; i<bloomDay.size();i++){
//             if(bloomDay[i] <= mid){
//                 consecutive_count++;
//             }
//             else{
//                 consecutive_count = 0;
//             }

//             if(consecutive_count == k){
//                 bouqCount++;
//                 consecutive_count = 0;
//             }
//         }

//         return bouqCount;
//     }

//     int minDays(vector<int>& bloomDay, int m, int k) {
//         int n = bloomDay.size();

//         int start_day = 0;
//         int end_day = *max_element(begin(bloomDay),end(bloomDay));

//         int minDays = -1;
//         //O(n * log(max_day))
//         while( start_day <= end_day){        //log(max_day)
//             int mid = start_day + ( end_day - start_day)/2;

//             if(canMakeMBouq(bloomDay, mid, k) >= m){    // O(n)
//                 minDays = mid;

//                 end_day = mid-1;
//             }
//             else{
//                 start_day = mid + 1;
//             }
//         }
//         return minDays;
//     }
// };




class Solution {
public:
    // ============================================================================
    // HELPER FUNCTION: canMakeMBouq()
    // ============================================================================
    // Purpose: Given a specific day 'mid', check HOW MANY complete bouquets can
    //          be made, where each bouquet requires 'k' ADJACENT flowers that
    //          have ALL bloomed by day 'mid'.
    //
    // KEY RULE OF THE PROBLEM:
    //   - A flower i is "bloomed" if bloomDay[i] <= mid (the day we're testing).
    //   - A bouquet needs 'k' flowers that are ADJACENT in the original array
    //     AND all bloomed. You CANNOT skip a non-bloomed flower and still use
    //     the ones before/after it as one bouquet — the run must be CONTIGUOUS.
    //   - Once you use k adjacent bloomed flowers for one bouquet, you reset
    //     and start looking for the NEXT bouquet from the next flower onward
    //     (flowers can't be reused across bouquets).
    //
    // Intuition: This is a SLIDING WINDOW style scan combined with binary
    //            search on the answer. We walk through bloomDay left to right,
    //            counting how many bloomed flowers are CONSECUTIVE. The moment
    //            we hit 'k' consecutive bloomed flowers, that's ONE bouquet —
    //            we lock it in and reset the counter to look for the next batch.
    //
    // Parameters:
    //   - bloomDay: array where bloomDay[i] = the day flower i blooms
    //   - mid: the day we're TESTING ("has this day passed for flower i?")
    //   - k: number of ADJACENT bloomed flowers needed per bouquet
    //
    // Returns: the TOTAL number of complete bouquets makeable by day 'mid'.
    // ============================================================================
    int canMakeMBouq(vector<int>& bloomDay, int mid, int k) {
        int bouqCount = 0;           // Total bouquets successfully made so far
        int consecutive_count = 0;   // Current streak of adjacent bloomed flowers

        // Scan through every flower, left to right (order matters! adjacency)
        for (int i = 0; i < bloomDay.size(); i++) {
            // CHECK: Has flower i bloomed by day 'mid'?
            if (bloomDay[i] <= mid) {
                // YES → extend the current consecutive streak
                consecutive_count++;
            } else {
                // NO → flower i hasn't bloomed yet, this BREAKS the streak
                // Reset counter — any bouquet must use flowers that are ALL
                // bloomed AND adjacent, so a single non-bloomed flower "resets"
                // our progress toward the next possible bouquet
                consecutive_count = 0;
            }

            // CHECK: Have we accumulated EXACTLY k consecutive bloomed flowers?
            if (consecutive_count == k) {
                // YES → we have enough adjacent bloomed flowers for ONE bouquet!
                bouqCount++;              // Lock in this bouquet

                // Reset the streak to 0 so the NEXT k flowers (starting fresh)
                // count toward a DIFFERENT bouquet — flowers already used
                // can't be reused for another bouquet.
                consecutive_count = 0;
            }
        }

        // Return how many complete bouquets we managed to assemble by day 'mid'
        return bouqCount;
    }

    // ============================================================================
    // MAIN FUNCTION: minDays()
    // ============================================================================
    // Problem: Given n flowers with bloomDay[i] = day flower i blooms, find the
    //          MINIMUM day on which we can make 'm' bouquets, each requiring
    //          'k' ADJACENT bloomed flowers. Return -1 if impossible (m*k > n).
    //
    // PATTERN: BINARY SEARCH ON ANSWER
    //
    // WHY BINARY SEARCH ON ANSWER?
    // -----------------------------
    // 1. SEARCH RANGE (over DAYS, not speed/capacity this time):
    //    - Lower bound (start_day): 0 — technically could be min(bloomDay), but
    //      0 is a safe, simple starting point (no flowers bloomed yet at day 0
    //      if all bloomDay[i] >= 1, so canMakeMBouq would return 0 anyway).
    //    - Upper bound (end_day): max(bloomDay) — by this day, EVERY flower has
    //      bloomed, so this is the LATEST day we'd ever need to wait. Waiting
    //      any longer doesn't help since all flowers are already bloomed.
    //
    // 2. MONOTONICITY PROPERTY:
    //    - If day X allows making >= m bouquets, then ANY day > X ALSO allows
    //      it (more time = more flowers bloomed = more bouquets possible,
    //      NEVER fewer).
    //    - If day X doesn't allow enough bouquets, any day < X ALSO won't.
    //    - Pattern: [NO, NO, NO, ..., YES, YES, YES, ...] → perfect for binary search!
    //
    // 3. We want the MINIMUM day where canMakeMBouq() >= m first becomes true.
    //
    // EDGE CASE: If m * k > n (total flowers needed exceeds total flowers
    //            available), it's IMPOSSIBLE no matter how many days pass.
    //            This isn't explicitly checked in this code — but the binary
    //            search would naturally fail to find enough bouquets even at
    //            end_day = max(bloomDay), leaving minDays = -1 (sentinel value,
    //            never gets updated). It's still good practice to add an
    //            explicit early check: if ((long long)m * k > n) return -1;
    //
    // TIME COMPLEXITY: O(n * log(max_day))
    //   - n = number of flowers (scanned inside canMakeMBouq every iteration)
    //   - log(max_day) = number of binary search iterations
    // SPACE COMPLEXITY: O(1) - only a few variables used
    // ============================================================================
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();  // Total number of flowers

        // ========================================================================
        // STEP 1: Define search range [start_day, end_day]
        // ========================================================================
        int start_day = 0;  // Earliest day to test (before any flower blooms)

        int end_day = *max_element(begin(bloomDay), end(bloomDay));
        // Latest day to test: the day the LAST flower blooms.
        // By this point, ALL flowers have bloomed — this is the absolute
        // worst-case scenario, guaranteed to give the MAXIMUM possible
        // bouquet count (floor(n / k)).

        int minDays = -1;  // Sentinel value: stays -1 if 'm' bouquets are
                            // NEVER achievable even by end_day (impossible case)

        // O(n * log(max_day)) — overall time complexity
        while (start_day <= end_day) {  // log(max_day) iterations
            // Calculate mid-point safely (avoids overflow vs (start+end)/2)
            int mid = start_day + (end_day - start_day) / 2;

            // ====================================================================
            // STEP 2: Test if day 'mid' allows making AT LEAST 'm' bouquets
            // ====================================================================
            if (canMakeMBouq(bloomDay, mid, k) >= m) {  // O(n) check
                // CASE A: Day 'mid' gives us ENOUGH bouquets (>= m)
                // ------------------------------------------------
                // This is a valid answer, but maybe an EARLIER day also works.
                // Record it and search the LEFT half for a smaller day.
                minDays = mid;

                end_day = mid - 1;  // Try to find an even earlier valid day
            } else {
                // CASE B: Day 'mid' does NOT give enough bouquets (< m)
                // --------------------------------------------------------
                // We need to wait LONGER for more flowers to bloom.
                // Search the RIGHT half for a later day.
                start_day = mid + 1;
            }
        }

        // ========================================================================
        // STEP 3: Return the answer
        // ========================================================================
        // If minDays is still -1, it means even waiting until the LAST flower
        // blooms (end_day) couldn't produce 'm' bouquets → truly IMPOSSIBLE.
        // Otherwise, minDays holds the EARLIEST day that works.
        return minDays;
    }
};

/*
 * ================================================================================
 * COMPLETE LOGIC SUMMARY (For Quick Revision)
 * ================================================================================
 *
 * PROBLEM INTUITION:
 * ------------------
 * You have 'n' flowers in a row, each blooming on a specific day (bloomDay[i]).
 * You need to make 'm' bouquets, where EACH bouquet requires 'k' ADJACENT
 * flowers that have ALL bloomed. Find the EARLIEST day this becomes possible.
 *
 * KEY DIFFERENCE FROM PREVIOUS PROBLEMS:
 * ----------------------------------------
 * This is the FIRST problem in your series where the check function isn't
 * about SUMMING hours/trips — it's about counting CONSECUTIVE RUNS (like a
 * sliding window scan). The "adjacency" requirement is what makes this unique.
 *
 * ================================================================================
 * REAL-WORLD ANALOGY: The Flower Garland Maker 💐
 * ================================================================================
 * Imagine a garden with flowers planted in a STRAIGHT ROW (order matters!).
 * You're making garlands (bouquets), and each garland needs exactly 'k'
 * NEIGHBORING flowers that have all bloomed — you can't pick flower #3 and
 * flower #7 for the same garland if flower #5 between them hasn't bloomed yet
 * (they're not adjacent in an unbroken chain).
 *
 * As days pass, more flowers bloom. You want to know: what's the EARLIEST day
 * you'll have enough "unbroken chains" of k bloomed flowers to make m garlands?
 *
 * Walking along the row of flowers on a given day is like checking a string
 * of Christmas lights — you're looking for unbroken RUNS of "lit" (bloomed)
 * bulbs of length exactly k, and every time you find one, you "cut" that
 * segment out and keep looking for the next run in the remaining lights.
 *
 * ================================================================================
 * DRY RUN EXAMPLE (Tiny Case):
 * ================================================================================
 * bloomDay = [1, 10, 3, 10, 2], m = 3, k = 1
 *
 * start_day = 0, end_day = 10 (max bloom day)
 *
 * Let's directly test day = 3 (to see canMakeMBouq in action):
 *   i=0: bloomDay[0]=1 <= 3? YES → consecutive_count = 1
 *        consecutive_count == k(1)? YES → bouqCount = 1, reset to 0
 *   i=1: bloomDay[1]=10 <= 3? NO → consecutive_count = 0
 *   i=2: bloomDay[2]=3 <= 3? YES → consecutive_count = 1
 *        consecutive_count == k(1)? YES → bouqCount = 2, reset to 0
 *   i=3: bloomDay[3]=10 <= 3? NO → consecutive_count = 0
 *   i=4: bloomDay[4]=2 <= 3? YES → consecutive_count = 1
 *        consecutive_count == k(1)? YES → bouqCount = 3, reset to 0
 *
 *   Total bouqCount = 3 >= m(3)? YES → day 3 WORKS!
 *
 * Binary search would then try to find if an EARLIER day also works, narrowing
 * down until it confirms day 3 is indeed the MINIMUM valid day.
 *
 * ================================================================================
 * WHY THE CONSECUTIVE COUNT RESETS (Critical Detail):
 * ================================================================================
 * There are TWO reset triggers in the code, and BOTH matter:
 *
 * 1. Reset on a NON-BLOOMED flower (else branch):
 *    consecutive_count = 0;
 *    → This flower breaks the "chain" — any bouquet must be UNBROKEN adjacent
 *      flowers, so hitting a non-bloomed flower forces us to start counting
 *      from scratch for the NEXT potential bouquet.
 *
 * 2. Reset AFTER completing a bouquet (consecutive_count == k):
 *    consecutive_count = 0;
 *    → Once we've "used up" k flowers for one bouquet, those flowers are GONE
 *      (can't be reused). We start fresh from the very next flower to look
 *      for the NEXT bouquet's flowers.
 *
 * Missing EITHER of these resets leads to WRONG answers (either overcounting
 * bouquets by reusing flowers, or undercounting by not restarting properly).
 *
 * ================================================================================
 * TRIGGER WORDS FOR THIS PATTERN:
 * ================================================================================
 * Look for these clues in problem statements:
 *   - "Find the MINIMUM day/time such that a condition on ADJACENT/CONSECUTIVE
 *     elements is satisfied"
 *   - Mentions of "adjacent", "consecutive", "contiguous" combined with a
 *     day/threshold that determines element eligibility
 *   - The check function requires SCANNING with a running streak counter,
 *     not just a simple sum
 *
 * Common problems using this exact pattern:
 *   - LeetCode 1482: Minimum Number of Days to Make m Bouquets (this problem)
 *   - LeetCode 1231: Divide Chocolate (similar family, different check logic)
 *   - LeetCode 410: Split Array Largest Sum (similar family)
 *
 * ================================================================================
 * COMMON MISTAKES TO AVOID:
 * ================================================================================
 * 1. Forgetting to reset consecutive_count after completing a bouquet: This
 *    leads to OVERCOUNTING because the same flowers could be "reused" in your
 *    counting logic (even though logically each flower can only be in ONE
 *    bouquet).
 *
 * 2. Not checking the impossible case (m * k > n): If you need more total
 *    flowers than exist, it's impossible regardless of days. Always consider
 *    adding an explicit check: if ((long long)m * k > n) return -1; at the
 *    START of minDays(), before running binary search at all. This code
 *    relies on the sentinel value naturally staying -1, which works but is
 *    less explicit — good practice is to check this upfront.
 *
 * 3. Confusing "adjacent" with "any k bloomed flowers": A bouquet does NOT
 *    mean "any k flowers that have bloomed" — it means k CONSECUTIVE flowers
 *    in the array, all bloomed. This is the #1 source of confusion for this
 *    problem.
 *
 * 4. Wrong upper bound: end_day should be max(bloomDay), NOT some arbitrary
 *    large constant. By the time the slowest flower blooms, ALL flowers are
 *    bloomed — waiting longer never helps.
 *
 * ================================================================================
 * TIME & SPACE COMPLEXITY:
 * ================================================================================
 * Time: O(n * log(max_day))
 *   - n = number of flowers (scanned inside canMakeMBouq every iteration)
 *   - log(max_day) = number of binary search iterations
 *   - Example: if max_day = 1e9, log2(1e9) ≈ 30 iterations
 *
 * Space: O(1)
 *   - Only using a few integer variables (start_day, end_day, mid, bouqCount,
 *     consecutive_count)
 *
 * ================================================================================
 * QUICK COMPARISON: ALL FIVE BINARY SEARCH ON ANSWER PROBLEMS SO FAR
 * ================================================================================
 * | Aspect          | Ship Capacity | Bus Trips | Koko Bananas | Train Speed | Bouquets      |
 * |-----------------|---------------|-----------|--------------|-------------|---------------|
 * | Search Variable | Capacity      | Time      | Speed        | Speed       | Day           |
 * | Check Logic     | Simulate/reset| Sum trips | Sum ceil     | Sum ceil*   | Count runs    |
 * | Needs Adjacency?| No            | No        | No           | No          | YES (unique!) |
 * | Lower bound     | max(weights)  | 1         | 1            | 1           | 0             |
 * | Upper bound     | sum(weights)  | min*trips | max(piles)   | 1e7         | max(bloomDay) |
 * | Loop template   | l <= r        | l < r     | l < r        | l <= r      | l <= r        |
 * | Impossible case | N/A           | N/A       | N/A          | Returns -1  | Returns -1    |
 * ================================================================================
 */