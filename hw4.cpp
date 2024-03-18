#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <math.h>
using namespace std;

class Tree {
private:
    int node_number;
public:
    int degree[10];
    int value[10];
    int neighbor[10][10];
    vector<int> ans_minimumHeight;
    string gate[10];
    Tree();
    void addEdge(int v,int w);
    int get_nodeNumber();
    void insert_nodeNumber(int x);
    void insert_gate(string s,int index);
    

};
Tree :: Tree() {
    node_number = 0;
    for(int i = 0;i < 10;i++) {
        for(int j = 0;j < 10;j++) {
            neighbor[i][j] = 0;
        }
    }
    for(int i = 0;i < 10;i++) {
        degree[i] = 0;
    }
    for(int i = 0;i < 10;i++) {
        value[i] = -1;
    }
}
void Tree :: addEdge(int v,int w) {
    neighbor[v][w] = 1;
    neighbor[w][v] = 1;
    degree[v]++;
    degree[w]++;
}
int Tree :: get_nodeNumber() {
    return node_number;
}
void Tree :: insert_nodeNumber(int x) {
    node_number = x;
}

void Tree :: insert_gate(string s,int index) {
    gate[index] = s;
}
int calculate_ans(string logicGate,int sum,int inputNumber) {
    if(inputNumber == 1) {
        inputNumber = 2;
        sum = sum + sum;
    }
    if(logicGate == "AND") {
        if(sum == inputNumber) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if (logicGate == "OR") {
        if(sum >= 1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if (logicGate == "NAND") {
        if(sum <= inputNumber -1 ) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if (logicGate == "NOR") {
        if(sum == 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if (logicGate == "XOR") {
        if(sum >= 1 && sum <= inputNumber-1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if (logicGate == "XNOR") {
        if(sum == inputNumber || sum == 0) {
        return 1;
        }
    else {
        return 0;
    }
    }
}

int main(int agrc,char *argv[]) {
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    outfile.open(argv[2]);
    if(!infile) {
      //  cout << "cannot open infile" << endl;
        return 0;
    }
    if(!outfile) {
       // cout << "cannot open outfile" << endl;
        return 0;
    }
    int node_number;
    string temp;
    int node_index;
    int node_index2;
    string gate;
    Tree tree;
    infile >> node_number;
    tree.insert_nodeNumber(node_number);
   // outfile << node_number << endl;
    getline(infile,temp);
    for(int i = 0;i < node_number-1;i++) {
        char c;
        infile.get(c);
        infile >> node_index;
        infile.get(c);
        infile >> node_index2;
        infile.get(c);
        tree.addEdge(node_index,node_index2);
      //  outfile << node_index << " " << node_index2 << endl;
        getline(infile,temp);
    }
  
    while(!infile.eof()) {
        infile >> node_index;
        char c;
        infile.get(c);
        infile >> gate;
        tree.insert_gate(gate,node_index);
      //  outfile << node_index << " : " << gate << endl;
        getline(infile,temp);
    }
    infile.close();
    /////////////////////////////////////////////////////////////
    int d[10];
    for(int i = 0;i < 10;i++) {
        d[i] = tree.degree[i];
    }
    int n[10][10];
    for(int i = 0;i < 10;i++) {
        for(int j = 0;j < 10 ;j++) {
            n[i][j] = tree.neighbor[i][j];
        }
    }
    ////////////////////////////////////mininum height
    queue <int> q;
    for(int i = 0; i < node_number;i++) {
        if(d[i] == 1) {
            q.push(i);
        }
    }
    while(node_number > 2) {
        node_number -= q.size();
        int qsize = q.size();
        for(int i = 0;i < qsize;i++) {
            int temp = q.front();
            q.pop();
            d[temp]--;
            int neighbor_index;
            for(int i = 0;i < tree.get_nodeNumber();i++) {
                if(n[temp][i] == 1) {
                    neighbor_index = i;
                    n[temp][i] = 0;
                }
            }
            d[neighbor_index]--;
            n[neighbor_index][temp] = 0;
            if(d[neighbor_index] == 1) {
                 q.push(neighbor_index);
            }
              
        
        }
    }
    while(!q.empty()) {
        int root = q.front();
        q.pop();
        tree.ans_minimumHeight.push_back(root);
    }
     /////////////////////////////////////////////////////////////////// SAT
    int count_degreeOne = 0; //the number of degreeone node in initially
    int D[10];
    for(int i = 0;i < 10;i++) {
        D[i] = tree.degree[i];
    }
    for(int i = 0;i < tree.get_nodeNumber();i++) {
        if(D[i] == 1) {
            count_degreeOne++;
        }
    }
    int root_index;
    for(int i = 0;i < tree.ans_minimumHeight.size();i++) { ///times of minumum height root 
        root_index = tree.ans_minimumHeight[i];
        outfile << "root=" << root_index << endl;
        for(int i = 0;i < pow(2,count_degreeOne);i++) { //// get SAT from every minumum height root
            vector <int> degreeOneVector;////traverse;
            for(int j = 0;j < tree.get_nodeNumber();j++) {
                if(D[j] == 1) {
                degreeOneVector.push_back(j);
                }
            }
            int try_index = i;  ////initialize input value (dec to bin)
            for(int i = 0;i < degreeOneVector.size();i++) {
                tree.value[degreeOneVector[degreeOneVector.size()-1-i]] = try_index %  2 ;
                try_index /= 2;
            }
            int degreeArray[10];
            for(int  i = 0;i < 10;i++) {
                degreeArray[i] = tree.degree[i];
            }
            int neighborArray[10][10];
            for(int i = 0;i < 10;i++) {
                for(int j = 0;j < 10;j++) {
                    neighborArray[i][j] = tree.neighbor[i][j];
                }
            }
            
            /////////////////////////////////////// 
            int flag_canCalculate = 0;
            int neighbor_index;
            vector <int> calculateVector;
            while(degreeOneVector.size() > 0) {
                int tryCombination = degreeOneVector.size();
            for(int i = 0;i < tryCombination;i++) {  // find reasonable calculate combinaiton 
                int tryCombination_index = degreeOneVector[i];
                for(int i = 0;i < tree.get_nodeNumber();i++) {
                    if(neighborArray[tryCombination_index][i] == 1) {
                        neighbor_index = i;
                        break;
                    }
                }
                for(int i = 0;i < degreeOneVector.size();i++) {///////  find index of (degree = 1 and neighbor = neighbor_index)
                        for(int j = 0;j < tree.get_nodeNumber();j++) {
                            if(neighborArray[degreeOneVector[i]][j] == 1 && j == neighbor_index) {
                                calculateVector.push_back(degreeOneVector[i]);
                            }
                        }
                }
                ////////////////////////////////////////////////////
                int neighborIndex_neighbor = 0; /// the number of neighbors of neighbor_index
                for(int i = 0;i < tree.get_nodeNumber();i++) {
                    if(neighborArray[neighbor_index][i] == 1) {
                        neighborIndex_neighbor++;
                    }
                }
                //////////////////////successful calculate combination 
                if(neighbor_index == root_index) { ////// successful calculate combination condition 1
                    if(neighborIndex_neighbor == calculateVector.size()) {
                        flag_canCalculate = 1;
                        break;
                    }
                }
                else if(neighbor_index != root_index) { ////// successful calculate combination condition 2
                    if(neighborIndex_neighbor - 1 == calculateVector.size()) {
                        flag_canCalculate = 1;
                        break;
                    }
                }
                if(flag_canCalculate == 0) {
                    calculateVector.clear();
                }
            }////////end of for(try combianation)
            if(flag_canCalculate == 1) { //// start to calculate
                int input_sum = 0;
                for(int i = 0;i < calculateVector.size();i++) {
                    input_sum += tree.value[calculateVector[i]];
                }
                tree.value[neighbor_index] = calculate_ans(tree.gate[neighbor_index],input_sum,calculateVector.size());
                for(int i = 0;i < calculateVector.size();i++) {
                    degreeArray[calculateVector[i]]--;
                    int erase_index;
                    for(int j = 0;j < degreeOneVector.size();j++) {
                        if(calculateVector[i] == degreeOneVector[j]) {
                            erase_index = j;
                            degreeOneVector.erase(degreeOneVector.begin() + erase_index);
                            break;
                        }
                    }
                }
                degreeArray[neighbor_index] -= calculateVector.size();
                if(degreeArray[neighbor_index] == 1) {
                    degreeOneVector.push_back(neighbor_index);
                }
                calculateVector.clear();
            }  /////end of if flag == 1 start calculate
            
            }//// end of while(degreeOneVector.size() >0)
            
                if(tree.value[root_index] == 1) { ///// get SAT
                    outfile << "SAT" << endl;
                    int d[10];
                    for(int i = 0;i < 10;i++) {
                        d[i] = tree.degree[i];
                    }
                    for(int i = 0;i < tree.get_nodeNumber();i++) {
                        if(d[i] == 1) {
                        outfile << i << ":" << tree.value[i] << endl;
                    }
                    }
                    break;
                }

            }
            if(tree.value[root_index] == 0) {
            outfile << "UNSAT" << endl;
            }
 
        }
 
    outfile.close();
    return 0;
}