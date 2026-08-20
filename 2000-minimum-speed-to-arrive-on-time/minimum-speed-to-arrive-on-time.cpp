// class Solution {
// public:
//     double Possible(vector<int>& dist, int mid_speed) {
//         double time = 0.0;

//         int n = dist.size();

//         for (int i = 0; i < n - 1; i++) {
//             double t = (double)(dist[i] / (double)mid_speed);
//             time += ceil(t);
//         }
//         time += (double)(dist[n - 1] / (double)mid_speed);
//         return time;
//     }
//     int minSpeedOnTime(vector<int>& dist, double hour) {
//         int l = 1;
//         int r = 1e7;

//         int min_speed = -1;

//         while (l <= r) {
//             int mid_speed = l + (r - l) / 2;

//             if (Possible(dist, mid_speed) <= hour) {
//                 min_speed = mid_speed;
//                 r = mid_speed - 1;
//             } else {
//                 l = mid_speed + 1;
//             }
//         }
//         return min_speed;
//     }
// };




class Solution {
public:
    // ============================================================================
    // HELPER FUNCTION: Possible()
    // ============================================================================
    // Purpose: Calculate the TOTAL TIME needed to travel all train segments at
    //          a given 'mid_speed', following the "must wait for whole hour if
    //          you don't reach the station exactly" rule for ALL segments
    //          EXCEPT the very last one.
    //
    // KEY RULE OF THE PROBLEM:
    //   - You're riding 'n' trains back to back, covering distances dist[0..n-1].
    //   - After EVERY train EXCEPT THE LAST, if you don't arrive at a WHOLE
    //     number of hours, you must WAIT until the next whole hour before
    //     boarding the next train (trains only depart on the hour).
    //   - The LAST train has NO such rule — you just need to arrive by 'hour',
    //     partial time is fine (no waiting needed since journey ends there).
    //
    // Why the loop only goes to n-1 (not n)?
    //   - We treat the LAST segment SEPARATELY (outside the loop) because it
    //     does NOT need the ceiling/rounding — partial time is acceptable.
    //
    // Parameters:
    //   - dist: array of distances for each train segment
    //   - mid_speed: the speed we're TESTING (km/h or units/hour)
    //
    // Returns: total time (as a double) needed to complete the whole journey
    //          at this speed.
    // ============================================================================
    double Possible(vector<int>& dist, int mid_speed) {
        double time = 0.0;  // Running total time for the journey
        int n = dist.size();  // Total number of train segments

        // ========================================================================
        // STEP 1: Process ALL segments EXCEPT THE LAST ONE
        // ========================================================================
        // For these segments, we MUST round UP to the next whole hour, because
        // trains only depart on exact hour marks (can't catch a train mid-hour).
        for (int i = 0; i < n - 1; i++) {
            // Calculate raw time for this segment: distance / speed
            double t = (double)(dist[i] / (double)mid_speed);
            
            // Round UP to nearest whole hour (must wait for next departure)
            // Example: t = 2.3 hours → ceil(2.3) = 3 hours (wait for train at hour 3)
            time += ceil(t);
        }

        // ========================================================================
        // STEP 2: Process the LAST segment separately (NO rounding needed)
        // ========================================================================
        // Since the journey ENDS here, we don't need to catch another train.
        // Partial time is perfectly fine (e.g., 1.5 hours is valid, no need to
        // round up to 2 hours).
        time += (double)(dist[n - 1] / (double)mid_speed);

        // Return the TOTAL time needed for the entire journey at this speed
        return time;
    }

