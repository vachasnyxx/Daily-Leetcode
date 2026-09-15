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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode* a = head;
        ListNode* b = head->next;

        while (b != NULL) {
            while (b != NULL && b->val == a->val) {
                b = b->next;
            }
            a->next = b;
            // for next round
            a = b;
            if (b != NULL)
                b = b->next;
        }
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
//  */
// class Solution {
// public:
//     ListNode* deleteDuplicates(ListNode* head) {

//         // ============================================================
//         // 🧠 INTUITION & PATTERN: TWO POINTERS ON A SORTED LIST
//         //         (Keeper + Scanner Technique)
//         // ============================================================
//         // The core IDEA is:
//         //   "Since the list is SORTED, all duplicates are ADJACENT.
//         //    So we don't need a hash set or anything fancy. We just
//         //    need one pointer to HOLD the current unique value ('a')
//         //    and another to SCAN ahead ('b'), skipping all nodes that
//         //    match 'a's value. Once 'b' finds a DIFFERENT value, we
//         //    wire 'a' directly to 'b', effectively deleting the dupes."
//         //
//         // 🆚 HOW IS THIS DIFFERENT FROM PREVIOUS PROBLEMS?
//         //   LC 19:   Gap of (n+1) to find nth from end.
//         //   LC 2095: Speed ratio 1:2 to find middle.
//         //   LC 160:  Length alignment across two lists.
//         //   LC 141:  Speed ratio 1:2 to detect cycle.
//         //   LC 142:  Phase 1 (detect) + Phase 2 (find entrance).
//         //   LC 83:   NO gap, NO speed trick — just a KEEPER and a
//         //            SCANNER on a SORTED list. The sorted property
//         //            is what makes this problem simple!
//         //
//         // ⚠️ IMPORTANT DISTINCTION — LC 83 vs LC 82:
//         //   LC 83 (THIS): Keep ONE copy of each value.
//         //     [1,1,2,3,3] → [1,2,3]
//         //   LC 82 (HARDER): Remove ALL nodes that had duplicates.
//         //     [1,1,2,3,3] → [2]
//         //   Your code solves LC 83. The key difference is that here
//         //   'a' STAYS on the first occurrence (we keep it), while in
//         //   LC 82 you'd need to skip 'a' itself if duplicates exist.
//         // ============================================================

//         // 🔹 STEP 0: Handle EDGE CASES
//         //
//         // ⚠️ ATOMIC DETAIL #1 — Why check head->next == NULL?
//         //    → 0 nodes (head == NULL): Nothing to deduplicate. Return NULL.
//         //    → 1 node (head->next == NULL): A single node can't have
//         //      duplicates. Return it as-is.
//         //    → 2+ nodes: Duplicates are possible. Proceed with logic.
//         //    This early return also prevents `head->next` from being
//         //    accessed when head is NULL (which would be a SEGFAULT).
//         if (head == NULL || head->next == NULL)
//             return head;  // ✅ 0 or 1 node — already "deduplicated"

//         // 🔹 STEP 1: Initialize the two pointers
//         //
//         // ⚠️ ATOMIC DETAIL #2 — The roles of 'a' and 'b':
//         //    → 'a' (Keeper): Points to the LAST CONFIRMED UNIQUE node.
//         //      This node will STAY in the final list. It acts as the
//         //      "anchor" — we build the deduplicated list behind it.
//         //    → 'b' (Scanner): Scans AHEAD of 'a', looking for the next
//         //      node with a DIFFERENT value. It skips over all duplicates.
//         //
//         //    Why start 'b' at head->next (not head)?
//         //    → Because 'a' is already at head. We want 'b' to look at
//         //      the NEXT node to compare values. Starting both at head
//         //      would mean b->val == a->val immediately (same node!),
//         //      and the inner loop would skip the head itself — WRONG!
//         //
//         //    Visual (list: 1 → 1 → 2 → 3 → 3 → NULL):
//         //      a    b
//         //      ↓    ↓
//         //      1 →  1 →  2 →  3 →  3 → NULL
//         ListNode* a = head;        // 🏠 Keeper — stays on unique values
//         ListNode* b = head->next;  // 🔍 Scanner — hunts for next unique

