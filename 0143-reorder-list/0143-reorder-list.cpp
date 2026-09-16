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
        if (head == NULL || head->next == NULL)
            return head;
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newHead;
    }
    void reorderList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next != NULL && fast->next->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
        }
        // slow is at the left middle / middle

        ListNode* b = reverseList(slow->next);
        ListNode* a = head;
        slow->next = NULL; // for breaking the list
        // merge these two - a and b, alternatively
        ListNode* c = new ListNode(10);
        ListNode* tempC = c;
        ListNode* tempA = a;
        ListNode* tempB = b;
        while(tempA != NULL && tempB != NULL){   // while(tempA && tempB)
            tempC->next = tempA;
            tempA = tempA->next;
            tempC = tempC->next;

            tempC->next = tempB;
            tempB = tempB->next;
            tempC = tempC->next;
        }
        tempC->next = tempA;
        head = c->next;
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
//     // 🔧 HELPER FUNCTION: REVERSE LINKED LIST (RECURSIVE)
//     // ═══════════════════════════════════════════════════════════════════════════
    
//     ListNode* reverseList(ListNode* head) {
        
//         // ───────────────────────────────────────────────────────────────────────
//         // BASE CASE: Empty or Single Node
//         // ───────────────────────────────────────────────────────────────────────
//         if (head == NULL || head->next == NULL)
//             return head;
//         // Empty list or single node needs no reversal
//         // Also handles the recursion termination at the last node
        
//         // ───────────────────────────────────────────────────────────────────────
//         // RECURSIVE REVERSAL
//         // ───────────────────────────────────────────────────────────────────────
//         ListNode* newHead = reverseList(head->next);
//         // Recurse to the end, newHead will be the last node (new head)
        
//         head->next->next = head;
//         // Make the next node point back to current node (reverse the link)
        
//         head->next = NULL;
//         // Break the old forward link to prevent cycle
        
//         return newHead;
//         // Pass back the new head (unchanged through all recursive returns)
//     }
    
    
//     // ═══════════════════════════════════════════════════════════════════════════
//     // 🎯 MAIN FUNCTION: REORDER LIST
//     // ═══════════════════════════════════════════════════════════════════════════
//     // PROBLEM: LEETCODE 143 - REORDER LIST
//     // ═══════════════════════════════════════════════════════════════════════════
//     // Given: A linked list L₀ → L₁ → L₂ → ... → Lₙ₋₁ → Lₙ
//     // Task: Reorder it to: L₀ → Lₙ → L₁ → Lₙ₋₁ → L₂ → Lₙ₋₂ → ...
//     //
//     // VISUAL EXAMPLE:
//     // ───────────────
//     // Input:  1 -> 2 -> 3 -> 4 -> 5
//     // Output: 1 -> 5 -> 2 -> 4 -> 3
//     //         └─┬──┘    └─┬──┘    └─ (middle stays if odd length)
//     //       alternating pattern: first, last, second, second-last, etc.
//     //
//     // PATTERN: "Zipper Merge" - Like zipping two halves of a jacket together
//     // ═══════════════════════════════════════════════════════════════════════════
    
//     void reorderList(ListNode* head) {
        
//         // ───────────────────────────────────────────────────────────────────────
//         // 🎯 HIGH-LEVEL STRATEGY: "SPLIT, REVERSE, MERGE"
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // THE ALGORITHM (3 Main Steps):
//         // ─────────────────────────────
//         // STEP 1: Find the MIDDLE of the list (slow-fast pointers)
//         // STEP 2: SPLIT into two halves and REVERSE the second half
//         // STEP 3: MERGE the two halves in alternating fashion (zipper merge)
//         //
//         // WHY THIS WORKS:
//         // ───────────────
//         // To alternate between first and last elements, we need:
//         // 1. Access to beginning (easy - we have head)
//         // 2. Access to end (hard in singly linked list!)
//         //
//         // SOLUTION: Reverse second half!
//         // Now "end" elements are at the start of reversed second half
//         //
//         // VISUAL TRANSFORMATION:
//         // ──────────────────────
//         // Original:       1 -> 2 -> 3 -> 4 -> 5
//         //                 └──first─┘  └─second─┘
//         //
//         // After split:    1 -> 2 -> 3
//         //                 4 -> 5
//         //
//         // After reverse:  1 -> 2 -> 3
//         //                 5 -> 4
//         //
//         // After merge:    1 -> 5 -> 2 -> 4 -> 3 ✓
//         //                 ↑    ↑    ↑    ↑    ↑
//         //                 a    b    a    b    a (alternating!)
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 1: FIND THE MIDDLE OF THE LIST (Slow-Fast Pointer Technique)
//         // ═══════════════════════════════════════════════════════════════════════
        
//         ListNode* slow = head;  // Tortoise - moves 1 step at a time
//         ListNode* fast = head;  // Hare - moves 2 steps at a time
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THE SLOW-FAST RACE TO FIND MIDDLE
//         // ───────────────────────────────────────────────────────────────────────
//         while(fast->next != NULL && fast->next->next != NULL){
//             slow = slow->next;          // Slow moves 1 step
//             fast = fast->next->next;    // Fast moves 2 steps
//         }
        
