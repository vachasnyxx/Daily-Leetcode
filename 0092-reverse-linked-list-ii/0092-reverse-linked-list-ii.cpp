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
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* Next = head;
        while (curr != NULL) {
            Next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = Next;
        }
        return prev;
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right)
            return head;
        ListNode* a = NULL;
        ListNode* b = NULL;
        ListNode* c = NULL;
        ListNode* d = NULL;
        ListNode* temp = head;
        int n = 1;
        while (temp) {
            if (n == left - 1)
                a = temp;
            if (n == left)
                b = temp;
            if (n == right)
                c = temp;
            if (n == right + 1)
                d = temp;
            temp = temp->next;
            n++;
        }
        if (a != NULL) {
            a->next = NULL;
        }
        c->next = NULL;
        c = reverseList(b);
        if (a != NULL)
            a->next = c;
        b->next = d;
        if(a != NULL) return head;
        return c;
    }
};






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

// class Solution {
// public:
//     // ═══════════════════════════════════════════════════════════════════════════
//     // 🔧 HELPER FUNCTION: REVERSE LINKED LIST (ITERATIVE)
//     // ═══════════════════════════════════════════════════════════════════════════
//     // Same as before - reverses entire list from given head to end
//     // ═══════════════════════════════════════════════════════════════════════════
    
//     ListNode* reverseList(ListNode* head) {
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THREE-POINTER REVERSAL TECHNIQUE
//         // ───────────────────────────────────────────────────────────────────────
//         // This reverses the ENTIRE list starting from 'head' to NULL
//         // We'll use this to reverse ONLY a portion by careful pointer manipulation
//         // ───────────────────────────────────────────────────────────────────────
        
//         ListNode* prev = NULL;     // Previous node (what we're pointing back to)
//         ListNode* curr = head;     // Current node being processed
//         ListNode* Next = head;     // Next node (saved before breaking link)
        
//         while (curr != NULL) {
//             Next = curr->next;     // Save next node before we lose it
//             curr->next = prev;     // Reverse the link
//             prev = curr;           // Move prev forward
//             curr = Next;           // Move curr forward
//         }
        
//         return prev;  // prev is now the new head of reversed list
//     }
    
    
//     // ═══════════════════════════════════════════════════════════════════════════
//     // 🎯 MAIN FUNCTION: REVERSE SUBLIST BETWEEN POSITIONS left AND right
//     // ═══════════════════════════════════════════════════════════════════════════
//     // PROBLEM: LEETCODE 92 - REVERSE LINKED LIST II
//     // ═══════════════════════════════════════════════════════════════════════════
//     // Given: Head of a linked list and positions 'left' and 'right' (1-indexed)
//     // Task: Reverse ONLY the nodes from position left to right (inclusive)
//     // Return: Head of the modified list
//     //
//     // Example: 1 -> 2 -> 3 -> 4 -> 5, left = 2, right = 4
//     // Output:  1 -> 4 -> 3 -> 2 -> 5
//     //          └─┘  └────┬────┘  └─┘
//     //         same   reversed   same
//     //
//     // CONSTRAINTS:
//     // - 1 ≤ left ≤ right ≤ n (number of nodes)
//     // - Positions are 1-indexed (not 0-indexed!)
//     // ═══════════════════════════════════════════════════════════════════════════
    
//     ListNode* reverseBetween(ListNode* head, int left, int right) {
        
//         // ───────────────────────────────────────────────────────────────────────
//         // 🎯 HIGH-LEVEL STRATEGY: "ISOLATE, REVERSE, RECONNECT"
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // CONCEPT: We need to reverse PART of the list, not all of it
//         //
//         // STEPS:
//         // 1. IDENTIFY four critical nodes: a, b, c, d
//         // 2. ISOLATE the sublist [b...c] by breaking connections
//         // 3. REVERSE the isolated sublist
//         // 4. RECONNECT the reversed sublist back into the main list
//         //
//         // VISUAL REPRESENTATION:
//         // ──────────────────────
//         // Original:  ... -> a -> b -> ... -> c -> d -> ...
//         //                   ↑         ↑         ↑    ↑
//         //                   |         |         |    |
//         //              (left-1)   (left)    (right) (right+1)
//         //
//         // After:     ... -> a -> c -> ... -> b -> d -> ...
//         //                   └──── reversed ────┘
//         //
//         // KEY NODES:
//         // ──────────
//         // a = node at position (left - 1)  → The node BEFORE the reversal zone
//         // b = node at position (left)      → START of reversal zone
//         // c = node at position (right)     → END of reversal zone
//         // d = node at position (right + 1) → The node AFTER the reversal zone
//         //
//         // SPECIAL CASES TO HANDLE:
//         // ────────────────────────
//         // • If left = 1: 'a' doesn't exist (we're reversing from head)
//         // • If right = n: 'd' doesn't exist (we're reversing till tail)
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 BASE CASE: No Reversal Needed
//         // ═══════════════════════════════════════════════════════════════════════
//         if (left == right)
//             return head;
        
