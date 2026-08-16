class Solution {
public:
    // Problem: Find the length of the longest substring WITHOUT repeating characters
    // Example: s = "abcabcbb" → longest unique substring is "abc" → return 3
    // Pattern: Sliding Window + Hash Map (optimization to avoid re-scanning)
    int lengthOfLongestSubstring(string s) {
        // Hash map: stores the LAST SEEN INDEX of each character
        // Key = character, Value = its most recent position in the string
        // Example: if s = "abcba", after processing:
        // mp = {'a': 0, 'b': 1, 'c': 2, ...} then updates as we go
        // Why store index? So we can JUMP left pointer past duplicates instantly
        unordered_map<char, int> mp;
        
        // Two pointers defining our sliding window [left, right]
        // left = start of current substring (inclusive)
        // right = end of current substring (inclusive)
        // Window always contains UNIQUE characters only
        int left = 0;
        
        // Track the maximum length of valid substring found so far
        // Initialize to 0 (edge case: empty string returns 0)
        int maxlen = 0;

        // STEP 1: Expand the window by moving right pointer from 0 to end
        // We're trying to include as many characters as possible
        // as long as we don't have duplicates in our window
        for (int right = 0; right < s.size(); right++) {
            
            // STEP 2: Check if current character s[right] is a DUPLICATE
            // mp.count(s[right]) returns true if we've seen this character BEFORE
            // BUT: we only care if it's a duplicate WITHIN our current window
            // Example: s = "abba", when right=3 (second 'a'), we saw 'a' at index 0
            // But if left already moved past 0, that 'a' is irrelevant
            if (mp.count(s[right])) {
                // DUPLICATE FOUND! We need to shrink window from the left
                // CRITICAL INSIGHT: Don't just move left by 1, JUMP it!
                // Move left to ONE POSITION AFTER the previous occurrence
                // Why? Because everything from old position to current is invalid
                
                // BUT WAIT: Use max(left, ...) to ensure left NEVER moves backward
                // Example: s = "abba"
                // - right=0: mp={'a':0}, left=0, maxlen=1
                // - right=1: mp={'a':0, 'b':1}, left=0, maxlen=2
                // - right=2: s[2]='b' is duplicate at index 1
                //   left = max(0, 1+1) = 2, mp['b']=2, maxlen=2
                // - right=3: s[3]='a' is duplicate at index 0
                //   left = max(2, 0+1) = 2 (NOT 1! because left already at 2)
                //   This prevents left from going backward, which would include old duplicates
                left = max(left, mp[s[right]] + 1);
            }
            
            // STEP 3: Update the last seen index of current character
            // Whether it's a new character or a duplicate, we update its position
            // This ensures mp always has the MOST RECENT index for each character
            // Example: s = "abcba"
            // - right=0: mp['a'] = 0
            // - right=1: mp['b'] = 1
            // - right=2: mp['c'] = 2
            // - right=3: mp['b'] = 3 (update! 'b' seen again)
            // - right=4: mp['a'] = 4 (update! 'a' seen again)
            mp[s[right]] = right;
            
            // STEP 4: Calculate current window length and update maximum
            // Current valid window is [left, right], so length = right - left + 1
            // Example: left=2, right=5 → window includes indices 2,3,4,5 → length = 4
            // We use max() to keep track of the longest valid substring seen so far
            maxlen = max(maxlen, right - left + 1);
        }
        
        // Return the maximum length found
        // Edge cases handled naturally:
        // - Empty string: loop doesn't run, returns 0 ✓
        // - Single char: right=0, left=0, maxlen=1 ✓
        // - All unique: left stays 0, maxlen = s.size() ✓
        // - All same: left jumps each time, maxlen = 1 ✓
        return maxlen;
    }
};

