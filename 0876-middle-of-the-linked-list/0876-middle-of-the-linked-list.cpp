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
//     ListNode* middleNode(ListNode* head) {
//         int len = 0;
//         ListNode* temp = head;

//         while(temp != NULL){
//             len++;
//             temp= temp->next;
//         }

//         int midIdx = len/2;
//         ListNode* mid = head;
//         for(int i = 1; i<= midIdx; i++){
//             mid = mid->next;
//         }
//         return mid;

//     }
// };





// class Solution {
// public:
//     ListNode* middleNode(ListNode* head) {
//         ListNode* slow = head;
//         ListNode* fast = head;

//         while(fast != NULL && fast->next != NULL){
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         return slow;
//     }
// };





// class Solution {
// public:
//     ListNode* middleNode(ListNode* head) {
//         // Initialize two pointers:
//         // 'slow' moves one step at a time
//         // 'fast' moves two steps at a time
//         ListNode* slow = head;
//         ListNode* fast = head;

//         // Loop continues as long as:
//         // 1. 'fast' is not NULL (list not fully traversed)
//         // 2. 'fast->next' is not NULL (so 'fast' can safely move two steps)
//         while(fast != NULL && fast->next != NULL){
//             // Move 'slow' one step forward
//             slow = slow->next;

//             // Move 'fast' two steps forward
//             fast = fast->next->next;
//         }

//         // When loop ends:
//         // - 'fast' has reached the end (or gone past it)
//         // - 'slow' is exactly at the middle node
//         return slow;
//     }
// };





class Solution {
public:
    ListNode* middleNode(ListNode* head) {

        // ============================================================
        // INTUITION: THE "TORTOISE AND HARE" (FAST & SLOW) PATTERN
        // ============================================================
        // Imagine two runners on a track:
        //   - Runner SLOW jogs at 1 step per second.
        //   - Runner FAST sprints at 2 steps per second.
        //
        // When FAST reaches the finish line (end of list),
        // SLOW will be EXACTLY at the halfway mark (middle).
        //
        // Why? Because distance = speed × time.
        //   FAST covers  "n" nodes  →  SLOW covers  "n/2" nodes.
        // That's the entire trick. No counting needed!
        // ============================================================

        // STEP 1: Initialize both pointers at the START of the list.
        // 🔍 ATOMIC DETAIL: Both start at 'head', NOT head->next.
        //    Starting at head ensures correct middle for BOTH
        //    even-length and odd-length lists.
        ListNode* slow = head;   // 🐢 Tortoise — moves 1 step at a time
        ListNode* fast = head;   // 🐇 Hare     — moves 2 steps at a time

        // STEP 2: Move both pointers until fast reaches the end.
        //
        // 🔍 ATOMIC DETAIL — THE WHILE CONDITION (CRITICAL!):
        //    We check TWO things, and ORDER matters:
        //
        //    1) fast != NULL
        //       → Handles EVEN-length lists.
        //         e.g., [1,2,3,4]: fast jumps past the last node → becomes NULL.
        //         If we didn't check this, fast->next would CRASH (null dereference).
        //
        //    2) fast->next != NULL
        //       → Handles ODD-length lists.
        //         e.g., [1,2,3,4,5]: fast lands exactly on the last node (5).
        //         fast->next is NULL, so fast->next->next would CRASH.
        //
        //    ⚠️ ORDER IS NON-NEGOTIABLE:
        //       'fast != NULL' MUST come FIRST because of short-circuit evaluation.
        //       If fast IS NULL, C++ won't evaluate 'fast->next', avoiding a crash.
        //       If you swap the order → SEGMENTATION FAULT on even-length lists.
        //
        while (fast != NULL && fast->next != NULL) {

            // 🐢 Slow moves ONE step forward.
            slow = slow->next;

            // 🐇 Fast moves TWO steps forward.
            // 🔍 ATOMIC DETAIL: We can safely do fast->next->next here
            //    because the while-condition already guaranteed that
            //    fast != NULL  AND  fast->next != NULL.
            fast = fast->next->next;
        }

        // STEP 3: When the loop ends, 'slow' is sitting at the middle.
        //
        // 🔍 ATOMIC DETAIL — WHAT "MIDDLE" MEANS FOR EVEN vs ODD:
        //
        //    ODD length  → [1, 2, 3, 4, 5]
        //                   slow ends at 3  ✅ (true middle)
        //                   fast ends at 5 (fast->next == NULL → loop stops)
        //
        //    EVEN length → [1, 2, 3, 4, 5, 6]
        //                   slow ends at 4  ✅ (SECOND middle, per LeetCode rule)
        //                   fast ends at NULL (fast == NULL → loop stops)
        //
        //    LeetCode 876 asks for the SECOND middle in even-length lists,
        //    and this algorithm naturally gives exactly that.
        //    (If you wanted the FIRST middle, you'd start fast at head->next.)
        //
        return slow;
    }
};

