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
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        bool flag = false; // no cycle
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                flag = true;
                break;
            }
        }
        if (flag == false)
            return NULL;
        else {
            ListNode* temp = head;
            while (temp != slow) {
                slow = slow->next;
                temp = temp->next;
            }
            return slow;
        }
    }
};




// class Solution {
// public:
//     ListNode* detectCycle(ListNode* head) {

//         // ============================================================
//         // 🧠 INTUITION & PATTERN: FLOYD'S CYCLE DETECTION — PHASE 2
//         //         (Finding the ENTRANCE of the Cycle)
//         // ============================================================
//         // This is the DIRECT FOLLOW-UP to LeetCode 141 (Cycle Detection).
//         //
//         // LC 141 asked: "IS there a cycle?"        → return true/false
//         // LC 142 asks:  "WHERE does the cycle START?" → return the node
//         //
//         // The algorithm has TWO PHASES:
//         //   PHASE 1: Detect IF a cycle exists (identical to LC 141).
//         //   PHASE 2: Find the EXACT ENTRANCE node of the cycle.
//         //
//         // The Phase 2 trick is one of the most BEAUTIFUL results in
//         // linked list algorithms. After the two pointers meet inside
//         // the cycle, if you reset ONE pointer to the head and move
//         // BOTH at 1x speed, they will meet EXACTLY at the cycle entrance!
//         //
//         // WHY? The math behind it (explained in detail below in Phase 2).
//         // ============================================================

//         // 🔹 PHASE 1: DETECT IF A CYCLE EXISTS
//         // ============================================================
//         // This is EXACTLY the same logic as LC 141.
//         // 🐢 slow moves 1 step, 🐇 fast moves 2 steps.
//         // If they meet → cycle exists. If fast hits NULL → no cycle.

//         ListNode* slow = head;  // 🐢 Tortoise — 1x speed
//         ListNode* fast = head;  // 🐇 Hare — 2x speed

//         // ⚠️ ATOMIC DETAIL #1 — The `flag` variable
//         //    In LC 141, we returned `true` immediately when slow == fast.
//         //    Here, we can't return yet — we still need to find the
//         //    ENTRANCE. So we use a boolean flag to remember whether
//         //    a cycle was found, then break out of the loop.
//         //
//         //    Alternative approach (without flag):
//         //      You could use a nested structure or just check after
//         //      the loop whether fast reached NULL. The flag is cleaner
//         //      and more readable — perfectly fine for interviews!
//         bool flag = false;  // 🚩 Assume no cycle initially

//         // ⚠️ ATOMIC DETAIL #2 — Same loop condition as LC 141
//         //    `fast != NULL && fast->next != NULL`
//         //    → Prevents segfault when fast jumps 2 steps.
//         //    → Handles both odd and even length lists safely.
//         //    → If no cycle, fast eventually hits NULL → loop exits.
//         while (fast != NULL && fast->next != NULL) {
//             slow = slow->next;          // 🐢 1 step
//             fast = fast->next->next;    // 🐇 2 steps

//             if (slow == fast) {
//                 flag = true;  // 🎯 Cycle detected! They met!
//                 break;        // ⛔ Stop — don't keep looping forever
//             }
//         }

//         // 🔹 TRANSITION: Check if a cycle was found
//         // ============================================================
//         //
//         // ⚠️ ATOMIC DETAIL #3 — Why check flag AFTER the loop?
//         //    The loop can exit in TWO ways:
//         //    → Way 1: `break` was hit → cycle exists → flag = true
//         //    → Way 2: `fast == NULL` or `fast->next == NULL` → no cycle
//         //      → flag remains false
//         //    We need to distinguish these two cases before Phase 2.
//         //
//         if (flag == false) {
//             // 🚫 No cycle found — fast reached the end of the list.
//             //    The list is a straight line with a proper NULL tail.
//             //    Return NULL to indicate "no cycle entrance exists."
//             return NULL;
//         }
//         else {
//             // ✅ Cycle CONFIRMED! Now we need to find WHERE it starts.
//             //    At this point:
//             //    → `slow` and `fast` are BOTH at the meeting point
//             //      somewhere INSIDE the cycle.
//             //    → `head` is still at the beginning of the list.

