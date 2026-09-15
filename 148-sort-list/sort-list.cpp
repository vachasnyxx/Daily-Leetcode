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
    ListNode* merge(ListNode* a, ListNode* b) {

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
    ListNode* sortList(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        // to find the left middle
        ListNode* slow = head;
        ListNode* fast = head;

         while(fast->next != NULL && fast->next->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
        }
        //now slow is at left middle
        ListNode* a = head;
        ListNode* b = slow->next;
        slow->next = NULL;
        a = sortList(a);
        b = sortList(b);
        ListNode* c = merge(a,b);
        return c;

    }
};




    //                 TWO-POINTER BASICS
    //                /        |         \
    //       LC 19 (Gap)  LC 141 (Cycle)  LC 160 (Align)
    //            |            |
    //       LC 2095 (Mid)  LC 142 (Entrance)
    //            |
    //            ↓
    //       LC 83 (Dedup)    LC 61 (Rotate)
    //            |
    //            ↓
    //       LC 21 (Merge 2) ←── DUMMY NODE pattern
    //         /         \
    //        ↓           ↓
    // LC 148 (Sort)   LC 23 (Merge K)
    // = Mid + Merge    = Repeated Merge

// Final Takeaway: LC 148 proves that easy problems are subroutines for hard problems. Master LC 2095 and LC 21 deeply, and LC 148 becomes almost trivial — just glue them together with recursion! 




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

//     // ============================================================
//     // 🔧 HELPER FUNCTION: Merge Two Sorted Lists (EXACTLY LC 21)
//     // ============================================================
//     // Same function from LC 21. Merges two SORTED lists into one.
//     // Used here as the "CONQUER" step of Merge Sort.
//     // (See LC 21 comments for full detail.)
//     // ============================================================
//     ListNode* merge(ListNode* a, ListNode* b) {

//         ListNode* c = new ListNode(100);  // 🏗️ Dummy node
//         ListNode* temp = c;               // 🔨 Builder pointer

//         while (a != NULL && b != NULL) {
//             if (a->val <= b->val) {
//                 temp->next = a;
//                 a = a->next;
//                 temp = temp->next;
//             }
//             else {
//                 temp->next = b;
//                 b = b->next;
//                 temp = temp->next;
//             }
//         }
//         if (a == NULL) temp->next = b;
//         else temp->next = a;
//         return c->next;
//     }

//     // ============================================================
//     // 🧠 INTUITION & PATTERN: MERGE SORT ON A LINKED LIST
//     //         (Divide & Conquer using LC 2095 + LC 21 as subroutines!)
//     // ============================================================
//     // The core IDEA is:
//     //   "Merge Sort works in three steps:
//     //      1. DIVIDE: Split the list into two halves (find the middle).
//     //      2. CONQUER: Recursively sort each half.
//     //      3. COMBINE: Merge the two sorted halves into one.
//     //    The base case is a list of 0 or 1 nodes — already sorted!"
//     //
//     // 🤯 THE BEAUTIFUL CONNECTION:
//     //   This single problem COMBINES two previous problems:
//     //   → DIVIDE step = LC 2095 (Find Middle) with a slight tweak
//     //   → COMBINE step = LC 21 (Merge Two Sorted Lists) exactly
//     //   → CONQUER step = Recursion (the function calls itself!)
//     //
//     //   If you've mastered LC 2095 and LC 21, LC 148 is just
//     //   GLUING them together with recursion. That's it!
//     //
//     // 🆚 WHY MERGE SORT (not Quick Sort or Heap Sort)?
//     //   → Merge Sort is the BEST sorting algorithm for linked lists.
//     //   → Arrays: Quick Sort is preferred (random access, cache-friendly).
//     //   → Linked Lists: Merge Sort wins because:
//     //     a) No random access needed (you can't do arr[i] in O(1)).
//     //     b) Splitting is O(1) — just break a pointer (no shifting).
//     //     c) Merging is O(1) space — just rewire pointers (no extra array).
//     //     d) Guaranteed O(N log N) — no worst-case O(N²) like Quick Sort.
//     //
//     // 🆚 HOW IS THIS DIFFERENT FROM PREVIOUS PROBLEMS?
//     //   All previous problems were SINGLE-PASS or TWO-PASS pointer tricks.
//     //   LC 148 is the first RECURSIVE problem in our set. It uses
//     //   DIVIDE & CONQUER — the list is split, sorted, and merged
//     //   in a tree-like fashion. The recursion depth is O(log N).
//     // ============================================================
//     ListNode* sortList(ListNode* head) {

