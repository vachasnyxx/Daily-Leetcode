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
    ListNode* oddEvenList(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        ListNode* odd = head;
        ListNode* even = head->next;

        ListNode* evenStart = head->next;

        while(even != NULL && even->next != NULL){ // while(even)
            odd->next = even->next;
            even->next = even->next->next;
            
            odd = odd->next;
            even = even->next;
        }
        odd->next = evenStart;
        return head;
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
//     // 🎯 PROBLEM: LEETCODE 328 - ODD EVEN LINKED LIST
//     // ═══════════════════════════════════════════════════════════════════════════
//     // Given: A singly linked list
//     // Task: Group all ODD-indexed nodes together, followed by EVEN-indexed nodes
//     //       (Indices are 1-based: first node is index 1, second is index 2, etc.)
//     //
//     // IMPORTANT: "Odd/Even" refers to NODE POSITION, NOT node VALUES!
//     //
//     // VISUAL EXAMPLE:
//     // ───────────────
//     // Input:  1 -> 2 -> 3 -> 4 -> 5 -> NULL
//     //         ↑    ↑    ↑    ↑    ↑
//     //        odd  even odd  even odd  (positions)
//     //
//     // Output: 1 -> 3 -> 5 -> 2 -> 4 -> NULL
//     //         └─ odd ──┘  └─ even ─┘
//     //         (odd positions first, then even positions)
//     //
//     // CONSTRAINTS:
//     // • The relative order inside both odd and even groups should remain as it was
//     // • Must solve in O(1) space (in-place) and O(n) time
//     // • First node is considered odd (index 1), second is even (index 2), etc.
//     // ═══════════════════════════════════════════════════════════════════════════
    
//     ListNode* oddEvenList(ListNode* head) {
        
//         // ───────────────────────────────────────────────────────────────────────
//         // 🎯 HIGH-LEVEL STRATEGY: "TWO-LIST SEGREGATION WITH SMART REWIRING"
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // CORE INSIGHT:
//         // ─────────────
//         // Instead of creating separate lists from scratch, we'll REWIRE the
//         // existing list by making odd nodes skip even nodes, and vice versa!
//         //
//         // ALGORITHM:
//         // ──────────
//         // STEP 1: Handle edge cases (empty or single node)
//         // STEP 2: Initialize two pointers (odd starts at 1st, even at 2nd)
//         // STEP 3: Save the start of even list (for later connection)
//         // STEP 4: Traverse and rewire: odd nodes → skip even, even nodes → skip odd
//         // STEP 5: Connect odd list's tail to even list's head
//         // STEP 6: Return original head (which is still the first odd node)
//         //
//         // VISUAL TRANSFORMATION:
//         // ──────────────────────
//         // Original:  1 -> 2 -> 3 -> 4 -> 5 -> NULL
//         //            ↑    ↑
//         //          odd  even
//         //
//         // After rewiring odd:
//         //            1 ─────> 3 ─────> 5
//         //               2 -> 3 -> 4 -> 5 (even connections still intact)
//         //
//         // After rewiring even:
//         //            1 ─────> 3 ─────> 5
//         //               2 ─────> 4
//         //
//         // After connecting:
//         //            1 -> 3 -> 5 -> 2 -> 4 -> NULL ✓
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 1: BASE CASES - Handle Trivial Cases
//         // ═══════════════════════════════════════════════════════════════════════
//         if(head == NULL || head->next == NULL) return head;
        
//         // ───────────────────────────────────────────────────────────────────────
//         // BASE CASE HANDLING
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // CASE 1: head == NULL (Empty list)
//         // ──────────────────────────────────
//         // No nodes to rearrange → return NULL
//         //
//         // CASE 2: head->next == NULL (Single node)
//         // ─────────────────────────────────────────
//         // Only one node (odd position) → already in correct order
//         // Example: 5 -> NULL
//         // Output: 5 -> NULL (no change needed)
//         //
//         // WHY CHECK BOTH?
//         // ───────────────
//         // Prevents accessing NULL pointers in the code below
//         // Without this check, even = head->next would crash if head is NULL
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 2: INITIALIZE POINTERS
//         // ═══════════════════════════════════════════════════════════════════════
        
//         ListNode* odd = head;
//         // ───────────────────────────────────────────────────────────────────────
//         // ODD POINTER - Tracks Odd-Positioned Nodes
//         // ───────────────────────────────────────────────────────────────────────
//         // Starts at the FIRST node (index 1, which is odd)
//         // This pointer will traverse: 1 -> 3 -> 5 -> 7 -> ...
//         //
//         // PURPOSE:
//         // ────────
//         // We'll use this to build the "odd chain" by skipping even nodes
//         //
//         // THINK OF IT AS:
//         // ───────────────
//         // A worker walking through odd positions, connecting them directly
//         // ───────────────────────────────────────────────────────────────────────
        
//         ListNode* even = head->next;
//         // ───────────────────────────────────────────────────────────────────────
//         // EVEN POINTER - Tracks Even-Positioned Nodes
//         // ───────────────────────────────────────────────────────────────────────
//         // Starts at the SECOND node (index 2, which is even)
//         // This pointer will traverse: 2 -> 4 -> 6 -> 8 -> ...
//         //
//         // PURPOSE:
//         // ────────
//         // We'll use this to build the "even chain" by skipping odd nodes
//         //
//         // THINK OF IT AS:
//         // ───────────────
//         // Another worker walking through even positions, connecting them directly
//         // ───────────────────────────────────────────────────────────────────────
        
//         ListNode* evenStart = head->next;
//         // ───────────────────────────────────────────────────────────────────────
//         // EVEN START MARKER - Remembers Where Even List Begins
//         // ───────────────────────────────────────────────────────────────────────
//         // CRITICAL: We need to remember where the even list STARTS!
//         //
//         // WHY?
//         // ────
//         // At the end, we need to connect the odd list to the even list
//         // After all the rewiring, we'll lose track of where even list begins
//         // This variable SAVES that reference
//         //
//         // EXAMPLE:
//         // ────────
//         // List: 1 -> 2 -> 3 -> 4 -> 5
//         //            ↑
//         //       evenStart (points to 2)
//         //
//         // After rewiring, 'even' pointer might be at 4 or NULL
//         // But evenStart still points to 2 (the beginning of even list)
//         // So we can do: odd->next = evenStart (connecting 5 to 2)
//         //
//         // ANALOGY:
//         // ────────
//         // Like placing a bookmark at the start of Chapter 2 before rearranging
//         // the book's pages - we need to know where Chapter 2 starts later!
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 3: THE REWIRING LOOP - Building Odd and Even Chains
//         // ═══════════════════════════════════════════════════════════════════════
        
//         while(even != NULL && even->next != NULL){ // while(even)
            
//             // ───────────────────────────────────────────────────────────────────
//             // LOOP CONDITION EXPLAINED
//             // ───────────────────────────────────────────────────────────────────
//             //
//             // WHY even != NULL && even->next != NULL?
//             // ────────────────────────────────────────
//             //
//             // REASONING:
//             // ──────────
//             // 'even' pointer ALWAYS moves faster or equal to 'odd' pointer
//             // This is because:
//             // • odd starts at position 1, even starts at position 2
//             // • Both move forward by 2 positions each iteration
//             // • even is always 1 position ahead or becomes NULL first
//             //
//             // So if 'even' still has nodes, 'odd' definitely has nodes!
//             // We only need to check 'even' for termination
//             //
//             // TWO CONDITIONS:
//             // ───────────────
//             //
//             // CONDITION 1: even != NULL
//             // ──────────────────────────
//             // Ensures 'even' pointer itself is valid
//             // Prevents: even->next access on NULL
//             //
//             // Example (EVEN length: 1->2->3->4):
//             // After last iteration, even points to 4, even->next is NULL
//             // Condition fails → loop exits ✓
//             //
//             // CONDITION 2: even->next != NULL
//             // ────────────────────────────────
//             // Ensures there's a next odd node to connect to
//             // Prevents: even->next->next access on NULL
//             //
//             // Example (ODD length: 1->2->3->4->5):
//             // When even points to 4, even->next is 5, even->next->next is NULL
//             // We need to rewire once more (odd 3 → 5, even 4 → NULL)
//             // After that, even becomes NULL → loop exits ✓
//             //
//             // WHY NOT just while(even)?
//             // ─────────────────────────
//             // If we only check 'even', we might try even->next->next when
//             // even->next is NULL, causing a crash!
//             //
//             // TRACE EXAMPLES:
//             // ───────────────
//             //
//             // ODD length (1->2->3->4->5):
//             // ───────────────────────────
//             // Iter 1: even=2, even->next=3 ✓ → Continue
//             // Iter 2: even=4, even->next=5 ✓ → Continue
//             // Iter 3: even=NULL → Exit ✓
//             //
//             // EVEN length (1->2->3->4):
//             // ──────────────────────────
//             // Iter 1: even=2, even->next=3 ✓ → Continue
//             // Iter 2: even=4, even->next=NULL ✗ → Exit ✓
//             // ───────────────────────────────────────────────────────────────────
            
            
//             // ═══════════════════════════════════════════════════════════════════
//             // REWIRING STEP 1: Connect Current Odd to Next Odd
//             // ═══════════════════════════════════════════════════════════════════
//             odd->next = even->next;
            
//             // ───────────────────────────────────────────────────────────────────
//             // ODD NODE REWIRING
//             // ───────────────────────────────────────────────────────────────────
//             //
//             // WHAT THIS DOES:
//             // ───────────────
//             // Make current odd node SKIP the even node and point to next odd node
//             //
//             // VISUAL EXAMPLE (First iteration):
//             // ──────────────────────────────────
//             // Before:  1 -> 2 -> 3 -> 4 -> 5
//             //          ↑    ↑    ↑
//             //         odd  even even->next
//             //
//             // Action: odd->next = even->next (1->next = 3)
//             //
//             // After:   1 ─────> 3 -> 4 -> 5
//             //          ↑    ↘   ↑
//             //         odd    2  (even still points here)
//             //
//             // Node 1 now points directly to node 3, skipping node 2!
//             //
//             // WHY even->next?
//             // ───────────────
//             // If odd is at position 1, even is at position 2
//             // even->next is at position 3 (next odd position!)
//             // So even->next is the next node in the odd chain
//             //
//             // PATTERN:
//             // ────────
//             // Positions: 1(odd) -> 2(even) -> 3(odd) -> 4(even) -> 5(odd)
//             // odd->next should skip 2 and go to 3
//             // even->next points exactly to 3! ✓
//             // ───────────────────────────────────────────────────────────────────
            
            
//             // ═══════════════════════════════════════════════════════════════════
//             // REWIRING STEP 2: Connect Current Even to Next Even
//             // ═══════════════════════════════════════════════════════════════════
//             even->next = even->next->next;
            
//             // ───────────────────────────────────────────────────────────────────
//             // EVEN NODE REWIRING
//             // ───────────────────────────────────────────────────────────────────
//             //
//             // WHAT THIS DOES:
//             // ───────────────
//             // Make current even node SKIP the odd node and point to next even node
//             //
//             // VISUAL EXAMPLE (First iteration, continuing from above):
//             // ─────────────────────────────────────────────────────────────
//             // Current state:
//             //          1 ─────> 3 -> 4 -> 5
//             //               2 -> 3 -> 4 -> 5
//             //               ↑         ↑
//             //             even   even->next->next
//             //
//             // Action: even->next = even->next->next (2->next = 4)
//             //
//             // After:   1 ─────> 3 ─────> 5
//             //               2 ─────> 4 -> 5
//             //               ↑
//             //             even
//             //
//             // Node 2 now points directly to node 4, skipping node 3!
//             //
//             // WHY even->next->next?
//             // ─────────────────────
//             // If even is at position 2:
//             // • even->next is at position 3 (odd)
//             // • even->next->next is at position 4 (next even!)
//             //
//             // PATTERN:
//             // ────────
//             // Positions: 2(even) -> 3(odd) -> 4(even) -> 5(odd)
//             // even->next should skip 3 and go to 4
//             // even->next->next points exactly to 4! ✓
//             //
//             // CRITICAL TIMING:
//             // ────────────────
//             // We do this AFTER odd->next = even->next because:
//             // 1. First, odd grabs the next odd node (even->next)
//             // 2. Then, even can safely skip over that node
//             // If we did it in reverse order, we'd lose references!
//             // ───────────────────────────────────────────────────────────────────
            
            
//             // ═══════════════════════════════════════════════════════════════════
//             // ADVANCING POINTERS - Move to Next Nodes in Each Chain
//             // ═══════════════════════════════════════════════════════════════════
            
//             odd = odd->next;
//             // ───────────────────────────────────────────────────────────────────
//             // MOVE ODD POINTER FORWARD
//             // ───────────────────────────────────────────────────────────────────
//             // Move to the next odd node (which we just connected to)
//             //
//             // EXAMPLE:
//             // ────────
//             // After odd->next = even->next (which was 3), odd now points to 1
//             // By doing odd = odd->next, odd moves to 3
//             // Next iteration will connect 3 to 5
//             // ───────────────────────────────────────────────────────────────────
            
//             even = even->next;
//             // ───────────────────────────────────────────────────────────────────
//             // MOVE EVEN POINTER FORWARD
//             // ───────────────────────────────────────────────────────────────────
//             // Move to the next even node (which we just connected to)
//             //
//             // EXAMPLE:
//             // ────────
//             // After even->next = even->next->next (which was 4), even still points to 2
//             // By doing even = even->next, even moves to 4
//             // Next iteration will connect 4 to 6 (if it exists)
//             // ───────────────────────────────────────────────────────────────────
            
//             // ───────────────────────────────────────────────────────────────────
//             // STATE AFTER FIRST ITERATION (List: 1->2->3->4->5):
//             // ───────────────────────────────────────────────────────────────────
//             //
//             // Odd chain:  1 -> 3 -> 5
//             //                  ↑
//             //                 odd (ready for next iteration)
//             //
//             // Even chain: 2 -> 4 -> NULL
//             //                  ↑
//             //                even (ready for next iteration)
//             //
//             // Next iteration will connect 3->5 and 4->NULL
//             // ───────────────────────────────────────────────────────────────────
            
//             // ───────────────────────────────────────────────────────────────────
//             // COMPLETE ITERATION TRACE (1->2->3->4->5):
//             // ───────────────────────────────────────────────────────────────────
//             //
//             // INITIAL STATE:
//             //   1 -> 2 -> 3 -> 4 -> 5 -> NULL
//             //   ↑    ↑
//             //  odd  even
//             //
//             // ITERATION 1:
//             // ────────────
//             // odd->next = even->next:    1 -> 3
//             // even->next = even->next->next: 2 -> 4
//             // odd = odd->next:           odd now at 3
//             // even = even->next:         even now at 4
//             //
//             // State: 1 -> 3 -> 5
//             //        2 -> 4 -> 5
//             //             ↑    ↑
//             //            odd  even
//             //
//             // ITERATION 2:
//             // ────────────
//             // odd->next = even->next:    3 -> 5
//             // even->next = even->next->next: 4 -> NULL
//             // odd = odd->next:           odd now at 5
//             // even = even->next:         even now at NULL
//             //
//             // State: 1 -> 3 -> 5
//             //        2 -> 4
//             //             ↑    ↑
//             //            odd  even (NULL)
//             //
//             // Loop exits (even is NULL)
//             // ───────────────────────────────────────────────────────────────────
//         }
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 4: CONNECT ODD LIST TO EVEN LIST
//         // ═══════════════════════════════════════════════════════════════════════
        
//         odd->next = evenStart;
        
//         // ───────────────────────────────────────────────────────────────────────
//         // THE FINAL CONNECTION - Joining Two Chains
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // WHAT THIS DOES:
//         // ───────────────
//         // Connect the TAIL of odd chain to the HEAD of even chain
//         //
//         // VISUAL EXAMPLE (List: 1->2->3->4->5):
//         // ──────────────────────────────────────
//         // Before connection:
//         //   Odd chain:  1 -> 3 -> 5
//         //                         ↑
//         //                        odd (at tail)
//         //
//         //   Even chain: 2 -> 4
//         //               ↑
//         //          evenStart (at head)
//         //
//         // Action: odd->next = evenStart (5->next = 2)
//         //
//         // After connection:
//         //   1 -> 3 -> 5 -> 2 -> 4 -> NULL
//         //   └─ odd ──┘  └─ even ─┘
//         //
//         // Perfect! Now we have all odd positions followed by all even positions ✓
//         //
//         // WHY evenStart AND NOT even?
//         // ───────────────────────────
//         // After the loop, 'even' points to:
//         // • NULL (for odd-length lists)
//         // • Last even node (for even-length lists)
//         //
//         // But we need to connect to the FIRST even node (position 2)!
//         // evenStart was saved at the beginning for exactly this purpose
//         //
//         // EXAMPLE:
//         // ────────
//         // List: 1->2->3->4->5
//         // After loop: even = NULL
//         // If we did odd->next = even, we'd get: 1->3->5->NULL (losing even chain!)
//         // With evenStart: odd->next = evenStart → 1->3->5->2->4 ✓
//         //
//         // EDGE CASE: What if even list is empty?
//         // ───────────────────────────────────────
//         // Only possible with single-node list, but we handled that in base case
//         // For 2+ nodes, there's always at least one even node
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════
//         // 📋 STEP 5: RETURN THE HEAD
//         // ═══════════════════════════════════════════════════════════════════════
        
//         return head;
        
//         // ───────────────────────────────────────────────────────────────────────
//         // RETURNING THE RESULT
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // WHY RETURN head?
//         // ────────────────
//         // The FIRST node (index 1) is an odd-positioned node
//         // After all our rewiring, it's STILL the first node in the result!
//         //
//         // EXAMPLE:
//         // ────────
//         // Original: 1 -> 2 -> 3 -> 4 -> 5
//         // Result:   1 -> 3 -> 5 -> 2 -> 4
//         //           ↑
//         //         head (unchanged!)
//         //
//         // We never changed what 'head' points to - it still points to node 1
//         // Node 1 is still the beginning of the list, so return head ✓
//         //
//         // THE HEAD NEVER CHANGES:
//         // ───────────────────────
//         // Unlike some problems where we might need to return a new head,
//         // here the first node is always odd, which should be first in result
//         // So the head remains the same throughout!
//         //
//         // CONTRAST WITH OTHER PROBLEMS:
//         // ──────────────────────────────
//         // • Reverse List: head changes (last becomes first)
//         // • Reverse Between: head might change (if reversing from position 1)
//         // • Odd Even List: head NEVER changes (first is always first!)
//         // ───────────────────────────────────────────────────────────────────────
//     }
// };


// /*
// ╔════════════════════════════════════════════════════════════════════════════════╗
// ║                                                                                ║
// ║                    🎓 COMPREHENSIVE REVISION SUMMARY                           ║
// ║                   LEETCODE 328: ODD EVEN LINKED LIST                           ║
// ║                                                                                ║
// ╚════════════════════════════════════════════════════════════════════════════════╝

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎯 PROBLEM UNDERSTANDING                                                      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ⚠️ CRITICAL CLARIFICATION: "Odd/Even" refers to NODE POSITION, NOT node values!

// TASK: Group all odd-indexed nodes, then all even-indexed nodes
//       (Indices are 1-based: first node = index 1)

// EXAMPLES:
// ─────────
// Input:  1 -> 2 -> 3 -> 4 -> 5
//         1st  2nd  3rd  4th  5th  (positions)
//         odd  even odd  even odd

// Output: 1 -> 3 -> 5 -> 2 -> 4
//         └─ odd ──┘  └─ even ─┘

// Input:  2 -> 1 -> 3 -> 5 -> 6 -> 4 -> 7
// Output: 2 -> 3 -> 6 -> 7 -> 1 -> 5 -> 4
//         └──── odd ─────┘  └──── even ────┘

// CONSTRAINTS:
// • O(n) time complexity
// • O(1) space complexity (in-place)
// • Preserve relative order within odd and even groups


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🧠 CORE ALGORITHM - "PARALLEL CHAIN BUILDING"                                 ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🎯 THE STRATEGY - SIMULTANEOUS REWIRING                       ║
// ╚═══════════════════════════════════════════════════════════════╝

// Instead of creating separate lists, we REWIRE the existing list!

// STEP 1: Initialize two pointers
// ├─ odd = head (starts at position 1)
// └─ even = head->next (starts at position 2)

// STEP 2: Save even list's start
// └─ evenStart = head->next (we'll need this later!)

// STEP 3: Rewire in parallel
// ├─ odd->next = even->next (skip even node)
// ├─ even->next = even->next->next (skip odd node)
// ├─ Advance both pointers
// └─ Repeat until no more pairs

// STEP 4: Connect the chains
// └─ odd->next = evenStart (join odd tail to even head)

// STEP 5: Return head
// └─ First node is odd, still at the start!

// ANALOGY: "The Two-Lane Highway"
// ────────────────────────────────
// Think of nodes as cars on a highway:
// • Odd cars move to the fast lane (skip evens)
// • Even cars move to the slow lane (skip odds)
// • At the end, merge fast lane into slow lane
// • All odd cars end up in front!


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎨 COMPLETE VISUAL WALKTHROUGH                                                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// INPUT: 1 -> 2 -> 3 -> 4 -> 5 -> NULL

// ┌─────────────────────────────────────────────────────────────┐
// │ INITIALIZATION                                              │
// └─────────────────────────────────────────────────────────────┘

// Original list:
//   1 -> 2 -> 3 -> 4 -> 5 -> NULL
//   ↑    ↑
//  odd  even
//      evenStart

// State:
//   odd = 1
//   even = 2
//   evenStart = 2 (saved!)


// ┌─────────────────────────────────────────────────────────────┐
// │ ITERATION 1                                                 │
// └─────────────────────────────────────────────────────────────┘

// Before:
//   1 -> 2 -> 3 -> 4 -> 5 -> NULL
//   ↑    ↑    ↑
//  odd  even even->next

// Action 1: odd->next = even->next
//   Result: 1 -> 3 (1 now points to 3, skipping 2)

// Action 2: even->next = even->next->next
//   Result: 2 -> 4 (2 now points to 4, skipping 3)

// After rewiring:
//   1 ─────> 3 -> 4 -> 5
//      2 ─────> 4 -> 5

// Advance pointers:
//   odd = odd->next (odd moves to 3)
//   even = even->next (even moves to 4)

// New positions:
//   1 -> 3 -> 5
//   2 -> 4 -> 5
//        ↑    ↑
//       odd  even


// ┌─────────────────────────────────────────────────────────────┐
// │ ITERATION 2                                                 │
// └─────────────────────────────────────────────────────────────┘

// Before:
//   1 -> 3 -> 5
//   2 -> 4 -> 5
//        ↑    ↑
//       odd  even

// Action 1: odd->next = even->next
//   Result: 3 -> 5 (3 now points to 5, skipping 4)

// Action 2: even->next = even->next->next
//   Result: 4 -> NULL (4 points to NULL, end of even chain)

// After rewiring:
//   1 -> 3 -> 5 -> NULL
//   2 -> 4 -> NULL

// Advance pointers:
//   odd = odd->next (odd moves to 5)
//   even = even->next (even moves to NULL)

// New state:
//   1 -> 3 -> 5
//   2 -> 4
//             ↑    ↑
//            odd  even (NULL)

// Loop exits! (even is NULL)


// ┌─────────────────────────────────────────────────────────────┐
// │ FINAL CONNECTION                                            │
// └─────────────────────────────────────────────────────────────┘

// Current state:
//   Odd chain:  1 -> 3 -> 5
//                         ↑
//                        odd

//   Even chain: 2 -> 4
//               ↑
//          evenStart

// Action: odd->next = evenStart
//   Result: 5->next = 2

// Final result:
//   1 -> 3 -> 5 -> 2 -> 4 -> NULL ✓

// Return: head (which points to 1)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🔍 KEY INSIGHTS & "AHA!" MOMENTS                                              ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #1: Why Save evenStart?                           ║
// ╚═══════════════════════════════════════════════════════════════╝

// After rewiring, the 'even' pointer moves through the even chain
// But we need to connect odd chain to the START of even chain!

// Without evenStart:
//   • After loop, even might be NULL or at the last even node
//   • We'd lose reference to the first even node (position 2)

// With evenStart:
//   • We save position 2 before any rewiring
//   • Later: odd->next = evenStart connects chains correctly


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #2: Why Check even->next->next?                   ║
// ╚═══════════════════════════════════════════════════════════════╝

// The rewiring: even->next = even->next->next
// Requires THREE nodes: even, even->next, even->next->next

// If we only checked even->next, we might crash on NULL->next!

// The condition: even != NULL && even->next != NULL
// Ensures both even->next and even->next->next are safe to access


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #3: Order of Rewiring Matters!                    ║
// ╚═══════════════════════════════════════════════════════════════╝

// We MUST do:
//   1. odd->next = even->next (grab next odd)
//   2. even->next = even->next->next (grab next even)

// If reversed:
//   1. even->next = even->next->next (breaks the chain!)
//   2. odd->next = even->next (points to wrong node!)

// The first rewiring MUST happen before the second!


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 💡 INSIGHT #4: Even Pointer Moves Faster                     ║
// ╚═══════════════════════════════════════════════════════════════╝

// Even starts one position ahead (position 2 vs position 1)
// Both move forward by 2 each iteration
// So even always reaches the end first or simultaneously

// This is why we check 'even' for loop termination:
//   • If even has nodes, odd definitely has nodes
//   • If even runs out, we're done!


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⏱️ COMPLEXITY ANALYSIS                                                        ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╭────────────────────────────────────────────────────────────────╮
// │  ⏱️ TIME COMPLEXITY: O(n)                                      │
// ╰────────────────────────────────────────────────────────────────╯

// REASONING:
// ──────────
// • We traverse the list ONCE
// • Each node is visited exactly once during the loop
// • Each iteration processes 2 nodes (one odd, one even)
// • Total iterations: n/2 where n = number of nodes
// • Each iteration: O(1) work (pointer assignments)

// CALCULATION:
// ────────────
// n/2 iterations × O(1) per iteration = O(n/2) = O(n)

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We make a single pass through the list, visiting each node once.
// We perform constant-time operations (pointer assignments) at each
// step. Therefore, time complexity is O(n) where n is the list length."


// ╭────────────────────────────────────────────────────────────────╮
// │  💾 SPACE COMPLEXITY: O(1)                                     │
// ╰────────────────────────────────────────────────────────────────╯

// SPACE USED:
// ───────────
// • odd pointer: O(1)
// • even pointer: O(1)
// • evenStart pointer: O(1)
// • No arrays, hash tables, or recursion

// Total: O(1) - Constant space!

// KEY POINT:
// ──────────
// We REWIRE the existing list in-place
// No new nodes are created
// We only use a fixed number of pointers

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We use only three pointers regardless of input size. The solution
// modifies the list in-place by changing next pointers. No auxiliary
// data structures are needed, achieving O(1) space complexity."


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🐛 EDGE CASES & HOW THEY'RE HANDLED                                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// EDGE CASE 1: Empty List (NULL)
// ───────────────────────────────
// Input: NULL
// Base case: head == NULL → return NULL
// No processing needed ✓

// EDGE CASE 2: Single Node
// ─────────────────────────
// Input: 5 -> NULL
// Base case: head->next == NULL → return head
// Output: 5 -> NULL (unchanged) ✓
// Reason: Only one node, it's odd, already in correct position

// EDGE CASE 3: Two Nodes
// ──────────────────────
// Input: 1 -> 2 -> NULL

// Initialization:
//   odd = 1, even = 2, evenStart = 2

// Loop check: even != NULL ✓, even->next != NULL ✗
// Loop doesn't execute!

// Connection: odd->next = evenStart
//   Result: 1 -> 2 -> NULL

// Output: 1 -> 2 -> NULL (unchanged) ✓
// Reason: Already in correct order (odd then even)

// EDGE CASE 4: Three Nodes
// ────────────────────────
// Input: 1 -> 2 -> 3 -> NULL

// Iteration 1:
//   odd->next = 3 (1 -> 3)
//   even->next = NULL (2 -> NULL)
//   odd moves to 3, even moves to NULL

// Loop exits

// Connection: 3->next = 2

// Output: 1 -> 3 -> 2 -> NULL ✓

// EDGE CASE 5: Four Nodes (EVEN length)
// ──────────────────────────────────────
// Input: 1 -> 2 -> 3 -> 4 -> NULL

// Iteration 1:
//   odd->next = 3, even->next = 4
//   odd = 3, even = 4

// Loop check: even != NULL ✓, even->next != NULL ✗
// Loop exits

// Connection: 3->next = 2

// Output: 1 -> 3 -> 2 -> 4 -> NULL ✓

// EDGE CASE 6: Five Nodes (ODD length)
// ─────────────────────────────────────
// Input: 1 -> 2 -> 3 -> 4 -> 5 -> NULL

// [See complete walkthrough above]

// Output: 1 -> 3 -> 5 -> 2 -> 4 -> NULL ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ ⚠️ COMMON MISTAKES & DEBUGGING TIPS                                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ❌ MISTAKE #1: Not Saving evenStart
// ───────────────────────────────────
// Wrong:
//   At the end: odd->next = even
//   Problem: even might be NULL or at wrong position!

// Correct:
//   Save evenStart = head->next at the start
//   At the end: odd->next = evenStart ✓

// ❌ MISTAKE #2: Wrong Loop Condition
// ───────────────────────────────────
// Wrong: while(even)
//   Problem: Might crash on even->next->next when even->next is NULL

// Correct: while(even && even->next)
//   Ensures even->next->next is safe to access ✓

// ❌ MISTAKE #3: Reversing Rewiring Order
// ───────────────────────────────────────
// Wrong:
//   even->next = even->next->next;  (breaks chain first!)
//   odd->next = even->next;         (points to wrong node!)

// Correct:
//   odd->next = even->next;         (grab next odd first)
//   even->next = even->next->next;  (then break chain) ✓

// ❌ MISTAKE #4: Forgetting to Advance Pointers
// ─────────────────────────────────────────────
// Wrong:
//   Rewire but don't move odd and even
//   Problem: Infinite loop!

// Correct:
//   After rewiring, ALWAYS do:
//   odd = odd->next;
//   even = even->next; ✓

// ❌ MISTAKE #5: Confusing Position with Value
// ────────────────────────────────────────────
// Common misconception: "Separate odd VALUES from even VALUES"
// ACTUAL task: "Separate odd POSITIONS from even POSITIONS"

// Example: 2 -> 1 -> 3
//   Values: 2(even), 1(odd), 3(odd)
//   Positions: 2(1st-odd), 1(2nd-even), 3(3rd-odd)
//   Output: 2 -> 3 -> 1 (not 1 -> 3 -> 2!)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎤 INTERVIEW TALKING POINTS                                                   ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// OPENING:
// ────────
// "I'll solve this by building two chains simultaneously - one for
// odd positions and one for even positions. Instead of creating new
// lists, I'll rewire the existing nodes in-place. This achieves
// O(n) time and O(1) space."

// CLARIFYING QUESTION (IMPORTANT!):
// ──────────────────────────────────
// "Just to confirm: by 'odd' and 'even', we're referring to node
// positions (1st, 2nd, 3rd, etc.), not node values, correct?"
// [Wait for confirmation]

// DURING CODING:
// ──────────────
// [Base cases] "Handling edge cases for empty and single-node lists..."

// [Initialization] "I'll save the start of the even list before
// rewiring, as I'll need it for the final connection..."

// [Loop] "The key insight: make odd nodes skip even nodes, and vice
// versa, by adjusting next pointers in parallel..."

// [Connection] "Finally, connect the tail of odd chain to the head
// of even chain that we saved earlier..."

// AFTER CODING:
// ─────────────
// "The algorithm is O(n) time with a single pass, and O(1) space
// using only three pointers. Let me trace through an example to
// verify correctness..."

// FOLLOW-UP QUESTIONS:
// ────────────────────

// Q: "Can you do it recursively?"
// A: "Yes, but it would use O(n) space on the call stack. The
// iterative approach is better for large lists."

// Q: "What if you need to group by every 3rd position?"
// A: "We'd extend this to three chains. The pattern generalizes:
// k chains for every kth position, still O(n) time but using k pointers."

// Q: "How would you verify the output?"
// A: "Check that: 1) All odd positions come first in order,
// 2) Then all even positions in order, 3) No nodes lost,
// 4) No cycles created."


// ═══════════════════════════════════════════════════════════════════════════════

// 🎓 MEMORY TRICK - "THE TWO-LANE HIGHWAY":

// Imagine cars (nodes) on a highway:
// 1. ODD cars merge to FAST lane (positions 1, 3, 5, ...)
// 2. EVEN cars merge to SLOW lane (positions 2, 4, 6, ...)
// 3. Each car skips the car ahead in the other lane
// 4. At the end, fast lane (odd) connects to slow lane (even)
// 5. All odd cars end up in front!

// ═══════════════════════════════════════════════════════════════════════════════

// 📋 QUICK REFERENCE - THE ALGORITHM:

// INITIALIZATION:
//   odd = head
//   even = head->next
//   evenStart = head->next (SAVE THIS!)

// LOOP (while even && even->next):
//   odd->next = even->next       (skip even)
//   even->next = even->next->next (skip odd)
//   odd = odd->next              (advance)
//   even = even->next            (advance)

// CONNECTION:
//   odd->next = evenStart

// RETURN:
//   head (unchanged!)

// ═══════════════════════════════════════════════════════════════════════════════
// */