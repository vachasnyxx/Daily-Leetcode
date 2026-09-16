/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// recursively approach
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newHead;
    }
};

// iterative approach
// class Solution {
// public:
//     ListNode* reverseList(ListNode* head) {
//         ListNode* prev = NULL;
//         ListNode* curr = head;
//         ListNode* Next = head;
//         while(curr != NULL){
//             Next = curr->next;
//             curr->next = prev;
//             prev = curr;
//             curr = Next;
//         }
//         return prev;

//     }
// };








// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */

// class Solution {
// public:
//     ListNode* reverseList(ListNode* head) {
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 🎯 PROBLEM: LEETCODE 206 - REVERSE LINKED LIST (RECURSIVE APPROACH)
//         // ═══════════════════════════════════════════════════════════════════════════
//         // Given: Head of a singly linked list
//         // Return: The list reversed
//         //
//         // Example: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
//         // Output:  5 -> 4 -> 3 -> 2 -> 1 -> NULL
//         //
//         // APPROACH: Recursive "Unwinding" Method
//         // Think of it like a stack of plates - you go down to the last plate,
//         // then reverse connections as you come back up
//         // ═══════════════════════════════════════════════════════════════════════════
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 BASE CASE - When to STOP Recursion
//         // ═══════════════════════════════════════════════════════════════════════════
//         if (head == NULL || head->next == NULL)
//             return head;
        
//         // ───────────────────────────────────────────────────────────────────────────
//         // WHY TWO CONDITIONS?
//         // ───────────────────────────────────────────────────────────────────────────
//         // CONDITION 1: head == NULL
//         // ────────────────────────
//         // Handles: Empty list case
//         // Example: reverseList(NULL) → return NULL
//         // Without this: head->next would cause NULL pointer dereference! 💥
//         //
//         // CONDITION 2: head->next == NULL
//         // ────────────────────────────────
//         // Handles: Single node OR reached the LAST node during recursion
//         // Example: List is just [5] → return 5
//         //         OR we've recursed down to node 5 in [1,2,3,4,5]
//         //
//         // This is our "bottom of recursion" - the last node becomes new head
//         // Think: When you reach the last domino, it doesn't need reversing,
//         //        it becomes the starting point for the reversed list
//         // ───────────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 RECURSIVE CASE - Go Deeper First
//         // ═══════════════════════════════════════════════════════════════════════════
//         ListNode* newHead = reverseList(head->next);
        
//         // ───────────────────────────────────────────────────────────────────────────
//         // WHAT'S HAPPENING HERE?
//         // ───────────────────────────────────────────────────────────────────────────
//         // We're calling reverseList on the REST of the list (everything after head)
//         // This is the "DIVE DOWN" phase of recursion
//         //
//         // EXAMPLE TRACE (List: 1 -> 2 -> 3 -> NULL):
//         // ────────────────────────────────────────────
//         // Call 1: reverseList(1) → calls reverseList(2)
//         // Call 2: reverseList(2) → calls reverseList(3)
//         // Call 3: reverseList(3) → 3->next is NULL, BASE CASE! Returns 3
//         //
//         // Now we "unwind" back up:
//         // ───────────────────────
//         // Back in Call 2: newHead = 3 (the last node, our new head!)
//         // Back in Call 1: newHead = 3 (same head is passed back up)
//         //
//         // KEY INSIGHT:
//         // ────────────
//         // newHead will ALWAYS be the last node of original list (becomes first)
//         // It's discovered once at the bottom and passed back up unchanged
//         // Think of it as: "Find the last person in line, they become the leader"
//         //
//         // AT THIS POINT IN EXECUTION:
//         // ───────────────────────────
//         // The list from head->next onwards is ALREADY REVERSED (by recursion)
//         // But head is still pointing to the old next node
//         // We need to reverse the connection between head and head->next
//         // ───────────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 THE REVERSAL STEP - Most Critical Part! 🔥
//         // ═══════════════════════════════════════════════════════════════════════════
//         head->next->next = head;
        
