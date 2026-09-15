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
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {

        ListNode* c = new ListNode(100);
        ListNode* temp = c;

        while (a != NULL && b != NULL) {
            if (a->val <= b->val) {
                temp->next = a;
                a = a->next;
                temp = temp->next;
            }
            else{ // b->val < a->val
                temp->next = b;
                b = b->next;
                temp = temp->next;
            }
        }
        if(a==NULL) temp->next = b;
        else temp->next = a;
        return c->next;
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
//     ListNode* mergeTwoLists(ListNode* a, ListNode* b) {

//         // ============================================================
//         // 🧠 INTUITION & PATTERN: DUMMY NODE + TWO POINTER MERGE
//         //         (The "Zipper" Technique — same as Merge Sort's merge step)
//         // ============================================================
//         // The core IDEA is:
//         //   "You have two SORTED linked lists. You want to merge them
//         //    into ONE sorted list. Since both are already sorted, you
//         //    just need to compare the FRONT of each list, pick the
//         //    smaller one, and attach it to your result. Repeat until
//         //    one list is exhausted, then attach the rest of the other."
//         //
//         //   This is EXACTLY the merge step from Merge Sort! If you've
//         //   studied merge sort, you already know this algorithm.
//         //
//         // 🆚 HOW IS THIS DIFFERENT FROM PREVIOUS PROBLEMS?
//         //   LC 19:   Gap of (n+1) on ONE list.
//         //   LC 2095: Speed ratio 1:2 on ONE list.
//         //   LC 160:  Length alignment across TWO lists.
//         //   LC 141:  Speed ratio 1:2 for cycle detection.
//         //   LC 142:  Floyd's Phase 1 + Phase 2.
//         //   LC 83:   Keeper + Scanner on sorted list.
//         //   LC 61:   Measure + Cut with circular rewiring.
//         //   LC 2326: Spiral matrix traversal (hybrid).
//         //   LC 21:   TWO sorted lists → merge into ONE. No gap, no speed
//         //            trick — just a HEAD-TO-HEAD COMPARISON at each step.
//         //            The NEW concept here is the DUMMY NODE technique.
//         //
//         // 🔑 KEY INSIGHT — THE DUMMY NODE:
//         //   When building a new linked list from scratch, the FIRST node
//         //   is always a special case (you need to set the head). Every
//         //   subsequent node is easy (just do tail->next = newNode).
//         //   A DUMMY NODE eliminates this special case by giving you a
//         //   "fake head" to start with. You build the list after the dummy,
//         //   then return dummy->next as the real head. Clean and elegant!
//         // ============================================================

//         // 🔹 STEP 1: Create a DUMMY node and a builder pointer
//         //
//         // ⚠️ ATOMIC DETAIL #1 — What is a DUMMY node and WHY do we need it?
//         //    A dummy node is a FAKE node placed before the actual head
//         //    of the result list. It serves as an "anchor" so we don't
//         //    have to handle the first insertion differently from the rest.
//         //
//         //    WITHOUT dummy (the painful way):
//         //      ListNode* head = NULL;
//         //      ListNode* tail = NULL;
//         //      // First node: special case!
//         //      if(a->val <= b->val) { head = a; tail = a; a = a->next; }
//         //      else { head = b; tail = b; b = b->next; }
//         //      // Remaining nodes: normal case
//         //      while(...) { tail->next = ...; tail = tail->next; }
//         //      return head;
//         //    → Ugly! You need an if-else just for the first node.
//         //
//         //    WITH dummy (your approach — the clean way):
//         //      ListNode* dummy = new ListNode();
//         //      ListNode* tail = dummy;
//         //      while(...) { tail->next = ...; tail = tail->next; }
//         //      return dummy->next;  // Skip the fake head
//         //    → Beautiful! Every insertion is the same. No special case.
//         //
//         // ⚠️ ATOMIC DETAIL #2 — The value 100 in `new ListNode(100)`
//         //    The value doesn't matter AT ALL! The dummy node is never
//         //    part of the final result (we return c->next, skipping it).
//         //    You could use 0, -1, 999, INT_MIN — anything works.
//         //    Some people write `new ListNode()` (default 0) or
//         //    `new ListNode(-1)`. Your choice of 100 is perfectly fine.
//         //    The key is that the node EXISTS as a placeholder.
//         //
//         // ⚠️ ATOMIC DETAIL #3 — `temp` is the BUILDER pointer
//         //    → `c` is the dummy (anchor, never moves).
//         //    → `temp` starts at `c` and moves forward as we attach nodes.
//         //    → `temp` always points to the LAST node of the merged list
//         //      built so far. It's the "tail" of the result.
//         //    → We use `temp` to build; we use `c` to remember the start.
//         //    → This is why we need TWO pointers for the result: one to
//         //      build (temp), one to return (c->next).
//         //
//         //    Visual (initial state):
//         //      c (dummy)
//         //      ↓
//         //     [100] → NULL
//         //      ↑
//         //     temp (same as c initially)
//         //
//         //      a → [1] → [3] → [5] → NULL
//         //      b → [2] → [4] → [6] → NULL
//         ListNode* c = new ListNode(100);  // 🏗️ Dummy node (fake head, value irrelevant)
//         ListNode* temp = c;               // 🔨 Builder pointer (starts at dummy)

//         // 🔹 STEP 2: Merge by comparing heads of both lists
//         //
//         // ⚠️ ATOMIC DETAIL #4 — The while condition `a != NULL && b != NULL`
//         //    → We can only COMPARE when BOTH lists have nodes remaining.
//         //    → If EITHER list is exhausted, we can't compare anymore.
//         //    → The loop stops when at least one list runs out.
//         //    → The remaining nodes of the OTHER list are handled after
//         //      the loop (Step 3).
//         //
//         //    Why `&&` and not `||`?
//         //    → `&&`: Stop when ANY list is empty (safe for comparison).
//         //    → `||`: Would continue when one list is empty → NULL->val
//         //      would SEGFAULT! 💥
//         //
//         // ⚠️ ATOMIC DETAIL #5 — The comparison `a->val <= b->val`
//         //    → `<=` (not `<`) ensures STABILITY: when values are equal,
//         //      we prefer the node from list `a`. This doesn't affect
//         //      correctness (both values are the same), but it's a good
//         //      habit for stable sorting.
//         //    → We attach the SMALLER node to temp->next, then advance
//         //      that list's pointer. The other list's pointer stays put.
//         //
//         //    Visual walkthrough (a=[1,3,5], b=[2,4,6]):
//         //
//         //      Iter 1: a->val(1) <= b->val(2) → attach a(1)
//         //        c → [100] → [1] → NULL
//         //                       ↑
//         //                      temp
//         //        a moves to 3, b stays at 2
//         //
//         //      Iter 2: a->val(3) > b->val(2) → attach b(2)
//         //        c → [100] → [1] → [2] → NULL
//         //                              ↑
//         //                             temp
//         //        a stays at 3, b moves to 4
//         //
//         //      Iter 3: a->val(3) <= b->val(4) → attach a(3)
//         //        c → [100] → [1] → [2] → [3] → NULL
//         //                                    ↑
//         //                                   temp
//         //        a moves to 5, b stays at 4
//         //
//         //      Iter 4: a->val(5) > b->val(4) → attach b(4)
//         //        c → [100] → [1] → [2] → [3] → [4] → NULL
//         //                                        ↑
//         //                                       temp
//         //        a stays at 5, b moves to 6
//         //
//         //      Iter 5: a->val(5) <= b->val(6) → attach a(5)
//         //        c → [100] → [1] → [2] → [3] → [4] → [5] → NULL
//         //                                                ↑
//         //                                               temp
//         //        a moves to NULL, b stays at 6
//         //
//         //      Loop exits (a == NULL) ✅
//         //
//         while (a != NULL && b != NULL) {
//             if (a->val <= b->val) {
//                 // 📌 List a has the smaller (or equal) front value
//                 temp->next = a;    // 🔗 Attach a's current node to result
//                 a = a->next;       // ⏭️ Advance list a (consume this node)
//                 temp = temp->next; // 🔨 Advance builder to the new tail
//             }
//             else {
//                 // 📌 List b has the strictly smaller front value
//                 //    (b->val < a->val)
//                 temp->next = b;    // 🔗 Attach b's current node to result
//                 b = b->next;       // ⏭️ Advance list b (consume this node)
//                 temp = temp->next; // 🔨 Advance builder to the new tail
//             }
//             // ⚠️ ATOMIC DETAIL #6 — What are we actually doing here?
//             //    We are NOT creating new nodes! We are REWIRING the
//             //    existing nodes from lists a and b into a new order.
//             //    This is an IN-PLACE merge — O(1) extra space!
//             //    The original lists a and b are "consumed" (their nodes
//             //    are now part of the merged list). After this function,
//             //    the original a and b pointers are meaningless.
//         }

//         // 🔹 STEP 3: Attach the remaining nodes
//         //
//         // ⚠️ ATOMIC DETAIL #7 — Why is one list guaranteed to have leftovers?
//         //    The while loop exits when a == NULL OR b == NULL (or both).
//         //    → If a == NULL: list a is exhausted, list b might have nodes left.
//         //    → If b == NULL: list b is exhausted, list a might have nodes left.
//         //    → If both == NULL: both exhausted simultaneously (equal length,
//         //      last comparison consumed the last node of one, and the other
//         //      was already NULL). In this case, attaching NULL is harmless.
//         //
//         //    The KEY insight: the remaining portion of the non-empty list
//         //    is ALREADY SORTED (it was sorted to begin with, and we only
//         //    removed elements from the front). So we can attach the ENTIRE
//         //    remaining chain in one step — no need to iterate!
//         //
//         //    Visual (continuing from above, a=NULL, b=[6]):
//         //      temp->next = b → attach [6] to the end
//         //      c → [100] → [1] → [2] → [3] → [4] → [5] → [6] → NULL ✅
//         //
//         // ⚠️ ATOMIC DETAIL #8 — Why `if(a==NULL) temp->next = b; else temp->next = a;`?
//         //    This is a clean shorthand. Exactly one of these is true:
//         //    → a is NULL → attach whatever is left of b (could be NULL too).
//         //    → a is NOT NULL → b must be NULL (loop condition) → attach a.
//         //    Both cases are handled correctly. No need for two separate ifs.
//         //
//         //    What if BOTH are NULL?
//         //    → a==NULL is true → temp->next = b = NULL → temp->next = NULL.
//         //    → This is correct! The merged list ends properly. ✅
//         if (a == NULL)
//             temp->next = b;  // 🔗 Attach remaining of b (or NULL if both done)
//         else
//             temp->next = a;  // 🔗 Attach remaining of a (b must be NULL here)

//         // 🔹 STEP 4: Return the real head (skip the dummy)
//         //
//         // ⚠️ ATOMIC DETAIL #9 — Why `c->next` and not `c`?
//         //    `c` is the DUMMY node with value 100. It's not part of the
//         //    actual merged list. The real merged list starts at c->next.
//         //    Returning `c` would include the fake 100 at the front — WRONG!
//         //
//         //    Visual:
//         //      c      real head
//         //      ↓      ↓
//         //     [100] → [1] → [2] → [3] → [4] → [5] → [6] → NULL
//         //              ↑
//         //         return THIS (c->next)
//         //
//         // ⚠️ ATOMIC DETAIL #10 — Memory leak consideration
//         //    The dummy node `c` was allocated with `new` but is never
//         //    `delete`d. In a real C++ application, this is a memory leak.
//         //    To fix it properly:
//         //      ListNode* result = c->next;
//         //      delete c;
//         //      return result;
//         //    LeetCode doesn't check for this, but mentioning it in an
//         //    interview shows attention to detail! 💯
//         return c->next;  // 🎯 Skip dummy, return the real merged head
//     }
// };

// // ================================================================
// // 📝 DETAILED SUMMARY FOR REVISION
// // ================================================================
// //
// // 🎯 PROBLEM:
// //    Merge two SORTED linked lists into one sorted linked list.
// //    The merged list should be made by splicing together the nodes
// //    of the first two lists (no new nodes, just rewiring).
// //    Example: a=[1,2,4], b=[1,3,4] → [1,1,2,3,4,4]
// //
// // 🧩 PATTERN USED: Dummy Node + Two Pointer Merge (Zipper Technique)
// //    This is the EXACT merge step from Merge Sort. If you know merge
// //    sort, you already know this algorithm!
// //
// // 🏠 REAL-LIFE ANALOGY:
// //    Imagine you have two DECKS of cards, each sorted by number.
// //    Deck A: [2, 5, 8]    Deck B: [1, 3, 9]
// //
// //    You want to merge them into one sorted deck. You look at the
// //    TOP card of each deck:
// //    → A shows 2, B shows 1. Pick 1 (smaller). Put it face-down
// //      on the merged pile.
// //    → A shows 2, B shows 3. Pick 2. Put it on the pile.
// //    → A shows 5, B shows 3. Pick 3. Put it on the pile.
// //    → A shows 5, B shows 9. Pick 5. Put it on the pile.
// //    → A shows 8, B shows 9. Pick 8. Put it on the pile.
// //    → A is empty. Dump all of B (just 9) onto the pile.
// //    → Result: [1, 2, 3, 5, 8, 9] ✅
// //
// //    The DUMMY NODE is like placing a "placeholder card" at the
// //    bottom of the merged pile before you start. You don't care
// //    about this card — you just need something to place the first
// //    real card ON TOP of. At the end, you remove the placeholder.
// //
// // 📌 STEP-BY-STEP RECIPE:
// //    1. Create dummy node `c`. Set builder `temp = c`.
// //    2. While BOTH a and b are not NULL:
// //       a. Compare a->val and b->val.
// //       b. Attach the smaller node to temp->next.
// //       c. Advance that list's pointer.
// //       d. Advance temp to the new tail.
// //    3. Attach whichever list is remaining: temp->next = a or b.
// //    4. Return c->next (skip the dummy).
// //
// // ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
// //    ☐ DUMMY NODE is essential — avoids special-casing the first insertion.
// //      → Without it, you need an ugly if-else for the head of the result.
// //    ☐ Dummy value (100) is IRRELEVANT — it's never in the final result.
// //    ☐ `temp` and `c` serve DIFFERENT purposes:
// //      → `temp` moves (builder/tail). `c` stays (anchor for return).
// //    ☐ While condition uses `&&` (both must be non-NULL for comparison).
// //      → Using `||` would cause NULL->val segfault.
// //    ☐ Use `<=` not `<` for stability (equal values: prefer list a).
// //    ☐ After the loop, attach the REMAINING list in ONE step.
// //      → Don't loop through the rest — it's already sorted!
// //    ☐ Return `c->next`, NOT `c` (skip the dummy).
// //    ☐ We REWIRE existing nodes — no `new ListNode()` for data nodes.
// //      → This is O(1) space. Only the dummy is allocated.
// //    ☐ Edge cases handled naturally:
// //      → a is NULL from start: loop skips, temp->next = b → return b ✅
// //      → b is NULL from start: loop skips, temp->next = a → return a ✅
// //      → Both NULL: loop skips, temp->next = NULL → return NULL ✅
// //      → One list much longer: loop handles the overlap, Step 3 handles rest ✅
// //
// // 🔗 COMPARISON WITH ALL PREVIOUS PROBLEMS:
// //    ┌──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐
// //    │    Aspect    │ LC 19        │ LC 2095      │ LC 160       │ LC 141/142   │ LC 83        │ LC 61        │ LC 2326      │
// //    │              │ (Nth End)    │ (Mid Delete) │ (Intersect)  │ (Cycle)      │ (Duplicates) │ (Rotate)     │ (Spiral)     │
// //    ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
// //    │ Lists        │ 1            │ 1            │ 2            │ 1            │ 1 (sorted)   │ 1            │ 1 + matrix   │
// //    │ Technique    │ Fixed gap    │ 1:2 speed    │ Align length │ Floyd's      │ Keep+Scan    │ Measure+Cut  │ Spiral sim   │
// //    │ Key concept  │ Predecessor  │ Middle       │ Merge point  │ Cycle detect │ Adj dupes    │ Circular     │ Boundaries   │
// //    │ Dummy node?  │ No           │ No           │ No           │ No           │ No           │ No           │ No           │
// //    ├──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┤
// //    │    LC 21 (THIS PROBLEM)                                                                                              │
// //    ├──────────────┬──────────────────────────────────────────────────────────────────────────────────────────────────────────┤
// //    │ Lists        │ 2 SORTED lists → merge into 1                                                                          │
// //    │ Technique    │ Dummy Node + Head-to-Head Comparison (Zipper/Merge Sort step)                                          │
// //    │ Key concept  │ Pick smaller front, attach to result, advance that list                                                │
// //    │ Dummy node?  │ YES! First problem in our set to use this technique                                                    │
// //    │ New nodes?   │ NO — rewires existing nodes (O(1) space)                                                               │
// //    │ Edge case    │ One or both lists empty from the start                                                                 │
// //    └──────────────┴──────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// //
// //    🔑 KEY OBSERVATION:
// //    LC 21 introduces the DUMMY NODE technique — one of the most
// //    important linked list patterns. You'll use it again in:
// //    → LC 23 (Merge K Sorted Lists)
// //    → LC 82 (Remove Duplicates II)
// //    → LC 86 (Partition List)
// //    → LC 143 (Reorder List)
// //    → LC 148 (Sort List — uses this exact merge function!)
// //    Master the dummy node here, and these harder problems become easier.
// //
// // ⏱️ TIME COMPLEXITY: O(M + N) where M = len(a), N = len(b)
// //    → Each iteration of the while loop consumes exactly ONE node
// //      (from either a or b).
// //    → Total iterations = M + N (all nodes are consumed).
// //    → Step 3 is O(1) — just one pointer assignment.
// //    → Interview answer: "Linear in the total number of nodes, O(M+N).
// //      Each node is visited and attached exactly once."
// //
// // 💾 SPACE COMPLEXITY: O(1)
// //    → We only allocate ONE new node (the dummy). Everything else
// //      is rewiring existing nodes from lists a and b.
// //    → No arrays, no recursion, no hash maps.
// //    → Interview answer: "Constant extra space, O(1). We reuse the
// //      existing nodes — no new allocations except the dummy."
// //    → If the interviewer asks about the dummy: "One extra node is
// //      negligible. Technically O(1)."
// //
// // 🎤 INTERVIEW FOLLOW-UP QUESTIONS TO PREPARE FOR:
// //
// //    Q1: "Can you solve this recursively?"
// //    → Yes! The recursive approach is elegant:
// //      ListNode* merge(ListNode* a, ListNode* b) {
// //          if (!a) return b;
// //          if (!b) return a;
// //          if (a->val <= b->val) {
// //              a->next = merge(a->next, b);
// //              return a;
// //          } else {
// //              b->next = merge(a, b->next);
// //              return b;
// //          }
// //      }
// //    → But recursion uses O(M+N) stack space — iterative is better
// //      for large lists. Mention both, prefer iterative.
// //
// //    Q2: "How would you merge K sorted lists?" (LC 23 — Hard!)
// //    → Use a Min-Heap (priority queue) of size K.
// //    → Push the head of each list into the heap.
// //    → Pop the smallest, attach to result, push that list's next.
// //    → Time: O(N log K), Space: O(K).
// //    → OR: Use this merge function in a divide-and-conquer fashion
// //      (merge pairs, then merge the results, like merge sort).
// //      Time: O(N log K), Space: O(1) iterative.
// //
// //    Q3: "What if the lists are NOT sorted?"
// //    → You can't merge in O(M+N). You'd need to sort first:
// //      O(M log M + N log N) to sort, then O(M+N) to merge.
// //    → Or just concatenate and sort: O((M+N) log(M+N)).
// //
// //    Q4: "Does this modify the original lists?"
// //    → YES! The nodes from a and b are rewired into the merged list.
// //    → After calling this function, the original a and b pointers
// //      no longer represent valid independent lists.
// //    → If you need to preserve the originals, you'd need to create
// //      new nodes (deep copy) — but that's O(M+N) space.
// //
// //    Q5: "How is this used in Merge Sort for linked lists?" (LC 148)
// //    → Merge Sort = Divide + Conquer + MERGE.
// //    → Divide: Find middle (LC 2095 technique!) and split.
// //    → Conquer: Recursively sort both halves.
// //    → Merge: THIS EXACT FUNCTION (LC 21)!
// //    → LC 148 literally calls LC 21 as a subroutine. Beautiful!
// // ================================================================