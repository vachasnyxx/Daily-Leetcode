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
    ListNode* mergeKLists(vector<ListNode*>& arr) {
        if(arr.size() == 0) return NULL;
        while(arr.size() > 1){
            ListNode* a = arr[0];
            arr.erase(arr.begin());
            ListNode* b =arr[0];
            arr.erase(arr.begin());
            ListNode* c = merge(a,b);
            arr.push_back(c);
        }
        return arr[0];
    }
};





// LC 21 (Merge 2 Lists) ──→ LC 23 (Merge K Lists)
//          │                          │
//          ↓                          ↓
//     LC 148 (Sort List)         LC 295 (Find Median)
//     = Find Mid (LC 2095)       = Two Heaps
//     + Merge (LC 21)



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
//     // This is the SAME function you wrote for LeetCode 21.
//     // Reusing it here is EXCELLENT design — you recognized that
//     // merging K lists can be broken down into repeated 2-list merges.
//     //
//     // Quick recap (see LC 21 comments for full detail):
//     //   → Dummy node `c` avoids special-casing the first insertion.
//     //   → `temp` builds the result by picking the smaller front node.
//     //   → After one list is exhausted, attach the rest of the other.
//     //   → Return c->next (skip dummy).
//     //   → O(M+N) time, O(1) space per merge call.
//     // ============================================================
//     ListNode* merge(ListNode* a, ListNode* b) {

//         ListNode* c = new ListNode(100);  // 🏗️ Dummy node (value irrelevant)
//         ListNode* temp = c;               // 🔨 Builder pointer

//         while (a != NULL && b != NULL) {
//             if (a->val <= b->val) {
//                 temp->next = a;           // 📌 Pick from list a
//                 a = a->next;
//                 temp = temp->next;
//             }
//             else {
//                 temp->next = b;           // 📌 Pick from list b
//                 b = b->next;
//                 temp = temp->next;
//             }
//         }
//         if (a == NULL) temp->next = b;    // 🔗 Attach remainder
//         else temp->next = a;
//         return c->next;                   // 🎯 Skip dummy
//     }

//     // ============================================================
//     // 🧠 INTUITION & PATTERN: SEQUENTIAL PAIRWISE MERGING
//     //         (Reduce K lists → 1 list by merging two at a time)
//     // ============================================================
//     // The core IDEA is:
//     //   "You know how to merge TWO sorted lists (LC 21). So to merge
//     //    K lists, just keep merging the first two lists in the array,
//     //    replace them with the merged result, and repeat until only
//     //    ONE list remains. It's like a tournament bracket where you
//     //    keep combining pairs until one champion remains."
//     //
//     // 🆚 HOW DOES THIS BUILD ON LC 21?
//     //   LC 21:  Merge 2 sorted lists → 1 sorted list.
//     //   LC 23:  Merge K sorted lists → 1 sorted list.
//     //   LC 23 literally USES LC 21 as a subroutine! This is a classic
//     //   example of how mastering easy problems unlocks hard ones.
//     //
//     // ⚠️ IMPORTANT: Your approach is SEQUENTIAL merging.
//     //   It works correctly but is NOT the most optimal.
//     //   → Your approach: O(N × K) time (explained below).
//     //   → Optimal (min-heap or divide & conquer): O(N log K) time.
//     //   Both are valid in interviews, but you should know the optimal
//     //   too. I'll explain all three in the summary.
//     // ============================================================
//     ListNode* mergeKLists(vector<ListNode*>& arr) {

//         // 🔹 STEP 0: Handle the edge case of an EMPTY input array
//         //
//         // ⚠️ ATOMIC DETAIL #1 — Why check arr.size() == 0?
//         //    → If the input vector is empty (no lists at all), there's
//         //      nothing to merge. Return NULL.
//         //    → Without this check, `arr[0]` at the end would be an
//         //      OUT-OF-BOUNDS access → undefined behavior / crash! 💥
//         //    → Note: arr could also contain NULL lists (e.g., [[], [1,2]]).
//         //      The merge function handles NULL inputs gracefully (if a
//         //      is NULL, it returns b; if b is NULL, it returns a). So
//         //      NULL lists inside the array are NOT a problem.
//         //
//         //    Examples:
//         //      arr = [] → return NULL ✅
//         //      arr = [[]] → arr.size()=1, loop doesn't run, return arr[0]=NULL ✅
//         //      arr = [[1,2], [], [3]] → merge handles the empty list fine ✅
//         if (arr.size() == 0) return NULL;