//         // ───────────────────────────────────────────────────────────────────────
//         // WHY THIS CHECK?
//         // ───────────────────────────────────────────────────────────────────────
//         // If left == right, we're "reversing" a single node
//         // Example: Reverse from position 3 to 3 → No change needed!
//         // Reversing one node does nothing, so return original list
//         // This also prevents unnecessary work below
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 1: INITIALIZE THE FOUR CRITICAL POINTERS
//         // ═══════════════════════════════════════════════════════════════════════
//         ListNode* a = NULL;  
//         // Node at position (left - 1) - the node BEFORE reversal zone
//         // Will be NULL if left == 1 (reversing from head)
        
//         ListNode* b = NULL;  
//         // Node at position (left) - FIRST node to be reversed
//         // After reversal, this becomes the LAST node of reversed section
        
//         ListNode* c = NULL;  
//         // Node at position (right) - LAST node to be reversed
//         // After reversal, this becomes the FIRST node of reversed section
        
//         ListNode* d = NULL;  
//         // Node at position (right + 1) - the node AFTER reversal zone
//         // Will be NULL if right == n (reversing till end)
        
//         // ───────────────────────────────────────────────────────────────────────
//         // WHY INITIALIZE TO NULL?
//         // ───────────────────────────────────────────────────────────────────────
//         // NOT all four nodes may exist in every case:
//         // • If left = 1: 'a' won't exist (no node before first node)
//         // • If right = n: 'd' won't exist (no node after last node)
//         // NULL initialization helps us detect these cases later
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 2: FIND THE FOUR CRITICAL NODES (SINGLE TRAVERSAL)
//         // ═══════════════════════════════════════════════════════════════════════
//         ListNode* temp = head;  
//         // Traversal pointer to walk through the list
        
//         int n = 1;              
//         // Position counter (1-indexed to match left/right)
//         // Starts at 1 because linked lists positions in this problem are 1-indexed
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THE IDENTIFICATION LOOP
//         // ───────────────────────────────────────────────────────────────────────
//         // GOAL: Walk through the list ONCE and mark a, b, c, d as we encounter them
//         //
//         // EXAMPLE TRACE (List: 1->2->3->4->5, left=2, right=4):
//         // ──────────────────────────────────────────────────────────────────────
//         // n=1, temp=1: Check all conditions → No matches
//         // n=2, temp=2: n==left → b=2
//         // n=3, temp=3: Check all conditions → No matches
//         // n=4, temp=4: n==right → c=4
//         // n=5, temp=5: n==right+1 → d=5
//         //
//         // After loop: a=1, b=2, c=4, d=5 ✓
//         // ───────────────────────────────────────────────────────────────────────
        
//         while (temp) {
            
//             if (n == left - 1)
//                 a = temp;
//             // ───────────────────────────────────────────────────────────────────
//             // CAPTURING NODE 'a' - The Guard Before Reversal Zone
//             // ───────────────────────────────────────────────────────────────────
//             // When position is (left - 1), we've found the node BEFORE reversal
//             //
//             // Example: left = 3, we want position 2
//             // List: 1 -> 2 -> 3 -> 4 -> 5
//             //            ↑    ↑
//             //            a    b (reversal starts here)
//             //
//             // EDGE CASE: If left = 1, this condition is n == 0
//             // But n starts at 1, so this NEVER executes → a stays NULL ✓
//             // This correctly handles "reversing from head" scenario
//             // ───────────────────────────────────────────────────────────────────
            
//             if (n == left)
//                 b = temp;
//             // ───────────────────────────────────────────────────────────────────
//             // CAPTURING NODE 'b' - Start of Reversal Zone
//             // ───────────────────────────────────────────────────────────────────
//             // When position equals 'left', this is our first node to reverse
//             //
//             // Example: left = 2
//             // List: 1 -> 2 -> 3 -> 4 -> 5
//             //            ↑
//             //            b (first to be reversed)
//             //
//             // KEY INSIGHT: After reversal, 'b' will become the TAIL of reversed section
//             // We'll need to connect b->next to 'd' later!
//             // ───────────────────────────────────────────────────────────────────
            
