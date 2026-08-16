// class Solution {
// public:
//     int compress(vector<char>& chars) {
//         int n = chars.size();

//         int index = 0;
//         int i = 0;

//         while(i < n){
//             char curr_char = chars[i];
//             int count = 0;

//             // find count of duplicates
//             while(i < n && chars[i] == curr_char){
//                 count++;
//                 i++;
//             }

//             // now do the assign work

//             chars[index] = curr_char;

//             index++;
//             if(count > 1){
//                 string count_str = to_string(count);

//                 for(char &ch : count_str){
//                     chars[index] = ch;
//                     index++;
//                 }
//             }
//         }
//         return index;
//     }
// };



// The Analogy: The Librarian's Book Catalog Story
// Imagine you're a librarian organizing a book catalog:

// You have a shelf of books: ["a", "a", "b", "b", "b", "c", "c"]

// You need to compress this into a shorter format: ["a", "2", "b", "3", "c", "2"]

// BUT you can only write on the same shelf — you can't use a separate notepad (in-place modification)

// Your strategy:

// Use one finger (i) to scan through the books and count duplicates

// Use another finger (index) to mark where you're writing the compressed version

// For each group of identical books, write the character + count (if count > 1)

// Return the new length of the compressed catalog

// This is EXACTLY what your code does!



class Solution {
public:
    int compress(vector<char>& chars) {
        // ============================================
        // STEP 1: Get the Size of the Input Array
        // ============================================
        // Store the total number of characters in the input array
        // We'll use this as the boundary for our loops
        int n = chars.size();

        // ============================================
        // STEP 2: Initialize Two Pointers
        // ============================================
        // index = pointer for WRITING the compressed result
        // This marks where we'll place the next character/digit in the compressed array
        // We start at 0 (beginning of the array)
        //
        // i = pointer for READING/scanning through the original array
        // This helps us count consecutive duplicate characters
        // We also start at 0 (beginning of the array)
        //
        // KEY INSIGHT: Both pointers start at 0, but they move at different speeds
        // - 'i' moves forward to count duplicates
        // - 'index' moves forward to write the compressed result
        // This is a classic "two-pointer" pattern for in-place modification
        int index = 0;
        int i = 0;

        // ============================================
        // STEP 3: Main Loop - Process Each Character Group
        // ============================================
        // We'll scan through the entire array using pointer 'i'
        // For each group of consecutive identical characters, we'll:
        // 1. Count how many there are
        // 2. Write the character + count (if count > 1) to the compressed array
        while(i < n) {
            // ============================================
            // Capture the Current Character
            // ============================================
            // Store the character we're currently processing
            // This is the character we'll count duplicates of
            //
            // Example: chars = ["a", "a", "b", "b", "b", "c"]
            // First iteration: curr_char = 'a'
            // Second iteration: curr_char = 'b'
            // Third iteration: curr_char = 'c'
            char curr_char = chars[i];

            // ============================================
            // Initialize Count for This Character
            // ============================================
            // We'll count how many times curr_char appears consecutively
            // Start at 0, then increment as we find duplicates
            int count = 0;

            // ============================================
            // STEP 4: Inner Loop - Count Consecutive Duplicates
            // ============================================
            // This inner loop scans forward from position 'i' to count
            // how many times curr_char appears consecutively
            //
            // Conditions:
            // 1. i < n: Don't go out of bounds
            // 2. chars[i] == curr_char: Only count if the character matches
            //
            // Example: chars = ["a", "a", "b", "b", "b", "c"], curr_char = 'a'
            // - i = 0: chars[0] = 'a' == curr_char, count = 1, i = 1
            // - i = 1: chars[1] = 'a' == curr_char, count = 2, i = 2
            // - i = 2: chars[2] = 'b' != curr_char, exit inner loop
            // Result: count = 2 (two 'a's)
            while(i < n && chars[i] == curr_char) {
                count++;  // Increment the count of consecutive duplicates
                i++;      // Move the reading pointer forward
            }

            // ============================================
            // STEP 5: Write the Compressed Result
            // ============================================
            // Now we write the compressed version to the array
            // The compressed format is: [character][count] (if count > 1)
            // or just [character] (if count == 1)
            //
            // First, write the character itself
            // Example: chars[index] = 'a'
            chars[index] = curr_char;

            // Move the writing pointer forward
            // We've written one character, so increment index
            index++;

            // ============================================
            // STEP 6: Write the Count (If Greater Than 1)
            // ============================================
            // If the character appears more than once, we need to write the count
            // If count == 1, we skip this (no need to write "1")
            //
            // Example: count = 12
            // - Convert to string: count_str = "12"
            // - Write each digit: chars[index] = '1', chars[index+1] = '2'
            if(count > 1) {
                // Convert the count to a string so we can write each digit
                // Example: count = 12 → count_str = "12"
                // Example: count = 3 → count_str = "3"
                string count_str = to_string(count);

                // Write each digit of the count to the array
                // This handles multi-digit counts correctly
                //
                // Example: count_str = "12"
                // - First iteration: ch = '1', chars[index] = '1', index = index + 1
                // - Second iteration: ch = '2', chars[index] = '2', index = index + 1
                for(char &ch : count_str) {
                    chars[index] = ch;  // Write the digit to the array
                    index++;            // Move the writing pointer forward
                }
            }

            // After this, we go back to the outer loop
            // 'i' is already at the next new character (from the inner loop)
            // We'll process the next group of consecutive duplicates
        }

        // ============================================
        // STEP 7: Return the New Length
        // ============================================
        // The problem asks us to return the new length of the compressed array
        // 'index' now points to the position AFTER the last written character
        // So 'index' is exactly the length of the compressed array
        //
        // Example: Original: ["a", "a", "b", "b", "b", "c"] (length 6)
        // Compressed: ["a", "2", "b", "3", "c"] (length 5)
        // Return value: 5
        return index;
    }
};


