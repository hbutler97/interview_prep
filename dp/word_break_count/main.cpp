#include<string>
#include<vector>
#include <iostream>
#include <unordered_set>
using namespace std;

vector<vector<bool>> bag;
vector<string> string_bag;
string build_string(vector<bool> slate, string &txt){
    string text(txt);
    string ret(1,text[0]);
    text.erase(0,1);

    for(size_t i = 0; i < slate.size(); i++){
        if(slate[i]){
            ret = ret + " " + text[0];
        } else {
            ret = ret + text[0];
        }
        text.erase(0,1);
    }
    return ret + text;
}
template <class Container>
void split(const std::string& str, Container& cont,
            char delim = ' ')
{
    std::size_t current, previous = 0;
    current = str.find(delim);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find(delim, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
}
bool valid_slate(unordered_set<string> &dictionary, vector<bool> slate, string txt, bool whole_string = false){
    string test_string = build_string(slate, txt);
    vector<string> test_string_vector;
    split(test_string, test_string_vector, ' ');
    bool valid(true);
    size_t loop = (whole_string)?test_string_vector.size():test_string_vector.size()-1;
    for(size_t i = 0; i < loop && valid; ++i){
        valid = (dictionary.find(test_string_vector[i]) != dictionary.end());
    }
    return valid;
}
void helper(unordered_set<string> &dictionary, vector<bool> slate, string txt){
    if(slate.size()>=txt.length())return;
    if(!valid_slate(dictionary,slate,txt))return;
    int test = txt.length();
    if(slate.size() == txt.length() - 1 && valid_slate(dictionary,slate,txt,true)){
        bag.push_back(slate);
        return;
    }
    slate.push_back(true);
    helper(dictionary, slate, txt);
    slate.pop_back();
    slate.push_back(false);
    helper(dictionary,slate, txt);
    slate.pop_back();
}

void permute(vector<string> &dictionary, vector<bool> slate, string txt){
    unordered_set<string> dictionary_set(dictionary.begin(), dictionary.end());
    helper(dictionary_set,slate,txt);
}
int wordBreakCount(vector<string> &dictionary, string &txt)
{
    vector<bool> slate;
    permute(dictionary, slate, txt);
    return bag.size();
}

int main() {
    vector<string> dictionary = {"kick", "start", "kickstart", "is", "awe", "some", "awesome",};
    string txt("kickstartisawesome");
    std::cout << wordBreakCount(dictionary,txt) << std::endl;
    for(auto x: bag){
        string_bag.push_back(build_string(x,txt));
    }
    return 0;
}