//         // ───────────────────────────────────────────────────────────────────────
//         // WHY THIS LOOP CONDITION?
//         // ───────────────────────────────────────────────────────────────────────
//         // CONDITION: fast->next != NULL && fast->next->next != NULL
//         //
//         // This specific condition ensures 'slow' lands at the CORRECT position:
//         //
//         // ODD-length list (e.g., 1->2->3->4->5):
//         // ──────────────────────────────────────
//         // Start:     s,f
//         //            1 -> 2 -> 3 -> 4 -> 5
//         //
//         // Step 1:         s    f
//         //            1 -> 2 -> 3 -> 4 -> 5
//         //
//         // Step 2:              s         f
//         //            1 -> 2 -> 3 -> 4 -> 5
//         //
//         // Stop! fast->next->next is NULL
//         // slow is at 3 (TRUE MIDDLE) ✓
//         // First half: 1->2->3
//         // Second half: 4->5
//         //
//         // EVEN-length list (e.g., 1->2->3->4):
//         // ─────────────────────────────────────
//         // Start:     s,f
//         //            1 -> 2 -> 3 -> 4
//         //
//         // Step 1:         s    f
//         //            1 -> 2 -> 3 -> 4
//         //
//         // Stop! fast->next is NULL
//         // slow is at 2 (LEFT-MIDDLE) ✓
//         // First half: 1->2
//         // Second half: 3->4
//         //
//         // PERFECT SPLIT:
//         // ──────────────
//         // For ODD length (5 nodes): First half gets 3 nodes, second gets 2
//         // For EVEN length (4 nodes): First half gets 2 nodes, second gets 2
//         // This ensures first half is NEVER shorter than second half!
//         // ───────────────────────────────────────────────────────────────────────
        
//         // slow is at the left middle / middle
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 2a: REVERSE THE SECOND HALF
//         // ═══════════════════════════════════════════════════════════════════════
        
//         ListNode* b = reverseList(slow->next);
        
//         // ───────────────────────────────────────────────────────────────────────
//         // REVERSING THE SECOND HALF
//         // ───────────────────────────────────────────────────────────────────────
//         // slow->next is the START of the second half
//         // We reverse from there to the end
//         //
//         // EXAMPLE (List: 1->2->3->4->5, slow at 3):
//         // ─────────────────────────────────────────
//         // Before reverse:
//         //   First half: 1 -> 2 -> 3
//         //   Second half: 4 -> 5 (slow->next starts here)
//         //
//         // After reverse:
//         //   First half: 1 -> 2 -> 3 (unchanged)
//         //   Second half: 5 -> 4 (reversed!)
//         //   b points to 5 (new head of reversed second half)
//         //
//         // WHY REVERSE?
//         // ────────────
//         // To get alternating pattern, we need:
//         // - Elements from START of first half (easy: just traverse)
//         // - Elements from END of original list (hard!)
//         //
//         // By reversing second half, END elements are now at the START!
//         // So we can traverse both halves simultaneously from their starts
//         // ───────────────────────────────────────────────────────────────────────
        
//         ListNode* a = head;
//         // 'a' points to the START of first half
//         // We'll use 'a' and 'b' to traverse both halves simultaneously
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 2b: SPLIT THE LIST (CRITICAL!)
//         // ═══════════════════════════════════════════════════════════════════════
        
//         slow->next = NULL; // for breaking the list
        
//         // ───────────────────────────────────────────────────────────────────────
//         // WHY BREAK THE CONNECTION?
//         // ───────────────────────────────────────────────────────────────────────
//         // CRITICAL STEP: We MUST disconnect the two halves!
//         //
//         // BEFORE this line:
//         //   1 -> 2 -> 3 -> 4 -> 5 (still connected)
//         //         ↑         ↑
//         //       slow    slow->next
//         //
//         // AFTER this line:
//         //   1 -> 2 -> 3    5 -> 4
//         //         ↑    X   ↑
//         //       slow      b (disconnected!)
//         //
//         // WHY IS THIS NECESSARY?
//         // ──────────────────────
//         // 1. PREVENT CYCLE: Without this, the first half still connects to
//         //    the second half at position 4, but 4 is now in the MIDDLE of
//         //    the reversed second half! This creates unexpected connections.
//         //
//         // 2. CLEAN TERMINATION: After merging, we need to know when the
//         //    first half ends. Setting slow->next = NULL gives us a clear
//         //    endpoint.
//         //
//         // WHAT IF WE FORGET THIS LINE?
//         // ─────────────────────────────
//         // Example: 1->2->3->4->5 becomes 1->2->3->5->4
//         // Without breaking:
//         //   1->2->3->4 (original connection still exists)
//         //   But 4 now also connects to NULL (from reversal)
//         //   During merge, we might get: 1->5->2->4->3->4->... (cycle!)
//         //
//         // WITH breaking:
//         //   First half cleanly ends: 1->2->3->NULL
//         //   Second half: 5->4->NULL
//         //   Clean merge possible! ✓
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 3: MERGE THE TWO HALVES IN ALTERNATING FASHION (ZIPPER MERGE)
//         // ═══════════════════════════════════════════════════════════════════════
        
