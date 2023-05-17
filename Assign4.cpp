#include <bits/stdc++.h> 
using namespace std;


class Process {  
  public:
    int pid;
    int AT;
    int BT;
    int ST;
    int WT;
    int FT;
    int TAT;
    int RBT;
    int included;
    int qmap;
};


class Round_Robin {
//Round Robin Process Scheduling Algorithm
  public:
  int time_quantum;
  int no_process;
  queue <int> q;
  int AWT,ATAT;
  vector <Process> ans;
  Process processes[20];

  Round_Robin(int no_process,int tq) {
    this->no_process = no_process;
    time_quantum = tq;
    AWT = ATAT = 0;
  }
  
  void input() {
    cout<<"\n Enter pid, AT, BT of all processes:\n";
    for(int i=0;i<no_process;i++) {
      Process p;
      int value;
      cin>>value;
      p.pid=value;
      cin>>value;
      p.AT=value;
      cin>>value;
      p.BT=value;
      p.RBT= value;
      p.ST = p.FT = p.WT = p.TAT = p.included = p.qmap = 0;
      processes[i]=p;
    }
  }


  static int comparator(Process p1,Process p2) {
    return p1.AT < p2.AT;
  }
  
  void execute() {
    sort(processes,processes+no_process,comparator);
    int flag=0;
    int index = 0;
    q.push(0);
    processes[0].qmap = 1;
  
    while(flag < 1) {
      int CT=time_quantum;
      
      if(processes[index].RBT < CT) {
        CT = processes[index].RBT;
      }

      for(int i=0;i<no_process;i++) {
        if(processes[i].included < 1 && processes[i].AT <= processes[index].ST + CT && processes[i].qmap < 1) {
          q.push(i);
          processes[i].qmap = 1;
        }
      }
      
      processes[index].RBT -= CT; 
   
      processes[index].FT = processes[index].ST + CT;
      processes[index].TAT = processes[index].FT - processes[index].AT;
      processes[index].WT = processes[index].TAT - processes[index].BT + processes[index].RBT;

      if(processes[index].RBT <= 0) {
         processes[index].included = 1;
      }
      else {
         q.push(index);
      }
      
      ans.push_back(processes[index]);
      q.pop();
      
      if(!q.empty()) {
        int nextIndex = q.front();
        processes[nextIndex].ST = processes[index].FT;
        index = nextIndex;
      }

      for(int i=0;i<no_process;i++) {
        if(processes[i].included < 1) { 
          flag=0;
          break;
        }
        else {
          flag = 1;
        }
      }
      
      
    }
  }

  void display() {
    cout<<endl<<"pid  AT  BT  ST  FT  WT  TAT"<<endl;
    for(int i=0;i<no_process;i++) {
      cout<<"  "<<processes[i].pid<<"   "<<processes[i].AT<<"  "<<processes[i].BT<<"  "<<processes[i].ST<<"  "<<processes[i].FT<<"  "<<processes[i].WT<<"  "<<processes[i].TAT<<"  "<<endl;
      AWT += processes[i].WT;
      ATAT += processes[i].TAT;
    }
    
    for(int i=0;i<ans.size();i++) {
      cout<<"---- ";
    }
    cout<<endl;
    for(int i=0;i<ans.size();i++) {
      cout<<"  "<<ans[i].pid<<"  ";
    }
    cout<<endl;
    cout<<0;
    for(int i=0;i<ans.size();i++) {
      cout<<"---"<<ans[i].FT<<" ";
    }

    cout<<"\n Average Waiting Time: "<<1.0 * AWT/no_process<<endl;
    cout<<"\n Average TurnAround Time: "<<1.0 * ATAT/no_process<<endl;
  }
  
};

int main() {
  
  Round_Robin r(4,2);
  r.input();
  r.execute();
  r.display();
  return 0;
}