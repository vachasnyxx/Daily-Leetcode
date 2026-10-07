class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        // Base case: If the list is empty or has only one node, return it as is
        if (head == NULL || head->next == NULL) {
            return head;
        }

        // Recursively process the next node
        ListNode* nextNode = removeNodes(head->next);

        // If the current node's value is less than the next node's value, skip it
        if (head->val < nextNode->val) {
            return nextNode;
        }

        // Otherwise, retain the current node and link it to the modified next node
        head->next = nextNode;
        return head;
    }
};
