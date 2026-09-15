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
//Simple SImulation
//T.C : O(m*n)
//S.C : O(1) (I am not considering the result matrix we have to return as result)
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> matrix(m, vector<int>(n, -1));

        int id    = 0; //0, 1, 2, 3
        int top   = 0;
        int down  = m-1;
        int left  = 0;
        int right = n-1;

        while(top <= down && left <= right) {
            if(id == 0) { //left to right
                for(int i = left; head != NULL && i <= right; i++) {
                    matrix[top][i] = head->val;
                    head = head->next;
                }
                top++;
            }

            if(id == 1) { //top to down
                for(int i = top; head != NULL && i <= down; i++) {
                    matrix[i][right] = head->val;
                    head = head->next;
                }
                right--;
            }

            if(id == 2) { //right to left
                for(int i = right; head != NULL && i >= left; i--) {
                    matrix[down][i] = head->val;
                    head = head->next;
                }
                down--;
            }

            if(id == 3) { //down to top
                for(int i = down; head != NULL && i >= top; i--) {
                    matrix[i][left] = head->val;
                    head = head->next;
                }
                left++;
            }

            id = (id+1)%4; //0, 1, 2, 3
        }

        return matrix;
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
// Simple Simulation
// T.C : O(m*n)
// S.C : O(1) (not counting the result matrix we have to return)
// class Solution {
// public:
//     vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {

//         // ============================================================
//         // 🧠 INTUITION & PATTERN: BOUNDARY SHRINKING SIMULATION
//         //         (Spiral Traversal + Linked List Consumption)
//         // ============================================================
//         // The core IDEA is:
//         //   "Imagine peeling an onion layer by layer in a spiral.
//         //    You walk RIGHT across the top, DOWN the right side,
//         //    LEFT across the bottom, and UP the left side. After
//         //    each side, you SHRINK the boundary inward. Meanwhile,
//         //    you're reading values from a linked list one by one
//         //    and placing them into the matrix cells you visit."
//         //
//         //   The linked list acts as a "stream" of values. You pour
//         //   this stream into the matrix following the spiral path.
//         //   If the stream runs out before the matrix is full, the
//         //   remaining cells stay as -1 (the default fill value).
//         //
//         // 🆚 HOW IS THIS DIFFERENT FROM PREVIOUS PROBLEMS?
//         //   ALL previous problems (LC 19, 2095, 160, 141, 142, 83, 61)
//         //   were PURE linked list problems — pointers chasing pointers.
//         //
//         //   LC 2326 is a HYBRID: Linked List + 2D Matrix Traversal.
//         //   → The linked list is just a DATA SOURCE (like a queue).
//         //   → The real challenge is the SPIRAL MATRIX traversal pattern.
//         //   → The linked list part is trivial: just `head->val` and
//         //     `head = head->next` at each cell.
//         //
//         // 🆚 HOW IS THIS DIFFERENT FROM CLASSIC SPIRAL MATRIX (LC 54)?
//         //   LC 54:  READ from a filled matrix in spiral order → return array.
//         //   LC 2326: WRITE into an empty matrix in spiral order FROM a list.
//         //   → LC 54: matrix is the INPUT, array is the OUTPUT.
//         //   → LC 2326: linked list is the INPUT, matrix is the OUTPUT.
//         //   → LC 2326 has an extra twist: the list might be SHORTER than
//         //     m×n, so you need `head != NULL` checks everywhere.
//         // ============================================================

//         // 🔹 STEP 1: Initialize the result matrix with -1
//         //
//         // ⚠️ ATOMIC DETAIL #1 — Why fill with -1?
//         //    The problem says: "If the linked list has fewer than m×n
//         //    nodes, fill the remaining cells with -1."
//         //    By initializing the ENTIRE matrix with -1 upfront, we
//         //    don't need to handle leftover cells separately. If the
//         //    list runs out mid-spiral, we just stop writing, and the
//         //    unwritten cells are ALREADY -1. Elegant! ✅
//         //
//         //    Example: m=3, n=3, list = [1,2,3,4] (only 4 nodes, need 9)
//         //      After filling:  1  2  3
//         //                      4 -1 -1
//         //                     -1 -1 -1
//         //      The -1s were never overwritten — they stayed from init.
//         vector<vector<int>> matrix(m, vector<int>(n, -1));

