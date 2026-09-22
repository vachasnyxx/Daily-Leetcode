class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* p1 = NULL;
        ListNode* p2 = NULL;

        ListNode* temp = head;

        while(temp != NULL){

            if(p2 != NULL){
                p2 = p2->next;
            }

            k--;
            if(k == 0){
                p1 = temp;
                p2 = head;
            }
            temp = temp->next;
        }
        swap(p1->val, p2->val);
        return head;
    }
};









// class Solution {
// public:
//     ListNode* swapNodes(ListNode* head, int k) {
        
//         // ============================================================
//         // PROBLEM: Swap the k-th node from START and k-th node from END
//         // Example: [1,2,3,4,5], k=2  →  swap node 2 and node 4
//         //          [1, 2, 3, 4, 5]
//         //               ↑        ↑
//         //            k=2nd    2nd from end
//         // ============================================================
        
//         ListNode* p1 = NULL;   // Will point to k-th node from START
//         ListNode* p2 = NULL;   // Will point to k-th node from END
        
//         ListNode* temp = head; // Iterator to walk through the list
        
//         // ============================================================
//         // THE GENIUS SINGLE-PASS TRICK 🧠
//         // ============================================================
//         // Instead of two passes (one to find length, one to find nodes),
//         // we use a GAP TECHNIQUE:
//         //
//         // Step 1: Walk until we hit the k-th node → lock p1 there
//         // Step 2: At that EXACT moment, start p2 from head
//         // Step 3: Now p2 and temp move together until temp hits NULL
//         //
//         // WHY p2 lands on k-th from end:
//         // ──────────────────────────────
//         // When temp is at k-th node, there are (n-k) nodes remaining.
//         // p2 starts at head and also moves (n-k) steps.
//         // So p2 ends at position (n-k+1) from start = k-th from end!
//         //
//         // VISUAL for [1,2,3,4,5], k=2:
//         // ─────────────────────────────
//         // Iteration 1: temp→1, k becomes 1
//         // Iteration 2: temp→2, k becomes 0 → p1=2, p2=head(1)  ← GAP CREATED!
//         // Iteration 3: temp→3, p2→2   (both move together)
//         // Iteration 4: temp→4, p2→3   (both move together)
//         // Iteration 5: temp→5, p2→4   (both move together)
//         // temp→NULL: STOP! p1=2, p2=4 ✓
//         // ============================================================
        
//         while(temp != NULL){
            
//             // ─── PHASE 2: Move p2 forward (only AFTER gap is created) ───
//             // p2 is NULL until we find the k-th node from start.
//             // Once p2 is set to head, it chases temp with a gap of (k-1) nodes.
//             if(p2 != NULL){
//                 p2 = p2->next;
//                 // ⚠️ ATOMIC DETAIL #1: This runs BEFORE the k-check below.
//                 // This is CRUCIAL! On the iteration where k hits 0,
//                 // p2 is still NULL here, so it doesn't move prematurely.
//                 // It only gets set to head AFTER this block.
//             }
            
//             // ─── COUNTDOWN: Decrement k to find the k-th node ───
//             k--;
            
//             // ─── PHASE 1: Lock p1 and activate p2 ───
//             if(k == 0){
//                 p1 = temp;      // 🔒 Lock: k-th node from start FOUND!
//                 p2 = head;      // 🚀 Activate: p2 starts its journey from head
//                 // ⚠️ ATOMIC DETAIL #2: p2 starts at head, NOT at temp.
//                 // The gap between temp and p2 is exactly (k-1) nodes,
//                 // which is what we need for p2 to land on k-th from end.
//             }
            
//             // ─── ADVANCE: Move to next node ───
//             temp = temp->next;
//         }
        
//         // ============================================================
//         // SWAP VALUES (not nodes!)
//         // ============================================================
//         // ⚠️ ATOMIC DETAIL #3: We swap VALUES, not node pointers.
//         // Swapping actual nodes would require tracking prev pointers
//         // and handling many edge cases (adjacent nodes, head/tail, etc.)
//         // Value swap is O(1) and much cleaner.
//         // 
//         // The problem says "swap the values" so this is valid.
//         // ============================================================
//         swap(p1->val, p2->val);
        
//         return head; // Head never changes since we only swap values
//     }
// };

// /*
// ╔══════════════════════════════════════════════════════════════════════════════╗
// ║                   🧠 DEEP DIVE REVISION GUIDE - LC 1721                      ║
// ╚══════════════════════════════════════════════════════════════════════════════╝

// 📌 PROBLEM: Swap k-th node from beginning with k-th node from end

// 🎯 ALGORITHM: Two-Pointer Gap Technique (Single Pass)

// ═══════════════════════════════════════════════════════════════════════════════
// 🏃 THE "RACE TRACK" ANALOGY (Remember This Forever!)
// ═══════════════════════════════════════════════════════════════════════════════

// Imagine a race track with N runners lined up:

//   Start ──[R1]──[R2]──[R3]──[R4]──[R5]── Finish
//                   ↑                  ↑
//               k=2nd from         2nd from
//                start               end

// Now imagine TWO joggers:
//   🏃 Jogger A (temp): Starts at the beginning, runs to the finish
//   🚶 Jogger B (p2):   Waits at the start line until Jogger A reaches 
//                        the k-th position, THEN starts jogging

//   When Jogger A reaches the k-th runner:
//     🏃 A is at position k
//     🚶 B is at position 1 (just starting)
//     GAP between them = k-1 positions

