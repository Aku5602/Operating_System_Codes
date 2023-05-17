//Disk Scheduling ==> FCFS && SSTF
#include <bits/stdc++.h>
using namespace std;


class Disk_Scheduling{
  public:
    int headcounts;
    int no_cylinders;
    int no_req;
    int head_pos;
    vector <int> req;
    map <int,int> flag;
    
    Disk_Scheduling(int no_req,int no_cylinders) {
      this -> no_req =no_req;
      this -> no_cylinders = no_cylinders;
      cout<<"Enter head position: "<<endl;
      cin>>head_pos;

      cout<<"Enter all requests:"<<endl;
      for(int i=0;i<no_req;i++) {
        int value;
        cin>>value;
        req.push_back(value);  
        flag[i] = -1;
      }

    }

    void FCFS() {

      int curr_head = head_pos;
      headcounts=0;

      for(int i=0;i<no_req;i++) {
        headcounts += abs(curr_head - req[i]);
        curr_head = req[i];
      }
      
    }

    void SSTF() {

      int curr_head = head_pos;
      headcounts=0;
      
      int min_index=-1;
      for(int i=0;i<no_req;i++) {
        if(flag[i] < 1 && (min_index == -1 || abs(curr_head - req[i]) < req[min_index])) {
          min_index = i;
          //cout<<i<<endl;
        }
      
      }

      if(min_index > -1){
        headcounts += abs(curr_head - req[min_index]);
        curr_head = req[min_index];
        flag[min_index] = 1;
         //cout<<headcounts<<endl;
      }
      
     
      
      cout<<"Total headcounts = "<<headcounts<<endl;
    }
   

};

int main() {
  Disk_Scheduling d(5,200);
  d.FCFS();
  d.SSTF();
  
  return 0;
}