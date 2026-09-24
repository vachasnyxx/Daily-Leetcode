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
        if (!head) return nullptr;

        ListNode* dummy = new ListNode(0, head); // dummy before head
        ListNode* prev = dummy;                  // prev points to dummy
        ListNode* curr = head;

        while (curr) {
            // check if current node has duplicates
            if (curr->next && curr->val == curr->next->val) {
                int duplicateVal = curr->val;
                // skip all nodes with duplicateVal
                while (curr && curr->val == duplicateVal) {
                    curr = curr->next;
                }
                prev->next = curr; // link prev to the next distinct node
            } else {
                prev = curr;       // move prev forward
                curr = curr->next; // move curr forward
            }
        }

        return dummy->next;
    }
};
