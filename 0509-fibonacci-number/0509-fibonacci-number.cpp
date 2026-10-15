class Solution {
public:
    int fibo(int n){
        if(n == 1) return 1;
        if(n == 0) return 0;
        return fibo(n-1) + fibo(n-2);
    }
    int fib(int n) {
        return fibo(n);
    }
};