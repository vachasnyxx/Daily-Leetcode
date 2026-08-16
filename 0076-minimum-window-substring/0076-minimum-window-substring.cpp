// class Solution {
// public:
//     string minWindow(string s, string t) {
//         int n = s.size();

//         if (t.size() > n) {
//             return "";
//         }

//         unordered_map<char, int> map;

//         // store kr liya

//         for (char& ch : t) {
//             map[ch]++;
//         }

//         int requiredcount = t.size();
//         int i = 0;
//         int j = 0;

//         int minwindowSize = INT_MAX;

//         int start_i = 0;

//         // story starts
//         while (j < n) {
//             char ch = s[j];

//             if (map[ch] > 0) {
//                 requiredcount--;
//             }
//             map[ch]--;

//             while (requiredcount == 0) {
//                 // start shrinking the window

//                 int currWindowSize = j - i + 1;
//                 if (minwindowSize > currWindowSize) {
//                     minwindowSize = currWindowSize;
//                     start_i = i;
//                 }

//                 map[s[i]]++;

//                 if (map[s[i]] > 0) {
//                     requiredcount++;
//                 }
//                 i++;
//             }
//             j++;
//         }
//         return  minwindowSize == INT_MAX ? "" : s.substr(start_i, minwindowSize);
//     }
// };




