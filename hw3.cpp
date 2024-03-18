#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
   
class Node {
public :
    friend class List;
    string data;
    Node *next;
    int cross; //// cross = 1 (marked)
   Node(string a) {
    data = a;
   }
};
class List{
public:
    Node *head;
    Node *current;
    Node *comHead;////////// the combination head node of every stage

    List() {
        head = NULL;
        current = NULL;
        comHead = NULL;
    }
    void addNode(string a); 
   // void deleteNode(Node *deNode);
  //  void traverse(ostream &out);


};
void List :: addNode(string a) { 
   Node *add = new Node(a);
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


///////////////////////// QM function

int compare(string &a,string &b,int size) { //// determine two sting whether can merge.
    int canMerge = 0;
    int different = 0;
    for(int i = 0;i < size;i++) {
        if(a[i] != b[i]) 
            different++;
    }
    if(different == 1)
            canMerge = 1;
    return  canMerge;
}

string Merge(string &a,string &b, int size) { //// merge two strings.
    string c; 
    for(int i = 0;i < size;i++) {
        if(a[i] != b[i]) 
            c += '-';
        else    
            c += a[i];
    }
    return c;
}


int stringsame(string &a, Node *p) { //// ensure the merge string is different from the string existed in the list.
    int same = 0;
    while(p != NULL) {
        if (a == p->data) {
            same = 1;
            break;
        }
        p = p->next;
    }
    return same;

}

int countminus(string a) {
      int m = 0;
      for(int i = 0;i < a.size();i++) {
        if(a[i] == '-'){
          m++;
	}
      }
      return m;
}

/////////////////////////////////////////
int main(int argc, char  *argv[]) {
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    outfile.open(argv[2]);
    if(!infile) {
     //   cout << "cannnot open infile" << endl;
        return 0;
    }
    if(!outfile) {
     //   cout << "cannot open outfile" << endl;
        return 0;
    }
    ///////////////////////////////////read infile
    
    int variable;
    string temp;
    int dec;
    int count = 0;////count how many '1' in binary 
    infile >> variable;
    getline(infile,temp);
    //outfile << variable << endl;
 
   List list[17];
   List LL;
    while(infile >> dec) {
        count = 0;
     //   outfile << dec << endl;
        int a[variable];
        for(int i = 0;i < variable;i++) { /// decimal to binary
            a[variable-1-i] = dec % 2;
            dec /= 2;
        }
        for(int i = 0;i < variable;i++) {
            if(a[i] == 1)
                count++;
        } 
        string n;
        for(int i = 0;i < variable ;i++) {
            n += a[i] + '0';
        }
        list[count].addNode(n);
     
        char c;
        infile.get(c);
        if(c == '\n')
            break;
    }
    infile.close();
    ////////////////////////////// infile close

    int flag = 0;
    outfile << "Initial Grouping" << endl;
    for(int i = 0;i < variable+1;i++) {
        outfile << i << ": ";
        Node *print = list[i].head;
        int countprint = 0;
        while(print != NULL) {
            if(countprint == 0){
                outfile << print->data;
                flag++;
            }
            else {   
                outfile << ", " << print->data;
                flag++;
            }
            print = print->next;
            countprint++; 
        }
        outfile << endl;
    }
    ////////////////////////// QM
    List PrimeList;
    Node *p1,*p2; /////// use to traverse
    Node *com; ////// record the first add node position in every combination.
    Node *head1,*head2; ///// the first node need to traverse of every stage.
    int canMerge = 0;
    int same = 0;
    int countAdd = 0;
    bool print_comb = 0;

    for(int i = 0;i < variable-2;i++) { /////// combination 1 to variable -2 
     //   cout << " combination========" << i + 1 << endl;

        for(int j = 0;j < variable - i;j++) {

            countAdd = 0;
            /////////////////// initialize pointer
            if(i == 0) { ////// pointer initialize : combination 1
                p1 = list[j].head;
                p2 = list[j+1].head;
                head2 = list[j+1].head;
            }
            else { ////// pointer initialize : combination 2 to variable -2 
                p1 = list[j].comHead;
                p2 = list[j+1].comHead;
                head2 = list[j+1].comHead;
            }
            
            ////////////////////////// start to compare and merge and delete
            while(p1 != NULL) {
                while(p2 != NULL) {
                    canMerge = 0;
                    canMerge = compare(p1->data,p2->data,variable);
                    if(canMerge == 1) {
                        p1->cross = 1;
                        p2->cross = 1;
                        string mergeString = Merge(p1->data,p2->data,variable);
                        if(countAdd >= 1) {
                            same = stringsame(mergeString,list[j].comHead);
                            if(same == 0) { ////different
                                list[j].addNode(mergeString);
                                countAdd++;
                            }   
                        }
                        if(countAdd == 0) {
                            list[j].addNode(mergeString);
                            countAdd++;
                            list[j].comHead = list[j].current; ////// update list[j] combination head 
                        }
                    }
                    p2 = p2 -> next;
                }
                p1 = p1 -> next;
                if(p1 == list[j].comHead)
                    break;
                p2 = head2;
            }
        }
        list[variable-i].comHead = NULL;
        if(flag<=1) break;
        flag = 0;
        //////////////// print the result of the combination
        outfile << "Combination " << i+1 << endl;
        if(!print_comb){
        for(int k = 0;k < variable-i;k++) {
            int countprint = 0;
            outfile << k <<": ";
            Node *print = list[k].comHead;
            while(print != NULL) {
                  if(countprint == 0 && countminus(print->data) == i + 1){
                    outfile << print->data;
                    flag++;
                  }
                  else if(countminus(print->data) == i + 1){
                    outfile << "," << print->data;
                    flag++;
                  }
                  print = print->next;
                  countprint++;
            }
            outfile << endl;

        }
        }
        if(flag<=1) print_comb=1;
    }
 
/////////////////////////////////////////
    outfile << "Prime implicants" << endl;

    Node *ptr = NULL;
    int minus = 0;
    int countnode = 0;
    for(int i = 0;i < variable -1;i++) {
	for(int j = 0;j < variable+1;j++) {
	   ptr = list[j].head;
           while(ptr != NULL) {
             minus = countminus(ptr->data);
           //  cout<<ptr->data << " ";
             if(ptr->cross == 0 && minus == i) {
                if(countnode == 0)
                    outfile << ptr->data ;
                else
                    outfile << ", "<< ptr->data;
                countnode++;
             }
             ptr = ptr->next;
           }

        }
    }
    outfile.close();
    return 0;
}