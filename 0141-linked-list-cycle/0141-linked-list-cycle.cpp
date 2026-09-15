/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
//  */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
            if(slow==fast) return true;
        }
        return false;
    }
};





// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode(int x) : val(x), next(NULL) {}
//  * };
//  */
// class Solution {
// public:
//     bool hasCycle(ListNode *head) {

//         // ============================================================
//         // 🧠 INTUITION & PATTERN: FLOYD'S TORTOISE AND HARE
//         //         (Cycle Detection using Two Pointers)
//         // ============================================================
//         // The core IDEA is:
//         //   "If there is a cycle in the linked list, a fast pointer
//         //    moving at 2x speed will EVENTUALLY LAP the slow pointer
//         //    moving at 1x speed — just like a faster runner on a
//         //    circular track will eventually catch up to a slower one."
//         //
//         //   If there is NO cycle, the fast pointer will simply reach
//         //   the end (NULL) and we know the list is clean.
//         //
//         // 🆚 HOW IS THIS DIFFERENT FROM PREVIOUS PROBLEMS?
//         //   LC 19:   Fixed gap (n+1) → find a specific node from end.
//         //   LC 2095: Speed ratio 1:2 → find the MIDDLE of the list.
//         //   LC 160:  Length alignment → find intersection of TWO lists.
//         //   LC 141:  Speed ratio 1:2 → detect if a CYCLE exists.
//         //
//         //   LC 2095 and LC 141 use the SAME speed ratio (1:2), but:
//         //   → LC 2095: Loop until fast reaches NULL (no cycle assumed).
//         //   → LC 141:  Loop until fast reaches NULL OR slow meets fast.
//         //     The MEETING is the signal, not the end!
//         // ============================================================

//         // 🔹 STEP 1: Initialize both pointers at the head
//         //
//         // ⚠️ ATOMIC DETAIL #1 — Why do both start at the SAME position?
//         //    In LC 19, we created a GAP of (n+1) between slow and fast.
//         //    Here, we DON'T need any gap. We want them to MEET.
//         //    Starting together is fine because:
//         //    → On the first iteration, fast moves 2 steps and slow moves 1.
//         //    → They immediately separate (gap = 1). No false positive.
//         //    → If we checked `slow == fast` BEFORE moving, we'd get a
//         //      false positive on the very first check (both at head)!
//         //      That's why the check is AFTER the movement. ✅
//         //
//         // ⚠️ ATOMIC DETAIL #2 — What if head is NULL?
//         //    If head == NULL, then slow = NULL and fast = NULL.
//         //    The while condition `fast != NULL` fails immediately.
//         //    We skip the loop and return false. Correct! ✅
//         //    (An empty list has no cycle.)
//         ListNode* slow = head;  // 🐢 Tortoise — moves 1 step per iteration
//         ListNode* fast = head;  // 🐇 Hare — moves 2 steps per iteration

//         // 🔹 STEP 2: Traverse the list with different speeds
//         //
//         // ⚠️ ATOMIC DETAIL #3 — The loop condition is CRITICAL:
//         //    `fast != NULL && fast->next != NULL`
//         //
//         //    Why BOTH checks? Let's break it down:
//         //
//         //    → `fast != NULL`:
//         //      Handles ODD-length lists (no cycle). Fast lands exactly
//         //      on the last node. If we tried `fast->next->next`, we'd
//         //      need fast->next to exist first. But wait — this check
//         //      alone isn't enough because...
//         //
//         //    → `fast->next != NULL`:
//         //      Handles EVEN-length lists (no cycle). Fast would jump
//         //      PAST the last node and become NULL. Without this check,
//         //      `fast->next->next` inside the loop would cause a
//         //      SEGFAULT (null pointer dereference). 💥
//         //
//         //    Together, they guarantee that `fast->next->next` is SAFE
//         //    to execute inside the loop body.
//         //
//         //    Visual (no cycle, list = 1→2→3→4→NULL):
//         //      Iter 1: slow=2, fast=3  ✅ (fast=3, fast->next=4, both valid)
//         //      Iter 2: slow=3, fast=NULL ✅ (fast->next was 4, fast->next->next=NULL)
//         //      Now fast == NULL → loop stops → return false ✅
//         //
//         //    Visual (no cycle, list = 1→2→3→NULL):
//         //      Iter 1: slow=2, fast=3  ✅ (fast=3, fast->next=NULL → STOP)
//         //      Loop condition fails because fast->next == NULL → return false ✅
//         //
//         while (fast != NULL && fast->next != NULL) {

//             slow = slow->next;          // 🐢 Tortoise: 1 step forward
//             fast = fast->next->next;    // 🐇 Hare: 2 steps forward (double speed!)

