// LeetCode 724: Find Pivot Index
// Pattern: PREFIX SUM (running total trick)

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();

        // STEP 1: Compute the total sum of the array ONCE.
        // Why? Because for any index i:
        //      rightSum = totalSum - leftSum - nums[i]
        // Instead of re-summing the right side every time (which would be O(n) 
        // per index -> O(n^2) overall), we derive it in O(1) using totalSum.
        // This is the core "aha" of prefix sums: precompute the whole, then
        // subtract pieces you already know instead of recalculating from scratch.
        int totalsum = 0;
        for (int num : nums) {
            totalsum += num;
        }

        // leftsum = running sum of everything STRICTLY to the left of index i.
        // It starts at 0 because at i = 0, there is nothing to the left.
        int leftsum = 0;

        for (int i = 0; i < n; i++) {

            // rightsum = "everything except leftsum and nums[i] itself"
            // i.e. totalsum minus the left part minus the pivot element itself.
            // This is the key algebra: 
            //      totalsum = leftsum + nums[i] + rightsum
            //   => rightsum = totalsum - leftsum - nums[i]
            int rightsum = totalsum - leftsum - nums[i];

            // If left and right sums match, i is a pivot index. Return immediately
            // (first valid pivot from the left, as required by the problem).
            if (leftsum == rightsum) {
                return i;
            }

            // IMPORTANT: update leftsum AFTER checking, not before.
            // At the moment we check index i, leftsum must NOT include nums[i] 
            // yet (nums[i] belongs to neither "left" nor "right" - it's the pivot).
            // Only after moving past i do we fold nums[i] into leftsum for the 
            // next iteration.
            leftsum += nums[i];
        }

        // No pivot index existed anywhere in the array.
        return -1;
    }
};

/*
=====================================================================
REVISION SUMMARY — read this whenever you forget how this works
=====================================================================

PLAIN ENGLISH:
A pivot index is a position where "everything to its left" weighs the 
same as "everything to its right" on a balance scale. The element AT 
that index itself sits on neither side.

ANALOGY — The Seesaw / Weighing Scale:
Imagine you're balancing a seesaw. You have kids (numbers) standing in 
a line. You want to find the ONE kid who can stand exactly at the 
center pivot point such that the total weight of kids to their left 
equals the total weight of kids to their right. You don't want to keep 
re-weighing the right side of kids every single time you test a new 
pivot candidate — that's slow and repetitive. Instead, you weigh 
EVERYONE once (totalsum), and every time you test a new pivot, you 
just do quick subtraction: "total weight minus the kid at the pivot 
minus the kids already counted on the left = weight of the right 
side." That's the whole trick.

WHY PREFIX SUM WORKS HERE:
Without prefix sums, computing rightSum for every index would mean 
re-scanning the array each time -> O(n^2). Prefix sum lets you carry 
forward a running total (leftsum) and derive the other side (rightsum) 
using simple arithmetic from a value you computed once (totalsum). 
This "compute once, derive the rest via subtraction" mindset is the 
heart of prefix sum problems.

DRY RUN (nums = [1, 7, 3, 6, 5, 6]):
totalsum = 1+7+3+6+5+6 = 28

i=0: leftsum=0,  rightsum = 28-0-1  = 27  -> 0 != 27, leftsum becomes 1
i=1: leftsum=1,  rightsum = 28-1-7  = 20  -> 1 != 20, leftsum becomes 8
i=2: leftsum=8,  rightsum = 28-8-3  = 17  -> 8 != 17, leftsum becomes 11
i=3: leftsum=11, rightsum = 28-11-6 = 11  -> 11 == 11 -> PIVOT FOUND, return 3

Check manually: left of index 3 = [1,7,3] sum=11, right of index 3 = 
[5,6] sum=11. Balanced! Matches leetcode's expected output for this 
classic example.

TIME COMPLEXITY: O(n)
- One pass to compute totalsum: O(n)
- One pass to check each index using O(1) arithmetic: O(n)
- Total: O(n), no nested loops, no re-scanning.

SPACE COMPLEXITY: O(1)
- Only a few integer variables (totalsum, leftsum, rightsum) — no 
  extra arrays or prefix-sum array stored. This is the "optimized" 
  version of prefix sum (running variable) vs the "textbook" version 
  (building a full prefix array), which would cost O(n) space.

COMMON MISTAKES STUDENTS MAKE:
1. Updating leftsum BEFORE the comparison instead of after — this 
   incorrectly includes nums[i] on the left side while checking, 
   breaking the balance logic.
2. Recomputing rightsum by looping from i+1 to n every iteration 
   instead of deriving it via totalsum - leftsum - nums[i], turning 
   an O(n) solution into O(n^2).
3. Forgetting that the pivot element itself is excluded from BOTH 
   sides — some students mistakenly include nums[i] in leftsum or 
   rightsum during the comparison step.

TRIGGER WORDS for this pattern:
"sum of elements to the left equals sum to the right", "running total", 
"cumulative sum", "subarray sum", "range sum" — whenever you see 
comparisons between a "before" segment and an "after" segment of an 
array, think PREFIX SUM.

COMPANIES that test this pattern:
Pivot Index itself is a common warm-up question at Amazon and Adobe 
online assessments. The broader prefix sum pattern (e.g., subarray 
sum equals K, range sum queries) shows up heavily in Google, Amazon, 
and Microsoft interviews as a stepping stone before moving into 
prefix-sum + hashmap combo problems.
=====================================================================
*/












// class Solution {
// public:
//     int pivotIndex(vector<int>& nums) {
//         int n = nums.size();
//         int totalsum = 0;
//         for (int num : nums) {
//             totalsum += num;
//         }

//         int leftsum = 0;

//         for (int i = 0; i < n; i++) {

//             int rightsum = totalsum - leftsum - nums[i];

//             if (leftsum == rightsum) {
//                 return i;
//             }
//             leftsum += nums[i];
//         }
//         return -1;
//     }
// };











// class Solution {
// public:
//     int pivotIndex(vector<int>& nums) {
//         int n = nums.size();

//         for(int i =0; i<n; i++){
//             int leftsum = 0;
//             for(int j =0; j<i; j++){
//                 leftsum += nums[j];
//             }

//             int rightsum = 0;

//             for(int k = i+1; k<n; k++){
//                 rightsum += nums[k];
//             }

//             if(leftsum == rightsum){
//                 return i;
//             }
//         }
//         return -1;

//     }
// };
