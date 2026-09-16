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
        while(curr != NULL){
            Next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = Next;
        }
        return prev;
    }
    bool isPalindrome(ListNode* head) {
        // if the first half and second half are reverse of each other then it is palindrome
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next != NULL && fast->next->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
        }
        // slow is at the left middle / middle
        ListNode* newHead = reverseList(slow->next);
        ListNode* a = head;
        ListNode* b = newHead;
        while(b){
            if(a->val != b->val) return false;
            a = a->next;
            b = b->next;
        }
        return true;
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
//     ListNode* reverseList(ListNode* head) {
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THREE-POINTER TECHNIQUE for Reversing
//         // ───────────────────────────────────────────────────────────────────────
//         // Think of it like reversing arrows between people holding hands:
//         // A → B → C → D becomes A ← B ← C ← D
//         // We need to track: where we came from, where we are, where we're going
//         // ───────────────────────────────────────────────────────────────────────
        
//         ListNode* prev = NULL;     
//         // Points to the PREVIOUS node (starts as NULL - will be new tail)
//         // Think: "The person behind me in the original line"
        
//         ListNode* curr = head;     
//         // Points to the CURRENT node we're processing
//         // Think: "Me - the person I'm currently reversing"
        
//         ListNode* Next = head;     
//         // Points to the NEXT node (saves reference before we change curr->next)
//         // Think: "The person ahead of me - I need to remember them!"
//         // NOTE: Initialized to head, but will be updated in loop
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THE REVERSAL LOOP
//         // ───────────────────────────────────────────────────────────────────────
//         // VISUAL TRACE (List: 1 -> 2 -> 3 -> NULL):
//         //
//         // Initial:
//         //   prev = NULL, curr = 1, Next = 1
//         //   NULL    1 -> 2 -> 3 -> NULL
//         //    ↑      ↑
//         //   prev  curr/Next
//         // ───────────────────────────────────────────────────────────────────────
        
//         while(curr != NULL){
//             // Continue until we've processed all nodes
//             // When curr becomes NULL, we've finished reversing
            
//             Next = curr->next;          
//             // ───────────────────────────────────────────────────────────────────
//             // STEP 1: Save the Next Node BEFORE Breaking the Link
//             // ───────────────────────────────────────────────────────────────────
//             // CRITICAL! We're about to change curr->next, so we need to save
//             // where to go next, otherwise we LOSE the rest of the list!
//             //
//             // Example (curr = 1):
//             //   Next = 1->next = 2 (saved!)
//             //   Now we can safely modify 1->next
//             //
//             // ANALOGY: Taking a photo of the road ahead before turning around
//             // ───────────────────────────────────────────────────────────────────
            
//             curr->next = prev;          
//             // ───────────────────────────────────────────────────────────────────
//             // STEP 2: Reverse the Link (THE CORE REVERSAL!)
//             // ───────────────────────────────────────────────────────────────────
//             // Make current node point BACKWARDS to previous node
//             //
//             // Example (curr = 1, prev = NULL):
//             //   1->next = NULL (instead of pointing to 2)
//             //   Now: NULL <- 1    2 -> 3 -> NULL
//             //
//             // Example (curr = 2, prev = 1):
//             //   2->next = 1 (instead of pointing to 3)
//             //   Now: NULL <- 1 <- 2    3 -> NULL
//             //
//             // THINK: "I turn around and hold the hand of person behind me"
//             // ───────────────────────────────────────────────────────────────────
            
//             prev = curr;                
//             // ───────────────────────────────────────────────────────────────────
//             // STEP 3: Move prev Forward
//             // ───────────────────────────────────────────────────────────────────
//             // The current node becomes the new "previous" for next iteration
//             //
//             // Example: prev moves from NULL to 1, then to 2, then to 3
//             //
//             // THINK: "The person I just reversed becomes the 'previous' person
//             //         for the next reversal"
//             // ───────────────────────────────────────────────────────────────────
            
//             curr = Next;                
//             // ───────────────────────────────────────────────────────────────────
//             // STEP 4: Move curr Forward
//             // ───────────────────────────────────────────────────────────────────
//             // Move to the next node (which we saved earlier)
//             //
//             // Example: curr moves from 1 to 2, then to 3, then to NULL (exit)
//             //
//             // THINK: "I move forward to the next person in line"
//             // ───────────────────────────────────────────────────────────────────
//         }
        