//             // 🔹 STEP 3: Check if they've met
//             //
//             // ⚠️ ATOMIC DETAIL #4 — Why check AFTER moving, not before?
//             //    If we checked before moving, on the very first iteration
//             //    both slow and fast are at head → slow == fast → true.
//             //    That would be a FALSE POSITIVE (every list would appear
//             //    to have a cycle). By checking AFTER movement, they've
//             //    already separated, so a match means a REAL cycle. ✅
//             //
//             // ⚠️ ATOMIC DETAIL #5 — Why is `slow == fast` (address check)?
//             //    Just like LC 160, we compare POINTER ADDRESSES, not values.
//             //    Two different nodes could have the same value but be
//             //    completely separate in memory. A cycle means the SAME
//             //    physical node is visited again — same memory address.
//             //
//             // ⚠️ ATOMIC DETAIL #6 — WHY are they GUARANTEED to meet
//             //    if a cycle exists? (The math intuition)
//             //
//             //    Think of it like a circular running track:
//             //    → The hare is 1 step faster than the tortoise per iteration.
//             //    → The gap between them SHRINKS by 1 each iteration.
//             //    → In a cycle of length C, the maximum gap is C-1.
//             //    → So within at most C iterations, the gap becomes 0.
//             //    → Gap = 0 means they're on the same node → MEET! ✅
//             //
//             //    Why not 3x speed? Or 4x?
//             //    → 2x works because the gap reduces by exactly 1 each step.
//             //      This guarantees they meet at some point (gap hits 0).
//             //    → 3x speed: gap reduces by 2 each step. If cycle length
//             //      is even, the gap might "jump over" 0 (e.g., 2→0 ✅,
//             //      but 3→1→-1 ❌ missed!). So 2x is the SAFEST choice.
//             //    → In an interview: "2x speed guarantees the gap closes
//             //      by exactly 1 each step, ensuring they always meet."
//             //
//             if (slow == fast) {
//                 return true;  // 🎯 CYCLE DETECTED! They met inside the loop.
//             }
//         }

//         // 🔹 STEP 4: If we exit the loop, fast reached the end
//         //
//         // ⚠️ ATOMIC DETAIL #7 — What does reaching here mean?
//         //    The loop only exits when `fast == NULL` or `fast->next == NULL`.
//         //    This means fast reached the END of the list (a tail node
//         //    pointing to NULL). A list with a cycle has NO end — it
//         //    loops forever. So if fast found an end, there's NO cycle.
//         //
//         //    Think of it this way:
//         //    → Cycle exists: fast runs forever in the loop, eventually
//         //      catches slow → returns true from inside the loop.
//         //    → No cycle: fast reaches the finish line (NULL) → we get
//         //      here → return false.
//         return false;  // ✅ No cycle — the list has a proper end.
//     }
// };

