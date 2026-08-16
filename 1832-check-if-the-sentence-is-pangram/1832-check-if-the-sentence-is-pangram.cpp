// class Solution {
// public:
//     bool checkIfPangram(string sentence) {
//         vector<int> arr(26, 0);
//         int count = 0;
//         for (char& ch : sentence) {
//             int index = ch - 'a';

//             if (arr[index] == 0) {
//                 arr[index]++;
//                 count++;
//             }
//         }

//         if(count==26){
//             return true;
//         }

//         // for(int &count : arr){
//         //     if(count == 0){
//         //         return false;
//         //     }
//         // }
//         return false;
//     }
// };





class Solution {
public:
    // ============================================
    // PROBLEM: Check if the Sentence Is Pangram
    // ============================================
    // A pangram is a sentence that contains every letter of the alphabet at least once.
    // We need to return true if the sentence is a pangram, false otherwise.
    //
    // Example 1:
    // Input: "thequickbrownfoxjumpsoverthelazydog"
    // Output: true (contains all 26 letters)
    //
    // Example 2:
    // Input: "leetcode"
    // Output: false (only contains a few letters)
    
    bool checkIfPangram(string sentence) {
        // ============================================
        // ANALOGY: The Alphabet Collector's Checklist
        // ============================================
        // Imagine you're a collector trying to collect all 26 letters of the alphabet.
        // You have a checklist with 26 boxes (one for each letter: a, b, c, ..., z).
        // As you read through the sentence, you mark off each letter you find.
        // Once you've marked all 26 boxes, you can stop immediately — you've found a pangram!
        //
        // This is EXACTLY what your code does:
        // - arr[26] = your checklist (26 boxes for 26 letters)
        // - count = how many unique letters you've found so far
        // - When count == 26, you return true immediately (early termination)
        
        // ============================================
        // STEP 1: Initialize Frequency Array and Counter
        // ============================================
        // Create a frequency array of size 26 to track which letters we've seen
        // arr[0] = count of 'a', arr[1] = count of 'b', ..., arr[25] = count of 'z'
        // Initialize all values to 0 (no letters seen yet)
        //
        // WHY ARRAY INSTEAD OF MAP?
        // - Since we know input only contains lowercase English letters (a-z),
        //   we can use a fixed-size array for O(1) access and less memory overhead
        // - This is faster and more space-efficient than unordered_map for this constraint
        //
        // VISUALIZATION:
        // arr = [0, 0, 0, 0, ..., 0]  (26 zeros)
        //        a  b  c  d          z
        vector<int> arr(26, 0);
        
        // Counter to track how many UNIQUE letters we've found so far
        // When this reaches 26, we know we have a pangram and can return early
        // This is an OPTIMIZATION — we don't need to scan the entire string
        // if we've already found all 26 letters
        int count = 0;
        
        // ============================================
        // STEP 2: Traverse the Sentence (Collect Letters)
        // ============================================
        // Iterate through each character in the sentence
        // For each character, mark it as seen in our frequency array
        // If it's a new letter (arr[index] == 0), increment our unique count
        //
        // WHY CHECK arr[index] == 0?
        // - We only want to increment 'count' when we find a NEW letter
        // - If arr[index] > 0, we've already seen this letter, so don't increment count
        // - This ensures 'count' tracks UNIQUE letters, not total letters
        //
        // DRY RUN EXAMPLE 1:
        // sentence = "thequickbrownfoxjumpsoverthelazydog"
        // Initial: arr = [0, 0, 0, ..., 0], count = 0
        //
        // Iteration 1: ch = 't'
        // - index = 't' - 'a' = 19
        // - arr[19] == 0 → new letter!
        // - arr[19] = 1, count = 1
        //
        // Iteration 2: ch = 'h'
        // - index = 'h' - 'a' = 7
        // - arr[7] == 0 → new letter!
        // - arr[7] = 1, count = 2
        //
        // ... continue until count == 26 ...
        //
        // At some point: count == 26 → all letters found!
        // Return true immediately (early termination)
        for (char& ch : sentence) {
            // Map the character to an index (0-25) using: ch - 'a'
            // This works because in ASCII/Unicode, letters are consecutive:
            // 'a' - 'a' = 0, 'b' - 'a' = 1, 'c' - 'a' = 2, ..., 'z' - 'a' = 25
            int index = ch - 'a';
            
            // Check if we've already seen this letter
            // If arr[index] == 0, it means this is a NEW letter we haven't seen before
            if (arr[index] == 0) {
                // Mark this letter as seen (increment its count)
                arr[index]++;
                
                // Increment the unique letter counter
                // This tracks how many DIFFERENT letters we've found so far
                count++;
            }
            
            // NOTE: We don't need an else branch here
            // If arr[index] > 0, we've already seen this letter, so we just skip it
            // (we don't need to increment count again)
        }
        
        // ============================================
        // STEP 3: Check if All 26 Letters Were Found
        // ============================================
        // After scanning the entire sentence, check if we found all 26 letters
        // If count == 26, it means we found every letter of the alphabet at least once
        // Return true (it's a pangram)
        //
        // DRY RUN EXAMPLE 1 (continued):
        // sentence = "thequickbrownfoxjumpsoverthelazydog"
        // After loop: count == 26 (all letters found)
        // Return: true ✓
        //
        // DRY RUN EXAMPLE 2:
        // sentence = "leetcode"
        // After loop: count == 5 (only 'l', 'e', 't', 'c', 'o' found)
        // Return: false (count != 26) ✓
        if(count == 26) {
            return true;
        }
        
        // ============================================
        // STEP 4: Not a Pangram (Fallback)
        // ============================================
        // If we've scanned the entire sentence and count != 26,
        // it means we didn't find all 26 letters of the alphabet
        // Return false (it's not a pangram)
        //
        // ALTERNATIVE APPROACH (commented out in your code):
        // You could also check the frequency array directly:
        // for(int &count : arr) {
        //     if(count == 0) {
        //         return false;  // Found a letter that wasn't seen
        //     }
        // }
        // return true;
        //
        // WHY YOUR APPROACH IS BETTER:
        // - Using a separate 'count' variable is more efficient
        // - You don't need to scan the entire array at the end
        // - You can return early as soon as count == 26 (optimization)
        return false;
    }
    