//         // ───────────────────────────────────────────────────────────────────────
//         // AFTER THE LOOP:
//         // ───────────────────────────────────────────────────────────────────────
//         // curr = NULL (moved past the last node)
//         // prev = points to the LAST node of original list (now the FIRST node!)
//         //
//         // Final state for 1->2->3:
//         //   NULL <- 1 <- 2 <- 3    NULL
//         //                     ↑      ↑
//         //                   prev   curr
//         //
//         // prev is the new head of the reversed list!
//         // ───────────────────────────────────────────────────────────────────────
        
//         return prev;  
//         // Return the new head (which is the old tail)
//     }
    
    
//     // ═══════════════════════════════════════════════════════════════════════════
//     // 🎯 MAIN FUNCTION: CHECK IF LINKED LIST IS PALINDROME
//     // ═══════════════════════════════════════════════════════════════════════════
//     // PROBLEM: Determine if a linked list reads the same forwards and backwards
//     // Example: 1->2->2->1 is palindrome, 1->2->3 is not
//     // ═══════════════════════════════════════════════════════════════════════════
    
//     bool isPalindrome(ListNode* head) {
        
//         // ───────────────────────────────────────────────────────────────────────
//         // 💡 HIGH-LEVEL STRATEGY (THE "MIRROR CHECK" APPROACH)
//         // ───────────────────────────────────────────────────────────────────────
//         // INSIGHT: A palindrome is SYMMETRIC - first half mirrors second half
//         //
//         // ALGORITHM:
//         // 1. Find the MIDDLE of the list (using slow/fast pointers)
//         // 2. REVERSE the second half
//         // 3. COMPARE first half with reversed second half
//         // 4. If they match → palindrome! Otherwise → not palindrome
//         //
//         // VISUAL EXAMPLE (List: 1 -> 2 -> 3 -> 2 -> 1):
//         // ────────────────────────────────────────────
//         // Original:     1 -> 2 -> 3 -> 2 -> 1
//         //               └─first─┘   └─second─┘
//         //
//         // After finding middle (slow at 3):
//         //               1 -> 2 -> 3
//         //                         ↑
//         //                       slow
//         //
//         // Reverse second half (after slow):
//         //               1 -> 2 -> 3    1 <- 2
//         //               └─first─┘      └─reversed─┘
//         //
//         // Compare: 1==1 ✓, 2==2 ✓ → PALINDROME!
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 1: FIND THE MIDDLE OF THE LIST (SLOW-FAST POINTER TECHNIQUE)
//         // ═══════════════════════════════════════════════════════════════════════
        
//         ListNode* slow = head;  
//         // Slow pointer moves ONE step at a time
//         // Think: "Tortoise in the race"
        
//         ListNode* fast = head;  
//         // Fast pointer moves TWO steps at a time
//         // Think: "Hare in the race"
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THE SLOW-FAST POINTER PATTERN
//         // ───────────────────────────────────────────────────────────────────────
//         // CONCEPT: When fast reaches the end, slow is at the middle!
//         //
//         // WHY? Fast moves 2x speed, so covers 2x distance
//         // If fast traveled 10 nodes, slow traveled 5 nodes (middle!)
//         //
//         // VISUAL (ODD length: 1->2->3->4->5):
//         // ────────────────────────────────────
//         // Start:     s,f
//         //            1 -> 2 -> 3 -> 4 -> 5
//         //
//         // Step 1:         s    f
//         //            1 -> 2 -> 3 -> 4 -> 5
//         //
//         // Step 2:              s         f
//         //            1 -> 2 -> 3 -> 4 -> 5
//         //
//         // Stop: fast->next->next is NULL
//         // slow is at 3 (middle) ✓
//         //
//         // VISUAL (EVEN length: 1->2->3->4):
//         // ──────────────────────────────────
//         // Start:     s,f
//         //            1 -> 2 -> 3 -> 4
//         //
//         // Step 1:         s    f
//         //            1 -> 2 -> 3 -> 4
//         //
//         // Stop: fast->next is NULL
//         // slow is at 2 (left-middle) ✓
//         // ───────────────────────────────────────────────────────────────────────
        
