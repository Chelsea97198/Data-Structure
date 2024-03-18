#include <iostream>
#include <fstream>
using namespace std;
#define HT  100000
class Node {
public :
    friend class List;
    int value;
    int index;
   // int ht_index;
    Node *next;
    Node(int v,int ii) {
        value = v;
        index = ii;
    }
};
class List {
public:
    Node *head;
    Node *current;
    List() {
        head = NULL;
        current = NULL;
    }
    void addNode(int value,int index);
};
void List :: addNode(int value,int ii) {
    Node *add = new Node(value,ii);
    if(head == NULL) {
        head = add;
        add->next = NULL;
    }
    else {
        current->next = add;
        add->next = NULL;
    }
    current = add;
}
int hash(int input) {
    int tableIndex;
    if(input >= 0) {
        tableIndex = input % HT;
    }
    else {
        tableIndex = (-input) % HT;
    }
    return tableIndex;
}
int main(int argc ,char *argv[]) {
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);
    int sum;
    infile >> sum;
    int input;
    List inputArray;
    int count = 0;
    while(infile >> input ) {
        inputArray.addNode(input,count);
        count++;

    }
    infile.close();
    List hashTable[HT];
    int temp;
    for(Node *ptr = inputArray.head;ptr != NULL;ptr = ptr->next) {
        temp = hash(ptr->value);
        hashTable[temp].addNode(ptr->value,ptr->index);
    }
    int find = 0;
    int target;
    int ht_index;
    for(Node *ptr = inputArray.head;ptr!= NULL;ptr = ptr->next) {
        find = 0;
        target = sum - ptr->value;
        ht_index = hash(target);
      //  outfile << ptr->value << " " <<  target << " "<< ht_index << endl;
        for(Node *ptr_ht = hashTable[ht_index].head;ptr_ht != NULL;ptr_ht = ptr_ht->next) {
            if(ptr_ht->value == target && ptr_ht->index != ptr->index) {
                outfile << ptr->index << endl;
                outfile << ptr_ht->index;
                find = 1;
                break;
            }
        }
        if(find == 1) {
            break;
        }
    }/*
    if(find == 0) {
        outfile << "cannot find pairs";
    }*/
    outfile.close();
    return 0;
}