//         // ───────────────────────────────────────────────────────────────────────
//         // SETTING UP THE MERGE
//         // ───────────────────────────────────────────────────────────────────────
//         // We'll build a NEW list by alternating between 'a' and 'b'
//         // Using a DUMMY node to simplify the merge logic
//         // ───────────────────────────────────────────────────────────────────────
        
//         ListNode* c = new ListNode(10);
//         // Dummy node - placeholder to simplify insertion
//         // Value 10 is arbitrary (doesn't matter, we'll skip this node)
//         // Helps avoid NULL checks when building the merged list
        
//         ListNode* tempC = c;
//         // Pointer to build the merged list
//         // Think: "Construction worker building the new list"
        
//         ListNode* tempA = a;
//         // Pointer to traverse first half
//         // Think: "Reading from the first book"
        
//         ListNode* tempB = b;
//         // Pointer to traverse reversed second half
//         // Think: "Reading from the second book"
        
//         // ───────────────────────────────────────────────────────────────────────
//         // CURRENT STATE:
//         // ───────────────────────────────────────────────────────────────────────
//         // tempA → 1 -> 2 -> 3 -> NULL (first half)
//         // tempB → 5 -> 4 -> NULL (reversed second half)
//         // tempC → [dummy:10] -> NULL (merged list, empty)
//         //
//         // GOAL: Alternate between tempA and tempB
//         // Result should be: 1 -> 5 -> 2 -> 4 -> 3 -> NULL
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THE ZIPPER MERGE LOOP
//         // ───────────────────────────────────────────────────────────────────────
//         while(tempA != NULL && tempB != NULL){   // while(tempA && tempB)
            
//             // ───────────────────────────────────────────────────────────────────
//             // LOOP CONDITION: Continue while BOTH lists have nodes
//             // ───────────────────────────────────────────────────────────────────
//             // We stop when EITHER list runs out
//             // This handles the case where first half might have 1 extra node
//             // (in odd-length lists)
//             //
//             // WHY CHECK BOTH?
//             // ───────────────
//             // We need nodes from BOTH lists to continue alternating
//             // If either runs out, we can't continue the pattern
//             // ───────────────────────────────────────────────────────────────────
            
//             // ═══════════════════════════════════════════════════════════════════
//             // MERGE STEP 1: Take Node from First Half (tempA)
//             // ═══════════════════════════════════════════════════════════════════
//             tempC->next = tempA;
//             // ───────────────────────────────────────────────────────────────────
//             // ATTACHING NODE FROM 'a' LIST
//             // ───────────────────────────────────────────────────────────────────
//             // Connect current position in merged list to current node from 'a'
//             //
//             // EXAMPLE (First iteration):
//             // ──────────────────────────
//             // Before: [dummy] -> NULL,  tempA -> 1 -> 2 -> 3
//             // After:  [dummy] -> 1,     tempA -> 1 -> 2 -> 3
//             //
//             // We're REUSING the existing node from 'a', not creating new one!
//             // ───────────────────────────────────────────────────────────────────
            
//             tempA = tempA->next;
//             // ───────────────────────────────────────────────────────────────────
//             // ADVANCE POINTER IN 'a' LIST
//             // ───────────────────────────────────────────────────────────────────
//             // Move to the next node in first half for the next iteration
//             //
//             // EXAMPLE: tempA moves from 1 to 2
//             //
//             // WHY BEFORE moving tempC?
//             // ────────────────────────
//             // We need to save the next node in 'a' BEFORE we lose access to it
//             // Though in this case, it's okay either way since we're not breaking
//             // connections yet, it's good practice to save "next" references early
//             // ───────────────────────────────────────────────────────────────────
            
//             tempC = tempC->next;
//             // ───────────────────────────────────────────────────────────────────
//             // ADVANCE BUILDER POINTER
//             // ───────────────────────────────────────────────────────────────────
//             // Move to the node we just added, ready to append the next node
//             //
//             // EXAMPLE: tempC moves from [dummy] to 1
//             //
//             // Now tempC is at the "end" of our merged list (so far)
//             // Next insertion will happen after this node
//             // ───────────────────────────────────────────────────────────────────
            
