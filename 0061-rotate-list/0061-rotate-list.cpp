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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL)
            return head;
        // find the length of the list
        int n = 0; // n is length
        ListNode* temp = head;
        ListNode* tail = NULL;
        while (temp != NULL) {
            if (temp->next == NULL)
                tail = temp;
            n++;
            temp = temp->next;
        }

        k = k % n;
        if (k == 0)
            return head;
        // I have to place temp at (n-k)th position
        temp = head;
        for(int i = 1; i < n-k; i++){
            temp = temp->next;
        }

        tail->next = head;
        head = temp->next;
        temp->next = NULL;
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
//     ListNode* rotateRight(ListNode* head, int k) {

//         // ============================================================
//         // 🧠 INTUITION & PATTERN: MAKE CIRCULAR, THEN BREAK AT NEW TAIL
//         //         (Length + Modular Arithmetic Technique)
//         // ============================================================
//         // The core IDEA is:
//         //   "Rotating a list right by k is the same as CUTTING the list
//         //    at position (n-k) from the front and moving the back piece
//         //    to the front. The easiest way to do this is to temporarily
//         //    make the list CIRCULAR (connect tail to head), then BREAK
//         //    the circle at the right spot."
//         //
//         //    Visual (list: 1→2→3→4→5, k=2):
//         //      Original:    1 → 2 → 3 → 4 → 5 → NULL
//         //      Rotate R 2:  4 → 5 → 1 → 2 → 3 → NULL
//         //                         ↑
//         //                    cut here! (after node 3, which is position n-k=3)
//         //      The last 2 nodes (4,5) move to the front.
//         //
//         // 🆚 HOW IS THIS DIFFERENT FROM PREVIOUS PROBLEMS?
//         //   LC 19:   Fixed gap (n+1) to find nth from end.
//         //   LC 2095: Speed ratio 1:2 to find middle.
//         //   LC 160:  Length alignment across two lists.
//         //   LC 141:  Speed ratio 1:2 to detect cycle.
//         //   LC 142:  Floyd's Phase 1 + Phase 2.
//         //   LC 83:   Keeper + Scanner on sorted list.
//         //   LC 61:   NO two-pointer speed tricks! This uses a SINGLE
//         //            pointer with LENGTH COUNTING and MODULAR ARITHMETIC.
//         //            The "trick" is making the list circular temporarily.
//         //
//         // 🔑 KEY INSIGHT:
//         //   "Rotate right by k" = "The last k nodes become the first k nodes."
//         //   So we need to find the (n-k)th node — it becomes the NEW TAIL.
//         //   Everything after it becomes the new head portion.
//         // ============================================================

//         // 🔹 STEP 0: Handle EDGE CASES
//         //
//         // ⚠️ ATOMIC DETAIL #1 — Why check head->next == NULL?
//         //    → 0 nodes (head == NULL): Nothing to rotate. Return NULL.
//         //    → 1 node (head->next == NULL): Rotating a single node by
//         //      any amount gives the same list. Return it as-is.
//         //    → This also prevents division by zero later (k % n where n=0).
//         //    → And it prevents `tail->next = head` from creating a
//         //      self-loop on a single node unnecessarily.
//         if (head == NULL || head->next == NULL)
//             return head;  // ✅ 0 or 1 node — rotation has no effect

//         // 🔹 STEP 1: Find the LENGTH and the TAIL in ONE pass
//         //
//         // ⚠️ ATOMIC DETAIL #2 — Why do we need BOTH length and tail?
//         //    → Length (n): Needed to compute k % n and find the cut point.
//         //    → Tail: Needed to connect tail→head to make the list circular.
//         //      Without the tail, we'd need a SECOND pass to find it.
//         //      Getting both in one pass is more efficient!
//         //
//         // ⚠️ ATOMIC DETAIL #3 — How does the tail detection work?
//         //    `if (temp->next == NULL) tail = temp;`
//         //    → When temp->next is NULL, temp IS the last node (tail).
//         //    → This check happens INSIDE the counting loop, so we find
//         //      the tail "for free" while counting — no extra traversal!
//         //    → This is a neat trick: combine two tasks in one loop.
//         //
//         //    Visual (list: 1→2→3→4→5→NULL):
//         //      temp=1: next=2 (not NULL) → n=1
//         //      temp=2: next=3 (not NULL) → n=2
//         //      temp=3: next=4 (not NULL) → n=3
//         //      temp=4: next=5 (not NULL) → n=4
//         //      temp=5: next=NULL → tail=5 ✅, n=5
//         //      temp=NULL → loop exits
//         int n = 0;              // 📏 Length of the list
//         ListNode* temp = head;  // 🚶 Traversal pointer
//         ListNode* tail = NULL;  // 🏁 Will point to the last node

