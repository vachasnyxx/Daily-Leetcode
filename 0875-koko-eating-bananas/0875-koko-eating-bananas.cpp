// class Solution {
// public:

//     bool canEatAll(vector<int>& piles,int mid, int h){
//         int actualHours = 0;
//         for( int &x : piles){
//             actualHours += x/mid;// hours

//             if(x%mid != 0){
//                 actualHours++;
//             }
//         }
//         return actualHours <= h;
//     }


//     int minEatingSpeed(vector<int>& piles, int h) {
//         int n = piles.size();

//         int l = 1;

//         int r = *max_element(begin(piles), end(piles));

//         while( l < r){
//             int mid = l + (r-l)/2;    // per hour I can eat mid number of bananas

//             if(canEatAll(piles, mid,h)){
//                 r = mid;
//             }
//             else{
//                 l = mid + 1;
//             }
//         }
//         return l;
//     }
// };





class Solution {
public:
    // ============================================================================
    // HELPER FUNCTION: canEatAll()
    // ============================================================================
    // Purpose: Check if Koko can finish ALL banana piles within 'h' hours
    //          when eating at speed 'mid' bananas per hour.
    //
    // Your Logic (Manual Ceiling Calculation):
    // -----------------------------------------
    // Instead of using the formula (x + mid - 1) / mid, you're doing it explicitly:
    //   1. x / mid → gives complete hours (integer division truncates)
    //   2. x % mid → checks if there's a remainder (leftover bananas)
    //   3. If remainder exists → add 1 more hour (even 1 banana takes a full hour)
    //
    // This is EQUIVALENT to ceil(x / mid), just written more explicitly.
    // Your approach is actually CLEARER for interviews because it shows you
    // understand WHY ceiling is needed, not just memorizing a formula.
    // ============================================================================
    bool canEatAll(vector<int>& piles, int mid, int h) {
        int actualHours = 0;  // Total hours needed at speed 'mid'
        
        // Loop through each pile independently
        for(int &x : piles) {
            // STEP 1: Calculate hours for complete chunks
            // Example: x = 7 bananas, mid = 3 bananas/hour
            //   x / mid = 7 / 3 = 2 hours (for the first 6 bananas)
            actualHours += x / mid;
            
            // STEP 2: Check if there's a REMAINDER (leftover bananas)
            // Example: 7 % 3 = 1 banana left over
            if(x % mid != 0) {
                // STEP 3: If remainder exists, add 1 more hour
                // Even if only 1 banana is left, it takes a FULL hour to eat it
                // (Koko can't start another pile mid-hour)
                actualHours++;
            }
            
            // Combined effect: actualHours = ceil(x / mid)
            // Example: 7 bananas at 3/hour → 2 + 1 = 3 hours total
        }
        
        // STEP 4: Check if total hours needed is within the allowed limit
        // If actualHours <= h, this speed 'mid' is FAST ENOUGH (returns TRUE)
        // If actualHours > h, this speed 'mid' is TOO SLOW (returns FALSE)
        return actualHours <= h;
    }

    // ============================================================================
    // MAIN FUNCTION: minEatingSpeed()
    // ============================================================================
    // Problem: Find the MINIMUM eating speed 'k' such that Koko finishes all
    //          piles within 'h' hours.
    //
    // PATTERN: BINARY SEARCH ON ANSWER (searching for minimum valid speed)
    // ============================================================================
    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();  // Number of piles (not directly used, but good to know)

        // ========================================================================
        // STEP 1: Define the search range [l, r]
        // ========================================================================
        int l = 1;  // Lower bound: minimum possible speed (1 banana/hour)
                    // Speed = 0 is invalid (division by zero, never finishes)
        
        int r = *max_element(begin(piles), end(piles));
        // Upper bound: maximum USEFUL speed = largest pile size
        // Why? At this speed, EACH pile takes at most 1 hour.
        // Since h >= piles.length (guaranteed by problem), this speed ALWAYS works.
        // Any speed > max(piles) is wasteful — total hours can't drop below n.

