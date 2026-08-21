// class Solution {
// public:
//     typedef long long ll;

//     bool possible(vector<int>& batteries, ll mid_minutes, int n){
//         ll target_minutes = n * mid_minutes;

//         for(int i = 0; i < batteries.size();i++){

//             target_minutes -= min((ll)batteries[i], mid_minutes);

//             if(target_minutes <= 0) return true;
//         } 
//         return false;
//     }

//     long long maxRunTime(int n, vector<int>& batteries) {
//         ll l = *min_element(begin(batteries), end(batteries));

//         ll sum_total_minutes = 0;
//         for (auto& mints : batteries) {
//             sum_total_minutes += mints;
//         }
//         ll r = sum_total_minutes / n;

//         ll result = 0;

//         while (l <= r) {
//             ll mid_minutes = l + (r - l) / 2;

//             if (possible(batteries, mid_minutes, n)) {
//                 result = mid_minutes;
//                 l = mid_minutes + 1;
//             } else {
//                 r = mid_minutes - 1;
//             }
//         }
//         return result;
//     }
// };





// ============================================================================
// LeetCode 2141: Maximum Running Time of N Computers
// PATTERN: Binary Search on the ANSWER (same skeleton as LC 1552!)
// ============================================================================
//
// PROBLEM RECAP: You have n computers and an array of batteries (each with
// some charge in minutes). At any moment, at most n batteries can be
// "connected" (one per computer). You can swap batteries between computers
// FREELY and INSTANTLY, any number of times. Find the MAXIMUM number of
// minutes you can keep ALL n computers running simultaneously.

class Solution {
public:
    typedef long long ll;
    // Using long long because total battery minutes can overflow a 32-bit
    // int (sum of up to 10^5 batteries, each up to 10^9 minutes).


    // ------------------------------------------------------------------
    // possible(batteries, mid_minutes, n)
    // ------------------------------------------------------------------
    // GOAL: Check whether we can keep ALL n computers running for exactly
    //       'mid_minutes' minutes simultaneously, using free battery swaps.
    //
    // KEY INSIGHT (the trick that makes this whole problem solvable):
    //   Because batteries can be swapped freely and instantly between
    //   computers, WHICH computer uses WHICH battery doesn't matter at all.
    //   All that matters is: does the TOTAL usable energy (capped smartly)
    //   meet the TOTAL energy demand?
    //
    //   Total energy demand for 'mid_minutes' across n computers running
    //   in parallel = n * mid_minutes  (each computer needs mid_minutes
    //   worth of charge, and there are n of them).
    //
    //   BUT — a single battery, no matter how huge, can only ever power
    //   ONE computer at any given instant. So even a battery with 1000
    //   minutes of charge can contribute AT MOST 'mid_minutes' minutes of
    //   USEFUL runtime toward our target window (anything beyond
    //   mid_minutes is wasted, since after that window we don't need it
    //   anymore — the "excess" charge has nowhere useful to go).
    //   That's exactly why we take min(battery[i], mid_minutes) below.
    // ------------------------------------------------------------------
    bool possible(vector<int>& batteries, ll mid_minutes, int n){

        // Total energy units we NEED to fully power n computers for
        // 'mid_minutes' minutes each, running in parallel.
        ll target_minutes = n * mid_minutes;

        for(int i = 0; i < batteries.size(); i++){

            // Each battery can contribute AT MOST 'mid_minutes' worth of
            // useful energy (capped), because it can only serve one
            // computer at a time and we only need it for this long.
            target_minutes -= min((ll)batteries[i], mid_minutes);

            // As soon as we've covered the full demand, we know it's
            // feasible — no need to scan remaining batteries.
            // (Early exit optimization, same idea as LC1552's break.)
            if(target_minutes <= 0) return true;
        }

        // If we ran out of batteries before covering the full demand,
        // 'mid_minutes' is NOT achievable for all n computers at once.
        return false;
    }