//         while (temp != NULL) {
//             if (temp->next == NULL)
//                 tail = temp;    // 🏁 Found the tail! (last node before NULL)
//             n++;                // 📏 Count this node
//             temp = temp->next;  // 🚶 Move forward
//         }
//         // ✅ After this loop: n = length, tail = last node, temp = NULL

//         // 🔹 STEP 2: Normalize k using modular arithmetic
//         //
//         // ⚠️ ATOMIC DETAIL #4 — WHY k % n? (CRITICAL!)
//         //    Rotating a list of length n by n positions gives the SAME list.
//         //      [1,2,3] rotated by 3 → [1,2,3] (full circle, no change!)
//         //    So rotating by k is the same as rotating by k % n.
//         //
//         //    Examples:
//         //      n=5, k=2  → 2 % 5 = 2  (rotate by 2)
//         //      n=5, k=7  → 7 % 5 = 2  (rotate by 2, same result!)
//         //      n=5, k=10 → 10 % 5 = 0 (full rotations, no change!)
//         //      n=5, k=12 → 12 % 5 = 2 (rotate by 2)
//         //
//         //    Without this, if k = 2,000,000,000 and n = 5, you'd loop
//         //    2 billion times → TLE (Time Limit Exceeded)! 💥
//         //    k % n reduces it to at most n-1 → always manageable.
//         //
//         // ⚠️ ATOMIC DETAIL #5 — Why check k == 0 AFTER the modulo?
//         //    If k is a multiple of n (e.g., k=10, n=5), then k%n = 0.
//         //    Rotating by 0 means NO rotation — return head as-is.
//         //    This also prevents the for-loop below from running with
//         //    n-k = n, which would put temp at the wrong position.
//         k = k % n;              // 🔄 Normalize k to [0, n-1]
//         if (k == 0)
//             return head;        // ✅ No rotation needed — full circles only

//         // 🔹 STEP 3: Find the NEW TAIL position (the cut point)
//         //
//         // ⚠️ ATOMIC DETAIL #6 — WHERE do we cut?
//         //    "Rotate right by k" means the LAST k nodes move to the front.
//         //    So the new tail is the (n-k)th node from the beginning.
//         //
//         //    Example (1→2→3→4→5, k=2):
//         //      n=5, k=2, n-k=3
//         //      New tail = 3rd node = node 3
//         //      New head = 4th node = node 4
//         //      Result: 4→5→1→2→3→NULL ✅
//         //
//         //    The for-loop `for(i=1; i<n-k; i++)` starts temp at head
//         //    (position 1) and moves it (n-k-1) times, landing on the
//         //    (n-k)th node.
//         //
//         //    Why i < n-k and not i <= n-k?
//         //    → temp starts at head (position 1, already counted).
//         //    → We need to reach position (n-k).
//         //    → Steps needed = (n-k) - 1 = n-k-1.
//         //    → Loop runs for i = 1, 2, ..., n-k-1 → exactly n-k-1 steps.
//         //    → If we used i <= n-k, we'd go one step too far!
//         //
//         //    Visual (n=5, k=2, n-k=3):
//         //      temp starts at 1 (position 1)
//         //      i=1: temp=2 (position 2)
//         //      i=2: temp=3 (position 3) → i < 3 is false → STOP ✅
//         //      temp is at node 3 = the new tail ✅
//         //
//         // 🆚 CONNECTION TO LC 19 (Remove Nth From End):
//         //    In LC 19, we used a GAP of (n+1) to find the predecessor
//         //    of the nth-from-end node. Here, we could ALSO think of
//         //    the (n-k)th node as the kth-from-end node's predecessor!
//         //    But since we already know n, direct counting is simpler.
//         //    No need for the two-pointer gap trick here.
//         temp = head;  // 🔄 Reset temp to head for the second traversal
//         for (int i = 1; i < n - k; i++) {
//             temp = temp->next;  // 🚶 Walk to the (n-k)th node
//         }
//         // ✅ temp is now at the NEW TAIL (the node that will point to NULL)