//         // 🔹 STEP 0: BASE CASE of the recursion
//         //
//         // ⚠️ ATOMIC DETAIL #1 — Why is this the base case?
//         //    → 0 nodes (head == NULL): Empty list is trivially sorted.
//         //    → 1 node (head->next == NULL): A single node is trivially sorted.
//         //    → You can't split a 0 or 1 node list further — recursion must stop.
//         //    → Without this, the recursion would go infinite (trying to
//         //      split a 1-node list forever).
//         //
//         //    This is the "leaf" of the recursion tree:
//         //      [4, 2, 1, 3]
//         //       /        \
//         //     [4, 2]    [1, 3]
//         //     /    \    /    \
//         //   [4]   [2] [1]   [3]   ← BASE CASES (1 node each)
//         //     \    /    \    /
//         //     [2, 4]    [1, 3]    ← MERGE step
//         //       \        /
//         //       [1, 2, 3, 4]      ← FINAL MERGE
//         if (head == NULL || head->next == NULL) return head;

//         // 🔹 STEP 1: DIVIDE — Find the LEFT MIDDLE to split the list
//         //
//         // ⚠️ ATOMIC DETAIL #2 — This is a VARIANT of LC 2095!
//         //    In LC 2095 (Delete Middle), the loop condition was:
//         //      `while(fast != NULL && fast->next != NULL)`
//         //    Here, the loop condition is:
//         //      `while(fast->next != NULL && fast->next->next != NULL)`
//         //
//         //    WHY THE DIFFERENCE? Because we need the LEFT middle, not the right!
//         //
//         //    LC 2095 loop (RIGHT middle for even length):
//         //      List [1, 2, 3, 4]: slow ends at 3 (right middle)
//         //      → Good for deletion (we delete the 2nd middle).
//         //
//         //    LC 148 loop (LEFT middle for even length):
//         //      List [1, 2, 3, 4]: slow ends at 2 (left middle)
//         //      → Good for splitting (we split into [1,2] and [3,4]).
//         //
//         //    WHY LEFT MIDDLE IS CRITICAL FOR SORTING:
//         //    Consider a 2-node list [1, 2]:
//         //      → LEFT middle = node 1. Split: [1] and [2]. ✅ Both halves smaller!
//         //      → RIGHT middle = node 2. Split: [1, 2] and []. ❌ First half = original!
//         //        → Recursion on [1, 2] would call sortList([1, 2]) again → INFINITE LOOP! 💥
//         //
//         //    The left middle GUARANTEES that both halves are STRICTLY SMALLER
//         //    than the original list. This ensures the recursion terminates.
//         //
//         //    Visual walkthrough (list [4, 2, 1, 3]):
//         //      Start: slow=4, fast=4
//         //      Check: fast->next(2) != NULL ✅ && fast->next->next(1) != NULL ✅
//         //      Iter 1: slow=2, fast=1
//         //      Check: fast->next(3) != NULL ✅ && fast->next->next(NULL) == NULL ❌
//         //      Loop stops. slow=2 = LEFT MIDDLE ✅
//         //      Split: [4, 2] and [1, 3]
//         //
//         //    Visual walkthrough (list [4, 2, 1, 3, 5]):
//         //      Start: slow=4, fast=4
//         //      Check: fast->next(2) != NULL ✅ && fast->next->next(1) != NULL ✅
//         //      Iter 1: slow=2, fast=1
//         //      Check: fast->next(3) != NULL ✅ && fast->next->next(5) != NULL ✅
//         //      Iter 2: slow=1, fast=5
//         //      Check: fast->next(NULL) == NULL ❌
//         //      Loop stops. slow=1 = TRUE MIDDLE ✅
//         //      Split: [4, 2, 1] and [3, 5]
//         //
//         // ⚠️ ATOMIC DETAIL #3 — Why no `prevslow` pointer here?
//         //    In LC 2095, we needed `prevslow` to DELETE the middle node
//         //    (we needed the predecessor to rewire). Here, we don't delete
//         //    anything — we just SPLIT the list by setting slow->next = NULL.
//         //    `slow` itself is the last node of the left half. No predecessor needed!
//         ListNode* slow = head;  // 🐢 Tortoise — will land on LEFT middle
//         ListNode* fast = head;  // 🐇 Hare — 2x speed

