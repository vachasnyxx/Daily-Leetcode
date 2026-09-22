class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL || k == 0)
            return head;

        int L = 1;

        ListNode* tail = head;

        while (tail->next != NULL) {
            tail = tail->next;
            L++;
        }

        k = k % L;
        if (k == 0) {
            return head;
        }

        tail->next = head;

        int remain = L - k;
        ;

        ListNode* newTail = head;
        for (int c = 1; c < remain; c++) {
            newTail = newTail->next;
        }
        ListNode* newHead = newTail->next;
        newTail->next = NULL;
        return newHead;
    }
};











// class Solution {
// public:
//     ListNode* rotateRight(ListNode* head, int k) {
        
//         // ============================================================
//         // PROBLEM: Rotate the linked list to the RIGHT by k positions
//         //
//         // Example: [1, 2, 3, 4, 5], k = 2
//         //   Original:     1 → 2 → 3 → 4 → 5
//         //   After rot 1:  5 → 1 → 2 → 3 → 4
//         //   After rot 2:  4 → 5 → 1 → 2 → 3
//         //
//         // It's like CIRCULAR SHIFT — last k elements jump to front
//         //
//         // VISUAL (Think of it as a Conveyor Belt 🏭):
//         //   BEFORE: [1, 2, 3, 4, 5]
//         //   Belt moves right by 2 → [4, 5, 1, 2, 3]
//         //   The "cut" happens between position (L-k) and (L-k+1)
//         // ============================================================


//         // ─── EDGE CASE 1: Trivial Cases ───
//         // ⚠️ ATOMIC DETAIL #1: THREE conditions, ALL mean "no rotation needed"
//         //
//         // head == NULL           → Empty list, nothing to rotate
//         // head->next == NULL     → Single node, rotating changes nothing
//         // k == 0                 → User explicitly says rotate 0 times
//         //
//         // WHY k == 0 here is important?
//         // Later we do k = k % L. If L = 1 (single node), k % 1 = 0 always.
//         // So this check is partially redundant BUT saves us from:
//         //   - Going into the loop unnecessarily
//         //   - Confusion in reasoning
//         // It's a SAFETY GUARD. Defensive programming! 🛡️
//         //
//         // ⚠️ ORDER MATTERS: head == NULL is checked FIRST
//         // If head is NULL, head->next would CRASH! 💥
//         if (head == NULL || head->next == NULL || k == 0)
//             return head;

//         // ─── STEP 1: MEASURE LENGTH AND FIND TAIL ───
//         // We need two things:
//         //   1. Length L (for k % L later)
//         //   2. Tail pointer (to close the circle temporarily)
//         //
//         // WHY do we need tail?
//         // To rotate, we need to connect the TAIL back to the HEAD
//         // creating a temporary CIRCLE, then cut at the new position.
//         //
//         // ⚠️ ATOMIC DETAIL #2: Initialize tail = head (NOT NULL)
//         // L starts at 1 (NOT 0) because head itself counts as the first node!
//         // Common bug: starting L = 0 and looping while tail != NULL
//         //             → that counts n+1 times. WRONG!
        
//         int L = 1;             // Length counter, starts at 1 (head counts!)

//         ListNode* tail = head;  // Will end up pointing to the LAST node

//         // Walk to the end, counting nodes
//         while (tail->next != NULL) {
//             tail = tail->next;
//             L++;
//         }
//         // Now: tail = last node, L = total length

//         // ─── STEP 2: HANDLE k > L CASE ───
//         // ⚠️ ATOMIC DETAIL #3: k = k % L — THIS IS CRUCIAL!
//         //
//         // If list has 5 nodes and k = 7:
//         //   Rotating 7 times = rotating 7%5 = 2 times (same result!)
//         //   Because after 5 rotations you're back to the original.
//         //
//         // WHY does this work?
//         // Rotating by L brings you back to start. So we only care
//         // about the remainder.
//         //
//         // Example: [1,2,3,4,5], k=7
//         //   7 % 5 = 2 → same as rotating by 2 → [4,5,1,2,3]
//         //
//         // This handles k = 1000000 efficiently too!
        
//         k = k % L;
        