//         // 🔹 STEP 4: Perform the rotation (3-step rewiring)
//         //
//         // ⚠️ ATOMIC DETAIL #7 — The THREE rewiring steps and their ORDER:
//         //    This is the most critical part. The order MATTERS because
//         //    we're modifying pointers that we still need to read!
//         //
//         //    STEP 4a: tail->next = head (make the list circular)
//         //      → Connects the old tail to the old head, forming a loop.
//         //      → This MUST happen first, because after step 4c, the
//         //        old tail would be disconnected and we'd lose access.
//         //
//         //    STEP 4b: head = temp->next (set the new head)
//         //      → temp->next is the (n-k+1)th node = the new head.
//         //      → This MUST happen before step 4c, because step 4c
//         //        sets temp->next = NULL, which would destroy this link!
//         //
//         //    STEP 4c: temp->next = NULL (break the circle)
//         //      → The new tail (temp) should point to NULL, not loop back.
//         //      → This MUST happen last, after we've already saved the
//         //        new head from temp->next.
//         //
//         //    Visual (1→2→3→4→5, k=2, temp=3, tail=5):
//         //
//         //      Before:
//         //        1 → 2 → 3 → 4 → 5 → NULL
//         //                  ↑         ↑
//         //                temp      tail
//         //
//         //      Step 4a: tail->next = head
//         //        1 → 2 → 3 → 4 → 5 ─┐
//         //        ↑                    │
//         //        └────────────────────┘  (circular!)
//         //
//         //      Step 4b: head = temp->next (= 4)
//         //        head now points to 4 ✅
//         //
//         //      Step 4c: temp->next = NULL
//         //        1 → 2 → 3 → NULL    (broken circle)
//         //                  ↑
//         //                temp (new tail)
//         //
//         //      Final: head → 4 → 5 → 1 → 2 → 3 → NULL ✅🎯
//         //
//         //    ⚠️ WHAT IF YOU DO THE STEPS IN WRONG ORDER?
//         //      If you do 4c before 4b:
//         //        temp->next = NULL → now temp->next is NULL
//         //        head = temp->next → head = NULL → WRONG! 💥
//         //      If you do 4c before 4a:
//         //        temp->next = NULL → list is split
//         //        tail->next = head → still works, but conceptually messy
//         //      ORDER MATTERS! 4a → 4b → 4c is the safe sequence.
//         tail->next = head;      // 🔗 Step 4a: Make circular (tail → old head)
//         head = temp->next;      // 🏠 Step 4b: New head = node after new tail
//         temp->next = NULL;      // ✂️ Step 4c: Break circle (new tail → NULL)

//         // 🔹 STEP 5: Return the new head
//         //
//         // ⚠️ ATOMIC DETAIL #8 — The head HAS changed here!
//         //    Unlike LC 19, LC 2095, LC 83 where head stayed the same,
//         //    rotation almost ALWAYS changes the head (unless k%n == 0,
//         //    which we already handled). The new head is the (n-k+1)th
//         //    node of the original list.
//         //
//         //    This is why we saved `head = temp->next` in step 4b.
//         return head;            // 🎯 Return the rotated list's new head
//     }
// };

