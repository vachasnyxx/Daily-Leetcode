// class Solution {
// public:
//     vector<int> arr;
//     Solution(ListNode* head){
//         ListNode* temp = head;
//         while(temp != NULL){
//             arr.push_back(temp->val);
//             temp = temp->next;
//         }
//     }
//     int getRandom() {
//         int n = arr.size();
//         int random_index = rand()%n;   //{0, 1, ..... n- 1}
//         return arr[random_index];
//     }
// };






class Solution {
public:
    ListNode* Head;

    Solution(ListNode* head){
        Head = head;
    }
    int getRandom() {
        int count = 1;
        int result = 0;

        ListNode* temp = Head;

        while(temp != NULL){
            if(rand()% count <1.0/count){
                result = temp->val;
            }
            count++;
            temp = temp->next;
        }
        return result;
    }
};