//         // ───────────────────────────────────────────────────────────────────────────
//         // ⚠️ UNDERSTANDING THIS LINE IS KEY TO UNDERSTANDING RECURSION HERE
//         // ───────────────────────────────────────────────────────────────────────────
//         //
//         // Let's break it down with an example:
//         // ────────────────────────────────────
//         // Say we're unwinding and currently at node 2:
//         // head = 2
//         // head->next = 3 (still points to old next)
//         // The rest (3 onwards) is already reversed: 3 -> NULL
//         //
//         // VISUAL BEFORE THIS LINE:
//         // ────────────────────────
//         //     head
//         //      ↓
//         //      2  ──→  3  ──→  NULL
//         //            ↑
//         //         head->next
//         //
//         // WHAT head->next->next = head DOES:
//         // ──────────────────────────────────
//         // head->next       = 3 (the node after current)
//         // head->next->next = 3's next pointer (currently NULL)
//         // We SET it to     = head (which is 2)
//         //
//         // VISUAL AFTER THIS LINE:
//         // ───────────────────────
//         //     head
//         //      ↓
//         //      2  ←──  3  ──→  NULL
//         //       ↓
//         //      (still pointing at 3, we'll fix this next)
//         //
//         // Now node 3 points BACK to node 2! The link is reversed!
//         //
//         // BUT THERE'S A PROBLEM:
//         // ──────────────────────
//         // Node 2 STILL points forward to 3, creating a cycle: 2 ⇄ 3
//         // We need to break the old forward link...
//         //
//         // MEMORY TIP:
//         // ───────────
//         // Think: "Make my next node point back to me"
//         // head->next (my next) ->next (their next pointer) = head (points to me)
//         // ───────────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 BREAK THE OLD CONNECTION
//         // ═══════════════════════════════════════════════════════════════════════════
//         head->next = NULL;
        
//         // ───────────────────────────────────────────────────────────────────────────
//         // WHY IS THIS NECESSARY?
//         // ───────────────────────────────────────────────────────────────────────────
//         // After head->next->next = head, we have a cycle:
//         //     2 ⇄ 3
//         //
//         // We need to cut the forward link to prevent:
//         // 1. Infinite loops when traversing
//         // 2. Incorrect list structure
//         //
//         // VISUAL AFTER THIS LINE:
//         // ───────────────────────
//         //     head
//         //      ↓
//         //      2  ←──  3
//         //      ↓
//         //     NULL
//         //
//         // Now node 2 points to NULL (will be the new tail eventually)
//         // And node 3 points back to node 2 (reverse link established)
//         //
//         // IMPORTANT DETAIL:
//         // ─────────────────
//         // For the FIRST node (original head), setting head->next = NULL makes it
//         // the NEW TAIL of the reversed list. Perfect! ✓
//         //
//         // For MIDDLE nodes, this seems to "disconnect" them, but don't worry:
//         // In the next unwinding step (previous recursive call), the PREVIOUS node
//         // will point to this node, reconnecting it. Trust the recursion!
//         //
//         // ANALOGY:
//         // ────────
//         // Imagine people holding hands in a line:
//         // - Person A holding Person B's right hand
//         // - We make Person B hold Person A's left hand (reverse)
//         // - Then Person A lets go of Person B's right hand (break old connection)
//         // - Now Person B is "leading" Person A
//         // ───────────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 RETURN THE NEW HEAD
//         // ═══════════════════════════════════════════════════════════════════════════
//         return newHead;
        
//         // ───────────────────────────────────────────────────────────────────────────
//         // WHAT IS newHead?
//         // ───────────────────────────────────────────────────────────────────────────
//         // newHead is the ORIGINAL LAST NODE, discovered at the base case
//         // It's passed back unchanged through all recursive calls
//         // This becomes the new head of the reversed list
//         //
//         // WHY NOT RETURN head?
//         // ────────────────────
//         // head is the CURRENT node we're processing (could be 1, 2, 3, etc.)
//         // After reversal, head becomes part of the MIDDLE or TAIL, not the head!
//         // Only the original last node should be the new head
//         //
//         // EXAMPLE:
//         // ────────
//         // Original: 1 -> 2 -> 3 -> NULL
//         // When we reach 3, newHead = 3 (base case)
//         // As we unwind:
//         //   - At node 2: reverse 2⇄3, return newHead (still 3)
//         //   - At node 1: reverse 1⇄2, return newHead (still 3)
//         // Final return: 3 (which now leads: 3->2->1->NULL) ✓
//         // ───────────────────────────────────────────────────────────────────────────
//     }
// };


