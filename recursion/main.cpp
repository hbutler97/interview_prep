#include <iostream>

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>
//given a array of chars, print out all permutations
void printpermhelper(std::string slate, std::vector<char> &array){
    if(array.size() == 0) {
        std::cout << slate << std::endl;
    }
    else {
        for (size_t i = 0; i < array.size(); ++i) {
            std::vector<char> temp_array(array);
            std::string temp_string(1, temp_array[i]);
            temp_array.erase(temp_array.begin() + i);
            printpermhelper(slate + temp_string, temp_array);
        }
    }
}
void printperm(std::vector<char> &array){
    std::string slate;
    printpermhelper(slate, array);
}
int count(int n){
    if(n == 1)
        return 1;
    else
        return 1 + count(n -1);
}

void runcount(){
    std::cout << "Hello, World!" << count(6)<< std::endl;
}
void runprintchars() {
    std::vector<char> array = {'a','b','c','d'};
    printperm(array);
}

/*void stringtest(void) {
    std::string test("12345");
    std::vector<int> intvector(test.length());
    std::stringstream result;
    std::copy(intvector.begin(), intvector.end(), std::ostreambuf_iterator<int>(result, ""));
}*/
bool evaluate_expression(std::string s, std::string op, std::string &output){
    bool final_result(false);
    size_t op_pos = s.find(op,0);

    if(op_pos == std::string::npos ) {
        output.erase();
        output = s;
        return true;
    }
    size_t op_left(0);
    size_t op_right(0);

    size_t op_mult = s.find("*", op_pos+1);
    size_t op_add = s.find("+", op_pos+1);
    //Case 1 both == nops
    if(op_mult == std::string::npos && op_add == std::string::npos){
        op_right = std::string::npos;
    }
    //Case 2 one equal npos
    else if(op_mult ==std::string::npos || op_add == std::string::npos) {
       op_right = (op_mult == std::string::npos)? op_add:op_mult;
    }
    else {
        size_t op_m_diff = abs(op_pos - op_mult);
        size_t op_a_diff = abs(op_pos - op_add);
        op_right = (op_m_diff < op_a_diff)?op_mult:op_add;
    }

    op_mult =  s.find_last_of("*", op_pos - 1);
    op_add =  s.find_last_of("+", op_pos - 1);
    //Case 1 both == nops
    if(op_mult == std::string::npos && op_add == std::string::npos){
        op_left = std::string::npos;
    }
        //Case 2 one equal npos
    else if(op_mult ==std::string::npos || op_add == std::string::npos) {
        op_left = (op_mult == std::string::npos)? op_add:op_mult;
    }
    else {
        size_t op_m_diff = abs(op_pos - op_mult);
        size_t op_a_diff = abs(op_pos - op_add);
        op_left = (op_m_diff < op_a_diff)?op_mult:op_add;
    }

    std::string left_operand = (op_left == std::string::npos)?s.substr (0,op_pos):s.substr (op_left+1,op_pos-op_left-1);
    std::string right_operand = (op_right == std::string::npos)?s.substr(op_pos+1, s.size() - op_pos -1):s.substr(op_pos+1,op_right - op_pos - 1);

    long long int left_op = stoll(left_operand, nullptr);
    long long int right_op = stoll(right_operand, nullptr);
    long long int result = (op == "*")? left_op * right_op: left_op + right_op;

    std::string new_expression = (op_left != std::string::npos)?s.substr(0, op_left+1):"";
    std::string rest_of_string = (op_right != std::string::npos)?s.substr(op_right):"";
    final_result =(new_expression == "" && rest_of_string == "");
    new_expression = new_expression + (std::to_string(result)) + rest_of_string;
    output = new_expression;
    return final_result;
}
void driveexpression(){
    std::string output("74*3+4*1+2*3+50*23+2*8");
    bool done(false);
    while (!evaluate_expression(output, "*", output));/* {
     done =   evaluate_expression(output, "*", output);
    }*/
    done = false;
    while (!done) {
        done =   evaluate_expression(output, "+", output);
    }
    //runcount();
    //runprintchars();

}
std::vector<std::string> sbag;
void stringhelper(std::string slate, std::string s){
    if(s.size() == 0){
        sbag.push_back(slate);
        return;
    }
    for(size_t i = 0; i < s.size(); ++i ){
        stringhelper(slate + s.substr(i,1),s.substr(0,i) + s.substr(i+1));
    }
}
void stringper(std::string s, std::string slate){
    stringhelper(slate,s);
    for(size_t i =0 ;i < sbag.size();++i){
        std::cout << sbag[i] << std::endl;
    }
}
std::vector<std::vector<int>> bag;
void generatebinaryhelper(std::vector<int> n, std::vector<int> slate){
    if(n.size() == 0){
        bag.push_back(slate);
        return;
    }
    for(size_t i = 0; i < n.size(); ++i){
        std::vector<int> y;
        y.insert(y.end(), n.begin(), n.begin() + i);
        y.insert(y.end(), n.begin()+i+1, n.end());
        std::vector<int> z(slate);
        z.push_back(n[i]);
        generatebinaryhelper(y,z);
    }
}
void generatebinary(int n){
    std::vector<int> buffer;
    std::vector<int> slate;
    for(size_t i = 1; i <= n; i++)
        buffer.push_back(i);
    generatebinaryhelper(buffer,slate);
}
bool isbinaryhelper(std::vector<int> buffer, int root_index){
    //B string properties
    //Left child is less than root == 2*root_index
    //Right child is greater than root; == 2*root_index + 1
    if(root_index >= buffer.size())
        return true;
    if((root_index * 2) + 1 >= buffer.size() && (root_index * 2) < buffer.size()){
        isbinaryhelper(buffer, root_index * 2);
    }
    if(buffer[root_index * 2] <= buffer[root_index] && buffer[(root_index *2)+1] >= buffer[root_index]){
        isbinaryhelper(buffer, root_index * 2);
        isbinaryhelper(buffer, (root_index * 2)+1);
    }
    else {
        return false;
    }

}
bool isbinary(std::vector<int> buffer){
    std::vector<int> y(buffer.size() + 1);
    for(size_t i = 1; i <= buffer.size(); ++i){
        y[i] = buffer[i];
    }
    isbinaryhelper(y,1);
}