class Solution {
public:
    // Problem: Find the MINIMUM LENGTH substring of s that contains ALL characters of t
    // Example: s = "ADOBECODEBANC", t = "ABC" → output: "BANC" (length 4)
    // Pattern: Variable-Size Sliding Window + Hash Map (TWO PHASES: expand then shrink)
    // Key insight: Expand until we have all chars, then shrink to find minimum, repeat!
    string minWindow(string s, string t) {
        // Get length of text (s) where we're searching
        int n = s.size();

        // EDGE CASE: If pattern (t) is longer than text (s), impossible to contain it
        // Example: s = "abc", t = "abcd" → can't fit 4 chars in 3-char string
        // Return empty string immediately (no valid window exists)
        if (t.size() > n) {
            return "";
        }

        // STEP 1: Build frequency map for pattern string t
        // This map tracks: "How many of each character do we STILL NEED?"
        // Key = character, Value = count of that character in t
        // POSITIVE value = we need this many more of this character
        // ZERO value = we have exactly what we need
        // NEGATIVE value = we have extra (more than needed)
        // Example: t = "AABC" → map = {'A': 2, 'B': 1, 'C': 1}
        // Initially, all values are positive (we need all of them)
        unordered_map<char, int> map;

        // Store kr liya - Build the "shopping list" of characters we need
        // We're essentially creating a "debt" - we owe these characters
        // As we find them in s, we'll pay off the debt (decrement counts)
        for (char& ch : t) {
            map[ch]++;  // Increment count for each character in t
        }
        // After this loop: map contains our "target requirements"
        // Example: t = "ABC" → map = {'A': 1, 'B': 1, 'C': 1}

        // STEP 2: Initialize tracking variables
        // requiredcount = total number of characters we still need to find
        // Initially, we need ALL characters from t (that's t.size())
        // As we find needed characters, this count decreases
        // When it reaches 0 → we have found ALL required characters!
        int requiredcount = t.size();
        
        // Two pointers for sliding window [i, j]
        // i = left boundary (start of window, inclusive)
        // j = right boundary (end of window, inclusive)
        // Window starts empty and expands as j moves forward
        int i = 0;
        int j = 0;

        // Track the minimum valid window found so far
        // Initialize to INT_MAX (infinity) so any valid window will be smaller
        // This is our "best answer" tracker
        int minwindowSize = INT_MAX;

        // Track the starting index of the minimum window
        // We'll update this whenever we find a smaller valid window
        // At the end, we'll return s.substr(start_i, minwindowSize)
        int start_i = 0;

        // STORY STARTS - THE MAIN ADVENTURE!
        // We're going to scan through string s with our sliding window
        // PHASE 1: Expand window (j++) until we have all required characters
        // PHASE 2: Shrink window (i++) to find minimum size while still valid
        // Repeat until we've checked all possibilities
        while (j < n) {
            // Get current character at right boundary of window
            // This is the NEW character we're about to include in our window
            char ch = s[j];

            // STEP 3: Check if this character is USEFUL (part of our requirements)
            // map[ch] > 0 means: we still NEED this character (it's in t and we haven't found enough)
            // Example: t = "AABC", map = {'A': 2, 'B': 1, 'C': 1}
            // If ch = 'A', map['A'] = 2 > 0 → useful! We need 2 more 'A's
            // If ch = 'D', map['D'] = 0 (not in map, defaults to 0) → not useful
            if (map[ch] > 0) {
                // This character is part of our requirements!
                // We found one of the characters we were looking for
                // Decrement requiredcount because we now need one less character
                // Example: requiredcount = 4, found 'A' → requiredcount = 3
                requiredcount--;
            }
            
            // STEP 4: Update the map for this character (ALWAYS do this!)
            // Decrement the count whether it's useful or not
            // Why? Because this character is now INSIDE our window
            // If it was in t: count goes down (we're paying off debt)
            // If it wasn't in t: count goes negative (we have extra)
            // Example: map = {'A': 1, 'B': 1, 'C': 1}, ch = 'A'
            // After: map = {'A': 0, 'B': 1, 'C': 1} (we found the 'A' we needed!)
            // Example: map = {'A': 0, 'B': 1, 'C': 1}, ch = 'X' (not in t)
            // After: map = {'A': 0, 'B': 1, 'C': 1, 'X': -1} (extra 'X')
            map[ch]--;

            // STEP 5: Check if we have found ALL required characters
            // requiredcount == 0 means: we've found every character from t
            // (possibly with some extras, but that's okay)
            // Now we enter the INNER WHILE LOOP to find the MINIMUM window
            // This is the "shrinking phase" - we try to make window as small as possible
            // while still maintaining all required characters
            while (requiredcount == 0) {
                // We have a VALID window! All characters from t are present.
                // Now let's see if this is the SMALLEST valid window we've found so far.

                // Calculate current window size
                // Window is [i, j], so length = j - i + 1
                // Example: i = 3, j = 7 → window includes indices 3,4,5,6,7 → length = 5
                int currWindowSize = j - i + 1;

                // Check if current window is smaller than our best so far
                // If yes, update our "best answer" trackers
                // Example: minwindowSize = 10, currWindowSize = 5 → update!
                //          minwindowSize = 3, currWindowSize = 5 → don't update
                if (minwindowSize > currWindowSize) {
                    // NEW RECORD! This is the smallest valid window we've found
                    minwindowSize = currWindowSize;  // Update minimum size
                    start_i = i;  // Remember where this window starts
                }
                // After this check: we've recorded the best window so far

                // STEP 6: Try to shrink the window from the LEFT
                // We want to see if we can make the window even smaller
                // by removing characters from the start (i)
                // But we must be careful: don't remove a character we still need!

                // Get the character at the left boundary (about to be removed)
                // This character will NO LONGER be in our window after we increment i
                // We need to "give it back" to our map
                // Example: window = "ADOBEC", i = 0, s[i] = 'A'
                // We're about to remove 'A' from the window

                // STEP 7: Update map for the character being removed
                // Increment its count because it's leaving our window
                // If it was a required character (count was ≤ 0), it goes up
                // If count becomes > 0, it means we NO LONGER have enough of this character!
                // Example: map = {'A': -1, 'B': 0, 'C': 0} (we had extra 'A')
                // After removing 'A': map = {'A': 0, 'B': 0, 'C': 0} (still valid)
                // Example: map = {'A': 0, 'B': 0, 'C': 0} (exactly enough)
                // After removing 'A': map = {'A': 1, 'B': 0, 'C': 0} (INVALID! Need 'A')
                map[s[i]]++;

                // STEP 8: Check if removing this character broke our validity
                // map[s[i]] > 0 means: we just removed a character we STILL NEED
                // The count went from 0 (or negative) to positive
                // This means we no longer have all required characters!
                // We must exit the inner while loop and expand again (j++)
                // Example: map['A'] went from 0 to 1 → we need 'A' again!
                if (map[s[i]] > 0) {
                    // CRITICAL MOMENT: We just removed a required character!
                    // Our window is no longer valid (missing this character)
                    // Increment requiredcount because we now need this character again
                    // This will break the while loop condition (requiredcount == 0)
                    // and we'll go back to expanding the window (j++)
                    requiredcount++;
                }
                // If map[s[i]] <= 0, it means:
                // - Either this character wasn't in t (count was negative, still negative or zero)
                // - Or we had extras of this character (count was -2, now -1, still have enough)
                // In either case, window is still valid, continue shrinking!

                // STEP 9: Move left pointer forward (shrink the window)
                // We've successfully removed s[i] from the window
                // Increment i to move the left boundary to the right
                // The window is now [i+1, j] instead of [i, j]
                i++;
                
                // After incrementing i, we loop back to the while condition:
                // - If requiredcount == 0: window is still valid, try shrinking more!
                // - If requiredcount > 0: window is invalid, exit inner while, expand with j++
            }
            // Inner while loop exited - either:
            // 1. We shrunk too much and lost a required character (requiredcount > 0)
            // 2. We can't shrink anymore (window is as small as possible)
            // Either way, we need to expand the window again to find more valid windows

            // STEP 10: Expand the window by moving right pointer forward
            // In the next iteration, we'll include s[j+1] into our window
            // This might help us find all required characters again (if we lost one)
            // Or it might give us a larger valid window to try shrinking
            j++;
        }
        // Outer while loop finished - we've checked all possible windows!

        // STEP 11: Return the result
        // If minwindowSize is still INT_MAX, it means we never found a valid window
        // Return empty string ""
        // Otherwise, return the actual substring using substr(start, length)
        // Example: start_i = 9, minwindowSize = 4 → s.substr(9, 4) = "BANC"
        return minwindowSize == INT_MAX ? "" : s.substr(start_i, minwindowSize);
    }
};