//             // ───────────────────────────────────────────────────────────────────
//             // STATE AFTER FIRST MERGE STEP:
//             // ───────────────────────────────────────────────────────────────────
//             // Merged: [dummy] -> 1 -> (old connections still exist)
//             //                    ↑
//             //                  tempC
//             //
//             // First half: 2 -> 3 -> NULL
//             //             ↑
//             //           tempA
//             //
//             // Second half: 5 -> 4 -> NULL
//             //              ↑
//             //            tempB (unchanged so far)
//             // ───────────────────────────────────────────────────────────────────
            
            
//             // ═══════════════════════════════════════════════════════════════════
//             // MERGE STEP 2: Take Node from Second Half (tempB)
//             // ═══════════════════════════════════════════════════════════════════
//             tempC->next = tempB;
//             // ───────────────────────────────────────────────────────────────────
//             // ATTACHING NODE FROM 'b' LIST
//             // ───────────────────────────────────────────────────────────────────
//             // Connect current position in merged list to current node from 'b'
//             //
//             // EXAMPLE (First iteration):
//             // ──────────────────────────
//             // Before: [dummy] -> 1 -> (2,3...),  tempB -> 5 -> 4
//             // After:  [dummy] -> 1 -> 5,         tempB -> 5 -> 4
//             //
//             // Now we have: [dummy] -> 1 -> 5 -> ...
//             // The alternating pattern is taking shape! ✓
//             // ───────────────────────────────────────────────────────────────────
            
//             tempB = tempB->next;
//             // ───────────────────────────────────────────────────────────────────
//             // ADVANCE POINTER IN 'b' LIST
//             // ───────────────────────────────────────────────────────────────────
//             // Move to the next node in reversed second half
//             //
//             // EXAMPLE: tempB moves from 5 to 4
//             // ───────────────────────────────────────────────────────────────────
            
//             tempC = tempC->next;
//             // ───────────────────────────────────────────────────────────────────
//             // ADVANCE BUILDER POINTER
//             // ───────────────────────────────────────────────────────────────────
//             // Move to the node we just added
//             //
//             // EXAMPLE: tempC moves from 1 to 5
//             //
//             // Ready for next iteration!
//             // ───────────────────────────────────────────────────────────────────
            
//             // ───────────────────────────────────────────────────────────────────
//             // STATE AFTER FIRST COMPLETE ITERATION:
//             // ───────────────────────────────────────────────────────────────────
//             // Merged: [dummy] -> 1 -> 5 -> (will continue...)
//             //                         ↑
//             //                       tempC
//             //
//             // First half: 2 -> 3 -> NULL
//             //             ↑
//             //           tempA
//             //
//             // Second half: 4 -> NULL
//             //              ↑
//             //            tempB
//             //
//             // NEXT ITERATION WILL ADD:
//             // 2 (from tempA), then 4 (from tempB)
//             // Result: [dummy] -> 1 -> 5 -> 2 -> 4 -> ...
//             // ───────────────────────────────────────────────────────────────────
            
//             // ───────────────────────────────────────────────────────────────────
//             // COMPLETE ITERATION TRACE (1->2->3->4->5):
//             // ───────────────────────────────────────────────────────────────────
//             //
//             // Setup:
//             //   tempA: 1 -> 2 -> 3
//             //   tempB: 5 -> 4
//             //   tempC: [dummy]
//             //
//             // Iteration 1:
//             //   Add 1: [dummy] -> 1
//             //   Add 5: [dummy] -> 1 -> 5
//             //   tempA moves to 2, tempB moves to 4
//             //
//             // Iteration 2:
//             //   Add 2: [dummy] -> 1 -> 5 -> 2
//             //   Add 4: [dummy] -> 1 -> 5 -> 2 -> 4
//             //   tempA moves to 3, tempB moves to NULL
//             //
//             // Loop exits (tempB is NULL)
//             //
//             // Remaining: tempA still points to 3 (needs to be added!)
//             // ───────────────────────────────────────────────────────────────────
//         }
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 4: HANDLE REMAINING NODES (IF ANY)
//         // ═══════════════════════════════════════════════════════════════════════
        
//         tempC->next = tempA;
        
//         // ───────────────────────────────────────────────────────────────────────
//         // APPENDING LEFTOVER NODES
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // WHY THIS LINE?
//         // ──────────────
//         // When the loop exits, one of the lists has been exhausted:
//         // • If tempB became NULL first: tempA might still have node(s)
//         // • If tempA became NULL first: tempB would have node(s)
//         // • If both became NULL together: both are NULL
//         //
//         // By setting tempC->next = tempA, we handle TWO cases at once:
//         //
//         // CASE 1: tempA has remaining nodes (ODD-length list)
//         // ────────────────────────────────────────────────────
//         // Example: 1->2->3->4->5
//         // After loop: merged is 1->5->2->4, tempA points to 3
//         // This line: Attaches 3 to the end
//         // Result: 1->5->2->4->3 ✓
//         //
//         // CASE 2: tempA is NULL (EVEN-length list or both exhausted)
//         // ───────────────────────────────────────────────────────────
//         // Example: 1->2->3->4
//         // After loop: merged is 1->4->2->3, tempA is NULL
//         // This line: tempC->next = NULL (properly terminates!)
//         // Result: 1->4->2->3->NULL ✓
//         //
//         // WHY NOT CHECK tempB?
//         // ────────────────────
//         // Due to our split strategy:
//         // • First half is NEVER shorter than second half
//         // • For ODD length: first half has 1 extra node
//         // • For EVEN length: both halves are equal
//         //
//         // Therefore, tempB will NEVER have leftover nodes when tempA is exhausted
//         // Only tempA can have a leftover node (the middle one in odd-length lists)
//         //
//         // PROOF BY EXAMPLES:
//         // ──────────────────
//         // 5 nodes: Split as 3 + 2 → First half larger ✓
//         // 4 nodes: Split as 2 + 2 → Equal ✓
//         // 3 nodes: Split as 2 + 1 → First half larger ✓
//         // 2 nodes: Split as 1 + 1 → Equal ✓
//         // 1 node:  No second half → Trivial case ✓
//         //
//         // In ALL cases, first half ≥ second half!
//         // So only tempA needs to be appended
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 5: UPDATE head (IMPORTANT!)
//         // ═══════════════════════════════════════════════════════════════════════
        