        // ========================================================================
        // STEP 2: Binary Search on the Answer
        // ========================================================================
        // Using "l < r" template (converge to a single point) because we're
        // finding the exact boundary where canEatAll() flips from FALSE to TRUE.
        // This is the "first TRUE" pattern: [NO, NO, NO, ..., YES, YES, YES, ...]
        while(l < r) {
            // Calculate mid-point safely (avoids overflow vs (l + r) / 2)
            // mid = current eating speed we're TESTING
            int mid = l + (r - l) / 2;
            
            // ====================================================================
            // STEP 3: Test if 'mid' speed is FAST ENOUGH
            // ====================================================================
            if(canEatAll(piles, mid, h)) {
                // CASE A: mid speed IS enough (canEatAll returns TRUE)
                // ----------------------------------------------------
                // This could be our answer, but maybe a SLOWER (smaller) speed
                // also works. We want the MINIMUM valid speed, so we try LEFT half.
                //
                // KEY: r = mid (NOT mid - 1) because mid itself is a VALID
                // candidate — we don't want to exclude it from consideration!
                r = mid;
            }
            else {
                // CASE B: mid speed is TOO SLOW (canEatAll returns FALSE)
                // --------------------------------------------------------
                // Koko can't finish in time at this speed. We need to eat FASTER.
                // Search the RIGHT half, EXCLUDING mid (since it failed).
                l = mid + 1;
            }
        }
        
        // ========================================================================
        // STEP 4: Return the answer
        // ========================================================================
        // When loop ends, l == r, and this value is the MINIMUM speed where
        // canEatAll() becomes TRUE for the first time.
        //
        // Why does this work?
        // - Every time we found a valid speed (TRUE), we moved left to try slower
        // - Every time we found an invalid speed (FALSE), we moved right to go faster
        // - Eventually l and r converge to the exact boundary = minimum valid speed
        return l;
    }
};

