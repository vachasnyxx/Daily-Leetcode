class Solution {
public:
    int pairSum(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* mid = slow;

        // rverse 2nd hafl of our Linked List
        // reversal code

        ListNode* prev = NULL;
        ListNode* nextNode = NULL;

        while (mid != NULL) {
            nextNode = mid->next;
            mid->next = prev;
            prev = mid;
            mid = nextNode;
        }

        // find max result

        int result = 0;

        ListNode* curr = head;

        while (prev != NULL) {
            result = max(result, curr->val + prev->val);
            curr = curr->next;
            prev = prev->next;
        }
        return result;
    }
};


// class Solution {
// public:
//     int pairSum(ListNode* head) {
        
//         // ============================================================
//         // PROBLEM: Find the MAXIMUM "twin sum" in an EVEN-length list
//         // Twin of node i = node (n-1-i) where n = total nodes
//         //
//         // Example: [5, 4, 2, 1]   (n=4)
//         //   Twin pairs: (5,1) → sum=6
//         //               (4,2) → sum=6
//         //   Max twin sum = 6
//         //
//         // Example: [4, 2, 2, 3]   (n=4)
//         //   Twin pairs: (4,3) → sum=7
//         //               (2,2) → sum=4
//         //   Max twin sum = 7
//         //
//         // VISUAL: Think of folding the list in half!
//         //   [5, 4, 2, 1]
//         //    ↕  ↕  ↕  ↕
//         //   [5, 4] + [1, 2]  ← second half REVERSED
//         //    ↓  ↓
//         //   (6, 6) → max = 6
//         // ============================================================
//         // APPROACH: 3 Steps
//         //   1. Find the MIDDLE (slow/fast pointers)
//         //   2. REVERSE the second half
//         //   3. Walk both halves simultaneously, track max sum
//         // ============================================================


//         // ─── STEP 1: FIND THE MIDDLE ───
//         // ⚠️ ATOMIC DETAIL #1: The problem GUARANTEES even length.
//         // This means slow will ALWAYS land on the exact start of the
//         // second half. No ambiguity about "which middle" like odd-length.
//         //
//         // For [5, 4, 2, 1]:
//         //   slow starts at 5, fast starts at 5
//         //   Iter 1: slow→4, fast→2
//         //   Iter 2: slow→2, fast→NULL (past end)
//         //   Loop stops. slow = node(2) = FIRST node of second half ✓
//         //
//         // WHY does this work?
//         // fast moves 2x speed of slow.
//         // When fast reaches the end (n steps), slow has gone n/2 steps.
//         // n/2 is exactly the start of the second half for even n!
        
//         ListNode* slow = head;
//         ListNode* fast = head;

//         while (fast != NULL && fast->next != NULL) {
//             // ⚠️ ATOMIC DETAIL #2: Check fast AND fast->next!
//             // fast != NULL      → handles even-length (fast lands ON NULL)
//             // fast->next != NULL → handles odd-length (fast lands on last node)
//             // Even though problem says even, this is SAFE defensive coding.
//             // If you only check fast != NULL → crash on odd-length! 💥
            
//             slow = slow->next;        // Moves 1 step
//             fast = fast->next->next;  // Moves 2 steps (double speed!)
//         }

//         // slow is now at the START of the second half
//         ListNode* mid = slow;
//         // ⚠️ ATOMIC DETAIL #3: mid = slow, NOT slow->next!
//         // Because for even-length, slow is already at the correct position.
//         // If this were odd-length and we wanted to skip the middle node,
//         // we'd use slow->next. But here, even length = no middle node to skip.


//         // ─── STEP 2: REVERSE THE SECOND HALF ───
//         // Classic 3-pointer reversal technique
//         //
//         // BEFORE reversal: [5, 4] → [2, 1] → NULL
//         //                              ↑ mid
//         // AFTER reversal:  [5, 4] → NULL   [1, 2] → NULL
//         //                                      ↑ prev (new head of 2nd half)
//         //
//         // THE "TRAIN REVERSAL" ANALOGY 🚂:
//         // Imagine train cars: 2→1→NULL
//         // You detach each car from the front and reattach it to a new track:
//         //   Step 1: Detach 2, new track: 2→NULL
//         //   Step 2: Detach 1, new track: 1→2→NULL  ← REVERSED!

//         ListNode* prev = NULL;      // Will become the new head of reversed half
//         ListNode* nextNode = NULL;  // Temporary: saves the next node before we break the link

