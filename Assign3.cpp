 /*
  FCFS => Non-Preemptive
  SJF => Non-Preemptive and Preemptive
  Priority => Non-Preemptive and Preemptive

  Input: pid, AT, BT

  ST, FT, WT, TAT
  AWT, ATAT

  Output: pid, AT, BT, ST, FT, WT, TAT
  AWT   ATAT  
*/

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
};

class Process_Scheduling {
  public:
    int no_process;
    Process processes[20];
    vector <Process> AnsSJF;
    vector <Process> Preemptive_SJF;
    queue <Process> Round_Robin;

    float AWT=0;
    float ATAT=0;

  Process_Scheduling(int no_process) {
    this->no_process = no_process; 
  }

  void input() {
    cout<<"\n Enter pid,AT,BT of all processes:\n";
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
      processes[i]=p;
      
    }
    sort(processes,processes + no_process,SortProc);
  }

 void init() {
    for(int i=0;i<no_process;i++) {
      processes[i].ST = processes[i].FT = processes[i].WT = processes[i].TAT = processes[i].included = 0;
      processes[i].RBT = processes[i].BT;
      AWT = ATAT = 0;
    }
 }

 static int SortProc(Process a,Process b){
   return a.AT < b.AT;
 }

  void FCFS() {
    //Non-Preemptive
    processes[0].ST=0;
    for(int i=0;i<no_process;i++) {
      processes[i].FT = processes[i].ST + processes[i].BT; 
      processes[i].TAT = processes[i].FT - processes[i].AT;
      processes[i].WT = processes[i].TAT - processes[i].BT;
      AWT += processes[i].WT;
      ATAT += processes[i].TAT;

      if(i<no_process-1) {
        processes[i+1].ST = processes[i].FT;
      }
    }
  }

  void SJF_NonPreemptive() {
    processes[0].ST=0;
    int flag=0;
    int index=0;
    while(flag!=1) {

      processes[index].FT = processes[index].ST + processes[index].BT; 
      processes[index].TAT = processes[index].FT - processes[index].AT;
      processes[index].WT = processes[index].TAT - processes[index].BT;
      AWT += processes[index].WT;
      ATAT += processes[index].TAT;
      processes[index].included=1;
      
      AnsSJF.push_back(processes[index]);
      
      int min_burst=100;
      int min_index=index;
      for(int i=0;i<no_process;i++) {
        if(processes[i].included < 1 && processes[i].BT < min_burst && processes[i].AT <= processes[index].FT) {
          flag=0;
          min_burst = processes[i].BT;
          min_index = i; 
        }
      }//end of for

      for(int i=0;i<no_process;i++) {
        if(processes[i].included==0) {
          flag=0;
          break;
        }
        else {
          flag=1;
        }
      }
      
      if(flag < 1) {
        processes[min_index].ST = processes[index].FT;
        index = min_index;
      }
      
    }
  }

  void SJF_Preemptive() {
    int flag=0;
    processes[0].ST = 0;
    int index=0;
    while(flag < 1) {
      int min_index=index;
      int min_burst=processes[index].BT;
      int CT=processes[index].RBT;
      for(int i=0;i<no_process;i++) {
        if(processes[i].included < 1 && processes[i].AT <= processes[index].ST + processes[index].RBT && processes[i].RBT < min_burst) {
          min_burst = processes[i].RBT;
          min_index = i;
          break;
        }
      }

      if(min_index!=index) {
        CT = processes[min_index].AT - processes[index].ST;
      }
  
      processes[index].RBT = processes[index].RBT - CT;
      
      cout<<processes[index].pid<<endl;
      processes[index].FT = processes[index].ST + CT;
      processes[index].TAT = processes[index].FT - processes[index].AT;
      processes[index].WT = processes[index].TAT - processes[index].BT + processes[index].RBT;

      Preemptive_SJF.push_back(processes[index]);
      
      if(processes[index].RBT <=0) {
        processes[index].included = 1;
      }
      
      int minimum_burst = 100;
      int nextIndex=index;
      for(int i=0;i<no_process;i++){
        if(processes[i].included < 1 && processes[i].AT <= processes[index].FT &&  processes[i].RBT < minimum_burst) {
          minimum_burst = processes[i].RBT;
          nextIndex = i;
        }
      }
     
      if(nextIndex!=index) {
        processes[nextIndex].ST = processes[index].FT;
        index=nextIndex;
       
      }

      for(int i=0;i<no_process;i++) {
        if(processes[i].included < 1) {
          flag = 0;
          break;
        }
        else {
          flag=1;
        }
      }
      
    }
  }

  void display() {
    cout<<endl<<"pid  AT  BT  ST  FT  WT  TAT"<<endl;
    for(int i=0;i<no_process;i++) {
      cout<<" "<<processes[i].pid<<" "<<processes[i].AT<<" "<<processes[i].BT<<" "<<processes[i].ST<<" "<<processes[i].FT<<" "<<processes[i].WT<<" "<<processes[i].TAT<<" "<<endl;
    }
    for(int i=0;i<no_process;i++) {
      cout<<"---- ";
    }
    cout<<endl;
    for(int i=0;i<no_process;i++) {
      cout<<"  "<<processes[i].pid<<"  ";
    }
    cout<<endl;
    cout<<0;
    for(int i=0;i<no_process;i++) {
      cout<<"---"<<processes[i].FT<<" ";
    }

    cout<<"\n Average Waiting Time: "<<1.0 * AWT/no_process<<endl;
    cout<<"\n Average TurnAround Time: "<<1.0 * ATAT/no_process<<endl;

  }

  void displaySJF() {
    cout<<endl<<"pid  AT  BT  ST  FT  WT  TAT"<<endl;
    for(int i=0;i<AnsSJF.size();i++) {
      cout<<"  "<<AnsSJF[i].pid<<"   "<<AnsSJF[i].AT<<"  "<<AnsSJF[i].BT<<"  "<<AnsSJF[i].ST<<" "<<AnsSJF[i].FT<<"  "<<AnsSJF[i].WT<<"  "<<AnsSJF[i].TAT<<"  "<<endl;
    }
    for(int i=0;i<AnsSJF.size();i++) {
      cout<<"---- ";
    }
    cout<<endl;
    for(int i=0;i<AnsSJF.size();i++) {
      cout<<"  "<<AnsSJF[i].pid<<"  ";
    }
    cout<<endl;
    cout<<0;
    for(int i=0;i<AnsSJF.size();i++) {
      cout<<"---"<<AnsSJF[i].FT<<" ";
    }

    cout<<"\n Average Waiting Time: "<<1.0 * AWT/no_process<<endl;
    cout<<"\n Average TurnAround Time: "<<1.0 * ATAT/no_process<<endl;

  }
  
