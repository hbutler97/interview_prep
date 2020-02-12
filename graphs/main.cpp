#include <bits/stdc++.h>

using namespace std;
#include<unordered_map>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>

std::map<std::string, std::vector<string>> graph;
std::unordered_map<std::string, int> visited;
std::vector<std::vector<std::string>> slate;
std::vector<std::string> bag;
bool isvalid_neighbor(std::string vertix, std::string neighbor) {
    std::sort(vertix.begin(), vertix.end());
    std::sort(neighbor.begin(), neighbor.end());
    std::string temp;
    temp.resize(vertix.size() + neighbor.size());
    std::string::iterator it = std::set_intersection(vertix.begin(), vertix.end(), neighbor.begin(), neighbor.end(), temp.begin());
    temp.resize(it - temp.begin());

    return ((vertix.size() - temp.size()) == 1);
}

bool isvalid_neighbor2(std::string vertix, std::string neighbor) {
    int diff(0);
    for(size_t i =0; i < vertix.size(); i++){
        if(vertix[i] != neighbor[i])
            diff++;
    }
    return (diff == 1);
}


void trimslate(std::vector<std::vector<std::string>> slate){
    for(size_t i = 1; i<slate.size(); ++i){
        std::vector<std::string> temp;
        for(size_t j = 0; j < slate[i-1].size(); j++){

            for(size_t k = 0; k < slate[i].size(); k++){
                if(isvalid_neighbor2(slate[i-1][j], slate[i][k]))
                    if(!std::count(temp.begin(), temp.end(), slate[i][k]))
                        temp.push_back(slate[i][k]);
            }

        }
        slate[i] = temp;

    }
    for(size_t i = slate.size()-1; i> 0; --i){
        std::vector<std::string> temp;
        for(size_t j = 0; j < slate[i].size(); j++){

            for(size_t k = 0; k < slate[i-1].size(); k++){
                if(isvalid_neighbor2(slate[i-1][k], slate[i][j]))
                    if(!std::count(temp.begin(), temp.end(), slate[i-1][k]))
                        temp.push_back(slate[i-1][k]);
            }

        }
        slate[i-1] = temp;


    }
    for(size_t i = 0; i < slate.size(); i++)
        bag.push_back(slate[i][0]);
}

std::vector<std::string> check_level(std::vector<std::string> stable_level, std::vector<std::string> test_level){

    std::vector<std::string> ret;
    for(auto x: stable_level) {
        for(auto y: test_level){
            if(x != y && isvalid_neighbor2(x,y) && !std::count(ret.begin(), ret.end(),y)){
                ret.push_back(y);
            }
        }
    }
  return ret;
}