//         while (mid != NULL) {
//             // ⚠️ ATOMIC DETAIL #4: ORDER IS CRITICAL! Follow these 4 steps exactly:
//             //
//             // ① SAVE the next node (before we destroy the link!)
//             nextNode = mid->next;
//             //    If we don't save this, mid->next will be overwritten
//             //    in the next step and we'll LOSE the rest of the list!
//             //
//             // ② REVERSE the pointer (point backward instead of forward)
//             mid->next = prev;
//             //    This is the actual "reversal" — flipping the arrow direction
//             //
//             // ③ ADVANCE prev (it becomes the current node for next iteration)
//             prev = mid;
//             //    prev always tracks the head of the "reversed so far" portion
//             //
//             // ④ ADVANCE mid (move to the saved next node)
//             mid = nextNode;
//             //    Continue processing the remaining unreversed portion
//         }
//         // After loop: prev = head of reversed second half
//         //             mid = NULL (we've processed everything)


//         // ─── STEP 3: FIND MAXIMUM TWIN SUM ───
//         // Now we have:
//         //   head → [first half:  5, 4, ...]
//         //   prev → [second half: 1, 2, ...]  (REVERSED!)
//         //
//         // Because the second half is reversed, corresponding twins
//         // are now ALIGNED at the same positions!
//         //
//         //   head→  5   4        curr walks forward
//         //          ↕   ↕        ← twin pairs line up perfectly!
//         //   prev→  1   2        prev walks forward (was reversed)
//         //
//         // This is the GENIUS of reversing! No need for arrays or stacks!

//         int result = 0;  // ⚠️ ATOMIC DETAIL #5: Initialize to 0, not INT_MIN.
//                          // Node values are ≥ 1 (per constraints), so sums ≥ 2.
//                          // 0 is a safe floor. But INT_MIN would also work.

//         ListNode* curr = head;  // Pointer for the first half

//         while (prev != NULL) {
//             // ⚠️ ATOMIC DETAIL #6: We loop on prev, NOT on curr!
//             // WHY? Both halves have exactly n/2 nodes (even length guarantee).
//             // So either condition works. But prev is the reversed half,
//             // and when prev hits NULL, we've processed all twin pairs.
//             // Using curr != NULL would also work identically here.
            
//             result = max(result, curr->val + prev->val);
//             // Calculate twin sum and keep the maximum
            
//             curr = curr->next;  // Move first half pointer forward
//             prev = prev->next;  // Move reversed second half pointer forward
//         }
        
//         return result;
        
//         // ============================================================
//         // FULL TRACE for [5, 4, 2, 1]:
//         // ============================================================
//         //
//         // STEP 1 - Find Middle:
//         //   slow=5, fast=5
//         //   → slow=4, fast=2
//         //   → slow=2, fast=NULL (stop!)
//         //   mid = node(2)
//         //
//         // STEP 2 - Reverse [2, 1]:
//         //   Iter 1: nextNode=1, 2→NULL, prev=2, mid=1
//         //   Iter 2: nextNode=NULL, 1→2, prev=1, mid=NULL
//         //   Reversed: 1→2→NULL, prev points to 1
//         //
//         // STEP 3 - Max Twin Sum:
//         //   curr=5, prev=1: sum=6, result=6
//         //   curr=4, prev=2: sum=6, result=6
//         //   prev=NULL → stop
//         //   Return 6 ✓
//         // ============================================================
//     }
// };

// /*
// ╔══════════════════════════════════════════════════════════════════════════════╗
// ║                   🧠 DEEP DIVE REVISION GUIDE - LC 2134                      ║
// ╚══════════════════════════════════════════════════════════════════════════════╝

// 📌 PROBLEM: Maximum twin sum in an even-length linked list

// 🎯 ALGORITHM: Slow/Fast + Reverse Second Half + Two-Pointer Walk

// ═══════════════════════════════════════════════════════════════════════════════
// 📖 THE "FOLDING A PAPER" ANALOGY (Remember This Forever!)
// ═══════════════════════════════════════════════════════════════════════════════

// Imagine writing numbers on a long strip of paper:

//   [5]  [4]  [2]  [1]

// Now FOLD the paper in half so the ends meet:

//   [5]  [4]
//    ↕    ↕      ← These are "twins"!
//   [1]  [2]     ← Second half is naturally reversed when folded!

//   Sums: 5+1=6, 4+2=6 → Max = 6

// THAT'S exactly what our algorithm does:
//   1. Find the fold point (middle) → slow/fast pointers
//   2. Actually reverse the second half → mimics the fold
//   3. Read pairs from both halves → aligned twins!

// The reversal is just "folding the paper" programmatically! 📄

// ═══════════════════════════════════════════════════════════════════════════════
// 🧩 THE 3-STEP PATTERN (Memorize This Template!)
// ═══════════════════════════════════════════════════════════════════════════════

