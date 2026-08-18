// class Solution {
// public:

//     bool possibleHai(vector<int>& time, long long givenTime, int totalTrips){
//         long long actualTrips = 0;  // kitna cover ho payega 

//         for(int &t: time){
//             actualTrips += givenTime/t; // number of trips har bus k
//         }

//         return actualTrips >= totalTrips;
//     }

//     long long minimumTime(vector<int>& time, int totalTrips) {
//         int n = time.size();

//         long long l = 1;
//         long long r = (long long) *min_element(begin(time),end(time)) * totalTrips;

//         while(l < r){
//             long long mid_time = l + (r - l)/2;

//             if(possibleHai(time,mid_time,totalTrips)) {
//                 r = mid_time;
//             }
//             else{
//                 l = mid_time +1;
//             }
//         }
//         return l;
//     }
// };





class Solution {
public:
    // ============================================================================
    // HELPER FUNCTION: possibleHai()
    // ============================================================================
    // Purpose: Check if, given 'givenTime' amount of time, all buses COMBINED
    //          can complete at least 'totalTrips' trips.
    //
    // Intuition: Each bus works INDEPENDENTLY and SIMULTANEOUSLY (parallel, not
    //            sequential like the ship problem!). 
    //            - Bus with time[i] minutes per trip can make (givenTime / time[i])
    //              COMPLETE trips in 'givenTime' minutes.
    //            - We SUM UP trips from all buses to get total trips possible.
    //            - If that sum >= totalTrips required, this much time is ENOUGH.
    //
    // Parameters:
    //   - time: array where time[i] = minutes bus i takes to complete ONE trip
    //   - givenTime: the amount of time we're TESTING (is this enough?)
    //   - totalTrips: minimum trips required across all buses combined
    //
    // Returns: true if 'givenTime' is SUFFICIENT to complete totalTrips, false otherwise.
    // ============================================================================
    bool possibleHai(vector<int>& time, long long givenTime, int totalTrips) {
        long long actualTrips = 0;  // Running total: kitna cover ho payega (how many trips get covered)

        // Go through each bus and calculate how many FULL trips it can make
        for (int &t : time) {
            // Integer division gives us COMPLETE trips only.
            // Example: if givenTime = 10 and t = 3, bus completes 3 full trips (9 mins used),
            // the 4th trip (would need 3 more mins) doesn't count as it's INCOMPLETE.
            actualTrips += givenTime / t;

            // MICRO-OPTIMIZATION (not in your code, but good to know):
            // You could early-exit here if actualTrips >= totalTrips already,
            // to avoid unnecessary iterations. Not required, but speeds up large inputs.
        }

        // Check if total trips achieved by ALL buses meets/exceeds the requirement
        return actualTrips >= totalTrips;
    }

    // ============================================================================
    // MAIN FUNCTION: minimumTime()
    // ============================================================================
    // Problem: Given multiple buses each taking time[i] minutes per trip, running
    //          IN PARALLEL, find the MINIMUM total time needed so that the
    //          COMBINED number of trips across all buses reaches 'totalTrips'.
    //
    // PATTERN: BINARY SEARCH ON ANSWER
    //
    // WHY BINARY SEARCH ON ANSWER?
    // -----------------------------
    // 1. SEARCH RANGE is well-defined:
    //    - Lower bound (l): 1 minute (technically could be 0, but 1 is safe/valid start)
    //    - Upper bound (r): fastest_bus_time * totalTrips
    //      → If ONLY the fastest bus ran alone, this is the worst-case time needed
    //        to hit totalTrips. The real answer (with all buses helping) will be
    //        <= this, since more buses only ADD more trips, never fewer.
    //
    // 2. MONOTONICITY PROPERTY:
    //    - If 'givenTime' minutes is enough to complete totalTrips, then ANY time
    //      LARGER than givenTime is also enough (more time = more trips possible).
    //    - If 'givenTime' is NOT enough, any SMALLER time is also not enough.
    //    - Pattern looks like: [NO, NO, NO, ..., YES, YES, YES, ...]
    //      This monotonic boolean behavior = perfect binary search candidate!
    //
    // 3. We want the MINIMUM time where possibleHai() first becomes TRUE.
    //    This uses the "first TRUE" binary search template (l < r, converge to l).
    //
    // TIME COMPLEXITY: O(n * log(fastest_bus_time * totalTrips))
    //   - n = number of buses (checked in every possibleHai() call)
    //   - log(range) = number of binary search iterations
    // SPACE COMPLEXITY: O(1) - only a few variables used
    // ============================================================================
    long long minimumTime(vector<int>& time, int totalTrips) {
        int n = time.size();  // Number of buses

        // ========================================================================
        // STEP 1: Define search range [l, r]
        // ========================================================================
        long long l = 1;
        // Lower bound: smallest possible time (1 minute). We know 0 trips can be
        // done in 0 time, but we need totalTrips >= 1, so start search from 1.

        long long r = (long long) *min_element(begin(time), end(time)) * totalTrips;
        // Upper bound: time taken if ONLY the FASTEST bus did ALL the trips alone.
        // This is a guaranteed UPPER LIMIT because with other (slower) buses also
        // helping in parallel, the real answer will be <= this value.
        // We cast to long long to avoid overflow (totalTrips can be large, up to 1e7,
        // and bus time up to 1e5 → product can exceed INT_MAX).

        // ========================================================================
        // STEP 2: Binary Search on the Answer
        // ========================================================================
        // Using "l < r" template here (instead of "l <= r") because we're
        // converging to find the exact minimum boundary point, and 'l' will
        // naturally land on the answer when the loop ends.
        while (l < r) {
            // Calculate mid-point safely (avoids overflow vs (l+r)/2)
            long long mid_time = l + (r - l) / 2;

            // ====================================================================
            // STEP 3: Test if 'mid_time' minutes is ENOUGH to complete totalTrips
            // ====================================================================
            if (possibleHai(time, mid_time, totalTrips)) {
                // CASE A: mid_time IS enough (feasible)
                // ----------------------------------------
                // This could be our answer, but maybe a SMALLER time also works.
                // So we shrink the search space to the LEFT half (including mid_time).
                r = mid_time;
                // Note: r = mid_time (NOT mid_time - 1) because mid_time itself
                // is a VALID candidate answer — we don't want to exclude it!
            } 
            else {
                // CASE B: mid_time is NOT enough (infeasible)
                // ----------------------------------------------
                // We definitely need MORE time than mid_time.
                // Search the RIGHT half, EXCLUDING mid_time (since it failed).
                l = mid_time + 1;
            }
        }

        // ========================================================================
        // STEP 4: Return the answer
        // ========================================================================
        // When loop ends, l == r, and this value is the MINIMUM time where
        // possibleHai() becomes true for the first time.
        return l;
    }
};