// // ================================================================
// // 📝 DETAILED SUMMARY FOR REVISION
// // ================================================================
// //
// // 🎯 PROBLEM:
// //    Given the head of a linked list, rotate the list to the RIGHT
// //    by k places. Return the new head.
// //    Example: [1,2,3,4,5], k=2 → [4,5,1,2,3]
// //
// // 🧩 PATTERN USED: Length Counting + Modular Arithmetic + Circular Rewiring
// //    (NOT a two-pointer speed/gap trick — this is a "measure then cut" approach)
// //
// // 🏠 REAL-LIFE ANALOGY:
// //    Imagine a chain of paper clips 📎📎📎📎📎 laid out on a table.
// //    Your boss says "rotate the last 2 clips to the front."
// //
// //    Step 1: You COUNT the total clips (n=5) and find the LAST clip (tail).
// //    Step 2: You realize rotating by 7 is the same as rotating by 2
// //            (because 7 % 5 = 2). No need to do extra work!
// //    Step 3: You connect the last clip to the first clip, making a
// //            CIRCLE of paper clips. 🔄
// //    Step 4: You count 3 clips from the start (n-k = 5-2 = 3) and
// //            SNIP the chain right after the 3rd clip. ✂️
// //    Step 5: The clip after the snip (4th clip) is your new start.
// //            The chain is now: 4→5→1→2→3. Done! 🎉
// //
// // 📌 STEP-BY-STEP RECIPE:
// //    1. Edge case: 0 or 1 node → return head.
// //    2. Traverse once: count length (n) and find tail.
// //    3. Normalize: k = k % n. If k == 0 → return head.
// //    4. Walk to the (n-k)th node — this is the new tail.
// //    5. Rewire in order:
// //       a. tail->next = head   (make circular)
// //       b. head = temp->next   (save new head)
// //       c. temp->next = NULL   (break circle)
// //    6. Return new head.
// //
// // ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
// //    ☐ k % n is MANDATORY — k can be up to 2×10⁹, n can be small.
// //      Without modulo, you'd TLE or get wrong cut position.
// //    ☐ Check k == 0 AFTER modulo — k could be a multiple of n.
// //      Without this, n-k = n, and the for-loop goes out of bounds.
// //    ☐ Find tail DURING the counting loop — saves a second traversal.
// //    ☐ For-loop: `i < n-k`, NOT `i <= n-k` — off-by-one!
// //      temp starts at position 1 (head), needs (n-k-1) steps.
// //    ☐ Rewiring ORDER: 4a → 4b → 4c. Wrong order = lost pointers.
// //      → 4b before 4c is critical (save new head before breaking link).
// //    ☐ Head CHANGES in this problem (unlike LC 19, 83, 2095).
// //      → Must return the new head, not the old one.
// //    ☐ Edge case: k == 0 or k == n → no rotation → return early.
// //    ☐ Edge case: k > n → k % n handles it automatically.
// //
// // 🔗 COMPARISON WITH ALL PREVIOUS PROBLEMS:
// //    ┌──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐
// //    │    Aspect    │ LC 19        │ LC 2095      │ LC 160       │ LC 141/142   │ LC 83        │ LC 61        │
// //    │              │ (Nth End)    │ (Mid Delete) │ (Intersect)  │ (Cycle)      │ (Duplicates) │ (Rotate)     │
// //    ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
// //    │ Technique    │ Fixed gap    │ 1:2 speed    │ Align length │ Floyd's      │ Keep+Scan    │ Measure+Cut  │
// //    │ Pointers     │ 2 (s,f)      │ 3 (p,s,f)    │ 2 (tA,tB)    │ 2 (s,f)      │ 2 (a,b)      │ 1 (temp)+tail│
// //    │ Passes       │ ~1           │ 1            │ 3            │ 1-2          │ 1            │ 2            │
// //    │ Key math     │ gap = n+1    │ mid = N/2    │ diff=|A-B|   │ L = nC-K     │ sorted=adj   │ k % n, n-k   │
// //    │ Circular?    │ No           │ No           │ No           │ YES (detect) │ No           │ YES (temp!)  │
// //    │ Head changes?│ Maybe        │ No (2+ nodes)│ No           │ No           │ No           │ YES (always) │
// //    │ Edge case    │ Delete head  │ 1-node       │ No intersect │ No cycle     │ 0/1 node     │ k%n == 0     │
// //    └──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┘
// //
// //    🔑 KEY OBSERVATION:
// //    LC 61 is unique because:
// //    1. It TEMPORARILY creates a cycle (tail→head) and then breaks it.
// //       LC 141/142 DETECT existing cycles; LC 61 CREATES one on purpose!
// //    2. The head ALWAYS changes (unless k%n==0). Most other problems
// //       keep the head the same.
// //    3. It uses MODULAR ARITHMETIC — the only problem in this set that
// //       requires math beyond simple pointer manipulation.
// //
// // ⏱️ TIME COMPLEXITY: O(N) where N = length of the list
// //    → Pass 1: Count length + find tail → O(N).
// //    → Pass 2: Walk to (n-k)th node → O(N-k) ≤ O(N).
// //    → Rewiring: O(1) — just 3 pointer assignments.
// //    → Total: O(N) + O(N) = O(N).
// //    → Interview answer: "Two passes through the list, still O(N)."
// //
// // 💾 SPACE COMPLEXITY: O(1)
// //    → Only a few pointers (temp, tail) and integers (n, k).
// //    → No arrays, no hash maps, no recursion.
// //    → Interview answer: "Constant space, O(1)."
// //
// // 🎤 INTERVIEW FOLLOW-UP QUESTIONS TO PREPARE FOR:
// //
// //    Q1: "Can you do this in ONE pass?"
// //    → Yes! Use two pointers with a gap of k (similar to LC 19).
// //      Move fast k steps ahead, then move both until fast->next == NULL.
// //      Slow will be at the new tail. But you still need the tail pointer,
// //      so it's not strictly one pass — you need to know where the end is.
// //      The two-pass approach is clearer and equally O(N).
// //
// //    Q2: "What if k is negative (rotate LEFT)?"
// //    → Rotate left by k = rotate right by (n - k%n).
// //    → Convert to right rotation and use the same logic.
// //
// //    Q3: "How is this different from reversing a linked list?"
// //    → Reversal (LC 206): changes the DIRECTION of all pointers.
// //    → Rotation (LC 61): keeps direction, just changes the START point.
// //    → Rotation is like cutting a circular necklace and re-clasping it
// //      at a different bead. Reversal is like flipping the necklace over.
// //
// //    Q4: "What about the memory of the original nodes?"
// //    → No nodes are created or deleted — we only rewire existing pointers.
// //    → All original nodes are preserved, just in a different order.
// //    → This is an in-place operation: O(1) space, no allocations.
// // ================================================================