#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class node {
public: 
    int key;
    int index;
    node(int k,int i);
};
node :: node (int k ,int i) {
    key = k;
    index = i;
}
int main (int argc ,char *argv[]) {
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    outfile.open(argv[2]);
    vector<node> a;
    int A,B;
    int temp;
    char c;
    int index = 0;
    while(infile >> temp) {
        a.push_back(node(temp,index));
        infile.get(c);
        if(c == '\n') {
            break;
        }
        index++;
    }
    infile >> A;
    infile >> B;/*
    for(int i = 0;i < a.size();i++) {
        cout << a[i].index << " " << a[i].key << endl;
    }
    cout << A << " " << B << endl;
    cout << index << endl;*/
    infile.close();
    //////////////////////// sort
    int count = 0;
    for(int i = 0;i < a.size()+1;i++) {
        if (i + B > a.size()-1) {
            for(int j = i+1;j < a.size();j++) {
                if(a[i].key - a[j].key < A && a[i].key - a[j].key > 0 ) {
                  //  cout <<  i << " " << j << endl;
                    count++;
                }
                else if (a[i].key - a[j].key < 0 && -(a[i].key - a[j].key) < A) {
                    //cout <<  i << " " << j << endl;
                    count++;
                }
            }
        }
        else {
            for(int j = i+1;j < i + B + 1;j++) {
                if(a[i].key - a[j].key < A && a[i].key - a[j].key > 0 ) {
                    //cout <<  i << " " << j << endl;
                    count++;
                }
                else if (a[i].key - a[j].key < 0 && -(a[i].key - a[j].key) < A) {
                    //cout <<  i << " " << j << endl;
                    count++;
                }
            }
        }
    }
    //cout << count << endl;
    outfile << count;
    outfile.close();
    return 0;
}