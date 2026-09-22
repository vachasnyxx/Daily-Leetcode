class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL ||head->next == NULL){
            return head;
        }


        ListNode* temp = head->next;
        head->next = swapPairs(head->next->next);
        temp->next = head;

        return temp;

    }
};






// class Solution {
// public:
//     ListNode* swapPairs(ListNode* head) {
        
//         // ============================================================
//         // PROBLEM: Swap every TWO adjacent nodes in the linked list
//         // Example: [1,2,3,4] → [2,1,4,3]
//         // Example: [1,2,3]   → [2,1,3]   (odd one out stays)
//         // Example: [1]       → [1]       (nothing to swap)
//         // ============================================================
//         // APPROACH: RECURSION (Divide & Conquer on Pairs)
//         // ============================================================
        
        
//         // ─── BASE CASE: When to STOP recursing ───
//         // ⚠️ ATOMIC DETAIL #1: TWO conditions, order matters!
//         //   1. head == NULL       → Empty list (even length list exhausted)
//         //   2. head->next == NULL → Single node left (odd length leftover)
//         // In BOTH cases, there's no pair to swap, so return as-is.
//         // 
//         // WHY check head->next == NULL?
//         // Because swapping requires a PAIR. A lone node can't swap with nobody.
//         // 
//         // ⚠️ ATOMIC DETAIL #2: Short-circuit evaluation!
//         // head == NULL is checked FIRST. If true, head->next is never evaluated.
//         // This prevents NULL pointer dereference. If you swap the order → CRASH! 💥
//         if(head == NULL || head->next == NULL){
//             return head;
//         }

//         // ─── RECURSIVE STEP: The "Pair Swap" Dance 💃🕺 ───
//         // 
//         // Let's visualize with [1, 2, 3, 4]:
//         //                        ↑  ↑  ↑  ↑
//         //                      head temp  rest...
//         //
//         // We are at the FIRST pair: (1, 2)
//         // head = node 1
//         // temp = node 2  (the second node in the pair)
//         //
//         // GOAL: Make it (2 → 1 → [result of swapping rest])
//         //                         ↑ this is the recursive leap!
        
//         // STEP 1: Save the second node (it will become the NEW head of this pair)
//         ListNode* temp = head->next;
//         // ⚠️ ATOMIC DETAIL #3: We MUST save temp BEFORE modifying head->next.
//         // If we did head->next = swapPairs(...) first, we'd LOSE access to node 2!
//         // Because head->next would already be overwritten.
//         //
//         // Think of it like: "Grab your partner before the music changes!" 🎵

//         // STEP 2: Recursively swap the REST of the list and connect
//         // head->next should point to whatever comes AFTER the swapped rest
//         // 
//         // head->next->next is node 3 (start of the remaining list)
//         // swapPairs(3→4) returns 4→3
//         // So head(1)->next = 4→3
//         // 
//         // THE RECURSIVE LEAP OF FAITH 🙏:
//         // "I trust that swapPairs will correctly swap everything after my pair.
//         //  I just need to connect my pair to that result."
//         head->next = swapPairs(head->next->next);

//         // STEP 3: Complete the pair swap
//         // temp (node 2) should point to head (node 1)
//         // Now: temp(2) → head(1) → [swapped rest]
//         temp->next = head;

//         // STEP 4: Return the NEW head of this pair
//         // temp (node 2) is now the front of this swapped pair
//         // The caller will connect THEIR pair to this returned node
//         return temp;
        
//         // ============================================================
//         // FULL TRACE for [1, 2, 3, 4]:
//         // ============================================================
//         // 
//         // Call 1: swapPairs(1→2→3→4)
//         //   temp = 2
//         //   head(1)->next = swapPairs(3→4)  ← WAIT for Call 2
//         //
//         //   Call 2: swapPairs(3→4)
//         //     temp = 4
//         //     head(3)->next = swapPairs(NULL)  ← WAIT for Call 3
//         //
//         //     Call 3: swapPairs(NULL)
//         //       return NULL  ← BASE CASE HIT!
//         //
//         //     Back in Call 2:
//         //       head(3)->next = NULL  ✓
//         //       temp(4)->next = 3     ✓
//         //       return 4  →  List is now: 4→3→NULL
//         //
//         //   Back in Call 1:
//         //     head(1)->next = 4→3→NULL  ✓
//         //     temp(2)->next = 1         ✓
//         //     return 2  →  List is now: 2→1→4→3→NULL  🎉
//         //
//         // Final Answer: 2→1→4→3  ✓✓✓
//         // ============================================================
//     }
// };