//         head = c->next;
        
//         // ───────────────────────────────────────────────────────────────────────
//         // UPDATING THE HEAD REFERENCE
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // WHAT DOES THIS LINE DO?
//         // ───────────────────────
//         // c points to the DUMMY node [dummy:10]
//         // c->next points to the FIRST REAL node of the merged list
//         //
//         // Example: [dummy] -> 1 -> 5 -> 2 -> 4 -> 3
//         //           ↑        ↑
//         //           c      c->next
//         //
//         // We assign head = c->next to point head to the actual start (1)
//         //
//         // WHY IS THIS NECESSARY?
//         // ──────────────────────
//         // The function signature is: void reorderList(ListNode* head)
//         // 'head' is PASSED BY VALUE (it's a copy of the pointer!)
//         //
//         // CRITICAL UNDERSTANDING - POINTER PASS-BY-VALUE:
//         // ────────────────────────────────────────────────
//         // When you do: void reorderList(ListNode* head)
//         // You receive a COPY of the pointer, not the original pointer itself!
//         //
//         // VISUAL:
//         // ───────
//         // Caller has:    originalPtr → [1] -> [2] -> [3]
//         //                     ↓
//         // Function gets: head (copy) → [1] -> [2] -> [3]
//         //
//         // If we modify head (head = something), we ONLY change the local copy!
//         // The caller's originalPtr remains unchanged!
//         //
//         // WAIT - THEN WHY DOES THIS LINE EXIST?
//         // ──────────────────────────────────────
//         // This is a bit confusing, so let's clarify:
//         //
//         // ❌ MISCONCEPTION: "This line updates the caller's head pointer"
//         // ✓ REALITY: "This line is actually UNNECESSARY for the caller!"
//         //
//         // WHY IT SEEMS TO WORK:
//         // ─────────────────────
//         // The reordering happens BY MODIFYING THE NODES' NEXT POINTERS!
//         // We change: node1->next, node2->next, etc.
//         // These changes affect the ACTUAL NODES in memory, not just our pointer
//         //
//         // The CALLER'S head pointer STILL points to node 1
//         // And node 1's STRUCTURE has been modified in-place
//         // So traversing from the caller's head gives the reordered list!
//         //
//         // EXAMPLE:
//         // ────────
//         // Before: caller's head → 1 -> 2 -> 3 -> 4 -> 5
//         // We modify: 1->next to 5, 5->next to 2, etc.
//         // After: caller's head → 1 -> 5 -> 2 -> 4 -> 3
//         //        (head still points to 1, but 1's connections changed!)
//         //
//         // SO WHY WRITE head = c->next?
//         // ────────────────────────────
//         // 1. Good practice for local clarity
//         // 2. If we use 'head' later in the function, it's correct
//         // 3. Some might think it's needed (doesn't hurt to have it)
//         //
//         // ALTERNATIVE (if function returned ListNode*):
//         // ─────────────────────────────────────────────
//         // If signature was: ListNode* reorderList(ListNode* head)
//         // Then we'd RETURN c->next to give caller the new head
//         // But here it's void, so we rely on in-place modification
//         // ───────────────────────────────────────────────────────────────────────
        
//         // ───────────────────────────────────────────────────────────────────────
//         // FUNCTION COMPLETE!
//         // ───────────────────────────────────────────────────────────────────────
//         // The list has been reordered in-place
//         // Original: 1 -> 2 -> 3 -> 4 -> 5
//         // Result:   1 -> 5 -> 2 -> 4 -> 3
//         // The caller's head pointer still points to node 1, which now has
//         // the reordered structure ✓
//         // ───────────────────────────────────────────────────────────────────────
//     }
// };


// /*
// ╔════════════════════════════════════════════════════════════════════════════════╗
// ║                                                                                ║
// ║                    🎓 COMPREHENSIVE REVISION SUMMARY                           ║
// ║                      LEETCODE 143: REORDER LIST                                ║
// ║                                                                                ║
// ╚════════════════════════════════════════════════════════════════════════════════╝

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎯 PROBLEM UNDERSTANDING                                                      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// TASK: Reorder a linked list to alternate between start and end nodes

