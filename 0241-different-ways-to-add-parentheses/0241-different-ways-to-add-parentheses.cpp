class Solution {
public:
    vector<int> solve(string expression) {
        vector<int> result;

        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == '+' || expression[i] == '-' ||
                expression[i] == '*') {
                vector<int> left_results = solve(expression.substr(0, i));
                vector<int> right_results = solve(expression.substr(i + 1));

                for (int& x : left_results) {
                    for (int& y : right_results) {
                        if (expression[i] == '+') {
                            result.push_back(x + y);
                        } else if (expression[i] == '-') {
                            result.push_back(x - y);
                        } else {
                            result.push_back(x * y);
                        }
                    }
                }
            }
        }
        if (result.empty()) {
                result.push_back(stoi(expression));
            }
            return result;
    }
    vector<int> diffWaysToCompute(string expression) {
        return solve(expression);
    }
};