std::vector<std::string> chessbag;
void generatechesshelper(std::string slate, int value){
    int count(0);
    for(size_t i = 0; i < slate.size(); ++i){
        if(slate[i] == 'q'){
            count++;
        }
        if(count > 1)
            return;
    }
    std::string all_blanks(value, '-');
    if(slate == all_blanks)
        return;
    if(slate.size() >= value ){
        chessbag.push_back(slate);
        return;
    }
    generatechesshelper(slate + "-", value );
    generatechesshelper(slate + "q", value);

}
void generatechessperm(int value){
    std::string s(value,'-');
    std::string slate;
    generatechesshelper(slate, value);

}
void generatechessperm2(int value){
    std::string temp;
    for(int i = 0; i < value; ++i){
        for(int j = 0; j < value; ++j){
            temp = (i == j)? temp + "q": temp + "-";
        }
        chessbag.push_back(temp);
        temp.clear();
    }
}
std::vector<std::vector<std::string>> boardbag;
bool checklegal(std::vector<std::string> slate){
    if(slate.size() < 2){
        return true;
    }
    bool legal(true);
    std::pair<int,int> max( slate.size()-1, slate[0].length() -1);
    std::pair<int,int> min(0,0);
    std::pair<int,int> target;
    //lots of legal bound checking needed
    for(size_t i = 0; i < (slate.size()) ; ++i){
        target.second = slate[i].find('q');
        target.first = i;
        int search_x = target.second;
        int search_y = target.first;

        //search above me straight up
        while((search_y >= min.second) && legal == true) {
            if(slate[search_y][search_x] == 'q' && search_y != target.first)
                return false;
            search_y--;
        }
        search_x = target.second;
        search_y = target.first;
        //search below me
        while((search_y <= max.first) && legal == true) {
            if(slate[search_y][search_x] == 'q' && search_y != target.first) {
                return false;
            }
            search_y++;
        }
        search_x = target.second;
        search_y = target.first;
        //search up to the left
        while((search_x >= min.first && search_y >= min.second) && legal) {
            if(slate[search_y][search_x] == 'q' && search_x != target.second && search_y != target.first)
                return false;
            search_x--;
            search_y--;
        }
        search_x = target.second;
        search_y = target.first;
        //search up to the right
        while((search_x <= max.first && search_y >= min.second) && legal) {
            if(slate[search_y][search_x] == 'q' && search_x != target.second && search_y != target.first)
                return false;
            search_x++;
            search_y--;
        }
        //search down to the left
        search_x = target.second;
        search_y = target.first;
        while((search_x >= min.first && search_y <= max.first) && legal) {
            if(slate[search_y][search_x] == 'q' && search_x != target.second && search_y != target.first)
                return false;
            search_x--;
            search_y++;
        }
        //search down to the right
        search_x = target.second;
        search_y = target.first;
        while((search_x <= max.second && search_y <= max.first) && legal) {
            if(slate[search_y][search_x] == 'q' && search_x != target.second && search_y != target.first)
                return false;
            search_x++;
            search_y++;
        }
    }
    return legal;
}
void generateboardhelper(std::vector<std::string> slate, std::vector<std::string> rows) {
    if(!checklegal(slate)) {
        return;
    }
    if(rows.empty()) {
        boardbag.push_back(slate);
        return;
    }
    for(size_t i = 0; i < rows.size(); ++i){
        std::vector<std::string> temp_slate(slate);
        temp_slate.push_back(rows[i]);
        std::vector<std::string> temp_rows;
        temp_rows.insert(temp_rows.end(), rows.begin(), rows.begin() + i);
        temp_rows.insert(temp_rows.end(), rows.begin() + i+1, rows.end());
        generateboardhelper(temp_slate, temp_rows);
    }

}
void generateboards(std::vector<std::string> rows, int value){
    std::vector<std::string> slate;
    generateboardhelper(slate, rows);
}