//         while(fast->next != NULL && fast->next->next != NULL){
//             // ───────────────────────────────────────────────────────────────────
//             // LOOP CONDITION BREAKDOWN (Two Conditions - Both Important!)
//             // ───────────────────────────────────────────────────────────────────
//             //
//             // CONDITION 1: fast->next != NULL
//             // ────────────────────────────────
//             // Handles EVEN-length lists
//             // Prevents accessing NULL->next when fast is at the last node
//             //
//             // Example: 1->2->3->4
//             // When fast is at 4, fast->next is NULL → stop!
//             // (Otherwise fast->next->next would crash!)
//             //
//             // CONDITION 2: fast->next->next != NULL
//             // ──────────────────────────────────────
//             // Handles ODD-length lists
//             // Prevents fast from going past the end
//             //
//             // Example: 1->2->3->4->5
//             // When fast is at 4, fast->next is 5, fast->next->next is NULL → stop!
//             //
//             // WHY CHECK fast->next BEFORE fast->next->next?
//             // ─────────────────────────────────────────────
//             // SHORT-CIRCUIT EVALUATION!
//             // If fast->next is NULL, the second condition isn't even checked
//             // This prevents NULL pointer dereference
//             //
//             // ORDER MATTERS:
//             // ✓ Correct: fast->next != NULL && fast->next->next != NULL
//             // ✗ Wrong:   fast->next->next != NULL && fast->next != NULL
//             //            (Could check NULL->next if fast is at last node!)
//             // ───────────────────────────────────────────────────────────────────
            
//             slow = slow->next;          
//             // Move slow ONE step forward
//             // Think: Tortoise takes one step
            
//             fast = fast->next->next;    
//             // Move fast TWO steps forward
//             // Think: Hare takes two steps (jumps over one node)
//         }
        
//         // ───────────────────────────────────────────────────────────────────────
//         // AFTER THE LOOP - WHERE IS slow?
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // ODD-length list (e.g., 1->2->3->4->5):
//         // ──────────────────────────────────────
//         // slow points to MIDDLE element (3)
//         // We want to reverse AFTER the middle: 4->5
//         // So we reverse slow->next onwards
//         //
//         // EVEN-length list (e.g., 1->2->3->4):
//         // ─────────────────────────────────────
//         // slow points to LEFT-MIDDLE (2)
//         // We want to reverse second half: 3->4
//         // So we reverse slow->next onwards
//         //
//         // IN BOTH CASES: We reverse starting from slow->next
//         // ───────────────────────────────────────────────────────────────────────
        
//         // slow is at the left middle / middle
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 2: REVERSE THE SECOND HALF
//         // ═══════════════════════════════════════════════════════════════════════
        
//         ListNode* newHead = reverseList(slow->next);
//         // ───────────────────────────────────────────────────────────────────────
//         // REVERSING THE SECOND HALF
//         // ───────────────────────────────────────────────────────────────────────
//         // slow->next is the START of the second half
//         // We reverse from there to the end
//         // newHead will point to the LAST node (now first of reversed second half)
//         //
//         // EXAMPLE (List: 1->2->3->2->1):
//         // ──────────────────────────────
//         // After finding middle:
//         //   slow = 3
//         //   slow->next = first 2
//         //
//         // Reverse slow->next onwards (2->1):
//         //   Before: 2 -> 1 -> NULL
//         //   After:  1 -> 2 -> NULL
//         //   newHead = 1 (the last node, now first)
//         //
//         // Current state:
//         //   First half:  1 -> 2 -> 3 (unchanged)
//         //   Second half: 1 -> 2 -> NULL (reversed)
//         //
//         // WHY REVERSE?
//         // ────────────
//         // For palindrome check, we need to compare first half with second half
//         // But they go in opposite directions!
//         // Solution: Reverse second half so both go in same direction
//         //
//         // ALTERNATIVE (not used here):
//         // ────────────────────────────
//         // We could reverse first half instead - mathematically equivalent
//         // Or use a stack - but that's O(n) extra space
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 3: COMPARE FIRST HALF WITH REVERSED SECOND HALF
//         // ═══════════════════════════════════════════════════════════════════════
        
