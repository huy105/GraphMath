#include <iostream>
#include "Graph.h"


using namespace std;

void pruferCodeCompression(int n, int deg[],vi danhSachKe[], int pruferCode[]) {       //deg là mảng số đỉnh mỗi nút

    int label = 1; while(deg[label] != 1) label ++;    // label là nhãn nhỏ nhất của phần tử có bậc 1  và đỉnh đó khác 0
    int x = label;                                      // gán nhãn nhỏ nhất có bậc 1 cho x

    
    for (int i = 0; i <= n - 2; i++) {
        
        deg[x]--;                                 //bớt đỉnh của dòng trên

        int viTri = 0;      // nhãn của dòng dưới prufercode

        viTri = danhSachKe[x].front();
        
        pruferCode[i] = viTri;                      // gán giá trị cho dòng dưới prufercode

        int index;
        for (int j = 0; j < danhSachKe[viTri].size(); j++) {
            if (danhSachKe[viTri][j] == x) {
                index = j;                             // lấy ra vị trí của phần tử kề với phần tử ở dòng dưới
                break;                                  // trong danh sách kề
            }                                           
        }

        // ở đây ta sẽ xóa đi phần tử đã xuất hiện ở dòng trên để danhSachKe ở dòng dưới 
        // không còn phần tử này nữa

        danhSachKe[viTri].erase(danhSachKe[viTri].begin()+index);
        
        deg[pruferCode[i]]--;                               // bậc của đỉnh ở dòng dưới bớt đi 1
        // labelNode[label]--;                                 // label của phần tử đầu tiên đã có nên ko xuất hiện ở dòng trên nữa

        int label = 1; while(deg[label] != 1) label++;     // tìm lại node có bậc là 1 và nhỏ nhất và đỉnh đó khác 0
        x = label;                                      // gán nhãn nhỏ nhất có bậc 1 cho x

    }
}

int main() {

    int n = 10;                     // n là số đỉnh

    Graph G(n);
    G.addEdge(0,2);
    G.addEdge(0,3);
    G.addEdge(2,4);
    G.addEdge(2,6);
    G.addEdge(2,9);
    G.addEdge(6,1);
    G.addEdge(6,5);
    G.addEdge(9,7);
    G.addEdge(9,8);

    vi *danhSachKe;
    danhSachKe = new vi [n];                        // danhSachKe là array mã mỗi phần tử 
                                                    // là vector chứa các đỉnh kề
    for (int i = 0; i < n; i++) {                  
        danhSachKe[i] = G.getAdj(i);
    }

    int deg[n];                                     // Danh sách số bậc mỗi đỉnh
    
    for (int i = 0; i < n; i++) {
        deg[i] = G.getDeg(i);
    }

    int pruFer[n - 2];

    pruferCodeCompression(n, deg, danhSachKe, pruFer);

    for (int i = 0; i < n - 2; i++) {
        cout << pruFer[i] << " ";
    }
    
    return 0;
}