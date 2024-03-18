#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <list>
using namespace std; 

class incoming {
public:
    int index;
    int weight;
    incoming(int i,int w);
    incoming(int i);
};
incoming :: incoming(int i ,int w) {
    index = i;
    weight = w;
}
incoming :: incoming(int i) {
    index = i;
}
class outcoming {
public:
    int index;
    int weight;
    outcoming(int i,int w);
    outcoming(int i);
};
outcoming :: outcoming (int i,int w) {
    index = i;
    weight = w;
}
outcoming :: outcoming(int i) {
    index = i;
}
class vertex{
public:
    string name;
    int index;
    int type; // input,gate,output 0,1,2
    vector<incoming> incoming_neighbor;
    vector<outcoming> outcoming_neighbor;
    int ee; // earliest event time
    int le; // lastest event time
    int mark_ee; 
    int mark_le;
    int critical; 
    vertex(string n,int i);
    /// /////////// graph 
    int V;
    list<int>* neighbor;
    void printAllPathsUtil(int, int, bool[], int[], int&);
    vector <string> vertex_name;
    vertex (int num);
    void addEdge(int u,int v);
    void printAllPaths(int s,int d, vector <string> &n,ofstream &);
    ofstream *out;
};
    
vertex :: vertex(string n,int i) {
    name = n;
    index = i;
    if(n[0] == 'I') {
        type = 0; ///input
    }
    else if (n[0] == 'G') {
        type = 1; ///gate
    }
    else if (n[0] == 'O') {
        type = 2; //output
    }
    ee = 0;
    mark_ee = 0;
    mark_le = 0;
    critical = 0;
}

vertex :: vertex(int num) {
    V = num;
    neighbor = new list<int>[V];
}
void vertex::addEdge(int u, int v) {
    neighbor[u].push_back(v); 
}

void vertex::printAllPaths(int s, int d, vector <string> &n,ofstream &outfile) {
    out = &outfile;
    for(int i = 0;i < n.size();i++) {
        vertex_name.push_back(n[i]);
    }
    bool* visited = new bool[V];
    int* path = new int[V];
    int path_index = 0; 
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    printAllPathsUtil(s, d, visited, path, path_index);
}

void vertex ::printAllPathsUtil(int u, int d, bool visited[],int path[], int& path_index) {
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    if (u == d) {
        *out << endl;
        for (int i = 0; i < path_index; i++) {
            *out << vertex_name[path[i]] << " ";
        }
    }
    else { 
        list<int>::iterator i;
        for (i = neighbor[u].begin(); i != neighbor[u].end(); ++i) {
            if (!visited[*i]) {
                printAllPathsUtil(*i, d, visited, path, path_index);
            }
        }
    }
    path_index--;
    visited[u] = false;
}
 
class edge {
public:
    string name1;
    string name2;
    int index1;
    int index2;
    int weight;
    edge(string s1, string s2,int i1,int i2,int w);
    edge(string s1, string s2,int i1,int i2);
};
edge :: edge(string s1,string s2,int i1,int i2,int w) {
    name1 = s1;
    name2 = s2;
    index1 = i1;
    index2 = i2;
    weight = w;
}
edge :: edge(string s1,string s2,int i1,int i2) {
    name1 = s1;
    name2 = s2;
    index1 = i1;
    index2 = i2;
}