//         ListNode* a = head;      
//         // Pointer for first half (starts at beginning)
//         // Think: "Left hand reading the list from start"
        
//         ListNode* b = newHead;   
//         // Pointer for reversed second half (starts at reversed head)
//         // Think: "Right hand reading the reversed second half"
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THE COMPARISON LOOP - "MIRROR CHECK"
//         // ───────────────────────────────────────────────────────────────────────
//         // STRATEGY: Walk both halves simultaneously, comparing values
//         //
//         // EXAMPLE (Palindrome: 1->2->3->2->1):
//         // ────────────────────────────────────
//         // First half:   1 -> 2 -> 3
//         //               ↑
//         //               a
//         //
//         // Second half (reversed): 1 -> 2 -> NULL
//         //                         ↑
//         //                         b
//         //
//         // Iteration 1: a=1, b=1 → Match ✓ → Move both forward
//         // Iteration 2: a=2, b=2 → Match ✓ → Move both forward
//         // Iteration 3: b=NULL → Exit loop
//         // All matched → Return true (Palindrome!)
//         //
//         // EXAMPLE (NOT Palindrome: 1->2->3->4):
//         // ──────────────────────────────────────
//         // First half:   1 -> 2
//         // Second half (reversed): 4 -> 3
//         //
//         // Iteration 1: a=1, b=4 → MISMATCH ✗ → Return false
//         // ───────────────────────────────────────────────────────────────────────
        
//         while(b){
//             // ───────────────────────────────────────────────────────────────────
//             // WHY LOOP ON b (not a)?
//             // ───────────────────────────────────────────────────────────────────
//             // CRITICAL INSIGHT: Second half is always SHORTER or EQUAL to first half
//             //
//             // ODD-length list (e.g., 1->2->3->2->1):
//             // ──────────────────────────────────────
//             // First half: 1->2->3 (3 nodes)
//             // Second half: 2->1 (2 nodes)
//             // We only need to compare 2 nodes!
//             // The middle element (3) doesn't need comparison with anything
//             //
//             // EVEN-length list (e.g., 1->2->2->1):
//             // ─────────────────────────────────────
//             // First half: 1->2 (2 nodes)
//             // Second half: 2->1 (2 nodes)
//             // Compare all 2 nodes
//             //
//             // If we looped on 'a', we'd try to compare the middle element
//             // in odd-length lists, which has no counterpart!
//             //
//             // SAFETY: Since second half ≤ first half, 'a' won't become NULL
//             // before 'b' does, so a->val is always safe to access
//             // ───────────────────────────────────────────────────────────────────
            
//             if(a->val != b->val) return false;
//             // ───────────────────────────────────────────────────────────────────
//             // MISMATCH DETECTED - NOT A PALINDROME!
//             // ───────────────────────────────────────────────────────────────────
//             // If ANY pair doesn't match, the list can't be a palindrome
//             // We can immediately return false (early termination optimization)
//             //
//             // Example: 1->2->3->4
//             // First comparison: 1 != 4 → Return false immediately
//             // No need to check further!
//             // ───────────────────────────────────────────────────────────────────
            
//             a = a->next;  
//             // Move to next node in first half
            
//             b = b->next;  
//             // Move to next node in reversed second half
//         }
        
//         // ───────────────────────────────────────────────────────────────────────
//         // IF WE EXIT THE LOOP - ALL VALUES MATCHED!
//         // ───────────────────────────────────────────────────────────────────────
//         // We compared every node in the second half with corresponding node
//         // in the first half, and they all matched
//         // This means the list is a palindrome! ✓
//         // ───────────────────────────────────────────────────────────────────────
        
//         return true;  
//         // All comparisons passed → Palindrome confirmed!
//     }
// };


// /*
// ╔════════════════════════════════════════════════════════════════════════════════╗
// ║                                                                                ║
// ║                    🎓 COMPREHENSIVE REVISION SUMMARY                           ║
// ║                     LEETCODE 234: PALINDROME LINKED LIST                       ║
// ║                                                                                ║
// ╚════════════════════════════════════════════════════════════════════════════════╝

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎯 PROBLEM UNDERSTANDING                                                      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// DEFINITION: A palindrome reads the same forwards and backwards

