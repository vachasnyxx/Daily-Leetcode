class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int> que;

        for(int i = 1; i<= n; i++){
            que.push(i);
        }

        while(que.size() > 1){
            for(int count = 1; count <= k -1; count++){
                que.push(que.front());
                que.pop();
            }

            que.pop();
        }

        return que.front();
    }
};


















// using queue
// class Solution {
// public:
//     int findTheWinner(int n, int k) {
//         queue<int> que;

//         for(int i = 1; i<= n; i++){
//             que.push(i);
//         }

//         while(que.size() > 1){
//             for(int count = 1; count <= k -1; count++){
//                 que.push(que.front());
//                 que.pop();
//             }

//             que.pop();
//         }

//         return que.front();
//     }
// };















// approach of simulation and using array
// class Solution {
// public:
//     int findTheWinner(int n, int k) {
//         vector<int> arr;

//         for(int i = 1; i<= n; i++){
//             arr.push_back(i);
//         }

//         int i = 0;// game starts from 1st player which is sitting at index 0 

//         while(arr.size() > 1){
//             int idx = (i + k - 1) % arr.size();

//             arr.erase(arr.begin() + idx);   

//             i = idx;
//         }

//         return arr[0];
//     }
// };