void buildgraphentry(std::vector<std::string> words, std::string node, std::vector<std::string> &neighbors){
    for(auto word: words){
        if(word != node && isvalid_neighbor2(word, node) && !std::count(neighbors.begin(), neighbors.end(), word)){
            neighbors.push_back(word);
        }
    }
}
void buildgraph(std::vector<string> words, std::string start, std::string stop){
    words.push_back(start);
    words.push_back(stop);
    visited[start] = 0;
    visited[stop] = 0;
    for(auto x: words){
        if(graph.find(x) == graph.end() && x != stop && x != start){
            visited[x] = 0;
            std::vector<std::string> neighbors;
            buildgraphentry(words, x, neighbors);
            graph[x] = neighbors;
        }
    }
}
void bfs(std::map<std::string, std::vector<string>> g, std::vector<string> words, std::string start, std::string stop){
    std::vector<std::string> level1;
    std::vector<std::string> level2;
    std::deque<std::string> q;
    q.push_back(start);
    visited[start] += 1;
    level1.push_back(start);
    slate.push_back(level1);
    std::vector<std::string> neighboards;
    buildgraphentry(words,start,neighboards);
    graph[start] = neighboards;
    bool stop_found(false);
    bool start_eq_stop = (start == stop);

    //neighboards.clear();
    //buildgraphentry(words,stop,neighboards);
    //graph[stop] = neighboards;

    while(!q.empty() && !stop_found){
        int level_size = q.size();
        for(size_t i = 0; i< level_size && !stop_found; ++i ){
            std::string key = q.front();
            for(size_t j = 0; j < graph[key].size() && !stop_found; ++j){
                std::string neighbor = graph[key][j];
                int allowed_visits = (start_eq_stop && neighbor == start)?2:1;
                if(visited[neighbor] < allowed_visits) {
                    visited[neighbor] += true;
                    if(neighbor == stop){
                        level2.clear();
                        level2.push_back(neighbor);
                        stop_found = true;
                        break;
                    }
                    else {
                        level2.push_back(neighbor);
                        q.push_back(neighbor);
                    }
                }
            }
            q.pop_front();
        }

        level2 = check_level(level1, level2);
        if(level2.empty()){
            std::vector<std::string> temp;
            temp.push_back("-1");
            slate.clear();
            slate.push_back(temp);
            return;
        }
        slate.push_back(level2);
        level1.clear();
        level1 = level2;
        level2.clear();
    }
    if(!stop_found) {
        neighboards.clear();
        neighboards.push_back(stop);
        slate.push_back(neighboards);
    }
    for(size_t z = slate.size() - 1; z >= 1; --z) {
        std::vector<std::string> temp = check_level(slate[z], slate[z - 1]);
        if(!temp.empty()) {
            slate[z - 1] = check_level(slate[z], slate[z - 1]);
        } else {
            temp.clear();
            temp.push_back("-1");
            slate.clear();
            slate.push_back(temp);
            return;
        }
    }

}
/*void bfs(std::map<std::string, std::vector<string>> g, std::string start, std::string stop){
    std::deque<std::string> q;
    q.push_back(start);
    visited[start] += 1;
    bool start_eq_stop = (start == stop);
    int start_stop_visit = (start_eq_stop)?2:1;
    std::vector<std::string> temp;
    temp.push_back(start);
    slate.push_back(temp);
    while(!q.empty()) {
        int level_size = q.size();
        for (size_t i = 0; i < level_size; ++i) {
            std::string key = q.front();
            for(size_t j = 0; j < g[key].size(); j++){
                if(key == start && visited[g[key][j]] < start_stop_visit) {
                    visited[g[key][j]] += 1;
                    q.push_back(g[key][j]);
                }
                else if(visited[g[key][j]] < 1){
                        visited[g[key][j]] += 1;
                        q.push_back(g[key][j]);
                }
            }
            q.pop_front();
        }
        std::vector<std::string> temp2;
        bool stop_is_here(false);
        for(size_t k = 0; k < q.size(); ++k){
            temp2.push_back(q[k]);
            stop_is_here = (q[k] == stop);
        }
        if(stop_is_here && temp2.size() > 1){
            int prev_level_size = slate[slate.size() - 1].size();
            bool works_with_level_above(false);
            for(size_t i = 0; i < prev_level_size && !works_with_level_above; ++i){
                if(isvalid_neighbor2(stop, slate[slate.size() -1][i])){
                    works_with_level_above = true;
                }
            }
            if(works_with_level_above){
                std::vector<std::string> z;
                z.push_back(stop);
                slate.push_back(z);
                return;
            }else {

                std::vector<std::string>::iterator it = std::find(temp2.begin(), temp2.end(), stop);
                temp2.erase(it);
                slate.push_back(temp2);
                std::vector<std::string> z;
                z.push_back(stop);
                slate.push_back(z);
                return;
            }
        }

        else if(!temp2.empty()) {
            slate.push_back(temp2);
        }


    }
}
*/
vector<string> string_transformation(vector<string> words, string start, string stop) {
    if(words.size() == 0 && start == stop){
        std::vector<string> temp;
        temp.push_back("-1");
        return temp;
    }
    if(stop.empty() || start.empty()) {
        std::vector<string> temp;
        temp.push_back("-1");
        return temp;
    }
    if(isvalid_neighbor2(start, stop)) {
        std::vector<std::string> temp;
        temp.push_back(start);
        temp.push_back(stop);
        return temp;
    }
    buildgraph(words,start,stop);
    bfs(graph, words, start, stop);
    for(size_t i = 0; i < slate.size(); ++i){
        if(slate[i][0].empty()){
            std::vector<std::string> bag2;
            bag2.push_back("-1");
            return bag;
        }
        bag.push_back(slate[i][0]);
    }
    return bag;
}

int main()
{
    ostream &fout = cout;

    int words_size;
    cin >> words_size;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> words(words_size);
    for (int words_i = 0; words_i < words_size; words_i++) {
        string words_item;
        getline(cin, words_item);

        words[words_i] = words_item;
    }

    string start;
    getline(cin, start);

    string stop;
    getline(cin, stop);

    vector<string> res = string_transformation(words, start, stop);

    for (int res_itr = 0; res_itr < res.size(); res_itr++) {
        fout << res[res_itr];

        if (res_itr != res.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";


    return 0;
}