// Examples:
// ✓ Palindromes:     1->2->2->1, 1->2->3->2->1, 5->5
// ✗ Not Palindromes: 1->2, 1->2->3, 1->2->3->4


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🧠 CORE ALGORITHM - THE "SPLIT & MIRROR" STRATEGY                             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🎯 HIGH-LEVEL APPROACH                                        ║
// ╚═══════════════════════════════════════════════════════════════╝

// STEP 1: Find the middle of the list (Slow-Fast pointers)
// STEP 2: Reverse the second half
// STEP 3: Compare first half with reversed second half
// STEP 4: If all match → Palindrome, else → Not palindrome

// ANALOGY: "The Folding Paper Test"
// ─────────────────────────────────
// Imagine writing numbers on a paper strip:
// 1. Find the middle and fold the paper
// 2. Flip one half over (reverse it)
// 3. Check if numbers align perfectly
// 4. If they do → Palindrome!


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎨 VISUAL WALKTHROUGH - COMPLETE EXAMPLE                                      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// Example: 1 -> 2 -> 3 -> 2 -> 1 -> NULL (ODD-length palindrome)

// ┌─────────────────────────────────────────────────────────────┐
// │ PHASE 1: FINDING THE MIDDLE (Slow-Fast Pointers)           │
// └─────────────────────────────────────────────────────────────┘

// Initial State:
//   slow, fast
//      ↓
//      1 -> 2 -> 3 -> 2 -> 1 -> NULL

// After Step 1: (slow moves 1, fast moves 2)
//           slow   fast
//            ↓      ↓
//      1 -> 2 -> 3 -> 2 -> 1 -> NULL

// After Step 2: (slow moves 1, fast moves 2)
//                slow        fast
//                 ↓           ↓
//      1 -> 2 -> 3 -> 2 -> 1 -> NULL

// Stop! (fast->next->next is NULL)
// slow is at 3 (the middle) ✓


// ┌─────────────────────────────────────────────────────────────┐
// │ PHASE 2: REVERSING SECOND HALF (slow->next onwards)        │
// └─────────────────────────────────────────────────────────────┘

// Before Reversal:
//   First half:  1 -> 2 -> 3
//   Second half: 2 -> 1 -> NULL
//                     (from slow->next)

// After Reversal:
//   First half:  1 -> 2 -> 3 (unchanged)
//   Second half: 1 -> 2 -> NULL (reversed!)
//                ↑
//             newHead

// State:
//      1 -> 2 -> 3    (original list, but 3's next is modified)
     
//      1 -> 2 -> NULL (reversed second half)
//      ↑
//   newHead


// ┌─────────────────────────────────────────────────────────────┐
// │ PHASE 3: COMPARING BOTH HALVES                             │
// └─────────────────────────────────────────────────────────────┘

// Setup:
//   a = head (1)
//   b = newHead (1)

// Iteration 1:
//   a points to 1 (first half)
//   b points to 1 (reversed second half)
//   1 == 1 ✓ → Continue

// Iteration 2:
//   a points to 2 (first half)
//   b points to 2 (reversed second half)
//   2 == 2 ✓ → Continue

// Iteration 3:
//   b is NULL → Exit loop

// All matched → Return TRUE ✓


// ═══════════════════════════════════════════════════════════════
// EXAMPLE 2: 1 -> 2 -> 3 -> 4 -> NULL (EVEN-length, NOT palindrome)
// ═══════════════════════════════════════════════════════════════

// Finding Middle:
//   slow ends at 2 (left-middle)

// Reversing Second Half:
//   First half:  1 -> 2
//   Second half (reversed): 4 -> 3 -> NULL

// Comparison:
//   a=1, b=4 → 1 != 4 ✗ → Return FALSE immediately


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🔍 KEY PATTERNS & TECHNIQUES USED                                             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🎯 PATTERN #1: SLOW-FAST POINTER (Floyd's Tortoise & Hare)   ║
// ╚═══════════════════════════════════════════════════════════════╝