//         // 🔹 STEP 2: Main loop — scan until 'b' reaches the end
//         //
//         // ⚠️ ATOMIC DETAIL #3 — Why `b != NULL` and not `a != NULL`?
//         //    → 'a' is always BEHIND 'b'. If 'b' is not NULL, 'a' is
//         //      guaranteed to be not NULL (it's at or before 'b').
//         //    → 'b' is the "frontier" — when it hits NULL, we've scanned
//         //      the entire list. No more duplicates to skip.
//         //    → Checking 'a' would be redundant and could cause an
//         //      infinite loop if 'a' somehow stays valid after 'b' ends.
//         while (b != NULL) {

//             // 🔹 STEP 2a: INNER LOOP — Skip ALL duplicates of a->val
//             //
//             // ⚠️ ATOMIC DETAIL #4 — The inner while loop is the CORE
//             //    of this algorithm. It's what actually "deletes" dupes.
//             //
//             //    Condition: `b != NULL && b->val == a->val`
//             //    → `b != NULL`: Safety check! Without this, `b->val`
//             //      would SEGFAULT when b reaches the end of a list
//             //      like [1, 1, 1] (all duplicates, b goes to NULL).
//             //    → `b->val == a->val`: This is the duplicate check.
//             //      Since the list is SORTED, all duplicates of a->val
//             //      are RIGHT NEXT to each other. So we just keep
//             //      advancing 'b' until we find a DIFFERENT value.
//             //
//             //    Visual (list: 1 → 1 → 1 → 2 → 3 → 3 → NULL):
//             //      Round 1: a=1, b starts at 1
//             //        Inner: b->val(1)==a->val(1) → b moves to 1
//             //        Inner: b->val(1)==a->val(1) → b moves to 2
//             //        Inner: b->val(2)!=a->val(1) → STOP ✅
//             //        Now b=2, all the extra 1s are "skipped"
//             //
//             //    ⚠️ ATOMIC DETAIL #5 — Why does this only work on
//             //       SORTED lists?
//             //       Because in a sorted list, duplicates are CONTIGUOUS.
//             //       [1,1,2,3,3] → all 1s are together, all 3s together.
//             //       In an UNSORTED list like [1,3,1,2,3], duplicates
//             //       are scattered. The inner loop would skip the first
//             //       3 but miss the second 3 later. You'd need a hash
//             //       set for unsorted lists → O(N) space.
//             //       The sorted property is what gives us O(1) space!
//             while (b != NULL && b->val == a->val) {
//                 b = b->next;  // 🔍 Skip this duplicate, keep scanning
//             }
//             // ✅ After inner loop:
//             //    → 'b' is either NULL (end of list) or points to the
//             //      FIRST node with a value DIFFERENT from a->val.
//             //    → All nodes between 'a' and 'b' are duplicates of a->val.

//             // 🔹 STEP 2b: Rewire — connect 'a' directly to 'b'
//             //
//             // ⚠️ ATOMIC DETAIL #6 — This is the ACTUAL deletion step.
//             //    By setting a->next = b, we "cut out" all the duplicate
//             //    nodes between 'a' and 'b'. They become unreachable
//             //    (garbage collected in Java/Python; leaked in C++ unless
//             //    you explicitly delete them).
//             //
//             //    Before:  a → dup → dup → dup → b → ...
//             //    After:   a ──────────────────→ b → ...
//             //             (duplicates are orphaned/skipped)
//             //
//             //    Example: a=1, b=2 (after skipping extra 1s)
//             //    Before:  1 → 1 → 1 → 2 → ...
//             //    After:   1 ──────────→ 2 → ...  ✅
//             a->next = b;  // ✂️ Cut out the duplicates!

