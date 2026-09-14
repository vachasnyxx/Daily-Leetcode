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
//     ListNode* deleteMiddle(ListNode* head) {
//         if (head == NULL || head->next == NULL) {
//             return NULL;
//         }
//         ListNode* prevslow = NULL;
//         ListNode* slow = head;
//         ListNode* fast = head;

//         while(fast != NULL && fast->next != NULL){
//             prevslow = slow;
//             slow= slow->next;
//             fast  = fast->next->next;
//         }
//         prevslow->next = slow->next;
//         delete(slow);
//         return head;
//     }
// };




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
    ListNode* deleteMiddle(ListNode* head) {

        // ============================================================
        // 🧠 INTUITION & PATTERN: FAST & SLOW POINTER (TORTOISE & HARE)
        // ============================================================
        // The core IDEA is:
        //   "If one pointer moves TWICE as fast as the other,
        //    by the time the fast pointer reaches the END of the list,
        //    the slow pointer will be exactly at the MIDDLE."
        //
        // Why does this work?
        //   Think of it like a race track. If the hare runs at 2x speed
        //   and the tortoise at 1x speed, when the hare finishes the
        //   full lap, the tortoise is exactly at the halfway mark.
        //
        // 🆚 HOW IS THIS DIFFERENT FROM LEETCODE 19 (Remove Nth From End)?
        //   In LC 19: We KNEW the target position (nth from end), so we
        //              created a FIXED GAP of (n+1) and maintained it.
        //   In LC 2095: We DON'T know the middle position in advance.
        //               We DISCOVER it dynamically using the 2x speed trick.
        //               No fixed gap — the gap grows naturally.
        // ============================================================

        // 🔹 STEP 0: Handle EDGE CASES
        //
        // ⚠️ ATOMIC DETAIL #1 — Why check head->next == NULL?
        //    If the list has 0 nodes (head == NULL): nothing to delete.
        //    If the list has 1 node (head->next == NULL): the ONLY node
        //    IS the middle. Deleting it means returning an empty list (NULL).
        //    For 2+ nodes, the middle always exists and is not the head
        //    (for even length, it's the 2nd of the two middles).
        //
        //    Example: [1] → middle is 1 → delete it → return NULL
        //             [1,2] → middle is 2 (index 1) → delete → return [1]
        if (head == NULL || head->next == NULL) {
            return NULL;  // 🚨 List is empty or has only one node
        }

        // 🔹 STEP 1: Initialize THREE pointers
        //
        // ⚠️ ATOMIC DETAIL #2 — Why do we need THREE pointers here
        //    but only TWO in LeetCode 19?
        //
        //    In LC 19, we created a gap of (n+1) AHEAD OF TIME, so 'slow'
        //    naturally landed on the PREDECESSOR of the target. No extra
        //    pointer needed.
        //
        //    Here, we DON'T know where the middle is until the loop ends.
        //    When the loop ends, 'slow' is ON the middle node (the target).
        //    But to DELETE a node in a singly linked list, we need to be
        //    at its PREDECESSOR. Since we can't go backwards, we must
        //    TRACK the predecessor as we go → that's 'prevslow'!
        //
        //    🐢 prevslow = one step behind slow (the predecessor)
        //    🐢 slow       = moves 1 step at a time (will land on middle)
        //    🐇 fast       = moves 2 steps at a time (will reach the end)
        ListNode* prevslow = NULL;  // Tracks the node BEFORE slow
        ListNode* slow = head;      // 🐢 Tortoise — 1x speed
        ListNode* fast = head;      // 🐇 Hare — 2x speed

        // 🔹 STEP 2: Move pointers until fast reaches the end
        //
        // ⚠️ ATOMIC DETAIL #3 — The loop condition is CRITICAL:
        //    `fast != NULL && fast->next != NULL`
        //
        //    Why BOTH checks?
        //    → `fast != NULL`:     Handles ODD-length lists.
        //                          Fast lands exactly on the last node,
        //                          then fast->next is NULL → loop stops.
        //                          Slow is at the true middle. ✅
        //
        //    → `fast->next != NULL`: Handles EVEN-length lists.
        //                          Fast would go PAST the last node
        //                          (fast becomes NULL). Without this check,
        //                          `fast->next->next` would CRASH (segfault).
        //                          Slow lands on the 2nd middle. ✅
        //
        //    Visual walkthrough:
        //
        //    ODD  [1 → 2 → 3 → 4 → 5]:
        //      Start:  p=NULL  s=1  f=1
        //      Iter 1: p=1     s=2  f=3
        //      Iter 2: p=2     s=3  f=5  → fast->next == NULL → STOP
        //      Middle = 3 ✅  Predecessor = 2 ✅
        //
        //    EVEN [1 → 2 → 3 → 4]:
        //      Start:  p=NULL  s=1  f=1
        //      Iter 1: p=1     s=2  f=3
        //      Iter 2: p=2     s=3  f=NULL → fast == NULL → STOP
        //      Middle = 3 ✅  Predecessor = 2 ✅
        //      (For even length, LeetCode defines middle as the 2nd one)
        //
        while (fast != NULL && fast->next != NULL) {
            prevslow = slow;          // 📌 Save current slow BEFORE moving it
            slow = slow->next;        // 🐢 Tortoise: 1 step
            fast = fast->next->next;  // 🐇 Hare: 2 steps (double speed!)
        }

        // ✅ After the loop:
        //    - 'slow' is ON the middle node (the one we want to delete)
        //    - 'prevslow' is the node RIGHT BEFORE the middle
        //    - 'fast' is at or past the end of the list

        // 🔹 STEP 3: Delete the middle node
        //
        // ⚠️ ATOMIC DETAIL #4 — The deletion rewiring
        //    We bypass 'slow' by connecting prevslow directly to
        //    whatever comes AFTER slow. This removes 'slow' from the chain.
        //
        //    Before:  ... → prevslow → slow → slow->next → ...
        //    After:   ... → prevslow ──────────→ slow->next → ...
        //
        //    Why is prevslow guaranteed to be non-NULL here?
        //    Because we already handled the 0-node and 1-node cases
        //    at the top. For 2+ nodes, the loop runs at least once,
        //    so prevslow gets assigned at least once. ✅
        prevslow->next = slow->next;

        // ⚠️ ATOMIC DETAIL #5 — Memory cleanup
        //    `delete(slow)` frees the memory of the removed node.
        //    LeetCode doesn't strictly require this (their judge ignores it),
        //    but in a REAL interview or production code, you MUST free
        //    the memory to avoid memory leaks. Mentioning this earns
        //    bonus points in interviews! 💯
        delete(slow);

        // 🔹 STEP 4: Return the head
        //
        // ⚠️ ATOMIC DETAIL #6 — The head never changes here.
        //    Why? Because the edge case where the head IS the middle
        //    (single-node list) is already handled at the top (returns NULL).
        //    For 2+ nodes, the middle is never the head, so head stays valid.
        //    (Contrast with LC 19, where head COULD be the target and we
        //     had to handle it inside the loop.)
        return head;
    }
};