// ================================================================
// 📝 DETAILED REVISION SUMMARY (read this before interviews!)
// ================================================================
//
// PROBLEM:
//   Given a singly linked list, return the middle node.
//   If two middles exist (even length), return the SECOND one.
//
// BRUTE FORCE (what NOT to say first in interviews):
//   1st pass → count total nodes (n).
//   2nd pass → walk to node n/2.
//   Works, but it's TWO passes. We can do it in ONE.
//
// OPTIMAL — FAST & SLOW POINTER (one pass):
//   • slow moves 1 step, fast moves 2 steps.
//   • When fast hits the end, slow is at the middle.
//   • Math: if fast covers distance "d", slow covers "d/2".
//
// ANALOGY TO REMEMBER FOREVER:
//   🚗 Imagine a highway from City A to City B (100 km).
//      Car FAST drives at 100 km/h. Car SLOW drives at 50 km/h.
//      When FAST arrives at City B (1 hour), where is SLOW?
//      → At the 50 km mark. THE EXACT MIDDLE. 🎯
//
// LOOP CONDITION CHEAT SHEET:
//   while (fast != NULL && fast->next != NULL)
//          ^^^^^^^^^^^^^    ^^^^^^^^^^^^^^^^^^
//          even-length       odd-length
//          guard             guard
//
// WHAT TO RETURN:
//   return slow;   ← NOT fast. Fast is at the end. Slow is at the middle.
//
// ================================================================
// ⏱️  TIME COMPLEXITY:  O(n)
// ================================================================
//   • 'fast' traverses the entire list of n nodes.
//   • 'slow' traverses n/2 nodes.
//   • Total work = n + n/2 = 1.5n → drop constants → O(n).
//   • In an interview, just say:
//     "We visit each node at most once with the fast pointer,
//      so it's linear time, O(n)."
//
// 💾 SPACE COMPLEXITY:  O(1)
// ================================================================
//   • We only use two extra pointers: 'slow' and 'fast'.
//   • No arrays, no hash maps, no recursion stack.
//   • Memory doesn't grow with input size → constant space.
//   • In an interview, just say:
//     "We only use two pointers regardless of list size,
//      so it's constant extra space, O(1)."
//
// ================================================================
// 🔬 ATOMIC DETAILS CHECKLIST (things that trip people up):
// ================================================================
//  ✅ Both pointers start at 'head' (not head->next).
//  ✅ Loop condition checks fast != NULL FIRST (short-circuit safety).
//  ✅ Loop condition checks fast->next != NULL SECOND (avoid null->next).
//  ✅ Return 'slow', not 'fast'.
//  ✅ This returns the SECOND middle for even-length lists.
//     → To get the FIRST middle, initialize fast = head->next instead.
//  ✅ Works for single-node list: loop never runs, returns head. ✅
//  ✅ Works for two-node list: slow moves once → returns 2nd node. ✅
//  ✅ Works for NULL head? Technically yes (returns NULL), but
//     LeetCode guarantees at least 1 node in constraints.
// ================================================================