/*
================================================================================
                    COMPLETE REVISION SUMMARY - LEETCODE 76
================================================================================

PROBLEM: Minimum Window Substring
Given s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"  (the smallest substring of s that contains all of 'A', 'B', 'C')

Other examples:
- s = "a", t = "a" → output: "a"
- s = "a", t = "aa" → output: "" (impossible, t is longer)
- s = "a", t = "b" → output: "" (no 'b' in s)
- s = "aa", t = "aa" → output: "aa"
- s = "bba", t = "ab" → output: "ba" (or "ab" if it existed)

--------------------------------------------------------------------------------
CORE INTUITION - VARIABLE-SIZE SLIDING WINDOW (EXPAND-SHRINK PATTERN)
--------------------------------------------------------------------------------

This is one of the HARDEST sliding window problems because it has TWO PHASES:
1. EXPAND until valid (find all required characters)
2. SHRINK while valid (find minimum size)
3. Repeat until end of string

Think of this like a "treasure hunt" with a "net":

1. VISUAL ANALOGY - THE "FISHING NET" STORY:
   - You're fishing in a river (string s) with a net (your window)
   - Goal: Catch at least one of each required fish type (characters in t)
   - You want the SMALLEST net that still catches all required fish
   - Strategy:
     * Cast your net wide (expand j) until you've caught all required fish
     * Once you have all fish, try to shrink the net from the back (move i forward)
     * Keep shrinking until you're about to lose a required fish
     * Record the net size, then cast wide again to find better catches
     * Repeat until you've checked the entire river
   
   Example: s = "ADOBECODEBANC", t = "ABC"
   
   Think of it like this:
   - Required fish: A, B, C (one of each)
   - You're dragging a net through the river
   
   Step-by-step story:
   
   j=0: 'A' → net="A", caught: {A}, still need: {B, C}, expand
   j=1: 'D' → net="AD", caught: {A, D}, still need: {B, C}, expand
   j=2: 'O' → net="ADO", caught: {A, D, O}, still need: {B, C}, expand
   j=3: 'B' → net="ADOB", caught: {A, D, O, B}, still need: {C}, expand
   j=4: 'E' → net="ADOBE", caught: {A, D, O, B, E}, still need: {C}, expand
   j=5: 'C' → net="ADOBEC", caught: {A, D, O, B, E, C}, GOT THEM ALL! ✓
        
        Now SHRINK from left:
        - Current net: "ADOBEC" (size 6), record: min=6, window="ADOBEC"
        - Remove 'A': net="DOBEC", lost 'A'! (need it again)
        - Exit shrink mode, go back to expanding
        
   j=6: 'O' → net="DOBECO", caught all again! 
        SHRINK:
        - Current net: "DOBECO" (size 6), min=6 (no update)
        - Remove 'D': net="OBECO", still got all (D wasn't required)
        - Remove 'O': net="BECO", still got all (extra O)
        - Remove 'B': net="ECO", lost 'B'! (need it again)
        - Exit shrink mode
        
   j=7: 'D' → net="ECOD", still missing 'B', expand
   j=8: 'E' → net="ECODE", still missing 'B', expand
   j=9: 'B' → net="ECODEB", got all again!
        SHRINK:
        - Current net: "ECODEB" (size 6), min=6 (no update)
        - Remove 'E': net="CODEB", still got all
        - Remove 'C': net="ODEB", lost 'C'! 
        - Exit shrink mode
        
   j=10: 'A' → net="ODEBA", got all again!
        SHRINK:
        - Current net: "ODEBA" (size 5), min=5 (NEW RECORD!)
        - Remove 'O': net="DEBA", still got all
        - Remove 'D': net="EBA", still got all
        - Remove 'E': net="BA", lost 'A'!
        - Exit shrink mode
        
   j=11: 'N' → net="BAN", missing 'C', expand
   j=12: 'C' → net="BANC", got all again!
        SHRINK:
        - Current net: "BANC" (size 4), min=4 (NEW RECORD!) ← THIS IS OUR ANSWER!
        - Remove 'B': net="ANC", lost 'B'!
        - Exit shrink mode
        
   j=13: end of string, stop
   
   Final answer: "BANC" (size 4)

2. THE MAP - YOUR "FISH COUNTER":
   - Unlike previous problems, this map tracks DEBT/INVENTORY
   - POSITIVE value = we OWE this many (still need to find them)
   - ZERO value = we have EXACTLY what we need (perfect!)
   - NEGATIVE value = we have EXTRA (more than needed)
   
   Example: t = "AABC"
   Initial map: {'A': 2, 'B': 1, 'C': 1} (we need these)
   
   As we find characters:
   - Found 'A': map['A'] = 1 (still need 1 more 'A')
   - Found 'A': map['A'] = 0 (got exactly what we need!)
   - Found 'A': map['A'] = -1 (we have 1 extra 'A')
   - Found 'B': map['B'] = 0 (got what we need)
   - Found 'X': map['X'] = -1 (extra, not in t)
   
   requiredcount tracks: "How many total characters do we still need?"
   - Starts at t.size() (total characters in pattern)
   - Decrements when we find a NEEDED character (map[ch] > 0)
   - Increments when we REMOVE a NEEDED character (map[ch] becomes > 0)
   - When requiredcount == 0: WE HAVE ALL REQUIRED CHARACTERS!

3. WHY TWO WHILE LOOPS (NESTED STRUCTURE):
   
   Outer while (j < n): "Keep scanning the string"
   - This ensures we check every possible window
   - We expand j from 0 to n-1
   
   Inner while (requiredcount == 0): "Shrink while valid"
   - This finds the MINIMUM window for each valid configuration
   - We shrink i as much as possible without losing validity
   - We exit when we're about to lose a required character
   
   This nested structure is CRUCIAL:
   - Expand until valid → Shrink to minimum → Record → Expand again → Repeat
   - It's like: "Find a valid window, optimize it, then find the next one"

4. THE CRITICAL MAP UPDATE LOGIC:
   
   When ADDING a character (s[j]):
   - If map[ch] > 0: it was needed, decrement requiredcount
   - Always: map[ch]-- (it's now in our window)
   
   When REMOVING a character (s[i]):
   - Always: map[ch]++ (it's leaving our window)
   - If map[ch] > 0: we just lost a needed character, increment requiredcount
   
   Why this works:
   - Positive → Zero/Negative: "Paying off debt" (found what we needed)
   - Zero/Negative → Positive: "Going back into debt" (lost what we had)
   - requiredcount tracks the "total debt" across all characters

5. TIME & SPACE COMPLEXITY:
   - Time: O(n + m) where n = s.length, m = t.length
     * Building initial map: O(m) - iterate through t once
     * Scanning s: O(n) - j goes from 0 to n-1
     * Each character added once (j++) and removed at most once (i++)
     * Map operations are O(1) average
     * Total: O(m + n) = O(n) since m ≤ n
   - Space: O(m) or O(k) where k = character set size
     * Map stores at most all unique characters from t
     * For lowercase English: O(26) = O(1)
     * For full ASCII: O(128) = O(1)
     * In general: O(min(m, k))

6. COMMON MISTAKES TO AVOID:
   ❌ Not checking t.size() > n edge case → may access out of bounds
   ❌ Using if instead of while for inner loop → doesn't shrink enough
   ❌ Decrementing requiredcount for ALL characters → counts extras incorrectly
   ❌ Incrementing requiredcount BEFORE updating map → off-by-one error
   ❌ Not updating map for every character (both add and remove) → wrong counts
   ❌ Checking requiredcount == 0 before adding s[j] → misses valid windows
   ❌ Returning s.substr(start_i, minwindowSize) without checking INT_MAX → crash
   ❌ Using map[ch]-- without checking map[ch] > 0 first → wrong requiredcount

7. TRIGGER WORDS FOR THIS PATTERN:
   ✓ "minimum/shortest substring containing all characters of"
   ✓ "smallest window that has all elements of"
   ✓ "minimum length subarray with all required elements"
   ✓ "shortest segment containing"
   ✓ "minimum size window with"
   ✓ "smallest substring with all characters from pattern"

8. VARIATIONS OF THIS PROBLEM:
   - LeetCode 567: Permutation in String (fixed-size window, exact match)
   - LeetCode 438: Find All Anagrams in a String (fixed-size, all indices)
   - LeetCode 30: Substring with Concatenation of All Words (words, not chars)
   - GFG: Smallest window in a string containing all characters of another string
   - LeetCode 239: Sliding Window Maximum (different constraint, same technique)

9. COMPARISON WITH OTHER SLIDING WINDOW PROBLEMS:
   
   | Problem              | Window Type    | Constraint              | Goal           |
   |----------------------|----------------|-------------------------|----------------|
   | LeetCode 3           | Variable       | All unique              | Max length     |
   | GFG K Uniques        | Variable       | Exactly k uniques       | Max length     |
   | LeetCode 567         | Fixed          | Exact frequency match   | Boolean        |
   | LeetCode 76 (This)   | Variable       | Contains all chars      | Min length     |
   
   Key difference: This is the only one asking for MINIMUM length!
   All others ask for maximum length or existence check.

10. ALTERNATIVE APPROACHES (and why they're worse):
    
    Approach 1: Check All Substrings O(n³)
    - Generate all O(n²) substrings
    - For each, check if it contains all chars from t: O(n)
    - Total: O(n³) → TLE for n > 1000
    
    Approach 2: Two Pointers Without Map O(n²)
    - For each starting position i, expand j until valid
    - Check validity by scanning: O(n) per window
    - Total: O(n²) → Better but still slow
    
    Approach 3: Sliding Window With Map O(n) ← OUR SOLUTION
    - Use map to track requirements in O(1)
    - Each character added/removed once
    - Total: O(n) → OPTIMAL!

11. KEY INSIGHT SUMMARY:
    - Two-phase sliding window: expand until valid, shrink while valid
    - Map tracks debt: positive = need it, zero = perfect, negative = extra
    - requiredcount = "total debt" across all characters
    - Nested while loops: outer scans, inner optimizes
    - Record best answer during shrinking phase (when valid)

12. MEMORY TRICK - THE "GROCERY SHOPPING" ANALOGY:
    Imagine you're shopping with a list (t = "ABC"):
    - Your shopping cart is the window [i, j]
    - Your list says: need 1 A, 1 B, 1 C
    - You walk through the store (scan s left to right)
    - PHASE 1 (j++): Put items in cart until you have everything on your list
    - PHASE 2 (i++): Remove items from the START of your cart
      * If it's not on your list (D, E, etc.) → remove it, still valid
      * If it's on your list but you have extras → remove it, still valid
      * If it's on your list and you need it → STOP! Put it back!
    - Record your cart size, then continue shopping for a smaller combination
    - Goal: Find the smallest cart that still has everything on your list!
    
    The map is your "inventory tracker": what you need vs what you have
    requiredcount is your "items left to find" counter
    The two while loops are: "Fill cart" → "Optimize cart" → Repeat!

13. PRACTICE PROBLEMS TO REINFORCE:
    - LeetCode 567: Permutation in String (easier, fixed-size)
    - LeetCode 438: Find All Anagrams (similar, but find all)
    - LeetCode 30: Substring with Concatenation of All Words (harder)
    - GFG: Smallest window containing all characters (same problem)
    - LeetCode 239: Sliding Window Maximum (different pattern, same technique)

14. DEBUGGING TIPS:
    - Print map state at each step to see what's happening
    - Track requiredcount carefully - it's the key to validity
    - Remember: map values can go negative (extras are okay!)
    - The answer is recorded during the INNER while loop, not outer
    - If stuck, trace through with s="ADOBECODEBANC", t="ABC" step by step

================================================================================
*/