    // ============================================
    // REVISION SUMMARY (The Mental Model)
    // ============================================
    // THE BIG PICTURE:
    // This is a frequency counting + early termination pattern.
    //
    // ANALOGY:
    // You're a collector trying to collect all 26 letters of the alphabet.
    // You have a checklist with 26 boxes (one for each letter: a, b, c, ..., z).
    // As you read through the sentence, you mark off each letter you find.
    // Once you've marked all 26 boxes, you can stop immediately — you've found a pangram!
    //
    // THE FLOW (Story Version):
    // 1. Setup Phase:
    //    - Create a frequency array of size 26 (for lowercase letters a-z)
    //    - Initialize all counts to 0 (no letters seen yet)
    //    - Initialize count = 0 (tracks unique letters found)
    //
    // 2. Traversal Phase:
    //    - For each character in the sentence:
    //      - Map the character to an index (0-25) using: ch - 'a'
    //      - If arr[index] == 0 (new letter), mark it as seen and increment count
    //      - If arr[index] > 0 (already seen), skip it
    //
    // 3. Check Phase:
    //    - If count == 26, return true (all letters found, it's a pangram)
    //    - Otherwise, return false (not all letters found)
    //
    // KEY INSIGHTS:
    // - Why array instead of map? Because we know the input only contains lowercase
    //   English letters (a-z). An array of size 26 is faster (O(1) access) and uses
    //   less memory than a hash map.
    // - Why use a separate 'count' variable? It allows early termination — we don't
    //   need to scan the entire array at the end to check if all letters were found.
    // - Why check arr[index] == 0? To ensure we only increment 'count' for NEW letters,
    //   not duplicates. This way, 'count' tracks UNIQUE letters.
    // - Time Complexity: O(n) - we traverse the string once, where n = sentence length
    // - Space Complexity: O(1) - the frequency array is always size 26 (constant space)
    //
    // TRIGGER WORDS for This Pattern:
    // - "check if all characters are present"
    // - "contains all letters of the alphabet"
    // - "pangram" / "pangram checking"
    // - "frequency counting with early termination"
    //
    // COMMON MISTAKES TO AVOID:
    // 1. Forgetting to check arr[index] == 0 before incrementing count (would count duplicates)
    // 2. Using a map instead of an array (less efficient for this specific constraint)
    // 3. Not handling the edge case where the sentence is shorter than 26 characters
    //    (can't be a pangram if length < 26, but your code handles this naturally)
    // 4. Scanning the entire array at the end instead of using a 'count' variable
    //    (less efficient, no early termination)
    //
    // COMPANIES THAT ASK THIS:
    // Amazon, Microsoft, Adobe, Google, Facebook/Meta, Bloomberg
};