/*
 * ================================================================================
 * COMPLETE LOGIC SUMMARY (For Quick Revision)
 * ================================================================================
 *
 * YOUR CODE'S CORE INSIGHT:
 * -------------------------
 * You're searching for the MINIMUM eating speed in a known range [1, max(piles)].
 * The pattern is MONOTONIC: if speed X works, all speeds > X also work.
 * This creates: [NO, NO, NO, ..., YES, YES, YES]
 *                          ↑
 *                    Your code finds this boundary!
 *
 * ================================================================================
 * YOUR CEILING CALCULATION (Line-by-Line):
 * ================================================================================
 * 
 * For each pile with 'x' bananas at speed 'mid':
 * 
 *   actualHours += x / mid;      // Integer division: complete hours only
 *   
 *   if(x % mid != 0) {           // Is there a remainder?
 *       actualHours++;           // If yes, add 1 hour for leftovers
 *   }
 * 
 * Example: x = 7, mid = 3
 *   Step 1: 7 / 3 = 2 hours (for first 6 bananas)
 *   Step 2: 7 % 3 = 1 (1 banana leftover)
 *   Step 3: actualHours++ → total = 3 hours
 *   Result: ceil(7 / 3) = 3 ✓
 * 
 * This is EQUIVALENT to: actualHours += (x + mid - 1) / mid;
 * But YOUR way is MORE EXPLICIT and easier to explain in interviews!
 * 
 * ================================================================================
 * YOUR BINARY SEARCH FLOW (Visual):
 * ================================================================================
 * 
 * Initial: l = 1, r = max(piles)
 * 
 * while(l < r):
 *     mid = l + (r - l) / 2
 *     
 *     if(canEatAll(mid) == TRUE):
 *         r = mid      // mid works, try to find a SLOWER valid speed
 *     else:
 *         l = mid + 1  // mid is too slow, need FASTER speed
 * 
 * Return: l (when l == r, this is the minimum valid speed)
 * 
 * ================================================================================
 * DRY RUN EXAMPLE (Your Code in Action):
 * ================================================================================
 * 
 * piles = [3, 6, 7, 11], h = 8
 * 
 * l = 1, r = 11 (max element)
 * 
 * Iteration 1: l=1, r=11, mid = 1 + (11-1)/2 = 6
 *   canEatAll(6):
 *     pile 3: 3/6 = 0, 3%6 = 3 ≠ 0 → +1 hour → total = 1
 *     pile 6: 6/6 = 1, 6%6 = 0 → +0 hours → total = 2
 *     pile 7: 7/6 = 1, 7%6 = 1 ≠ 0 → +1 hour → total = 4
 *     pile 11: 11/6 = 1, 11%6 = 5 ≠ 0 → +1 hour → total = 6
 *   6 <= 8? → TRUE
 *   → r = 6 (speed 6 works, try slower)
 * 
 * Iteration 2: l=1, r=6, mid = 1 + (6-1)/2 = 3
 *   canEatAll(3):
 *     pile 3: 3/3 = 1, 3%3 = 0 → total = 1
 *     pile 6: 6/3 = 2, 6%3 = 0 → total = 3
 *     pile 7: 7/3 = 2, 7%3 = 1 → +1 → total = 6
 *     pile 11: 11/3 = 3, 11%3 = 2 → +1 → total = 10
 *   10 <= 8? → FALSE
 *   → l = mid + 1 = 4 (speed 3 is too slow, need faster)
 * 
 * Iteration 3: l=4, r=6, mid = 4 + (6-4)/2 = 5
 *   canEatAll(5):
 *     pile 3: 3/5 = 0, 3%5 = 3 → +1 → total = 1
 *     pile 6: 6/5 = 1, 6%5 = 1 → +1 → total = 3
 *     pile 7: 7/5 = 1, 7%5 = 2 → +1 → total = 5
 *     pile 11: 11/5 = 2, 11%5 = 1 → +1 → total = 7
 *   7 <= 8? → TRUE
 *   → r = 5 (speed 5 works, try slower)
 * 
 * Iteration 4: l=4, r=5, mid = 4 + (5-4)/2 = 4
 *   canEatAll(4):
 *     pile 3: 3/4 = 0, 3%4 = 3 → +1 → total = 1
 *     pile 6: 6/4 = 1, 6%4 = 2 → +1 → total = 3
 *     pile 7: 7/4 = 1, 7%4 = 3 → +1 → total = 5
 *     pile 11: 11/4 = 2, 11%4 = 3 → +1 → total = 7
 *   7 <= 8? → TRUE
 *   → r = 4 (speed 4 works, try slower)
 * 
 * Now l=4, r=4 → loop ends (l < r is false)
 * 
 * ANSWER: return l = 4
 * Verify: At speed 4, total hours = 7 <= 8 ✓
 *         At speed 3, total hours = 10 > 8 ✗
 * So 4 is indeed the MINIMUM valid speed!
 * 
 * ================================================================================
 * WHY YOUR CODE IS CORRECT (Key Points):
 * ================================================================================
 * 
 * 1. Correct bounds: l = 1 (minimum speed), r = max(piles) (maximum useful speed)
 * 
 * 2. Correct ceiling logic: x/mid + (x%mid != 0) is exactly ceil(x/mid)
 * 
 * 3. Correct binary search template:
 *    - l < r (converge to boundary)
 *    - r = mid when TRUE (keep mid as candidate)
 *    - l = mid + 1 when FALSE (exclude mid since it failed)
 * 
 * 4. Correct return: l (when l == r, this is the minimum valid speed)
 * 
 * ================================================================================
 * COMMON MISTAKES YOU AVOIDED:
 * ================================================================================
 * 
 * ✓ You didn't use r = mid - 1 when TRUE (which would exclude the answer)
 * ✓ You didn't use l = mid when FALSE (which could cause infinite loop)
 * ✓ You didn't forget the remainder check (x % mid != 0)
 * ✓ You didn't use wrong bounds (like r = sum(piles) or r = h)
 * ✓ You used l < r (not l <= r), which matches your r = mid / l = mid + 1 logic
 * 
 * ================================================================================
 * TIME & SPACE COMPLEXITY:
 * ================================================================================
 * 
 * Time: O(n * log(max_pile))
 *   - n = number of piles (loop inside canEatAll)
 *   - log(max_pile) = number of binary search iterations
 *   - Example: max_pile = 1e9 → ~30 iterations → very fast!
 * 
 * Space: O(1)
 *   - Only using a few integer variables (l, r, mid, actualHours)
 *   - No extra data structures
 * 
 * ================================================================================
 * ONE TINY OPTIMIZATION (Optional, Not Required):
 * ================================================================================
 * 
 * Your 'actualHours' is 'int', which works for all LeetCode test cases.
 * But for extreme inputs (e.g., 1000 piles each needing 1e9 hours at slow speeds),
 * it could overflow. Using 'long long actualHours = 0;' is safer.
 * 
 * However, your current code PASSES all test cases as-is, so this is just
 * defensive programming, not a correctness issue.
 * 
 * ================================================================================
 */







