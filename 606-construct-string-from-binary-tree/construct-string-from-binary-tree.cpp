// /**
//  * Definition for a binary tree node.
//  * struct TreeNode {
//  *     int val;
//  *     TreeNode *left;
//  *     TreeNode *right;
//  *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//  * };
//  */

// class Solution {
// public:
//     string tree2str(TreeNode* root) {
//         if(root == NULL){
//             return "";
//         }

//         string result = to_string(root->val); // root (L)(R)

//         string LEFT = tree2str(root->left);
//         string RIGHT = tree2str(root->right);

//         if(root->left == NULL && root->right == NULL){
//             return result;
//         }

//         if(root->left == NULL){
//             return result + "()" + "(" + RIGHT + ")"; 
//         } 

//         if(root -> right == NULL){
//             return result + "(" + LEFT + ")";
//         }

//         return result + "(" +  LEFT + ")" + "(" + RIGHT + ")";
//     }
// };






/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    string tree2str(TreeNode* root) {

        // BASE CASE: if the current node is NULL, it contributes NOTHING
        // to the string representation. An empty subtree has no characters
        // to add — the caller will decide whether to write "()" for it
        // based on the omission rules.
        if (root == NULL) {
            return "";
        }

        // Start with the current node's value as a string.
        // The final format for any non-empty node is:
        //   "value" + optional "(left-subtree)" + optional "(right-subtree)"
        string result = to_string(root->val);   // root (L)(R)

        // Recursively build the string representations of the left and right
        // subtrees. These calls return the INNER content of the parentheses
        // — the caller is responsible for wrapping them in "()" when needed.
        string LEFT = tree2str(root->left);
        string RIGHT = tree2str(root->right);

        // CASE 1: Leaf node (both children are NULL).
        // Per the problem's omission rules, a leaf's children are NEVER
        // represented — no empty parentheses for either side.
        // Example: node 3 with no children → just "3", not "3()()".
        if (root->left == NULL && root->right == NULL) {
            return result;
        }

        // CASE 2: Left child is NULL but right child EXISTS.
        // This is the ONLY situation where we MUST write an empty "()"
        // for the left side. Why? Because without it, the string would
        // ambiguously suggest the RIGHT subtree is actually the LEFT one.
        // The empty "()" acts as a placeholder to preserve the mapping
        // from string back to tree structure.
        // Format: "value()(right-subtree-string)"
        if (root->left == NULL) {
            return result + "()" + "(" + RIGHT + ")";
        }

        // CASE 3: Right child is NULL but left child EXISTS.
        // Here we OMIT the right child's parentheses entirely — the rules
        // say trailing empty right-child parentheses are unnecessary and
        // should be dropped to keep the string minimal.
        // Format: "value(left-subtree-string)"
        if (root->right == NULL) {
            return result + "(" + LEFT + ")";
        }

        // CASE 4: Both children exist (neither is NULL).
        // Include both subtrees, each wrapped in its own pair of parentheses.
        // Format: "value(left-subtree-string)(right-subtree-string)"
        return result + "(" + LEFT + ")" + "(" + RIGHT + ")";
    }
};

