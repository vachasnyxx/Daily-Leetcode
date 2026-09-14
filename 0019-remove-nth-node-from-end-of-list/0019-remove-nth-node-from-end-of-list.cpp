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
// // class Solution {
// // public:
// //     ListNode* removeNthFromEnd(ListNode* head, int n) {
// //         int len = 0;
// //         ListNode* temp = head;
// //         while (temp != NULL) {
// //             len++;
// //             temp = temp->next;
// //         }
// //         if (n == len) {
// //             head = head->next;
// //             return head;
// //         }
// //         // nth from end = (len - n + 1)th from start
// //         temp = head;
// //         for (int i = 1; i < len - n; i++) {
// //             temp = temp->next;
// //         }
// //         temp->next = temp->next->next;
// //         return head;
// //     }
// // };



// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         ListNode* slow = head;
//         ListNode* fast = head;
//         // 1st step is to traverse fast to n+1 steps forward

//         for(int i = 1;i<=n+1;i++){
//             if(fast == NULL) return head->next;
//             fast = fast->next;
//         }
//         // move slow and fast at the same pace
//         while(fast != NULL){
//             slow = slow->next;
//             fast = fast->next;
//         }
//         // now the slow is exactly at left of the nth node from the end
//         slow->next = slow->next->next;
//         return head;
//     }
// };





class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        // ============================================================
        // 🧠 INTUITION & PATTERN: FAST & SLOW POINTER (TWO POINTERS)
        // ============================================================
        // The core IDEA is:
        //   "If I can create a GAP of exactly (n+1) between two pointers,
        //    then when the FRONT pointer hits the end (NULL),
        //    the BACK pointer will be sitting RIGHT BEFORE the node
        //    I need to delete."
        //
        // Why (n+1) and not n?
        //   Because to DELETE a node in a singly linked list, you need
        //   to stand ONE STEP BEHIND it (to rewire the .next pointer).
        //   A gap of n would land you ON the target — useless for deletion.
        //   A gap of n+1 lands you just BEFORE it — exactly what we need.
        // ============================================================

        // 🔹 STEP 0: Initialize both pointers at the head
        // Both start at the same position. We will now "stretch" the gap.
        ListNode* slow = head;   // 🐢 This will eventually sit BEFORE the target node
        ListNode* fast = head;   // 🐇 This will race ahead to create the gap

        // 🔹 STEP 1: Move 'fast' pointer (n+1) steps ahead of 'slow'
        //
        // ⚠️ ATOMIC DETAIL #1 — Why n+1 and not n?
        //    If we move fast only n steps, when fast hits NULL,
        //    slow would be ON the target node, not BEFORE it.
        //    We need slow to be at the PREDECESSOR so we can do:
        //        slow->next = slow->next->next  (skip/delete the target)
        //    So the gap must be n+1.
        //
        // ⚠️ ATOMIC DETAIL #2 — The NULL check INSIDE the loop
        //    If fast becomes NULL before we finish the n+1 steps,
        //    it means the node to remove IS the HEAD itself.
        //    Example: list = [1,2], n = 2 → remove 2nd from end = head
        //    In this case, fast goes NULL during the loop, so we
        //    simply return head->next (effectively deleting the head).
        for (int i = 1; i <= n + 1; i++) {
            if (fast == NULL) {
                // 🚨 EDGE CASE: We are removing the HEAD node.
                // This happens when n == length of the list.
                // The (n+1)th step doesn't even exist, so fast hits NULL early.
                // Returning head->next removes the first node.
                return head->next;
            }
            fast = fast->next;  // 🐇 fast races ahead one step
        }
        // ✅ After this loop:
        //    - 'fast' is (n+1) nodes ahead of 'slow'
        //    - 'slow' is still at head
        //    - The gap between them is exactly (n+1)

        // 🔹 STEP 2: Move BOTH pointers at the SAME speed (1 step each)
        //
        // ⚠️ ATOMIC DETAIL #3 — Why does this work?
        //    The gap of (n+1) is PRESERVED because both move equally.
        //    When fast reaches NULL (end of list), slow will be exactly
        //    (n+1) positions from the end → which is ONE BEFORE the
        //    nth-from-end node. That's our deletion spot!
        //
        //    Visual (list = 1→2→3→4→5, n = 2, removing node '4'):
        //
        //    After Step 1 (gap created):
        //      slow          fast
        //       ↓             ↓
        //       1 → 2 → 3 → 4 → 5 → NULL
        //
        //    After Step 2 (both move together until fast == NULL):
        //                slow        fast
        //                 ↓           ↓
        //       1 → 2 → 3 → 4 → 5 → NULL
        //                        ↑
        //                   slow is at 3 (predecessor of target 4) ✅
        while (fast != NULL) {
            slow = slow->next;   // 🐢 moves one step
            fast = fast->next;   // 🐇 moves one step (gap stays same!)
        }

        // 🔹 STEP 3: Delete the target node
        //
        // ⚠️ ATOMIC DETAIL #4 — The actual deletion
        //    slow->next is the node we want to REMOVE.
        //    slow->next->next is the node AFTER the one we remove.
        //    By pointing slow->next to slow->next->next, we "skip over"
        //    the target node, effectively removing it from the chain.
        //
        //    Before:  ... → 3 → 4 → 5 → ...
        //                     ↑    ↑
        //                   slow  target
        //    After:   ... → 3 ──────→ 5 → ...   (4 is gone!)
        slow->next = slow->next->next;

        // 🔹 STEP 4: Return the (possibly modified) head
        //
        // ⚠️ ATOMIC DETAIL #5 — Why not return slow?
        //    Because the head of the list hasn't changed (we already
        //    handled the head-removal case in Step 1). We always
        //    return the original 'head' pointer.
        return head;
    }
};