//             // 🔹 PHASE 2: FIND THE CYCLE ENTRANCE
//             // ============================================================
//             //
//             // 🧮 THE MATH BEHIND THE MAGIC (this is the key insight!):
//             //
//             //    Let's define three distances:
//             //      L = distance from HEAD to CYCLE ENTRANCE
//             //      C = length of the CYCLE (number of nodes in the loop)
//             //      K = distance from CYCLE ENTRANCE to MEETING POINT
//             //          (measured in the direction of traversal)
//             //
//             //    When slow and fast meet:
//             //      → slow has traveled:  L + K
//             //      → fast has traveled:  L + K + nC  (n = number of
//             //         full laps fast did around the cycle extra)
//             //
//             //    Since fast moves at 2x speed:
//             //      2 × (L + K) = L + K + nC
//             //      2L + 2K = L + K + nC
//             //      L + K = nC
//             //      L = nC - K
//             //
//             //    🔑 THIS IS THE KEY EQUATION: L = nC - K
//             //
//             //    What does this mean physically?
//             //    → From the MEETING POINT, if you walk (nC - K) steps
//             //      forward around the cycle, you arrive at the ENTRANCE.
//             //    → But nC - K = L, which is ALSO the distance from
//             //      HEAD to the ENTRANCE!
//             //    → So if one pointer starts at HEAD (distance L from
//             //      entrance) and another starts at MEETING POINT
//             //      (distance nC - K = L from entrance, going forward),
//             //      they will BOTH arrive at the ENTRANCE at the SAME TIME!
//             //
//             //    Visual:
//             //
//             //      head ──(L steps)──→ ENTRANCE ──(K steps)──→ MEETING POINT
//             //                              ↑                        │
//             //                              │                        │
//             //                              └──(C - K steps)─────────┘
//             //                                    (rest of cycle)
//             //
//             //      From head:     walk L steps → reach ENTRANCE
//             //      From meeting:  walk (nC - K) = L steps → reach ENTRANCE
//             //      They meet at the ENTRANCE! 🎯
//             //
//             // ⚠️ ATOMIC DETAIL #4 — Why does this work even if n > 1?
//             //    If fast did multiple laps (n = 2, 3, ...), then
//             //    nC - K means "go around the cycle n times, then back
//             //    up K steps." But going around the cycle n full times
//             //    brings you back to the same spot! So effectively,
//             //    from the meeting point, you just need to go (C - K)
//             //    steps to reach the entrance, which equals L (mod C).
//             //    Since the pointer from head takes exactly L steps,
//             //    and L = nC - K, both arrive at the entrance together.
//             //    The math holds regardless of n! ✅

//             // ⚠️ ATOMIC DETAIL #5 — The `temp` pointer
//             //    We create a NEW pointer `temp` at head. We DON'T move
//             //    `head` itself because we might need it later (good
//             //    practice, though here we return `slow` so it doesn't
//             //    matter). More importantly, `temp` clearly communicates
//             //    "this pointer starts fresh from the beginning."
//             ListNode* temp = head;  // 🔄 New pointer starting from HEAD

//             // ⚠️ ATOMIC DETAIL #6 — The loop condition `temp != slow`
//             //    → `temp` starts at head, `slow` is at the meeting point.
//             //    → Both move at 1x speed (1 step per iteration).
//             //    → They are GUARANTEED to meet at the cycle entrance
//             //      (proven by the math above: both are L steps away).
//             //    → When temp == slow → we've found the entrance!
//             //
//             //    Why NOT use fast here?
//             //    → We COULD use fast (it's at the same position as slow).
//             //    → But using slow is more semantically clear:
//             //      "one pointer from head, one from meeting point."
//             //    → After Phase 1, fast and slow are at the same node,
//             //      so it doesn't matter which one we pick.
//             //
//             // ⚠️ ATOMIC DETAIL #7 — Why 1x speed for BOTH in Phase 2?
//             //    In Phase 1, the speed ratio was 1:2 to DETECT the cycle.
//             //    In Phase 2, the speed ratio is 1:1 to FIND the entrance.
//             //    The math L = nC - K only works when both pointers
//             //    cover the SAME distance. If one moved faster, they'd
//             //    overshoot the entrance and miss each other!
//             //
//             //    Visual walkthrough (list: 3→2→0→-4→back to 2):
//             //      head=3, entrance=2, cycle: 2→0→-4→2 (C=3)
//             //      L=1 (head to entrance), K=2 (entrance to meeting)
//             //
//             //      Phase 1: slow and fast meet at node -4
//             //      Phase 2: temp=3 (head), slow=-4 (meeting)
//             //        Iter 1: temp=2, slow=2 → MEET at node 2! ✅
//             //        Node 2 IS the cycle entrance! 🎯
//             //
//             while (temp != slow) {
//                 slow = slow->next;  // 🐢 Move from meeting point (1x)
//                 temp = temp->next;  // 🚶 Move from head (1x)
//             }
//             // ✅ When loop exits: temp == slow == CYCLE ENTRANCE NODE

