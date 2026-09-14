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
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//         ListNode* tempA = headA;
//         ListNode* tempB = headB;
//         int lenA = 0;
//         while(tempA != NULL){
//             lenA++;
//             tempA = tempA->next;
//         }
//         int lenB = 0;
//         while(tempB != NULL){
//             lenB++;
//             tempB = tempB->next;
//         }

//         tempA = headA;
//         tempB = headB;

//         if(lenA > lenB){
//             int diff = lenA - lenB;
//             for(int i = 1; i<= diff; i++){
//                 tempA = tempA->next;
//             }
//             while(tempA != tempB){
//                 tempA = tempA->next;
//                 tempB = tempB->next;
//             }
//             return tempA;
//         }
//         else{ // lena <= lenB
//             int diff = lenB - lenA;
//             for(int i = 1; i<= diff; i++){
//                 tempB = tempB->next;
//             }
//             while(tempA != tempB){
//                 tempA = tempA->next;
//                 tempB = tempB->next;
//             }
//             return tempA;
//         }
//     }
// };





/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

        // ============================================================
        // 🧠 INTUITION & PATTERN: LENGTH-DIFFERENCE ALIGNMENT
        // ============================================================
        // The core IDEA is:
        //   "If two linked lists intersect, they share a COMMON TAIL.
        //    The only difference is how much 'extra' each list has
        //    BEFORE the intersection point. If we SKIP that extra
        //    portion in the longer list, both pointers will be at
        //    equal distance from the end — and we can walk them
        //    together to find where they meet."
        //
        // 🆚 HOW IS THIS DIFFERENT FROM LC 19 & LC 2095?
        //   LC 19:  Two pointers with a FIXED GAP (n+1) on ONE list.
        //   LC 2095: Two pointers with a SPEED RATIO (1:2) on ONE list.
        //   LC 160:  Two pointers on TWO DIFFERENT lists, aligned by
        //            LENGTH DIFFERENCE so they reach the end together.
        //
        //   All three use two pointers, but the RELATIONSHIP between
        //   the pointers is different each time!
        // ============================================================

        // 🔹 STEP 1: Calculate the LENGTH of both linked lists
        //
        // ⚠️ ATOMIC DETAIL #1 — Why do we need lengths?
        //    The two lists can have different lengths before they merge.
        //    Example:
        //      List A:  4 → 1 ─┐
        //                       → 8 → 4 → 5   (lenA = 5)
        //      List B:  5 → 6 → 1 ┘            (lenB = 4... wait, 5→6→1→8→4→5 = 6)
        //
        //    Actually let me redraw properly:
        //      List A:  4 → 1 ──────→ 8 → 4 → 5 → NULL   (lenA = 5)
        //      List B:  5 → 0 → 6 → 1 ┘                   (lenB = 4... no)
        //
        //    Cleaner example:
        //      List A:  a1 → a2 ──→ c1 → c2 → c3 → NULL   (lenA = 5)
        //      List B:  b1 → b2 → b3 ──→ c1 → c2 → c3 → NULL   (lenB = 6)
        //                          ↑
        //                     intersection at c1
        //
        //    The "extra" part: List B has 3 nodes before c1, List A has 2.
        //    Difference = 1. If we skip 1 node in B, both are 2 nodes from c1.
        //
        //    Without knowing lengths, we wouldn't know how much to skip!
        //
        // ⚠️ ATOMIC DETAIL #2 — We use TEMPORARY pointers (tempA, tempB)
        //    because we don't want to lose the original headA and headB.
        //    If we moved headA directly, we'd lose the start of the list!
        ListNode* tempA = headA;  // 📏 Will traverse list A to count length
        ListNode* tempB = headB;  // 📏 Will traverse list B to count length

        int lenA = 0;
        while (tempA != NULL) {
            lenA++;               // Count each node
            tempA = tempA->next;  // Move to next
        }
        // ✅ After this: lenA = total nodes in list A, tempA = NULL

        int lenB = 0;
        while (tempB != NULL) {
            lenB++;               // Count each node
            tempB = tempB->next;  // Move to next
        }
        // ✅ After this: lenB = total nodes in list B, tempB = NULL

        // 🔹 STEP 2: Reset pointers back to the heads
        //
        // ⚠️ ATOMIC DETAIL #3 — Why reset?
        //    After counting, tempA and tempB are both NULL (end of lists).
        //    We need them back at the start to do the actual intersection search.
        tempA = headA;  // 🔄 Reset to beginning of list A
        tempB = headB;  // 🔄 Reset to beginning of list B

        // 🔹 STEP 3: Align the pointers by skipping the "extra" nodes
        //            in the LONGER list
        //
        // ⚠️ ATOMIC DETAIL #4 — The ALIGNMENT trick (most important part!)
        //    After the intersection point, both lists share the SAME nodes.
        //    So the distance from the intersection to the end is IDENTICAL
        //    for both lists. The only difference is BEFORE the intersection.
        //
        //    If lenA = 5 and lenB = 3, then list A has 2 extra nodes
        //    before the shared portion. We skip those 2 nodes in A.
        //    Now both pointers are equidistant from the end, and we can
        //    walk them in lockstep to find the meeting point.
        //
        //    Visual:
        //      List A:  a1 → a2 → [c1 → c2 → c3 → NULL]   lenA = 5
        //      List B:            [c1 → c2 → c3 → NULL]   lenB = 3
        //                          ↑
        //                     intersection
        //
        //      diff = 5 - 3 = 2. Skip 2 nodes in A:
        //      tempA starts at a1 → skip a1 → skip a2 → now at c1 ✅
        //      tempB starts at c1 → already at c1 ✅
        //      Both are aligned! Walk together → they match at c1.
        //
        if (lenA > lenB) {
            // List A is longer → skip the extra nodes in A
            int diff = lenA - lenB;  // How many extra nodes A has
            for (int i = 1; i <= diff; i++) {
                tempA = tempA->next;  // 🏃 Advance only tempA
            }
            // ✅ Now tempA and tempB are equidistant from the end

            // 🔹 STEP 4: Walk both pointers together until they meet
            //
            // ⚠️ ATOMIC DETAIL #5 — Why `tempA != tempB` and not
            //    `tempA->val != tempB->val`?
            //    Intersection is defined by REFERENCE (memory address),
            //    NOT by value! Two nodes can have the same value but be
            //    completely different nodes in memory.
            //    `tempA != tempB` compares the actual pointer addresses.
            //    When they point to the SAME node in memory → intersection!
            //
            // ⚠️ ATOMIC DETAIL #6 — What if there's NO intersection?
            //    Both pointers will eventually reach NULL at the same time
            //    (because they're equidistant from the end).
            //    NULL == NULL is true, so the loop stops and we return NULL.
            //    This is CORRECT — no intersection means return NULL. ✅
            while (tempA != tempB) {
                tempA = tempA->next;  // 🚶 Step in list A
                tempB = tempB->next;  // 🚶 Step in list B (same speed!)
            }
            // ✅ Loop exits when tempA == tempB
            //    Either they meet at the intersection node, or both are NULL.
            return tempA;  // Returns intersection node or NULL
        }
        else {
            // lenA <= lenB → List B is longer (or equal) → skip extra in B
            int diff = lenB - lenA;  // How many extra nodes B has
            for (int i = 1; i <= diff; i++) {
                tempB = tempB->next;  // 🏃 Advance only tempB
            }
            // ✅ Now tempA and tempB are equidistant from the end

            // Same logic as above — walk together until they meet
            while (tempA != tempB) {
                tempA = tempA->next;
                tempB = tempB->next;
            }
            return tempA;  // Returns intersection node or NULL
        }

        // ⚠️ ATOMIC DETAIL #7 — Code duplication observation:
        //    Notice that the while loop inside if and else is IDENTICAL.
        //    You could simplify by aligning first, then having ONE loop:
        //
        //      // Align
        //      while(lenA > lenB) { tempA = tempA->next; lenA--; }
        //      while(lenB > lenA) { tempB = tempB->next; lenB--; }
        //      // Find intersection
        //      while(tempA != tempB) { tempA = tempA->next; tempB = tempB->next; }
        //      return tempA;
        //
        //    Your version works perfectly fine though! This is just a
        //    cleaner way to write it. Mention this in interviews to show
        //    you can refactor. 💯
    }
};