//   ┌───────────────────────────────────────────────────────────────┐
//   │ STEP 1: FIND MIDDLE                                          │
//   │   slow/fast pointers → slow lands at start of second half    │
//   │                                                               │
//   │ STEP 2: REVERSE SECOND HALF                                  │
//   │   3-pointer technique (prev, curr, next)                     │
//   │   prev becomes new head of reversed half                     │
//   │                                                               │
//   │ STEP 3: WALK BOTH HALVES                                     │
//   │   head walks first half, prev walks reversed second half     │
//   │   Compare/combine corresponding nodes                        │
//   └───────────────────────────────────────────────────────────────┘

//   This EXACT pattern appears in:
//   ✓ LC 234 - Palindrome Linked List (compare instead of sum)
//   ✓ LC 143 - Reorder List (interleave instead of sum)
//   ✓ LC 2134 - This problem (max sum)
  
//   Master this template → solve 3+ problems instantly! 🚀

// ═══════════════════════════════════════════════════════════════════════════════
// ⚠️ ATOMIC DETAILS YOU MUST NOTICE (Interview Differentiators)
// ═══════════════════════════════════════════════════════════════════════════════

//   1️⃣ EVEN LENGTH GUARANTEE
//      The problem says n is even. This means:
//      → No "middle element" to worry about
//      → Both halves are exactly n/2
//      → slow lands EXACTLY at the start of second half
//      → If n were odd, you'd need to skip the middle node!

//   2️⃣ SLOW LANDS ON FIRST NODE OF SECOND HALF (not last of first)
//      For [5,4,2,1]: slow = node(2), NOT node(4)
//      This is because fast starts at head (not head->next).
     
//      ⚠️ If fast started at head->next:
//         slow would land on node(4) = last of first half
//         You'd need mid = slow->next to get second half start
//         Both approaches work, just be CONSISTENT!

//   3️⃣ REVERSAL DESTROYS ORIGINAL LIST STRUCTURE
//      After reversal: [5,4] → NULL  and  [1,2] → NULL
//      The link between 4 and 2 is BROKEN (4->next = NULL after reversal
//      reaches it... actually 4->next still points to 2, but 2->next = NULL).
     
//      ⚠️ INTERVIEW FOLLOW-UP: "Can you restore the list?"
//      → Reverse the second half AGAIN to restore original order!
//      → Shows you think about side effects.

//   4️⃣ REVERSAL POINTER ORDER: SAVE → REVERSE → ADVANCE PREV → ADVANCE CURR
//      ┌──────────────────────────────────────────────────────┐
//      │ nextNode = mid->next;   // ① SAVE next              │
//      │ mid->next = prev;       // ② REVERSE link           │
//      │ prev = mid;             // ③ MOVE prev forward      │
//      │ mid = nextNode;         // ④ MOVE mid forward       │
//      └──────────────────────────────────────────────────────┘
//      Swap ANY two lines → broken code! This order is sacred. 🔒

//   5️⃣ WHY prev != NULL as loop condition in Step 3?
//      Both halves have n/2 nodes. When prev exhausts, curr also exhausts.
//      Either condition works. prev is chosen because it's the reversed
//      half and its length is clearly bounded.

//   6️⃣ result = 0 is safe because constraints say node values ≥ 1
//      So minimum possible sum = 1+1 = 2 > 0.
//      If values could be negative, use INT_MIN instead!

// ═══════════════════════════════════════════════════════════════════════════════
// 🐛 EDGE CASES TO THINK ABOUT
// ═══════════════════════════════════════════════════════════════════════════════

//   Case 1: Minimum list [1, 1] (n=2)
//     → slow=1(second), reverse [1]→[1]
//     → sum = 1+1 = 2 ✓

//   Case 2: [1, 100000] (n=2, large values)
//     → sum = 100001, fits in int ✓
//     → Constraints say values ≤ 10^5, max sum = 2×10^5 < INT_MAX ✓

//   Case 3: All same values [5, 5, 5, 5]
//     → All twin sums = 10, result = 10 ✓

//   Case 4: Large list (n = 10^5)
//     → O(n) handles it easily within time limit ✓

// ═══════════════════════════════════════════════════════════════════════════════
// ⏱️ COMPLEXITY (Easy Interview Explanation)
// ═══════════════════════════════════════════════════════════════════════════════

//   TIME: O(n)
//   ──────────
//   "Three linear passes, each touching every node at most once:
//    Pass 1: Slow/fast to find middle → O(n)
//    Pass 2: Reverse second half → O(n/2) = O(n)
//    Pass 3: Walk both halves → O(n/2) = O(n)
//    Total: O(n) + O(n) + O(n) = O(n). Constants don't matter in Big-O."