//             if (n == right)
//                 c = temp;
//             // ───────────────────────────────────────────────────────────────────
//             // CAPTURING NODE 'c' - End of Reversal Zone
//             // ───────────────────────────────────────────────────────────────────
//             // When position equals 'right', this is our last node to reverse
//             //
//             // Example: right = 4
//             // List: 1 -> 2 -> 3 -> 4 -> 5
//             //                      ↑
//             //                      c (last to be reversed)
//             //
//             // KEY INSIGHT: After reversal, 'c' will become the HEAD of reversed section
//             // We'll need to connect 'a' to 'c' later!
//             // ───────────────────────────────────────────────────────────────────
            
//             if (n == right + 1)
//                 d = temp;
//             // ───────────────────────────────────────────────────────────────────
//             // CAPTURING NODE 'd' - The Guard After Reversal Zone
//             // ───────────────────────────────────────────────────────────────────
//             // When position is (right + 1), we've found the node AFTER reversal
//             //
//             // Example: right = 4, we want position 5
//             // List: 1 -> 2 -> 3 -> 4 -> 5
//             //                      ↑    ↑
//             //                      c    d (reversal ends before this)
//             //
//             // EDGE CASE: If right = n (last node), there's no (right + 1)
//             // This condition never executes → d stays NULL ✓
//             // This correctly handles "reversing till end" scenario
//             // ───────────────────────────────────────────────────────────────────
            
//             temp = temp->next;  // Move to next node
//             n++;                // Increment position counter
//         }
        
//         // ───────────────────────────────────────────────────────────────────────
//         // AFTER THE LOOP - VERIFICATION
//         // ───────────────────────────────────────────────────────────────────────
//         // At this point, we have identified (or left as NULL):
//         // • a: The connector node before reversal (NULL if left==1)
//         // • b: First node of reversal zone (always exists)
//         // • c: Last node of reversal zone (always exists)
//         // • d: The connector node after reversal (NULL if right==n)
//         //
//         // IMPORTANT: 'b' and 'c' will ALWAYS be non-NULL (guaranteed by constraints)
//         // But 'a' and 'd' MAY be NULL in edge cases
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 3: ISOLATE THE SUBLIST [b...c] - "CUT THE WIRES"
//         // ═══════════════════════════════════════════════════════════════════════
        
//         if (a != NULL) {
//             a->next = NULL;
//         }
//         // ───────────────────────────────────────────────────────────────────────
//         // BREAKING THE LEFT CONNECTION
//         // ───────────────────────────────────────────────────────────────────────
//         // WHY: To isolate the sublist for reversal
//         //
//         // BEFORE:  ... -> a -> b -> ... -> c -> d -> ...
//         //                  └────────┘
//         //                (to be reversed)
//         //
//         // AFTER:   ... -> a    b -> ... -> c -> d -> ...
//         //                 X    └────────┘
//         //              (cut!)
//         //
//         // Now the sublist starting at 'b' is disconnected from the left part
//         //
//         // WHY CHECK if (a != NULL)?
//         // ─────────────────────────
//         // If left = 1, 'a' doesn't exist (we're reversing from head)
//         // We can't do NULL->next = NULL (crash!)
//         // In that case, there's no left connection to break anyway
//         //
//         // EXAMPLE: left=1, right=3 in list 1->2->3->4->5
//         // a = NULL (no node before position 1)
//         // We skip this step - no left connection to break ✓
//         // ───────────────────────────────────────────────────────────────────────
        
