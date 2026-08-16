// class Solution {
// public:
//     bool allZero(vector<int>& counter) {
//         for (int& i : counter) {
//             if (i != 0) return false;
//         }
//         return true;
//     }

//     vector<int> findAnagrams(string txt, string pat) {
//         int n = txt.size();
//         int k = pat.size();
//         vector<int> counter(26, 0);
//         vector<int> ans;

//         // count the freq of each char in pat
//         for (char ch : pat) {
//             counter[ch - 'a']++;
//         }

//         int i = 0, j = 0;
//         while (j < n) {
//             counter[txt[j] - 'a']--;

//             if (j - i + 1 == k) {
//                 if (allZero(counter)) {
//                     ans.push_back(i); // store starting index
//                 }
//                 counter[txt[i] - 'a']++; // slide window
//                 i++;
//             }
//             j++;
//         }
//         return ans;
//     }
// };


class Solution {
public:
    // Helper function: checks if all characters in our frequency counter have been matched
    // Think of this as checking if our "shopping list" is completely empty (all items bought)
    // Time: O(26) ≈ O(1) since we always check exactly 26 lowercase letters
    bool allZero(vector<int>& counter) {
        // Iterate through each letter's count in our frequency array
        for (int& i : counter) {
            // If ANY letter still has a non-zero count, pattern isn't matched yet
            // Positive count = we need more of this letter
            // Negative count = we have extra of this letter (not in pattern)
            if (i != 0) return false;
        }
        // All counts are zero → perfect anagram found!
        return true;
    }

    // Main function: Find all starting indices where pattern's anagrams appear in text
    // Pattern: "Sliding Window" - we maintain a fixed-size window (length = pattern)
    // and slide it one character at a time, updating our frequency counter
    // Analogy: Like checking if any 3-letter segment of a sentence contains the same letters as "cat"
    vector<int> findAnagrams(string txt, string pat) {
        int n = txt.size();  // Total length of text we're searching in
        int k = pat.size();  // Window size = pattern length (fixed-size sliding window)
        
        // Frequency counter: tracks how many of each letter we "owe" or "have extra"
        // Index 0 = 'a', Index 1 = 'b', ..., Index 25 = 'z'
        // Positive value = we need this many more of that letter to match pattern
        // Negative value = we have this many extra (letter not in pattern or too many)
        // Zero = perfect match for that letter
        vector<int> counter(26, 0);
        
        // Result vector: stores starting indices of all anagram matches
        vector<int> ans;

        // STEP 1: Initialize counter with pattern's character frequencies
        // We're essentially creating a "shopping list" of letters we need to find
        // Example: pat = "abc" → counter['a'-'a'] = 1, counter['b'-'a'] = 1, counter['c'-'a'] = 1
        for (char ch : pat) {
            counter[ch - 'a']++;  // Increment count for each letter in pattern
        }

        // STEP 2: Sliding Window - Two pointers (i = left, j = right)
        // We expand the window by moving j forward, shrink by moving i forward
        // Window size is always maintained at exactly k characters once it reaches that size
        int i = 0, j = 0;
        
        // Process each character in the text one by one
        while (j < n) {
            // INCLUDE current character (txt[j]) into our window
            // Decrement its count because we "found" one occurrence
            // If it was in pattern, count goes down toward zero
            // If it wasn't in pattern, count goes negative (we have extra)
            counter[txt[j] - 'a']--;

            // Check if window has reached the target size (pattern length)
            if (j - i + 1 == k) {
                // Window is now exactly k characters long
                // Check if ALL letter frequencies match (all counts are zero)
                // This means: every letter in pattern appears exactly the right number of times
                // AND no extra letters are present in our window
                if (allZero(counter)) {
                    // Perfect anagram! Store the starting index of this window
                    ans.push_back(i);
                }
                
                // BEFORE sliding the window forward, we need to REMOVE the leftmost character (txt[i])
                // Why? Because when j moves forward, the window shifts right by 1
                // So txt[i] is no longer in our window, and we "give back" its count
                // If we decremented it earlier, now we increment to undo that effect
                counter[txt[i] - 'a']++;
                
                // Slide the window: move left pointer forward
                // This shrinks the window from the left (we'll expand from right in next iteration)
                i++;
            }
            
            // Expand the window: move right pointer forward
            // In next iteration, we'll include txt[j+1] into our window
            j++;
        }
        
        // Return all starting indices where anagrams were found
        return ans;
    }
};