int main(int argc,char *argv[]) {
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    outfile.open(argv[2]);
    if(!infile){
        cout << "cannot open infile" << endl;
        return 0;
    }
    if(!outfile) {
        cout << "cannot open outfile" << endl;
    }
    string temp1,temp2;
    int weight;
    int count_edge = 0;
    int count_vertex = 0;
    vector <string> temp_vertex;
    vector <vertex> v;
    vector <edge> e;
    while(!infile.eof()) {
        infile >> temp1;
        int same = 0;
        for(int i = 0;i < v.size();i++) {
            if(temp1 == v[i].name) {
                same = 1;
                break;
            }
        }
        if(same == 0) {
            v.push_back( vertex(temp1,count_vertex));
            count_vertex++;
        }
        temp_vertex.push_back(temp1);
        same = 0;
        infile >> temp2;
        
        for(int i = 0;i < v.size();i++) {
            if(temp2 == v[i].name) {
                same = 1;
                break;
            }
        }
        if(same == 0) {
            v.push_back( vertex(temp2,count_vertex));
            count_vertex++;
        }
        temp_vertex.push_back(temp2);
        infile >> weight;
        int index1,index2;
        for(int i = 0;i < v.size();i++) {
            if(temp1 == v[i].name) {
                index1 = v[i].index;
            }
            else if(temp2 == v[i].name) {
                index2 = v[i].index;
            }
        }
        v[index1].outcoming_neighbor.push_back(outcoming(index2,weight));
        v[index2].incoming_neighbor.push_back(incoming(index1,weight)); 
        e.push_back( edge(temp1,temp2,index1,index2,weight));
        count_edge++;
    }
    infile.close();

    //////////////////////////////////////////////////////// calculate earliest event time
    stack <int> earliest;
    for(int i = 0;i < v.size();i++ ) {
        if(v[i].type == 0) { ////type = input
            earliest.push(v[i].index);
        }
    }
    
    while(!earliest.empty()) {
        int pop_index = earliest.top();
        earliest.pop();
        for(int i = 0;i < v[pop_index].outcoming_neighbor.size();i++) {
            int ee_index = v[pop_index].outcoming_neighbor[i].index;
            int ee_cal = v[pop_index].ee + v[pop_index].outcoming_neighbor[i].weight;
            if(ee_cal > v[ee_index].ee) {
                v[ee_index].ee = ee_cal;
            }
            int all_marked = 1;
            for(int j = 0;j < v[ee_index].incoming_neighbor.size();j++) {
                int ee_incoming_index = v[ee_index].incoming_neighbor[j].index;
                if(v[ee_incoming_index].mark_ee == 0) {
                    break;
                }
            }
            if(all_marked == 1 && v[ee_index].type != 2) {
                earliest.push(ee_index);
            }
        }
    }
    int max_latency = v[0].ee;
    for(int i = 0;i < v.size();i++) {
        if(v[i].ee > max_latency) {
            max_latency = v[i].ee;
        }
    }
    ///////////////////////////////////////////////////////// calculate latest event time 
    stack <int> lastest;
    for(int i = 0;i < v.size();i++) {
        v[i].le = max_latency;
        if(v[i].type == 2) {
            lastest.push(v[i].index);
        }
    }
    while(!lastest.empty()) {
        int pop_index = lastest.top();
        lastest.pop();
        for(int i = 0;i < v[pop_index].incoming_neighbor.size();i++) {
            int le_index = v[pop_index].incoming_neighbor[i].index;
            int le_cal = v[pop_index].le - v[pop_index].incoming_neighbor[i].weight;
            if(le_cal < v[le_index].le) {
                v[le_index].le = le_cal;
            }
            int all_marked = 1;
            for(int j = 0;j < v[le_index].outcoming_neighbor.size();j++) {
                int le_incoming_index = v[le_index].outcoming_neighbor[j].index;
                if(v[le_incoming_index].mark_le == 0) {
                    break;
                }
            }
            if(all_marked == 1 && v[le_index].type != 0) {
                lastest.push(le_index);
            }
        }
    }
    vector <edge> critical_edge;
    int count_critical_edge = 0;
    for(int i = 0;i < count_edge;i++) {
        outfile <<  e[i].name1 << " " << e[i].name2;
        outfile << " " << v[e[i].index1].ee << " " << v[e[i].index2].le  - e[i].weight;
        int slack = (v[e[i].index2].le  - e[i].weight) - v[e[i].index1].ee;
        outfile << " " << slack << " ";
        if(slack == 0) {
            outfile << 'Y';
            count_critical_edge++;
            critical_edge.push_back(edge(e[i].name1,e[i].name2,e[i].index1,e[i].index2));
            v[e[i].index1].critical = 1;
            v[e[i].index2].critical = 1;
        }
        else {
            outfile << 'N';
        }
        outfile << endl;
    }
    outfile << "max latency: " << max_latency << endl;

    ///////////////////////////////////////////// critical path
    outfile << "critical paths: ";
    vertex g(v.size());

    for(int i = 0;i < critical_edge.size();i++) {
        g.addEdge(critical_edge[i].index1,critical_edge[i].index2);
    }
    vector <int> source;
    vector <int> destination;
    for(int i = 0;i < v.size();i++) {
        if(v[i].type == 0) {
            source.push_back(v[i].index);
        }
        else if(v[i].type == 2) {
            destination.push_back(v[i].index);
        }
    }
    vector <string> vertex_name;
    for(int i = 0;i < v.size();i++) {
        vertex_name.push_back(v[i].name);
    }
    for(int i = 0;i < source.size();i++) {
        for(int j = 0;j < destination.size();j++) {
            g.printAllPaths(source[i],destination[j],vertex_name,outfile);
        }
    }

    outfile.close();
    return 0;
}