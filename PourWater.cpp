// g++ --std=c++17 donuoc.cc -o donuoc
#include<iostream>
#include<tuple>
#include <map>
#include <vector>

using namespace std;

typedef  tuple<int, int, int> Vertex;
// (10 lit, 7 lit, 4 lit)

map<Vertex, bool> visited;

void printState (Vertex &u, Vertex &v){
    int l10,l7,l4;
    tie(l10,l7,l4) = u;
    cout<<"\"("<<l10<<","<<l7<<","<<l4<<")\" "<<"->";
    tie(l10,l7,l4) = v;
    cout<<"\"("<<l10<<","<<l7<<","<<l4<<")\";"<<endl;
}

void explore (Vertex &s) {
    visited[s] = true;

    int l10, l7, l4;
    tie(l10, l7, l4) = s;

    if (l7==2 or l4==2) exit(0);

    int do_max;
    
    // Place state consecutively to pouring water from each tank to the other tank by for loop
    vector<int> state = {l10, l7, l4, l10, l7}; // The state which we consider to action
    vector<int> max = {10, 7, 4, 10, 7};        // Max volume of each tank
    map<int, int> result;                      // Result of tank

    
    for (int i = 0; i < 3; i++) {               
        if (state[i] > 0) {                         // if volume in tank > 0 which mean we can pour out
            for(int j = 1; j < 3; j++) {
                if (state[i + j] < max[i + j]) {    // if volume in tank < max of it which mean we can pour in
                    do_max = min ((max[i + j] - state[i + j]), state[i]);

                    result[max[i]] = state[i] - do_max;
                    result[max[i + j]] = state[i+j] + do_max;
                    
                    if (j == 1) {
                        result[max[i + 2]] = state[i+2];
                    } else {
                        result[max[i + 1]] = state[i+1];
                    }
                   
                    Vertex v = make_tuple(result[10], result[7], result[4]);
                    
                    if (!visited[v]) {
                        printState (s, v);
                        explore(v);
                    }     
                }
            }
        }
    }
}
int main() {
    // Max of first is 10, second is 7, third is 4
    // We start at first tank is 0, second is 7, third is 4
    Vertex start = make_tuple(0, 7, 4);
    explore(start);
    return 0;
}