    // ============================================================================
    // MAIN FUNCTION: minSpeedOnTime()
    // ============================================================================
    // Problem: You must complete 'n' train journeys (with given distances) and
    //          arrive at the FINAL destination within 'hour' time. Between
    //          journeys (except the last), you must wait for the next whole
    //          hour if you don't arrive exactly on the hour. Find the MINIMUM
    //          integer speed to make it happen. Return -1 if IMPOSSIBLE.
    //
    // PATTERN: BINARY SEARCH ON ANSWER
    //
    // WHY BINARY SEARCH ON ANSWER?
    // -----------------------------
    // 1. SEARCH RANGE:
    //    - Lower bound (l): 1 (minimum valid speed, can't be 0 or negative)
    //    - Upper bound (r): 1e7 (a safely large speed, given problem constraints
    //      say dist[i] <= 1e6 and hour <= 1e7, so speed = 1e7 is always enough
    //      to make even the longest segment take negligible time)
    //
    // 2. MONOTONICITY PROPERTY:
    //    - If speed X works (total time <= hour), then any speed > X ALSO works
    //      (going faster only reduces or keeps time the same, never increases it).
    //    - If speed X doesn't work, any speed < X also won't work.
    //    - Pattern: [NO, NO, NO, ..., YES, YES, YES, ...] → Binary search fits!
    //
    // 3. SPECIAL CASE: If EVEN the maximum speed (1e7) can't satisfy the time
    //    limit, the journey is IMPOSSIBLE. This can happen if hour < n - 1
    //    (not enough time even to make the mandatory "wait for whole hour"
    //    stops between segments). We detect this using min_speed = -1 as a
    //    sentinel value (never updated if no speed ever works).
    //
    // TIME COMPLEXITY: O(n * log(max_speed))
    //   - n = number of segments (checked inside Possible() every iteration)
    //   - log(max_speed) = number of binary search iterations (log2(1e7) ≈ 24)
    // SPACE COMPLEXITY: O(1) - only a few variables used
    // ============================================================================
    int minSpeedOnTime(vector<int>& dist, double hour) {
        // ========================================================================
        // STEP 1: Define search range [l, r]
        // ========================================================================
        int l = 1;        // Minimum possible speed
        int r = 1e7;       // Maximum speed to try (safely large upper bound
                            // based on problem constraints)

        int min_speed = -1;  // Sentinel value: stays -1 if NO speed ever works
                              // (i.e., the journey is truly IMPOSSIBLE)

        // ========================================================================
        // STEP 2: Binary Search on the Answer
        // ========================================================================
        // Using "l <= r" template here (different from Koko's "l < r"), so we
        // explicitly STORE the answer in min_speed whenever we find a valid speed,
        // similar to the Ship Capacity problem's style.
        while (l <= r) {
            // Calculate mid-point safely (avoids overflow vs (l + r) / 2)
            int mid_speed = l + (r - l) / 2;

            // ====================================================================
            // STEP 3: Test if 'mid_speed' allows arriving within 'hour' time
            // ====================================================================
            if (Possible(dist, mid_speed) <= hour) {
                // CASE A: mid_speed WORKS! (total time is within limit)
                // --------------------------------------------------------
                // Record this as a POTENTIAL answer (we want the MINIMUM speed,
                // so we keep searching for something even smaller/slower).
                min_speed = mid_speed;

                // Search the LEFT half for a smaller (slower) valid speed
                r = mid_speed - 1;
            } else {
                // CASE B: mid_speed is TOO SLOW (total time exceeds limit)
                // -----------------------------------------------------------
                // We need to go FASTER. Search the RIGHT half.
                l = mid_speed + 1;
            }
        }

        // ========================================================================
        // STEP 4: Return the answer
        // ========================================================================
        // If min_speed was NEVER updated (still -1), it means NO speed (not even
        // the maximum 1e7) could satisfy the time limit → journey is IMPOSSIBLE.
        // Otherwise, min_speed holds the MINIMUM speed that works.
        return min_speed;
    }
};