// PURPOSE: Find the middle of a linked list in ONE pass

// MECHANISM:
//   • Slow pointer: moves 1 step at a time
//   • Fast pointer: moves 2 steps at a time
//   • When fast reaches end, slow is at middle

// CONDITION: while(fast->next != NULL && fast->next->next != NULL)
//   • Handles both ODD and EVEN length lists
//   • Prevents NULL pointer errors

// APPLICATIONS:
//   ✓ Finding middle of linked list
//   ✓ Detecting cycles in linked list
//   ✓ Finding the start of a cycle
//   ✓ Finding kth node from end


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🎯 PATTERN #2: THREE-POINTER REVERSAL                        ║
// ╚═══════════════════════════════════════════════════════════════╝

// PURPOSE: Reverse a linked list in-place

// THREE POINTERS:
//   • prev: The node behind (where we came from)
//   • curr: The node we're currently processing
//   • Next: The node ahead (where we're going)

// STEPS (for each node):
//   1. Save Next (curr->next) before breaking link
//   2. Reverse link (curr->next = prev)
//   3. Move prev forward (prev = curr)
//   4. Move curr forward (curr = Next)

// APPLICATIONS:
//   ✓ Reverse entire list
//   ✓ Reverse sublist
//   ✓ Reverse in k-groups
//   ✓ Palindrome checking (this problem!)


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🎯 PATTERN #3: DIVIDE & CONQUER ON LINKED LIST               ║
// ╚═══════════════════════════════════════════════════════════════╝

// CONCEPT: Split problem into smaller subproblems

// HERE:
//   • Split list into two halves
//   • Process second half (reverse it)
//   • Combine (compare both halves)

// SIMILAR PROBLEMS:
//   ✓ Merge sort on linked list
//   ✓ Reorder list
//   ✓ Sort list


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⏱️ COMPLEXITY ANALYSIS                                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╭────────────────────────────────────────────────────────────────╮
// │  ⏱️ TIME COMPLEXITY: O(n)                                      │
// ╰────────────────────────────────────────────────────────────────╯

// BREAKDOWN:
// ──────────
// 1. Finding middle:     O(n/2) ≈ O(n)
//    - Traverse half the list with slow pointer

// 2. Reversing second half: O(n/2) ≈ O(n)
//    - Reverse half the list

// 3. Comparing:          O(n/2) ≈ O(n)
//    - Compare half the list

// TOTAL: O(n) + O(n) + O(n) = O(n)
//        (Constants dropped in Big-O notation)

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We make three passes over the list, but each pass only covers
// half the list or less. Since we drop constants in Big-O, the
// time complexity is O(n) where n is the number of nodes."


// ╭────────────────────────────────────────────────────────────────╮
// │  💾 SPACE COMPLEXITY: O(1)                                     │
// ╰────────────────────────────────────────────────────────────────╯

// SPACE USED:
// ───────────
// • slow, fast pointers: O(1)
// • prev, curr, Next pointers: O(1)
// • a, b pointers: O(1)
// • newHead pointer: O(1)

// Total: O(1) - Constant space!

// KEY INSIGHT:
// ────────────
// We DON'T use recursion (no call stack)
// We DON'T create new nodes (modify in-place)
// We DON'T use arrays or hash tables

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We only use a constant number of pointers regardless of input
// size. The reverseList function is iterative (not recursive), so
// there's no call stack overhead. We modify the list in-place
// without creating new data structures, achieving O(1) space."


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🐛 CRITICAL EDGE CASES                                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// EDGE CASE 1: Empty List
// ───────────────────────
// Input: NULL
// Issue: fast->next would crash!
// BUT: Problem constraints usually guarantee at least 1 node
// If needed, add: if (!head) return true;

// EDGE CASE 2: Single Node
// ────────────────────────
// Input: 5 -> NULL
// Fast-slow: Loop doesn't execute (fast->next is NULL)
// slow = 5, slow->next = NULL
// Reverse NULL → returns NULL
// Compare loop doesn't execute (b is NULL)
// Return: true ✓ (Correct: single node is palindrome)

