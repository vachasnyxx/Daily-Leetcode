// class Solution {
// public:
//     bool checkInclusion(string s1, string s2) {
//         int n = s1.size();
//         int m = s2.size();

//         if (n > m) {
//             return false;
//         }

//         vector<int> s1_freq(26, 0);
//         vector<int> s2_freq(26, 0);

//         for (char &ch : s1) {    
//             s1_freq[ch - 'a']++;
//         }

//         int i = 0;
//         int j = 0;
//         while (j < m) {
//             s2_freq[s2[j] - 'a']++;

//             if (j - i + 1 > n) {     // time to shrink the window
//                 s2_freq[s2[i] - 'a']--;
//                 i++;
//             }

//             if (s1_freq == s2_freq) {
//                 return true;
//             }
//             j++;
//         }
//         return false;
//     }
// };




class Solution {
public:
    // Problem: Check if s2 contains ANY permutation of s1 as a substring
    // Example: s1 = "ab", s2 = "eidboaoo" → return true (because "bo" is a permutation of "ab")
    // Example: s1 = "ab", s2 = "eidboaoo" → "ba" at index 4-5 is also a permutation
    // Pattern: Fixed-Size Sliding Window + Frequency Array Comparison
    // Key insight: Two strings are permutations if and only if they have identical character frequencies!
    bool checkInclusion(string s1, string s2) {
        // Get lengths of both strings
        int n = s1.size();  // Length of pattern (what we're looking for)
        int m = s2.size();  // Length of text (where we're searching)
        
        // EDGE CASE: If pattern is longer than text, impossible to find it
        // Example: s1 = "abc", s2 = "ab" → can't fit "abc" in "ab"
        // This check prevents unnecessary computation and potential bugs
        if (n > m) {
            return false;
        }

        // STEP 1: Create frequency arrays for both strings
        // We use vector<int>(26, 0) because we're dealing with lowercase English letters
        // Index 0 = 'a', Index 1 = 'b', ..., Index 25 = 'z'
        // s1_freq: stores the target frequency we need to match
        // s2_freq: stores the current window's frequency (will change as we slide)
        // Example: s1 = "aab" → s1_freq = [2, 1, 0, 0, ...] (2 'a's, 1 'b')
        vector<int> s1_freq(26, 0);
        vector<int> s2_freq(26, 0);

        // STEP 2: Build the frequency map for s1 (our pattern)
        // This is our "target signature" - we're looking for any window in s2
        // that has the EXACT same frequency distribution
        // Why this works: Permutations have identical character counts!
        // Example: "abc", "bca", "cab" all have freq = [1, 1, 1, 0, ...]
        for (char &ch : s1) {    
            s1_freq[ch - 'a']++;  // Increment count for each character
        }
        // After this loop: s1_freq is our "goal" that we'll compare against

        // STEP 3: Sliding Window - Two pointers (i = left, j = right)
        // We maintain a window of EXACTLY size n (length of s1)
        // As we slide, we compare s2_freq with s1_freq
        // If they match → found a permutation!
        int i = 0;  // Left boundary of window (inclusive)
        int j = 0;  // Right boundary of window (inclusive)
        
        // Process each character in s2 one by one
        while (j < m) {
            // INCLUDE current character s2[j] into our window
            // Increment its frequency in s2_freq
            // This expands our window to the right
            // Example: window = "ab", s2[j] = 'c' → window becomes "abc"
            s2_freq[s2[j] - 'a']++;

            // CHECK if window has exceeded the target size (n)
            // We want window size to be EXACTLY n (same as s1 length)
            // If j - i + 1 > n, we need to shrink from the left
            // Example: n = 3, window = "abcd" (size 4) → remove 'a' → "bcd" (size 3)
            if (j - i + 1 > n) {     // time to shrink the window
                // Remove the leftmost character s2[i] from our window
                // Decrement its frequency in s2_freq
                // This character is no longer in our window
                // Example: window = "abcd", remove 'a' → decrement count of 'a'
                s2_freq[s2[i] - 'a']--;
                
                // Move left pointer forward (window shrinks from left)
                // After this, window size = n (exactly what we want)
                i++;
            }
            // After this if-block, window size is guaranteed to be <= n
            // Specifically, once j >= n-1, window size is exactly n

            // STEP 4: Compare frequency arrays
            // This is the KEY CHECK: Do we have a permutation match?
            // Vector comparison in C++ checks if ALL 26 elements are equal
            // This is O(26) = O(1) constant time!
            // If s1_freq == s2_freq, it means:
            // - Every character appears the same number of times in both
            // - Therefore, current window is a permutation of s1
            // Example: s1 = "ab", s2 window = "ba" → both have [1, 1, 0, ...] → MATCH!
            if (s1_freq == s2_freq) {
                return true;  // Found a permutation! Return immediately
            }
            
            // Expand window: move right pointer forward
            // In next iteration, we'll include s2[j+1] into our window
            j++;
        }
        
        // If we've checked all possible windows and found no match
        // Return false (no permutation of s1 exists in s2)
        return false;
    }
};