// /*
// ╔════════════════════════════════════════════════════════════════════════════════╗
// ║                                                                                ║
// ║                    🎓 COMPREHENSIVE REVISION SUMMARY                           ║
// ║                    LEETCODE 206: REVERSE LINKED LIST (RECURSIVE)               ║
// ║                                                                                ║
// ╚════════════════════════════════════════════════════════════════════════════════╝

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎯 THE BIG PICTURE - RECURSIVE REVERSAL                                       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// CORE IDEA: "Go to the end, reverse on the way back"

// RECURSION PHASES:
// ─────────────────
// 1. DIVE DOWN: Keep calling reverseList(head->next) until we reach the last node
// 2. BASE CASE: When we hit the last node, that becomes our new head
// 3. UNWIND: As we return from each recursive call, reverse the link
// 4. RETURN: Pass the new head back up through all calls


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎨 VISUAL WALKTHROUGH - COMPLETE EXECUTION TRACE                              ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// Original List: 1 -> 2 -> 3 -> 4 -> NULL

// ┌─────────────────────────────────────────────────────────────┐
// │ PHASE 1: DIVING DOWN (Making Recursive Calls)              │
// └─────────────────────────────────────────────────────────────┘

// Call Stack Building:
// ────────────────────

// reverseList(1)  →  head = 1, head->next = 2 (not base case)
//     ↓
//     calls reverseList(2)  →  head = 2, head->next = 3 (not base case)
//         ↓
//         calls reverseList(3)  →  head = 3, head->next = 4 (not base case)
//             ↓
//             calls reverseList(4)  →  head = 4, head->next = NULL
//                                       ✓ BASE CASE! Return 4

// Call Stack Now:
// ───────────────
// reverseList(1) ← waiting
//     reverseList(2) ← waiting
//         reverseList(3) ← waiting
//             reverseList(4) ← RETURNED 4 (newHead)


// ┌─────────────────────────────────────────────────────────────┐
// │ PHASE 2: UNWINDING (Reversing Links as We Return)          │
// └─────────────────────────────────────────────────────────────┘

// ═══════════════════════════════════════════════════════════════
// UNWINDING STEP 1: Back in reverseList(3)
// ═══════════════════════════════════════════════════════════════
// Context:
//   head = 3
//   head->next = 4
//   newHead = 4 (returned from reverseList(4))

// Current State:
//   1 -> 2 -> 3 -> 4 -> NULL
//             ↑    ↑
//           head  newHead

// Execute: head->next->next = head
//   ↳ 4->next = 3 (making 4 point back to 3)

// State Now:
//   1 -> 2 -> 3 ⇄ 4
//             ↑
//           head

// Execute: head->next = NULL
//   ↳ 3->next = NULL (breaking forward link)

// State Now:
//   1 -> 2 -> 3 <- 4
//             ↓
//            NULL

// Return: newHead (which is 4)


// ═══════════════════════════════════════════════════════════════
// UNWINDING STEP 2: Back in reverseList(2)
// ═══════════════════════════════════════════════════════════════
// Context:
//   head = 2
//   head->next = 3
//   newHead = 4 (returned from reverseList(3))

// Current State:
//   1 -> 2 -> 3 <- 4
//        ↑    ↓
//      head  NULL

// Execute: head->next->next = head
//   ↳ 3->next = 2 (making 3 point back to 2)

// State Now:
//   1 -> 2 ⇄ 3 <- 4
//        ↑
//      head

// Execute: head->next = NULL
//   ↳ 2->next = NULL

// State Now:
//   1 -> 2 <- 3 <- 4
//        ↓
//       NULL

// Return: newHead (which is 4)


// ═══════════════════════════════════════════════════════════════
// UNWINDING STEP 3: Back in reverseList(1)
// ═══════════════════════════════════════════════════════════════
// Context:
//   head = 1
//   head->next = 2
//   newHead = 4 (returned from reverseList(2))