/*
==================== REVISION SUMMARY (READ THIS FIRST WHEN YOU FORGET) ====================

PROBLEM IN ONE LINE:
Given a binary tree, return its preorder string representation where each
node is "value" optionally followed by "(left)" and "(right)", but omit
unnecessary empty parentheses while preserving the one-to-one mapping
between the string and the original tree structure.

ANALOGY — "Reading a family tree aloud with minimal words":
Imagine you're describing a person's family to someone over the phone, and
you must say it in a way that they could reconstruct the exact tree later.
For each person, you say their name, then optionally describe their left
child and right child in parentheses. If a person has NO children, you just
say their name and stop — no need to say "no left child, no right child."
But if they have ONLY a right child, you MUST explicitly say "no left
child" (as an empty pause — "()") before describing the right child,
otherwise the listener would assume the single child you mention is the
left one. If they have ONLY a left child, you describe that child and just
don't mention the right side at all — trailing silence is understood.

THE OMISION RULES (the entire logic of this problem):
1. If a node has BOTH children NULL → write nothing for children.
   (Leaf: "3", not "3()()")
2. If a node has LEFT=NULL, RIGHT≠NULL → write "()" for left, then "(right)".
   (Placeholder needed: "1()(2)" — without the "()", "2" would be misread
   as the left child.)
3. If a node has LEFT≠NULL, RIGHT=NULL → write "(left)", omit right entirely.
   (Trailing empty right is unnecessary: "1(2)", not "1(2)()")
4. If a node has BOTH children ≠NULL → write both: "1(2)(3)".

WHY THESE RULES EXIST (the "uniqueness" constraint):
The problem guarantees the string must map back to ONE unique tree. If we
omitted the "()" in case 2, the string "1(2)" could mean either:
  - node 1 with left child 2, right child NULL, OR
  - node 1 with left child NULL, right child 2.
The empty "()" disambiguates — it's a deliberate placeholder that says
"there IS a left child here, and it's empty, so the next child MUST be
the right one."

DRY RUN (tree: [1,2,3,4] → 1 has left=2, right=3; 2 has left=4):
        1
       / \
      2   3
     /
    4

tree2str(1):
  result = "1"
  LEFT = tree2str(2), RIGHT = tree2str(3)

  tree2str(2):
    result = "2"
    LEFT = tree2str(4), RIGHT = tree2str(NULL) = ""
    tree2str(4):
      result = "4"
      LEFT = "", RIGHT = ""
      both children NULL → return "4"
    So LEFT = "4", RIGHT = ""
    Node 2: left≠NULL, right==NULL → case 3 → return "2(4)"

  tree2str(3):
    result = "3"
    LEFT = "", RIGHT = ""
    both children NULL → return "3"

  Back at node 1: LEFT = "2(4)", RIGHT = "3"
  Node 1: both children ≠NULL → case 4 → return "1(2(4))(3)"

Final: "1(2(4))(3)" — matches the expected LeetCode output exactly.

TIME COMPLEXITY: O(n), where n is the number of nodes in the tree.
Each node is visited exactly once, and at each node we do O(1) string
concatenations (the total length of all concatenated strings across the
whole recursion is proportional to the output size, which is O(n)).
SPACE COMPLEXITY: O(h) for the recursion call stack, where h is the tree
height (O(log n) for balanced, O(n) for skewed). Plus O(n) for the output
string itself.

TRIGGER WORDS for this pattern:
- "string representation of a tree," "preorder traversal with parentheses,"
  "omit unnecessary parentheses" → tree recursion with case analysis on
  which children are NULL, following the four omission rules above.
- Any problem that says "return a serialization that can be deserialized
  back uniquely" → think about what minimal information is needed to
  preserve the structure (often empty placeholders for missing children
  in specific cases).

COMMON MISTAKES:
1. Always writing "()" for NULL children — this produces "1(2()())(3()())"
   which is technically a valid tree encoding but violates the "omit
   unnecessary parentheses" requirement and fails LeetCode's tests.
2. Forgetting the "()" placeholder when left is NULL but right exists —
   this produces "1(3)" for a node with only a right child, which is
   ambiguous and maps to the WRONG tree (left child 3, right NULL).
3. Checking only one child's NULL status without considering the other —
   the omission rules depend on the COMBINATION of both children's states,
   so you must check all four cases (both NULL, left NULL only, right NULL
   only, neither NULL).
4. Not handling the base case (root == NULL) returning "" — without this,
   the recursion crashes or produces garbage for leaf nodes' children.

WHERE THIS SHOWS UP:
Tree serialization/deserialization patterns (of which this is a simplified
version) appear frequently at Amazon, Microsoft, and Google — often as a
warm-up before the harder "Serialize and Deserialize Binary Tree" (LC 297),
which requires a full round-trip encoding. LC 606 itself is commonly used
to test whether a candidate can carefully implement case-based logic in a
recursive tree traversal without missing edge cases.
================================================================================
*/