//         // 🔹 STEP 2: Set up the spiral traversal state
//         //
//         // ⚠️ ATOMIC DETAIL #2 — The `id` variable (direction indicator)
//         //    id = 0 → Move LEFT to RIGHT  (→ across the top row)
//         //    id = 1 → Move TOP to BOTTOM  (↓ down the right column)
//         //    id = 2 → Move RIGHT to LEFT  (← across the bottom row)
//         //    id = 3 → Move BOTTOM to TOP  (↑ up the left column)
//         //    After each direction, id cycles: 0→1→2→3→0→1→...
//         //    Using `(id+1) % 4` achieves this cycling automatically.
//         //
//         // ⚠️ ATOMIC DETAIL #3 — The four BOUNDARIES
//         //    These define the "active rectangle" we're currently spiraling.
//         //    After completing each side, we SHRINK the corresponding boundary:
//         //    → After going RIGHT across the top: top++ (top row is done)
//         //    → After going DOWN the right side: right-- (right col is done)
//         //    → After going LEFT across the bottom: down-- (bottom row is done)
//         //    → After going UP the left side: left++ (left col is done)
//         //
//         //    Visual (3×4 matrix, initial boundaries):
//         //         left        right
//         //          ↓           ↓
//         //    top → [ 0,  1,  2,  3 ]
//         //          [ 4,  5,  6,  7 ]
//         //    down →[ 8,  9, 10, 11 ]
//         //
//         //    After id=0 (top row done): top becomes 1
//         //    After id=1 (right col done): right becomes 2
//         //    After id=2 (bottom row done): down becomes 1
//         //    After id=3 (left col done): left becomes 1
//         //    Now the active rectangle is just [5, 6] — one row!
//         int id    = 0;      // 🧭 Direction: 0=Right, 1=Down, 2=Left, 3=Up
//         int top   = 0;      // ⬆️ Top boundary (shrinks downward)
//         int down  = m - 1;  // ⬇️ Bottom boundary (shrinks upward)
//         int left  = 0;      // ⬅️ Left boundary (shrinks rightward)
//         int right = n - 1;  // ➡️ Right boundary (shrinks leftward)

//         // 🔹 STEP 3: Main spiral loop
//         //
//         // ⚠️ ATOMIC DETAIL #4 — The outer while condition
//         //    `top <= down && left <= right`
//         //    → This ensures the active rectangle is still VALID.
//         //    → If top > down: all rows have been covered.
//         //    → If left > right: all columns have been covered.
//         //    → Either condition means the spiral is complete.
//         //
//         //    Why `<=` and not `<`?
//         //    → When top == down, there's exactly ONE row left to fill.
//         //    → When left == right, there's exactly ONE column left.
//         //    → Both are valid! We need `<=` to process these last strips.
//         //    → If we used `<`, we'd miss the final row/column.
//         //
//         //    ⚠️ ATOMIC DETAIL #5 — Why is the `head != NULL` check
//         //       NOT in the outer while condition?
//         //       Because the spiral should continue its PATH even if the
//         //       list runs out. The matrix cells need to stay -1 for
//         //       unfilled positions. If we stopped the outer loop when
//         //       head == NULL, the boundaries wouldn't shrink properly,
//         //       and we might get stuck in an infinite loop or miss
//         //       the -1 fills. Instead, we check `head != NULL` INSIDE
//         //       each for-loop — we stop WRITING but keep SPIRALING.
//         //       (Though practically, once head is NULL, all subsequent
//         //       for-loops skip immediately, so the outer loop exits
//         //       quickly via the boundary conditions.)
//         while (top <= down && left <= right) {