// ================================================================
// 📝 DETAILED SUMMARY FOR REVISION
// ================================================================
//
// 🎯 PROBLEM:
//    Given heads of two singly linked lists, find the node where
//    they INTERSECT (by reference/memory address). If no intersection,
//    return NULL. The lists retain their original structure after.
//
// 🧩 PATTERN USED: Two Pointers — "Length-Difference Alignment"
//
// 🏠 REAL-LIFE ANALOGY:
//    Imagine two hiking trails that eventually MERGE into a single
//    path leading to a summit. Trail A is 5 km long, Trail B is 3 km.
//    The last 2 km are shared (the merged portion).
//
//    You and your friend want to find the EXACT merge point.
//    You start at Trail A's entrance, your friend at Trail B's.
//    But Trail A is 2 km longer before the merge, so you walk 2 km
//    alone first. NOW you're both the same distance from the summit.
//    You both walk at the same pace, and the moment you see each
//    other on the same path — that's the merge point!
//
//    If the trails never merge, you'll both reach dead ends (NULL)
//    at the same time and realize there's no intersection.
//
// 📌 STEP-BY-STEP RECIPE:
//    1. Traverse list A to count lenA.
//    2. Traverse list B to count lenB.
//    3. Reset both pointers to their respective heads.
//    4. Calculate diff = |lenA - lenB|.
//    5. Advance the pointer of the LONGER list by 'diff' steps.
//    6. Walk both pointers one step at a time.
//    7. When they point to the SAME node (or both NULL) → return it.
//
// ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
//    ☐ Intersection is by REFERENCE (address), NOT by value.
//      → Use `tempA != tempB`, never `tempA->val != tempB->val`.
//    ☐ Use temporary pointers for counting — don't destroy headA/headB.
//    ☐ Reset tempA and tempB to heads AFTER counting (they'll be NULL).
//    ☐ Align the LONGER list, not the shorter one.
//    ☐ No intersection case: both reach NULL simultaneously → return NULL.
//    ☐ The if-else branches can be unified (cleaner code, same logic).
//    ☐ After the intersection, lists share the SAME tail — they can't
//      diverge again (singly linked list, each node has only one next).
//
// 🔗 COMPARISON WITH LC 19 & LC 2095:
//    ┌──────────────┬──────────────────┬──────────────────┬──────────────────┐
//    │    Aspect    │ LC 19            │ LC 2095          │ LC 160           │
//    │              │ (Nth from End)   │ (Delete Middle)  │ (Intersection)   │
//    ├──────────────┼──────────────────┼──────────────────┼──────────────────┤
//    │ Lists        │ 1 list           │ 1 list           │ 2 lists          │
//    │ Pointers     │ 2 (slow, fast)   │ 3 (prev,s,f)     │ 2 (tempA, tempB) │
//    │ Technique    │ Fixed gap (n+1)  │ Speed ratio 1:2  │ Length alignment │
//    │ Goal         │ Find predecessor │ Find middle      │ Find merge point │
//    │ Key trick    │ Gap = n+1        │ fast = 2x slow   │ Skip diff nodes  │
//    │ Edge case    │ Delete head      │ 1-node list      │ No intersection  │
//    │ Passes       │ ~1 pass          │ 1 pass           │ 3 passes*        │
//    └──────────────┴──────────────────┴──────────────────┴──────────────────┘
//    * 3 passes: count A, count B, then walk together.
//
// ⏱️ TIME COMPLEXITY: O(M + N) where M = lenA, N = lenB
//    → Pass 1: Traverse list A → O(M)
//    → Pass 2: Traverse list B → O(N)
//    → Pass 3: Walk together → O(max(M, N)) in worst case
//    → Total: O(M + N) — linear in the combined length.
//    → Interview answer: "Linear time, O(M + N)."
//
// 💾 SPACE COMPLEXITY: O(1)
//    → Only a few integer variables and two pointers.
//    → No hash sets, no arrays, no extra data structures.
//    → Interview answer: "Constant space, O(1)."
//
// 🎤 INTERVIEW BONUS — The "Elegant" Two-Pointer Approach:
//    There's a famous O(M+N) / O(1) solution that does it in 2 passes
//    WITHOUT counting lengths:
//
//      ListNode *a = headA, *b = headB;
//      while (a != b) {
//          a = (a == NULL) ? headB : a->next;
//          b = (b == NULL) ? headA : b->next;
//      }
//      return a;
//
//    How? When 'a' finishes list A, it jumps to head B (and vice versa).
//    By the time they switch, the length difference is automatically
//    compensated! Both travel exactly (M + N) steps and meet at the
//    intersection (or both hit NULL). It's like running two laps on
//    different tracks that share a final stretch — you'll sync up!
//
//    Your length-difference approach is equally valid and arguably
//    MORE READABLE. In an interview, solve with your approach first,
//    then mention this as an optimization. Interviewers love that! 💯
// ================================================================