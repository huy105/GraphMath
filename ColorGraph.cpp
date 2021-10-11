#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

void colorGraph(int n, Graph graph, int colorTarget[]) {
    vi *danhSachKe;
    danhSachKe = new vi [n];                       // danhSachKe is array which an element is an vector<int>
                                                    // is vector contain its neighbor
    for (int i = 0; i < n; i++) {                  
        danhSachKe[i] = graph.getAdj(i);
    }

    int *deg;                                            // Dynamic allocating because sometime we get huge of vertexs
    deg = new int[n];                                    
    
    int maxDeg = 0;                                      // Biggest degree
    int secMaxDeg = 0;                                   // Second biggest degree

    deg[0] = graph.getDeg(0);
    deg[1] = graph.getDeg(1);

    int indexStart = 0;                          // IndexStart is node where algorithm start, its = k - 1 (where k is max degree)
    if (deg[0] > deg[1]){                        // BLOCK 1//  to get second biggest degree
        maxDeg = deg[0];                         
        secMaxDeg = deg[1];
        int indexStart = 1;                                

    }else {
        maxDeg = deg[1];
        secMaxDeg = deg[0];
        int indexStart = 0;                                     
    }
    
    for(int i = 2; i < n; i++){
        
        deg[i] = graph.getDeg(i);
        
        if(deg[i] >= maxDeg) {
            secMaxDeg = maxDeg;
            maxDeg = deg[i];
        } else if (deg[i] > secMaxDeg){
            secMaxDeg = deg[i];
            indexStart = i;
        }
    }                                             // BLOCK 1//  

    bool visitedVer[7] = {false};                 // Array to check if we visited that vertex

    vector<int> orderList;                                      // OrderList is vector of vertex using greedy algorithm 
    orderList.push_back(indexStart);                            // Push vertex first to order
    visitedVer[indexStart] = true;

    int i = 0;
    do {
        int node = orderList[i];                                // Take vertex 1 by 1 in orderList (assign to variable node that vertex)
        for(int j = 0; j < danhSachKe[node].size(); j++) {
            
            int tempVer = danhSachKe[node][j];                  // Get the temp vertex in danhSachKe[node]

            if(visitedVer[tempVer] == false) {                        // If we haven't visited that vertex
                
                orderList.push_back(danhSachKe[node][j]);       // Push it to orderList
                visitedVer[tempVer] = true;                     // Mark it true
            } 
        
        }

        i++;
    } while (orderList.size() != n);                            // Till orderList size == n it stop

    // Now we get an order vector of vertex for coloring (orderList)

    int colorTarget[n];                     // Make an array of color for each vertex

    for (int i = 0; i < n; i++) {           // Assign each vertex to maximum color
        colorTarget[i] = maxDeg;
    }

    for (int i = 0; i < n; i++) {
        int vertex = orderList[i];                     // Get the vertex 1 by 1 in orderList

        int color = 0;                                  // Start with smallest color

        for (int j = 0; j < danhSachKe[vertex].size(); j++) {         
            
            int checkVertex = danhSachKe[vertex][j];                // Get vertex 1 by 1 in danhSachKe[vertex]

            if (color == colorTarget[checkVertex]) {                   // If color already in its neighbor 
                color++;                                            // Increment color
            } else if (color < colorTarget[checkVertex]) {             // If color smaller than its neighbor 
                continue;                                           // Do nothing
            }
        }
        colorTarget[vertex] = color;
    }
}




int main() {

    int n = 7;                     // n là số đỉnh

    Graph G(n);
    G.addEdge(0,5);
    G.addEdge(0,1);
    G.addEdge(4,3);
    G.addEdge(6,4);
    G.addEdge(5,4);
    G.addEdge(0,2);
    G.addEdge(0,6);
    G.addEdge(5,3);

    int colorVertex[n];

    colorGraph(n, G, colorVertex);

    return 0;
}