//             // 🔹 DIRECTION 0: LEFT → RIGHT (top row)
//             //
//             // ⚠️ ATOMIC DETAIL #6 — The for-loop structure
//             //    `for(int i = left; head != NULL && i <= right; i++)`
//             //    → `i = left`: Start from the leftmost active column.
//             //    → `i <= right`: Go up to the rightmost active column.
//             //    → `head != NULL`: STOP if the linked list is exhausted.
//             //      This is the KEY difference from LC 54! In LC 54,
//             //      the matrix is fully populated, so you never run out
//             //      of data. Here, the list might end mid-row.
//             //
//             //    What happens when head becomes NULL mid-loop?
//             //    → The for-loop condition fails → loop exits early.
//             //    → Remaining cells in this row stay -1 (from init). ✅
//             //    → Subsequent directions also skip (head is still NULL).
//             //    → Eventually boundaries cross → outer loop exits.
//             //
//             //    Visual (3×3, list=[1,2,3,4,5,6,7,8,9]):
//             //      id=0: Fill top row L→R
//             //        matrix[0][0]=1, matrix[0][1]=2, matrix[0][2]=3
//             //        1  2  3
//             //       -1 -1 -1
//             //       -1 -1 -1
//             //      Then top++ → top=1
//             if (id == 0) {
//                 for (int i = left; head != NULL && i <= right; i++) {
//                     matrix[top][i] = head->val;  // ✏️ Write list value into cell
//                     head = head->next;            // ⏭️ Consume one list node
//                 }
//                 top++;  // ⬆️ Shrink: top row is done, move boundary down
//             }

//             // 🔹 DIRECTION 1: TOP → BOTTOM (right column)
//             //
//             // ⚠️ ATOMIC DETAIL #7 — Why start from `top` (not 0)?
//             //    Because `top` was already incremented after Direction 0.
//             //    The top-right corner cell was ALREADY filled in Direction 0.
//             //    If we started from row 0, we'd OVERWRITE it!
//             //    Starting from the updated `top` avoids double-filling.
//             //
//             //    Visual (continuing from above):
//             //      id=1: Fill right col T→B (from row top=1 to down=2)
//             //        matrix[1][2]=4, matrix[2][2]=5  (wait, let me recount)
//             //        Actually: matrix[1][2]=6, matrix[2][2]=7
//             //        1  2  3
//             //       -1 -1  6
//             //       -1 -1  7
//             //      Then right-- → right=1
//             if (id == 1) {
//                 for (int i = top; head != NULL && i <= down; i++) {
//                     matrix[i][right] = head->val;  // ✏️ Write into right column
//                     head = head->next;              // ⏭️ Consume one list node
//                 }
//                 right--;  // ➡️ Shrink: right column is done, move boundary left
//             }

//             // 🔹 DIRECTION 2: RIGHT → LEFT (bottom row)
//             //
//             // ⚠️ ATOMIC DETAIL #8 — Why `i >= left` (not `i >= 0`)?
//             //    Because `left` might have been incremented in a previous
//             //    spiral layer. We only fill within the ACTIVE rectangle.
//             //    Also, `i--` (decrement) because we're going RIGHT to LEFT.
//             //
//             //    Visual (continuing):
//             //      id=2: Fill bottom row R→L (from col right=1 to left=0)
//             //        matrix[2][1]=8, matrix[2][0]=9
//             //        1  2  3
//             //       -1 -1  6
//             //        9  8  7
//             //      Then down-- → down=1
//             if (id == 2) {
//                 for (int i = right; head != NULL && i >= left; i--) {
//                     matrix[down][i] = head->val;  // ✏️ Write into bottom row
//                     head = head->next;             // ⏭️ Consume one list node
//                 }
//                 down--;  // ⬇️ Shrink: bottom row is done, move boundary up
//             }