//         c->next = NULL;
//         // ───────────────────────────────────────────────────────────────────────
//         // BREAKING THE RIGHT CONNECTION
//         // ───────────────────────────────────────────────────────────────────────
//         // WHY: To terminate the sublist for reversal
//         //
//         // BEFORE:  ... -> a    b -> ... -> c -> d -> ...
//         //
//         // AFTER:   ... -> a    b -> ... -> c    d -> ...
//         //                      └────────┘ X
//         //                   (isolated)  (cut!)
//         //
//         // Now the sublist [b...c] is completely isolated
//         // It's a standalone list: b -> ... -> c -> NULL
//         //
//         // WHY NO CHECK for c != NULL?
//         // ───────────────────────────
//         // 'c' is ALWAYS non-NULL (guaranteed by constraints: left ≤ right ≤ n)
//         // We always have at least one node to reverse
//         //
//         // CRITICAL: Setting c->next = NULL is necessary for reverseList to work!
//         // reverseList expects a NULL-terminated list
//         // Without this, reversal could go beyond 'c' into the 'd' section!
//         //
//         // EDGE CASE: What if right = n (last node)?
//         // ─────────────────────────────────────────
//         // Then c->next is already NULL! Setting it again doesn't hurt.
//         // No issue here ✓
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 4: REVERSE THE ISOLATED SUBLIST
//         // ═══════════════════════════════════════════════════════════════════════
//         c = reverseList(b);
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THE REVERSAL - CRITICAL UNDERSTANDING!
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // INPUT TO reverseList:
//         // ─────────────────────
//         // b -> ... -> c -> NULL (the isolated sublist)
//         //
//         // WHAT reverseList DOES:
//         // ──────────────────────
//         // Reverses the entire list starting from 'b'
//         //
//         // BEFORE REVERSAL:
//         // b -> x -> y -> c -> NULL
//         //
//         // AFTER REVERSAL:
//         // c -> y -> x -> b -> NULL
//         //
//         // RETURN VALUE:
//         // ─────────────
//         // reverseList returns the NEW HEAD of the reversed list
//         // The new head is 'c' (what was the tail is now the head)
//         //
//         // WHY ASSIGN TO 'c'?
//         // ──────────────────
//         // After reversal:
//         // • The original 'c' node is now the FIRST node of reversed list
//         // • We REUSE variable 'c' to point to this new head
//         // • The original 'b' node is now the LAST node (tail) of reversed list
//         // • 'b' still points to the original 'b' node (useful for reconnection!)
//         //
//         // VISUAL TRANSFORMATION:
//         // ──────────────────────
//         // Before: b(2) -> 3 -> c(4) -> NULL
//         //         ↑              ↑
//         //         b              c
//         //
//         // After:  c(4) -> 3 -> b(2) -> NULL
//         //         ↑              ↑
//         //         c (new!)       b (same!)
//         //
//         // KEY INSIGHT:
//         // ────────────
//         // Variable 'c' now points to the new head of reversed section
//         // Variable 'b' still points to the same node, which is now the tail!
//         // This is PERFECT for reconnection:
//         // • We need to connect 'a' to the new head → a->next = c ✓
//         // • We need to connect the new tail to 'd' → b->next = d ✓
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 5: RECONNECT THE REVERSED SUBLIST - "REWIRE THE CIRCUIT"
//         // ═══════════════════════════════════════════════════════════════════════
        
//         if (a != NULL)
//             a->next = c;
//         // ───────────────────────────────────────────────────────────────────────
//         // RECONNECTING THE LEFT SIDE
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // CONNECTING: Node before reversal zone → New head of reversed zone
//         //
//         // BEFORE:  ... -> a    c(reversed) -> ... -> b -> NULL
//         //                 X
//         //
//         // AFTER:   ... -> a -> c(reversed) -> ... -> b -> NULL
//         //                 └──────────┘
//         //              (reconnected!)
//         //
//         // WHY CHECK if (a != NULL)?
//         // ─────────────────────────
//         // If left = 1, there's no node before the reversal zone
//         // In that case:
//         // • 'a' is NULL
//         // • The reversed section starts at the HEAD of the list
//         // • No left connection needed!
//         // • We'll return 'c' as the new head instead of 'head'
//         //
//         // EXAMPLE: Reverse positions 1-3 in list 1->2->3->4->5
//         // ────────────────────────────────────────────────────
//         // a = NULL (no node at position 0)
//         // After reversal: 3 -> 2 -> 1 -> NULL
//         // c points to 3 (new head)
//         // We skip this connection (nothing to connect to left)
//         // Later, we return 'c' as the new head of entire list ✓
//         // ───────────────────────────────────────────────────────────────────────
        
//         b->next = d;
//         // ───────────────────────────────────────────────────────────────────────
//         // RECONNECTING THE RIGHT SIDE
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // CONNECTING: New tail of reversed zone → Node after reversal zone
//         //
//         // BEFORE:  ... -> a -> c(reversed) -> ... -> b    d -> ...
//         //                                            X
//         //
//         // AFTER:   ... -> a -> c(reversed) -> ... -> b -> d -> ...
//         //                                            └──────┘
//         //                                        (reconnected!)
//         //
//         // WHY NO CHECK for d != NULL?
//         // ───────────────────────────
//         // Even if d is NULL (reversing till end), b->next = NULL is correct!
//         // It properly terminates the list
//         //
//         // EXAMPLE: Reverse positions 2-5 in list 1->2->3->4->5
//         // ──────────────────────────────────────────────────
//         // d = NULL (no node at position 6)
//         // After reversal: 1 -> 5 -> 4 -> 3 -> 2 -> NULL
//         // b->next = NULL ✓ (correct termination)
//         //
//         // CRITICAL INSIGHT:
//         // ─────────────────
//         // After reversal, 'b' (which was the START of original reversal zone)
//         // is now the TAIL of the reversed section
//         // So connecting b->next = d is exactly what we need!
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 6: RETURN THE CORRECT HEAD
//         // ═══════════════════════════════════════════════════════════════════════
        