/*
================================================================================
                    COMPLETE REVISION SUMMARY - LEETCODE 438
================================================================================

PROBLEM: Find All Anagrams in a String
Given text = "cbaebabacb", pattern = "abc"
Output: [0, 6]  (because "cba" at index 0 and "bac" at index 6 are anagrams of "abc")

--------------------------------------------------------------------------------
CORE INTUITION - THE SLIDING WINDOW PATTERN
--------------------------------------------------------------------------------

Think of this like a "moving magnifying glass" or "camera frame" of fixed size:

1. VISUAL ANALOGY:
   - Imagine you have a photo frame that's exactly 3 inches wide (pattern length = 3)
   - You're scanning a long painting (the text) by sliding this frame from left to right
   - At each position, you check: "Does this 3-inch section contain the same colors 
     (letters) as my reference swatch (pattern), just in a different order?"
   
2. THE COUNTER ARRAY - YOUR "SHOPPING LIST":
   - Before starting, write down what letters you need: pat = "aab" → need 2 'a's, 1 'b'
   - counter = [2, 1, 0, 0, ...] (for 'a', 'b', 'c', 'd', ...)
   - As you scan the text, cross off items from your list:
     * See an 'a'? Cross one off (decrement counter['a'])
     * See a 'b'? Cross one off (decrement counter['b'])
     * See a 'z' (not in pattern)? You now have -1 'z's (extra, not needed)
   - When ALL items are crossed off (all zeros), you found an anagram!

3. WHY SLIDING WINDOW WORKS HERE:
   - We're looking for CONTIGUOUS substrings (not subsequences)
   - The substring length is FIXED (must equal pattern length)
   - We need to check EVERY possible window of that size
   - Instead of re-counting from scratch each time (O(k) per window),
     we UPDATE our counter incrementally (O(1) per step)
   
4. STEP-BY-STEP DRY RUN:
   txt = "cbaebabacb", pat = "abc"
   Initial counter: [1, 1, 1, 0, 0, ...] (need 1 'a', 1 'b', 1 'c')
   
   j=0: window="c", counter['c']-- → [1, 1, 0, ...], window size < 3, continue
   j=1: window="cb", counter['b']-- → [1, 0, 0, ...], window size < 3, continue
   j=2: window="cba", counter['a']-- → [0, 0, 0, ...], window size = 3
        allZero() = TRUE! → ans.push_back(0)
        Remove txt[0]='c': counter['c']++ → [0, 0, 1, ...], i=1
   j=3: window="bae", counter['e']-- → [0, 0, 1, -1, ...], window size = 3
        allZero() = FALSE (we have extra 'e' and missing 'c'), i=2
   j=4: window="aeb", counter['b']-- → [...], window size = 3
        allZero() = FALSE, i=3
   j=5: window="eba", counter['a']-- → [...], window size = 3
        allZero() = FALSE, i=4
   j=6: window="bac", counter['c']-- → [0, 0, 0, ...], window size = 3
        allZero() = TRUE! → ans.push_back(6)
        Remove txt[4]='b': counter['b']++, i=5
   ... and so on

5. TIME & SPACE COMPLEXITY:
   - Time: O(n) where n = text length
     * We visit each character exactly once (j goes 0 to n-1)
     * allZero() check is O(26) = O(1) constant time
     * Total: O(n × 1) = O(n)
   - Space: O(1) 
     * counter array is always 26 integers (fixed size, independent of input)
     * ans vector stores output, but that's required, not extra space

6. COMMON MISTAKES TO AVOID:
   ❌ Forgetting to increment counter when removing txt[i] (window slides wrong)
   ❌ Checking allZero() before window reaches size k (checks partial windows)
   ❌ Using counter[txt[j]] instead of counter[txt[j] - 'a'] (wrong indexing)
   ❌ Not handling the case where pattern is longer than text (return empty)
   ❌ Checking allZero() AFTER incrementing counter for txt[i] (checks wrong state)

7. TRIGGER WORDS FOR SLIDING WINDOW PATTERN:
   ✓ "contiguous subarray/substring"
   ✓ "fixed size window" or "window of size k"
   ✓ "find all occurrences of pattern/anagram"
   ✓ "longest/shortest substring with property X"
   ✓ "maximum/minimum sum of subarray of size k"
   ✓ "count of substrings with condition Y"

8. VARIATIONS OF THIS PROBLEM:
   - LeetCode 76: Minimum Window Substring (variable-size window)
   - LeetCode 30: Substring with Concatenation of All Words
   - LeetCode 340: Longest Substring with At Most K Distinct Characters
   - LeetCode 424: Longest Repeating Character Replacement
   - LeetCode 567: String Permutation (check if ANY anagram exists, boolean)

9. KEY TAKEAWAY:
   Sliding window is about MAINTAINING STATE as you move, not recalculating from scratch.
   Think: "What changes when I slide one step right?" → Update incrementally!

================================================================================
*/