//             // 🔹 DIRECTION 3: BOTTOM → TOP (left column)
//             //
//             // ⚠️ ATOMIC DETAIL #9 — Why `i >= top` (not `i >= 0`)?
//             //    Same reason: `top` has been incremented. The top-left
//             //    corner was already filled in Direction 0 of this layer.
//             //    We start from `down` (already decremented) and go UP
//             //    to `top`. `i--` because we're going BOTTOM to TOP.
//             //
//             //    Visual (continuing, next layer):
//             //      Boundaries now: top=1, down=1, left=0, right=1
//             //      id=3: Fill left col B→T (from row down=1 to top=1)
//             //        matrix[1][0]=... (if list had more values)
//             //      Then left++ → left=1
//             //      Now top=1, down=1, left=1, right=1 → one cell left!
//             if (id == 3) {
//                 for (int i = down; head != NULL && i >= top; i--) {
//                     matrix[i][left] = head->val;  // ✏️ Write into left column
//                     head = head->next;             // ⏭️ Consume one list node
//                 }
//                 left++;  // ⬅️ Shrink: left column is done, move boundary right
//             }

//             // 🔹 STEP 4: Cycle the direction
//             //
//             // ⚠️ ATOMIC DETAIL #10 — The modulo trick `(id+1) % 4`
//             //    This cycles id through 0 → 1 → 2 → 3 → 0 → 1 → ...
//             //    → 0+1=1, 1%4=1 ✅
//             //    → 1+1=2, 2%4=2 ✅
//             //    → 2+1=3, 3%4=3 ✅
//             //    → 3+1=4, 4%4=0 ✅ (wraps back to 0!)
//             //    This is cleaner than `if(id==3) id=0; else id++;`
//             //    and scales if you ever need more directions (e.g., % 6).
//             //
//             // ⚠️ ATOMIC DETAIL #11 — Why is this OUTSIDE the if blocks
//             //    but INSIDE the while loop?
//             //    → It must execute after EVERY direction, regardless of
//             //      which direction just ran. Placing it outside the ifs
//             //      ensures it runs exactly once per while-loop iteration.
//             //    → If it were inside each if, you'd need to duplicate it
//             //      four times (DRY principle violation).
//             //    → If it were outside the while, it would never execute.
//             id = (id + 1) % 4;  // 🧭 Rotate direction: R→D→L→U→R→...
//         }

//         // 🔹 STEP 5: Return the filled matrix
//         //
//         // ⚠️ ATOMIC DETAIL #12 — What if the list was empty (head == NULL)?
//         //    → The for-loops never execute (head != NULL fails immediately).
//         //    → Boundaries never shrink.
//         //    → Outer while eventually exits (after 4 iterations, boundaries
//         //      cross because the for-loops do nothing but id still cycles).
//         //    → Actually wait — if head is NULL from the start, the for-loops
//         //      skip, boundaries DON'T shrink, and the while loop runs forever!
//         //    → BUT: the problem guarantees head has at least 1 node when
//         //      m,n >= 1. And if m=0 or n=0, the while condition fails
//         //      immediately. So this edge case doesn't arise in practice.
//         //    → If you wanted to be extra safe, add `if(!head) return matrix;`
//         //      at the top. But LeetCode's constraints make it unnecessary.
//         return matrix;  // 🎯 Return the spiral-filled matrix
//     }
// };