//         if(a != NULL) return head;
//         // ───────────────────────────────────────────────────────────────────────
//         // CASE 1: Reversal Started AFTER the First Node (left > 1)
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // CONDITION: a != NULL means left > 1
//         // This means we did NOT reverse from the head
//         // The original head is still the head of the entire list!
//         //
//         // EXAMPLE: List 1->2->3->4->5, reverse positions 2-4
//         // ────────────────────────────────────────────────────
//         // Original: 1 -> 2 -> 3 -> 4 -> 5
//         //           ↑
//         //         head (unchanged!)
//         //
//         // After:    1 -> 4 -> 3 -> 2 -> 5
//         //           ↑
//         //         head (still the first node!)
//         //
//         // 'a' = node 1 (not NULL)
//         // Return 'head' because the head hasn't changed ✓
//         // ───────────────────────────────────────────────────────────────────────
        
//         return c;
//         // ───────────────────────────────────────────────────────────────────────
//         // CASE 2: Reversal Started FROM the First Node (left = 1)
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // CONDITION: a == NULL means left = 1
//         // This means we reversed starting from the head
//         // The original head is now INSIDE the reversed section (at the tail!)
//         // The new head is 'c' (the last node of the reversed section)
//         //
//         // EXAMPLE: List 1->2->3->4->5, reverse positions 1-3
//         // ────────────────────────────────────────────────────
//         // Original: 1 -> 2 -> 3 -> 4 -> 5
//         //           ↑         ↑
//         //         head        c (before reversal)
//         //
//         // After:    3 -> 2 -> 1 -> 4 -> 5
//         //           ↑              ↑
//         //           c          old head (now in middle!)
//         //
//         // 'a' = NULL
//         // 'c' = node 3 (new head of entire list)
//         // Return 'c' because it's the new head ✓
//         //
//         // WHY 'c' AND NOT 'head'?
//         // ───────────────────────
//         // After reversal:
//         // • 'head' still points to node 1 (original first node)
//         // • But node 1 is no longer the first! It's now somewhere in the middle/end
//         // • 'c' points to the actual first node of the reversed section
//         // • Since we reversed from position 1, 'c' is the new head of entire list
//         //
//         // VISUAL:
//         // ───────
//         // head -> 1 (wrong! this is no longer the first node)
//         // c -> 3 (correct! this is now the first node)
//         // ───────────────────────────────────────────────────────────────────────
//     }
// };


// /*
// ╔════════════════════════════════════════════════════════════════════════════════╗
// ║                                                                                ║
// ║                    🎓 COMPREHENSIVE REVISION SUMMARY                           ║
// ║                   LEETCODE 92: REVERSE LINKED LIST II                          ║
// ║                                                                                ║
// ╚════════════════════════════════════════════════════════════════════════════════╝

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎯 PROBLEM UNDERSTANDING                                                      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// TASK: Reverse ONLY a portion of a linked list (from position left to right)

// INPUT:  head = 1 -> 2 -> 3 -> 4 -> 5, left = 2, right = 4
// OUTPUT: 1 -> 4 -> 3 -> 2 -> 5
//         └─┘  └────┬────┘  └─┘
//        same   reversed   same

// KEY CONSTRAINTS:
// • Positions are 1-indexed (not 0-indexed!)
// • 1 ≤ left ≤ right ≤ n
// • Must reverse in ONE PASS (optimal solution)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🧠 CORE ALGORITHM - "ISOLATE, REVERSE, RECONNECT"                             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🎯 THE BIG PICTURE - 6 STEPS                                  ║
// ╚═══════════════════════════════════════════════════════════════╝

// STEP 1: Base Case Check
// ├─ If left == right, no reversal needed → return head

// STEP 2: Find Four Critical Nodes
// ├─ a = node at position (left - 1)  [guard before reversal]
// ├─ b = node at position (left)      [start of reversal]
// ├─ c = node at position (right)     [end of reversal]
// └─ d = node at position (right + 1) [guard after reversal]

// STEP 3: Isolate the Sublist
// ├─ Break connection: a->next = NULL (if a exists)
// └─ Break connection: c->next = NULL

// STEP 4: Reverse the Isolated Sublist
// └─ c = reverseList(b)  [b...c becomes c...b]

// STEP 5: Reconnect
// ├─ Left connection:  a->next = c (if a exists)
// └─ Right connection: b->next = d

// STEP 6: Return Appropriate Head
// ├─ If a != NULL (left > 1): return original head
// └─ If a == NULL (left = 1): return c (new head)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎨 VISUAL WALKTHROUGH - COMPLETE EXAMPLE                                      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// INPUT: 1 -> 2 -> 3 -> 4 -> 5 -> NULL, left = 2, right = 4

