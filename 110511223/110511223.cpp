#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include "110511223-city.h"
#include "110511223-path.h"
using namespace std;

int main(int argc , char *argv[]) {
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    outfile.open(argv[2]);
    if(!infile) {
    //    cout << "cannot open infile" << endl;
        return 0;
    }
    if(!outfile) {
     //   cout << "cannot open outfile" << endl;
        return 0;
    }
    ////////////////////////////////////////// infile
    int city_num;
    vector <City> city;
    string temp;
    infile >> city_num;
 //   cout << city_num << endl;
    getline(infile,temp);
    for(int i = 0;i < city_num;i++) {
        getline(infile,temp);
        City city_temp(i,temp,0);
        city.push_back(city_temp);
   //     cout << city[i].index << " : " << city[i].name << " vistit : " << city[i].visit << endl;
    }
    int path_num;
    infile >> path_num;
  //  cout << path_num << endl;
    vector <Path> path;
    int temp_source;
    int temp_desCity;
    int temp_distance;
    for(int i = 0;i < path_num;i++) {
        infile >> temp_source;
        infile >> temp_desCity;
        infile >> temp_distance;
        Path path_temp(temp_source,temp_desCity,temp_distance);
        path.push_back(path_temp);
      //  cout << path[i].source << " " << path[i].destination << " " << path[i].distance << endl;
        getline(infile,temp);

    }
    string target;
    int target_index = -1; 
    getline(infile,target);
    for(int i = 0;i < city_num;i++) {
        if(city[i].name == target) {
            target_index = i;
            break;
        }
    }
  //  cout << target << endl;
  //  cout << target_index << endl;
  //  cout << "///////////////////////" << endl;
    infile.close();
    ///////////////////////////////////////////////////////////////// DFS
    stack <int> stack;
    vector <int> traverse;
    int v;
    int neighbor_num;
    int neighbor_index;
    if(target_index == -1) { ///////// city doesn't exsist
     //   cout << "the target city doesn't exsist" << endl;
      //  return 0;
    }
    stack.push(0);
    outfile << "push " << 0 << endl;
    
    while(stack.top() != target_index) {
        v= stack.top();
   //     cout << "v : " << v << endl;
      /*  if(stack.empty()) { ///////////// cannot find route
            cout << "stack is empty /path not found" << endl;
            outfile << "-1" ;
            break;
        }*/
        stack.pop();
        outfile << "pop " << v << endl;
        if(city[v].visit == 0) {
            traverse.push_back(v);
            city[v].visit = 1;
            neighbor_num = 0;
            for(int i = 0;i < path_num;i++) { ////////find neighbor 
                if( path[i].source == v) { 
                    neighbor_num++;
                    neighbor_index = path[i].destination;
               //     cout << "visit : " << v << " back_neighbor : " << neighbor_index << endl;
                    city[v].neighbor.push_back(neighbor_index);
                    if(city[neighbor_index].visit == 0) {
                        stack.push(neighbor_index);
                        outfile << "push " << neighbor_index << endl;
                    }
                }
                if(path[i].destination == v) {
                    neighbor_num++;
                    neighbor_index = path[i].source;
               //     cout << "visit : " << v << " front_neighbor : " << neighbor_index << endl;
                    city[v].neighbor.push_back(neighbor_index);
                    if(city[neighbor_index].visit == 0) {
                        stack.push(neighbor_index);
                        outfile << "push " << neighbor_index << endl;
                    }
                }
            }
        //    cout << v << "'s neighbor : ";
            for(int i = 0;i < neighbor_num;i++) {
        //        cout << city[v].neighbor[i] << " ";
            }
         //   cout << endl;
        }
        if(stack.empty()) ////////////////!!!!!!!!
            break;
        
    }
 //   cout << "get out " << endl;
    if(stack.empty()) {
   //     cout << "cannot find route" << endl;
        outfile << -1;
        return 0;
    }
    if(target_index == stack.top()) { ////////// can find route
      //  cout << "find target : " << target_index << endl;
        int sum = 0;
        int backtrack;
        for(int i = 0;i < path.size();i++) { /////// calculate first backtrack distance
            if(path[i].destination == target_index) {
                backtrack = path[i].source;
                sum += path[i].distance;
             //   cout << "distance : " << path[i].distance << " sum : " << sum << endl;
             //   cout << "backtrack : " << backtrack << endl;
                break;
            }
        }
        
        while(backtrack != 0) { //////// calculate left backtrack distance
            for(int i = 0;i < path.size();i++) {
                if(path[i].destination == backtrack) {
                    backtrack = path[i].source;
                    sum += path[i].distance;
                  //  cout << "distance : " << path[i].distance << " sum : " << sum << endl;
                  //  cout << "backtrack : " << backtrack << endl;
                }
             }
        }

  //      cout << "total distance " << sum <<endl;
        outfile << sum;
    }

  //  cout << "traverse : ";
  //  for(int i = 0;i < traverse.size();i++) {
      //  cout << traverse[i] << " ";
 //   }
  //  cout << endl;
   

   


    //////////////////////////////////////////////////////////////// outfile check
   /* outfile << city_num << endl;
    for(int i = 0;i < city_num;i++) {
       // outfile << i << " : " << city[i] <<  endl;
       outfile << city[i].index << " : " << city[i].name << " visit : " << city[i].visit << endl;
    }
    outfile << path_num << endl;
    for(int i = 0;i < path_num;i++) {
     //   outfile << sourceCity[i] << " " << desCity[i] << " " << Distance[i] << endl;
        outfile << path[i].source << " " << path[i].destination << " " << path[i].distance << endl;
    }
    outfile << target << endl;
    outfile << target_index << endl;
    */
    city.clear();
    path.clear();
    traverse.clear();
    while(!stack.empty())
        stack.pop();
    outfile.close();

    return 0;
}