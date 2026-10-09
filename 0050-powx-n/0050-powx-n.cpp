class Solution {
public:
    double myPow(double x, int n) {
        long binform=n;
           if (n==0)
        {return 1.0;}
        if(x==0)
        {return 0;}
        if (x==1)
        {return 1.0;}
        if(n==1)
        {return x;}
        if(x==-1&&n%2==-1)
        {return -1.0;}
        if(x==-1&&n%2==0)
        {return 1.0;}
        if (n<0)
        {
           
            binform=-binform;
        }
        double ans=1;
        while (binform>0)
        {
            if(binform%2==1)
            {
                ans*=x;
            }
            x*=x;
            binform/=2;
        }
        return n < 0 ? 1.0 / ans : ans;
    }
};





// class Solution {
// public:
//     double myPow(double x, int n) {
//         long expo = n;
//         if (expo < 0) {
//             x = 1 / x;
//             expo = -expo;
//         }
//         return power(x,expo,1);
//     }

//     double power(double x, long n, double ans){
//         if(n == 0){
//             return ans;
//         }

//         if(n%2 != 0){
//             ans *= x;
//         }
//         return power(x*x, n/2, ans);
//     }
// };







// class Solution {
// public:
//     double myPow(double x, int n) {
//         long expo = n;
//         if (expo < 0) {
//             x = 1 / x;
//             expo = -expo;
//         }

//         double ans =1;

//         while(expo > 0){
//             if(expo%2 != 0){
//                 ans *= x;
//             }

//             x *= x;
//             expo /=2;
//         }
//         return ans;
//     }
// };