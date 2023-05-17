

#include <bits/stdc++.h>
using namespace std;

class ContiguousMemoryAlloc {
  public:
    int no_process;
    int no_holes;
  
    vector <int> process_sizes;
    vector <int> hole_sizes;

    vector <int> process_alloc;
    vector <int> hole_alloc;

    ContiguousMemoryAlloc(int no_process,int no_holes) {
      this -> no_process = no_process;
      this -> no_holes = no_holes;
    }

    void input() {
      cout<<"\nEnter size of all processes:"<<endl;
      for(int i=0;i<no_process;i++) {
        int value;
        cin>>value;
        process_sizes.push_back(value);
        process_alloc.push_back(-1); 
      }
      cout<<"\nEnter size of all holes:"<<endl;
      for(int i=0;i<no_holes;i++) {
        int value;
        cin>>value;
        hole_sizes.push_back(value);
        hole_alloc.push_back(-1); 
      }
    }
    
    void init() {
      for(int i=0;i<no_process;i++) {
        process_alloc[i]=-1; 
      }
      for(int i=0;i<no_holes;i++) {
        hole_alloc[i]=-1; 
      }
    }

    int FirstFit() {
      for(int i=0;i<no_process;i++) {
        for(int j=0;j<no_holes;j++) {
          if(hole_sizes[j] >= process_sizes[i] && hole_alloc[j] < 0) {
            process_alloc[i] = j;
            hole_alloc[j] = i;
            
            break;
          }
        }
      }

      for(int i=0;i<no_process;i++) {
        if(process_alloc[i] < 0) return 0;
      }
      
      return 1;
    }
    
    int NextFit() {
      
      int j=0;
      int flag=1;
      for(int i=0;i<no_process;i++) {
        int count = no_holes;
        while(j<no_holes) {
          count--;
          if(hole_sizes[j] >= process_sizes[i] && hole_alloc[j] < 0) {
            process_alloc[i] = j;
            hole_alloc[j] = i;
            break;
          }
          if(j==no_holes-1) {
            j=0;
          }
          if(count<1) {
            break;
            flag=0;
          }
          j++;
        }
        
      }
      if(flag == 0) return 0;
      
      return 1;
    }
    
    void display() {
      for(int i=0;i<no_process;i++) {
        cout<<i<<"=>"<<process_sizes[i]<<" "<<process_alloc[i]<<" "<<hole_sizes[process_alloc[i]]<<endl;
      }
    }
    
   int BestFit() {
      int flag = 1;
      for(int i=0;i<no_process;i++) {
        int min_hole_size = 1000;
        int min_hole_index = -1;
        for(int j=0;j<no_holes;j++) {
          if(hole_alloc[j] < 0 && min_hole_size > hole_sizes[j] && hole_sizes[j] >= process_sizes[i]) {
            min_hole_size = hole_sizes[j];
            min_hole_index = j;
          }
        }

        if(min_hole_index < 0) {
          flag = 0;
          continue;
        }
        else {
          process_alloc[i] = min_hole_index;
          hole_alloc[min_hole_index] = i;
        }
      }

      if(flag ==0 ) {
        return 0;
      }
      return 1;
   }

   int WorstFit() {
      int flag = 1;
      for(int i=0;i<no_process;i++) {
        int min_hole_size = -1;
        int min_hole_index = -1;
        for(int j=0;j<no_holes;j++) {
          if(hole_alloc[j] < 0 && min_hole_size < hole_sizes[j] && hole_sizes[j] >= process_sizes[i]) {
            min_hole_size = hole_sizes[j];
            min_hole_index = j;
          }
        }

        if(min_hole_index < 0) {
          flag = 0;
          continue;
        }
        else {
          process_alloc[i] = min_hole_index;
          hole_alloc[min_hole_index] = i;
        }
      }

      if(flag ==0 ) {
        return 0;
      }
      return 1;
   }


};

int main() {
  //First Fit,Next Fit, Best Fit and Worst Fit
  //Input: Process and its sizes, Memory Holes and its sizes.
  ContiguousMemoryAlloc cm(4,5);
  
  cm.input();
  //cm.FirstFit();
  //cm.display();
  //cm.init();
  cm.BestFit();
  cm.display();
  cm.init();
  cm.WorstFit();
  cout<<endl;
  cm.display();
  
  
  return 0;
}