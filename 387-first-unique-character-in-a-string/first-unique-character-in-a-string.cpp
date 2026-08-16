// class Solution {
// public:
//     int firstUniqChar(string s) {
//         int arr[26] = {0};

//         int n = s.length();

//         for (int i = 0; i < n; i++) {
//             char ch = s[i];

//             arr[ch - 'a']++;
//         }

//         for (int i = 0; i < n; i++) {
//             char ch = s[i];
//             if (arr[ch - 'a'] == 1) {
//                 return i;
//             }
//         }

//         return -1;
//     }
// };



// The Analogy: The Attendance Register Story
// Imagine you're a teacher checking attendance in a classroom:

// You have a list of student names in order: ["alice", "bob", "charlie", "bob", "diana"]

// You need to find the first student who is present exactly once (unique attendance)

// You can't just look at the list once — you need to:

// First pass: Count how many times each student appears

// Second pass: Go through the list in order and find the first student with count = 1

// This is EXACTLY what your code does!



class Solution {
public:
    int firstUniqChar(string s) {
        // ============================================
        // STEP 1: Initialize Frequency Array
        // ============================================
        // Create an array of size 26 to store frequency of each lowercase letter
        // arr[0] = count of 'a', arr[1] = count of 'b', ..., arr[25] = count of 'z'
        // Initialize all values to 0 (no characters seen yet)
        //
        // WHY ARRAY INSTEAD OF MAP?
        // - Since we know input only contains lowercase English letters (a-z),
        //   we can use a fixed-size array for O(1) access and less memory overhead
        // - This is faster and more space-efficient than unordered_map for this constraint
        int arr[26] = {0};

        // Get the length of the string
        int n = s.length();

        // ============================================
        // STEP 2: First Pass - Count Frequencies
        // ============================================
        // Traverse the entire string once to count how many times each character appears
        // This is our "attendance counting" phase
        for (int i = 0; i < n; i++) {
            // Get the current character at position i
            char ch = s[i];

            // Map the character to an index (0-25) using: ch - 'a'
            // This works because in ASCII/Unicode, letters are consecutive:
            // 'a' - 'a' = 0, 'b' - 'a' = 1, 'c' - 'a' = 2, ..., 'z' - 'a' = 25
            // Increment the count for this character
            arr[ch - 'a']++;
        }

        // After this loop, arr contains the frequency of each character
        // Example: s = "leetcode"
        // arr['l'-'a'] = 1, arr['e'-'a'] = 3, arr['t'-'a'] = 1, arr['c'-'a'] = 1, arr['o'-'a'] = 1, arr['d'-'a'] = 1

        // ============================================
        // STEP 3: Second Pass - Find First Unique
        // ============================================
        // Traverse the string AGAIN in the original order
        // For each character, check if its frequency is exactly 1
        // The FIRST character with frequency 1 is our answer
        //
        // WHY TWO PASSES?
        // - We need to return the INDEX of the first unique character
        // - The first pass gives us frequencies, but we need to check in ORIGINAL ORDER
        // - By iterating again from left to right, we guarantee we find the FIRST unique
        for (int i = 0; i < n; i++) {
            // Get the current character at position i
            char ch = s[i];

            // Check if this character appears exactly once in the entire string
            if (arr[ch - 'a'] == 1) {
                // Found it! Return the current index
                // This is the first (leftmost) character with frequency 1
                return i;
            }
        }

        // ============================================
        // STEP 4: No Unique Character Found
        // ============================================
        // If we've gone through the entire string and haven't found any character
        // with frequency 1, it means all characters appear more than once
        // Return -1 to indicate no unique character exists
        return -1;
    }
};




// Revision Summary (The Mental Model)
// THE BIG PICTURE:

// This is a frequency counting + two-pass pattern.

// Analogy: You're a teacher checking attendance. You need to find the first student who appears exactly once in the attendance list. You can't do this in one pass — you need to count everyone first, then check in order.

// THE FLOW (Story Version):

// Setup Phase:

// Create a frequency array of size 26 (for lowercase letters a-z)

// Initialize all counts to 0

// First Pass (Counting Phase):

// Traverse the string from left to right

// For each character, increment its count in the frequency array

// Use ch - 'a' to map characters to indices 0-25

// Second Pass (Finding Phase):

// Traverse the string AGAIN from left to right (preserves original order)

// For each character, check if its frequency is exactly 1

// Return the index of the FIRST character with frequency 1

// Edge Case:

// If no character has frequency 1, return -1

// KEY INSIGHTS:

// Why array instead of map? Because we know the input only contains lowercase English letters (a-z). An array of size 26 is faster (O(1) access) and uses less memory than a hash map.

// Why two passes? Because we need to return the INDEX of the first unique character. The first pass gives us frequencies, but we need to check in the ORIGINAL order to find the FIRST one.

// Time Complexity: O(n) - we traverse the string twice, which is still O(n)

// Space Complexity: O(1) - the frequency array is always size 26, regardless of input size (constant space)

// TRIGGER WORDS for This Pattern:

// "first unique character"

// "first non-repeating character"

// "character that appears exactly once"

// "find the index of the first..."

// COMMON MISTAKES TO AVOID:

// Trying to do this in one pass (you can't know if a character is unique until you've seen the entire string)

// Forgetting to use ch - 'a' to map characters to array indices

// Returning the character instead of its index

// Not handling the edge case where no unique character exists (return -1)

// Using a map when an array is sufficient (less efficient for this specific constraint)

// COMPANIES THAT ASK THIS:
// Amazon, Microsoft, Adobe, Flipkart, Google (as a warm-up), Facebook/Meta

// Time & Space Complexity Breakdown
// Time Complexity: O(n)

// First pass: O(n) - traverse the entire string once

// Second pass: O(n) - traverse the entire string once (worst case)

// Total: O(n) + O(n) = O(n)

// Space Complexity: O(1)

// We use a fixed-size array of 26 integers

// This doesn't grow with input size, so it's constant space

// (If we used a hash map, it would be O(k) where k = unique characters, but still O(1) for lowercase letters)

