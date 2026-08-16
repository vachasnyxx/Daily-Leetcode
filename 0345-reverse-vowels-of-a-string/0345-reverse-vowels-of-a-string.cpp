// class Solution {
// public:
//     bool isVowel(char& ch) {
//         if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
//             ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
//             return true;
//         }
//         return false;
//     }

//     string reverseVowels(string s) {
//         int n = s.size();

//         int i = 0;
//         int j = n - 1;

//         while (i < j) {
//             if (!isVowel(s[i])) {
//                 i++;
//             } else if (!isVowel(s[j])) {
//                 j--;
//             } else { // both are vowel

//                 swap(s[i], s[j]);
//                 i++;
//                 j--;
//             }
//         }
//         return s;
//     }
// };


// The Analogy: The Bookend Swap Story
// Imagine you're a librarian organizing a bookshelf:

// You have a row of books: ["H", "a", "l", "l", "o"]

// Some books are "special" (vowels: a, e, i, o, u, A, E, I, O, U)

// You need to reverse only the special books, keeping everything else in place

// Your strategy:

// Put one finger at the left end (i), one at the right end (j)

// Move i forward until you find a special book (vowel)

// Move j backward until you find a special book (vowel)

// Swap them, then move both fingers inward

// Repeat until the fingers meet

// This is EXACTLY what your code does!





class Solution {
public:
    // ============================================
    // HELPER FUNCTION: Check if a Character is a Vowel
    // ============================================
    // This function takes a character reference and returns true if it's a vowel
    // (either lowercase or uppercase), false otherwise
    //
    // WHY A HELPER FUNCTION?
    // - It makes the main logic cleaner and more readable
    // - We can call this function multiple times without repeating the condition
    // - It's easier to test and debug separately
    // - Interviewers love seeing clean, modular code!
    //
    // WHY PASS BY REFERENCE (char&)?
    // - Avoids copying the character (minor optimization, but good practice)
    // - Shows you understand pass-by-reference vs pass-by-value
    bool isVowel(char& ch) {
        // Check if the character is any of the 10 vowels (5 lowercase + 5 uppercase)
        // Return true if it matches any vowel, false otherwise
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
            return true;
        }
        return false;
    }

    // ============================================
    // MAIN FUNCTION: Reverse Vowels in a String
    // ============================================
    string reverseVowels(string s) {
        // ============================================
        // STEP 1: Get the Length of the String
        // ============================================
        // Store the total length of the string for later calculations
        int n = s.size();

        // ============================================
        // STEP 2: Initialize Two Pointers
        // ============================================
        // i = left pointer (starts at the beginning of the string)
        // j = right pointer (starts at the end of the string)
        //
        // KEY INSIGHT: This is a "two pointers moving toward each other" pattern
        // - i moves forward (left to right)
        // - j moves backward (right to left)
        // - They meet in the middle
        // This is different from the "two pointers moving in same direction" pattern
        // we saw in String Compression (LC 443)
        int i = 0;
        int j = n - 1;

        // ============================================
        // STEP 3: Main Loop - Two Pointers Moving Toward Each Other
        // ============================================
        // Continue until the pointers meet or cross
        // When i >= j, we've processed all characters
        //
        // Example: s = "hello", n = 5
        // Initial: i = 0, j = 4
        // Iteration 1: i = 0, j = 4 → swap 'h' and 'o'? No, 'h' is not a vowel
        // Iteration 2: i = 1, j = 4 → swap 'e' and 'o'? Yes, both are vowels!
        // Iteration 3: i = 2, j = 3 → i >= j, exit loop
        while (i < j) {
            // ============================================
            // CASE 1: Left Character is NOT a Vowel
            // ============================================
            // If s[i] is not a vowel, we don't want to swap it
            // Move the left pointer forward to find the next vowel
            //
            // Example: s = "hello", i = 0, s[0] = 'h' (not a vowel)
            // Action: i++ → i = 1
            if (!isVowel(s[i])) {
                i++;
            }
            // ============================================
            // CASE 2: Right Character is NOT a Vowel
            // ============================================
            // If s[j] is not a vowel, we don't want to swap it
            // Move the right pointer backward to find the next vowel
            //
            // NOTE: We use 'else if' here because we only check this
            // if the left character IS a vowel (from the first condition)
            //
            // Example: s = "hello", i = 1 (vowel 'e'), j = 4, s[4] = 'o' (vowel)
            // This condition is skipped because s[j] IS a vowel
            else if (!isVowel(s[j])) {
                j--;
            }
            // ============================================
            // CASE 3: Both Characters are Vowels
            // ============================================
            // If both s[i] and s[j] are vowels, we swap them
            // Then move both pointers inward (i++, j--)
            //
            // Example: s = "hello", i = 1 (vowel 'e'), j = 4 (vowel 'o')
            // Action: swap('e', 'o') → s = "holle", then i = 2, j = 3
            else { // both are vowel
                // Swap the two vowels
                swap(s[i], s[j]);

                // Move both pointers inward
                i++;  // Left pointer moves right
                j--;  // Right pointer moves left
            }
        }

        // ============================================
        // STEP 4: Return the Modified String
        // ============================================
        // The string 's' has been modified in-place (vowels reversed)
        // Return the modified string
        //
        // Example: s = "hello" → after processing: s = "holle"
        // Return: "holle"
        return s;
    }
};




