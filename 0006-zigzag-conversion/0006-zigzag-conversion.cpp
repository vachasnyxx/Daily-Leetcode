#include <string>
#include <vector>

class Solution {
public:
    string convert(string s, int numRows) {
        // Edge case: If there's only 1 row, no zigzag pattern is formed.
        if (numRows == 1 || numRows >= s.length()) {
            return s;
        }
        
        // Track strings for each individual row
        vector<string> rows(numRows);
        int currentRow = 0;
        bool goingDown = false;
        
        // Iterate through each character
        for (char c : s) {
            rows[currentRow] += c;
            
            // Reverse direction when reaching the top or bottom row
            if (currentRow == 0 || currentRow == numRows - 1) {
                goingDown = !goingDown;
            }
            
            // Move up or down depending on the direction
            currentRow += goingDown ? 1 : -1;
        }
        
        // Combine all row strings into one final string
        string result;
        for (const string& row : rows) {
            result += row;
        }
        
        return result;
    }
};