// /*
// ╔══════════════════════════════════════════════════════════════════════════════╗
// ║                   🧠 DEEP DIVE REVISION GUIDE - LC 24                        ║
// ╚══════════════════════════════════════════════════════════════════════════════╝

// 📌 PROBLEM: Swap every two adjacent nodes in a linked list

// 🎯 ALGORITHM: Recursion (Divide & Conquer on Pairs)

// ═══════════════════════════════════════════════════════════════════════════════
// 🔗 THE "CONGA LINE" ANALOGY (Remember This Forever!)
// ═══════════════════════════════════════════════════════════════════════════════

// Imagine a conga line of dancers: [A, B, C, D, E, F]

// The rule: Every TWO dancers must swap positions.

//   Original:  A-B  C-D  E-F
//   Swapped:   B-A  D-C  F-E

// How does the RECURSIVE approach work?

//   🧠 Think of it as a chain of managers:
  
//   Manager 1 handles pair (A, B):
//     "I'll swap A and B, but I need to know what comes AFTER us."
//     → Calls Manager 2 for the rest (C, D, E, F)
  
//   Manager 2 handles pair (C, D):
//     "I'll swap C and D, but I need to know what comes AFTER us."
//     → Calls Manager 3 for the rest (E, F)
  
//   Manager 3 handles pair (E, F):
//     "I'll swap E and F, nothing comes after."
//     → Returns F→E
  
//   Manager 2 receives F→E:
//     → Connects: D→C→F→E
//     → Returns D→C→F→E
  
//   Manager 1 receives D→C→F→E:
//     → Connects: B→A→D→C→F→E
//     → Returns B→A→D→C→F→E  ✅ DONE!

//   Each manager does ONLY their pair and trusts the next manager!

// ═══════════════════════════════════════════════════════════════════════════════
// 🧩 THE 3-LINE RECURSIVE PATTERN (Memorize This!)
// ═══════════════════════════════════════════════════════════════════════════════

//   For ANY pair (head, head->next):

//   ┌───────────────────────────────────────────────────────────────┐
//   │  ListNode* temp = head->next;            // Save 2nd node    │
//   │  head->next = swapPairs(head->next->next); // Link to rest   │
//   │  temp->next = head;                      // Swap the pair    │
//   │  return temp;                            // New pair head    │
//   └───────────────────────────────────────────────────────────────┘

//   VISUAL TRANSFORMATION:
  
//   BEFORE:  head(1) → temp(2) → 3 → 4 → ...
  
//   AFTER:   temp(2) → head(1) → [swapped 3,4,...]
//            ↑ return this!

// ═══════════════════════════════════════════════════════════════════════════════
// ⚠️ ATOMIC DETAILS YOU MUST NOTICE (Interview Differentiators)
// ═══════════════════════════════════════════════════════════════════════════════

//   1️⃣ SAVE temp BEFORE modifying head->next
//      ┌──────────────────────────────────────────────────────────┐
//      │ ✅ ListNode* temp = head->next;   // Save first!        │
//      │    head->next = swapPairs(...);   // Then modify        │
//      │                                                          │
//      │ ❌ head->next = swapPairs(...);   // Lost head->next!   │
//      │    ListNode* temp = head->next;   // temp is WRONG now   │
//      └──────────────────────────────────────────────────────────┘
//      This is the #1 mistake candidates make!

//   2️⃣ head->next->next is the start of the NEXT pair
//      Not head->next! Because head->next is the CURRENT pair's second node.
//      We need to skip BOTH nodes of the current pair.

//   3️⃣ Base case checks head AND head->next
//      - NULL head → even-length list fully processed
//      - Single node → odd-length leftover, can't swap alone
//      - Order matters: check NULL first to avoid crash!

//   4️⃣ We return temp, NOT head
//      After swapping, temp (originally 2nd node) is the NEW front.
//      The caller needs the new front to connect their pair.

//   5️⃣ We're swapping NODES (pointers), not values
//      Unlike LC 1721 where we swapped values, here we rearrange
//      actual pointers. The problem says "swap the nodes" not values.
//      This is the CORRECT approach for this problem.