// EDGE CASE 3: Two Nodes (Palindrome)
// ───────────────────────────────────
// Input: 1 -> 1 -> NULL
// Fast-slow: Loop doesn't execute
// slow = 1 (first node)
// Reverse second half (second 1) → returns second 1
// Compare: 1 == 1 ✓
// Return: true ✓

// EDGE CASE 4: Two Nodes (Not Palindrome)
// ───────────────────────────────────────
// Input: 1 -> 2 -> NULL
// Compare: 1 != 2 ✗
// Return: false ✓

// EDGE CASE 5: All Same Values
// ────────────────────────────
// Input: 3 -> 3 -> 3 -> 3 -> NULL
// All comparisons match
// Return: true ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⚠️ COMMON MISTAKES & HOW TO AVOID THEM                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ❌ MISTAKE #1: Wrong Slow-Fast Condition
// ────────────────────────────────────────
// Wrong: while(fast != NULL && fast->next != NULL)
//   → This puts slow one position too far!

// Correct: while(fast->next != NULL && fast->next->next != NULL)
//   → This gives us the correct middle

// ❌ MISTAKE #2: Reversing from slow instead of slow->next
// ────────────────────────────────────────────────────────
// Wrong: reverseList(slow)
//   → Reverses too much, including the middle!

// Correct: reverseList(slow->next)
//   → Only reverses the second half

// ❌ MISTAKE #3: Looping on 'a' instead of 'b' in comparison
// ──────────────────────────────────────────────────────────
// Wrong: while(a)
//   → In odd-length lists, tries to compare middle element
//   → Middle has no counterpart!

// Correct: while(b)
//   → Only compares the shorter half (correct!)

// ❌ MISTAKE #4: Not Saving Next before Reversing
// ───────────────────────────────────────────────
// Wrong:
//   curr->next = prev;
//   Next = curr->next;  ← This is now prev, not the original next!

// Correct:
//   Next = curr->next;  ← Save BEFORE modifying
//   curr->next = prev;

// ❌ MISTAKE #5: Checking fast instead of fast->next
// ──────────────────────────────────────────────────
// Wrong: while(fast->next->next != NULL)
//   → Crashes when fast is at last node (fast->next->next on NULL!)

// Correct: while(fast->next != NULL && fast->next->next != NULL)
//   → Short-circuit evaluation prevents crash


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎤 INTERVIEW TALKING POINTS                                                   ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// OPENING:
// ────────
// "To check if a linked list is a palindrome, I'll use a three-step
// approach: find the middle using slow-fast pointers, reverse the
// second half, then compare both halves. This gives us O(n) time
// and O(1) space."

// DURING CODING:
// ──────────────
// [Finding middle] "I'm using the slow-fast pointer technique to find
// the middle in one pass..."

// [Reversing] "Now I'll reverse the second half using the three-pointer
// iterative approach..."

// [Comparing] "Finally, I compare both halves. If any mismatch occurs,
// it's not a palindrome..."

// AFTER CODING:
// ─────────────
// "The algorithm is O(n) time because we make three linear passes.
// It's O(1) space because we only use a few pointers and modify the
// list in-place. Let me trace through a quick example..."

// FOLLOW-UP QUESTIONS:
// ────────────────────

// Q: "Does this modify the original list?"
// A: "Yes, the second half gets reversed. If we need to preserve the
// original, we could reverse the second half back after comparison,
// still maintaining O(1) space."

// Q: "Could you use extra space to make it simpler?"
// A: "Yes! We could push all values to a stack (or array), then compare
// with the list. But that would be O(n) space instead of O(1)."

// Q: "What if the list is doubly-linked?"
// A: "We could traverse from both ends simultaneously, comparing
// values as we go. No need to reverse anything!"


// ═══════════════════════════════════════════════════════════════════════════════

// 🎓 MEMORY TRICK - "THE MIRROR FOLD":

// Imagine the list is written on paper:
// 1. FOLD the paper at the middle (find middle with slow-fast)
// 2. FLIP one half over (reverse second half)
// 3. SHINE A LIGHT through - do the numbers align? (compare)
// 4. If yes → PALINDROME! If no → NOT PALINDROME!

// ═══════════════════════════════════════════════════════════════════════════════
// */