// ┌─────────────────────────────────────────────────────────────┐
// │ INITIAL STATE                                               │
// └─────────────────────────────────────────────────────────────┘
// Position:  1    2    3    4    5
// List:      1 -> 2 -> 3 -> 4 -> 5 -> NULL
//            ↑
//          head


// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 2: FINDING THE FOUR NODES                             │
// └─────────────────────────────────────────────────────────────┘

// Position Counter (n): 1, 2, 3, 4, 5

// When n = 1 (temp = 1):
//   n == left-1 (2-1=1) ✓ → a = 1

// When n = 2 (temp = 2):
//   n == left (2) ✓ → b = 2

// When n = 4 (temp = 4):
//   n == right (4) ✓ → c = 4

// When n = 5 (temp = 5):
//   n == right+1 (4+1=5) ✓ → d = 5

// Result:
//   a = 1 (node before reversal)
//   b = 2 (start of reversal)
//   c = 4 (end of reversal)
//   d = 5 (node after reversal)

// Visual:
//      a    b         c    d
//      ↓    ↓         ↓    ↓
//      1 -> 2 -> 3 -> 4 -> 5 -> NULL
//           └────┬────┘
//         (to reverse)


// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 3: ISOLATING THE SUBLIST                              │
// └─────────────────────────────────────────────────────────────┘

// Action 1: a->next = NULL
// Before: 1 -> 2 -> 3 -> 4 -> 5
// After:  1    2 -> 3 -> 4 -> 5
//         ↑    ↑
//         a    b (now disconnected from a)

// Action 2: c->next = NULL
// Before: 1    2 -> 3 -> 4 -> 5
// After:  1    2 -> 3 -> 4    5
//         ↑    └────┬───┘     ↑
//         a     isolated      d

// Isolated sublist: b(2) -> 3 -> c(4) -> NULL


// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 4: REVERSING THE ISOLATED SUBLIST                     │
// └─────────────────────────────────────────────────────────────┘

// Input to reverseList: 2 -> 3 -> 4 -> NULL
//                       ↑         ↑
//                       b         c (before)

// Reversal Process:
//   Initial: 2 -> 3 -> 4 -> NULL
//   Step 1:  NULL <- 2    3 -> 4 -> NULL
//   Step 2:  NULL <- 2 <- 3    4 -> NULL
//   Step 3:  NULL <- 2 <- 3 <- 4

// Output: 4 -> 3 -> 2 -> NULL
//         ↑              ↑
//         c (new!)       b (same node, new position!)

// Note: Variable 'c' now points to 4 (new head of reversed section)
//       Variable 'b' still points to 2 (now tail of reversed section)


// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 5: RECONNECTING                                       │
// └─────────────────────────────────────────────────────────────┘

// Current State:
//   Part 1: a(1)    (disconnected)
//   Part 2: c(4) -> 3 -> b(2)    (reversed, disconnected)
//   Part 3: d(5) -> NULL    (disconnected)

// Action 1: a->next = c
//   Connects: 1 -> 4 -> 3 -> 2

// Action 2: b->next = d
//   Connects: 1 -> 4 -> 3 -> 2 -> 5 -> NULL

// Final State:
//      1 -> 4 -> 3 -> 2 -> 5 -> NULL
//      ↑    └────┬────┘
//    head    reversed


// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 6: RETURN THE HEAD                                    │
// └─────────────────────────────────────────────────────────────┘

// Check: a != NULL? YES (a = 1)
// Since left > 1, original head is still valid
// Return: head (which points to 1) ✓

// OUTPUT: 1 -> 4 -> 3 -> 2 -> 5 -> NULL ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🔍 CRITICAL EDGE CASES                                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ EDGE CASE 1: Reversing from Head (left = 1)                  ║
// ╚═══════════════════════════════════════════════════════════════╝

// Input: 1 -> 2 -> 3 -> 4 -> 5, left = 1, right = 3

// Finding Nodes:
//   a = NULL (no position 0)
//   b = 1
//   c = 3
//   d = 4

// Isolation:
//   Skip a->next = NULL (a is NULL)
//   c->next = NULL

// Reversal:
//   1 -> 2 -> 3 becomes 3 -> 2 -> 1

// Reconnection:
//   Skip a->next = c (a is NULL)
//   b->next = d → 1->next = 4

// Result: 3 -> 2 -> 1 -> 4 -> 5

// Return: c (since a is NULL) → Returns 3 as new head ✓


// ╔═══════════════════════════════════════════════════════════════╗
// ║ EDGE CASE 2: Reversing till End (right = n)                  ║
// ╚═══════════════════════════════════════════════════════════════╝