// PATTERN: L₀ → L₁ → L₂ → ... → Lₙ₋₁ → Lₙ
// BECOMES: L₀ → Lₙ → L₁ → Lₙ₋₁ → L₂ → Lₙ₋₂ → ...

// EXAMPLES:
// ─────────
// Input:  1 -> 2 -> 3 -> 4
// Output: 1 -> 4 -> 2 -> 3

// Input:  1 -> 2 -> 3 -> 4 -> 5
// Output: 1 -> 5 -> 2 -> 4 -> 3

// CONSTRAINT: Must do it IN-PLACE (O(1) extra space, ignoring recursion stack)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🧠 CORE ALGORITHM - "SPLIT, REVERSE, ZIPPER"                                  ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🎯 THE THREE-STEP STRATEGY                                    ║
// ╚═══════════════════════════════════════════════════════════════╝

// STEP 1: FIND MIDDLE (Slow-Fast Pointers)
// ├─ Use tortoise & hare to locate the middle
// └─ Split point: slow (left-middle for even, true middle for odd)

// STEP 2: SPLIT & REVERSE
// ├─ Break the list at middle: slow->next = NULL
// ├─ Reverse the second half
// └─ Now we have two lists: first half & reversed second half

// STEP 3: ZIPPER MERGE
// ├─ Alternate between first half and reversed second half
// └─ Pattern: take from first, take from second, repeat

// ANALOGY: "The Zipper Jacket"
// ─────────────────────────────
// Imagine a jacket with two sides:
// 1. Lay both sides flat (split the list)
// 2. Flip one side over (reverse second half)
// 3. Zip them together, alternating teeth (merge)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎨 COMPLETE VISUAL WALKTHROUGH                                                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// INPUT: 1 -> 2 -> 3 -> 4 -> 5

// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 1: FINDING THE MIDDLE                                 │
// └─────────────────────────────────────────────────────────────┘

// Initial:
//   slow, fast
//      ↓
//      1 -> 2 -> 3 -> 4 -> 5

// After Iteration 1:
//           slow   fast
//            ↓      ↓
//      1 -> 2 -> 3 -> 4 -> 5

// After Iteration 2:
//                slow        fast
//                 ↓           ↓
//      1 -> 2 -> 3 -> 4 -> 5

// STOP! (fast->next->next is NULL)
// slow is at 3 (middle) ✓


// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 2a: REVERSING SECOND HALF (slow->next onwards)        │
// └─────────────────────────────────────────────────────────────┘

// Second half before reverse: 4 -> 5 -> NULL

// Reversal process:
//   NULL <- 4    5 -> NULL
//   NULL <- 4 <- 5

// Second half after reverse: 5 -> 4 -> NULL
//                            ↑
//                            b (points here)


// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 2b: SPLITTING THE LIST                                │
// └─────────────────────────────────────────────────────────────┘

// Before split:
//   1 -> 2 -> 3 -> 4 -> 5
//             ↑
//           slow

// After slow->next = NULL:
//   1 -> 2 -> 3    5 -> 4
//             X    ↑
//          (cut!)  b

// Now we have TWO independent lists:
//   List A: 1 -> 2 -> 3 -> NULL
//   List B: 5 -> 4 -> NULL


// ┌─────────────────────────────────────────────────────────────┐
// │ STEP 3: ZIPPER MERGE                                       │
// └─────────────────────────────────────────────────────────────┘

// Setup:
//   tempA: 1 -> 2 -> 3 -> NULL
//   tempB: 5 -> 4 -> NULL
//   tempC: [dummy] -> NULL

// ═══════════════════════════════════════════════════════════════
// ITERATION 1:
// ═══════════════════════════════════════════════════════════════

// Take from A:
//   [dummy] -> 1
//   tempA moves to 2
//   tempC moves to 1

// Take from B:
//   [dummy] -> 1 -> 5
//   tempB moves to 4
//   tempC moves to 5

// State:
//   Merged: [dummy] -> 1 -> 5
//   tempA: 2 -> 3 -> NULL
//   tempB: 4 -> NULL

// ═══════════════════════════════════════════════════════════════
// ITERATION 2:
// ═══════════════════════════════════════════════════════════════

// Take from A:
//   [dummy] -> 1 -> 5 -> 2
//   tempA moves to 3
//   tempC moves to 2

// Take from B:
//   [dummy] -> 1 -> 5 -> 2 -> 4
//   tempB moves to NULL
//   tempC moves to 4

// State:
//   Merged: [dummy] -> 1 -> 5 -> 2 -> 4
//   tempA: 3 -> NULL
//   tempB: NULL

// Loop exits (tempB is NULL)

// ═══════════════════════════════════════════════════════════════
// APPENDING REMAINING:
// ═══════════════════════════════════════════════════════════════

// tempC->next = tempA
//   [dummy] -> 1 -> 5 -> 2 -> 4 -> 3 -> NULL