//         // 🔹 STEP 1: Repeatedly merge the first two lists until one remains
//         //
//         // ⚠️ ATOMIC DETAIL #2 — The while condition `arr.size() > 1`
//         //    → We keep merging as long as there are 2 or more lists.
//         //    → When only 1 list remains, that's our fully merged result.
//         //    → Each iteration REDUCES the array size by 1 (remove 2, add 1).
//         //    → So after (K-1) iterations, we go from K lists to 1 list.
//         //
//         //    Visual (arr = [L1, L2, L3, L4], K=4):
//         //      Iter 1: merge(L1, L2) → M1. arr = [L3, L4, M1]  (size 3)
//         //      Iter 2: merge(L3, L4) → M2. arr = [M1, M2]      (size 2)
//         //      Iter 3: merge(M1, M2) → M3. arr = [M3]          (size 1)
//         //      Loop exits. Return M3. ✅
//         //
//         // ⚠️ ATOMIC DETAIL #3 — The erase + push_back pattern
//         //    → `arr[0]` grabs the first list.
//         //    → `arr.erase(arr.begin())` removes it from the front.
//         //    → Then `arr[0]` grabs what WAS the second list (now first).
//         //    → `arr.erase(arr.begin())` removes it too.
//         //    → `merge(a, b)` combines them.
//         //    → `arr.push_back(c)` adds the merged result at the end.
//         //
//         //    Net effect: array shrinks by 1 each iteration.
//         //    2 lists removed from front, 1 merged list added to back.
//         //
//         // ⚠️ ATOMIC DETAIL #4 — PERFORMANCE CONCERN with `arr.erase(arr.begin())`
//         //    `vector::erase` at the BEGINNING is O(K) because all remaining
//         //    elements must shift left by one position. Over K iterations,
//         //    this adds O(K²) overhead just for the erasing!
//         //    → For small K, this is fine.
//         //    → For large K (e.g., 10⁴), this becomes a bottleneck.
//         //    → A better data structure would be a `queue` or `deque`
//         //      (O(1) pop from front) or use an index-based approach.
//         //    → Or better yet, use the optimal approaches (see summary).
//         //
//         //    In an interview, your logic is CORRECT. Mention the erase
//         //    cost and suggest using a queue or divide & conquer for
//         //    optimization. Interviewers love when you self-critique! 💯
//         while (arr.size() > 1) {
//             // 📌 Grab the first list
//             ListNode* a = arr[0];          // 📋 First list to merge
//             arr.erase(arr.begin());        // ✂️ Remove it from the array

//             // 📌 Grab the (new) first list (originally the second)
//             ListNode* b = arr[0];          // 📋 Second list to merge
//             arr.erase(arr.begin());        // ✂️ Remove it from the array

//             // 📌 Merge the two lists using your LC 21 function
//             ListNode* c = merge(a, b);     // 🔗 Merge a and b into c

//             // 📌 Put the merged result back into the array
//             arr.push_back(c);              // ➕ Add merged list to the end
//             // ✅ Array size decreased by 1 (removed 2, added 1)
//         }

//         // 🔹 STEP 2: Return the single remaining list
//         //
//         // ⚠️ ATOMIC DETAIL #5 — Why arr[0]?
//         //    → The while loop exits when arr.size() == 1.
//         //    → That single element is the fully merged list.
//         //    → arr[0] is safe because we already handled the size==0
//         //      case at the top, and the loop guarantees size >= 1 here.
//         //
//         //    What if the original array had only 1 list?
//         //    → arr.size() == 1 → while loop never executes → return arr[0].
//         //    → Correct! A single list is already "merged." ✅
//         //
//         //    What if all lists in the array are NULL?
//         //    → merge(NULL, NULL) → both a and b are NULL → loop skips →
//         //      temp->next = NULL → return NULL.
//         //    → After K-1 merges, arr[0] = NULL → return NULL. ✅
//         return arr[0];  // 🎯 The fully merged sorted list
//     }
// };

