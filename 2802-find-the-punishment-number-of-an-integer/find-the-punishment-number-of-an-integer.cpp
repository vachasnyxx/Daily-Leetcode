
class Solution {
public:
    bool check(int sq, int currsum, int num) {

        if (sq == 0) {
            return currsum == num;
        }

        return check(sq / 10, currsum + sq % 10, num) ||
               check(sq / 100, currsum + sq % 100, num) ||
               check(sq / 1000, currsum + sq % 1000, num) || check(sq / 10000, currsum + sq % 10000, num);
    }
    int punishmentNumber(int n) {
        int punish = 0;

        for (int num = 1; num <= n; num++) {
            int sq = num * num;

            if (check(sq, 0, num) == true) {
                punish += sq;
            }
        }

        return punish;
    }
};





















// class Solution {
// public:
//     bool check(int i, int currsum, string s, int num, vector<vector<int>>&
//     t){
//         if(i == s.size()){
//             return currsum == num;
//         }

//         if(currsum > num){
//             return false;
//         }

//         if(t[i][currsum] != -1){
//             return t[i][currsum];
//         }

//         bool possible = false;

//         for(int j = i; j<s.size(); j++){
//             string sub = s.substr(i, j-i+1);

//             int val = stoi(sub);

//             possible = possible || check(j+1, currsum+val,s,num,t);

//             if(possible == true){
//                 return true;
//             }
//         }

//         return  t[i][currsum] = possible;
//     }
//     int punishmentNumber(int n) {
//         int punish = 0;

//         for(int num  = 1; num <= n; num++){
//             int sq = num * num;

//             string s = to_string(sq);

//             vector<vector<int>> t(s.length(), vector<int> (num+1, -1));

//             if(check(0,0,s,num,t) == true){
//                 punish += sq;
//             }
//         }

//         return punish;
//     }
// };