// // ================================================================
// // 📝 DETAILED SUMMARY FOR REVISION
// // ================================================================
// //
// // 🎯 PROBLEM:
// //    Given dimensions m×n and a linked list head, generate an m×n
// //    matrix filled with the linked list values in SPIRAL order
// //    (clockwise from top-left). Fill remaining cells with -1 if
// //    the list has fewer than m×n nodes.
// //
// // 🧩 PATTERN USED: Boundary Shrinking Simulation (Spiral Traversal)
// //    This is a MATRIX traversal pattern, not a linked list pattern.
// //    The linked list is just a data source — the real logic is the spiral.
// //
// // 🏠 REAL-LIFE ANALOGY:
// //    Imagine you're a painter 🎨 standing at the top-left corner of
// //    a rectangular wall. You have a bucket of paint colors (the linked
// //    list) that you apply one by one.
// //
// //    You paint the top edge left-to-right, then the right edge
// //    top-to-bottom, then the bottom edge right-to-left, then the
// //    left edge bottom-to-top. After each edge, you step inward
// //    (shrink the boundary) and repeat on the smaller rectangle.
// //
// //    If you run out of paint (list ends) before the wall is fully
// //    covered, the unpainted spots stay as bare wall (-1).
// //
// //    The spiral looks like this on a 4×5 wall:
// //      →  →  →  →  →
// //                     ↓
// //      ↑  →  →  →  ↓
// //      ↑           ↓
// //      ↑  ←  ←  ←  ↓
// //      ↑
// //      ←  ←  ←  ←  ←
// //
// // 📌 STEP-BY-STEP RECIPE:
// //    1. Create m×n matrix filled with -1.
// //    2. Set boundaries: top=0, down=m-1, left=0, right=n-1, id=0.
// //    3. While top <= down AND left <= right:
// //       a. id=0: Fill top row L→R, then top++.
// //       b. id=1: Fill right col T→B, then right--.
// //       c. id=2: Fill bottom row R→L, then down--.
// //       d. id=3: Fill left col B→T, then left++.
// //       e. id = (id+1) % 4.
// //       (Each for-loop also checks head != NULL.)
// //    4. Return matrix.
// //
// // ⚠️ ATOMIC DETAILS CHECKLIST (things that break your code if missed):
// //    ☐ Initialize matrix with -1 — handles "list shorter than m×n" for free.
// //    ☐ `head != NULL` check INSIDE each for-loop, not just the outer while.
// //      → List can end mid-row/mid-column. Without this → NULL dereference.
// //    ☐ Boundary updates AFTER each direction (top++, right--, down--, left++).
// //      → Forgetting any one causes overwriting or infinite loops.
// //    ☐ Outer condition: `top <= down && left <= right` (use `<=`, not `<`).
// //      → `==` means one row/column left — still valid!
// //    ☐ Direction cycling: `(id+1) % 4` — clean and scalable.
// //    ☐ For Direction 2 and 3, loop goes BACKWARDS (`i--`, `i >= left/top`).
// //      → Easy to accidentally write `i++` and get wrong output.
// //    ☐ For Direction 1 and 3, the row index `i` varies (column is fixed).
// //      For Direction 0 and 2, the column index `i` varies (row is fixed).
// //      → Mixing these up gives transposed/wrong output.
// //    ☐ The linked list is consumed SEQUENTIALLY — one node per cell.
// //      → `head = head->next` in every for-loop body. Don't skip it!
// //
// // 🔗 COMPARISON WITH ALL PREVIOUS PROBLEMS:
// //    ┌──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐
// //    │    Aspect    │ LC 19        │ LC 2095      │ LC 160       │ LC 141/142   │ LC 83        │ LC 61        │
// //    │              │ (Nth End)    │ (Mid Delete) │ (Intersect)  │ (Cycle)      │ (Duplicates) │ (Rotate)     │
// //    ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
// //    │ Domain       │ Linked List  │ Linked List  │ Linked List  │ Linked List  │ Linked List  │ Linked List  │
// //    │ Technique    │ Fixed gap    │ 1:2 speed    │ Align length │ Floyd's      │ Keep+Scan    │ Measure+Cut  │
// //    │ Pointers     │ 2            │ 3            │ 2            │ 2            │ 2            │ 1+tail       │
// //    │ Data struct  │ List only    │ List only    │ 2 Lists      │ List only    │ Sorted List  │ List only    │
// //    │ Return       │ ListNode*    │ ListNode*    │ ListNode*    │ bool/Node*   │ ListNode*    │ ListNode*    │
// //    ├──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┤
// //    │    LC 2326 (THIS PROBLEM) — FUNDAMENTALLY DIFFERENT!                                                 │
// //    ├──────────────┬──────────────────────────────────────────────────────────────────────────────────────────┤
// //    │ Domain       │ HYBRID: Linked List + 2D Matrix                                                       │
// //    │ Technique    │ Boundary Shrinking Simulation (Spiral)                                                │
// //    │ Pointers     │ 1 (head) + 4 boundaries (top, down, left, right) + direction (id)                     │
// //    │ Data struct  │ List as DATA SOURCE, Matrix as OUTPUT                                                 │
// //    │ Return       │ vector<vector<int>> (2D matrix, not a ListNode!)                                      │
// //    │ Key trick    │ Spiral traversal + head!=NULL guard in each for-loop                                  │
// //    │ Edge case    │ List shorter than m×n → remaining cells stay -1                                       │
// //    └──────────────┴──────────────────────────────────────────────────────────────────────────────────────────┘
// //
// //    🔑 KEY OBSERVATION:
// //    This is the FIRST problem in our set that is NOT purely a linked
// //    list problem. The linked list is trivially consumed (just read
// //    head->val and advance). The REAL challenge is the spiral matrix
// //    traversal, which is a completely different pattern. In interviews,
// //    recognize this as a "matrix simulation" problem that happens to
// //    use a linked list as input.
// //
// // ⏱️ TIME COMPLEXITY: O(m × n)
// //    → We visit each cell of the m×n matrix at most once.
// //    → Each linked list node is consumed at most once.
// //    → Total work = number of cells = m × n.
// //    → Interview answer: "We fill each cell exactly once, so O(m×n)."
// //
// // 💾 SPACE COMPLEXITY: O(1) auxiliary (not counting the output matrix)
// //    → Only a few integer variables (id, top, down, left, right, i).
// //    → No extra data structures beyond the required output matrix.
// //    → Interview answer: "O(1) extra space. The output matrix is
// //      required by the problem, so we don't count it."
// //    → If the interviewer asks about total space including output:
// //      "O(m×n) for the result matrix, which is unavoidable."
// //
// // 🎤 INTERVIEW FOLLOW-UP QUESTIONS TO PREPARE FOR:
// //
// //    Q1: "How would you solve LC 54 (Spiral Matrix) — reading from matrix?"
// //    → Same boundary shrinking logic, but instead of writing head->val,
// //      you READ matrix[row][col] and push to a result array.
// //    → No `head != NULL` check needed (matrix is fully populated).
// //    → The four for-loops and boundary updates are IDENTICAL.
// //
// //    Q2: "What if the spiral should go counter-clockwise?"
// //    → Change the direction order: 0=Down, 1=Right, 2=Up, 3=Left.
// //    → The boundary shrinking logic stays the same, just reordered.
// //
// //    Q3: "What if the matrix is 1×n or m×1 (single row/column)?"
// //    → The algorithm handles it naturally!
// //    → 1×n: top=0, down=0. Direction 0 fills the row. top becomes 1.
// //      Now top > down → outer loop exits. Done! ✅
// //    → m×1: left=0, right=0. Direction 0 fills the single cell.
// //      Direction 1 fills the column. left becomes 1 > right → exit. ✅
// //
// //    Q4: "Can you do this without the `id` variable?"
// //    → Yes! Use four separate while-loops inside the outer while:
// //      while(top<=down && left<=right) {
// //        // L→R, then T→B, then R→L, then B→T
// //      }
// //    → This avoids the `id` variable but requires checking the outer
// //      condition before EACH inner loop (to handle non-square matrices).
// //    → The `id` approach is cleaner for this problem because the
// //      `head != NULL` check makes early exits possible mid-direction.
// //
// //    Q5: "How would you handle a doubly linked list or an array input?"
// //    → The spiral logic is IDENTICAL. Only the data source changes:
// //      → Array: use an index `idx++` instead of `head = head->next`.
// //      → Doubly linked list: same as singly, just use `head->next`.
// //    → The matrix traversal pattern is independent of the data source.
// // ================================================================