//   SPACE: O(1)
//   ────────────
//   "We only use a handful of pointers (slow, fast, mid, prev, nextNode, curr).
//    No arrays, no stacks, no recursion. Everything is done in-place.
//    The reversal modifies pointers but uses no extra memory."

//   ⚠️ COMPARE WITH ALTERNATIVES:
//   ┌──────────────────────┬──────────┬───────────┐
//   │ Approach             │ Time     │ Space     │
//   ├──────────────────────┼──────────┼───────────┤
//   │ Array + Two Pointers │ O(n)     │ O(n) ❌   │
//   │ Stack                │ O(n)     │ O(n/2) ❌ │
//   │ This (Reverse)       │ O(n)     │ O(1) ✅   │
//   └──────────────────────┴──────────┴───────────┘
//   Mention this comparison in interviews → shows optimization thinking!

// ═══════════════════════════════════════════════════════════════════════════════
// 🎤 INTERVIEWER EXPLANATION SCRIPT (30 seconds)
// ═══════════════════════════════════════════════════════════════════════════════

//   "I'll solve this in three steps with O(n) time and O(1) space.
//    First, I use slow and fast pointers to find the middle of the list.
//    Second, I reverse the second half in-place using the standard
//    three-pointer technique. Now the twin nodes are aligned — the i-th
//    node from the start pairs with the i-th node of the reversed half.
//    Third, I walk both halves simultaneously, computing pair sums and
//    tracking the maximum. Since the list is guaranteed even-length,
//    both halves are equal and the alignment is perfect."

// ═══════════════════════════════════════════════════════════════════════════════
// 🔄 ALTERNATIVE: STACK APPROACH (Simpler but O(n) Space)
// ═══════════════════════════════════════════════════════════════════════════════

//   int pairSum(ListNode* head) {
//       stack<int> st;
//       ListNode* slow = head;
//       ListNode* fast = head;
      
//       // Push first half onto stack
//       while(fast && fast->next) {
//           st.push(slow->val);
//           slow = slow->next;
//           fast = fast->next->next;
//       }
      
//       // Pop and compare with second half
//       int result = 0;
//       while(slow) {
//           result = max(result, st.top() + slow->val);
//           st.pop();
//           slow = slow->next;
//       }
//       return result;
//   }

//   PROS: Doesn't modify the list, easier to code
//   CONS: O(n/2) extra space for the stack
//   Mention as a trade-off if interviewer asks!

// ═══════════════════════════════════════════════════════════════════════════════
// 📚 PATTERN RECOGNITION CHEAT SHEET
// ═══════════════════════════════════════════════════════════════════════════════

//   "Find middle + Reverse second half + Two-pointer walk"
  
//   USE WHEN:
//   ✓ You need to compare/combine first half with second half
//   ✓ The list is a palindrome or has symmetric properties
//   ✓ You need O(1) space (can't use arrays/stacks)
  
//   RELATED PROBLEMS (Same Template!):
//   ┌─────────────────────────────────────────────────────────────┐
//   │ LC 234: Palindrome LL  → Compare halves (==)              │
//   │ LC 143: Reorder List   → Interleave halves (1,n,2,n-1...) │
//   │ LC 2134: This problem  → Max sum of twin pairs            │
//   │ LC 236: (variation)    → Any symmetric pair operation      │
//   └─────────────────────────────────────────────────────────────┘
  
//   THE MENTAL MODEL:
//   "Folding the list in half makes symmetric elements neighbors.
//    Reversing is the programmatic way to fold."

// */









// using stack
// class Solution {
// public:
//     int pairSum(ListNode* head) {
//         stack<int> st;

//         ListNode* curr = head;

//         while( curr != NULL){
//             st.push(curr->val);
//             curr = curr->next;
//         }
//         int N = st.size();
//         curr = head;
//         int count = 1;

//         int result = 0;

//         while(count <= N/2){
//             result = max(result, curr->val + st.top());
//             curr = curr->next;
//             st.pop();
//             count++;
//         }
//         return result;
//     }
// };






// using vector
// class Solution {
// public:
//     int pairSum(ListNode* head) {
//         vector<int> vec;

//         ListNode* curr = head;

//         while(curr != NULL){
//             vec.push_back(curr->val);
//             curr = curr->next;
//         }

//         int result = 0;

//         int i = 0, j = vec.size() - 1;

//         while(i < j){
//             result = max(result,  vec[i] + vec[j]);
//             i++;
//             j--;
//         }
//         return result;
//     }
// };