// Current State:
//   1 -> 2 <- 3 <- 4
//   ↑    ↓
// head  NULL

// Execute: head->next->next = head
//   ↳ 2->next = 1 (making 2 point back to 1)

// State Now:
//   1 ⇄ 2 <- 3 <- 4
//   ↑
// head

// Execute: head->next = NULL
//   ↳ 1->next = NULL

// Final State:
//   NULL <- 1 <- 2 <- 3 <- 4
//           ↑              ↑
//         (tail)        newHead

// Return: newHead (which is 4)

// FINAL REVERSED LIST: 4 -> 3 -> 2 -> 1 -> NULL ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🧠 THE "AHA!" MOMENT - KEY INSIGHTS                                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #1: The Recursion Goes DEEP First                 ║
// ╚═══════════════════════════════════════════════════════════════╝

// We don't reverse ANYTHING while going down
// We just keep calling reverseList(head->next) until base case
// Think: "Walk to the end of the bridge before turning around"

// All the ACTUAL WORK happens during the UNWINDING phase


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #2: newHead Never Changes                         ║
// ╚═══════════════════════════════════════════════════════════════╝

// Once we discover the last node (base case), that's our newHead
// It gets passed back unchanged through every recursive return
// It's like finding the "king" at the end - he stays king as we
// reorganize everyone else around him


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #3: Two-Step Reversal Dance                       ║
// ╚═══════════════════════════════════════════════════════════════╝

// For each node during unwinding:
// 1. head->next->next = head  → "Make next node point back to me"
// 2. head->next = NULL        → "Let go of next node"

// This pattern repeats for EVERY node except the last one


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #4: Trust the Recursion                           ║
// ╚═══════════════════════════════════════════════════════════════╝

// When we set head->next = NULL, it looks like we're "disconnecting"
// the node. But the PREVIOUS recursion level will reconnect it!

// Example:
//   At node 2: We set 2->next = NULL (seems disconnected)
//   At node 1: We set 1->next = NULL, but first 2->next = 1 happens
//   Result: 2 -> 1 -> NULL (reconnected!)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⏱️ COMPLEXITY ANALYSIS                                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╭────────────────────────────────────────────────────────────────╮
// │  ⏱️ TIME COMPLEXITY: O(n)                                      │
// ╰────────────────────────────────────────────────────────────────╯

// WHERE n = number of nodes

// REASONING:
// ──────────
// - We make exactly n recursive calls (one for each node)
// - Each recursive call does O(1) work:
//   * One comparison (base case check)
//   * Two pointer assignments (reverse the link)
// - Total: n × O(1) = O(n)

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We visit each node exactly once through recursion. At each node,
// we perform constant-time operations (pointer manipulations). Therefore,
// the time complexity is linear, O(n)."


// ╭────────────────────────────────────────────────────────────────╮
// │  💾 SPACE COMPLEXITY: O(n)                                     │
// ╰────────────────────────────────────────────────────────────────╯

// WHY O(n) and not O(1)?
// ──────────────────────
// Because of RECURSIVE CALL STACK!

// CALL STACK VISUALIZATION:
// ─────────────────────────
// For list with 4 nodes:

// reverseList(1)     ← Frame 1
//   reverseList(2)   ← Frame 2
//     reverseList(3) ← Frame 3
//       reverseList(4) ← Frame 4 (base case)

// Each recursive call adds a new frame to the call stack
// Stack depth = number of nodes = n
// Each frame stores: head, newHead, return address = O(1) space
// Total stack space: n × O(1) = O(n)

// IMPORTANT NOTE:
// ───────────────
// This is IMPLICIT space (call stack), not EXPLICIT space (variables)
// We don't create new nodes or arrays
// But recursion uses memory for the call stack!

// INTERVIEW EXPLANATION:
// ─────────────────────
// "The space complexity is O(n) due to the recursive call stack. We
// make n recursive calls, each adding a frame to the stack. At the
// deepest point, we have n frames on the stack, each using constant
// space. If we needed O(1) space, we'd use an iterative approach instead."


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🔄 COMPARISON: RECURSIVE vs ITERATIVE                                         ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// RECURSIVE (Your Solution):
// ──────────────────────────
// ✓ Elegant and concise (4 lines of logic)
// ✓ Easy to understand conceptually
// ✗ O(n) space due to call stack
// ✗ Risk of stack overflow for very long lists (>10,000 nodes)