//         // ─── EDGE CASE 2: After modulo, k might be 0 ───
//         // This happens when k was a multiple of L (e.g., L=5, k=10)
//         // k = 10 % 5 = 0 → no rotation needed
//         // ⚠️ ATOMIC DETAIL #4: MUST check AFTER k % L, not just before!
//         // The first check only catches k==0 as INPUT.
//         // This catches k that BECOMES 0 after modulo!
//         //
//         // Example: [1,2,3], k=6 → 6%3 = 0 → return original!
//         if (k == 0) {
//             return head;
//         }

//         // ─── STEP 3: CREATE TEMPORARY CIRCLE ───
//         // THE "CONGA LINE / MUSICAL CHAIRS" TRICK 🎵
//         //
//         // Original:  1 → 2 → 3 → 4 → 5 → NULL
//         //                          ↑ tail
//         //
//         // Connect tail to head:
//         //   1 → 2 → 3 → 4 → 5
//         //   ↑                  ↑
//         //  head              tail
//         //   └──────────────────┘  ← CIRCLE CLOSED!
//         //
//         // NOW the list is circular. We can "walk" around it
//         // and then "cut" at any point to get our rotated list.
//         //
//         // WHY circular?
//         // Rotating = moving the cut point. With a circle,
//         // we just walk (L - k) steps and cut there.
//         // Think of it like a FERRIS WHEEL 🎡 — all seats are
//         // connected, we just change where passengers board!
        
//         tail->next = head;

//         // ─── STEP 4: FIND THE NEW CUT POINT ───
//         // We need to walk (L - k) steps from head to find newTail.
//         // newTail is the node that should become the LAST node
//         // (its next will be set to NULL to break the circle).
//         //
//         // VISUAL for [1,2,3,4,5], k=2:
//         //   L = 5, remain = L - k = 5 - 2 = 3
//         //   We walk 3-1 = 2 steps (loop starts at c=1, ends at c=2)
//         //
//         //   Start: newTail = head(1)
//         //   c=1: newTail = 2
//         //   c=2: newTail = 3  ← STOP! This is our new tail
//         //                        (node 3)
//         //
//         //   New tail = node(3), new head = node(3)->next = node(4)
//         //   Cut: node(3)->next = NULL
//         //
//         //   Result: 4 → 5 → 1 → 2 → 3 → NULL  ✓
//         //
//         // ⚠️ ATOMIC DETAIL #5: remain = L - k, and loop runs (remain - 1) times
//         //   Why remain - 1?
//         //   Because newTail starts AT node 1 (which is step 0).
//         //   We need it to be at node (remain), so we advance (remain - 1) times.
//         //
//         //   c goes from 1 to remain-1 inclusive = (remain-1) iterations
//         //
//         //   L=5, k=2 → remain=3 → loop: c=1, c=2 → 2 iterations → node 3 ✓
//         //
//         // ⚠️ ATOMIC DETAIL #6: The stray semicolon ";;" in your code!
//         //   Harmless (just an empty statement) but shows lack of attention.
//         //   Remove it for cleaner code in interviews. ✨

//         int remain = L - k;   // Steps to walk before cutting

//         ListNode* newTail = head;  // Will be set to the new last node

//         // Walk (remain - 1) steps from head
//         for (int c = 1; c < remain; c++) {
//             newTail = newTail->next;
//         }
//         // newTail is now at position 'remain' from start
//         // Everything AFTER newTail will become the new front

//         // ─── STEP 5: CUT THE CIRCLE ───
//         // ⚠️ ATOMIC DETAIL #7: ORDER OF THESE 3 LINES MATTERS!
//         //
//         // If you set newTail->next = NULL FIRST:
//         //   → newHead = newTail->next would be NULL! 💥
//         //   → You'd lose the entire rotated section!
//         //
//         // CORRECT order:
//         //   ① Save newHead (grab the other side before cutting)
//         //   ② Cut the link (break the circle)
//         //   ③ Return newHead
//         //
//         // It's like holding BOTH sides of a rope before cutting! 🪢

//         ListNode* newHead = newTail->next;  // ① Save the new front
//         newTail->next = NULL;                // ② Break the circle (cut!)
//         return newHead;                       // ③ Return the new head