// Time & Space Complexity Breakdown
// Time Complexity: O(n)

// We traverse the string once, where n = length of the sentence

// Each character is processed in O(1) time (array access and increment)

// Total: O(n)

// Space Complexity: O(1)

// We use a fixed-size array of 26 integers

// This doesn't grow with input size, so it's constant space

// The count variable is O(1) as well





// EXAMPLE 1: Pangram
// sentence = "thequickbrownfoxjumpsoverthelazydog"

// Initial state:
// arr = [0, 0, 0, ..., 0]  (26 zeros)
// count = 0

// Iteration 1: ch = 't'
// - index = 't' - 'a' = 19
// - arr[19] == 0 → new letter!
// - arr[19] = 1, count = 1

// Iteration 2: ch = 'h'
// - index = 'h' - 'a' = 7
// - arr[7] == 0 → new letter!
// - arr[7] = 1, count = 2

// Iteration 3: ch = 'e'
// - index = 'e' - 'a' = 4
// - arr[4] == 0 → new letter!
// - arr[4] = 1, count = 3

// ... continue scanning ...

// At some point (when all 26 letters are found):
// count == 26 → return true immediately!

// Return: true ✓


// EXAMPLE 2: Not a Pangram
// sentence = "leetcode"

// Initial state:
// arr = [0, 0, 0, ..., 0]  (26 zeros)
// count = 0

// Iteration 1: ch = 'l'
// - index = 'l' - 'a' = 11
// - arr[11] == 0 → new letter!
// - arr[11] = 1, count = 1

// Iteration 2: ch = 'e'
// - index = 'e' - 'a' = 4
// - arr[4] == 0 → new letter!
// - arr[4] = 1, count = 2

// Iteration 3: ch = 'e' (duplicate)
// - index = 'e' - 'a' = 4
// - arr[4] == 1 → already seen, skip
// - count remains 2

// Iteration 4: ch = 't'
// - index = 't' - 'a' = 19
// - arr[19] == 0 → new letter!
// - arr[19] = 1, count = 3

// Iteration 5: ch = 'c'
// - index = 'c' - 'a' = 2
// - arr[2] == 0 → new letter!
// - arr[2] = 1, count = 4

// Iteration 6: ch = 'o'
// - index = 'o' - 'a' = 14
// - arr[14] == 0 → new letter!
// - arr[14] = 1, count = 5

// Iteration 7: ch = 'd'
// - index = 'd' - 'a' = 3
// - arr[3] == 0 → new letter!
// - arr[3] = 1, count = 6

// Iteration 8: ch = 'e' (duplicate)
// - index = 'e' - 'a' = 4
// - arr[4] == 1 → already seen, skip
// - count remains 6

// End of string:
// count == 6 (not 26) → return false

// Return: false ✓


