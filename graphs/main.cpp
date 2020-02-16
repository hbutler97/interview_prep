#include<vector>
#include <iostream>
#include <queue>
using namespace std;
vector<vector<int>> keypad {{1,2,3},
                            {4,5,6},
                            {7,8,9},
                            {-1,0,-1}};
int keypad_row_size = 3;
int keypad_col_size = 4;
vector<pair<int, int>> moves {{-1,2},
                              {-1,-2},
                              {1,2},
                              {1,-2},
                              {-2,1},
                              {-2,-1},
                              {2, 1},
                              {2, -1}};
void convert_num_to_row_col(int num, int row_size, int & row, int &col){
    if(num == 0){
        row = 3;
        col = 1;
    } else {
        row = (num - 1) / row_size;
        col = (num - 1) % row_size;
    }
}
int row_col_to_key(int row, int col){
    return keypad[row][col];
}

bool is_legal_row(int row){
    return (row >= 0 && row < keypad_col_size);
}
bool is_legal_col(int col){
    return (col >= 0 && col < keypad_row_size);
}
bool is_pound_start(int row, int col){
    return ((row == 3 && col == 0) || (row == 3 && col == 2));
}
vector<pair<long long int, long long int>> getlegalmoves(int startdigit){
    int row(0);
    int col(0);
    vector<pair<long long int, long long int>> ret;
    convert_num_to_row_col(startdigit, keypad_row_size, row, col);
    for(size_t i = 0; i < moves.size(); ++i){
        int dest_row = row + moves[i].first;
        int dest_col = col + moves[i].second;
        if(is_legal_row(dest_row) && is_legal_col(dest_col) && !is_pound_start(dest_row,dest_col)){
            ret.push_back({dest_row,dest_col});
        }
    }
    return ret;
}
/*long long int helper(vector<long long int> slate, int startdigit, int phonenumberlength){
    long long int ret(0);
    if(slate.size() == phonenumberlength) {
        return 1;
    }
    vector<pair<int, int>> legal_moves = getlegalmoves(startdigit);
    for(size_t i = 0; i < legal_moves.size(); i++){
        int key = keypad[legal_moves[i].first][legal_moves[i].second];
        slate.push_back(key);
        ret += helper(slate, key, phonenumberlength);
        slate.pop_back();
    }
    return ret;
}
long long int numPhoneNumbers(int startdigit, int phonenumberlength) {
    vector<long long int> slate{startdigit};
    return helper(slate, startdigit, phonenumberlength);

}*/
int number_legal_neighbors(int key){
    return getlegalmoves(key).size();
}
vector<long long int> getneighbornumbs(int key){
    std::vector<pair<long long int, long long int>> neighbors = getlegalmoves(key);
    std::vector<long long int> int_neighbors;
    for(size_t i = 0; i < neighbors.size(); ++i){
        int_neighbors.push_back(row_col_to_key(neighbors[i].first, neighbors[i].second));
    }
    return int_neighbors;
}

long long int numPhoneNumbers(int startdigit, int phonenumberlength) {
    vector<long long int> dp(phonenumberlength + 1, 0);
    vector<vector<long long int>> map;
    //create neighbor table;
    for(size_t i = 0; i < 10; ++i){
        map.push_back(getneighbornumbs(i));
    }
    dp[0] = 0;
    dp[1] = map[startdigit].size();
    deque<int> q;
    q.push_back(startdigit);
    for(size_t entry = 2; entry < phonenumberlength; ++entry){
        long long int level_size = q.size();
        for(long long int j = 0; j < level_size; ++j)
        {
           int key = q.front();
           for(size_t i = 0; i < map[key].size(); ++i){
               q.push_back(map[key][i]);
               dp[entry] += map[map[key][i]].size();
           }
           q.pop_front();
        }
    }
    return dp[phonenumberlength - 1];
}

long long int numPhoneNumbers3(int startdigit, int phonenumberlength) {

    vector<vector<long long int>> dp(10, vector<long long int>(phonenumberlength, 0));
    dp[startdigit][0] = 1;
    vector<vector<long long int>> map;

    for(size_t i = 0; i < 10; ++i){
        map.push_back(getneighbornumbs(i));
    }

    for(size_t i = 1; i < phonenumberlength; ++i){
        for(size_t num = 0; num < 10; ++num){
            vector<long long int> temp = map[num];
            for(auto x: temp) {
                dp[num][i] += dp[x][i-1];
            }
        }
    }
    long long int ret(0);
    for(size_t i = 0; i < 10; ++i){
        ret += dp[i][phonenumberlength-1];
    }
    return  ret;
}
int main(){
    std::cout << numPhoneNumbers3(6,30) << std::endl;
    //std::cout << numPhoneNumbers(1,7) << std::endl;
    return EXIT_SUCCESS;
}