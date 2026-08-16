// class Solution {
// public:
//     bool repeatedSubstringPattern(string s) {
//         int n = s.size();

//         for (int l = n / 2; l >= 1; l--) {
//             if (n % l == 0) {
//                 int times = n / l;

//                 string pattern = s.substr(0, l);
//                 string newstr = "";

//                 while (times--) {
//                     newstr += pattern;
//                 }

//                 if (newstr == s) {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
// };

// The Analogy: The Wallpaper Pattern Story
// Imagine you're a wallpaper installer, and you have a long strip of wallpaper with a repeating pattern:

// The wallpaper is: "abcabcabcabc" (length 12)

// You need to figure out: Is this made by repeating a smaller pattern?

// Your strategy:

// Try different pattern lengths (starting from the largest possible: half the length)

// For each length, check if it divides evenly into the total length

// If yes, extract the pattern and repeat it to see if it reconstructs the original string

// If it matches, you found the repeating pattern!

// This is EXACTLY what your code does!






class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        // ============================================
        // STEP 1: Get the Length of the String
        // ============================================
        // Store the total length of the string for later calculations
        int n = s.size();

        // ============================================
        // STEP 2: Try Different Pattern Lengths
        // ============================================
        // We'll try pattern lengths from n/2 down to 1
        //
        // WHY START FROM n/2?
        // - A repeating pattern must appear at least TWICE in the string
        // - If the pattern length is greater than n/2, it can't repeat even twice
        // - Example: s = "abcabc" (length 6), max pattern length = 3 (which is 6/2)
        // - Example: s = "abab" (length 4), max pattern length = 2 (which is 4/2)
        //
        // WHY GO DOWNWARDS (n/2 to 1)?
        // - We want to find the LARGEST repeating pattern first
        // - If we find one, we can return immediately (optimization)
        // - This is more efficient than going from 1 to n/2
        for (int l = n / 2; l >= 1; l--) {
            // ============================================
            // STEP 3: Check if Length Divides Evenly
            // ============================================
            // A repeating pattern must divide the total length evenly
            // If n % l != 0, the pattern can't repeat an integer number of times
            //
            // Example: s = "abcabcabc" (length 9)
            // - l = 4: 9 % 4 = 1 (not divisible, skip)
            // - l = 3: 9 % 3 = 0 (divisible, check this pattern)
            // - l = 2: 9 % 2 = 1 (not divisible, skip)
            // - l = 1: 9 % 1 = 0 (divisible, check this pattern)
            if (n % l == 0) {
                // ============================================
                // STEP 4: Calculate How Many Times Pattern Should Repeat
                // ============================================
                // If the pattern length is l, and total length is n,
                // the pattern should repeat exactly (n / l) times
                //
                // Example: s = "abcabcabc" (length 9), l = 3
                // times = 9 / 3 = 3 (pattern should repeat 3 times)
                int times = n / l;

                // ============================================
                // STEP 5: Extract the Candidate Pattern
                // ============================================
                // The pattern is the first l characters of the string
                // We assume this is the repeating unit and test it
                //
                // Example: s = "abcabcabc", l = 3
                // pattern = s.substr(0, 3) = "abc"
                string pattern = s.substr(0, l);

                // ============================================
                // STEP 6: Reconstruct the String from the Pattern
                // ============================================
                // Create a new string by repeating the pattern 'times' number of times
                // This is our "test" to see if the pattern actually repeats
                //
                // Example: pattern = "abc", times = 3
                // newstr = "abc" + "abc" + "abc" = "abcabcabc"
                string newstr = "";

                // Repeat the pattern 'times' number of times
                while (times--) {
                    newstr += pattern;
                }

                // ============================================
                // STEP 7: Check if Reconstructed String Matches Original
                // ============================================
                // If the reconstructed string equals the original string,
                // it means the original string IS made by repeating this pattern
                // Return true immediately (we found a valid repeating pattern)
                //
                // Example: newstr = "abcabcabc", s = "abcabcabc"
                // They match, so return true
                if (newstr == s) {
                    return true;
                }
            }
        }

        // ============================================
        // STEP 8: No Repeating Pattern Found
        // ============================================
        // If we've tried all possible pattern lengths (from n/2 down to 1)
        // and none of them reconstruct the original string,
        // it means the string is NOT made of a repeating pattern
        // Return false
        //
        // Example: s = "abcab" (length 5)
        // - l = 2: 5 % 2 = 1 (not divisible, skip)
        // - l = 1: 5 % 1 = 0 (divisible), pattern = "a", newstr = "aaaaa" ≠ "abcab"
        // No pattern works, return false
        return false;
    }
};




// Revision Summary (The Mental Model)
// THE BIG PICTURE:

// This is a divisor checking + pattern reconstruction pattern.

// Analogy: You're a wallpaper installer checking if a long strip of wallpaper is made by repeating a smaller pattern. You try different pattern lengths (starting from the largest possible), check if they divide evenly, and reconstruct the string to verify.

// THE FLOW (Story Version):

// Setup Phase:

// Get the total length n of the string

// We'll try pattern lengths from n/2 down to 1

// For Each Pattern Length l:

// Check if n % l == 0 (pattern must divide evenly into total length)

// If yes, calculate times = n / l (how many times the pattern should repeat)

// Extract the candidate pattern: pattern = s.substr(0, l)

// Reconstruct the string: newstr = pattern repeated times times

// If newstr == s, return true (found a valid repeating pattern)

// Edge Case:

// If no pattern length works, return false

// KEY INSIGHTS:

// Why start from n/2? A repeating pattern must appear at least twice. If the pattern length is greater than n/2, it can't repeat even twice.

// Why check divisibility? If the pattern length doesn't divide evenly into the total length, the pattern can't repeat an integer number of times to form the string.

// Why reconstruct the string? This is a brute-force but correct way to verify if the pattern actually repeats. There's a more efficient KMP-based solution, but this is intuitive and works well for interview settings.

// Time Complexity: O(n²) in worst case - we try O(n) pattern lengths, and for each we do O(n) work to reconstruct and compare strings

// Space Complexity: O(n) - we create a new string of length n for each pattern we test

// TRIGGER WORDS for This Pattern:

// "repeated substring pattern"

// "made by repeating a substring"

// "periodic string"

// "string is a repetition of"

// COMMON MISTAKES TO AVOID:

// Starting from length 1 instead of n/2 (you'd miss the optimization of finding the largest pattern first)

// Forgetting to check divisibility (n % l == 0) before testing a pattern

// Off-by-one errors in the loop (remember: l >= 1, not l > 1)

// Not handling the edge case where no pattern exists (return false)

// Confusing this with the KMP-based O(n) solution (your approach is O(n²) but more intuitive)

// COMPANIES THAT ASK THIS:
// Amazon, Google, Microsoft, Adobe, Facebook/Meta, Bloomberg

// Time & Space Complexity Breakdown
// Time Complexity: O(n²)

// Outer loop: We try pattern lengths from n/2 to 1, which is O(n) iterations

// For each valid pattern length:

// String reconstruction: O(n) (we build a string of length n)

// String comparison: O(n) (we compare two strings of length n)

// Worst case: O(n) × O(n) = O(n²)

// (Note: There's a more efficient O(n) solution using KMP algorithm's failure function, but your approach is more intuitive for interviews)

// Space Complexity: O(n)

// We create a new string newstr of length n for each pattern we test

// This is O(n) space