void displaySJFPreemptive() {
    cout<<endl<<"pid  AT  BT  ST  FT  WT  TAT"<<endl;
    for(int i=0;i<Preemptive_SJF.size();i++) {
      cout<<"  "<<Preemptive_SJF[i].pid<<"   "<<Preemptive_SJF[i].AT<<"  "<<Preemptive_SJF[i].BT<<"  "<<Preemptive_SJF[i].ST<<"  "<<Preemptive_SJF[i].FT<<"  "<<Preemptive_SJF[i].WT<<"  "<<Preemptive_SJF[i].TAT<<"  "<<endl;
      
    }
    
    for(int i=0;i<no_process;i++) {
      AWT += processes[i].WT;
      ATAT += processes[i].TAT;
    }
    
    for(int i=0;i<Preemptive_SJF.size();i++) {
      cout<<"---- ";
    }
    cout<<endl;
    for(int i=0;i<Preemptive_SJF.size();i++) {
      cout<<"  "<<Preemptive_SJF[i].pid<<"  ";
    }
    cout<<endl;
    cout<<0;
    for(int i=0;i<Preemptive_SJF.size();i++) {
      cout<<"---"<<Preemptive_SJF[i].FT<<" ";
    }

    cout<<"\n Average Waiting Time: "<<1.0 * AWT/no_process<<endl;
    cout<<"\n Average TurnAround Time: "<<1.0 * ATAT/no_process<<endl;

  }
  

};//end of class

int main() {
  int no_process;
  cout<<"\nEnter number of processes: ";
  cin>>no_process;

  Process_Scheduling p(no_process);
  p.input();
  /*p.FCFS();
  p.display();/*
  /*cout<<"\nSJF Non_Preemptive\n";
  p.init();
  p.SJF_NonPreemptive();
  p.displaySJF();*/
  cout<<"\nSJF Preemptive\n";
  //p.init();
  p.SJF_Preemptive();
  p.displaySJFPreemptive();
  

  

  return 0;
}

