class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty()) return true;
        string result;
        for(char c :s ){
            if(isalnum(static_cast<unsigned char>(c))){
                result += tolower(c);
            }
        }
        int n = result.size();
        int i = 0;
        int j = n-1;

        while( i < j){
            if( result[i] != result[j]){
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};