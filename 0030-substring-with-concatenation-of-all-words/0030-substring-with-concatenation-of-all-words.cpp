class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        // ============================================
        // EDGE CASES & INITIALIZATION
        // ============================================
        // Result vector to store all valid starting indices
        vector<int> result;

        // Get the length of the main string 's'
        int n = s.length();

        // Get the number of words in our 'words' array
        int numWords = words.size();

        // Get the length of each word (ALL words have the same length per problem constraint)
        // This is CRUCIAL - it means we can jump by this fixed length when sliding
        int wordLen = words[0].length();

        // Calculate the total length of a valid concatenated substring
        // This is our "window size" - a valid substring must be exactly this long
        // Example: if words = ["foo", "bar"] (2 words, each 3 chars), totalLen = 6
        int totalLen = numWords * wordLen;

        // EDGE CASE: If the string is shorter than the total length needed,
        // no valid concatenation can exist. Return empty result.
        if (n < totalLen) {
            return result;
        }

        // ============================================
        // STEP 1: Build the "Manifest" (Word Frequency Map)
        // ============================================
        // Create a frequency map of all words in our 'words' array
        // This is our "shopping list" or "manifest" - what we need to find in each window
        // Example: words = ["foo", "bar", "foo"] → wordCount = {foo: 2, bar: 1}
        unordered_map<string, int> wordCount;
        for (const string& word : words) {
            wordCount[word]++;
        }

        // ============================================
        // STEP 2: Sliding Window - The "Word-by-Word" Approach
        // ============================================
        // KEY INSIGHT: Since all words are the same length (wordLen),
        // we only need to check starting positions that align with word boundaries.
        // We check wordLen different "tracks" or "phases":
        // - Track 0: start at index 0, then wordLen, then 2*wordLen, ...
        // - Track 1: start at index 1, then 1+wordLen, then 1+2*wordLen, ...
        // - Track 2: start at index 2, then 2+wordLen, then 2+2*wordLen, ...
        // ... up to Track (wordLen-1)
        //
        // This avoids checking every single index and ensures we always read complete words.
        //
        // VISUALIZATION:
        // If wordLen = 3, we check these "tracks":
        // Track 0: [0,3,6,9,12,...]  → words start at positions 0, 3, 6, 9, ...
        // Track 1: [1,4,7,10,13,...] → words start at positions 1, 4, 7, 10, ...
        // Track 2: [2,5,8,11,14,...] → words start at positions 2, 5, 8, 11, ...

        for (int i = 0; i < wordLen; i++) {
            // ============================================
            // For each "track", we'll slide a window word-by-word
            // ============================================
            // left = start of our current window (left pointer)
            // right = end of our current window (right pointer, moves by wordLen each time)
            int left = i;
            int right = i;

            // Count of words in our current window that match our manifest requirements
            // When this equals numWords, we have a valid concatenation!
            int count = 0;

            // Frequency map for words in our CURRENT window
            // We'll compare this against our manifest (wordCount) to check validity
            unordered_map<string, int> currentCount;

            // ============================================
            // SLIDING WINDOW LOOP
            // ============================================
            // Move 'right' pointer by wordLen each iteration (reading one word at a time)
            // We continue as long as there's room for at least one complete word
            while (right + wordLen <= n) {
                // Extract the current word from the string
                // This is the word at position 'right' with length 'wordLen'
                // Example: if s = "barfoo...", right = 0, wordLen = 3 → word = "bar"
                string word = s.substr(right, wordLen);

                // Move the right pointer forward by wordLen (to the next word position)
                // We do this AFTER extracting the current word
                right += wordLen;

                // ============================================
                // Check if this word is even in our manifest
                // ============================================
                // If the word is NOT in wordCount, it's not part of our required words
                // This means our current window is INVALID, and we need to reset
                if (wordCount.find(word) == wordCount.end()) {
                    // Reset everything: clear current window's word count, reset count to 0
                    // Move left pointer to right (start fresh from the next position)
                    currentCount.clear();
                    count = 0;
                    left = right;
                    continue;  // Skip to next iteration
                }

                // ============================================
                // Word IS in our manifest - add it to current window
                // ============================================
                // Add this word to our current window's frequency map
                currentCount[word]++;
                count++;  // Increment the count of words in our window

                // ============================================
                // Check if we have TOO MANY of this word
                // ============================================
                // If currentCount[word] > wordCount[word], it means:
                // "We have more of this word in our window than we're allowed"
                // This makes our window INVALID, so we need to SHRINK from the left
                // until we remove the excess occurrence of this word
                //
                // Example: manifest = {foo: 1, bar: 1}, current window = "foofoo"
                // currentCount = {foo: 2}, which is > wordCount[foo] = 1
                // So we shrink from left until we remove one "foo"
                while (currentCount[word] > wordCount[word]) {
                    // Extract the word at the left edge of our window
                    string leftWord = s.substr(left, wordLen);

                    // Remove this word from our current window's frequency map
                    currentCount[leftWord]--;
                    count--;  // Decrement the count of words in our window

                    // Move the left pointer forward by wordLen (shrink window from left)
                    left += wordLen;
                }

                // ============================================
                // Check if we have a VALID window
                // ============================================
                // If count == numWords, it means:
                // - We have exactly the right number of words in our window
                // - No word appears more times than allowed (checked by the while loop above)
                // - All words in our window are from our manifest (checked earlier)
                // Therefore, this is a valid concatenation!
                if (count == numWords) {
                    // Add the starting index of this valid window to our result
                    result.push_back(left);

                    // ============================================
                    // Prepare for next iteration by shrinking window from left
                    // ============================================
                    // After recording a valid window, we need to continue searching
                    // Remove the leftmost word from our window to make room for new words
                    string leftWord = s.substr(left, wordLen);
                    currentCount[leftWord]--;
                    count--;
                    left += wordLen;
                }
            }
        }

        // ============================================
        // FINAL RESULT
        // ============================================
        // Return all starting indices where valid concatenations were found
        return result;
    }
};


