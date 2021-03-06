#ifndef GRAPH_H
#define GRAPH_H
#include <istream>
#include <vector>
using namespace std;

#define vi vector<int>


class Graph{
    private:
        int sodinh;
        int socanh;
        vi *danhsachke;
        bool *visited;
    public:
        Graph(int V){
            sodinh = V;
            socanh = 0;
            danhsachke = new vi [sodinh];
            visited = new bool [sodinh];
        }
        Graph (istream &in){
            int v, w;
            in>>sodinh;
            in>>socanh;
            for (int i=0; i < socanh; i++){
                in>>v>>w;
                danhsachke[v].push_back(w);
                danhsachke[w].push_back(v);
            }
        
        }
        void addEdge(int v, int w){
            socanh++;
            danhsachke[v].push_back(w);
            danhsachke[w].push_back(v);
        }

        vi getAdj(int v) const {
            return danhsachke[v];               // trả ra danh sách kề tại mỗi đỉnh v
        }
        int getV(){
            return sodinh;
        }
        int getE(){
            return socanh;
        }
        int getDeg(int v) const {                     // Tính số đỉnh nút v
            vi kev = getAdj(v);
    
            return kev.size();
        }
        void explore(int v) {
            vi danhsachke = getAdj(v);

            visited[v] = true;
            cout << v << " ";
            for (int i = 0; i < danhsachke.size(); i++) {
                if (visited[danhsachke[i]] == false) {
                    explore(danhsachke[i]);
                }
            }
        }
};
#endif