/*
 * ================================================================================
 * COMPLETE LOGIC SUMMARY (For Quick Revision)
 * ================================================================================
 *
 * PROBLEM INTUITION:
 * ------------------
 * You have several buses. Each bus takes a fixed amount of time to complete ONE
 * trip, and all buses run SIMULTANEOUSLY (in parallel, non-stop, forever).
 * Find the MINIMUM total time needed so that the SUM of all trips made by ALL
 * buses combined reaches at least 'totalTrips'.
 *
 * KEY DIFFERENCE FROM THE SHIP PROBLEM:
 * --------------------------------------
 * - Ship problem: SEQUENTIAL work (one ship, one day at a time, packages in order)
 * - This problem: PARALLEL work (multiple buses running AT THE SAME TIME,
 *   independently contributing trips)
 * Even though both use Binary Search on Answer, the "check" function's logic
 * differs based on whether work happens in sequence or in parallel.
 *
 * ================================================================================
 * REAL-WORLD ANALOGY: The Multi-Bus Depot 🚌🚌🚌
 * ================================================================================
 * Imagine you own a bus depot with 3 buses:
 *   - Bus A: completes 1 trip every 2 minutes (fast bus)
 *   - Bus B: completes 1 trip every 5 minutes (medium bus)
 *   - Bus C: completes 1 trip every 10 minutes (slow bus)
 *
 * Your boss says: "I need AT LEAST 10 trips completed total (from all buses
 * combined). What's the MINIMUM time needed?"
 *
 * All 3 buses start running AT THE SAME TIME, non-stop, in a loop.
 * You don't manually assign trips — each bus just keeps looping on its own.
 *
 * If you wait 10 minutes:
 *   - Bus A: 10/2 = 5 trips
 *   - Bus B: 10/5 = 2 trips
 *   - Bus C: 10/10 = 1 trip
 *   - Total = 8 trips → NOT ENOUGH (need 10)
 *
 * If you wait 12 minutes:
 *   - Bus A: 12/2 = 6 trips
 *   - Bus B: 12/5 = 2 trips (2.4 rounds down, incomplete trip doesn't count)
 *   - Bus C: 12/10 = 1 trip
 *   - Total = 9 trips → STILL NOT ENOUGH
 *
 * If you wait 14 minutes:
 *   - Bus A: 14/2 = 7 trips
 *   - Bus B: 14/5 = 2 trips
 *   - Bus C: 14/10 = 1 trip
 *   - Total = 10 trips → ENOUGH! ✓
 *
 * So instead of manually testing 10, 11, 12, 13, 14 one by one (linear search,
 * SLOW), we use BINARY SEARCH to jump straight to the answer efficiently,
 * because the pattern [NOT ENOUGH, NOT ENOUGH, ..., ENOUGH, ENOUGH, ...] is
 * MONOTONIC (once enough time passes, it stays enough forever).
 *
 * ================================================================================
 * WHY UPPER BOUND = fastest_bus_time * totalTrips?
 * ================================================================================
 * Think of it as the WORST-CASE scenario: "What if ONLY the fastest bus existed,
 * and it had to do ALL the trips completely alone?"
 * Time needed = fastest_time * totalTrips (since it needs that many trips solo).
 *
 * Since OTHER buses also contribute trips in parallel, the REAL answer (with
 * all buses helping) will ALWAYS be <= this worst-case value. This makes it a
 * mathematically SAFE and TIGHT upper bound for the binary search range.
 *
 * ================================================================================
 * DRY RUN EXAMPLE (Tiny Case):
 * ================================================================================
 * time = [1, 2, 3], totalTrips = 5
 *
 * l = 1, r = min(1,2,3) * 5 = 1 * 5 = 5
 *
 * Iteration 1: l=1, r=5, mid = 1 + (5-1)/2 = 3
 *   possibleHai(3): trips = 3/1 + 3/2 + 3/3 = 3 + 1 + 1 = 5 >= 5 → TRUE
 *   → r = 3 (mid_time is a valid candidate, try smaller)
 *
 * Iteration 2: l=1, r=3, mid = 1 + (3-1)/2 = 2
 *   possibleHai(2): trips = 2/1 + 2/2 + 2/3 = 2 + 1 + 0 = 3 >= 5? → FALSE
 *   → l = mid+1 = 3
 *
 * Now l=3, r=3 → loop ends (l < r is false)
 *
 * ANSWER: 3 minutes
 * Verify: At t=3, Bus1 makes 3 trips, Bus2 makes 1 trip, Bus3 makes 1 trip = 5 total ✓
 * At t=2, only 3 trips total (not enough) — confirms 3 is indeed the MINIMUM.
 *
 * ================================================================================
 * TRIGGER WORDS FOR THIS SPECIFIC VARIANT (Parallel Binary Search on Answer):
 * ================================================================================
 * Look for these clues in problem statements:
 *   - "Multiple workers/machines/buses work SIMULTANEOUSLY/in PARALLEL"
 *   - "Find the MINIMUM time such that COMBINED output reaches X"
 *   - "Each unit produces/completes work at a fixed RATE"
 *   - The check function involves SUMMING (givenTime / rate) across all units
 *
 * Common problems using this exact parallel-rate variant:
 *   - LeetCode 2187: Minimum Time to Complete Trips (this problem)
 *   - LeetCode 1870: Minimum Speed to Arrive on Time
 *   - LeetCode 1552: Magnetic Force Between Two Balls (slightly different check logic)
 *   - LeetCode 1552, 875 (Koko Eating Bananas) — same FAMILY, different check()
 *
 * ================================================================================
 * COMMON MISTAKES TO AVOID:
 * ================================================================================
 * 1. Using INT instead of LONG LONG: totalTrips can be up to 1e7 and time[i] up
 *    to 1e5, so r can be up to 1e12 — WAY beyond int range (max ~2.1 * 1e9).
 *    Always use long long for time-based binary search bounds!
 *
 * 2. Off-by-one with r = mid_time vs r = mid_time - 1:
 *    Since mid_time itself COULD be the answer (it's a valid feasible point),
 *    we must NOT exclude it → use r = mid_time, not mid_time - 1.
 *    (Contrast this with problems using l <= r template, where boundaries differ.)
 *
 * 3. Confusing this with the SHIP problem: In ship problem, buses/ships work
 *    SEQUENTIALLY (one at a time, days count up). Here, buses work in PARALLEL
 *    (simultaneously). This changes how you write the check() function —
 *    here it's a SUM of independent contributions, not a simulation with resets.
 *
 * 4. Forgetting integer division truncates: givenTime/t gives only COMPLETE
 *    trips. A bus that's 90% done with a trip contributes 0 to the count for
 *    that trip — it must FULLY finish to count.
 *
 * ================================================================================
 * TIME & SPACE COMPLEXITY:
 * ================================================================================
 * Time: O(n * log(minTime * totalTrips))
 *   - n = number of buses (checked inside possibleHai() every iteration)
 *   - log(range) = number of binary search steps, where range = r - l
 *   - Example: if r ~ 1e12, log2(1e12) ≈ 40 iterations → very fast even for
 *     huge inputs
 *
 * Space: O(1)
 *   - Only a handful of long long/int variables used, no extra arrays
 *
 * ================================================================================
 * QUICK COMPARISON: SHIP PROBLEM vs BUS TRIPS PROBLEM
 * ================================================================================
 * | Aspect              | Ship Capacity (Seq.)      | Bus Trips (Parallel)        |
 * |---------------------|---------------------------|------------------------------|
 * | Work Type           | Sequential (one at a time)| Parallel (all simultaneously)|
 * | check() logic       | Simulate loading/resets   | Sum independent trip counts  |
 * | Search variable     | Capacity                  | Time                         |
 * | Lower bound         | max(weights)              | 1                            |
 * | Upper bound         | sum(weights)               | min(time) * totalTrips       |
 * | Loop template       | l <= r, high = mid-1       | l < r, r = mid               |
 * ================================================================================
 */