// Final merged list: 1 -> 5 -> 2 -> 4 -> 3 ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🔍 KEY INSIGHTS & "AHA!" MOMENTS                                              ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #1: Why Reverse the Second Half?                  ║
// ╚═══════════════════════════════════════════════════════════════╝

// PROBLEM: We need to access elements from the END of the list
// CHALLENGE: Singly linked lists can't traverse backward!

// SOLUTION: Reverse the second half!
// Now "end" elements are at the START of reversed second half

// Before reverse:
//   First:  1 -> 2 -> 3
//   Second: 4 -> 5

// After reverse:
//   First:  1 -> 2 -> 3
//   Second: 5 -> 4

// Now we can traverse BOTH from start and get alternating pattern!


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #2: Why slow->next = NULL is Critical             ║
// ╚═══════════════════════════════════════════════════════════════╝

// WITHOUT breaking:
//   Node 3 still points to node 4
//   But node 4 is now in MIDDLE of reversed second half!
//   This creates unwanted connections during merge

// WITH breaking:
//   First half cleanly ends: 1->2->3->NULL
//   Second half is independent: 5->4->NULL
//   Clean merge possible!


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #3: First Half is Always ≥ Second Half            ║
// ╚═══════════════════════════════════════════════════════════════╝

// Due to our middle-finding logic:
// • ODD length (5 nodes): Split as 3 + 2
// • EVEN length (4 nodes): Split as 2 + 2

// First half NEVER has fewer nodes than second half!
// This is why we only check tempC->next = tempA at the end
// (Only tempA can have leftovers, never tempB)


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #4: Dummy Node Simplifies Merge                   ║
// ╚═══════════════════════════════════════════════════════════════╝

// WITHOUT dummy:
//   Need special case for the first insertion
//   if (mergedList == NULL) mergedList = nodeA; else ...

// WITH dummy:
//   Uniform insertion logic throughout
//   Always: tempC->next = node; tempC = tempC->next;
//   Skip dummy at end: return c->next


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⏱️ COMPLEXITY ANALYSIS                                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╭────────────────────────────────────────────────────────────────╮
// │  ⏱️ TIME COMPLEXITY: O(n)                                      │
// ╰────────────────────────────────────────────────────────────────╯

// BREAKDOWN:
// ──────────
// 1. Finding middle:    O(n/2) ≈ O(n)
//    - Traverse half the list

// 2. Reversing second half: O(n/2) ≈ O(n)
//    - Reverse half the list

// 3. Merging:           O(n/2) ≈ O(n)
//    - Traverse both halves simultaneously

// TOTAL: O(n) + O(n) + O(n) = O(n)
//        (Constants dropped)

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We make three linear passes over portions of the list. Finding
// the middle takes n/2 steps, reversing takes n/2 steps, and merging
// takes n/2 steps. Altogether, this is O(n) time."


// ╭────────────────────────────────────────────────────────────────╮
// │  💾 SPACE COMPLEXITY: O(1) or O(n)                             │
// ╰────────────────────────────────────────────────────────────────╯

// TWO PERSPECTIVES:

// AUXILIARY SPACE (Ignoring recursion): O(1)
// ──────────────────────────────────────────
// • Fixed number of pointers (slow, fast, a, b, c, tempA, tempB, tempC)
// • No auxiliary data structures
// • In-place modification

// TOTAL SPACE (Including recursion): O(n)
// ───────────────────────────────────────
// • reverseList is RECURSIVE → call stack depth = n/2
// • In worst case, O(n) stack frames

// INTERVIEW EXPLANATION:
// ─────────────────────
// "The auxiliary space is O(1) - we only use a constant number of
// pointers. However, the reverseList function uses recursion, which
// adds O(n) space on the call stack. If we used iterative reversal,
// we could achieve O(1) total space complexity."

// FOLLOW-UP:
// ──────────
// Interviewer: "Can you make it truly O(1) space?"
// You: "Yes! Replace the recursive reverseList with the iterative
// three-pointer version. That eliminates the call stack overhead."


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🐛 EDGE CASES & HOW THEY'RE HANDLED                                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// EDGE CASE 1: Single Node
// ─────────────────────────
// Input: 1 -> NULL

// Middle finding: slow = 1, fast = 1 (loop doesn't execute)
// slow->next = NULL (already NULL, no issue)
// Reverse NULL → returns NULL
// Merge: tempB is NULL from start, loop doesn't execute
// tempC->next = tempA → appends node 1
// Result: 1 -> NULL ✓


// EDGE CASE 2: Two Nodes
// ──────────────────────
// Input: 1 -> 2 -> NULL

// Middle finding: slow = 1 (left-middle)
// Second half: 2
// Reverse: 2 -> NULL
// Merge: 1 -> 2
// Result: 1 -> 2 -> NULL (same as input) ✓


// EDGE CASE 3: Three Nodes
// ────────────────────────
// Input: 1 -> 2 -> 3 -> NULL

