#include <iostream>
#include "Graph.h"
#include "fstream"
#include <set>

using namespace std;

void colorGraph(int n, vector<int> &listVertex, int *colorTarget, const Graph &graph,const vi *danhSachKe) {
    
    int *deg;                                            // Dynamic allocating because sometime we get huge of vertexs
    deg = new int[n];

    for (int i = 0; i < n; i++) {
        deg[i] = graph.getDeg(listVertex[i]);
    }                                   
    
    int maxDeg = 0;                                      // Biggest degree
    int secMaxDeg = 0;                                   // Second biggest degree

    int indexStart = 0;                   // IndexStart is node where algorithm start, its = k - 1 (where k is max degree)

    if (deg[0] > deg[1]){                        // BLOCK 1//  to get second biggest degree
        maxDeg = deg[0];                         
        secMaxDeg = deg[1];
        indexStart = listVertex[1];                                

    }else {
        maxDeg = deg[1];
        secMaxDeg = deg[0];
        indexStart = listVertex[0];                                     
    }
    
    for(int i = 2; i < n; i++){
        
        if(deg[i] >= maxDeg) {
            secMaxDeg = maxDeg;
            maxDeg = deg[i];
        } else if (deg[i] > secMaxDeg){
            secMaxDeg = deg[i];
            indexStart = listVertex[i];
        }
    }                                             // BLOCK 1//  


    bool visitedVer[n] = {false};                 // Array to check if we visited that vertex

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

    colorTarget[orderList[0]] = 0;

    for (int i = 1; i < n; i++) {
        int vertex = orderList[i];                     // Get the vertex 1 by 1 in orderList

        int color = 0;                                   // Start with smallest color

        if (danhSachKe[vertex].size() == 1) {                           // if it have 1 neighbor
            if(color == colorTarget[danhSachKe[vertex][0]]) {           // if color == neighbor
                color++;                                                // increment
            }
        } else {

            set<int> listColor;
            listColor.insert(11);                                           // add a big color
            for (int j = 0; j < danhSachKe[vertex].size(); j++) {         
                listColor.insert(colorTarget[danhSachKe[vertex][j]]);
            }

            set<int>::iterator it;
            for (it = listColor.begin(); it != listColor.end(); ++it) {     
                if(color == *it) {                                          // if color == its neighbor
                    color++;                                                // increment
                } else if (color < *it) {                                   // if color small than neighbor break
                    break;                          
                }
            }
        }  
        colorTarget[vertex] = color;
    }
}


int main() {

    string path = "C:\\Users\\Admin\\OneDrive\\Desktop\\AI\\GraphAlgorithm\\tinyG.txt";
    path = path.substr(0,1+path.find_last_of('\\'));
    path+= "mediumG.txt";                             // Using absolute path for debuggerVS recognize exe file    
    
    ifstream input;                                 
    input.open(path);
    int vertex, edge;                               // Vertex for number of vertex, edge for number of edge
    input >> vertex >> edge;   

    Graph G(vertex);                            // Create graph with variable vertex
    
    vector<int> firstArr, secArr;
    // int *secArr = new int[vertex];
    
    while (!input.eof()) { 
        int firstV, secV;                       // variable for vertex1, 2
        
        input >> firstV >> secV;
        firstArr.push_back(firstV);
        secArr.push_back(secV);
        G.addEdge(firstV, secV);                // Add edge to graph
    }
    input.close();


    vi *danhSachKe =  new vi [vertex];    // danhSachKe is array which an element is an vector<int> is vector contain its neighbor
                                            
    for (int i = 0; i < vertex; i++) {                  
        danhSachKe[i] = G.getAdj(i);
    }

    int *colorVertex= new int [vertex];             // this array is color of vertex

    for (int i = 0; i < vertex; i++) {
        colorVertex[i] = -1;
    }

    bool *graphIndex = new bool [vertex];             // this array to indicate if vertex is visited using dynamic allocating
    int *graphIdentity = new int [vertex];        // this array of vertex indicate which vertex belong to each child graph


    for (int i = 0; i < vertex; i++) {
        if (graphIndex[i] == false) {

            vector<int> tempGraph;              // vector for pushing back vertex which in same child graph
            tempGraph.push_back(i);             // Push back first vertex of child graph
            graphIndex[i] = true;              // Mark the first vertex is true
            
            
            for (int j = 0; j < tempGraph.size(); j++) {
                for (int k = 0; k < danhSachKe[tempGraph[j]].size(); k++) {     // get vertex 1 by 1 from tempGraph and enter its danhSachKe

                    int tempVer = danhSachKe[tempGraph[j]][k];          // get neighbor from tempGraph[j]

                    if (graphIndex[tempVer] == false) {               
                        tempGraph.push_back(danhSachKe[tempGraph[j]][k]);  
                        graphIndex[tempVer] = true;
                    } 
                }
            }

            colorGraph(tempGraph.size(), tempGraph, colorVertex, G, danhSachKe);

        }
    }


    string colorList[] = {"red", "green", "blue", "yellow","purple", "aqua", "aquamarine3", "green4", "gold2", "bisque", "cadetblue1", "darkred"};

    cout<<"graph tree {"<<endl;
    for (int i = 0; i < edge; i++) {
        cout << firstArr[i] << " -- " << secArr[i] << endl;
    }
    for (int i = 0; i < vertex; i++)
        cout << i << " [fillcolor=" << colorList[colorVertex[i]] << ", style=filled];" << endl;
    cout<<"}"<<endl;

    system("pause");
    return 0;

    return 0;
}