    // ------------------------------------------------------------------
    // maxRunTime(n, batteries)
    // ------------------------------------------------------------------
    // GOAL: Find the LARGEST 'mid_minutes' value for which possible()
    //       returns true — i.e., the max simultaneous runtime for all
    //       n computers.
    // ------------------------------------------------------------------
    long long maxRunTime(int n, vector<int>& batteries) {

        // ------------------------------------------------------------
        // LOWER BOUND (l): the smallest battery's charge.
        // WHY THIS IS SAFE: batteries.length is always >= n. If you just
        // grab the n LARGEST batteries and assign one per computer with
        // zero swapping, the achievable runtime is at least as large as
        // the GLOBAL minimum battery value (since the n largest batteries
        // are each >= the global min). So the true answer can never be
        // smaller than this — making it a valid, tight-ish starting
        // lower bound (using 0 also works, this is just a nicer bound).
        // ------------------------------------------------------------
        ll l = *min_element(begin(batteries), end(batteries));

        // ------------------------------------------------------------
        // UPPER BOUND (r): total charge divided evenly across n computers.
        // WHY THIS IS SAFE: sum_total_minutes is the ABSOLUTE MAXIMUM
        // energy available in the whole system. Even in the most perfect,
        // lossless swapping scenario, you can never stretch total runtime
        // (summed across all n computers) beyond sum_total_minutes.
        // Dividing by n gives the theoretical ceiling for EACH computer's
        // runtime if energy were perfectly, losslessly distributed.
        // ------------------------------------------------------------
        ll sum_total_minutes = 0;
        for (auto& mints : batteries) {
            sum_total_minutes += mints;
        }
        ll r = sum_total_minutes / n;

        ll result = 0;

        // ------------------------------------------------------------
        // MONOTONICITY CHECK (why binary search is legal here):
        //   If we can sustain all n computers for T minutes, we can
        //   DEFINITELY sustain them for any T' < T (less demand, easier).
        //   If we CANNOT sustain T minutes, we definitely can't sustain
        //   any T'' > T (more demand, even harder).
        //   => possible(T) is: true true true ... true | false false...
        //   This clean boolean cutoff is what binary search exploits.
        // ------------------------------------------------------------
        while (l <= r) {
            ll mid_minutes = l + (r - l) / 2;

            if (possible(batteries, mid_minutes, n)) {
                // mid_minutes works — save it, then push for something
                // BIGGER since we want the MAXIMUM feasible runtime.
                result = mid_minutes;
                l = mid_minutes + 1;
            } else {
                // mid_minutes is too ambitious — search smaller values.
                r = mid_minutes - 1;
            }
        }

        return result;
    }
};

// ============================================================================
// REVISION SUMMARY — read this first when you come back in a few weeks
// ============================================================================
//
// PLAIN ENGLISH: You have n laptops and a pile of spare power banks with
// different charge levels. You can swap power banks between laptops
// instantly and as often as you like. Find the longest time you can keep
// ALL laptops powered on simultaneously.
//
// ANALOGY — "Power bank relay team":
// Imagine n runners (computers) who must all keep running for T minutes
// straight, and a bag of walkie-talkie batteries (power banks) of
// different sizes lying on the sideline. You can hand any battery to any
// runner at any moment, instantly. A giant 500-minute battery is still
// only useful for T minutes to THIS relay — because after T minutes, the
// race window is over and any leftover charge is worthless for this
// question. So each battery's "useful contribution" is capped at T. You
// keep guessing a race duration T, check if total usable charge (each
// battery capped at T) is enough to cover n runners for T minutes, and
// adjust up or down. That's binary search on the answer.
//
// WHY min(battery, mid_minutes) IS THE HEART OF THIS PROBLEM:
// This single line encodes the physical constraint that ONE battery can
// only power ONE computer at any instant — so no matter how big a single
// battery is, it can never contribute more than the target duration
// itself. Miss this insight and you'd wrongly think "just sum all
// batteries and divide by n" is enough — but that ignores that a single
// giant battery can't power 3 computers at once, only one.
//
// TRIGGER WORDS for this exact family of problems:
//   "swap freely / redistribute freely between resources" +
//   "maximize the time / minimize resources needed" +
//   "can you quickly verify a candidate answer is feasible?"
//   => Binary Search on Answer, feasibility check via a capped-sum trick.
//
// TWO-FUNCTION TEMPLATE (same as LC1552 — memorize this shape forever):
//   1. possible(candidate) — O(n) feasibility checker, usually greedy or
//      a capped-sum/count argument.
//   2. maxRunTime driver — binary search over [low, high] candidate
//      answers, shrinking the range based on possible()'s true/false,
//      always saving the best true result found so far.
//
// COMPLEXITY:
//   - possible(): O(k) where k = batteries.size() — one linear pass.
//   - maxRunTime(): O(log(sum_total_minutes / n)) binary search steps,
//     each costing O(k) => Total: O(k log(sum/n)).
//   - Space: O(1) extra.
//
// COMMON MISTAKES (why they happen):
//   1. Forgetting the long long (ll) typedef and mixing int/ll in
//      arithmetic — n * mid_minutes or sum_total_minutes can overflow
//      a 32-bit int with large inputs, giving silently wrong answers.
//   2. Forgetting to CAP each battery's contribution at mid_minutes —
//      students often just sum raw battery values instead of
//      min(battery, mid_minutes), breaking the "one battery = one
//      computer at a time" physical constraint.
//   3. Setting a wrong upper bound like using max(batteries) instead of
//      sum_total_minutes/n — this under-estimates the true search space
//      and can miss the correct answer.
//
// COMPANIES: This exact "binary search + capped resource sum" feasibility
// trick shows up in Google and Amazon OA/onsite rounds, and pairs
// naturally with LC 1552 (Magnetic Force), LC 875 (Koko Eating Bananas),
// and LC 1231 (Divide Chocolate) — all four share the identical
// "guess an answer, verify with O(n) greedy/sum check, binary search the
// guess" template. Once this template is truly internalized, all of
// these become the SAME problem wearing different clothes.
// ============================================================================