//   They now jog TOGETHER at the same speed.
//   When A reaches the FINISH (end of list):
//     B is exactly k positions from the finish!
//     Because the gap never changed!

//   That's it. B is your k-th from end. 🎯

// ═══════════════════════════════════════════════════════════════════════════════
// 📐 MATHEMATICAL PROOF (For Interview Confidence)
// ═══════════════════════════════════════════════════════════════════════════════

//   List length = n
//   k-th from start = position k
//   k-th from end   = position (n - k + 1)

//   When temp reaches position k:
//     → p2 starts at position 1 (head)
//     → Remaining steps for temp = n - k

//   After (n-k) more steps:
//     → temp is at position n + 1 (NULL, past end)
//     → p2 is at position 1 + (n-k) = n - k + 1  ← EXACTLY k-th from end! ✓

// ═══════════════════════════════════════════════════════════════════════════════
// ⚠️ ATOMIC DETAILS YOU MUST NOTICE (Interview Differentiators)
// ═══════════════════════════════════════════════════════════════════════════════

//   1️⃣ ORDER OF OPERATIONS MATTERS!
//      ┌─────────────────────────────────────────────────────┐
//      │ if(p2 != NULL) p2 = p2->next;  ← CHECK FIRST       │
//      │ k--;                             ← DECREMENT SECOND │
//      │ if(k == 0) { p1=temp; p2=head; } ← SET THIRD        │
//      └─────────────────────────────────────────────────────┘
//      If you swap the order, p2 moves one step too early
//      and lands on the WRONG node!

//   2️⃣ p2 STARTS AT head, NOT at temp
//      The entire trick depends on p2 starting at the very
//      beginning when temp is at position k.

//   3️⃣ k is DECREMENTED (k--) not compared directly
//      We use k as a countdown timer, not a position index.
//      k=2 → k=1 → k=0 (BOOM! found it)

//   4️⃣ We swap VALUES, not NODES
//      Swapping nodes requires prev pointers and is a nightmare
//      with edge cases. Value swap is clean and accepted here.

//   5️⃣ p1 and p2 CAN point to the SAME node
//      Example: [1,2,3], k=2 → both point to node 2
//      swap(2,2) = no change. Code handles this naturally! ✓

//   6️⃣ k is 1-INDEXED (not 0-indexed)
//      k=1 means first node from start AND first from end (last node)

// ═══════════════════════════════════════════════════════════════════════════════
// 🐛 EDGE CASES TO THINK ABOUT
// ═══════════════════════════════════════════════════════════════════════════════

//   Case 1: k = 1
//     → Swap head and tail
//     → p1 = head (found immediately), p2 walks to last node ✓

//   Case 2: k = n (last node)
//     → Same as k=1 but reversed
//     → p1 = last node, p2 = head ✓

//   Case 3: k = middle of odd-length list
//     → p1 and p2 point to SAME node
//     → swap(x, x) = no-op ✓

//   Case 4: Single node list [1], k=1
//     → p1 = p2 = head, swap does nothing ✓

//   Case 5: Two nodes [1,2], k=1
//     → p1 = node 1, p2 = node 2, swap values ✓

// ═══════════════════════════════════════════════════════════════════════════════
// ⏱️ COMPLEXITY (Easy Interview Explanation)
// ═══════════════════════════════════════════════════════════════════════════════

//   TIME: O(n)
//   ──────────
//   "We traverse the linked list exactly ONCE from head to tail.
//    Both pointers move in the same loop, so it's a single pass.
//    The swap at the end is O(1). Total = O(n)."

//   SPACE: O(1)
//   ────────────
//   "We only use three pointers (p1, p2, temp) and one integer (k).
//    No extra data structures, no recursion. Constant space."

// ═══════════════════════════════════════════════════════════════════════════════
// 🎤 INTERVIEWER EXPLANATION SCRIPT (30 seconds)
// ═══════════════════════════════════════════════════════════════════════════════

//   "I'll use a two-pointer gap technique in a single pass.
//    I walk through the list with a temp pointer, counting down k.
//    When k reaches zero, I've found the k-th node from the start — 
//    I lock pointer p1 there and activate pointer p2 at the head.
//    Now both temp and p2 move together. When temp reaches the end,
//    p2 is exactly k positions from the end due to the maintained gap.
//    Finally, I swap their values. This is O(n) time, O(1) space."

// ═══════════════════════════════════════════════════════════════════════════════
// 🔄 ALTERNATIVE APPROACH (Two Pass - Simpler to Think, Slower Conceptually)
// ═══════════════════════════════════════════════════════════════════════════════

//   Pass 1: Count total nodes → get length n
//   Pass 2: Find node at position k AND node at position (n-k+1)
//   Swap their values.

//   Same O(n) time but TWO passes. Your single-pass solution is BETTER!
//   Mention this in interviews to show depth of understanding.

// ═══════════════════════════════════════════════════════════════════════════════
// 📚 PATTERN RECOGNITION (When to Use This Technique)
// ═══════════════════════════════════════════════════════════════════════════════

//   Use the GAP TECHNIQUE when:
//   ✓ You need to find the N-th node from the END of a linked list
//   ✓ You want to do it in ONE pass
//   ✓ Problems like: Remove Nth from End (LC 19), Middle of List (LC 876)
  
//   The pattern is ALWAYS:
//   → Give one pointer a head start of N steps
//   → Move both at same speed
//   → When fast pointer hits end, slow pointer is at target

// */