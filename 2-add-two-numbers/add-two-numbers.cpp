class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Dummy head to simplify result list construction
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        int carry = 0;

        // Traverse both lists until both are exhausted
        while (l1 != NULL || l2 != NULL || carry != 0) {
            int sum = carry;  // start with carry

            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }

            // Create new node with digit value
            curr->next = new ListNode(sum % 10);
            curr = curr->next;

            // Update carry
            carry = sum / 10;
        }

        // Return result list (skip dummy head)
        return dummy->next;
    }
};
