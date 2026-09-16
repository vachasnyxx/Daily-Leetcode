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