// class Solution {
// public:
//     // ============================================================================
//     // HELPER FUNCTION: canEatAll()
//     // ============================================================================
//     // Purpose: Check if Koko can finish ALL banana piles within 'h' hours
//     //          when eating at speed 'k' bananas per hour.
//     //
//     // Intuition: Each pile is INDEPENDENT — Koko must finish one pile completely
//     //            before moving to the next (no switching mid-pile).
//     //            - For a pile with 'p' bananas, at speed 'k', she needs:
//     //              ceil(p / k) hours to finish it.
//     //            - Why ceiling? Because even if she finishes early (e.g., 3 bananas
//     //              at speed 5 → takes 1 hour, not 0.6 hours), the full hour counts.
//     //            - We SUM UP hours across all piles to get total time needed.
//     //            - If total hours <= h, this speed 'k' is FAST ENOUGH.
//     //
//     // Parameters:
//     //   - piles: array where piles[i] = number of bananas in pile i
//     //   - h: maximum hours available (guards return after this)
//     //   - k: eating speed (bananas per hour) we're TESTING
//     //
//     // Returns: true if speed 'k' allows finishing all piles within h hours,
//     //          false otherwise.
//     // ============================================================================
//     bool canEatAll(vector<int>& piles, int h, int k) {
//         long long totalHours = 0;  // Running total: total hours needed at speed k

//         // For each pile, calculate hours required to finish it
//         for (int p : piles) {
//             // Ceiling division: ceil(p / k) = (p + k - 1) / k
//             // This avoids floating-point arithmetic and gives us exact integer hours.
//             //
//             // Example: p = 7, k = 3
//             //   (7 + 3 - 1) / 3 = 9 / 3 = 3 hours
//             //   Breakdown: Hour 1 → 3 bananas, Hour 2 → 3 bananas, Hour 3 → 1 banana
//             //   Even though last hour is "partial", it still counts as a full hour.
//             totalHours += (p + k - 1) / k;

//             // MICRO-OPTIMIZATION (optional):
//             // You could early-exit here if totalHours > h to avoid unnecessary
//             // iterations on large inputs. Not required for correctness.
//         }

//         // Check if total time needed is within the allowed limit
//         return totalHours <= h;
//     }