//         // ⚠️ ATOMIC DETAIL #4 — The loop condition in detail:
//         //    `fast->next != NULL && fast->next->next != NULL`
//         //    → `fast->next != NULL`: Ensures fast has at least 1 more step.
//         //    → `fast->next->next != NULL`: Ensures fast can take 2 steps.
//         //      If fast can't take 2 full steps, slow shouldn't move either.
//         //      This is what makes slow stop at the LEFT middle for even lengths.
//         //
//         //    Contrast with LC 2095's `fast != NULL && fast->next != NULL`:
//         //    → LC 2095: fast takes its LAST step even if it lands on NULL.
//         //      This pushes slow one step further → RIGHT middle.
//         //    → LC 148: fast only moves if it can take TWO full steps
//         //      (landing on a real node, not NULL). This keeps slow
//         //      one step earlier → LEFT middle.
//         //
//         //    The difference is subtle but CRITICAL. One character change
//         //    (checking fast->next->next instead of fast->next) switches
//         //    between left and right middle!
//         while (fast->next != NULL && fast->next->next != NULL) {
//             slow = slow->next;          // 🐢 1 step
//             fast = fast->next->next;    // 🐇 2 steps
//         }
//         // ✅ slow is now at the LEFT MIDDLE of the list

//         // 🔹 STEP 2: SPLIT the list into two halves
//         //
//         // ⚠️ ATOMIC DETAIL #5 — The split operation (3 lines, huge impact)
//         //    `ListNode* a = head;`        → Left half starts at head.
//         //    `ListNode* b = slow->next;`  → Right half starts after middle.
//         //    `slow->next = NULL;`         → BREAK the link! Left half ends here.
//         //
//         //    Before split:  head → 4 → 2 → 1 → 3 → NULL
//         //                         slow=2
//         //    After split:   a → 4 → 2 → NULL   (left half)
//         //                   b → 1 → 3 → NULL   (right half)
//         //
//         //    ⚠️ ATOMIC DETAIL #6 — WHY is `slow->next = NULL` so important?
//         //    Without it, the left half would still point to the right half:
//         //      a → 4 → 2 → 1 → 3 → NULL  (still the full list!)
//         //    The recursive call `sortList(a)` would sort the ENTIRE list,
//         //    not just the left half. And `sortList(b)` would sort the right
//         //    half again. You'd get wrong results AND potential infinite recursion.
//         //    Breaking the link is what makes the DIVIDE step actually divide!
//         //
//         //    ⚠️ ATOMIC DETAIL #7 — ORDER of these 3 lines matters!
//         //    → `b = slow->next` MUST come BEFORE `slow->next = NULL`.
//         //      If you NULL out slow->next first, b would be NULL — WRONG!
//         //    → `a = head` can be anywhere (head doesn't change).
//         ListNode* a = head;           // 📋 Left half: head to slow
//         ListNode* b = slow->next;     // 📋 Right half: slow->next to end
//         slow->next = NULL;            // ✂️ BREAK the list! (critical!)

//         // 🔹 STEP 3: CONQUER — Recursively sort both halves
//         //
//         // ⚠️ ATOMIC DETAIL #8 — The recursion is where the magic happens
//         //    → `sortList(a)` sorts the left half [4, 2] → [2, 4]
//         //    → `sortList(b)` sorts the right half [1, 3] → [1, 3]
//         //    → Each recursive call further splits until base case (1 node).
//         //    → Then the merge step combines them back in sorted order.
//         //
//         //    Full recursion tree for [4, 2, 1, 3]:
//         //
//         //              sortList([4,2,1,3])
//         //              /                 \
//         //       sortList([4,2])      sortList([1,3])
//         //        /        \           /        \
//         //    sortList([4]) sortList([2]) sortList([1]) sortList([3])
//         //      return 4      return 2      return 1      return 3
//         //        \        /           \        /
//         //      merge([4],[2])       merge([1],[3])
//         //        = [2,4]              = [1,3]
//         //              \                 /
//         //           merge([2,4], [1,3])
//         //             = [1,2,3,4] ✅
//         //
//         a = sortList(a);  // 🔄 Recursively sort left half
//         b = sortList(b);  // 🔄 Recursively sort right half

//         // 🔹 STEP 4: COMBINE — Merge the two sorted halves
//         //
//         // ⚠️ ATOMIC DETAIL #9 — This is EXACTLY LC 21!
//         //    After the recursive calls, `a` and `b` are now SORTED lists.
//         //    We merge them using the same dummy-node zipper technique
//         //    from LC 21. The result `c` is the fully sorted list.
//         //
//         //    Example: a = [2, 4] (sorted), b = [1, 3] (sorted)
//         //    merge(a, b) → [1, 2, 3, 4] ✅
//         ListNode* c = merge(a, b);  // 🔗 Merge two sorted halves (LC 21!)