// Input: 1 -> 2 -> 3 -> 4 -> 5, left = 3, right = 5

// Finding Nodes:
//   a = 2
//   b = 3
//   c = 5
//   d = NULL (no position 6)

// Isolation & Reversal:
//   3 -> 4 -> 5 becomes 5 -> 4 -> 3

// Reconnection:
//   a->next = c → 2->next = 5
//   b->next = d → 3->next = NULL (proper termination!)

// Result: 1 -> 2 -> 5 -> 4 -> 3 -> NULL ✓


// ╔═══════════════════════════════════════════════════════════════╗
// ║ EDGE CASE 3: Reversing Entire List (left=1, right=n)         ║
// ╚═══════════════════════════════════════════════════════════════╝

// Input: 1 -> 2 -> 3, left = 1, right = 3

// Finding Nodes:
//   a = NULL, b = 1, c = 3, d = NULL

// Result: 3 -> 2 -> 1 -> NULL
// Return: c (new head) ✓


// ╔═══════════════════════════════════════════════════════════════╗
// ║ EDGE CASE 4: Single Node Reversal (left = right)             ║
// ╚═══════════════════════════════════════════════════════════════╝

// Input: 1 -> 2 -> 3, left = 2, right = 2

// Base case check: left == right → return head immediately
// No processing needed ✓


// ╔═══════════════════════════════════════════════════════════════╗
// ║ EDGE CASE 5: Two Consecutive Nodes                           ║
// ╚═══════════════════════════════════════════════════════════════╝

// Input: 1 -> 2 -> 3, left = 2, right = 3

// Finding Nodes:
//   a = 1, b = 2, c = 3, d = NULL

// Reversal: 2 -> 3 becomes 3 -> 2
// Result: 1 -> 3 -> 2 -> NULL ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎯 KEY INSIGHTS & "AHA!" MOMENTS                                              ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #1: The Four-Node Framework                       ║
// ╚═══════════════════════════════════════════════════════════════╝

// The key to solving this problem is identifying FOUR critical nodes:

//   ... -> a -> [b -> ... -> c] -> d -> ...
//          ↑    └─────┬─────┘     ↑
//       before    reverse       after

// This framework handles ALL cases, including edge cases!


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #2: Variable Reuse After Reversal                 ║
// ╚═══════════════════════════════════════════════════════════════╝

// After reversal, we REUSE variable 'c' cleverly:
// • Before: 'c' points to LAST node of reversal zone
// • After: 'c' points to FIRST node (new head) of reversed section
// • Meanwhile 'b' still points to same node (now tail)

// This dual-reference is PERFECT for reconnection!


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #3: NULL Checks Encode Edge Cases                 ║
// ╚═══════════════════════════════════════════════════════════════╝

// • a == NULL → Reversing from head (left = 1)
// • d == NULL → Reversing till end (right = n)

// By initializing to NULL and checking before use, we automatically
// handle edge cases without separate logic!


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #4: Isolation is Critical                         ║
// ╚═══════════════════════════════════════════════════════════════╝

// Setting c->next = NULL BEFORE reversal is crucial!
// Without it, reverseList would continue past 'c' and reverse
// more nodes than intended!


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⏱️ COMPLEXITY ANALYSIS                                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╭────────────────────────────────────────────────────────────────╮
// │  ⏱️ TIME COMPLEXITY: O(n)                                      │
// ╰────────────────────────────────────────────────────────────────╯

// BREAKDOWN:
// ──────────
// 1. Finding a, b, c, d:  O(n)
//    - Single traversal through entire list

// 2. Reversing sublist:   O(right - left + 1) ≈ O(n)
//    - In worst case, reverse entire list

// 3. Reconnecting:        O(1)
//    - Constant time pointer assignments

// TOTAL: O(n) + O(n) + O(1) = O(n)

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We traverse the list once to find critical nodes, then reverse
// a portion of it. In the worst case, we reverse the entire list.
// The time complexity is O(n) where n is the number of nodes."


// ╭────────────────────────────────────────────────────────────────╮
// │  💾 SPACE COMPLEXITY: O(1)                                     │
// ╰────────────────────────────────────────────────────────────────╯

// SPACE USED:
// ───────────
// • Four pointers (a, b, c, d): O(1)
// • reverseList uses three pointers (prev, curr, Next): O(1)
// • temp and n variables: O(1)

// Total: O(1) - Constant space!

