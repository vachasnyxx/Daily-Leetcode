// class Solution {
// public:
//     char findKthBit(int n, int k) {

//         if (n == 1)
//             return '0';
//         int length = (1 << n) - 1; // pow(2, n) -1

//         if (k < ceil(length / 2.0)) {
//             return findKthBit(n - 1, k);

//         } else if (k == ceil(length / 2.0)) {
//             return '1';
//         } else {
//             char ch = findKthBit(n - 1, length - (k - 1));
//             return (ch == '0') ? '1' : '0'; // handled flipped bit
//         }
//     }
// };




class Solution {
public:
    char findKthBit(int n, int k) {

        // Base case:
        // S1 = "0", so if n becomes 1, the only bit is '0'.
        //
        // Recursion analogy:
        // Imagine opening Russian nesting dolls.
        // To solve Sn, we reduce the problem to Sn-1.
        if (n == 1)
            return '0';

        // Length of Sn is:
        // 2^n - 1
        //
        // Why?
        // Sn = S(n-1) + "1" + reverse(invert(S(n-1)))
        //
        // Therefore:
        // length(Sn) = length(S(n-1)) + 1 + length(S(n-1))
        //              = 2 * length(S(n-1)) + 1
        //
        // The expression (1 << n) means 2^n using bit shifting.
        int length = (1 << n) - 1; // pow(2, n) - 1

        // The middle position of Sn is:
        // (length / 2) + 1
        //
        // Since length is always odd, ceil(length / 2.0)
        // gives the middle position.
        //
        // Example:
        // If length = 7:
        // Positions: 1 2 3 4 5 6 7
        // Middle:              4
        //
        // The first half of Sn is exactly S(n-1).
        // Therefore, if k is before the middle,
        // we simply search for the kth bit in S(n-1).
        if (k < ceil(length / 2.0)) {
            return findKthBit(n - 1, k);


        // If k is the middle position, the answer is always '1'.
        //
        // Every string is constructed in this form:
        //
        // Sn = S(n-1) + "1" + ...
        //
        // So the center bit never needs recursion.
        } else if (k == ceil(length / 2.0)) {
            return '1';


        // Otherwise, k lies in the second half of Sn.
        //
        // The second half is:
        // reverse(invert(S(n-1)))
        //
        // This means:
        // 1. The positions are reversed.
        // 2. The bit is inverted.
        //
        // We need to convert the position k in Sn
        // into its corresponding position in S(n-1).
        //
        // The mirrored position is:
        // length - (k - 1)
        //
        // Why?
        // Suppose length = 7:
        //
        // k = 5  -> corresponding position = 7 - (5 - 1) = 3
        // k = 6  -> corresponding position = 7 - (6 - 1) = 2
        // k = 7  -> corresponding position = 7 - (7 - 1) = 1
        //
        // So the second half maps backward to positions
        // 3, 2, 1 of S(n-1).
        } else {
            char ch = findKthBit(n - 1, length - (k - 1));

            // Because the second half is inverted,
            // flip the answer obtained from S(n-1).
            //
            // '0' becomes '1'
            // '1' becomes '0'
            return (ch == '0') ? '1' : '0'; // handled flipped bit
        }
    }
};

/*
================================================================================
REVISION SUMMARY
================================================================================

Problem:
Find the kth bit of the recursively constructed string Sn.

Construction:
S1 = "0"

For n > 1:

Sn = S(n-1) + "1" + reverse(invert(S(n-1)))

Example:

S1 = 0

S2 = 0 + 1 + invert(reverse(0))
   = 0 + 1 + 1
   = 011

S3 = 011 + 1 + reverse(invert(011))
   = 011 + 1 + reverse(100)
   = 011 + 1 + 001
   = 0111001

Important structure of Sn:

                 middle
                   |
Sn = [ S(n-1) ] + 1 + [ reverse(invert(S(n-1))) ]

The string is divided into three parts:

1. First half:
   This is exactly S(n-1).

2. Middle:
   This is always '1'.

3. Second half:
   This is S(n-1), but:
   - written in reverse order
   - every bit is flipped

Core recursion idea:
Do not actually build the entire string.

Instead, determine where k lies:

- If k is in the first half:
      Search in S(n-1) at the same position k.

- If k is the middle:
      Return '1'.

- If k is in the second half:
      Convert k into its mirrored position in S(n-1),
      recursively find that bit,
      and flip the result.

Analogy:
Imagine a long road divided into three sections:

    Original road | Central lamp | Mirrored-and-inverted road

If your destination is in the first section, use the same address.
If it is the central lamp, the answer is always '1'.
If it is in the last section, walk backward to find the matching
location in the original section, then reverse the bit's color.

Position mapping in the second half:

    mirrored position = length - (k - 1)

For length = 7:

    k = 5  -> 3
    k = 6  -> 2
    k = 7  -> 1

After finding the corresponding bit recursively, invert it:

    0 -> 1
    1 -> 0

Why recursion works:
The large string Sn is defined using the smaller string S(n-1).
Therefore, every question about Sn can be reduced to a question
about S(n-1). This continues until n becomes 1.

Base case:
When n == 1, the string is "0", so return '0'.

Complexity:
- Time: O(n)
  At every recursive call, n decreases by 1.
  We do not construct the strings.

- Space: O(n)
  The recursion call stack can contain at most n calls.

Common mistakes:
1. Forgetting that k is 1-indexed.
   The problem positions start from 1, not 0.

2. Forgetting to flip the answer in the second half.
   The second half is inverted, so the recursively found bit
   must be changed from 0 to 1 or from 1 to 0.

3. Using the wrong mirrored position.
   The correct mapping is:
       length - (k - 1)
   not simply length - k.

Trigger words:
- Recursively defined string
- Find kth character or kth bit
- Reverse and invert
- Middle character
- Avoid constructing the entire string

The most important mental model:
Find the half containing k.
Reduce the problem to a smaller string.
If the position came from the inverted half, flip the answer.

================================================================================
*/