/*
 * ================================================================================
 * COMPLETE LOGIC SUMMARY (For Quick Revision)
 * ================================================================================
 *
 * PROBLEM INTUITION:
 * ------------------
 * You need to catch a sequence of trains to reach your destination. Each train
 * covers a fixed distance. Trains ONLY depart on exact whole-hour marks — so if
 * you arrive at a station at, say, 2.3 hours, you must WAIT until hour 3 to
 * board the next train. The ONLY exception is the LAST train — since the
 * journey ends there, partial time is fine (no need to "catch" anything after).
 *
 * Find the MINIMUM integer speed to reach your final destination within 'hour'
 * total time. If impossible even at max speed, return -1.
 *
 * ================================================================================
 * REAL-WORLD ANALOGY: The Train Hopper 🚂
 * ================================================================================
 * Imagine you're on a multi-city train trip: City A → City B → City C → City D.
 * Trains from B and C only leave on the hour (like a strict subway schedule).
 * But once you reach City D (your final stop), you don't need to catch anything
 * else — you can arrive at 2:45 PM and that's perfectly fine.
 *
 * If you travel FASTER, you're more likely to arrive at each intermediate city
 * with time to spare BEFORE the next whole hour, minimizing wasted waiting time.
 * If you go SLOWER, you might juuust miss an hour mark and have to wait almost
 * a full hour for the next train — wasting a ton of time.
 *
 * You want to know: what's the SLOWEST speed (to save fuel/energy) that still
 * gets you to City D within your deadline?
 *
 * ================================================================================
 * WHY CEIL() IS APPLIED DIFFERENTLY HERE (Key Distinction from Koko/Ship):
 * ================================================================================
 * Unlike Koko Eating Bananas (where EVERY pile gets ceiling treatment), THIS
 * problem treats the LAST segment SPECIALLY:
 *
 *   - Segments 0 to n-2 (all except last): MUST ceil() → mandatory waiting
 *     for the next train departure (whole hour boundary).
 *   - Segment n-1 (the last one): NO ceil() → partial time is fine since the
 *     journey is OVER, no more trains to catch.
 *
 * This is the trickiest part of the problem and the #1 reason people get WA
 * (Wrong Answer) — they either ceil() everything or ceil() nothing.
 *
 * ================================================================================
 * DRY RUN EXAMPLE (Tiny Case):
 * ================================================================================
 * dist = [1, 3, 2], hour = 6
 *
 * l = 1, r = 1e7, min_speed = -1
 *
 * Let's test speed = 3:
 *   Segment 0 (i=0, not last): t = 1/3 = 0.33 → ceil(0.33) = 1 hour
 *   Segment 1 (i=1, not last): t = 3/3 = 1.0  → ceil(1.0)  = 1 hour
 *   Segment 2 (i=2, LAST):     t = 2/3 = 0.67 → NO ceiling → 0.67 hours
 *   Total = 1 + 1 + 0.67 = 2.67 hours
 *   2.67 <= 6? → TRUE (speed 3 works, but let's see if slower also works)
 *
 * Let's test speed = 1:
 *   Segment 0: t = 1/1 = 1.0 → ceil(1.0) = 1 hour
 *   Segment 1: t = 3/1 = 3.0 → ceil(3.0) = 3 hours
 *   Segment 2 (LAST): t = 2/1 = 2.0 → NO ceiling → 2.0 hours
 *   Total = 1 + 3 + 2 = 6 hours
 *   6 <= 6? → TRUE! (speed 1 works too — this might be our answer)
 *
 * Since speed 1 is the MINIMUM possible speed anyway, binary search would
 * converge here as the final answer: min_speed = 1.
 *
 * ================================================================================
 * TRIGGER WORDS FOR THIS PATTERN:
 * ================================================================================
 * Look for these clues in problem statements:
 *   - "Find the MINIMUM speed/rate such that you arrive/finish by a deadline"
 *   - Mentions of "must wait for the next whole hour/unit" for intermediate steps
 *   - A SPECIAL EXCEPTION for the LAST step/segment (no rounding needed there)
 *   - "Return -1 if impossible"
 *
 * Common problems using this pattern:
 *   - LeetCode 1870: Minimum Speed to Arrive on Time (this problem)
 *   - LeetCode 875: Koko Eating Bananas (simpler variant — ceil everywhere)
 *   - LeetCode 1011: Capacity To Ship Packages Within D Days
 *   - LeetCode 2187: Minimum Time to Complete Trips
 *
 * ================================================================================
 * COMMON MISTAKES TO AVOID:
 * ================================================================================
 * 1. Applying ceil() to the LAST segment too: This is WRONG. The last segment
 *    doesn't need to catch another train, so partial time is valid.
 *
 * 2. Forgetting the -1 case: If hour < (n - 1), it's mathematically IMPOSSIBLE
 *    to make all the intermediate whole-hour stops in time, no matter how fast
 *    you go. Your code correctly handles this via the min_speed = -1 sentinel
 *    (never gets updated if no speed satisfies the condition).
 *
 * 3. Using 'l < r' instead of 'l <= r': Your code uses 'l <= r' WITH an explicit
 *    min_speed variable to store the answer, similar to the Ship Capacity
 *    problem's style. This is a valid alternative template to the Koko-style
 *    'l < r' — just make sure you're consistent within a single solution!
 *
 * 4. Integer overflow with r = 1e7: This is fine as an 'int' since 1e7 easily
 *    fits within int range (max ~2.1 * 1e9). But be careful if the upper bound
 *    were larger — you'd need long long.
 *
 * 5. Precision issues with double: Since 'hour' is a double (can have decimals
 *    like 2.5), and distances/speeds are ints, mixing double/int arithmetic
 *    carefully (as your code does with explicit casts) avoids precision bugs.
 *
 * ================================================================================
 * TIME & SPACE COMPLEXITY:
 * ================================================================================
 * Time: O(n * log(max_speed))
 *   - n = number of segments (checked inside Possible() every iteration)
 *   - log(max_speed) = log2(1e7) ≈ 24 iterations
 *   - Total: ~24 * n operations → very efficient
 *
 * Space: O(1)
 *   - Only using a few variables (l, r, mid_speed, min_speed, time)
 *
 * ================================================================================
 * QUICK COMPARISON: ALL FOUR BINARY SEARCH ON ANSWER PROBLEMS SO FAR
 * ================================================================================
 * | Aspect          | Ship Capacity | Bus Trips      | Koko Bananas  | Train Speed        |
 * |-----------------|---------------|----------------|---------------|--------------------|
 * | Work Type       | Sequential    | Parallel       | Sequential    | Sequential+Special |
 * | Search Variable | Capacity      | Time           | Speed         | Speed              |
 * | Ceiling Applied | N/A           | N/A (floor)    | ALL piles     | ALL EXCEPT LAST    |
 * | Lower bound     | max(weights)  | 1              | 1             | 1                  |
 * | Upper bound     | sum(weights)  | min*totalTrips | max(piles)    | 1e7 (constant)     |
 * | Loop template   | l <= r        | l < r          | l < r         | l <= r             |
 * | Impossible case | N/A           | N/A            | N/A           | Returns -1         |
 * ================================================================================
 */