// class Solution {
// public:
//     vector<int> arr;
//     Solution(ListNode* head){
//         ListNode* temp = head;
//         while(temp != NULL){
//             arr.push_back(temp->val);
//             temp = temp->next;
//         }
//     }
//     int getRandom() {
//         int n = arr.size();
//         int random_index = rand()%n;   //{0, 1, ..... n- 1}
//         return arr[random_index];
//     }
// };






class Solution {
public:
    ListNode* Head;

    Solution(ListNode* head){
        Head = head;
    }
    int getRandom() {
        int count = 1;
        int result = 0;

        ListNode* temp = Head;

        while(temp != NULL){
            if(rand()% count <1.0/count){
                result = temp->val;
            }
            count++;
            temp = temp->next;
        }
        return result;
    }
};









// class Solution {
// public:
//     ListNode* Head;

//     Solution(ListNode* head){
//         Head = head;
//     }
    
//     int getRandom() {
//         // RESERVOIR SAMPLING ALGORITHM (Size Unknown Stream)
//         // ================================================
        
//         int count = 1;      // Tracks which element number we're currently at (1-indexed)
//         int result = 0;     // Stores our randomly selected value
        
//         ListNode* temp = Head;  // Iterator to traverse the linked list
        
//         // CORE LOGIC: Process each element one by one
//         while(temp != NULL){
            
//             // KEY INSIGHT: Probability Magic ✨
//             // ================================
//             // We want each element to have equal probability (1/n) of being selected
//             // 
//             // At position 'count':
//             // - Generate random number from 0 to (count-1)
//             // - If it's 0, select current element
//             // - This gives probability: 1/count
//             //
//             // WHY THIS WORKS (Mathematical Proof by Example):
//             // For 3 elements [A, B, C]:
//             // - Element A: Selected with prob 1/1 = 100% initially
//             //   But survives: 1/1 × (1-1/2) × (1-1/3) = 1/1 × 1/2 × 2/3 = 1/3 ✓
//             // - Element B: Selected with prob 1/2
//             //   Survives: 1/2 × (1-1/3) = 1/2 × 2/3 = 1/3 ✓
//             // - Element C: Selected with prob 1/3 = 1/3 ✓
            
//             if(rand() % count < 1.0/count){  
//                 // ⚠️ CRITICAL OBSERVATION #1: This condition is ALWAYS TRUE!
//                 // rand() % count gives values from 0 to (count-1)
//                 // Only 0 < 1.0/count is true (since 1.0/count is always > 0 but ≤ 1)
//                 // 
//                 // BETTER/CLEARER VERSION:
//                 // if(rand() % count == 0)  // Same logic, more readable!
                
//                 result = temp->val;  // Replace result with current element
//             }
            
//             count++;           // Move to next position
//             temp = temp->next; // Advance pointer
//         }
        
//         return result;
//     }
// };

// /*
// ╔════════════════════════════════════════════════════════════════════════════╗
// ║                     COMPREHENSIVE SUMMARY & REVISION GUIDE                  ║
// ╚════════════════════════════════════════════════════════════════════════════╝

// 📌 PROBLEM: Select random element from linked list with EQUAL probability

// 🎯 ALGORITHM: RESERVOIR SAMPLING (Single Reservoir, k=1)

// 🧠 INTUITION - THE "LOTTERY TICKET" ANALOGY:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Imagine you're walking through a line of people, and you can only remember ONE 
// person's name at a time. How do you ensure everyone has an equal chance of being 
// remembered?

// 👤 Person 1: Remember them (100% chance)
// 👥 Person 2: Flip a coin (50% chance to replace)
// 👥 Person 3: Roll a die with 1/3 chance to replace
// 👥 Person n: Give them 1/n chance to replace current person

// By the end, everyone had EQUAL 1/n probability! 🎲

// 🔑 KEY PATTERN RECOGNITION:
// ━━━━━━━━━━━━━━━━━━━━━━━━━
// ✓ Use when: Stream of unknown length / Can't access random index
// ✓ Signature: Processing elements ONE-BY-ONE with decreasing replacement probability
// ✓ Variables: count (position counter) + result (current winner)

// 📐 MATHEMATICAL GUARANTEE:
// ━━━━━━━━━━━━━━━━━━━━━━━━━
// Element at position i has final probability = 1/n where n = total elements
// Proof: P(selected at i) × P(not replaced later) = 1/i × (i/(i+1)) × ... × ((n-1)/n) = 1/n

// ⚠️ CRITICAL CODE DETAILS (MUST NOTICE):
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// 1. count starts at 1 (not 0!) - Because we're counting "which element number"
// 2. Condition `rand()%count < 1.0/count` simplifies to `rand()%count == 0`
// 3. Must traverse from HEAD every time (no random access in linked list)
// 4. temp pointer prevents modifying Head
// 5. Integer division trap: Use 1.0/count NOT 1/count (avoid truncation)

// 🐛 COMMON MISTAKES TO AVOID:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━
// ❌ Starting count at 0
// ❌ Using 1/count (integer division gives 0)
// ❌ Modifying Head pointer directly
// ❌ Not resetting temp to Head in getRandom()

// ⏱️ TIME COMPLEXITY: O(n)
// ━━━━━━━━━━━━━━━━━━━━━━━━━
// - n = number of nodes in linked list
// - Must traverse ENTIRE list every call to getRandom()
// - No way to optimize (no random access in linked list)
// - Constructor: O(1) - just storing reference

// 💾 SPACE COMPLEXITY: O(1)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━
// - Only using: count (int) + result (int) + temp (pointer)
// - No extra data structures
// - No recursion stack

// 🎤 INTERVIEWER EXPLANATION TEMPLATE:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// "I'm using Reservoir Sampling because we can't randomly access linked list nodes.
// The idea is to give each element a probability of 1/n by processing them sequentially.
// For the i-th element, I generate a random number from 0 to i-1. If it's 0, I select
// that element. This gives it 1/i probability initially, and mathematically it works
// out that every element has exactly 1/n final probability. It takes O(n) time per
// call since we traverse the whole list, but only O(1) extra space."

// 🔄 COMPARISON WITH ARRAY VERSION (LC 398):
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Array: Can use rand() % array.length for O(1) random access
// Linked List: MUST use Reservoir Sampling - no choice!

// 📚 WHEN TO USE THIS PATTERN:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━
// ✓ Sampling from data stream
// ✓ Unknown data size
// ✓ No random access available
// ✓ Memory-constrained scenarios

// */

