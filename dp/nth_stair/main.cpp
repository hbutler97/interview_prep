#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long int helper(vector<int> steps, int n){
    long long int ret(0);
    if(n < 0) return 0;
    if(n == 0) return 1;
    if(n > 0 && n < steps[0]) return 0;
    for(size_t i = 0; i < steps.size(); ++i){
        ret += helper(steps, n-steps[i]);
    }
    return ret;
}
long long int permute(vector<int> steps, int n){
    sort(steps.begin(), steps.end());
    return helper(steps, n);
}
/*long long int countWaysToClimb(vector<int> steps, int n) {
    return permute(steps, n);
}*/

long long int countWaysToClimb(vector<int> steps, int n) {
    vector<long long int> dp(n+1, 0);
    sort(steps.begin(), steps.end());
    dp[0] = 1; //step 0

    //need a check for step greater than n

    for(size_t i= steps[0]; i <= n; ++i){
        long long int ways(0);
        for(auto x: steps){
            if(i >= x)
                ways += dp[i-x];
        }
        dp[i] = ways;
    }

    return dp[n];
}


//

int main() {
    vector<int> steps={2,3,5}; 
    countWaysToClimb(steps,10);

    return 0;
}