// // ================================================================
// // 📝 DETAILED SUMMARY FOR REVISION
// // ================================================================
// //
// // 🎯 PROBLEM:
// //    Given an array of K sorted linked lists, merge them all into
// //    one sorted linked list and return it.
// //    Example: [[1,4,5], [1,3,4], [2,6]] → [1,1,2,3,4,4,5,6]
// //
// // 🧩 PATTERN USED: Sequential Pairwise Merging (using LC 21 as subroutine)
// //    This is the SIMPLEST approach conceptually. Two optimal alternatives
// //    exist (Min-Heap and Divide & Conquer) — all explained below.
// //
// // 🏠 REAL-LIFE ANALOGY:
// //    Imagine you're a teacher who collected K stacks of exam papers,
// //    each stack already sorted by score. You want one big sorted stack.
// //
// //    YOUR APPROACH (Sequential):
// //      Take the first two stacks, merge them into one sorted stack.
// //      Put it at the back of the line. Take the next two, merge.
// //      Repeat until one giant stack remains.
// //      → Works, but the merged stacks keep getting bigger, so later
// //        merges take longer and longer. Like merging a 1000-page stack
// //        with a 10-page stack — most of the work is re-scanning the big one.
// //
// //    OPTIMAL APPROACH (Divide & Conquer — like a tournament):
// //      Pair up ALL stacks: merge stack 1&2, 3&4, 5&6, ...
// //      Then pair up the results: merge (1&2)&(3&4), (5&6)&(7&8), ...
// //      Like a sports tournament bracket — each round halves the players.
// //      → Every merge involves similarly-sized stacks → balanced work!
// //
// //    OPTIMAL APPROACH (Min-Heap — like a priority queue):
// //      Put the TOP paper from each stack into a "priority tray" (min-heap).
// //      Pick the smallest from the tray, put it in the result, and replace
// //      it with the next paper from the same stack.
// //      → Always picking the global minimum in O(log K) time.
// //
// // 📌 STEP-BY-STEP RECIPE (Your Approach):
// //    1. Edge case: if array is empty → return NULL.
// //    2. While array has more than 1 list:
// //       a. Remove the first two lists from the array.
// //       b. Merge them using the LC 21 merge function.
// //       c. Push the merged result back into the array.
// //    3. Return the single remaining list (arr[0]).
// //
// // ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
// //    ☐ Check arr.size() == 0 BEFORE accessing arr[0].
// //      → Empty array → arr[0] is out of bounds → crash.
// //    ☐ The merge function MUST handle NULL inputs gracefully.
// //      → arr could contain NULL lists (e.g., [[], [1,2]]).
// //      → Your merge handles this: if a==NULL, return b; if b==NULL, return a.
// //    ☐ `arr.erase(arr.begin())` is O(K) — shifts all elements left.
// //      → Not a correctness issue, but a performance issue.
// //      → In an interview, mention this and suggest a queue or index.
// //    ☐ After erase, the OLD arr[1] becomes the NEW arr[0].
// //      → So the second `arr[0]` correctly grabs the second original list.
// //    ☐ Each iteration reduces array size by exactly 1 (remove 2, add 1).
// //      → K-1 iterations total to go from K lists to 1.
// //    ☐ The merge function REWIRES nodes — no new data nodes are created.
// //      → Only the dummy node per merge call is extra allocation.
// //
// // 🔗 COMPARISON WITH ALL PREVIOUS PROBLEMS:
// //    ┌──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐
// //    │    Aspect    │ LC 19        │ LC 2095      │ LC 160       │ LC 141/142   │ LC 83        │ LC 61        │ LC 21        │
// //    │              │ (Nth End)    │ (Mid Delete) │ (Intersect)  │ (Cycle)      │ (Duplicates) │ (Rotate)     │ (Merge 2)    │
// //    ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
// //    │ Lists        │ 1            │ 1            │ 2            │ 1            │ 1            │ 1            │ 2            │
// //    │ Technique    │ Fixed gap    │ 1:2 speed    │ Align length │ Floyd's      │ Keep+Scan    │ Measure+Cut  │ Dummy+Zip    │
// //    │ Difficulty   │ Medium       │ Medium       │ Easy         │ Easy/Med     │ Easy         │ Medium       │ Easy         │
// //    ├──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┤
// //    │    LC 23 (THIS PROBLEM) — HARD! First "Hard" in our set!                                                              │
// //    ├──────────────┬──────────────────────────────────────────────────────────────────────────────────────────────────────────┤
// //    │ Lists        │ K sorted lists → merge into 1                                                                          │
// //    │ Technique    │ Sequential Pairwise Merging (reuses LC 21)                                                             │
// //    │ Difficulty   │ HARD (but easy with LC 21 as building block!)                                                          │
// //    │ Key insight  │ "If I can merge 2, I can merge K by repeating"                                                         │
// //    │ Builds on    │ LC 21 (merge two) is a DIRECT SUBROUTINE                                                               │
// //    └──────────────┴──────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// //
// //    🔑 KEY OBSERVATION:
// //    LC 23 is a perfect example of how EASY problems are building blocks
// //    for HARD problems. If you hadn't solved LC 21 first, LC 23 would
// //    be much harder. This is why grinding easy/medium patterns pays off!
// //
// // ⏱️ TIME COMPLEXITY (Your Sequential Approach): O(N × K)
// //    Let N = total number of nodes across ALL K lists.
// //    Let K = number of lists.
// //
// //    → Worst case: each merge involves an increasingly large list.
// //      Iter 1: merge(list of n₁, list of n₂) → O(n₁ + n₂)
// //      Iter 2: merge(list of n₁+n₂, list of n₃) → O(n₁ + n₂ + n₃)
// //      Iter 3: merge(list of n₁+n₂+n₃, list of n₄) → O(n₁+n₂+n₃+n₄)
// //      ...
// //      Iter K-1: merge(list of N-nₖ, list of nₖ) → O(N)
// //    → Total: O(N + N + N + ...) ≈ O(N × K) in the worst case.
// //    → Plus O(K²) for the vector erases (each erase is O(K)).
// //    → Interview answer: "My sequential approach is O(NK) time.
// //      I know the optimal is O(N log K) using divide & conquer or
// //      a min-heap. Let me explain those too."
// //
// // 💾 SPACE COMPLEXITY: O(1) auxiliary (not counting the output)
// //    → The merge function rewires existing nodes — O(1) per call.
// //    → The dummy nodes (one per merge call) are O(K) total, but
// //      negligible. In a strict analysis: O(K) for dummies.
// //    → The vector modifications are in-place (erase + push_back).
// //    → Interview answer: "O(1) extra space beyond the output, since
// //      we reuse all existing nodes."
// //
// // 🎤 THREE APPROACHES FOR INTERVIEWS (know all three!):
// //
// //    ┌─────────────────────┬───────────────┬───────────────┬─────────────────────┐
// //    │     Approach        │  Time         │  Space        │  Difficulty         │
// //    ├─────────────────────┼───────────────┼───────────────┼─────────────────────┤
// //    │ 1. Sequential (YOURS)│ O(N × K)     │ O(1)          │ Easiest to code     │
// //    │ 2. Min-Heap          │ O(N log K)   │ O(K)          │ Medium              │
// //    │ 3. Divide & Conquer  │ O(N log K)   │ O(1) iter.    │ Medium              │
// //    └─────────────────────┴───────────────┴───────────────┴─────────────────────┘
// //
// //    APPROACH 2 — MIN-HEAP (Priority Queue):
// //      → Create a min-heap of size K.
// //      → Push the HEAD of each list into the heap (compare by val).
// //      → Pop the smallest, attach to result, push that list's NEXT node.
// //      → Repeat until heap is empty.
// //      → Each pop/push is O(log K), done N times → O(N log K).
// //      → Space: O(K) for the heap.
// //      Code sketch:
// //        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
// //        for(auto list : arr) if(list) pq.push(list);
// //        while(!pq.empty()) {
// //            ListNode* node = pq.top(); pq.pop();
// //            temp->next = node; temp = temp->next;
// //            if(node->next) pq.push(node->next);
// //        }
// //
// //    APPROACH 3 — DIVIDE & CONQUER (Optimal + O(1) space):
// //      → Merge lists in PAIRS, like a tournament bracket.
// //      → Round 1: merge(0,1), merge(2,3), merge(4,5), ...
// //      → Round 2: merge(results of round 1 in pairs)
// //      → ... until 1 list remains.
// //      → log K rounds, each round processes all N nodes → O(N log K).
// //      → Space: O(1) iterative, O(log K) recursive.
// //      Code sketch:
// //        int interval = 1;
// //        while(interval < K) {
// //            for(int i = 0; i < K - interval; i += interval * 2)
// //                arr[i] = merge(arr[i], arr[i + interval]);
// //            interval *= 2;
// //        }
// //        return arr[0];
// //
// //    🏆 INTERVIEW STRATEGY:
// //      1. Start with your sequential approach (shows you can solve it).
// //      2. Self-critique: "This is O(NK). I can do better."
// //      3. Explain min-heap or divide & conquer (shows depth).
// //      4. Code the optimal if time permits.
// //      This progression impresses interviewers more than jumping
// //      straight to the optimal (which might look memorized).
// //
// // 🎤 INTERVIEW FOLLOW-UP QUESTIONS TO PREPARE FOR:
// //
// //    Q1: "What if K is very large (e.g., 10⁵) but each list is tiny?"
// //    → Sequential approach: O(NK) is terrible here.
// //    → Min-heap: O(N log K) handles it well.
// //    → Divide & conquer: O(N log K) also handles it well.
// //
// //    Q2: "What if the lists have very different lengths?"
// //    → All three approaches handle this correctly.
// //    → Min-heap is particularly efficient because short lists
// //      exit the heap early, reducing the heap size over time.
// //
// //    Q3: "Can you do this in a streaming fashion (lists arrive one by one)?"
// //    → Min-heap is ideal: just push the new list's head into the heap.
// //    → Sequential: you'd merge the new list with the running result.
// //      This is actually O(N) per new list → O(NK) total. Same as yours!
// //
// //    Q4: "How does this relate to Merge Sort?"
// //    → Merge Sort's merge step IS the LC 21 merge function.
// //    → Merge Sort on an array = divide & conquer merging of sub-arrays.
// //    → LC 23 = merge sort's merge step applied to linked lists.
// //    → LC 148 (Sort List) = full merge sort on a linked list, which
// //      uses LC 2095 (find middle) + LC 21 (merge two) as subroutines!
// //      The connections between these problems are beautiful! 🌟
// // ================================================================