/*
================================================================================
                    COMPLETE REVISION SUMMARY - LEETCODE 3
================================================================================

PROBLEM: Longest Substring Without Repeating Characters
Given s = "abcabcbb"
Output: 3  (because "abc" is the longest substring with all unique characters)
Other examples:
- s = "bbbbb" → output: 1 (just "b")
- s = "pwwkew" → output: 3 ("wke" or "kew")
- s = "" → output: 0
- s = "abcdef" → output: 6 (entire string)

--------------------------------------------------------------------------------
CORE INTUITION - SLIDING WINDOW + HASH MAP OPTIMIZATION
--------------------------------------------------------------------------------

Think of this like reading a book and highlighting the longest sentence 
where no word is repeated:

1. VISUAL ANALOGY - THE "UNIQUE WORDS" GAME:
   - You're scanning a sentence with a highlighter (your window)
   - Rule: You can only highlight words that haven't appeared in your current highlight
   - When you hit a repeated word, you must erase from the START until the repeat is gone
   - Goal: Find the longest highlight you can make
   
   Example: s = "abcabcbb"
   
   Step-by-step:
   right=0: 'a' → highlight "a" → length=1, max=1
   right=1: 'b' → highlight "ab" → length=2, max=2
   right=2: 'c' → highlight "abc" → length=3, max=3 ← NEW RECORD!
   right=3: 'a' → OH NO! 'a' already in "abc"
            → Erase from start until first 'a' is gone
            → New highlight: "bca" (start from index 1) → length=3, max=3
   right=4: 'b' → 'b' already in "bca"
            → Erase until first 'b' is gone
            → New highlight: "cab" (start from index 2) → length=3, max=3
   right=5: 'c' → 'c' already in "cab"
            → Erase until first 'c' is gone
            → New highlight: "abc" (start from index 3) → length=3, max=3
   right=6: 'b' → 'b' already in "abc"
            → Erase until first 'b' is gone
            → New highlight: "cb" (start from index 5) → length=2, max=3
   right=7: 'b' → 'b' already in "cb"
            → Erase until first 'b' is gone
            → New highlight: "b" (start from index 7) → length=1, max=3
   
   Final answer: 3

2. THE HASH MAP - YOUR "MEMORY BOOK":
   - Instead of re-scanning to find duplicates (O(n) per step),
     we use a hash map to INSTANTLY know where we last saw each character
   - mp[char] = last_index_where_we_saw_this_char
   - This turns duplicate detection from O(n) to O(1)!
   
   Why is this crucial?
   Without map: For each right, scan left to right checking duplicates → O(n²)
   With map: For each right, check map in O(1), jump left instantly → O(n)

3. WHY WE USE max(left, mp[s[right]] + 1):
   This is the MOST CRITICAL line - here's why:
   
   Scenario: s = "abba"
   
   right=0: s[0]='a', mp={'a':0}, left=0, maxlen=1
   right=1: s[1]='b', mp={'a':0, 'b':1}, left=0, maxlen=2
   right=2: s[2]='b' → DUPLICATE! mp['b']=1
            left = max(0, 1+1) = 2
            mp['b']=2 (update), maxlen=max(2, 2-2+1)=2
            Current window: "b" (indices 2 to 2)
   right=3: s[3]='a' → DUPLICATE! mp['a']=0
            left = max(2, 0+1) = max(2, 1) = 2 ← KEY!
            Why not 1? Because left is already at 2 (past the old 'a')
            If we set left=1, we'd include the old 'b' at index 1, which is WRONG!
            mp['a']=3 (update), maxlen=max(2, 3-2+1)=2
            Current window: "ba" (indices 2 to 3)
   
   Without max(): left would go backward, including old duplicates → BUG!

4. TIME & SPACE COMPLEXITY:
   - Time: O(n) where n = string length
     * Each character is visited exactly once by right pointer
     * Hash map operations (insert, lookup) are O(1) average
     * Total: O(n)
   - Space: O(min(n, m)) where m = character set size
     * In worst case, map stores all unique characters
     * For lowercase English letters: O(26) = O(1)
     * For full ASCII: O(128) = O(1)
     * For Unicode: O(n) if all characters are unique

5. COMMON MISTAKES TO AVOID:
   ❌ Forgetting max(left, ...) → left moves backward, includes old duplicates
   ❌ Using mp[s[right]] without checking mp.count() → accesses uninitialized keys
   ❌ Updating maxlen BEFORE updating mp → calculates wrong window length
   ❌ Setting left = mp[s[right]] instead of mp[s[right]] + 1 → includes duplicate
   ❌ Not updating mp[s[right]] = right after finding duplicate → stale index
   ❌ Using a set instead of map → can't jump left, only shrink by 1 (slower)

6. TRIGGER WORDS FOR THIS PATTERN:
   ✓ "longest/shortest substring/subarray"
   ✓ "without repeating/unique/distinct characters"
   ✓ "at most k distinct characters"
   ✓ "contiguous segment with property X"
   ✓ "maximum/minimum window satisfying condition"
   ✓ "find all substrings with no duplicates"

7. VARIATIONS OF THIS PROBLEM:
   - LeetCode 159: Longest Substring with At Most Two Distinct Characters
   - LeetCode 340: Longest Substring with At Most K Distinct Characters
   - LeetCode 424: Longest Repeating Character Replacement (can replace k chars)
   - LeetCode 76: Minimum Window Substring (must contain all chars from target)
   - LeetCode 395: Longest Substring with At Least K Repeating Characters

8. ALTERNATIVE APPROACHES (and why they're worse):
   
   Approach 1: Brute Force O(n³)
   - Check every possible substring (n² substrings)
   - For each, scan to check if all unique (O(n))
   - Total: O(n³) → TLE for n > 1000
   
   Approach 2: Brute Force with Set O(n²)
   - For each starting position, expand right until duplicate
   - Use set to track characters in current window
   - Total: O(n²) → Better but still slow for n > 10⁵
   
   Approach 3: Sliding Window with Set O(2n) = O(n)
   - Use set instead of map
   - When duplicate found, shrink from left one by one, removing from set
   - Total: O(n) but each char visited twice (once by right, once by left)
   
   Approach 4: Sliding Window with Map O(n) ← OUR SOLUTION
   - Use map to store last seen index
   - Jump left pointer instantly past duplicates
   - Total: O(n) with each char visited once → OPTIMAL!

9. KEY INSIGHT SUMMARY:
   - Sliding window = maintain a valid range [left, right]
   - Hash map = instant lookup of "where did I see this before?"
   - Jump optimization = don't shrink one-by-one, teleport past the problem
   - max(left, ...) = prevent left from going backward (critical!)
   - Update map AFTER handling duplicate = always have latest index

10. MEMORY TRICK - THE "NAME TAG" ANALOGY:
    Imagine you're at a conference with name tags:
    - Each person (character) wears a name tag with their seat number (index)
    - You're collecting people for a photo (your window)
    - Rule: No two people with same name in the photo
    - When you see a duplicate name, check their name tag:
      * If they're already in your photo, remove everyone from start up to them
      * If they're not in your photo (old name tag), ignore it
    - Keep track of the largest photo you've taken
    
    The hash map is like a directory: "Name → Current Seat Number"
    Updating mp[s[right]] = right is like updating the directory when someone moves seats!

================================================================================
*/


// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         unordered_map<char, int> mp;
//         int left = 0;
//         int maxlen = 0;

//         for (int right = 0; right < s.size(); right++) {
//             if (mp.count(s[right])) {
//                 left = max(left, mp[s[right]] + 1);
//             }
//             mp[s[right]] = right;
//             maxlen = max(maxlen, right - left + 1);
//         }
//         return maxlen;
//     }
// };

// brute approach
// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         unordered_map<char, int> mp;
//         int left = 0;
//         int maxlen = 0;

//         for(int right = 0; right < s.size(); right++){
//             mp[s[right]]++;

//             while(mp[s[left]] > 1){
//                 mp[s[left]]--;
//                 left++;
//             }

//             maxlen = max(maxlen, right - left + 1);
//         }
//         return maxlen;
//     }
// };