//   6️⃣ The recursion naturally handles odd-length lists
//      [1,2,3] → swap(1,2) + recurse(3) → 3 hits base case → returns 3
//      Result: 2→1→3 ✓ (the 3 just stays at the end)

// ═══════════════════════════════════════════════════════════════════════════════
// 🐛 EDGE CASES TO THINK ABOUT
// ═══════════════════════════════════════════════════════════════════════════════

//   Case 1: Empty list []
//     → head == NULL → return NULL ✓

//   Case 2: Single node [1]
//     → head->next == NULL → return head(1) ✓

//   Case 3: Two nodes [1,2]
//     → temp=2, head(1)->next=swapPairs(NULL)=NULL, temp(2)->next=1
//     → return 2→1 ✓

//   Case 4: Odd length [1,2,3]
//     → swap(1,2), recurse(3)→returns 3
//     → 2→1→3 ✓

//   Case 5: Even length [1,2,3,4]
//     → swap(1,2), recurse(3,4)→returns 4→3
//     → 2→1→4→3 ✓

// ═══════════════════════════════════════════════════════════════════════════════
// ⏱️ COMPLEXITY (Easy Interview Explanation)
// ═══════════════════════════════════════════════════════════════════════════════

//   TIME: O(n)
//   ──────────
//   "We visit each node exactly once. Each recursive call processes
//    2 nodes and makes one recursive call for the rest. So n/2 calls,
//    each doing O(1) work. Total = O(n)."

//   SPACE: O(n) — specifically O(n/2) call stack
//   ──────────────────────────────────────────────
//   "The recursion depth is n/2 because we process 2 nodes per call.
//    Each call adds a frame to the call stack. So space = O(n).
//    This is the trade-off of recursion vs iteration."

//   ⚠️ INTERVIEW TIP: If asked to optimize space:
//   "The iterative version uses O(1) space with a dummy node and
//    pointer manipulation. But the recursive version is cleaner
//    and more intuitive to explain."

// ═══════════════════════════════════════════════════════════════════════════════
// 🎤 INTERVIEWER EXPLANATION SCRIPT (30 seconds)
// ═══════════════════════════════════════════════════════════════════════════════

//   "I'll use recursion to swap pairs. The base case is when the list
//    is empty or has one node — nothing to swap. For each recursive call,
//    I take the first two nodes, save the second as the new head of this
//    pair, recursively swap the remaining list, connect the first node to
//    that result, then point the second node back to the first. I return
//    the second node as the new head. This gives O(n) time and O(n) space
//    for the call stack."

// ═══════════════════════════════════════════════════════════════════════════════
// 🔄 ITERATIVE ALTERNATIVE (For Comparison & Follow-up)
// ═══════════════════════════════════════════════════════════════════════════════

//   ListNode* swapPairs(ListNode* head) {
//       ListNode dummy(0);
//       dummy.next = head;
//       ListNode* prev = &dummy;
      
//       while(prev->next && prev->next->next) {
//           ListNode* first = prev->next;
//           ListNode* second = prev->next->next;
          
//           first->next = second->next;
//           second->next = first;
//           prev->next = second;
          
//           prev = first;  // Move prev to the end of swapped pair
//       }
//       return dummy.next;
//   }

//   KEY DIFFERENCE: Uses a DUMMY node to handle head changes cleanly.
//   Space: O(1) — no call stack!
//   Mention this if interviewer asks "Can you do it iteratively?"

// ═══════════════════════════════════════════════════════════════════════════════
// 📚 PATTERN RECOGNITION (When to Use This Technique)
// ═══════════════════════════════════════════════════════════════════════════════

//   Use RECURSIVE PAIR/GROUP processing when:
//   ✓ Problem involves reversing/swapping in fixed-size groups
//   ✓ Related: Reverse Nodes in k-Group (LC 25) — SAME pattern, group of k!
//   ✓ The subproblem is identical to the original (classic recursion signal)
//   ✓ You can cleanly define a base case for "not enough nodes"
  
//   THE RECURSIVE TEMPLATE FOR GROUP PROBLEMS:
//   ┌──────────────────────────────────────────────┐
//   │ 1. Base case: not enough nodes → return head │
//   │ 2. Process current group                     │
//   │ 3. Recurse on remaining list                 │
//   │ 4. Connect current group to recursive result │
//   │ 5. Return new head of current group          │
//   └──────────────────────────────────────────────┘

//   LC 24 is just LC 25 with k=2! Master this → LC 25 becomes easy! 🚀

// */