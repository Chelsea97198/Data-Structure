#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
//#include "poly.h"
using namespace std;
int main(int argc,char *argv[]) {
    vector<int> temp;
    vector<int> polyA;
    vector<int> polyB;
    vector<int> polyQ;
    vector<int> polyR;
    int coef;
    ifstream infile;
    ofstream outfile;

    infile.open(argv[1]);
    outfile.open(argv[2]);
    if(!infile) {
 //       cout << "can't open infile\n";
        return 0;
    }
    if(!outfile) {
 //       cout << "can't open outfile\n";
        return 0;
    }
    int Asize = 0;
    
    char c;
    while(!infile.eof()) {
        infile >> coef;
        temp.push_back(coef);
        infile.get(c);
        if(c == '\n'){
            Asize = temp.size();
        //    cout<<"Asize: "<<Asize<<endl;
            c = 'a';        
        }
    }
    infile.close();
//////////////////////////////////////////////////////
    for(int i = 0;i < Asize;i++){
        polyA.push_back(temp[Asize-1-i]);
    }
    for(int i = 0;i < temp.size()-Asize;i++) {
        polyB.push_back(temp[temp.size()-1-i]);
    }
   /* cout << "temp : ";
    for(int i = 0;i < temp.size();i++) {
        cout << temp[i] << " ";
    }
    cout << endl << polyA.size() << endl;
    cout << "polyA : ";
    for(int i = 0;i < polyA.size();i++) {
        cout <<  polyA[i] << " ";
    }
    cout << endl << polyB.size() << endl;
    cout << "polyB : ";
    for(int i = 0;i < polyB.size();i++) {
       cout <<  polyB[i] << " ";
    }
    cout << endl;*/
    ///////////////////calculate
    int moveB;
    int quotient;
  //  vector<int> polyMinus;
    while(polyA.size() >= polyB.size()) {
        moveB = polyA.size() - polyB.size();
        for(int i = 0;i < moveB;i++) {
            polyB.insert(polyB.begin(),0);
        }
 /*       cout << "polyB : ";
        for(int i = 0;i < polyB.size();i++) {
            cout << polyB[i] << " ";
        }
        cout << endl;
 */     polyQ.push_back(polyA[polyA.size()-1]/polyB[polyB.size()-1]);
        quotient = polyA[polyA.size()-1]/polyB[polyB.size()-1];

        for(int i = 0;i < polyA.size() ;i++) {
            polyA[polyA.size()-1-i] = polyA[polyA.size()-1-i] - quotient * polyB[polyB.size()-1-i]; 
        }
/*      cout << "polyA-minus(1) : " ;
        for(int i = 0;i < polyA.size();i++)
            cout << polyA[i] << " ";
        cout << endl;*/
        int count = 0;
        int AminusSize = polyA.size();
        polyA.pop_back();
/*        cout << "polyA-minus(popback)";
        for(int i = 0;i < polyA.size();i++) {
            cout  << polyA[i] << " "; 
        }
        cout << endl;*/
        for(int i = 0;i < moveB;i++)
            polyB.erase(polyB.begin());
        
    }
    ///
    for(int i = 0;i < polyA.size();i++) {
        polyR.push_back(polyA[polyA.size()-1-i]);
    }
    //cout << "\nquotient : ";
    for(int i = 0;i < polyQ.size();i++) {
      //  cout << polyQ[i] << " ";
        outfile << polyQ[i] << " ";
    }
    outfile << '\n';
   // cout << "remainder : ";
    for(int i = 0;i < polyR.size();i++) {
     //   cout << polyR[i] << " ";
        outfile << polyR[i] << " ";
    }
    if(polyR.size() == 0) {
      //  cout << 0;
        outfile << 0;
    }
   
    return 0;
}