using namespace std;
std::vector<vector<long long int>> bag2;
void helper(vector<long long int> arr, vector<long long int> slate, int index){

    if(index >= arr.size()){
        if(!slate.empty()) {
            bag2.push_back(slate);
        }
        return;
    }
    helper(arr, slate, index + 1);
    slate.push_back(arr[index]);
    helper(arr, slate, index + 1);
}
void getsets(vector <long long int> arr){
    vector<long long int> slate;
    helper(arr,slate, 0);
}
bool check_if_sum_possible(vector <long long int> arr, long long int k) {

    bool ret(false);
    getsets(arr);

    for(size_t i = 0; i < bag2.size(); ++i){
        vector<long long int> temp = bag2[i];
        int sum(0);
        for(size_t j = 0; j < temp.size(); ++j) {
            sum += temp[j];
        }
        if(sum == k){
            ret = true;
        }
    }

    return ret && (bag2.size() > 0);

}
bool checklastpal(std::string s){
    bool ispal(true);
    std::string my_s = s.substr(s.rfind("|") + 1);
    int begin(0);
    int end(my_s.size() -1);

    while((begin <= end) && ispal)
        ispal = (my_s[begin++] == my_s[end--]);

    return ispal;
}
std::string convertstring(std::string s, std::vector<bool> pipes){
    //assert pipes has size is one less than size of s
    std::string ret;
    std::size_t i = 0;
    for(i=0; i < s.size() ; ++i){
        if(i< pipes.size())
            ret = ret + (1,s[i]) + ((pipes[i])?"|":"");
        else
            ret = ret + (1,s[i]);
    }
    return ret;
}
std::string convertintstring(std::string s, std::vector<bool> pipes){
    //assert pipes has size is one less than size of s
    std::string ret;
    std::string my_s = s.substr(0, pipes.size() + 1);
    std::size_t i = 0;
    for(i=0; i < pipes.size() ; ++i){
        ret = ret + (1,my_s[i]) + ((pipes[i])?"|":"");
    }

    ret = "|" + ret + my_s[i] + "|";
    return ret;
}
bool ispal(std::string s){
    std::string my_s = "|" + s;
    if(s.rfind("|") == std::string::npos) return true;
    size_t second_pipe = (my_s.rfind("|") == std::string::npos) ? my_s.size() - 1 : my_s.rfind("|");
    size_t first_pipe = (my_s.rfind("|", second_pipe - 1) == std::string::npos) ? 0 : my_s.rfind("|", second_pipe - 1);
    std::string sample = my_s.substr(first_pipe+1, second_pipe - first_pipe - 1);

    bool ispal(true);
    int begin(0);
    int end(sample.size() -1);

    while((begin <= end) && ispal)
        ispal = (sample[begin++] == sample[end--]);

    return ispal;
}
std::vector<string> stringbag;
void genboolhelper(std::string s, int numb_slots, std::vector<bool> slate){
    if(slate.size() == numb_slots){
        std::string temp = convertstring(s, slate);
        if(checklastpal(temp))
            stringbag.push_back(temp);
        return;
    }
    slate.push_back(false);
    std::string temp = convertstring(s, slate);
    if(ispal(temp))
        genboolhelper(s,numb_slots,slate);
    slate.pop_back();
    slate.push_back(true);
    std::string temp2 = convertstring(s, slate);
    if(ispal(temp2))
        genboolhelper(s,numb_slots, slate);
    slate.pop_back();
}

void genboobag(std::string s){
    std::vector<bool> slate;
    int numb_slots = s.size() -1;
    genboolhelper(s, numb_slots, slate);
}


int main() {
    std::string s("abracadabra");
    genboobag(s);


    for(size_t i = 0; i < stringbag.size(); ++i){
        std::cout << stringbag[i] << std::endl;
    }


    return 0;
}

//std::cout << std::endl;
//single char std::cout << boardbag[0][0][0]<< std::endl;
//single row  std::cout << boardbag[0][0]<< std::endl;