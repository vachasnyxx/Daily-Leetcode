// class Solution {
// public:
//     bool check(int mid, vector<int>& weights, int days) {
//         int n = weights.size();
//         int m = mid;
//         int count = 1;

//         for(int i = 0; i<n; i++){
//             if(m >= weights[i]){
//                 m -= weights[i];
//             }
//             else{
//                 count++;
//                 m = mid;
//                 m -= weights[i];
//             }
//         }
//         if(count > days) return false;
//         else return true;
//     }

//     int shipWithinDays(vector<int>& weights, int days) {
//         int n = weights.size();
//         int max = INT_MIN;
//         int sum = 0;
//         for (int i = 0; i < n; i++) {
//             if (max < weights[i])
//                 max = weights[i];
//             sum += weights[i];
//         }
//         int low = max;
//         int high = sum;
//         int mincapacity = sum;

//         while (low <= high) {
//             int mid = low + (high - low) / 2;

//             if (check(mid, weights, days)) {
//                 mincapacity = mid;
//                 high = mid - 1;
//             } else {
//                 low = mid + 1;
//             }
//         }
//         return mincapacity;
//     }
// };



class Solution {
public:
    // ============================================================================
    // HELPER FUNCTION: check()
    // ============================================================================
    // Purpose: Determines if it's POSSIBLE to ship all packages within 'days' days
    //          using a ship capacity of 'mid'.
    //
    // Intuition: This is a GREEDY simulation.
    //            - We load packages onto the ship one by one.
    //            - If the current package fits in remaining capacity (m), we load it.
    //            - If it doesn't fit, we MUST send the ship today (count++), 
    //              and start fresh tomorrow with full capacity (mid).
    //            - At the end, we check if total days needed (count) <= allowed days.
    //
    // Parameters:
    //   - mid: The ship capacity we're testing (can this capacity work?)
    //   - weights: Array of package weights
    //   - days: Maximum number of days allowed
    //
    // Returns: true if 'mid' capacity is SUFFICIENT (feasible), false otherwise.
    // ============================================================================
    bool check(int mid, vector<int>& weights, int days) {
        int n = weights.size();  // Total number of packages
        int m = mid;             // Current remaining capacity of the ship (starts full)
        int count = 1;           // Number of days used. Start with 1 (we're on day 1 initially)
        
        // Iterate through each package in order (greedy: load in given sequence)
        for(int i = 0; i < n; i++) {
            // CASE 1: Current package FITS in remaining capacity
            if(m >= weights[i]) {
                // Load it onto the ship
                // Subtract package weight from remaining capacity
                m -= weights[i];
            }
            // CASE 2: Current package DOESN'T FIT
            else {
                // We must send the ship TODAY (even if not fully utilized)
                // Increment day counter (we're moving to the next day)
                count++;
                
                // Reset ship capacity to full for the new day
                m = mid;
                
                // Now load the current package onto the fresh ship
                m -= weights[i];
            }
        }
        
        // After processing all packages, check if we stayed within the day limit
        // If count > days, this capacity (mid) is TOO SMALL (not feasible)
        // If count <= days, this capacity (mid) is SUFFICIENT (feasible)
        if(count > days) 
            return false;  // Capacity too small, need more days than allowed
        else 
            return true;   // Capacity works! We can ship within 'days' days
    }

    // ============================================================================
    // MAIN FUNCTION: shipWithinDays()
    // ============================================================================
    // Problem: Find the MINIMUM ship capacity to ship all packages within 'days' days.
    //
    // PATTERN: BINARY SEARCH ON ANSWER (also called "Binary Search on Result Space")
    //
    // WHY BINARY SEARCH ON ANSWER?
    // -----------------------------
    // 1. The answer (minimum capacity) lies in a KNOWN RANGE:
    //    - Lower bound (low): max(weights) 
    //      → We MUST carry the heaviest package, so capacity can't be less than this.
    //    - Upper bound (high): sum(weights)
    //      → In the worst case, we ship everything in 1 day (carry all at once).
    //
    // 2. MONOTONICITY PROPERTY:
    //    - If capacity X works, then ANY capacity > X also works (easier to ship).
    //    - If capacity X doesn't work, then ANY capacity < X also won't work.
    //    - This TRUE/FALSE monotonic behavior = PERFECT for binary search!
    //
    // 3. We're searching for the MINIMUM capacity that returns TRUE (feasible).
    //    This is like finding the "first TRUE" in a sorted boolean array:
    //    [FALSE, FALSE, FALSE, ..., TRUE, TRUE, TRUE, ...]
    //                          ↑
    //                    We want this index!
    //
    // TIME COMPLEXITY: O(n * log(sum - max))
    //   - n = number of packages (for each check() call)
    //   - log(sum - max) = number of binary search iterations
    // SPACE COMPLEXITY: O(1) - only using a few variables
    // ============================================================================
    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();  // Total packages
        
