#include <string>
#include <climits>

class Solution {
public:
    int myAtoi(std::string s) {
        int i = 0;
        int n = s.length();
        int sign = 1;
        int result = 0;

        // Step 1: Skip leading whitespace
        while (i < n && s[i] == ' ') {
            i++;
        }

        // Handle empty or whitespace-only string
        if (i == n) return 0;

        // Step 2: Check for optional sign
        if (s[i] == '-') {
            sign = -1;
            i++;
        } else if (s[i] == '+') {
            i++;
        }

        // Step 3: Parse digits and protect against overflow
        while (i < n && std::isdigit(s[i])) {
            int digit = s[i] - '0';

            // Critical Overflow Check:
            // Check if multiplying by 10 or adding the digit exceeds INT_MAX
            if (result > (INT_MAX - digit) / 10) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }

            result = result * 10 + digit;
            i++;
        }

        return result * sign;
    }
};