// ================================================================
// 📝 DETAILED SUMMARY FOR REVISION
// ================================================================
//
// 🎯 PROBLEM:
//    Given a linked list, delete the MIDDLE node and return the head.
//    For even-length lists, the middle is the 2nd of the two middle nodes.
//    (e.g., [1,2,3,4] → middle is 3, not 2)
//
// 🧩 PATTERN USED: Two Pointers — "Tortoise and Hare" (Speed Ratio 1:2)
//
// 🏠 REAL-LIFE ANALOGY:
//    Imagine you're on a train with an unknown number of carriages.
//    You want to find the exact middle carriage, but you can't count
//    them all first (that would be two passes).
//
//    So you send your friend running through the carriages at DOUBLE
//    your speed. You walk 1 carriage at a time; they sprint 2.
//    When your friend falls off the end of the train, you know you're
//    standing in the middle carriage. Your buddy who was walking one
//    step behind you (prevslow) is in the carriage just before the
//    middle — they unhook the middle carriage, and you're done!
//
// 📌 STEP-BY-STEP RECIPE:
//    1. Edge case: if list has 0 or 1 node → return NULL.
//    2. Set up three pointers: prevslow (NULL), slow (head), fast (head).
//    3. Loop while fast and fast->next are not NULL:
//       → prevslow = slow (track predecessor)
//       → slow moves 1 step
//       → fast moves 2 steps
//    4. When loop ends, slow is at the middle.
//    5. Delete: prevslow->next = slow->next.
//    6. Free memory: delete(slow).
//    7. Return head.
//
// ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
//    ☐ Edge case for 0 and 1 node lists — MUST return NULL early.
//    ☐ Need THREE pointers (prevslow, slow, fast), not just two.
//      Without prevslow, you can't delete because you can't go backwards.
//    ☐ Loop condition: `fast != NULL && fast->next != NULL`
//      → Missing `fast->next` check = segfault on even-length lists.
//      → Missing `fast` check = infinite loop / crash on odd-length.
//    ☐ Order inside loop matters: update prevslow BEFORE moving slow!
//      If you move slow first, prevslow would be one step too far.
//    ☐ `delete(slow)` is good practice for real code / interviews.
//    ☐ Head never changes for 2+ nodes (unlike LC 19).
//
// 🔗 COMPARISON WITH LEETCODE 19 (Remove Nth From End):
//    ┌─────────────┬──────────────────────┬──────────────────────────┐
//    │   Aspect    │  LC 19 (Nth from End)│  LC 2095 (Middle)        │
//    ├─────────────┼──────────────────────┼──────────────────────────┤
//    │ Target      │ Known (nth from end) │ Unknown (middle)         │
//    │ Technique   │ Fixed gap of (n+1)   │ Speed ratio 1:2          │
//    │ Pointers    │ 2 (slow, fast)       │ 3 (prev, slow, fast)     │
//    │ Gap         │ Created upfront      │ Grows naturally          │
//    │ Head delete │ Handled in loop      │ Handled before loop      │
//    │ Loop cond.  │ fast != NULL         │ fast && fast->next       │
//    └─────────────┴──────────────────────┴──────────────────────────┘
//
// ⏱️ TIME COMPLEXITY: O(N) where N = length of the linked list
//    → 'fast' traverses the entire list in one pass.
//    → 'slow' traverses half the list.
//    → Total work is proportional to N → O(N).
//    → Interview answer: "Single pass, O(N) time."
//
// 💾 SPACE COMPLEXITY: O(1)
//    → Only three pointer variables (prevslow, slow, fast).
//    → No arrays, no hash maps, no recursion.
//    → Interview answer: "Constant extra space, O(1)."
//
// 🎤 INTERVIEW TIP:
//    If asked "Can you do it without prevslow?", you can use the
//    DUMMY NODE trick: start slow at a dummy node before head.
//    Then slow naturally becomes the predecessor when the loop ends.
//    This unifies the logic and avoids the extra pointer.
//    (But your current 3-pointer approach is perfectly valid and clear!)
// ================================================================