// Input: s = "leetcode"

// Initial state:
// s = "leetcode", n = 8
// i = 0, j = 7

// Iteration 1:
// - s[0] = 'l' (not a vowel) → i++ → i = 1
// - State: i = 1, j = 7

// Iteration 2:
// - s[1] = 'e' (vowel), s[7] = 'e' (vowel) → both are vowels!
// - Swap: s[1] and s[7] → s = "leetcodo" (wait, that's wrong, let me recalculate...)
//   Actually: s = "leetcode", swap s[1]='e' and s[7]='e' → s = "leetcode" (no change, same character)
// - i++, j-- → i = 2, j = 6
// - State: i = 2, j = 6, s = "leetcode"

// Iteration 3:
// - s[2] = 'e' (vowel), s[6] = 'd' (not a vowel) → j-- → j = 5
// - State: i = 2, j = 5, s = "leetcode"

// Iteration 4:
// - s[2] = 'e' (vowel), s[5] = 'o' (vowel) → both are vowels!
// - Swap: s[2]='e' and s[5]='o' → s = "loetcede"
// - i++, j-- → i = 3, j = 4
// - State: i = 3, j = 4, s = "loetcede"

// Iteration 5:
// - s[3] = 't' (not a vowel) → i++ → i = 4
// - State: i = 4, j = 4

// Exit loop: i = 4, j = 4 → i >= j, loop ends

// Return: "loetcede"



// Revision Summary (The Mental Model)
// THE BIG PICTURE:

// This is a two-pointer + helper function pattern with conditional skipping.

// Analogy: You're a librarian organizing a bookshelf. Some books are "special" (vowels), and you need to reverse only the special books, keeping everything else in place. You put one finger at each end, move them inward until both find special books, swap them, and repeat.

// THE FLOW (Story Version):

// Setup Phase:

// Get the length n of the string

// Initialize two pointers: i = 0 (left), j = n - 1 (right)

// Main Loop (Two Pointers Moving Toward Each Other):

// While i < j (pointers haven't met):

// Case 1: If s[i] is NOT a vowel → move i forward (i++)

// Case 2: If s[j] is NOT a vowel → move j backward (j--)

// Case 3: If BOTH are vowels → swap them, then move both inward (i++, j--)

// Return the modified string

// KEY INSIGHTS:

// Why two pointers moving toward each other? This is optimal for reversing or swapping elements from opposite ends. It's O(n) time and O(1) space.

// Why a helper function? It makes the code cleaner, more readable, and easier to test. Interviewers love modular code!

// Why pass by reference (char&)? It avoids copying the character (minor optimization) and shows you understand C++ semantics.

// Why else if for the second condition? We only check the right pointer if the left pointer IS pointing to a vowel. If the left is not a vowel, we just move it forward and re-check in the next iteration.

// Time Complexity: O(n) - each character is visited at most once by either i or j

// Space Complexity: O(1) - we only use a few integer variables (i, j, n)

// TRIGGER WORDS for This Pattern:

// "reverse vowels"

// "reverse only certain elements"

// "two pointers from both ends"

// "swap elements conditionally"

// "palindrome checking" (similar pattern)

// COMMON MISTAKES TO AVOID:

// Forgetting to handle both lowercase and uppercase vowels

// Using i <= j instead of i < j (can cause unnecessary swaps or infinite loops)

// Not using else if for the second condition (can cause both pointers to move in the same iteration when only one should move)

// Forgetting to move both pointers after swapping (can cause infinite loops)

// Not using a helper function (makes the code harder to read and debug)

// COMPANIES THAT ASK THIS:
// Amazon, Microsoft, Adobe, Google, Facebook/Meta, Bloomberg

// Time & Space Complexity Breakdown
// Time Complexity: O(n)

// In the worst case, both pointers traverse the entire string once

// Each character is visited at most once by either i or j

// Total: O(n)

// Space Complexity: O(1)

// We only use a few integer variables: i, j, n

// The helper function isVowel uses O(1) space

// We're modifying the string in-place, so no extra space is used