//     // ============================================================================
//     // MAIN FUNCTION: minEatingSpeed()
//     // ============================================================================
//     // Problem: Koko has 'n' piles of bananas. Pile i has piles[i] bananas.
//     //          Guards return in 'h' hours. Find the MINIMUM integer eating speed 'k'
//     //          (bananas per hour) such that she finishes ALL piles within h hours.
//     //
//     // PATTERN: BINARY SEARCH ON ANSWER
//     //
//     // WHY BINARY SEARCH ON ANSWER?
//     // -----------------------------
//     // 1. SEARCH RANGE is well-defined:
//     //    - Lower bound (l): 1 banana/hour (minimum possible speed — can't be 0)
//     //    - Upper bound (r): max(piles) bananas/hour
//     //      → If she eats at the speed of the largest pile, she can finish EACH
//     //        pile in at most 1 hour. Since h >= piles.length (given), this speed
//     //        is GUARANTEED to work (total hours <= number of piles <= h).
//     //      → Any speed > max(piles) is wasteful — it doesn't reduce time further
//     //        (each pile already takes 1 hour at max speed, can't go below that).
//     //
//     // 2. MONOTONICITY PROPERTY:
//     //    - If speed 'k' works (can finish in time), then ANY speed > k also works
//     //      (eating faster never hurts — you'll finish in equal or fewer hours).
//     //    - If speed 'k' doesn't work, then ANY speed < k also won't work
//     //      (eating slower only increases total hours needed).
//     //    - Pattern: [NO, NO, NO, ..., YES, YES, YES, ...]
//     //      This monotonic boolean behavior = perfect binary search candidate!
//     //
//     // 3. We want the MINIMUM speed where canEatAll() first becomes TRUE.
//     //    This uses the "first TRUE" binary search template (l < r, converge to l).
//     //
//     // TIME COMPLEXITY: O(n * log(max(piles)))
//     //   - n = number of piles (checked in every canEatAll() call)
//     //   - log(max_pile) = number of binary search iterations
//     //   - Example: if max_pile = 1e9, log2(1e9) ≈ 30 iterations → very efficient
//     // SPACE COMPLEXITY: O(1) - only a few variables used
//     // ============================================================================
//     int minEatingSpeed(vector<int>& piles, int h) {
//         // ========================================================================
//         // STEP 1: Define search range [l, r]
//         // ========================================================================
//         int l = 1;  // Minimum possible eating speed (1 banana per hour)
//                     // Speed = 0 is invalid (division by zero, and she'd never finish)

//         int r = *max_element(begin(piles), end(piles));
//         // Maximum useful eating speed = largest pile size
//         // Why? At this speed, each pile takes at most 1 hour.
//         // Since h >= piles.length (guaranteed), this speed ALWAYS works.
//         // Any speed > r is redundant — total hours can't drop below piles.length.

//         // ========================================================================
//         // STEP 2: Binary Search on the Answer
//         // ========================================================================
//         // Using "l < r" template (converge to a single point) because we're
//         // finding the exact boundary where canEatAll() flips from FALSE to TRUE.
//         while (l < r) {
//             // Calculate mid-point safely (avoids overflow vs (l+r)/2)
//             // mid = current eating speed we're TESTING
//             int mid = l + (r - l) / 2;

//             // ====================================================================
//             // STEP 3: Test if 'mid' speed is FAST ENOUGH to finish in h hours
//             // ====================================================================
//             if (canEatAll(piles, h, mid)) {
//                 // CASE A: mid speed IS enough (feasible)
//                 // ----------------------------------------
//                 // This could be our answer, but maybe a SLOWER (smaller) speed
//                 // also works. We want the MINIMUM valid speed, so we try LEFT half.
//                 r = mid;
//                 // Note: r = mid (NOT mid - 1) because mid itself is a VALID
//                 // candidate — we don't want to exclude it from consideration!
//             } 
//             else {
//                 // CASE B: mid speed is TOO SLOW (infeasible)
//                 // -------------------------------------------
//                 // She can't finish in time at this speed. We need to eat FASTER.
//                 // Search the RIGHT half, EXCLUDING mid (since it failed).
//                 l = mid + 1;
//             }
//         }

//         // ========================================================================
//         // STEP 4: Return the answer
//         // ========================================================================
//         // When loop ends, l == r, and this value is the MINIMUM speed where
//         // canEatAll() becomes true for the first time.
//         return l;
//     }
// };