// ================================================================
// 📝 DETAILED SUMMARY FOR REVISION
// ================================================================
//
// 🎯 PROBLEM:
//    Given a linked list, remove the Nth node from the END and
//    return the head. Do it in ONE PASS if possible.
//
// 🧩 PATTERN USED: Two Pointers (Fast & Slow) — "Gap Technique"
//
// 🏠 REAL-LIFE ANALOGY:
//    Imagine you and your friend are walking on a bridge made of
//    planks (each plank = a node). You don't know how long the
//    bridge is, but you need to stand exactly 1 plank BEFORE the
//    2nd-to-last plank to fix it.
//
//    So you tell your friend: "Walk 3 planks ahead of me (n+1 = 3)."
//    Then you BOTH walk at the same speed. When your friend steps
//    OFF the bridge (NULL), you know you're standing exactly where
//    you need to be — one plank before the target. You fix it
//    (skip the plank) and you're done!
//
// 📌 STEP-BY-STEP RECIPE:
//    1. Start both pointers at head.
//    2. Move 'fast' ahead by (n+1) steps.
//       → If fast becomes NULL during this, the HEAD is the target.
//         Return head->next. (Edge case!)
//    3. Move both pointers together until fast == NULL.
//       → Now 'slow' is just BEFORE the node to delete.
//    4. Skip the target: slow->next = slow->next->next.
//    5. Return head.
//
// ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
//    ☐ Gap is (n+1), NOT n — you need the PREDECESSOR, not the target.
//    ☐ NULL check INSIDE the for-loop — handles "delete the head" case.
//    ☐ Loop condition is i <= n+1, not i < n — off-by-one errors!
//    ☐ while(fast != NULL), not while(fast->next != NULL) — because
//      the gap is already n+1, so fast hitting NULL is the right signal.
//    ☐ No dummy node needed here because the head-removal edge case
//      is handled explicitly inside the for-loop. (Alternative approach
//      uses a dummy node to unify all cases — both are valid!)
//
// ⏱️ TIME COMPLEXITY: O(L) where L = length of the linked list
//    → We traverse the list at most once.
//    → 'fast' goes L steps total, 'slow' goes (L - n - 1) steps.
//    → Combined, it's still proportional to L → O(L).
//    → In an interview, just say: "One pass through the list, so O(N)."
//
// 💾 SPACE COMPLEXITY: O(1)
//    → We only use two extra pointers (slow and fast).
//    → No extra data structures, no recursion stack.
//    → In an interview: "Constant space, just two pointers."
//
// 🆚 WHY THIS OVER OTHER APPROACHES?
//    → Brute force: Count length first, then traverse again = 2 passes.
//    → This approach: 1 pass (technically ~1.5, but still O(N)).
//    → Interviewers LOVE the one-pass two-pointer solution.
// ================================================================