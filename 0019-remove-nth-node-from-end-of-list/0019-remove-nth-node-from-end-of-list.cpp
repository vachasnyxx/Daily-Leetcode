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
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         int len = 0;
//         ListNode* temp = head;
//         while (temp != NULL) {
//             len++;
//             temp = temp->next;
//         }
//         if (n == len) {
//             head = head->next;
//             return head;
//         }
//         // nth from end = (len - n + 1)th from start
//         temp = head;
//         for (int i = 1; i < len - n; i++) {
//             temp = temp->next;
//         }
//         temp->next = temp->next->next;
//         return head;
//     }
// };



class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* slow = head;
        ListNode* fast = head;
        // 1st step is to traverse fast to n+1 steps forward

        for(int i = 1;i<=n+1;i++){
            if(fast == NULL) return head->next;
            fast = fast->next;
        }
        // move slow and fast at the same pace
        while(fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
        // now the slow is exactly at left of the nth node from the end
        slow->next = slow->next->next;
        return head;
    }
};