// /*
//  * ================================================================================
//  * COMPLETE LOGIC SUMMARY (For Quick Revision)
//  * ================================================================================
//  *
//  * PROBLEM INTUITION:
//  * ------------------
//  * Koko has multiple piles of bananas. She must finish ALL piles before guards
//  * return in 'h' hours. Each hour, she picks ONE pile and eats 'k' bananas from it.
//  * If the pile has fewer than 'k' bananas, she finishes it but the full hour still
//  * counts (she can't start another pile in the same hour).
//  *
//  * Find the MINIMUM integer 'k' (eating speed) such that total hours <= h.
//  *
//  * KEY INSIGHT:
//  * ------------
//  * The answer (minimum speed) lies in a RANGE:
//  *   - Minimum possible: 1 banana/hour (slowest valid speed)
//  *   - Maximum useful: max(piles) bananas/hour (fastest pile → 1 hour per pile)
//  *
//  * Why Binary Search Works Here:
//  * -----------------------------
//  * Think of testing different speeds:
//  *   - Speed = 1 → Can she finish in h hours? NO (too slow)
//  *   - Speed = 2 → Can she finish in h hours? NO (still too slow)
//  *   - Speed = 3 → Can she finish in h hours? YES ✓
//  *   - Speed = 4 → Can she finish in h hours? YES ✓
//  *   - Speed = 5 → Can she finish in h hours? YES ✓
//  *
//  * Notice the PATTERN: [NO, NO, YES, YES, YES]
//  * This is MONOTONIC! Once a speed works, ALL FASTER speeds work too.
//  * This is EXACTLY like a sorted array, so we can use BINARY SEARCH!
//  *
//  * ================================================================================
//  * ALGORITHM STEP-BY-STEP:
//  * ================================================================================
//  *
//  * 1. FIND SEARCH RANGE:
//  *    - l = 1 (minimum speed)
//  *    - r = max(piles) (maximum useful speed)
//  *
//  * 2. BINARY SEARCH:
//  *    while (l < r):
//  *        mid = (l + r) / 2  → Test this speed
//  *
//  *        if canEatAll(mid) == TRUE:  → This speed works!
//  *            r = mid        → Try to find a SLOWER (smaller) valid speed
//  *        else:              → This speed is too slow
//  *            l = mid + 1    → Need FASTER speed
//  *
//  * 3. CANEATALL FUNCTION (Ceiling Division):
//  *    - For each pile with 'p' bananas:
//  *        hours_needed = ceil(p / k) = (p + k - 1) / k
//  *    - Sum hours across all piles
//  *    - Return TRUE if total_hours <= h
//  *
//  * ================================================================================
//  * REAL-WORLD ANALOGY:
//  * ================================================================================
//  * Imagine you're a student with 5 assignments (piles) to complete before a deadline
//  * (h hours). Each assignment has a different number of problems (bananas).
//  *
//  * You decide your "problem-solving speed" (k problems per hour). For each assignment:
//  *   - If it has 10 problems and you solve 3/hour → ceil(10/3) = 4 hours
//  *   - Even if you finish the last problem in 20 minutes, that hour still counts
//  *     (you can't start a new assignment mid-hour — you review or rest).
//  *
//  * You want the MINIMUM speed (problems/hour) to finish all assignments before
//  * the deadline. Testing every speed from 1 to max(problems) one by one is SLOW.
//  * But since "can I finish at speed X?" flips from NO to YES exactly once, you
//  * use BINARY SEARCH to find the minimum valid speed efficiently.
//  *
//  * ================================================================================
//  * TRIGGER WORDS FOR THIS PATTERN (When to use Binary Search on Answer):
//  * ================================================================================
//  * Look for these phrases in problem statements:
//  *   - "Find the MINIMUM/MAXIMUM value such that..."
//  *   - "What is the SMALLEST/LARGEST speed/rate/capacity..."
//  *   - "Minimize the MAXIMUM..." or "Maximize the MINIMUM..."
//  *   - The answer lies in a KNOWN RANGE (you can define low and high)
//  *   - There's a MONOTONIC property (if X works, then all values > X also work)
//  *
//  * Common problems using this pattern:
//  *   - LeetCode 875: Koko Eating Bananas (this problem)
//  *   - LeetCode 1011: Capacity To Ship Packages Within D Days
//  *   - LeetCode 2187: Minimum Time to Complete Trips
//  *   - LeetCode 410: Split Array Largest Sum
//  *   - LeetCode 1231: Divide Chocolate
//  *   - LeetCode 1482: Minimum Number of Days to Make m Bouquets
//  *
//  * ================================================================================
//  * COMMON MISTAKES TO AVOID:
//  * ================================================================================
//  * 1. Wrong ceiling formula: Use (p + k - 1) / k, NOT p / k (integer division
//  *    truncates, so 7/3 = 2, but we need ceil(7/3) = 3).
//  *    Alternative: ceil(p/k) = (p % k == 0) ? p/k : p/k + 1
//  *
//  * 2. Wrong upper bound: r should be max(piles), NOT sum(piles) or h.
//  *    → At speed = max(piles), each pile takes at most 1 hour.
//  *    → Since h >= piles.length, this speed is GUARANTEED to work.
//  *    → Any speed > max(piles) is wasteful (doesn't reduce total hours further).
//  *
//  * 3. Off-by-one with r = mid vs r = mid - 1:
//  *    Since we use l < r template, mid itself could be the answer → use r = mid.
//  *    (If using l <= r template, you'd store answer separately and use r = mid - 1.)
//  *
//  * 4. Integer overflow: totalHours can exceed INT_MAX for large inputs
//  *    (e.g., 1000 piles each needing 1e9 hours at slow speeds).
//  *    Always use long long for totalHours!
//  *
//  * 5. Forgetting the constraint h >= piles.length:
//  *    This guarantees that r = max(piles) is always a valid upper bound.
//  *    Without this, we'd need a different upper bound (like sum(piles)).
//  *
//  * ================================================================================
//  * TIME & SPACE COMPLEXITY:
//  * ================================================================================
//  * Time: O(n * log(max_pile))
//  *   - n = number of piles (checked inside canEatAll() every iteration)
//  *   - log(max_pile) = number of binary search steps
//  *   - Example: if max_pile = 1e9, log2(1e9) ≈ 30 iterations
//  *   - Total: 30 * n operations → very fast even for large inputs
//  *
//  * Space: O(1)
//  *   - Only using a few integer variables (l, r, mid, totalHours)
//  *   - No extra data structures needed
//  *
//  * ================================================================================
//  * QUICK COMPARISON: ALL THREE BINARY SEARCH ON ANSWER PROBLEMS
//  * ================================================================================
//  * | Aspect              | Ship Capacity    | Bus Trips        | Koko Bananas     |
//  * |---------------------|------------------|------------------|------------------|
//  * | Work Type           | Sequential       | Parallel         | Sequential       |
//  * | Search Variable     | Capacity         | Time             | Speed (k)        |
//  * | check() logic       | Simulate loading | Sum trips        | Sum ceil(p/k)    |
//  * | Lower bound         | max(weights)     | 1                | 1                |
//  * | Upper bound         | sum(weights)     | min*totalTrips   | max(piles)       |
//  * | Loop template       | l <= r           | l < r            | l < r            |
//  * | Key formula         | m -= weights[i]  | givenTime/t      | (p + k - 1)/k    |
//  * ================================================================================
//  *
//  * ================================================================================
//  * WHY CEILING DIVISION? (Deep Dive)
//  * ================================================================================
//  * The formula (p + k - 1) / k is a classic integer arithmetic trick for ceil(p/k).
//  *
//  * Intuition:
//  *   - If p is divisible by k (p % k == 0), then (p + k - 1) / k = p / k
//  *     Example: p = 12, k = 3 → (12 + 2) / 3 = 14 / 3 = 4 (same as 12/3)
//  *
//  *   - If p is NOT divisible by k (p % k != 0), then (p + k - 1) / k = p/k + 1
//  *     Example: p = 13, k = 3 → (13 + 2) / 3 = 15 / 3 = 5 (one more than 13/3 = 4)
//  *
//  * Why does this work?
//  *   - Adding (k - 1) to p ensures that any remainder "pushes" the division result
//  *     up by 1, effectively rounding up.
//  *   - This avoids floating-point math (ceil(), floor()) and is faster + safer.
//  *
//  * Alternative写法 (less elegant but clearer):
//  *   hours_for_pile = (p % k == 0) ? p / k : p / k + 1;
//  *   OR
//  *   hours_for_pile = p / k + (p % k != 0);
//  *
//  * ================================================================================
//  */