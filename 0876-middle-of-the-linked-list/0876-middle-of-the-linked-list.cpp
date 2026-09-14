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
//     ListNode* middleNode(ListNode* head) {
//         int len = 0;
//         ListNode* temp = head;

//         while(temp != NULL){
//             len++;
//             temp= temp->next;
//         }

//         int midIdx = len/2;
//         ListNode* mid = head;
//         for(int i = 1; i<= midIdx; i++){
//             mid = mid->next;
//         }
//         return mid;

//     }
// };





// class Solution {
// public:
//     ListNode* middleNode(ListNode* head) {
//         ListNode* slow = head;
//         ListNode* fast = head;

//         while(fast != NULL && fast->next != NULL){
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         return slow;
//     }
// };





class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        // Initialize two pointers:
        // 'slow' moves one step at a time
        // 'fast' moves two steps at a time
        ListNode* slow = head;
        ListNode* fast = head;

        // Loop continues as long as:
        // 1. 'fast' is not NULL (list not fully traversed)
        // 2. 'fast->next' is not NULL (so 'fast' can safely move two steps)
        while(fast != NULL && fast->next != NULL){
            // Move 'slow' one step forward
            slow = slow->next;

            // Move 'fast' two steps forward
            fast = fast->next->next;
        }

        // When loop ends:
        // - 'fast' has reached the end (or gone past it)
        // - 'slow' is exactly at the middle node
        return slow;
    }
};