/*
================================================================================
                    COMPLETE REVISION SUMMARY - LEETCODE 567
================================================================================

PROBLEM: Permutation in String (Check if s2 contains any permutation of s1)
Given s1 = "ab", s2 = "eidboaoo"
Output: true  (because "bo" at index 4-5 is a permutation of "ab")

Other examples:
- s1 = "ab", s2 = "eidboaoo" → true ("ba" is also a permutation)
- s1 = "adc", s2 = "dcda" → true ("dca" or "acd" are permutations)
- s1 = "abc", s2 = "def" → false (no permutation exists)
- s1 = "hello", s2 = "ooolleoooleh" → true ("olleh" is a permutation)
- s1 = "abc", s2 = "ccccbbbbaaaa" → false (no window matches freq)

--------------------------------------------------------------------------------
CORE INTUITION - FIXED-SIZE SLIDING WINDOW + FREQUENCY MATCHING
--------------------------------------------------------------------------------

Think of this like a "fingerprint matching" problem:

1. VISUAL ANALOGY - THE "MOULD" GAME:
   - Imagine s1 is a mould (like a cookie cutter) with a specific shape
   - The shape is defined by the COUNT of each letter (not the order!)
   - You're sliding this mould over s2, one position at a time
   - At each position, you check: "Does this section of s2 fit the mould?"
   - "Fitting" means: same letters, same counts (order doesn't matter!)
   
   Example: s1 = "abc", s2 = "eidboaoo"
   
   s1's "mould" (frequency signature):
   - 'a': 1, 'b': 1, 'c': 1, all others: 0
   - Represented as: [1, 1, 1, 0, 0, ..., 0] (26 elements)
   
   Now slide a window of size 3 over s2:
   
   Window "eid" (index 0-2):
   - 'e': 1, 'i': 1, 'd': 1 → [0, 0, 0, 1, 1, 0, ..., 1, ...]
   - Compare with s1: [1, 1, 1, 0, ...] ≠ [0, 0, 0, 1, ...] → NO MATCH
   
   Window "idb" (index 1-3):
   - 'i': 1, 'd': 1, 'b': 1 → [0, 1, 0, 1, 0, ..., 1, ...]
   - Compare with s1: [1, 1, 1, 0, ...] ≠ [0, 1, 0, 1, ...] → NO MATCH
   
   Window "dbo" (index 2-4):
   - 'd': 1, 'b': 1, 'o': 1 → [0, 1, 0, 1, 0, ..., 0, 1, ...]
   - Compare with s1: [1, 1, 1, 0, ...] ≠ [0, 1, 0, 1, ...] → NO MATCH
   
   Window "boa" (index 3-5):
   - 'b': 1, 'o': 1, 'a': 1 → [1, 1, 0, 0, 0, ..., 0, 1, ...]
   - Compare with s1: [1, 1, 1, 0, ...] ≠ [1, 1, 0, 0, ..., 0, 1, ...] → NO MATCH
   - Wait, s1 has 'c' but this window has 'o' → different signatures!
   
   Actually, let me recalculate with a better example:
   s1 = "ab", s2 = "eidboaoo"
   
   s1's mould: [1, 1, 0, 0, ..., 0] (1 'a', 1 'b')
   
   Window "ei" (index 0-1): [0, 0, 0, 0, 1, 0, ..., 1, ...] → NO
   Window "id" (index 1-2): [0, 0, 0, 1, 0, ..., 1, ...] → NO
   Window "db" (index 2-3): [0, 1, 0, 1, 0, ...] → NO
   Window "bo" (index 3-4): [0, 1, 0, 0, 0, ..., 0, 1, ...] → NO
   Window "oa" (index 4-5): [1, 0, 0, 0, 0, ..., 0, 1, ...] → NO
   Window "ao" (index 5-6): [1, 0, 0, 0, 0, ..., 0, 1, ...] → NO
   Window "oo" (index 6-7): [0, 0, 0, 0, 0, ..., 0, 2, ...] → NO
   
   Hmm, this example doesn't work. Let me use:
   s1 = "ab", s2 = "eidbaoo"
   
   s1's mould: [1, 1, 0, 0, ..., 0] (1 'a', 1 'b')
   
   Window "ei" (index 0-1): NO
   Window "id" (index 1-2): NO
   Window "db" (index 2-3): NO
   Window "ba" (index 3-4): [1, 1, 0, 0, ...] → MATCH! Return true ✓

2. WHY FREQUENCY ARRAYS WORK FOR PERMUTATIONS:
   - Two strings are permutations ⟺ they have identical character frequencies
   - This is a FUNDAMENTAL property of permutations!
   - Example: "abc", "bca", "cab", "acb", "bac", "cba"
     All have freq = [1, 1, 1, 0, 0, ...]
   - So instead of checking all n! permutations (impossible!),
     we just compare frequency arrays (O(26) = O(1))!
   
   Mathematical insight:
   - A permutation is a rearrangement of characters
   - Rearranging doesn't change counts, only order
   - Therefore: same counts ⟺ one is a rearrangement of the other

3. FIXED-SIZE VS VARIABLE-SIZE SLIDING WINDOW:
   
   This problem uses FIXED-SIZE window (size = n):
   - We ALWAYS maintain window size = length of s1
   - Expand by 1 (j++), then if size > n, shrink by 1 (i++)
   - This ensures we check every possible substring of length n
   
   Compare with variable-size window (like "at most k uniques"):
   - Expand freely, shrink only when constraint violated
   - Window size varies based on constraint
   
   Why fixed-size here?
   - We're looking for EXACTLY the length of s1
   - A permutation must have the same length as the original
   - No need to check windows of other sizes

4. TIME & SPACE COMPLEXITY:
   - Time: O(m) where m = length of s2
     * We iterate through s2 once (j goes 0 to m-1)
     * Each iteration: O(1) operations (increment, decrement, compare 26-element arrays)
     * Vector comparison s1_freq == s2_freq is O(26) = O(1)
     * Total: O(m × 1) = O(m)
   - Space: O(1)
     * Two frequency arrays of fixed size 26
     * Independent of input size (always 26 integers each)
     * Total: O(26) = O(1)

5. WHY WE COMPARE AFTER SHRINKING (NOT BEFORE):
   This is a subtle but important detail!
   
   Order of operations in the loop:
   1. Add s2[j] to window (expand right)
   2. If size > n, remove s2[i] (shrink left)
   3. Compare frequencies
   4. Increment j
   
   Why this order?
   - After step 2, window size is guaranteed to be <= n
   - Specifically, once j >= n-1, window size is exactly n
   - We only want to compare when window size = n (valid permutation length)
   - Comparing before shrinking would check invalid window sizes!
   
   Example: s1 = "abc" (n=3), s2 = "abcd"
   
   j=0: window="a", size=1 < 3, compare (waste, but harmless)
   j=1: window="ab", size=2 < 3, compare (waste, but harmless)
   j=2: window="abc", size=3 = 3, compare (FIRST VALID CHECK!)
   j=3: window="abcd", size=4 > 3
        → shrink: window="bcd", size=3 = 3, compare (VALID CHECK!)
   
   The first n-1 comparisons are "wasted" but don't affect correctness
   (they'll always be false since sizes don't match)

6. COMMON MISTAKES TO AVOID:
   ❌ Forgetting the n > m edge case → may access out of bounds or give wrong answer
   ❌ Comparing BEFORE shrinking → checks invalid window sizes
   ❌ Using if instead of checking every window → might miss the permutation
   ❌ Checking s1_freq == s2_freq before incrementing s2_freq → off-by-one error
   ❌ Not incrementing j → infinite loop
   ❌ Using a map instead of vector → slower (O(log 26) or O(1) avg vs O(1) guaranteed)
   ❌ Comparing strings directly instead of frequencies → order matters (wrong!)

7. TRIGGER WORDS FOR THIS PATTERN:
   ✓ "permutation of s1 in s2"
   ✓ "anagram of s1 in s2"
   ✓ "contains the same characters" (order doesn't matter)
   ✓ "rearrangement of pattern"
   ✓ "substring with same character counts"
   ✓ "fixed-size window with frequency match"

8. VARIATIONS OF THIS PROBLEM:
   - LeetCode 438: Find All Anagrams in a String (return all starting indices)
   - LeetCode 76: Minimum Window Substring (variable-size, must contain all chars)
   - LeetCode 242: Valid Anagram (check if two strings are anagrams, no sliding)
   - LeetCode 49: Group Anagrams (group all anagrams together using freq as key)
   - GFG: Smallest window in a string containing all characters of another string

9. COMPARISON WITH LEETCODE 438 (Find All Anagrams):
   
   | Aspect              | LeetCode 567 (This)       | LeetCode 438 (Find All)  |
   |---------------------|---------------------------|---------------------------|
   | Goal                | Check if ANY exists       | Find ALL starting indices |
   | Return type         | bool (true/false)         | vector<int> (indices)     |
   | Frequency array     | vector<int>(26)           | vector<int>(26)           |
   | Comparison          | s1_freq == s2_freq        | s1_freq == s2_freq        |
   | On match            | return true immediately   | push_back(i), continue    |
   | After loop          | return false              | return ans                |
   | Window size         | Fixed (n)                 | Fixed (n)                 |
   | Core logic          | Identical                 | Identical                 |
   
   Essentially, LeetCode 438 is the "find all" version of this problem!
   The sliding window logic is EXACTLY THE SAME.

10. ALTERNATIVE APPROACHES (and why they're worse):
    
    Approach 1: Generate All Permutations O(n! × m)
    - Generate all n! permutations of s1
    - For each, search in s2 using string::find()
    - Total: O(n! × m) → TLE for n > 10!
    
    Approach 2: Sort and Compare O(m × n log n)
    - For each window of size n in s2, sort it
    - Compare with sorted s1
    - Total: O(m × n log n) → TLE for large inputs
    
    Approach 3: Hash Map O(m)
    - Use unordered_map<char, int> instead of vector<int>
    - Same logic, but map operations are O(1) average (not guaranteed)
    - Slightly slower due to hashing overhead
    - More flexible (works with Unicode, not just 'a'-'z')
    
    Approach 4: Frequency Vector O(m) ← OUR SOLUTION
    - Use vector<int>(26) for lowercase English letters
    - O(1) guaranteed for all operations
    - Fastest for this constraint (only 'a'-'z')
    - Space-efficient (exactly 26 integers)

11. KEY INSIGHT SUMMARY:
    - Permutations = same characters, same counts, different order
    - Frequency array = fingerprint of a string (order-independent)
    - Fixed-size window = check every substring of length n
    - Vector comparison = O(26) = O(1) way to check "same fingerprint"
    - Early return = as soon as we find one match, we're done

12. MEMORY TRICK - THE "DNA MATCHING" ANALOGY:
    Imagine you're a forensic scientist matching DNA samples:
    - s1 is the crime scene DNA (the pattern we're looking for)
    - s2 is a long strand of suspect DNA (where we're searching)
    - DNA is made of 4 bases (A, C, G, T), strings are made of 26 letters
    - Two DNA samples match if they have the same BASE COUNTS (not order!)
    - You're sliding a "scanner" of length n over s2
    - At each position, you analyze the base composition
    - If it matches the crime scene sample → MATCH FOUND!
    
    The frequency array is your "DNA sequencer": it counts each base
    The sliding window is your "scanner": it moves along the DNA strand
    Vector comparison is your "match detector": same counts = same person!

13. PRACTICE PROBLEMS TO REINFORCE:
    - LeetCode 438: Find All Anagrams in a String (do this next!)
    - LeetCode 242: Valid Anagram (simpler, no sliding window)
    - LeetCode 76: Minimum Window Substring (harder, variable-size)
    - LeetCode 49: Group Anagrams (use freq as hash map key)
    - LeetCode 424: Longest Repeating Character Replacement (related pattern)

================================================================================
*/






// class Solution {
// public:
//     bool checkInclusion(string s1, string s2) {
//         int n = s1.size();
//         int m = s2.size();

//         if(n > m){
//             return false;
//         }

//         sort(s1.begin(), s1.end());
//         // T.C : O((m-n) *nlogn)
//         // S.C : O(1)
//         for(int i =0; i<= m-n; i++){
//             string substring = s2.substr(i, n);

//             sort(begin(substring), end(substring));

//             if(s1 == substring){
//                 return true;
//             }
//         }
//         return false;
//     }
// };

// brute approach of permutations
//  class Solution {
//  public:
//      int n;
//      bool result;

//     void solve (int idx, string& s1, string &s2){
//         if(idx == n){
//             if(s2.find(s1) != string::npos){
//                 result = true;
//             }
//             return;
//         }

//         for(int i = idx; i<n; i++){
//             swap(s1[i], s1[idx]);

//             solve(idx+1, s1, s2);

//             swap(s1[i], s1[idx]);

//             if(result == true){
//                 return;
//             }

//         }
//     }

//     bool checkInclusion(string s1, string s2) {
//         n = s1.length();
//         result = false;

//         solve(0, s1, s2);

//         return result;
//     }
// };