// ITERATIVE (Alternative):
// ────────────────────────
// ✓ O(1) space (only 3 pointers needed)
// ✓ No stack overflow risk
// ✗ Slightly more code
// ✗ Requires mental tracking of 3 pointers (prev, curr, next)

// WHEN TO USE WHICH:
// ──────────────────
// - Interviews: Either is fine, but mention the trade-off
// - Production: Iterative is safer for unknown list lengths
// - Learning: Recursive teaches recursion thinking


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🐛 EDGE CASES & HOW THEY'RE HANDLED                                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// EDGE CASE 1: Empty List (head = NULL)
// ──────────────────────────────────────
// Input: NULL
// Base case: head == NULL → return NULL ✓
// Output: NULL

// EDGE CASE 2: Single Node
// ─────────────────────────
// Input: 5 -> NULL
// Base case: head->next == NULL → return head ✓
// Output: 5 -> NULL (unchanged, which is correct)

// EDGE CASE 3: Two Nodes
// ──────────────────────
// Input: 1 -> 2 -> NULL
// Execution:
//   reverseList(1) calls reverseList(2)
//   reverseList(2): base case, returns 2
//   Back in reverseList(1):
//     2->next = 1
//     1->next = NULL
//     return 2
// Output: 2 -> 1 -> NULL ✓

// EDGE CASE 4: All Same Values
// ─────────────────────────────
// Input: 3 -> 3 -> 3 -> NULL
// Output: 3 -> 3 -> 3 -> NULL
// (Algorithm works fine, values don't matter, only structure)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⚠️ COMMON MISTAKES & HOW TO AVOID THEM                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ❌ MISTAKE #1: Forgetting Base Case
// ───────────────────────────────────
// Without: if (head == NULL || head->next == NULL)
// Result: Stack overflow! Infinite recursion!

// ❌ MISTAKE #2: Wrong Order of Operations
// ────────────────────────────────────────
// Wrong:
//   head->next = NULL;             ← Sets next to NULL first
//   head->next->next = head;       ← CRASH! head->next is NULL!

// Correct:
//   head->next->next = head;       ← Use head->next while it's valid
//   head->next = NULL;             ← Then set it to NULL

// ❌ MISTAKE #3: Returning head Instead of newHead
// ─────────────────────────────────────────────────
// Wrong: return head;
//   → Returns the CURRENT node (becomes tail), not the new head!

// Correct: return newHead;
//   → Returns the ORIGINAL last node (new head)

// ❌ MISTAKE #4: Not Setting head->next = NULL
// ────────────────────────────────────────────
// Without this line, you create a cycle!
// Node points to next, next points back to node → infinite loop


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎤 INTERVIEW TALKING POINTS                                                   ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// OPENING:
// ────────
// "I'll solve this using recursion. The idea is to recurse to the end
// of the list to find the new head, then reverse the links as we unwind
// the call stack. Let me code it step by step."

// DURING CODING:
// ──────────────
// [Base case] "First, I handle empty list and single node cases..."
// [Recursive call] "Then I recurse on the rest of the list..."
// [Reversal] "The key step: make the next node point back to current..."
// [Break link] "And break the old forward connection..."

// AFTER CODING:
// ─────────────
// "The time complexity is O(n) since we visit each node once. The space
// complexity is also O(n) due to the recursive call stack. If space is
// a concern, we could use an iterative approach with three pointers for
// O(1) space complexity."


// ═══════════════════════════════════════════════════════════════════════════════

// 🎓 MEMORY TRICK - THE "DOMINO FLIP" ANALOGY:

// Imagine dominoes standing in a row →→→
// You walk to the LAST domino (recursion down)
// Then as you walk BACK, you flip each domino to face the other way
// Each domino now points to the one you just came from
// By the time you return to the start, all dominoes point backwards ←←←

// That's exactly what this recursion does with linked list nodes!

// ═══════════════════════════════════════════════════════════════════════════════
// */