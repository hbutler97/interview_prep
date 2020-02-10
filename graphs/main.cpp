#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cctype>
#include <queue>
#include <stack>
/*'#' = Water.
'.' = Land.
'a' = Key of type 'a'. Any lowercase character represents a key.
'A' = Door that can be opened with key 'a'. Any uppercase character represents a door.
'@' = Starting cell.
'+' = The goal cell.*/

class square{
public:
    square(char c, int row, int col, int max_col):
            m_visited(false),
            m_is_water(false),
            m_is_land(false),
            m_is_key(false),
            m_is_door(false),
            m_is_start(false),
            m_is_goal(false),
            m_row(row),
            m_col(col),
            m_vertix(row * max_col + col),
            m_max_col(max_col)
    {
        switch (c){
            case '#': m_is_water = true; break;
            case '.': m_is_land = true; break;
            case '@': m_is_start = true; break;
            case '+': m_is_goal = true; break;
            default : break; //TODO should throw exception
        }
        if(isalpha(c) && isupper(c)){
            m_is_door = true;
            m_door_value = (1, tolower(c));
        }
        if(isalpha(c) && islower(c)){
            m_is_key = true;
            m_key_value = (1, c);
            m_keys.insert(m_key_value);
        }
    };
    bool is_water(){return m_is_water;};
    bool is_land(){return m_is_land;};
    bool is_door(){return m_is_door;};
    bool is_start(){return m_is_start;};
    bool is_goal(){return m_is_goal;};
    bool is_key(){return m_is_key;};
    std::string get_key(){return m_key_value;};
    std::string get_door(){return m_door_value;};
    void set_visited(bool value){m_visited = value;};
    bool visited(){return m_visited;};
    int get_vertix(){return m_vertix;};
    bool have_key(std::string key){std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c);}); return (m_keys.find(key) != m_keys.end());};
    bool have_same_keys(std::set<std::string> keys){ return (keys == m_keys);};
    void add_key(std::string key){m_keys.insert(key);};
    void set_parent(square* parent){if(std::find(m_parent.begin(), m_parent.end(), parent) == m_parent.end()) m_parent.push_back(parent);};
    ~square() = default;

private:
    bool m_visited;
    bool m_is_water;
    bool m_is_land;
    bool m_is_key;
    std::string m_key_value;
    bool m_is_door;
    std::string m_door_value;
    bool m_is_start;
    bool m_is_goal;
    int m_row;
    int m_col;
    int m_vertix;
    int m_max_col;
    std::deque<square *>m_parent;
    std::set<std::string> m_keys;
};
std::vector<std::vector<square*>> graph;
square *start(nullptr);
square *goal(nullptr);
std::deque<square*> path_q;
/*
3
...B
.b#.
@#+.
*/
int getvertix(int row, int col, int max_col){
    return row * max_col + col;
}
void bsf(std::vector<std::vector<square*>> the_graph, square* start_sq, square* goal_sq){
    std::deque<square*> q;
    std::set<std::string> keyring;
    q.push_back(start_sq);
    start_sq->set_visited(true);
    if(start_sq->is_key())
        keyring.insert(start_sq->get_key());

    while(!q.empty()){
        square* node = q.front();
        std::cout << node->get_vertix() << std::endl;
        if(node->get_vertix() == goal_sq->get_vertix()){
            std::cout << "match" <<std::endl;
            return;
        }

        for(size_t j = 0; j < graph[node->get_vertix()].size(); j++){
            square* this_square = graph[node->get_vertix()][j];
            //case 1 come to a door and we don't have the key we skip adding it to the queue
            if(this_square->is_door() &&
               keyring.find(this_square->get_door()) == keyring.end()){
                continue;
            }
            //case 2 this is a key.  We insert it into our key ring
            if(this_square->is_key()){
                keyring.insert(this_square->get_key());
            }
            //case 3 we already visited this square and the key ring is the same
            // we don't add the queue
            if(this_square->visited() && this_square->have_same_keys(keyring) && keyring.size() > 0) {
                continue;
            }
            //case 4 come to a cell with an different keyring.  this we visit it again
            if(this_square->visited() && !this_square->have_same_keys(keyring) && keyring.size() > 0) {
                this_square->set_visited(false);
            }
            if(!(this_square->visited())){
                this_square->set_visited(true);
                this_square->set_parent(node);
                for(auto x: keyring){
                    this_square->add_key(x);
                }
                path_q.push_back(this_square);
                q.push_back(this_square);
            }
        }
        q.pop_front();
    }
}
void build_graph(std::vector<std::string> maze){
    int col_max = maze[0].length();
    int row_max = maze.size();
    std::vector<std::pair<int, int>> neighbors = {{0,-1}, {0,1},{-1,0},{1,0}};
    graph.resize(row_max * col_max);
    std::vector<square*> buffer(row_max*col_max);
    for(size_t col = 0; col < col_max; col++){
        for(size_t row = 0; row < row_max; row++) {
            int value = getvertix(row,col,col_max);
            buffer[value] = new square(maze[row][col], row, col, col_max);
        }
    }
    for(size_t col = 0; col < col_max; col++){
        for(size_t row = 0; row < row_max; row++){
            for(auto x:neighbors){
                if(row + x.first >= 0 &&
                   row + x.first < row_max &&
                   col + x.second >= 0 &&
                   col + x.second < col_max &&
                   maze[row + x.first][col + x.second] != '#'){
                    int value = getvertix(row,col,col_max);
                    square *new_neighbor = buffer[getvertix(row + x.first, col + x.second, col_max)];
                    if(new_neighbor->is_start())
                        start = new_neighbor;
                    if(new_neighbor->is_goal())
                        goal = new_neighbor;
                    graph[value].push_back(new_neighbor);
                }
            }
        }
    }
}
int main(){
    std::vector<std::string> test;
    test.push_back("+B...");
    test.push_back("####.");
    test.push_back("##b#.");
    test.push_back("a...A");
    test.push_back("##@##");

    build_graph(test);
    bsf(graph,start, goal);
}