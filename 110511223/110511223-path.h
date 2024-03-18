#include <iostream>
using namespace std;
class Path {
public:
    Path(int s,int des,int dis) {
        source = s;
        destination = des;
        distance = dis;
    }
    int source;
    int destination;
    int distance;
};