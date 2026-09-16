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
    ListNode* partition(ListNode* head, int x) {
        ListNode* lo = new ListNode(100);
        ListNode* hi = new ListNode(100);
        ListNode* tempLo = lo;
        ListNode* tempHi = hi;
        ListNode* temp = head;
        while (temp != NULL) {
            if (temp->val < x) {
                tempLo->next = temp;
                temp = temp->next;
                tempLo = tempLo->next;
            } else { // temp->val >= x
                tempHi->next = temp;
                temp = temp->next;
                tempHi = tempHi->next;
            }
        }
        tempLo->next = hi->next;
        tempHi->next = NULL;
        return lo->next;
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
//     ListNode* partition(ListNode* head, int x) {
        
//         // ============================================
//         // PATTERN: Two-Pointer Partition (Segregation Pattern)
//         // ============================================
//         // INTUITION: Similar to quicksort partitioning but for linked lists
//         // We create TWO separate lists:
//         //   1. "lo" list - stores all nodes with values < x
//         //   2. "hi" list - stores all nodes with values >= x
//         // Then connect lo's tail to hi's head
//         // Think of it like sorting laundry: small items in one basket, large in another
        
//         // ============================================
//         // STEP 1: Create Dummy Heads for Both Lists
//         // ============================================
//         // Why dummy nodes? They prevent null pointer edge cases when lists are empty
//         // The value 100 doesn't matter - these are just placeholders
//         ListNode* lo = new ListNode(100);  // Dummy head for "less than x" list
//         ListNode* hi = new ListNode(100);  // Dummy head for "greater/equal to x" list
        
//         // ============================================
//         // STEP 2: Create Tail Pointers for Building Lists
//         // ============================================
//         // tempLo and tempHi will move forward as we append nodes
//         // Think of them as "construction workers" building the lists
//         ListNode* tempLo = lo;  // Points to the last node in lo list
//         ListNode* tempHi = hi;  // Points to the last node in hi list
        
//         // ============================================
//         // STEP 3: Traverse Original List
//         // ============================================
//         ListNode* temp = head;  // Iterator for the original list
        
//         while (temp != NULL) {
            
//             // CRITICAL DECISION: Which list does this node belong to?
//             if (temp->val < x) {
//                 // ============================================
//                 // Route 1: Value is LESS than x
//                 // ============================================
//                 tempLo->next = temp;        // Append current node to lo list
//                 temp = temp->next;          // Move to next node in original list
//                 tempLo = tempLo->next;      // Move lo's tail pointer forward
                
//                 // KEY OBSERVATION: We're reusing existing nodes, not creating new ones
//                 // This preserves relative order automatically!
                
//             } else { // temp->val >= x
//                 // ============================================
//                 // Route 2: Value is GREATER THAN or EQUAL to x
//                 // ============================================
//                 tempHi->next = temp;        // Append current node to hi list
//                 temp = temp->next;          // Move to next node in original list
//                 tempHi = tempHi->next;      // Move hi's tail pointer forward
//             }
//         }
        
//         // ============================================
//         // STEP 4: Connect the Two Lists
//         // ============================================
//         // Now we have: lo -> [nodes < x] and hi -> [nodes >= x]
//         // We need: lo -> [nodes < x] -> [nodes >= x]
        
//         tempLo->next = hi->next;  
//         // Connect lo's tail to hi's FIRST REAL NODE (skip dummy)
//         // hi->next gives us the first actual node in hi list
        
//         // ============================================
//         // CRITICAL STEP: Break the Cycle!
//         // ============================================
//         tempHi->next = NULL;
//         // MUST set hi's tail to NULL to prevent circular references
//         // Without this, the last node in hi might still point to something
//         // from the original list, creating a cycle or wrong connections
        
//         // EXAMPLE of why this matters:
//         // Original: 1->4->3->2->5, x=3
//         // After partition: lo: 1->2, hi: 4->3->5
//         // If we don't set tempHi->next = NULL, node 5 might still point
//         // to its original next, creating issues
        
//         // ============================================
//         // STEP 5: Return Result
//         // ============================================
//         return lo->next;  
//         // Return lo->next (not lo itself) to skip the dummy node
//         // This is the start of our partitioned list
//     }
// };

// /*
// ╔══════════════════════════════════════════════════════════════════════════════╗
// ║                          COMPREHENSIVE SUMMARY                                ║
// ╚══════════════════════════════════════════════════════════════════════════════╝

// 📚 ANALOGY - The Two-Basket Sorting Method:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Imagine you're sorting apples on a conveyor belt:
// - Small apples (< x) go into the LEFT basket
// - Large apples (>= x) go into the RIGHT basket
// - You go through each apple ONCE, putting it in the correct basket
// - At the end, you connect the baskets: LEFT → RIGHT
// - The order within each basket matches the order they arrived

// 🎯 KEY LOGIC:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// 1. Create two separate lists (using dummy heads to avoid edge cases)
// 2. Iterate through original list ONCE
// 3. Redirect each node to appropriate list based on value vs x
// 4. Connect tail of "lo" list to head of "hi" list
// 5. CRUCIAL: Set hi's tail to NULL (prevent cycles)
// 6. Return lo->next (skip dummy)

// ⚠️ CRITICAL DETAILS TO REMEMBER:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// 1. ✓ Use dummy nodes to avoid null checks for empty lists
// 2. ✓ We REUSE original nodes (don't create new ones) - preserves order
// 3. ✓ Must set tempHi->next = NULL to break any old connections
// 4. ✓ Return lo->next (not lo) to skip dummy
// 5. ✓ Connect to hi->next (not hi) to skip hi's dummy
// 6. ✓ Use >= for the else condition (not just >)

// 🔄 PATTERN RECOGNITION:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// This is a SEGREGATION pattern - useful for:
// - Partitioning linked lists
// - Separating even/odd positioned nodes
// - Grouping nodes by any criteria
// Template: Create 2+ lists → Distribute nodes → Reconnect

// ⏱️ TIME COMPLEXITY: O(n)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// - We traverse the list exactly ONCE
// - n = number of nodes in the list
// - Each node is visited once and redirected (constant time operation)
// - No nested loops, no backtracking
// - In interview, say: "Linear time because we touch each node once"

// 💾 SPACE COMPLEXITY: O(1)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// - We only create 2 dummy nodes (constant space)
// - We don't create new nodes for data; we REUSE existing nodes
// - Just reassigning pointers, not duplicating the list
// - In interview, say: "Constant space because we only use a few pointers
//   and rearrange existing nodes without creating new data structures"

// 🐛 COMMON MISTAKES TO AVOID:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// 1. ✗ Forgetting tempHi->next = NULL → creates cycles!
// 2. ✗ Returning lo instead of lo->next → includes dummy node
// 3. ✗ Connecting to hi instead of hi->next → includes hi's dummy
// 4. ✗ Creating new nodes instead of reusing → breaks relative order
// 5. ✗ Not handling empty list case → dummy nodes handle this automatically!

// 📝 INTERVIEW TALKING POINTS:
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// "I use a two-list approach similar to quicksort partitioning. By maintaining
// dummy heads, I avoid edge cases. The key insight is REUSING nodes rather than
// copying them, which preserves relative order and keeps space constant. The
// critical step is breaking the old connections by setting the hi list's tail
// to NULL, preventing cycles in the final list."

// */















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
//     ListNode* partition(ListNode* head, int x) {
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 🎯 PROBLEM UNDERSTANDING - LEETCODE 86: PARTITION LIST
//         // ═══════════════════════════════════════════════════════════════════════════
//         // Given: A linked list and a value x
//         // Task: Rearrange so that all nodes < x come BEFORE all nodes >= x
//         // IMPORTANT: Preserve the RELATIVE ORDER within each partition
//         // 
//         // Example: head = [1,4,3,2,5,2], x = 3
//         // Output: [1,2,2,4,3,5]
//         // Notice: 1,2,2 (all < 3) come first, maintaining their order
//         //         4,3,5 (all >= 3) come after, maintaining their order
//         //
//         // ═══════════════════════════════════════════════════════════════════════════
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 🧠 CORE INTUITION & PATTERN IDENTIFICATION
//         // ═══════════════════════════════════════════════════════════════════════════
//         // PATTERN NAME: "Two-Pointer Segregation Pattern" / "Dual List Building"
//         // 
//         // REAL-WORLD ANALOGY:
//         // ─────────────────
//         // Imagine you're a postal worker sorting letters on a conveyor belt:
//         // - You have TWO mail bags (lo and hi lists)
//         // - Bag 1 (lo): For local mail (values < x)
//         // - Bag 2 (hi): For outstation mail (values >= x)
//         // - As each letter comes, you look at it ONCE and put it in the right bag
//         // - Letters in each bag stay in the order they arrived (relative order preserved)
//         // - Finally, you connect Bag 1 → Bag 2 to get the sorted mail
//         //
//         // WHY THIS APPROACH?
//         // ─────────────────
//         // 1. Single pass through list → O(n) time
//         // 2. Reusing existing nodes → O(1) space
//         // 3. Naturally preserves relative order (we don't swap, just redirect)
//         // 4. Dummy nodes eliminate edge cases (empty lists, single element, etc.)
//         //
//         // ALTERNATIVE APPROACHES (and why we don't use them):
//         // ──────────────────────────────────────────────────
//         // ❌ Bubble sort style swapping: O(n²) time, complex pointer manipulation
//         // ❌ Converting to array, partitioning, rebuilding: O(n) space
//         // ❌ Recursion: O(n) stack space, harder to understand
//         // ✅ Our approach: O(n) time, O(1) space, clean and intuitive
//         //
//         // ═══════════════════════════════════════════════════════════════════════════
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 STEP 1: CREATE DUMMY HEADS FOR BOTH PARTITIONS
//         // ═══════════════════════════════════════════════════════════════════════════
//         // WHY DUMMY NODES?
//         // ────────────────
//         // Dummy nodes are "placeholder" nodes that simplify linked list operations
//         // They prevent us from writing special case code for:
//         // - Empty lists
//         // - Inserting at the beginning
//         // - Handling the first node differently
//         //
//         // THINK OF IT LIKE:
//         // A dummy node is like a "starting marker" in a race - it's not a real
//         // participant, but it marks where the race begins. All real nodes come after it.
//         //
//         ListNode* lo = new ListNode(100);  
//         // "lo" list will store all nodes with val < x
//         // The value "100" is arbitrary - could be anything, we'll skip this dummy later
//         // This is the DUMMY HEAD (not part of final result)
        
//         ListNode* hi = new ListNode(100);  
//         // "hi" list will store all nodes with val >= x
//         // Again, "100" is just a placeholder value
//         // This is also a DUMMY HEAD (not part of final result)
        
//         // VISUAL REPRESENTATION AT THIS POINT:
//         // ────────────────────────────────────
//         // lo: [dummy:100] -> NULL
//         // hi: [dummy:100] -> NULL
//         // original list: 1 -> 4 -> 3 -> 2 -> 5 -> NULL  (example)
//         //
//         // ═══════════════════════════════════════════════════════════════════════════
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 STEP 2: CREATE TAIL POINTERS FOR BOTH LISTS
//         // ═══════════════════════════════════════════════════════════════════════════
//         // WHY TAIL POINTERS?
//         // ──────────────────
//         // To append nodes to a linked list efficiently, we need to know where the
//         // END of the list is. Without a tail pointer, we'd have to traverse the
//         // entire list every time we want to add a node → O(n) for each insertion!
//         //
//         // WITH tail pointers: O(1) insertion at the end
//         // WITHOUT tail pointers: O(n) to find end, then insert
//         //
//         // ANALOGY:
//         // ────────
//         // Think of tempLo and tempHi as "construction workers" standing at the end
//         // of each line. When a new person (node) arrives, the worker just points
//         // them to join at the end and then moves to stand behind the new person.
//         //
//         ListNode* tempLo = lo;  
//         // tempLo points to the LAST node in the lo list
//         // Initially points to the dummy (since that's the only node)
//         // As we add nodes, tempLo will move forward
        
//         ListNode* tempHi = hi;  
//         // tempHi points to the LAST node in the hi list
//         // Initially points to the dummy
//         // As we add nodes, tempHi will move forward
        
//         // IMPORTANT DISTINCTION:
//         // ───────────────────────
//         // lo/hi → Fixed references to DUMMY HEADS (never change, need for final result)
//         // tempLo/tempHi → Moving references to TAIL of lists (change as we build)
//         //
//         // VISUAL:
//         // ───────
//         // lo (fixed)
//         //  ↓
//         // [dummy] -> NULL
//         //  ↑
//         // tempLo (will move)
//         //
//         // ═══════════════════════════════════════════════════════════════════════════
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 STEP 3: CREATE ITERATOR FOR ORIGINAL LIST
//         // ═══════════════════════════════════════════════════════════════════════════
//         ListNode* temp = head;  
//         // temp is our "walker" that will traverse the original list
//         // We use a separate pointer so we don't lose the head reference
//         // (though we don't need head after this, it's good practice)
//         //
//         // WHY NOT USE head DIRECTLY?
//         // ──────────────────────────
//         // - More readable (temp clearly indicates it's temporary/moving)
//         // - If we needed head later, we'd still have it
//         // - Follows standard pattern for linked list traversal
//         //
//         // ═══════════════════════════════════════════════════════════════════════════
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 STEP 4: MAIN LOOP - PARTITION THE NODES
//         // ═══════════════════════════════════════════════════════════════════════════
//         // LOOP INVARIANT (what's true at the start of each iteration):
//         // ────────────────────────────────────────────────────────────────────────
//         // 1. All nodes before 'temp' have been processed and placed in lo or hi
//         // 2. tempLo points to the last node in the lo list
//         // 3. tempHi points to the last node in the hi list
//         // 4. temp points to the next unprocessed node (or NULL if done)
//         //
//         while (temp != NULL) {
//             // Loop continues as long as there are nodes to process
//             // NULL means we've reached the end of the original list
            
//             // ═══════════════════════════════════════════════════════════════════════
//             // 🔀 DECISION POINT: Which partition does this node belong to?
//             // ═══════════════════════════════════════════════════════════════════════
            
//             if (temp->val < x) {
//                 // ───────────────────────────────────────────────────────────────────
//                 // CASE 1: Current node's value is LESS THAN x
//                 // ───────────────────────────────────────────────────────────────────
//                 // This node belongs in the "lo" (lower values) partition
//                 // We need to:
//                 // 1. Append this node to the end of lo list
//                 // 2. Move our walker (temp) to the next node
//                 // 3. Update the tail pointer of lo list
//                 //
//                 // VISUAL EXAMPLE (x=3, current node is 2):
//                 // ─────────────────────────────────────────
//                 // BEFORE:
//                 // lo: [dummy] -> 1 -> NULL
//                 //                ↑
//                 //              tempLo
//                 // 
//                 // temp -> [2] -> 4 -> NULL
//                 //
//                 // AFTER:
//                 // lo: [dummy] -> 1 -> 2 -> NULL
//                 //                     ↑
//                 //                   tempLo
//                 //
//                 // temp -> [4] -> NULL
//                 //
                
//                 tempLo->next = temp;        
//                 // ──────────────────────────────────────────────────────────────
//                 // CRITICAL LINE 1: Append current node to lo list
//                 // ──────────────────────────────────────────────────────────────
//                 // We're making the current tail's next pointer point to temp
//                 // This effectively adds temp to the end of the lo list
//                 //
//                 // KEY INSIGHT: We're NOT creating a new node!
//                 // We're REUSING the existing node from the original list
//                 // This is why relative order is preserved - we're just
//                 // redirecting pointers, not rearranging values
//                 //
//                 // MEMORY PERSPECTIVE:
//                 // ───────────────────
//                 // We're not allocating new memory (except for dummies)
//                 // We're just changing what 'next' pointers point to
//                 // The nodes still exist at their original memory addresses
//                 //
                
//                 temp = temp->next;          
//                 // ──────────────────────────────────────────────────────────────
//                 // CRITICAL LINE 2: Move to next node in original list
//                 // ──────────────────────────────────────────────────────────────
//                 // IMPORTANT: We do this BEFORE updating tempLo!
//                 // Why? Because temp->next will change when we update tempLo->next
//                 // in the next iteration
//                 //
//                 // ORDER MATTERS:
//                 // ──────────────
//                 // ✓ Correct: tempLo->next = temp; temp = temp->next; tempLo = tempLo->next;
//                 // ✗ Wrong:   tempLo->next = temp; tempLo = tempLo->next; temp = temp->next;
//                 //            (After tempLo = tempLo->next, temp and tempLo point to same node,
//                 //             so temp->next might give us wrong next node)
//                 //
//                 // SAVE THE NEXT REFERENCE:
//                 // ────────────────────────
//                 // By doing temp = temp->next NOW, we're saving where to go next
//                 // before we modify any pointers in the next iteration
//                 //
                
//                 tempLo = tempLo->next;      
//                 // ──────────────────────────────────────────────────────────────
//                 // CRITICAL LINE 3: Move tail pointer of lo list forward
//                 // ──────────────────────────────────────────────────────────────
//                 // Now tempLo points to the node we just added
//                 // This prepares us for the next insertion
//                 //
//                 // WHY THIS WORKS:
//                 // ───────────────
//                 // We just set tempLo->next = temp
//                 // So tempLo->next is now the node we added
//                 // By doing tempLo = tempLo->next, we move tempLo to that new node
//                 //
//                 // MAINTAINING THE TAIL:
//                 // ─────────────────────
//                 // This ensures tempLo ALWAYS points to the last node in lo list
//                 // So the next time we add a node, it gets added at the correct end
//                 //
//                 // ──────────────────────────────────────────────────────────────
                
//             } else { 
//                 // ───────────────────────────────────────────────────────────────────
//                 // CASE 2: Current node's value is >= x
//                 // ───────────────────────────────────────────────────────────────────
//                 // This node belongs in the "hi" (higher/equal values) partition
//                 //
//                 // IMPORTANT NOTE ON CONDITION:
//                 // ────────────────────────────
//                 // We use >= (greater than or equal) not just >
//                 // The problem says: nodes < x come BEFORE nodes >= x
//                 // So x itself (if present) should go in the "hi" partition
//                 //
//                 // Example: x = 3, list has [3, 1, 2]
//                 // Result should be: [1, 2, 3] (3 goes with >= partition)
//                 //
//                 // The logic here is IDENTICAL to Case 1, just using hi instead of lo
//                 //
                
//                 tempHi->next = temp;        
//                 // Append current node to hi list
//                 // Same concept as tempLo->next = temp
//                 // We're building the hi list by redirecting pointers
                
//                 temp = temp->next;          
//                 // Move to next node in original list
//                 // Again, done BEFORE updating tempHi to preserve correct next reference
                
//                 tempHi = tempHi->next;      
//                 // Move tail pointer of hi list forward
//                 // Maintains tempHi as the last node in hi list
//                 //
//                 // ───────────────────────────────────────────────────────────────────
//             }
            
//             // ═══════════════════════════════════════════════════════════════════════
//             // END OF LOOP ITERATION
//             // ═══════════════════════════════════════════════════════════════════════
//             // At this point:
//             // - One more node has been processed
//             // - temp points to the next unprocessed node (or NULL)
//             // - Either tempLo or tempHi has moved forward by one node
//             // - The relative order within each partition is maintained
//             //
//             // EXAMPLE TRACE (x=3, list=[1,4,3,2,5]):
//             // ───────────────────────────────────────
//             // Initially:
//             //   lo: [dummy]->NULL,  hi: [dummy]->NULL,  temp: 1
//             //
//             // After processing 1 (< 3):
//             //   lo: [dummy]->1->NULL,  hi: [dummy]->NULL,  temp: 4
//             //
//             // After processing 4 (>= 3):
//             //   lo: [dummy]->1->NULL,  hi: [dummy]->4->NULL,  temp: 3
//             //
//             // After processing 3 (>= 3):
//             //   lo: [dummy]->1->NULL,  hi: [dummy]->4->3->NULL,  temp: 2
//             //
//             // After processing 2 (< 3):
//             //   lo: [dummy]->1->2->NULL,  hi: [dummy]->4->3->NULL,  temp: 5
//             //
//             // After processing 5 (>= 3):
//             //   lo: [dummy]->1->2->NULL,  hi: [dummy]->4->3->5->NULL,  temp: NULL
//             //
//             // Loop exits (temp == NULL)
//             // ═══════════════════════════════════════════════════════════════════════
//         }
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 STEP 5: CONNECT THE TWO PARTITIONS
//         // ═══════════════════════════════════════════════════════════════════════════
//         // At this point, we have two separate lists:
//         // lo: [dummy] -> [all nodes < x] -> NULL
//         // hi: [dummy] -> [all nodes >= x] -> NULL
//         //
//         // We need to create: [all nodes < x] -> [all nodes >= x] -> NULL
//         //
//         tempLo->next = hi->next;  
//         // ───────────────────────────────────────────────────────────────────────
//         // CONNECTING THE CHAINS
//         // ───────────────────────────────────────────────────────────────────────
//         // tempLo points to the LAST node in the lo list
//         // We make its next pointer point to the FIRST REAL node in hi list
//         //
//         // WHY hi->next and not hi?
//         // ────────────────────────
//         // hi is the DUMMY node (value 100)
//         // hi->next is the FIRST REAL node with actual data
//         // We want to skip the dummy and connect to real data
//         //
//         // VISUAL:
//         // ───────
//         // BEFORE:
//         // lo: [dummy] -> 1 -> 2 -> NULL
//         //                     ↑
//         //                   tempLo
//         //
//         // hi: [dummy] -> 4 -> 3 -> 5 -> NULL
//         //         ↑       ↑
//         //        hi    hi->next
//         //
//         // AFTER:
//         // lo: [dummy] -> 1 -> 2 ─┐
//         //                         │
//         //                         └──> 4 -> 3 -> 5 -> ???
//         //
//         // hi: [dummy] -> 4 -> 3 -> 5 -> ???
//         //
//         // EDGE CASE: What if hi list is empty (all nodes < x)?
//         // ─────────────────────────────────────────────────────
//         // If no nodes went to hi, then hi->next is NULL
//         // So tempLo->next = NULL, which correctly terminates the list!
//         //
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 STEP 6: TERMINATE THE FINAL LIST (CRUCIAL!)
//         // ═══════════════════════════════════════════════════════════════════════════
//         tempHi->next = NULL;
//         // ───────────────────────────────────────────────────────────────────────
//         // ⚠️ MOST CRITICAL LINE - PREVENTS CYCLES AND CORRUPTION
//         // ───────────────────────────────────────────────────────────────────────
//         //
//         // WHY IS THIS ABSOLUTELY NECESSARY?
//         // ──────────────────────────────────
//         // When we partitioned the list, we redirected 'next' pointers
//         // But the LAST node in hi list might still have its 'next' pointing
//         // to something from the ORIGINAL list structure!
//         //
//         // CONCRETE EXAMPLE OF THE PROBLEM:
//         // ─────────────────────────────────
//         // Original list: 1 -> 4 -> 3 -> 2 -> 5 -> NULL, x = 3
//         //
//         // During partitioning:
//         // - 1 goes to lo
//         // - 4 goes to hi
//         // - 3 goes to hi (4->next = 3)
//         // - 2 goes to lo
//         // - 5 goes to hi (3->next = 5)
//         //
//         // Now, node 5 was the last node in original list
//         // But in our partitioning, we did: tempHi->next = 5
//         // At this moment, 5->next still points to whatever it pointed to before!
//         //
//         // If the original list was: 1->4->3->2->5->NULL
//         // After: 5->next is NULL (OK)
//         //
//         // But if original list was: 1->4->3->2->5->6, x=3 (and 6<3)
//         // - 5 goes to hi
//         // - 6 goes to lo
//         // After partitioning, 5->next still points to 6!
//         //
//         // Our final list looks like:
//         // [dummy]lo -> 1 -> 2 -> 6 -> [dummy]hi -> 4 -> 3 -> 5 -> 6 -> ...
//         //                      ↑___________________________________|
//         //                                 CYCLE!
//         //
//         // By setting tempHi->next = NULL, we BREAK this old connection
//         // and ensure the list properly terminates
//         //
//         // ANOTHER WAY TO THINK ABOUT IT:
//         // ───────────────────────────────
//         // We're "cutting the rope" at the end of hi list
//         // Without this cut, the rope might still be attached to old structure
//         //
//         // WHY DON'T WE NEED tempLo->next = hi->next (we already did this)?
//         // ─────────────────────────────────────────────────────────────────
//         // We explicitly set tempLo->next = hi->next, so it points to what we want
//         // But we never explicitly set what tempHi->next should be - it retains
//         // its old value from the original list, which could be anything!
//         //
//         // EDGE CASE: What if hi list is empty?
//         // ─────────────────────────────────────
//         // If no nodes went to hi, tempHi still points to the dummy
//         // Setting dummy->next = NULL is harmless (it was already NULL or we make it NULL)
//         //
//         // WHAT HAPPENS IF WE FORGET THIS LINE?
//         // ─────────────────────────────────────
//         // ❌ Potential infinite loops when traversing
//         // ❌ Garbage values appearing in the list
//         // ❌ Segmentation faults
//         // ❌ Wrong answer in the output
//         //
//         // THIS IS A COMMON INTERVIEW MISTAKE - INTERVIEWERS LOOK FOR THIS!
//         // ───────────────────────────────────────────────────────────────────────
        
        
//         // ═══════════════════════════════════════════════════════════════════════════
//         // 📋 STEP 7: RETURN THE RESULT
//         // ═══════════════════════════════════════════════════════════════════════════
//         return lo->next;  
//         // ───────────────────────────────────────────────────────────────────────
//         // SKIPPING THE DUMMY NODE
//         // ───────────────────────────────────────────────────────────────────────
//         // lo points to the dummy node (value 100)
//         // lo->next points to the FIRST REAL node in our partitioned list
//         //
//         // WHY NOT RETURN lo?
//         // ──────────────────
//         // Because lo is a dummy node we created - it's not part of the actual data
//         // The problem expects us to return the first REAL node of the partitioned list
//         //
//         // FINAL STRUCTURE:
//         // ────────────────
//         // [dummy:100] -> 1 -> 2 -> 4 -> 3 -> 5 -> NULL
//         //  ↑             ↑
//         //  lo         lo->next (this is what we return)
//         //
//         // EDGE CASE: What if entire list was >= x (lo is empty)?
//         // ───────────────────────────────────────────────────────
//         // Then lo->next = hi->next (from step 5)
//         // If hi->next exists, we return the first node from hi partition
//         // If hi->next is also NULL (empty input list), we return NULL ✓
//         //
//         // EDGE CASE: What if entire list was < x (hi is empty)?
//         // ──────────────────────────────────────────────────────
//         // Then lo->next points to first node of lo list
//         // tempLo->next = hi->next = NULL (properly terminated)
//         // We return the lo partition ✓
//         //
//         // MEMORY LEAK CONSIDERATION:
//         // ──────────────────────────
//         // We allocated memory for lo and hi using 'new'
//         // Technically, we should delete them to avoid memory leaks
//         // In interview settings, this is often acceptable if time is short
//         // But if asked about cleanup:
//         //   ListNode* result = lo->next;
//         //   delete lo;
//         //   delete hi;
//         //   return result;
//         //
//         // ───────────────────────────────────────────────────────────────────────
//     }
// };


// /*
// ╔════════════════════════════════════════════════════════════════════════════════╗
// ║                                                                                ║
// ║                    🎓 COMPREHENSIVE REVISION SUMMARY                           ║
// ║                         FOR LEETCODE 86: PARTITION LIST                        ║
// ║                                                                                ║
// ╚════════════════════════════════════════════════════════════════════════════════╝

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 📚 THE BIG PICTURE - PROBLEM ESSENCE                                          ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// WHAT: Partition a linked list around a value x
// HOW:  All nodes < x come before all nodes >= x
// CONSTRAINT: Preserve relative order within each partition

// INPUT:  1 -> 4 -> 3 -> 2 -> 5 -> NULL, x = 3
// OUTPUT: 1 -> 2 -> 4 -> 3 -> 5 -> NULL
//         └─┬──┘  └────┬─────┘
//          < 3       >= 3
//          (order preserved: 1 before 2, 4 before 3 before 5)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎯 CORE ALGORITHM - THE "TWO BASKETS" APPROACH                                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╭─────────────────────────────────────────────────────────────╮
// │  🏗️ STEP-BY-STEP CONSTRUCTION PROCESS                      │
// ╰─────────────────────────────────────────────────────────────╯

// STEP 1: Create Two Empty Lists (with dummy heads)
// ├─ lo: Will hold nodes < x
// └─ hi: Will hold nodes >= x

// STEP 2: Set Up Tail Pointers
// ├─ tempLo: Points to end of lo list (starts at dummy)
// └─ tempHi: Points to end of hi list (starts at dummy)

// STEP 3: Traverse Original List
// ├─ For each node:
// │  ├─ If value < x  → append to lo list, move tempLo forward
// │  └─ If value >= x → append to hi list, move tempHi forward
// └─ Key: We REUSE existing nodes (don't create new ones)

// STEP 4: Connect the Two Lists
// ├─ Make lo's tail point to hi's first real node
// └─ tempLo->next = hi->next

// STEP 5: Terminate the Final List  ⚠️ CRITICAL
// ├─ Set tempHi->next = NULL
// └─ Prevents cycles from old connections

// STEP 6: Return Result
// └─ Return lo->next (skip dummy)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎨 VISUAL WALKTHROUGH - CONCRETE EXAMPLE                                      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// Input: 1 -> 4 -> 3 -> 2 -> 5 -> NULL, x = 3

// ┌─────────────────────────────────────────────────────────────┐
// │ INITIALIZATION                                              │
// └─────────────────────────────────────────────────────────────┘
// lo: [D] -> NULL          (D = dummy)
//     ↑
//   tempLo

// hi: [D] -> NULL
//     ↑
//   tempHi

// temp -> 1 -> 4 -> 3 -> 2 -> 5 -> NULL


// ┌─────────────────────────────────────────────────────────────┐
// │ ITERATION 1: Processing node 1 (1 < 3) → goes to lo        │
// └─────────────────────────────────────────────────────────────┘
// Actions:
//   tempLo->next = temp    → Attach 1 to lo
//   temp = temp->next      → Move to 4
//   tempLo = tempLo->next  → Move tempLo to 1

// Result:
// lo: [D] -> 1 -> NULL
//            ↑
//          tempLo

// hi: [D] -> NULL
//     ↑
//   tempHi

// temp -> 4 -> 3 -> 2 -> 5 -> NULL


// ┌─────────────────────────────────────────────────────────────┐
// │ ITERATION 2: Processing node 4 (4 >= 3) → goes to hi       │
// └─────────────────────────────────────────────────────────────┘
// Actions:
//   tempHi->next = temp    → Attach 4 to hi
//   temp = temp->next      → Move to 3
//   tempHi = tempHi->next  → Move tempHi to 4

// Result:
// lo: [D] -> 1 -> NULL
//            ↑
//          tempLo

// hi: [D] -> 4 -> NULL
//            ↑
//          tempHi

// temp -> 3 -> 2 -> 5 -> NULL


// ┌─────────────────────────────────────────────────────────────┐
// │ ITERATION 3: Processing node 3 (3 >= 3) → goes to hi       │
// └─────────────────────────────────────────────────────────────┘
// Result:
// lo: [D] -> 1 -> NULL
//            ↑
//          tempLo

// hi: [D] -> 4 -> 3 -> NULL
//                 ↑
//               tempHi

// temp -> 2 -> 5 -> NULL


// ┌─────────────────────────────────────────────────────────────┐
// │ ITERATION 4: Processing node 2 (2 < 3) → goes to lo        │
// └─────────────────────────────────────────────────────────────┘
// Result:
// lo: [D] -> 1 -> 2 -> NULL
//                 ↑
//               tempLo

// hi: [D] -> 4 -> 3 -> NULL
//                 ↑
//               tempHi

// temp -> 5 -> NULL


// ┌─────────────────────────────────────────────────────────────┐
// │ ITERATION 5: Processing node 5 (5 >= 3) → goes to hi       │
// └─────────────────────────────────────────────────────────────┘
// Result:
// lo: [D] -> 1 -> 2 -> NULL
//                 ↑
//               tempLo

// hi: [D] -> 4 -> 3 -> 5 -> NULL
//                      ↑
//                    tempHi

// temp -> NULL  (loop exits)


// ┌─────────────────────────────────────────────────────────────┐
// │ CONNECTING: tempLo->next = hi->next                        │
// └─────────────────────────────────────────────────────────────┘
// lo: [D] -> 1 -> 2 ──┐
//                     │
//                     └──> 4 -> 3 -> 5 -> NULL

// hi: [D] -> 4 -> 3 -> 5 -> NULL
//                      ↑
//                    tempHi


// ┌─────────────────────────────────────────────────────────────┐
// │ TERMINATING: tempHi->next = NULL  ⚠️ CRUCIAL STEP          │
// └─────────────────────────────────────────────────────────────┘
// Ensures: 5 -> NULL (no lingering connections)


// ┌─────────────────────────────────────────────────────────────┐
// │ FINAL RESULT: return lo->next                              │
// └─────────────────────────────────────────────────────────────┘
// [D] -> 1 -> 2 -> 4 -> 3 -> 5 -> NULL
//        ↑
//     lo->next (returned)

// OUTPUT: 1 -> 2 -> 4 -> 3 -> 5 -> NULL ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🔍 CRITICAL IMPLEMENTATION DETAILS - THE "GOTCHAS"                            ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ ⚠️ GOTCHA #1: Why Dummy Nodes?                               ║
// ╚═══════════════════════════════════════════════════════════════╝

// WITHOUT DUMMY:
// ───────────────
// if (loHead == NULL) {
//     loHead = temp;
//     loTail = temp;
// } else {
//     loTail->next = temp;
//     loTail = temp;
// }
// → Lots of special case handling!
// → Error-prone, especially for empty lists

// WITH DUMMY:
// ───────────
// tempLo->next = temp;
// tempLo = tempLo->next;
// → Works for ALL cases (even empty lists)
// → Clean, uniform code

// LESSON: Dummy nodes = fewer edge cases


// ╔═══════════════════════════════════════════════════════════════╗
// ║ ⚠️ GOTCHA #2: Why tempHi->next = NULL is MANDATORY           ║
// ╚═══════════════════════════════════════════════════════════════╝

// SCENARIO: Original list: 1->4->3->2->5->6, x=3
//           (6 < 3, so it goes to lo)

// After partitioning:
// lo: [D]->1->2->6->NULL
// hi: [D]->4->3->5->?????

// Here's the problem:
// When we did "tempHi->next = temp" for node 5,
// node 5's next pointer STILL points to 6 (from original list)!

// So after connecting:
// [D]->1->2->6->4->3->5->6->... CYCLE! 💥

// By setting tempHi->next = NULL:
// [D]->1->2->6->4->3->5->NULL ✓

// LESSON: Always terminate the last list to break old connections


// ╔═══════════════════════════════════════════════════════════════╗
// ║ ⚠️ GOTCHA #3: Order of Operations in Loop                    ║
// ╚═══════════════════════════════════════════════════════════════╝

// ✓ CORRECT:
//   tempLo->next = temp;
//   temp = temp->next;        ← Save next BEFORE moving tail
//   tempLo = tempLo->next;

// ✗ WRONG:
//   tempLo->next = temp;
//   tempLo = tempLo->next;    ← Now tempLo and temp point to same node
//   temp = temp->next;        ← This might give WRONG next node!

// WHY: After "tempLo = tempLo->next", tempLo points to the same
//      node as temp. If we later modify tempLo->next in another
//      iteration, temp->next will also change!

// LESSON: Save the "next" reference before modifying pointers


// ╔═══════════════════════════════════════════════════════════════╗
// ║ ⚠️ GOTCHA #4: Returning lo->next, not lo                     ║
// ╚═══════════════════════════════════════════════════════════════╝

// lo → [Dummy:100] -> 1 -> 2 -> ...
//      ↑              ↑
//    Don't want    We want this

// REASON: The dummy is not part of the actual data
//         It's just a construction aid

// LESSON: Always skip dummy nodes when returning


// ╔═══════════════════════════════════════════════════════════════╗
// ║ ⚠️ GOTCHA #5: Why >= and not just > in the else condition    ║
// ╚═══════════════════════════════════════════════════════════════╝

// PROBLEM STATEMENT:
// "nodes less than x come before nodes greater than or equal to x"

// So:
// - Nodes < x  → lo partition
// - Nodes >= x → hi partition  (includes x itself!)

// If we used > instead:
// - Where would nodes with value == x go?
// - They'd need a third partition!

// Example: x=3, list has [3, 1, 2]
// ✓ Correct: 1->2->3 (3 goes to >= partition)
// ✗ Wrong:   Undefined behavior if we only check <

// LESSON: Read problem statement carefully for >= vs >


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🧮 COMPLEXITY ANALYSIS - TIME & SPACE                                         ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╭────────────────────────────────────────────────────────────────╮
// │  ⏱️ TIME COMPLEXITY: O(n)                                      │
// ╰────────────────────────────────────────────────────────────────╯

// WHERE n = number of nodes in the linked list

// BREAKDOWN:
// ──────────
// 1. Initialization (creating dummies, pointers): O(1)
//    - Just creating 4 pointers: constant time

// 2. Main loop (partitioning):                    O(n)
//    - We visit each node EXACTLY ONCE
//    - For each node: 3 pointer assignments → O(1)
//    - Total: n nodes × O(1) = O(n)

// 3. Connecting lists:                            O(1)
//    - tempLo->next = hi->next → single assignment

// 4. Terminating:                                 O(1)
//    - tempHi->next = NULL → single assignment

// TOTAL: O(1) + O(n) + O(1) + O(1) = O(n)

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We traverse the list exactly once in a single pass. For each node,
// we do constant-time operations (pointer assignments). There are no
// nested loops or recursive calls. Therefore, the time complexity is
// linear, or O(n), where n is the number of nodes."

// WHY NOT O(n²)?
// ──────────────
// - We DON'T traverse the list multiple times
// - We DON'T search for positions (no indexOf-like operations)
// - We DON'T sort (sorting would be O(n log n) or O(n²))
// - We just REDISTRIBUTE nodes in one pass


// ╭────────────────────────────────────────────────────────────────╮
// │  💾 SPACE COMPLEXITY: O(1)                                     │
// ╰────────────────────────────────────────────────────────────────╯

// AUXILIARY SPACE (extra space used):
// ───────────────────────────────────

// WHAT WE CREATE:
// - lo: 1 dummy node
// - hi: 1 dummy node
// - tempLo: 1 pointer variable
// - tempHi: 1 pointer variable
// - temp: 1 pointer variable

// Total: 2 nodes + 3 pointers = CONSTANT space

// WHAT WE DON'T CREATE:
// - ✗ We DON'T create new nodes for the data
// - ✗ We DON'T create arrays or hash tables
// - ✗ We DON'T use recursion (no call stack)

// THE KEY INSIGHT:
// ────────────────
// We REUSE the existing nodes from the input list!
// We're just REWIRING the next pointers, not copying data.

// ANALOGY:
// ────────
// It's like rearranging train cars on a track.
// - We don't build new train cars (no new data nodes)
// - We just change which car connects to which (modify next pointers)
// - We use a couple of markers to keep track (dummy nodes, pointers)

// INTERVIEW EXPLANATION:
// ─────────────────────
// "We use constant extra space, O(1). Although we create two dummy
// nodes and a few pointer variables, this space doesn't grow with
// input size. We reuse the existing nodes from the input list by
// redirecting their next pointers, rather than creating new nodes.
// This is an in-place rearrangement of pointers."

// FOLLOW-UP QUESTION:
// ───────────────────
// Interviewer: "But aren't you creating two lists?"
// You: "Great question! I'm not creating new NODES - I'm creating
// two new LIST STRUCTURES by redirecting pointers. The actual node
// objects already exist in memory from the input list. I'm just
// changing their 'next' references to form two new chains, then
// merging them. It's like rearranging furniture in a room - the
// furniture already exists, I'm just changing its position."


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🎭 PATTERN RECOGNITION - WHEN TO USE THIS APPROACH                            ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🏷️ PATTERN NAME: "Two-List Segregation" / "Dual Partition"   ║
// ╚═══════════════════════════════════════════════════════════════╝

// SIGNATURE CHARACTERISTICS:
// ──────────────────────────
// ✓ Need to separate elements into 2+ groups
// ✓ Order within groups must be preserved
// ✓ Working with linked lists
// ✓ Can't use extra O(n) space for arrays

// SIMILAR PROBLEMS THIS PATTERN SOLVES:
// ──────────────────────────────────────
// 1. ✓ Partition List (this problem)
//    - Separate < x and >= x

// 2. ✓ Separate Even and Odd Nodes (LeetCode 328)
//    - All even-positioned nodes before odd-positioned

// 3. ✓ Split Linked List in Parts (LeetCode 725)
//    - Divide into k consecutive parts

// 4. ✓ Sort List with 0s, 1s, 2s
//    - Dutch National Flag for linked lists

// 5. ✓ Separate Positive and Negative Numbers
//    - Negatives before positives

// TEMPLATE FOR THIS PATTERN:
// ──────────────────────────
// 1. Create dummy heads for each partition
// 2. Create tail pointers for each partition
// 3. Traverse original list once
// 4. Route each node to appropriate partition
// 5. Connect partitions in desired order
// 6. Terminate the final partition (set last->next = NULL)
// 7. Return first_partition->next

// WHEN NOT TO USE:
// ────────────────
// ✗ If you need to sort (use merge sort for linked lists)
// ✗ If you need to remove duplicates (use hash set approach)
// ✗ If you need random access (convert to array first)


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 🐛 EDGE CASES & HOW THE ALGORITHM HANDLES THEM                                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 1: Empty List (head = NULL)                        │
// └───────────────────────────────────────────────────────────────┘

// Input: NULL, x = 3

// temp = NULL
// Loop doesn't execute (while condition fails immediately)
// tempLo->next = hi->next (dummy->next = dummy->next = NULL)
// tempHi->next = NULL (already NULL)
// Return: lo->next = NULL ✓

// RESULT: NULL (correct!)


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 2: Single Node (Less Than x)                       │
// └───────────────────────────────────────────────────────────────┘

// Input: 1 -> NULL, x = 3

// 1 < 3, goes to lo
// lo: [D] -> 1 -> NULL
// hi: [D] -> NULL

// tempLo->next = hi->next = NULL
// Return: lo->next = 1 ✓

// RESULT: 1 -> NULL


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 3: Single Node (Greater/Equal to x)                │
// └───────────────────────────────────────────────────────────────┘

// Input: 5 -> NULL, x = 3

// 5 >= 3, goes to hi
// lo: [D] -> NULL
// hi: [D] -> 5 -> NULL

// tempLo->next = hi->next = 5
// Return: lo->next = 5 ✓

// RESULT: 5 -> NULL


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 4: All Nodes Less Than x                           │
// └───────────────────────────────────────────────────────────────┘

// Input: 1 -> 2 -> 1 -> NULL, x = 5

// All nodes go to lo
// lo: [D] -> 1 -> 2 -> 1 -> NULL
// hi: [D] -> NULL

// tempLo->next = hi->next = NULL (properly terminated)
// Return: lo->next = 1 ✓

// RESULT: 1 -> 2 -> 1 -> NULL


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 5: All Nodes Greater/Equal to x                    │
// └───────────────────────────────────────────────────────────────┘

// Input: 5 -> 6 -> 7 -> NULL, x = 3

// All nodes go to hi
// lo: [D] -> NULL
// hi: [D] -> 5 -> 6 -> 7 -> NULL

// tempLo->next = hi->next = 5
// Return: lo->next = 5 ✓

// RESULT: 5 -> 6 -> 7 -> NULL


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 6: All Nodes Equal to x                            │
// └───────────────────────────────────────────────────────────────┘

// Input: 3 -> 3 -> 3 -> NULL, x = 3

// All nodes >= 3, so all go to hi
// lo: [D] -> NULL
// hi: [D] -> 3 -> 3 -> 3 -> NULL

// tempLo->next = hi->next = 3
// Return: lo->next = 3 ✓

// RESULT: 3 -> 3 -> 3 -> NULL


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 7: Already Partitioned                             │
// └───────────────────────────────────────────────────────────────┘

// Input: 1 -> 2 -> 4 -> 5 -> NULL, x = 3

// 1,2 go to lo; 4,5 go to hi
// Result: 1 -> 2 -> 4 -> 5 -> NULL ✓

// (Same as input, algorithm handles efficiently)


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 8: Reverse Partitioned                             │
// └───────────────────────────────────────────────────────────────┘

// Input: 5 -> 4 -> 2 -> 1 -> NULL, x = 3

// 5,4 go to hi; 2,1 go to lo
// Result: 2 -> 1 -> 5 -> 4 -> NULL ✓

// (Preserves relative order within each partition)


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 9: Alternating Values                              │
// └───────────────────────────────────────────────────────────────┘

// Input: 1 -> 5 -> 2 -> 4 -> NULL, x = 3

// 1 -> lo
// 5 -> hi
// 2 -> lo (after 1)
// 4 -> hi (after 5)

// Result: 1 -> 2 -> 5 -> 4 -> NULL ✓


// ┌───────────────────────────────────────────────────────────────┐
// │ EDGE CASE 10: Negative Numbers                               │
// └───────────────────────────────────────────────────────────────┘

// Input: -5 -> 3 -> -2 -> 4 -> NULL, x = 0

// -5,-2 go to lo (both < 0)
// 3,4 go to hi (both >= 0)

// Result: -5 -> -2 -> 3 -> 4 -> NULL ✓


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 💡 INTERVIEW TIPS & TALKING POINTS                                            ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🗣️ HOW TO EXPLAIN YOUR APPROACH                              ║
// ╚═══════════════════════════════════════════════════════════════╝

// OPENING (Problem Understanding):
// ────────────────────────────────
// "Let me make sure I understand the problem correctly. We need to
// rearrange the linked list so all nodes with values less than x
// come before nodes with values greater than or equal to x, while
// preserving the relative order within each group. Is that correct?"

// [Wait for confirmation]

// APPROACH EXPLANATION:
// ─────────────────────
// "I'll use a two-list approach, similar to the partition step in
// quicksort but adapted for linked lists. Here's my strategy:

// 1. Create two separate lists - one for values less than x (let's
//    call it 'lo'), and one for values greater than or equal to x
//    (let's call it 'hi').

// 2. Use dummy head nodes for both lists to simplify edge case
//    handling, especially for empty partitions.

// 3. Traverse the original list once, routing each node to the
//    appropriate list based on its value.

// 4. After processing all nodes, connect the tail of the 'lo' list
//    to the head of the 'hi' list.

// 5. Important: Set the last node's next pointer to null to prevent
//    cycles from old connections.

// 6. Return the head of the partitioned list, skipping the dummy node.

// This gives us O(n) time complexity with a single pass, and O(1)
// space complexity since we're reusing existing nodes."

// DURING CODING:
// ──────────────
// [As you write each section]
// "I'm creating dummy nodes here... this will help with empty lists"
// "Now the main loop... I'll route each node to the correct partition"
// "This step is crucial - terminating the list to prevent cycles"

// AFTER CODING:
// ─────────────
// "Let me trace through a quick example to verify..."
// [Pick a small example like 1->4->3->2, x=3]
// "And let me think about edge cases..."
// [Mention: empty list, single node, all in one partition]


// ╔═══════════════════════════════════════════════════════════════╗
// ║ ❓ EXPECTED FOLLOW-UP QUESTIONS & ANSWERS                     ║
// ╚═══════════════════════════════════════════════════════════════╝

// Q1: "Why did you use dummy nodes?"
// ───────────────────────────────────
// A: "Dummy nodes eliminate special case handling for empty lists
//    and simplify insertion at the beginning. Without them, I'd
//    need to check if each partition is empty before appending,
//    which adds complexity and potential for bugs."

// Q2: "Why is tempHi->next = NULL necessary?"
// ────────────────────────────────────────────
// A: "Great question! When we partition, we're redirecting next
//    pointers, but the last node in the 'hi' list might still
//    point to a node that went to the 'lo' list. Without setting
//    it to NULL, we could create a cycle or incorrect connections.
//    This step breaks any old references and properly terminates
//    the list."

// Q3: "Can you do this in-place?"
// ────────────────────────────────
// A: "Yes, this IS an in-place solution! We're not creating new
//    nodes for the data - we're reusing the existing nodes from
//    the input list and just rewiring their next pointers. The
//    only extra space we use is for two dummy nodes and a few
//    pointers, which is O(1)."

// Q4: "What if all elements are less than x?"
// ────────────────────────────────────────────
// A: "In that case, all nodes go into the 'lo' list, and 'hi'
//    remains empty (just the dummy). When we connect, tempLo->next
//    points to hi->next, which is NULL, properly terminating the
//    list. The algorithm handles this naturally without special
//    code."

// Q5: "How does this preserve relative order?"
// ─────────────────────────────────────────────
// A: "We traverse the original list from left to right and append
//    nodes to their respective partitions in the same order we
//    encounter them. Since we're using tail pointers, appending
//    happens at the end, maintaining the sequence. We never swap
//    or reorder within a partition."

// Q6: "Could you use an array instead?"
// ──────────────────────────────────────
// A: "We could convert to an array, partition it, then rebuild
//    the list, but that would require O(n) extra space for the
//    array. The current approach is more space-efficient at O(1).
//    However, if we needed random access for other operations,
//    the array approach might make sense."

// Q7: "What about stability?"
// ────────────────────────────
// A: "This algorithm is stable - nodes with equal values (in this
//    case, equal position relative to x) maintain their relative
//    order. We append in the order we encounter them, never
//    swapping equal elements."


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🎯 KEY POINTS TO EMPHASIZE IN INTERVIEW                       ║
// ╚═══════════════════════════════════════════════════════════════╝

// ✓ Single pass through the list (efficient)
// ✓ Constant extra space (space-optimal)
// ✓ Preserves relative order (stability)
// ✓ Handles all edge cases naturally (robustness)
// ✓ Clean, readable code (maintainability)


// ╔═══════════════════════════════════════════════════════════════╗
// ║ ⚠️ COMMON MISTAKES TO AVOID (Tell interviewer you're aware)  ║
// ╚═══════════════════════════════════════════════════════════════╝

// ❌ Forgetting to set tempHi->next = NULL → creates cycles
// ❌ Returning lo instead of lo->next → includes dummy in result
// ❌ Using > instead of >= → wrong partition boundary
// ❌ Saving temp->next after updating pointers → loses next reference
// ❌ Not handling empty list → but dummies handle this automatically!


// ╔═══════════════════════════════════════════════════════════════╗
// ║ 🚀 POSSIBLE OPTIMIZATIONS/VARIATIONS (If interviewer asks)   ║
// ╚═══════════════════════════════════════════════════════════════╝

// 1. Memory Cleanup:
//    ────────────────
//    "We could delete the dummy nodes before returning to prevent
//    memory leaks, though in many interview contexts this is okay
//    to skip if time is limited."

// 2. Three-way Partition:
//    ─────────────────────
//    "If needed, we could extend this to partition into three
//    groups (< x, == x, > x) using three lists instead of two."

// 3. Generalized Criteria:
//    ──────────────────────
//    "We could make this more flexible by passing a comparison
//    function instead of a value x, allowing arbitrary partition
//    criteria."


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ 📖 FINAL REVISION CHECKLIST                                                   ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// Before the interview, make sure you can:

// ☐ Explain the "two baskets" analogy clearly
// ☐ Draw the visual representation of the algorithm
// ☐ Explain why dummy nodes are beneficial
// ☐ Justify why tempHi->next = NULL is critical
// ☐ State time complexity as O(n) and why
// ☐ State space complexity as O(1) and why
// ☐ Handle questions about in-place modification
// ☐ Walk through at least one example step-by-step
// ☐ Identify 3+ edge cases and how they're handled
// ☐ Explain how relative order is preserved
// ☐ Code the solution without looking at reference
// ☐ Spot the difference between > and >= in partition logic

// ═══════════════════════════════════════════════════════════════════════════════

// 🎓 ULTIMATE MEMORY AID:

//    Two baskets, one conveyor belt
//    Small items left, big items right
//    Keep them in order as they come
//    Connect the baskets at the end
//    Cut the rope behind (tempHi->next = NULL!)
//    Return the start (skip the dummy)

// ═══════════════════════════════════════════════════════════════════════════════

// Good luck with your interview! 🚀

// */