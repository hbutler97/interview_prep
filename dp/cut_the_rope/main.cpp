#include <iostream>
#include <vector>

long long int max_product_from_cut_pieces(int n) {
    std::vector<long long int> dp;
    // i * max(maxproduct(n - i), n-i)
    // 0  1  2  3  4  5  6
    //[x  1  1  2           ]
    dp.push_back(0);
    dp.push_back(1);
    long long int max_product_n(0);
    for(size_t i = 2; i <= n; ++i){
        for(size_t j = 1; j < i; j++) {
            long long int max = (dp[i - j]> (i-j))? dp[i-j]:(i-j);
            long long int temp = j * max;
            max_product_n = (temp > max_product_n)? temp:max_product_n;
        }
        dp.push_back(max_product_n);
    }

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    max_product_from_cut_pieces(6);
    return 0;
}