//             // 🔹 STEP 2c: Advance both pointers for the NEXT round
//             //
//             // ⚠️ ATOMIC DETAIL #7 — The order of advancement matters!
//             //    1. First, move 'a' to 'b' (the new unique node).
//             //       'a' is now the keeper of this new value.
//             //    2. Then, move 'b' one step ahead to start scanning
//             //       for duplicates of the NEW a->val.
//             //
//             //    Why the `if (b != NULL)` check before b = b->next?
//             //    → After the inner loop, 'b' COULD be NULL (if all
//             //      remaining nodes were duplicates, e.g., [1,2,2,2]).
//             //    → If b is NULL and we do b = b->next → SEGFAULT! 💥
//             //    → So we only advance 'b' if it's still valid.
//             //    → If b is NULL, the outer while loop will exit on
//             //      the next iteration anyway, so it's fine to leave
//             //      b as NULL.
//             //
//             //    Visual (continuing from [1,1,2,3,3]):
//             //      After rewiring: 1 → 2 → 3 → 3 → NULL
//             //      a = b → a=2
//             //      b = b->next → b=3
//             //      Next round: a=2, b=3
//             //        Inner: 3 != 2 → skip inner loop
//             //        a->next = b (2→3, already correct)
//             //        a = 3, b = 3
//             //      Next round: a=3, b=3
//             //        Inner: 3 == 3 → b moves to NULL
//             //        a->next = NULL (3→NULL) ✅
//             //        a = NULL, b check: b==NULL → skip
//             //      Outer: b == NULL → EXIT ✅
//             //      Result: 1 → 2 → 3 → NULL 🎯
//             a = b;              // 🏠 'a' moves to the new unique node
//             if (b != NULL)
//                 b = b->next;    // 🔍 'b' steps ahead to start scanning
//         }

//         // 🔹 STEP 3: Return the head
//         //
//         // ⚠️ ATOMIC DETAIL #8 — Why does head never change?
//         //    → The head is ALWAYS the first occurrence of its value.
//         //    → We never delete the first occurrence — we only delete
//         //      SUBSEQUENT duplicates. So head is always valid and
//         //      always part of the final list.
//         //    → Contrast with LC 82 (Remove Duplicates II) where the
//         //      head ITSELF might be a duplicate and needs removal.
//         //      That problem requires a DUMMY node before head.
//         //    → Here, no dummy needed. Just return head. ✅
//         return head;
//     }
// };