//             return slow;  // 🎯 Return the node where the cycle begins
//         }
//     }
// };

// // ================================================================
// // 📝 DETAILED SUMMARY FOR REVISION
// // ================================================================
// //
// // 🎯 PROBLEM:
// //    Given a linked list that may contain a cycle, return the node
// //    where the cycle BEGINS. If there is no cycle, return NULL.
// //    Do NOT modify the linked list. Use O(1) space.
// //
// // 🧩 PATTERN USED: Floyd's Tortoise and Hare — TWO PHASES
// //    Phase 1: Detect cycle (1:2 speed ratio) — same as LC 141
// //    Phase 2: Find entrance (1:1 speed ratio) — the NEW trick
// //
// // 🏠 REAL-LIFE ANALOGY:
// //    Imagine a race track shaped like a lollipop 🍭:
// //    → The "stick" is the straight part (length L from start to loop).
// //    → The "candy" is the circular loop (circumference C).
// //
// //    PHASE 1 (Detection):
// //      Two runners start at the beginning of the stick. The hare runs
// //      at 2x speed. If the track has a loop, the hare enters the loop
// //      first, starts circling, and eventually catches the tortoise
// //      somewhere inside the loop. They HIGH-FIVE! 🙌 → Cycle exists!
// //      If the track is just a straight road, the hare reaches the end
// //      first → No cycle.
// //
// //    PHASE 2 (Finding the entrance):
// //      Here's the magic trick. After the high-five, you tell the
// //      tortoise to stay at the meeting point. You send a NEW runner
// //      from the START of the stick. Both now walk at the SAME speed.
// //      The math guarantees they will meet EXACTLY at the point where
// //      the stick meets the candy — the ENTRANCE to the loop!
// //
// //      Why? Because the distance from the start to the entrance (L)
// //      is EXACTLY EQUAL to the distance from the meeting point back
// //      to the entrance (going around the loop). It's like two people
// //      walking toward the same door from different directions, both
// //      the same distance away — they arrive at the same time!
// //
// // 📌 STEP-BY-STEP RECIPE:
// //    PHASE 1:
// //      1. Start slow and fast at head.
// //      2. Move slow by 1, fast by 2 each iteration.
// //      3. If slow == fast → cycle exists → set flag, break.
// //      4. If fast hits NULL → no cycle → return NULL.
// //    PHASE 2:
// //      5. Create temp at head. Keep slow at meeting point.
// //      6. Move both temp and slow by 1 step each.
// //      7. When temp == slow → that's the cycle entrance → return it.
// //
// // ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
// //    ☐ Phase 1 is IDENTICAL to LC 141 — don't reinvent the wheel.
// //    ☐ Use a flag (or check fast after loop) to distinguish
// //      "cycle found" from "no cycle" before entering Phase 2.
// //    ☐ In Phase 2, BOTH pointers move at 1x speed (NOT 1:2!).
// //      → 1:1 is required by the math L = nC - K.
// //    ☐ Phase 2 loop condition is `temp != slow`, NOT `temp != fast`.
// //      → After Phase 1, slow and fast are at the same node, so either
// //        works. But `slow` is semantically clearer.
// //    ☐ Don't forget to `break` in Phase 1 when cycle is detected.
// //      → Without break, the loop runs forever (infinite cycle!).
// //    ☐ The meeting point in Phase 1 is NOT necessarily the entrance.
// //      → It's SOMEWHERE inside the cycle. Phase 2 finds the real entrance.
// //    ☐ Edge case: cycle starts at head (entire list is a loop).
// //      → L = 0, so temp and slow are already equal → loop doesn't
// //        execute → return head. Correct! ✅
// //    ☐ Edge case: self-loop (single node pointing to itself).
// //      → Phase 1: slow=head, fast=head→head → meet immediately.
// //      → Phase 2: temp=head, slow=head → already equal → return head. ✅
// //
// // 🔗 COMPARISON WITH ALL PREVIOUS PROBLEMS:
// //    ┌──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐
// //    │    Aspect    │ LC 19        │ LC 2095      │ LC 160       │ LC 141/142   │
// //    │              │ (Nth End)    │ (Mid Delete) │ (Intersect)  │ (Cycle)      │
// //    ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
// //    │ Lists        │ 1            │ 1            │ 2            │ 1            │
// //    │ Pointers     │ 2            │ 3            │ 2            │ 2 (+ 1 in P2)│
// //    │ Phase 1      │ Create gap   │ Find middle  │ Count lengths│ Detect cycle │
// //    │ Phase 2      │ Walk together│ Delete node  │ Align & walk │ Find entrance│
// //    │ Speed (P1)   │ 1:1          │ 1:2          │ 1:1 (sep.)   │ 1:2          │
// //    │ Speed (P2)   │ 1:1          │ —            │ 1:1          │ 1:1          │
// //    │ Key math     │ gap = n+1    │ mid = N/2    │ diff = |A-B| │ L = nC - K   │
// //    │ Return       │ ListNode*    │ ListNode*    │ ListNode*    │ ListNode*    │
// //    │ Edge case    │ Delete head  │ 1-node       │ No intersect │ No cycle     │
// //    └──────────────┴──────────────┴──────────────┴──────────────┴──────────────┘
// //
// //    🔑 KEY OBSERVATION:
// //    LC 141 and LC 142 are essentially the SAME algorithm.
// //    LC 142 = LC 141 + Phase 2 (the entrance-finding trick).
// //    If you've mastered LC 141, LC 142 is just ONE extra loop!
// //
// // ⏱️ TIME COMPLEXITY: O(N) where N = number of nodes
// //    → Phase 1: At most N steps for slow to enter the cycle,
// //      then at most C steps for fast to catch slow. Total: O(N).
// //    → Phase 2: At most L steps (≤ N) for both to reach the entrance.
// //    → Total: O(N) + O(N) = O(N).
// //    → Interview answer: "Linear time. Two passes at most, still O(N)."
// //
// // 💾 SPACE COMPLEXITY: O(1)
// //    → Only three pointers (slow, fast, temp) and one boolean (flag).
// //    → No hash set, no array, no recursion stack.
// //    → Interview answer: "Constant space, O(1). This is the optimal
// //      approach — the hash set alternative uses O(N) space."
// //
// // 🎤 INTERVIEW TIPS:
// //
// //    Q1: "Can you explain WHY Phase 2 works?"
// //    → Walk through the math: L + K = nC → L = nC - K.
// //    → "The distance from head to entrance equals the distance from
// //      the meeting point to the entrance (going forward around the cycle).
// //      So two pointers starting from head and meeting point, moving at
// //      the same speed, will converge at the entrance."
// //    → Draw the lollipop diagram on the whiteboard! 🍭
// //
// //    Q2: "What's the alternative approach?"
// //    → Hash set: traverse the list, store each node's address.
// //      First repeated address = cycle entrance. O(N) time, O(N) space.
// //    → Floyd's is strictly better (same time, less space).
// //
// //    Q3: "How would you find the LENGTH of the cycle?"
// //    → After detecting the cycle (Phase 1), keep one pointer fixed
// //      at the meeting point. Move the other pointer around the cycle,
// //      counting steps until it returns to the meeting point.
// //      The count = cycle length C.
// //
// //    Q4: "What if you need to REMOVE the cycle?"
// //    → Find the entrance (Phase 2). Then traverse the cycle from the
// //      entrance until you find the node whose `next` points back to
// //      the entrance. Set that node's `next` to NULL. Done!
// // ================================================================