        // ========================================================================
        // STEP 1: Find the search range [low, high]
        // ========================================================================
        int max = INT_MIN;  // To store the maximum weight (minimum possible capacity)
        int sum = 0;        // To store total weight (maximum possible capacity)
        
        // Single pass to find both max element and sum
        for (int i = 0; i < n; i++) {
            // Update maximum weight seen so far
            if (max < weights[i])
                max = weights[i];
            
            // Accumulate total weight
            sum += weights[i];
        }
        
        // ========================================================================
        // STEP 2: Initialize Binary Search
        // ========================================================================
        int low = max;      // Minimum capacity = heaviest single package
                            // (we can't split packages, so we MUST carry the heaviest one)
        
        int high = sum;     // Maximum capacity = all packages in one day
                            // (if we had infinite ship size, we'd ship everything at once)
        
        int mincapacity = sum;  // Variable to store the answer
                                // Initialize with worst case (all in 1 day)
        
        // ========================================================================
        // STEP 3: Binary Search on the Answer
        // ========================================================================
        // We're searching for the MINIMUM capacity that is FEASIBLE (check() returns true)
        while (low <= high) {
            // Calculate mid-point (using this formula avoids integer overflow)
            // mid = current capacity we're TESTING
            int mid = low + (high - low) / 2;
            
            // ====================================================================
            // STEP 4: Check if 'mid' capacity is feasible
            // ====================================================================
            // Call helper function to simulate shipping with capacity = mid
            // Returns TRUE if we can ship within 'days' days, FALSE otherwise
            if (check(mid, weights, days)) {
                // CASE A: 'mid' capacity WORKS!
                // --------------------------------
                // This is a VALID answer, but we want the MINIMUM.
                // So we store it and try to find a SMALLER valid capacity.
                
                mincapacity = mid;  // Record this as a potential answer
                
                // Search in the LEFT half for a smaller valid capacity
                high = mid - 1;
            } 
            else {
                // CASE B: 'mid' capacity is TOO SMALL
                // ------------------------------------
                // We couldn't ship within 'days' days with this capacity.
                // We need a LARGER ship capacity.
                
                // Search in the RIGHT half for a larger (hopefully feasible) capacity
                low = mid + 1;
            }
        }
        
        // ========================================================================
        // STEP 5: Return the minimum feasible capacity
        // ========================================================================
        return mincapacity;
    }
};

