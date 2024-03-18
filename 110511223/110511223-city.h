#include <iostream>
using namespace std;
#include <string>
#include <vector>
class City {
public:
    City(int i,string n,int v) {
        index = i;
        name = n;
        visit = v;
    }
    int index;
    string name;
    int visit;
    vector <int> neighbor;

};