// Revision Summary (The Mental Model)
// THE BIG PICTURE:

// This is a fixed-size sliding window problem with a word-frequency matching pattern.

// Analogy: You're a railway inspector with a manifest of train carriages (words). The railway track is a long string (s). You need to find all positions where you see a complete train made of ALL carriages from your manifest, each used exactly once, in any order.

// THE FLOW (Story Version):

// Setup Phase:

// Calculate totalLen = numWords × wordLen (this is your window size)

// Build a "manifest" map: frequency of each word in words

// We'll check wordLen different "tracks" (starting offsets: 0, 1, 2, ..., wordLen-1)

// For Each Track (Outer Loop):

// Initialize left = i, right = i (both pointers start at the track's offset)

// Initialize count = 0 (words in current window) and empty currentCount map

// Slide right forward by wordLen each iteration (reading one word at a time)

// Expansion Phase (Inner While Loop):

// Extract word at position right: word = s.substr(right, wordLen)

// If word is NOT in manifest → invalid window, reset everything, move left to right

// If word IS in manifest → add to currentCount, increment count

// If currentCount[word] > wordCount[word] → too many of this word, SHRINK from left until valid

// If count == numWords → VALID WINDOW! Record left in result, then shrink from left to continue

// Repeat for all tracks until end of string

// KEY INSIGHTS:

// Why check wordLen tracks? Because valid concatenations must align with word boundaries. If word length is 3, valid starts can only be at positions 0, 1, 2 (mod 3). This reduces redundant checks.

// Positive wordCount = "This word is in our manifest"

// currentCount[word] > wordCount[word] = "We have too many of this word, window is invalid"

// count == numWords = "We have exactly the right number of words, all valid → record answer"

// Time Complexity: O(n × wordLen) - we check each position at most once per track, and there are wordLen tracks

// Space Complexity: O(numWords × wordLen) - for storing word frequency maps

// TRIGGER WORDS for This Pattern:

// "concatenation of all words"

// "permutation of words"

// "all words exactly once"

// "fixed-length words" + "find all starting indices"

// COMMON MISTAKES TO AVOID:

// Not checking all wordLen tracks (you'll miss valid starts at certain offsets)

// Forgetting to reset currentCount and count when encountering an invalid word

// Not shrinking the window when currentCount[word] > wordCount[word]

// Off-by-one errors in substring extraction (remember: s.substr(right, wordLen))

// Forgetting the edge case where s.length() < totalLen

// COMPANIES THAT ASK THIS:
// Amazon, Google, Microsoft, Adobe, Facebook/Meta, Bloomberg