//         // ============================================================
//         // FULL TRACE for [1, 2, 3, 4, 5], k = 2:
//         // ============================================================
//         //
//         // STEP 1: Find tail & length
//         //   Walk: 1→2→3→4→5
//         //   tail = node(5), L = 5
//         //
//         // STEP 2: k = 2 % 5 = 2 (no change needed)
//         //
//         // STEP 3: Close circle
//         //   node(5)->next = node(1)
//         //   Circle: 1→2→3→4→5→(back to 1)→2→3→4→5→...
//         //
//         // STEP 4: Find newTail
//         //   remain = 5 - 2 = 3
//         //   c=1: newTail = node(2)
//         //   c=2: newTail = node(3)  ← newTail = node(3)
//         //
//         // STEP 5: Cut
//         //   newHead = node(3)->next = node(4)
//         //   node(3)->next = NULL
//         //   return node(4)
//         //
//         // Result: 4 → 5 → 1 → 2 → 3 → NULL  ✓✓✓
//         // ============================================================
//     }
// };

// /*
// ╔══════════════════════════════════════════════════════════════════════════════╗
// ║                   🧠 DEEP DIVE REVISION GUIDE - LC 61                        ║
// ╚══════════════════════════════════════════════════════════════════════════════╝

// 📌 PROBLEM: Rotate linked list to the right by k positions

// 🎯 ALGORITHM: Close Circle → Walk → Cut

// ═══════════════════════════════════════════════════════════════════════════════
// 🔗 THE "CIRCULAR TRAIN" ANALOGY (Remember This Forever!)
// ═══════════════════════════════════════════════════════════════════════════════

// Imagine train carriages arranged in a CIRCLE on a roundabout 🚂🎡:

//   Normal line:  [1] → [2] → [3] → [4] → [5] → END

//   Connect end to start (close the circle):
//                 [1] → [2] → [3] → [4] → [5]
//                  ↑                             │
//                  └─────────────────────────────┘

//   Now walk (L - k) = 3 steps from start:
//   1 → 2 → 3  ← STOP HERE, this is our new "end"

//   CUT the circle right after node 3:
//   [1] → [2] → [3] → ✂️ CUT ✂️

//   Rearrange as a straight line again:
//   [4] → [5] → [1] → [2] → [3]  ✓

//   That's it! Close → Walk → Cut → Done! 🎯

// ═══════════════════════════════════════════════════════════════════════════════
// 🧩 THE 5-STEP PATTERN (Memorize This Template!)
// ═══════════════════════════════════════════════════════════════════════════════

//   ┌───────────────────────────────────────────────────────────────┐
//   │ STEP 1: Handle trivial cases (empty, single, k=0)            │
//   │ STEP 2: Measure length L and find tail (walk to end)         │
//   │ STEP 3: k = k % L (handle k ≥ L efficiently)                │
//   │ STEP 4: Close circle: tail->next = head                      │
//   │ STEP 5: Walk (L-k) steps → cut at newTail → return newHead   │
//   └───────────────────────────────────────────────────────────────┘

//   THE MATH:
//   ┌──────────────────────────────────────────────────────┐
//   │ • k % L = effective rotations (always < L)          │
//   │ • remain = L - k = position of new tail from start   │
//   │ • newHead = node AFTER new tail                      │
//   │ • Cut: newTail->next = NULL                         │
//   └──────────────────────────────────────────────────────┘

// ═══════════════════════════════════════════════════════════════════════════════
// ⚠️ ATOMIC DETAILS YOU MUST NOTICE (Interview Differentiators)
// ═══════════════════════════════════════════════════════════════════════════════

//   1️⃣ TWO DIFFERENT k==0 CHECKS at different points
//      ┌──────────────────────────────────────────────────────────┐
//      │ Check 1 (beginning): k == 0 as INPUT                    │
//      │   → k=0 means "no rotation", return early               │
//      │                                                          │
//      │ Check 2 (after k%L): k BECOMES 0 after modulo            │
//      │   → e.g., L=3, k=6 → 6%3=0 → no effective rotation     │
//      │                                                          │
//      │ ⚠️ You MUST have BOTH!                                  │
//      │ Missing Check 2 → would close circle, walk 0 steps,     │
//      │   newTail=head, newHead=head->next, CUT WRONG → 💥     │
//      └──────────────────────────────────────────────────────────┘

//   2️⃣ k = k % L BEFORE deciding how many steps to walk
//      Without modulo, k=7 with L=5 would walk in WRONG direction
//      or crash. The modulo ENSURES k is always in [0, L-1].