// // ================================================================
// // 📝 DETAILED SUMMARY FOR REVISION
// // ================================================================
// //
// // 🎯 PROBLEM:
// //    Given the head of a linked list, determine if it has a cycle.
// //    A cycle exists if some node's `next` pointer points back to a
// //    previous node in the list (creating an infinite loop).
// //
// // 🧩 PATTERN USED: Floyd's Cycle Detection (Tortoise and Hare)
// //    Named after Robert Floyd — one of the most elegant algorithms
// //    in computer science!
// //
// // 🏠 REAL-LIFE ANALOGY:
// //    Imagine two runners on a track:
// //
// //    SCENARIO 1 — Straight road (no cycle):
// //      The fast runner (hare) will reach the finish line first and
// //      stop. The slow runner (tortoise) is still somewhere behind.
// //      They never meet after the start. → No cycle.
// //
// //    SCENARIO 2 — Circular track (cycle exists):
// //      There is no finish line! The hare keeps lapping the tortoise.
// //      Since the hare gains exactly 1 step per round, it will
// //      EVENTUALLY catch up to the tortoise from behind. When they
// //      bump into each other → Cycle detected!
// //
// //    It's like being on a highway vs. a roundabout:
// //    → Highway: the fast car exits first (NULL) → no cycle.
// //    → Roundabout: the fast car keeps circling and eventually
// //      catches the slow car → cycle!
// //
// // 📌 STEP-BY-STEP RECIPE:
// //    1. Start slow and fast both at head.
// //    2. Loop while fast and fast->next are not NULL:
// //       a. Move slow by 1 step.
// //       b. Move fast by 2 steps.
// //       c. If slow == fast → return true (cycle!).
// //    3. If loop exits → return false (no cycle, fast hit NULL).
// //
// // ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
// //    ☐ Loop condition MUST have BOTH `fast != NULL` AND `fast->next != NULL`.
// //      → Missing `fast->next` check = SEGFAULT on even-length lists.
// //      → Missing `fast` check = crash on odd-length lists.
// //    ☐ Check `slow == fast` AFTER moving, NOT before.
// //      → Checking before = false positive on first iteration (both at head).
// //    ☐ Use `==` on pointers (addresses), NOT on `->val` (values).
// //      → Same value ≠ same node. Cycle = same physical node.
// //    ☐ Fast moves EXACTLY 2 steps (not 3, not 4).
// //      → 2x guarantees gap closes by 1 each step → always meets.
// //      → 3x+ can "skip over" the meeting point in certain cycle lengths.
// //    ☐ No need to handle head == NULL separately — the while condition
// //      catches it naturally (fast == NULL → loop doesn't execute → false).
// //    ☐ The `if(slow == fast)` check is INSIDE the while loop.
// //      → Placing it outside would only check once — useless.
// //
// // 🔗 COMPARISON WITH ALL PREVIOUS PROBLEMS:
// //    ┌──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐
// //    │    Aspect    │ LC 19        │ LC 2095      │ LC 160       │ LC 141       │
// //    │              │ (Nth End)    │ (Mid Delete) │ (Intersect)  │ (Cycle)      │
// //    ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
// //    │ Lists        │ 1            │ 1            │ 2            │ 1            │
// //    │ Pointers     │ 2 (s, f)     │ 3 (p, s, f)  │ 2 (tA, tB)   │ 2 (s, f)     │
// //    │ Speed        │ Same (1:1)   │ 1:2          │ Same (1:1)   │ 1:2          │
// //    │ Gap          │ Fixed (n+1)  │ Growing      │ Length diff  │ Shrinking    │
// //    │ Stop when    │ fast = NULL  │ fast = NULL  │ tA == tB     │ s == f       │
// //    │ Goal         │ Predecessor  │ Middle node  │ Merge point  │ Cycle? T/F   │
// //    │ Return       │ ListNode*    │ ListNode*    │ ListNode*    │ bool         │
// //    │ Key trick    │ Pre-create   │ 2x speed     │ Align by     │ 2x speed     │
// //    │              │ gap          │ finds mid    │ length       │ catches up   │
// //    │ Edge case    │ Delete head  │ 1-node list  │ No intersect │ Empty list   │
// //    └──────────────┴──────────────┴──────────────┴──────────────┴──────────────┘
// //
// //    🔑 KEY OBSERVATION:
// //    LC 2095 and LC 141 use the EXACT SAME pointer movement (1:2 speed).
// //    The ONLY difference is the STOP CONDITION:
// //    → LC 2095: Stop when fast reaches NULL (assume no cycle).
// //    → LC 141:  Stop when slow meets fast (cycle!) OR fast hits NULL (no cycle).
// //    This shows how the SAME technique solves DIFFERENT problems!
// //
// // ⏱️ TIME COMPLEXITY: O(N) where N = number of nodes in the list
// //    → No cycle: fast traverses the list once → O(N).
// //    → Cycle exists: fast enters the cycle and catches slow within
// //      at most one full lap of the cycle → O(N + C) where C = cycle length.
// //      Since C ≤ N, total is O(N).
// //    → Interview answer: "Linear time, O(N). The fast pointer covers
// //      at most 2N steps before meeting slow or reaching the end."
// //
// // 💾 SPACE COMPLEXITY: O(1)
// //    → Only two pointer variables (slow and fast).
// //    → No hash set, no visited array, no recursion.
// //    → Interview answer: "Constant space, O(1)."
// //
// // 🎤 INTERVIEW FOLLOW-UP QUESTIONS TO PREPARE FOR:
// //
// //    Q1: "Can you solve it with O(1) space?"
// //    → YES! This solution already uses O(1). The alternative (hash set
// //      to track visited nodes) uses O(N) space. Mention both approaches.
// //
// //    Q2: "Why does 2x speed work? Why not 3x?"
// //    → 2x: gap shrinks by 1 each step → guaranteed to hit 0.
// //    → 3x: gap shrinks by 2 → might skip over 0 (e.g., gap 3→1→-1).
// //    → 2x is the minimum speed ratio that guarantees detection.
// //
// //    Q3: "How would you find the START of the cycle?" (LC 142!)
// //    → After slow and fast meet, reset one pointer to head.
// //    → Move both at 1x speed. They'll meet at the cycle entrance!
// //    → (This is a famous follow-up — worth practicing!)
// //
// //    Q4: "What if the list has only 1 or 2 nodes?"
// //    → 1 node, no cycle: fast->next == NULL → loop doesn't run → false ✅
// //    → 1 node, self-cycle (1→1): Iter 1: slow=1, fast=1 → meet → true ✅
// //    → 2 nodes, no cycle: fast->next->next = NULL → fast becomes NULL → false ✅
// //    → 2 nodes, cycle (1→2→1): Iter 1: slow=2, fast=1 → not equal.
// //      Iter 2: slow=1, fast=1 → meet → true ✅
// // ================================================================