// KEY POINTS:
// ───────────
// • No recursion (iterative reversal) → No call stack
// • No auxiliary data structures (arrays, hash maps)
// • In-place modification of existing list

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We use only a constant number of pointers regardless of input
// size. The reversal is done iteratively (not recursively), so
// there's no stack space overhead. We achieve O(1) space by
// modifying the list in-place."


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⚠️ COMMON MISTAKES & DEBUGGING TIPS                                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ❌ MISTAKE #1: Forgetting to Set c->next = NULL
// ───────────────────────────────────────────────
// Without: reverseList continues past 'c', reversing too much!
// Symptom: Entire list gets reversed or wrong nodes reversed
// Fix: ALWAYS set c->next = NULL before calling reverseList

// ❌ MISTAKE #2: Not Checking if a is NULL
// ────────────────────────────────────────
// Wrong: a->next = NULL without checking
// Result: NULL pointer dereference when left = 1!
// Fix: Always check if (a != NULL) before accessing a->next

// ❌ MISTAKE #3: Returning 'head' When left = 1
// ──────────────────────────────────────────────
// When reversing from head, 'head' is no longer the first node!
// Wrong: Always return head
// Correct: Return c when a == NULL, head otherwise

// ❌ MISTAKE #4: Wrong Position Comparisons
// ─────────────────────────────────────────
// Remember: Positions are 1-indexed!
// Wrong: if (n == left - 2) for node before reversal
// Correct: if (n == left - 1)

// ❌ MISTAKE #5: Confusing 'b' and 'c' After Reversal
// ───────────────────────────────────────────────────
// After c = reverseList(b):
// • 'c' points to NEW head (was last, now first)
// • 'b' points to SAME node (now last instead of first)
// Don't mix them up during reconnection!

// ❌ MISTAKE #6: Not Handling left == right
// ─────────────────────────────────────────
// Forgetting base case causes unnecessary work
// Fix: if (left == right) return head; at the start


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎤 INTERVIEW TALKING POINTS                                                   ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// OPENING:
// ────────
// "I'll solve this using the 'isolate-reverse-reconnect' approach.
// First, I'll identify four critical nodes that frame the reversal
// zone. Then I'll isolate that section, reverse it, and reconnect
// it back to the main list. This handles all edge cases elegantly."

// DURING CODING:
// ──────────────
// [Finding nodes] "I'm traversing once to find the four boundary
// nodes. This single pass makes the algorithm efficient..."

// [Isolation] "Now I'll break the connections to isolate the sublist.
// This ensures reverseList only affects the target section..."

// [Reversal] "The clever part: after reversal, variable 'c' points
// to the new head, while 'b' still points to what's now the tail.
// Perfect for reconnection..."

// [Reconnection] "I need to handle two cases: when we reverse from
// the head (a is NULL) versus when we don't..."

// AFTER CODING:
// ─────────────
// "The algorithm runs in O(n) time with a single traversal to find
// nodes, plus the reversal. Space is O(1) since we modify in-place.
// Let me trace through an example to verify..."

// FOLLOW-UP QUESTIONS:
// ────────────────────

// Q: "Can you do this in one pass?"
// A: "My solution already does! The finding phase is one pass, and
// the reversal is a pass over just the sublist. We can't do better
// than O(n) total since we must at least read every node once."

// Q: "What if you need to reverse multiple ranges?"
// A: "I'd call this function multiple times. For k ranges, it would
// be O(k*n) time. If ranges overlap, we'd need a different approach."

// Q: "How would you test this?"
// A: "I'd test: reversing from head (left=1), reversing to end
// (right=n), reversing entire list, single node reversal (left=right),
// and a standard middle range. Also test lists of length 1 and 2."


// ═══════════════════════════════════════════════════════════════════════════════

// 🎓 MEMORY TRICK - "THE SURGICAL EXTRACTION":

// Think of reversing a sublist like performing surgery:

// 1. LOCATE the operation site (find a, b, c, d)
// 2. CLAMP the blood vessels (break connections: a->next=NULL, c->next=NULL)
// 3. REMOVE the section (it's now isolated)
// 4. FLIP IT OVER (reverse it)
// 5. RECONNECT everything (a->next=c, b->next=d)
// 6. CHECK which end is up (return c if from head, else return head)

// Just like surgery, you need to be precise with each step!

// ═══════════════════════════════════════════════════════════════════════════════

// 📋 QUICK REFERENCE - THE FOUR NODES:

// a = (left - 1)  → "The guard before"     [may be NULL if left=1]
// b = (left)      → "Start of reversal"    [becomes tail after]
// c = (right)     → "End of reversal"      [becomes head after]
// d = (right + 1) → "The guard after"      [may be NULL if right=n]

// Connection Pattern:
//   BEFORE: a -> b -> ... -> c -> d
//   AFTER:  a -> c -> ... -> b -> d

// ═══════════════════════════════════════════════════════════════════════════════
// */