//   3️⃣ Walk (L-k) steps, NOT k steps
//      ┌──────────────────────────────────────────────┐
//      │ k rotations RIGHT means cut (L-k) from start │
//      │ k=2, L=5 → cut at position 3                │
//      │ 1→2→3|4→5    newTail=3, newHead=4           │
//      │              4→5→1→2→3 ✓                     │
//      │                                              │
//      │ Confusion alert: Some people walk k steps    │
//      │ from the END instead. Same result but you   │
//      │ need a tail pointer. Walking from start     │
//      │ with (L-k) is cleaner!                      │
//      └──────────────────────────────────────────────┘

//   4️⃣ For loop starts at c=1, NOT c=0
//      Because newTail starts AT head (position 1 already).
//      c=1 means "take your FIRST step to node 2".
     
//      L=5, k=2, remain=3:
//        newTail starts at node 1 (counted as position 1)
//        c=1: move to node 2 (position 2)
//        c=2: move to node 3 (position 3) ← DONE
//        Loop condition: c < 3 → runs for c=1, c=2 → 2 iterations
//        Total position: 1 + 2 = 3 = remain ✓

//   5️⃣ Capture newHead BEFORE cutting
//      newHead = newTail->next must happen BEFORE newTail->next = NULL
//      Otherwise newHead becomes NULL! Classic linked list gotcha.

//   6️⃣ Stray ";;" in your code
//      Harmless but looks sloppy. Remove it for interviews! ✨

//   7️⃣ tail->next = head creates a TEMPORARY circle
//      We intentionally BREAK this in step 5 with newTail->next = NULL
//      If we forget to cut, we'd have an infinite loop! 💀
//      (the list would circle forever)

// ═══════════════════════════════════════════════════════════════════════════════
// 🐛 EDGE CASES TO THINK ABOUT
// ═══════════════════════════════════════════════════════════════════════════════

//   Case 1: Empty list []
//     → head == NULL → return NULL ✓

//   Case 2: Single node [1], k = 5
//     → head->next == NULL → return head ✓
//     → (even without this check: 5%1=0 → returns head ✓)

//   Case 3: k = 0, any list
//     → First check catches it → return head ✓

//   Case 4: k = L (same as k=0 after modulo)
//     → [1,2,3], k=3 → 3%3=0 → return head ✓

//   Case 5: k = L-1 (rotate almost fully)
//     → [1,2,3,4,5], k=4 → 4%5=4, remain=1
//     → Loop: c=1 < 1? NO → newTail = head(node 1)
//     → newHead = node(2), cut node(1)->next = NULL
//     → Result: 5→1 → wait, let me retrace...
    
//     Actually: newTail = head = node(1), newHead = node(1)->next = node(2)
//     But node(1)->next = NULL would cut everything after node 1.
//     But the circle was: 1→2→3→4→5→(back to 1)
//     So newHead = node(2), and cutting node(1)->next = NULL
//     gives: 5→1→NULL? No...
    
//     Wait: newTail = node(1). newHead = node(1)->next = node(2).
//     node(1)->next = NULL.
//     But we RETURN newHead = node(2).
//     The list is: 2→3→4→5→1→NULL (since 1 was tail now... no)
    
//     Hmm, let me retrace properly:
//     - Circle: 1→2→3→4→5→1 (circular)
//     - newTail walks 0 steps (remain=1, loop doesn't run) → newTail = node(1)
//     - newHead = node(1)->next = node(2)
//     - node(1)->next = NULL
//     - return node(2)
//     - List from node(2): 2→3→4→5→1→NULL ✓ (that's rotating right by 4 = left by 1)

//   Case 6: k > L (handled by modulo!)
//     → [1,2,3], k=7 → 7%3=1 → rotate by 1 → [3,1,2] ✓

// ═══════════════════════════════════════════════════════════════════════════════
// ⏱️ COMPLEXITY (Easy Interview Explanation)
// ═══════════════════════════════════════════════════════════════════════════════

//   TIME: O(n)
//   ──────────
//   "Pass 1: Walk to find tail and length → O(n)
//    Pass 2: Walk (L-k) steps to find newTail → O(L-k) = O(n)
//    Total: O(n) + O(n) = O(n).
//    The k%L operation is O(1).
//    Even for huge k (like 10^9), modulo makes it O(1)."

//   SPACE: O(1)
//   ────────────
//   "We use only pointers (tail, newTail, newHead) and integers (L, k, remain).
//    No arrays, no stacks, no recursion. Everything is in-place pointer manipulation."