// // ================================================================
// // 📝 DETAILED SUMMARY FOR REVISION
// // ================================================================
// //
// // 🎯 PROBLEM:
// //    Given the head of a SORTED linked list, delete all duplicate
// //    elements so that each element appears only ONCE. Return the
// //    list still sorted.
// //    Example: [1,1,2,3,3] → [1,2,3]
// //
// // 🧩 PATTERN USED: Two Pointers — "Keeper + Scanner" on Sorted Data
// //
// // 🏠 REAL-LIFE ANALOGY:
// //    Imagine you're organizing a bookshelf where books are already
// //    sorted alphabetically. You notice some books have multiple
// //    copies sitting next to each other (because they're sorted!).
// //
// //    You place your LEFT HAND ('a') on the first copy of a book
// //    you want to keep. Your RIGHT HAND ('b') slides along the shelf,
// //    pushing past all the extra copies of the same book. When your
// //    right hand lands on a DIFFERENT book title, you remove all the
// //    copies between your hands (a->next = b). Then you move your
// //    left hand to where your right hand is, and repeat!
// //
// //    Since the books are sorted, you KNOW all copies are next to
// //    each other — you never have to look back or scan the whole
// //    shelf again. One pass is enough!
// //
// // 📌 STEP-BY-STEP RECIPE:
// //    1. Edge case: 0 or 1 node → return head (nothing to deduplicate).
// //    2. Set a = head (keeper), b = head->next (scanner).
// //    3. While b != NULL:
// //       a. Inner loop: advance b while b->val == a->val (skip dupes).
// //       b. Rewire: a->next = b (cut out the duplicates).
// //       c. Advance: a = b, then b = b->next (if b != NULL).
// //    4. Return head.
// //
// // ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
// //    ☐ List MUST be sorted for this O(1) space approach to work.
// //      → Unsorted → duplicates aren't adjacent → need hash set O(N).
// //    ☐ Inner loop condition MUST have `b != NULL` BEFORE `b->val`.
// //      → C++ evaluates left-to-right with short-circuit. If b is NULL,
// //        `b->val` would SEGFAULT. Order matters!
// //    ☐ The `if (b != NULL)` before `b = b->next` in Step 2c.
// //      → After inner loop, b could be NULL (all remaining were dupes).
// //      → Accessing NULL->next = SEGFAULT.
// //    ☐ Head NEVER changes in LC 83 (we keep first occurrence).
// //      → No dummy node needed (unlike LC 82).
// //    ☐ We keep ONE copy of each value (LC 83), not ZERO (LC 82).
// //      → 'a' stays on the first occurrence — it's the keeper.
// //    ☐ The rewiring `a->next = b` happens EVEN when there are no
// //      duplicates (b is already a->next). This is harmless — it's
// //      just reassigning the same pointer. No special case needed.
// //
// // 🔗 COMPARISON WITH ALL PREVIOUS PROBLEMS:
// //    ┌──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐
// //    │    Aspect    │ LC 19        │ LC 2095      │ LC 160       │ LC 141/142   │ LC 83        │
// //    │              │ (Nth End)    │ (Mid Delete) │ (Intersect)  │ (Cycle)      │ (Duplicates) │
// //    ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
// //    │ Lists        │ 1            │ 1            │ 2            │ 1            │ 1 (sorted!)  │
// //    │ Pointers     │ 2 (s, f)     │ 3 (p, s, f)  │ 2 (tA, tB)   │ 2 (s, f)     │ 2 (a, b)     │
// //    │ Speed        │ 1:1 (gap)    │ 1:2          │ 1:1          │ 1:2 → 1:1   │ 1:1 (nested) │
// //    │ Key trick    │ Fixed gap    │ 2x = middle  │ Align length │ Floyd's      │ Sorted=adj.  │
// //    │ Inner loop?  │ No           │ No           │ No           │ No           │ YES (skip)   │
// //    │ Data prop.   │ None         │ None         │ None         │ None         │ SORTED       │
// //    │ Return       │ ListNode*    │ ListNode*    │ ListNode*    │ bool / Node* │ ListNode*    │
// //    │ Edge case    │ Delete head  │ 1-node       │ No intersect │ No cycle     │ 0/1 node     │
// //    └──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┘
// //
// //    🔑 KEY OBSERVATION:
// //    LC 83 is the SIMPLEST two-pointer problem in this set because
// //    the SORTED property does most of the work for you. No gap math,
// //    no speed tricks, no cycle detection — just "skip adjacent dupes."
// //    The inner while loop is the only new concept compared to LC 19/160.
// //
// // ⏱️ TIME COMPLEXITY: O(N) where N = number of nodes
// //    → 'b' scans each node EXACTLY ONCE (it only moves forward).
// //    → 'a' also moves forward, always following 'b'.
// //    → Even though there's a nested loop, 'b' never goes backwards.
// //      Total iterations of the inner loop across ALL outer iterations
// //      is at most N. This is called AMORTIZED O(N).
// //    → Interview answer: "Single pass, O(N). Each node is visited
// //      at most once by pointer b."
// //
// // 💾 SPACE COMPLEXITY: O(1)
// //    → Only two pointers (a and b). No hash set, no array.
// //    → The sorted property is what allows O(1) space.
// //    → Interview answer: "Constant space, O(1). We exploit the
// //      sorted order to detect duplicates without extra storage."
// //
// // 🎤 INTERVIEW FOLLOW-UP QUESTIONS TO PREPARE FOR:
// //
// //    Q1: "What if the list is NOT sorted?"
// //    → Use a hash set to track seen values. O(N) time, O(N) space.
// //    → Or sort the list first (O(N log N)), then use this approach.
// //
// //    Q2: "What if you need to remove ALL occurrences of duplicates?"
// //    → That's LC 82 (Remove Duplicates from Sorted List II).
// //    → [1,1,2,3,3] → [2] (1 and 3 are completely removed).
// //    → You'd need a dummy node and a "previous" pointer to handle
// //      the case where the head itself is a duplicate.
// //
// //    Q3: "Can you do this recursively?"
// //    → Yes! If head->val == head->next->val, skip head->next and
// //      recurse. Otherwise, head->next = recurse(head->next).
// //    → But recursion uses O(N) stack space — iterative is better.
// //
// //    Q4: "What about memory leaks in C++?"
// //    → Your code rewires pointers but doesn't `delete` the skipped
// //      nodes. In a real C++ interview, mention this! You'd store
// //      the duplicate nodes and delete them after rewiring:
// //        ListNode* toDelete = a->next;
// //        a->next = b;
// //        while(toDelete != b) { ListNode* t = toDelete; toDelete = toDelete->next; delete t; }
// //    → LeetCode doesn't check for this, but interviewers appreciate it.
// // ================================================================