// Split: 1->2->NULL and 3->NULL
// Reverse second: 3->NULL (single node, unchanged)
// Merge: 1->3->2
// Result: 1 -> 3 -> 2 ✓


// EDGE CASE 4: Even Length (4 nodes)
// ───────────────────────────────────
// Input: 1 -> 2 -> 3 -> 4 -> NULL

// Split: 1->2->NULL and 3->4->NULL (equal halves)
// Reverse second: 4->3->NULL
// Merge: 1->4->2->3
// Result: 1 -> 4 -> 2 -> 3 ✓


// EDGE CASE 5: Odd Length (5 nodes)
// ──────────────────────────────────
// Input: 1 -> 2 -> 3 -> 4 -> 5 -> NULL

// Split: 1->2->3->NULL and 4->5->NULL
// Reverse second: 5->4->NULL
// Merge: 1->5->2->4, then append 3
// Result: 1 -> 5 -> 2 -> 4 -> 3 ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⚠️ COMMON MISTAKES & DEBUGGING TIPS                                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ❌ MISTAKE #1: Forgetting slow->next = NULL
// ───────────────────────────────────────────
// Symptom: Unexpected cycles or wrong connections
// Cause: First half still connected to second half
// Fix: ALWAYS break at slow->next = NULL before merge

// ❌ MISTAKE #2: Wrong Middle-Finding Condition
// ─────────────────────────────────────────────
// Wrong: while(fast && fast->next)
//   → slow ends up one position too far!

// Correct: while(fast->next && fast->next->next)
//   → slow at correct middle position

// ❌ MISTAKE #3: Not Handling Leftover Node
// ─────────────────────────────────────────
// Forgetting: tempC->next = tempA after loop
// Result: Middle node (in odd-length lists) gets lost!
// Fix: Always append remaining nodes

// ❌ MISTAKE #4: Modifying Wrong Pointers During Merge
// ────────────────────────────────────────────────────
// Wrong order:
//   tempA = tempA->next;
//   tempC->next = tempA;  ← Now points to wrong node!

// Correct order:
//   tempC->next = tempA;  ← Save current node
//   tempA = tempA->next;  ← Then advance

// ❌ MISTAKE #5: Thinking head = c->next Changes Caller's Pointer
// ───────────────────────────────────────────────────────────────
// Misconception: "This updates the original head"
// Reality: head is passed by value (copy of pointer)
//          Changes to head don't affect caller
//          The list is modified IN-PLACE via next pointers!


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎤 INTERVIEW TALKING POINTS                                                   ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// OPENING:
// ────────
// "I'll use a three-step approach to reorder the list. First, find
// the middle using slow-fast pointers. Second, split the list and
// reverse the second half. Third, merge both halves alternately,
// like zipping a zipper. This gives O(n) time and O(1) auxiliary space."

// DURING CODING:
// ──────────────
// [Finding middle] "Using the classic tortoise-hare technique..."

// [Splitting] "Critical step: I need to break the connection at the
// middle to create two independent lists..."

// [Reversing] "By reversing the second half, I can access 'end'
// elements from the start, enabling easy alternating..."

// [Merging] "Now I zipper-merge: take one from first half, one from
// second half, repeat..."

// AFTER CODING:
// ─────────────
// "The algorithm is O(n) time with three linear passes. Space is
// O(1) for auxiliary structures, though the recursive reversal adds
// O(n) stack space. Let me trace through a quick example..."

// FOLLOW-UP QUESTIONS:
// ────────────────────

// Q: "Can you do it without reversing?"
// A: "We'd need O(n) extra space (like a stack or array) to access
// end elements. Reversing allows us to maintain O(1) space."

// Q: "What if you need to preserve the original list?"
// A: "I'd need to create a new list, which would require O(n) space.
// The in-place constraint allows O(1) space optimization."

// Q: "How would you test this?"
// A: "I'd test: single node, two nodes, odd length (5), even length (4),
// verify alternating pattern, check for cycles (common bug!)."


// ═══════════════════════════════════════════════════════════════════════════════

// 🎓 MEMORY TRICK - "THE ZIPPER ANALOGY":

// Think of reordering like zipping a jacket:

// 1. FIND THE MIDDLE of the zipper (slow-fast pointers)
// 2. SEPARATE the two sides (split at middle)
// 3. FLIP ONE SIDE (reverse second half)
// 4. ZIP THEM TOGETHER (alternate: left tooth, right tooth, left, right...)
// 5. The odd tooth at the end (if any) gets appended last

// Just like a real zipper alternates sides!

// ═══════════════════════════════════════════════════════════════════════════════

// 📋 QUICK REFERENCE - THE THREE PHASES:

// PHASE 1: SPLIT
//   • Find middle: slow-fast pointers
//   • Break: slow->next = NULL

// PHASE 2: REVERSE
//   • Reverse second half: b = reverseList(slow->next)

// PHASE 3: MERGE
//   • Alternate: a, b, a, b, a, b, ...
//   • Append leftover: tempC->next = tempA

// ═══════════════════════════════════════════════════════════════════════════════
// */