//   ⚠️ COMPARE WITH ALTERNATIVES:
//   ┌──────────────────────┬──────────┬───────────┐
//   │ Approach             │ Time     │ Space     │
//   ├──────────────────────┼──────────┼───────────┤
//   │ Array + push_back    │ O(n)     │ O(n) ❌   │
//   │ Stack-based          │ O(n)     │ O(n) ❌   │
//   │ Close-Circle-Cut     │ O(n)     │ O(1) ✅   │  ← YOUR SOLUTION
//   └──────────────────────┴──────────┴───────────┘

// ═══════════════════════════════════════════════════════════════════════════════
// 🎤 INTERVIEWER EXPLANATION SCRIPT (45 seconds)
// ═══════════════════════════════════════════════════════════════════════════════

//   "I'll use a circle-and-cut approach. First, I walk to the end of
//    the list to find the length L and the tail node. Then I reduce
//    k to k%L to handle cases where k ≥ L. If k%L is 0, no rotation
//    needed. Otherwise, I temporarily connect tail->next to head to
//    form a circle. I then walk (L-k) steps from the head to find
//    the new tail — that's where the cut should happen. I save
//    newHead as newTail->next, then set newTail->next to NULL to
//    break the circle. The result is the rotated list. This takes
//    O(n) time and O(1) space."

// ═══════════════════════════════════════════════════════════════════════════════
// 🔄 ALTERNATIVE: LEFT ROTATION (If interviewer switches it up)
// ═══════════════════════════════════════════════════════════════════════════════

//   If problem asks for LEFT rotation by k:
//   [1,2,3,4,5], k=2 → [3,4,5,1,2]

//   Changes needed:
//   1. remain = k (NOT L-k!) — cut after k-th node instead
//   2. Or equivalently: use k' = (L - k) % L and follow same logic

//   THE RELATIONSHIP:
//   ┌──────────────────────────────────────────────────┐
//   │ RIGHT rotate by k = LEFT rotate by (L - k)       │
//   │ LEFT rotate by k  = RIGHT rotate by (L - k)      │
//   │                                                  │
//   │ This works because rotating right k times        │
//   │ is the same as rotating left (L-k) times         │
//   │ (since rotating L times = no change)             │
//   └──────────────────────────────────────────────────┘

// ═══════════════════════════════════════════════════════════════════════════════
// 📚 PATTERN RECOGNITION CHEAT SHEET
// ═══════════════════════════════════════════════════════════════════════════════

//   "Close Circle → Walk → Cut"

//   USE WHEN:
//   ✓ Problem involves circular operations on a linked list
//   ✓ Need to move sections from end to beginning (or vice versa)
//   ✓ The circular property simplifies the problem

//   KEY INSIGHT:
//   "Linked lists are linear, but ROTATION is a circular concept.
//    Close the circle → find the cut point → open it back up.
//    Transform circular problem into linear problem!"

//   RELATED PROBLEMS:
//   ┌──────────────────────────────────────────────────────────────┐
//   │ LC 61: Rotate List (this!)    → Close circle, cut          │
//   │ LC 25: Reverse k-Group        → Similar "group processing" │
//   │ LC 189: Rotate Array          → Same math, different data  │
//   │ LC 2237: (variant)            → Same pattern               │
//   └──────────────────────────────────────────────────────────────┘

//   THE UNIVERSAL ROTATION FORMULA:
//   ┌──────────────────────────────────────────────────┐
//   │ For length L, rotation by k:                     │
//   │ • Effective rotation = k % L                    │
//   │ • Right by k: cut after (L - k%L) nodes         │
//   │ • Left by k:  cut after (k%L) nodes             │
//   │ • If k%L == 0: no rotation                      │
//   └──────────────────────────────────────────────────┘

//   ⚠️ REMEMBER THE ATOMIC ORDER:
//   ┌──────────────────────────────────────────────────┐
//   │ 1. Check trivial cases (NULL, single, k==0)      │
//   │ 2. Find tail + length                             │
//   │ 3. k = k % L  → check k==0 again                │
//   │ 4. tail->next = head  (close circle)             │
//   │ 5. Walk L-k steps → newTail                      │
//   │ 6. Save newHead = newTail->next  (BEFORE cut!)  │
//   │ 7. newTail->next = NULL  (cut!)                  │
//   │ 8. Return newHead                                │
//   └──────────────────────────────────────────────────┘

// */