/*
 * ================================================================================
 * COMPLETE LOGIC SUMMARY (For Quick Revision)
 * ================================================================================
 * 
 * PROBLEM INTUITION:
 * ------------------
 * You have packages with different weights. You must ship them in order (can't reorder).
 * Each day you get a ship with some capacity. You load packages until the ship is full,
 * then send it. Find the MINIMUM ship capacity to finish within D days.
 * 
 * KEY INSIGHT:
 * ------------
 * The answer (minimum capacity) lies in a RANGE:
 *   - Minimum possible: max(weights) → Must carry the heaviest package
 *   - Maximum possible: sum(weights) → Carry everything in 1 day (worst case)
 * 
 * Why Binary Search Works Here:
 * -----------------------------
 * Think of testing different capacities:
 *   - Capacity = 10 → Can we do it in D days? NO (too small)
 *   - Capacity = 20 → Can we do it in D days? NO (still too small)
 *   - Capacity = 30 → Can we do it in D days? YES ✓
 *   - Capacity = 40 → Can we do it in D days? YES ✓
 *   - Capacity = 50 → Can we do it in D days? YES ✓
 * 
 * Notice the PATTERN: [NO, NO, YES, YES, YES]
 * This is MONOTONIC! Once we find a capacity that works, ALL LARGER capacities work too.
 * This is EXACTLY like a sorted array, so we can use BINARY SEARCH!
 * 
 * ================================================================================
 * ALGORITHM STEP-BY-STEP:
 * ================================================================================
 * 
 * 1. FIND SEARCH RANGE:
 *    - low = max(weights)  → Can't be smaller than heaviest package
 *    - high = sum(weights) → Worst case: ship everything in 1 day
 * 
 * 2. BINARY SEARCH:
 *    while (low <= high):
 *        mid = (low + high) / 2  → Test this capacity
 *        
 *        if check(mid) == TRUE:  → This capacity works!
 *            answer = mid        → Store it (potential minimum)
 *            high = mid - 1      → Try to find a SMALLER valid capacity
 *        else:                   → This capacity is too small
 *            low = mid + 1       → Need LARGER capacity
 * 
 * 3. CHECK FUNCTION (Greedy Simulation):
 *    - Start with day 1, full ship capacity
 *    - For each package:
 *        * If it fits → Load it (reduce remaining capacity)
 *        * If it doesn't fit → Send ship (day++), start fresh, load package
 *    - Return TRUE if total days used <= allowed days
 * 
 * ================================================================================
 * REAL-WORLD ANALOGY:
 * ================================================================================
 * Imagine you're a moving company owner. You need to figure out the MINIMUM truck size
 * to rent so you can move all your client's boxes in at most 5 days.
 * 
 * - Smallest truck you could rent: Must fit the heaviest box (e.g., a piano)
 * - Largest truck you could rent: One that fits ALL boxes at once (expensive!)
 * 
 * You test different truck sizes:
 *   - Small truck (capacity = piano weight): Takes 10 days → TOO SLOW
 *   - Medium truck: Takes 6 days → STILL TOO SLOW
 *   - Large truck: Takes 4 days → PERFECT! ✓
 *   - Extra-large truck: Takes 3 days → WORKS, but overkill (we want minimum)
 * 
 * You want the SMALLEST truck that gets the job done in ≤5 days.
 * That's EXACTLY what binary search on answer finds!
 * 
 * ================================================================================
 * TRIGGER WORDS FOR THIS PATTERN (When to use Binary Search on Answer):
 * ================================================================================
 * Look for these phrases in problem statements:
 *   - "Find the MINIMUM/MAXIMUM value such that..."
 *   - "What is the SMALLEST/LARGEST capacity/size/speed..."
 *   - "Minimize the MAXIMUM..." or "Maximize the MINIMUM..."
 *   - The answer lies in a KNOWN RANGE (you can define low and high)
 *   - There's a MONOTONIC property (if X works, then all values > X also work)
 * 
 * Common problems using this pattern:
 *   - LeetCode 1011: Capacity To Ship Packages Within D Days (this problem)
 *   - LeetCode 410: Split Array Largest Sum
 *   - LeetCode 875: Koko Eating Bananas
 *   - LeetCode 1231: Divide Chocolate
 *   - LeetCode 1482: Minimum Number of Days to Make m Bouquets
 * 
 * ================================================================================
 * COMMON MISTAKES TO AVOID:
 * ================================================================================
 * 1. Wrong lower bound: low should be max(weights), NOT 0 or 1
 *    → You MUST be able to carry the heaviest single package!
 * 
 * 2. Forgetting to reset capacity in check(): When starting a new day,
 *    you must set m = mid (full capacity), not keep the old remaining capacity.
 * 
 * 3. Off-by-one in day counting: Start with count = 1 (we're already on day 1),
 *    NOT count = 0.
 * 
 * 4. Wrong binary search direction:
 *    - If check(mid) is TRUE → We found a valid answer, but try SMALLER (high = mid - 1)
 *    - If check(mid) is FALSE → We need LARGER capacity (low = mid + 1)
 * 
 * 5. Integer overflow: Use mid = low + (high - low) / 2, NOT (low + high) / 2
 *    → Prevents overflow when low + high exceeds INT_MAX.
 * 
 * ================================================================================
 * TIME & SPACE COMPLEXITY:
 * ================================================================================
 * Time: O(n * log(sum - max))
 *   - n = number of packages (for each check() call in the loop)
 *   - log(sum - max) = number of binary search iterations
 *   - Example: If sum = 1000, max = 10, we do ~log(990) ≈ 10 iterations
 *   - Total: 10 * n operations → Very efficient!
 * 
 * Space: O(1)
 *   - Only using a few integer variables (low, high, mid, count, m)
 *   - No extra data structures needed
 * 
 * ================================================================================
 */