//         // 🔹 STEP 5: Return the sorted list
//         return c;  // 🎯 Return the merged, sorted result
//     }
// };

// // ================================================================
// // 📝 DETAILED SUMMARY FOR REVISION
// // ================================================================
// //
// // 🎯 PROBLEM:
// //    Sort a linked list in O(N log N) time and O(1) extra space
// //    (follow-up). Return the head of the sorted list.
// //    Example: [4, 2, 1, 3] → [1, 2, 3, 4]
// //
// // 🧩 PATTERN USED: Merge Sort (Divide & Conquer) on Linked List
// //    = LC 2095 (Find Middle, tweaked) + LC 21 (Merge Two Lists) + Recursion
// //
// // 🏠 REAL-LIFE ANALOGY:
// //    Imagine you have a messy deck of cards and you want to sort them.
// //    Instead of comparing every card to every other card (slow!), you:
// //
// //    1. SPLIT the deck in half. (Find the middle card, cut the deck.)
// //    2. Ask two friends to sort each half. (Recursion!)
// //    3. Each friend splits their half again, and again, until everyone
// //       has just ONE card. (Base case — one card is already sorted!)
// //    4. Now MERGE: Two friends compare their single cards and combine
// //       into a sorted pair. Then pairs merge into sorted quads. Then
// //       quads merge into the final sorted deck.
// //
// //    The splitting is like cutting a rope in half (O(1) — just one cut).
// //    The merging is like zipping two sorted lines of people into one
// //    sorted line (LC 21 — the zipper technique).
// //
// // 📌 STEP-BY-STEP RECIPE:
// //    1. Base case: 0 or 1 node → return head (already sorted).
// //    2. Find LEFT middle using slow/fast (LC 2095 variant).
// //    3. Split: a = head, b = slow->next, slow->next = NULL.
// //    4. Recurse: a = sortList(a), b = sortList(b).
// //    5. Merge: c = merge(a, b) using LC 21.
// //    6. Return c.
// //
// // ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
// //    ☐ LEFT middle, NOT right middle — critical for even-length lists.
// //      → Right middle on [1,2] gives split [1,2] + [] → infinite recursion!
// //      → Left middle on [1,2] gives split [1] + [2] → terminates correctly.
// //    ☐ Loop condition: `fast->next != NULL && fast->next->next != NULL`
// //      → NOT the same as LC 2095's `fast != NULL && fast->next != NULL`.
// //      → The extra `.next` check is what makes it LEFT middle.
// //    ☐ `slow->next = NULL` is MANDATORY — actually breaks the list.
// //      → Without it, left half still connects to right half → no divide.
// //    ☐ `b = slow->next` BEFORE `slow->next = NULL` — order matters!
// //      → NULL first → b becomes NULL → right half is lost.
// //    ☐ Base case MUST include head->next == NULL (not just head == NULL).
// //      → Without it, 1-node lists try to split → infinite recursion.
// //    ☐ The merge function handles NULL inputs (from empty halves).
// //      → Though with proper splitting, halves are always ≥ 1 node.
// //    ☐ Recursion depth is O(log N) — safe for N up to ~10⁵.
// //      → For N = 10⁵, depth ≈ 17. No stack overflow.
// //
// // 🔗 THE GRAND CONNECTION — ALL PREVIOUS PROBLEMS:
// //    ┌──────────────┬──────────────┬──────────────────────────────────────────────┐
// //    │   Problem    │ Technique    │ Role in LC 148                               │
// //    ├──────────────┼──────────────┼──────────────────────────────────────────────┤
// //    │ LC 2095      │ Find Middle  │ DIVIDE step (tweaked for LEFT middle)        │
// //    │ LC 21        │ Merge Two    │ COMBINE step (exact reuse of merge function) │
// //    │ LC 148       │ Merge Sort   │ = LC 2095 + LC 21 + Recursion               │
// //    ├──────────────┼──────────────┼──────────────────────────────────────────────┤
// //    │ LC 19        │ Fixed gap    │ Not used here, but same two-pointer family   │
// //    │ LC 160       │ Length align │ Not used here                                │
// //    │ LC 141/142   │ Floyd's      │ Same slow/fast concept, different goal       │
// //    │ LC 83        │ Keep+Scan    │ Not used here                                │
// //    │ LC 61        │ Measure+Cut  │ Similar "find position then cut" idea        │
// //    │ LC 2326      │ Spiral       │ Not related (matrix problem)                 │
// //    │ LC 23        │ Merge K      │ Uses LC 21's merge — same building block!    │
// //    └──────────────┴──────────────┴──────────────────────────────────────────────┘
// //
// //    🔑 KEY OBSERVATION:
// //    LC 148 is the CULMINATION of the linked list problem set.
// //    It combines the two most important linked list operations:
// //    → Finding the middle (LC 2095)
// //    → Merging two sorted lists (LC 21)
// //    If you can solve LC 148, you've truly mastered linked lists!
// //
// //    THE PROBLEM FAMILY TREE:
// //
// //         LC 2095 (Mid)          LC 21 (Merge 2)
// //              \                    /
// //               \                  /
// //                → LC 148 (Sort) ←
// //                     |
// //                     ↓
// //                LC 23 (Merge K) ← also uses LC 21
// //
// // ⏱️ TIME COMPLEXITY: O(N log N)
// //    → At each level of recursion, we split the list (O(N) to find middle)
// //      and merge the halves (O(N) to merge).
// //    → The recursion tree has log N levels (halving each time).
// //    → Total: O(N) per level × O(log N) levels = O(N log N).
// //    → This is OPTIMAL for comparison-based sorting.
// //    → Interview answer: "O(N log N) — same as merge sort on arrays.
// //      Each level does O(N) work for splitting and merging, and there
// //      are log N levels of recursion."
// //
// // 💾 SPACE COMPLEXITY: O(log N) for recursion stack
// //    → The recursion depth is O(log N) (halving each time).
// //    → Each recursive call uses O(1) extra space (a few pointers).
// //    → Total: O(log N) stack space.
// //    → The follow-up asks for O(1) space. To achieve that, you'd need
// //      an ITERATIVE (bottom-up) merge sort:
// //      → Start by merging pairs of 1-node lists.
// //      → Then merge pairs of 2-node lists.
// //      → Then 4-node, 8-node, ... until the whole list is sorted.
// //      → No recursion → O(1) space. But much harder to code!
// //    → Interview answer: "O(log N) for the recursion stack. The
// //      follow-up O(1) version uses bottom-up iterative merge sort,
// //      which avoids recursion entirely."
// //
// // 🎤 INTERVIEW FOLLOW-UP QUESTIONS TO PREPARE FOR:
// //
// //    Q1: "Can you do this in O(1) space?" (The follow-up!)
// //    → Yes, with BOTTOM-UP iterative merge sort:
// //      → Step size starts at 1, doubles each round: 1, 2, 4, 8, ...
// //      → In each round, split the list into chunks of `step` size,
// //        merge adjacent pairs, and reconnect.
// //      → No recursion → O(1) stack space.
// //      → Code is significantly longer (~40 lines vs ~15 lines).
// //      → Mention it in interviews but code the recursive version first.
// //
// //    Q2: "Why not Quick Sort for linked lists?"
// //    → Quick Sort needs random access for efficient partitioning (arr[i]).
// //    → Linked lists don't support O(1) random access.
// //    → Quick Sort's worst case is O(N²) (already sorted input).
// //    → Merge Sort guarantees O(N log N) always.
// //    → Merge Sort's merge step is naturally O(1) space for linked lists
// //      (just rewire pointers), unlike arrays (needs O(N) temp array).
// //    → So Merge Sort is strictly better for linked lists.
// //
// //    Q3: "How does this compare to sorting an array?"
// //    → Array Merge Sort: O(N log N) time, O(N) space (temp array for merge).
// //    → List Merge Sort: O(N log N) time, O(log N) space (recursion only).
// //    → Linked lists WIN on space because merging doesn't need extra memory!
// //
// //    Q4: "What if the list is already sorted?"
// //    → Merge Sort still does O(N log N) work (it doesn't detect sortedness).
// //    → Insertion Sort would be O(N) for already-sorted lists.
// //    → But for the general case, Merge Sort is the best choice.
// //
// //    Q5: "Can you use LC 23 (Merge K Lists) to sort?"
// //    → Yes! Treat each node as a 1-node list. Put all N nodes into an
// //      array of N lists. Call mergeKLists(arr).
// //    → With min-heap: O(N log N) time, O(N) space.
// //    → This works but is overkill — LC 148's approach is cleaner.
// // ================================================================