class Solution {
public:
    vector<int> arr;
    Solution(ListNode* head){
        ListNode* temp = head;
        while(temp != NULL){
            arr.push_back(temp->val);
            temp = temp->next;
        }
    }
    int getRandom() {
        int n = arr.size();
        int random_index = rand()%n;   //{0, 1, ..... n- 1}
        return arr[random_index];
    }
};