// Input: chars = ["a", "a", "b", "b", "b", "c", "c"]

// Initial state:
// chars = ["a", "a", "b", "b", "b", "c", "c"]
// index = 0, i = 0

// Iteration 1 (curr_char = 'a'):
// - Inner loop: count = 2, i = 2
// - Write: chars[0] = 'a', index = 1
// - count > 1, so write count: chars[1] = '2', index = 2
// - State: chars = ["a", "2", "b", "b", "b", "c", "c"], index = 2, i = 2

// Iteration 2 (curr_char = 'b'):
// - Inner loop: count = 3, i = 5
// - Write: chars[2] = 'b', index = 3
// - count > 1, so write count: chars[3] = '3', chars[4] = '4', index = 5
//   Wait, that's wrong! Let me recalculate...
//   count = 3, count_str = "3"
//   chars[3] = '3', index = 4
// - State: chars = ["a", "2", "b", "3", "b", "c", "c"], index = 4, i = 5

// Iteration 3 (curr_char = 'c'):
// - Inner loop: count = 2, i = 7 (exit outer loop since i >= n)
// - Write: chars[4] = 'c', index = 5
// - count > 1, so write count: chars[5] = '2', index = 6
// - State: chars = ["a", "2", "b", "3", "c", "2", "c"], index = 6, i = 7

// Return: index = 6

// Final compressed array: ["a", "2", "b", "3", "c", "2"] (first 6 elements)



// Revision Summary (The Mental Model)
// THE BIG PICTURE:

// This is an in-place array modification + two-pointer pattern.

// Analogy: You're a librarian organizing a book catalog. You have a shelf of books, and you need to compress consecutive duplicates into a shorter format (character + count). BUT you can only write on the same shelf — you can't use a separate notepad (in-place modification).

// THE FLOW (Story Version):

// Setup Phase:

// Get the total size n of the input array

// Initialize two pointers: index = 0 (for writing), i = 0 (for reading)

// Main Loop (Process Each Character Group):

// Capture the current character: curr_char = chars[i]

// Initialize count = 0

// Inner Loop (Count Consecutive Duplicates):

// While chars[i] matches curr_char, increment count and move i forward

// This counts how many times the current character appears consecutively

// Write the Compressed Result:

// Write the character: chars[index] = curr_char, then index++

// If count > 1, convert count to string and write each digit

// For each digit: chars[index] = digit, then index++

// Repeat until i reaches the end of the array

// Return the new length: index

// KEY INSIGHTS:

// Why two pointers? One pointer (i) scans forward to count duplicates, while another (index) marks where to write the compressed result. This allows in-place modification without extra space.

// Why in-place? The problem constraint requires O(1) extra space. We're modifying the input array directly instead of creating a new array.

// Why convert count to string? If count is 12, we need to write two characters: '1' and '2'. Converting to string lets us iterate over each digit.

// Time Complexity: O(n) - we scan through the array once with pointer i, and each character is written at most once by pointer index

// Space Complexity: O(1) - we only use a few integer variables (index, i, count). The count_str is temporary and doesn't count toward space complexity in this context.

// TRIGGER WORDS for This Pattern:

// "compress the array"

// "in-place modification"

// "remove duplicates"

// "encode/decode string"

// "two-pointer array manipulation"

// COMMON MISTAKES TO AVOID:

// Forgetting to check i < n in the inner loop (can cause out-of-bounds access)

// Writing the count even when count == 1 (should only write count if > 1)

// Not converting count to string for multi-digit numbers (e.g., 12 should become '1', '2', not a single character)

// Returning n instead of index (the compressed array may be shorter than the original)

// Using extra space (creating a new array) instead of modifying in-place

// COMPANIES THAT ASK THIS:
// Amazon, Microsoft, Adobe, Google, Facebook/Meta, Bloomberg

// Time & Space Complexity Breakdown
// Time Complexity: O(n)

// We scan through the array once with pointer i: O(n)

// For each group of duplicates, we write the character and count digits: O(n) total (each character is written at most once)

// Converting count to string: O(log₁₀(count)) per group, but this is negligible compared to O(n)

// Total: O(n)

// Space Complexity: O(1)

// We only use a few integer variables: index, i, count, curr_char

// The count_str is temporary and doesn't count toward space complexity in this context (it's O(log₁₀(count)) which is at most O(log₁₀(n)))

// We're modifying the input array in-place, so no extra array is created