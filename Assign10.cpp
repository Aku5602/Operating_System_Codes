
/*LRU and Optimal Page Replacement Algorithms
Input: Free_frames ( no_frames ), Processes ( no_process ) , FrameString
Middle: Page Table=> process_no =>[min_index/max_index , val/invalid bit]
Output: Frames changing only and page faults. */

#include <bits/stdc++.h>
using namespace std;

class Page_Replacement{
  public:
  int no_frames;
  int no_pages;
  vector <int> frames;
  string frameString;
  map <int,int[2]> pageTable;
  
  Page_Replacement(int no_pages, int no_frames){
     this->no_pages = no_pages;
     this->no_frames = no_frames;
     for(int i=0;i<no_pages;i++) {
       pageTable[i][0] = -1;
       pageTable[i][1] = 0;
     }
     for(int i=0;i<no_frames;i++) {
       frames.push_back(-1);

     }
  }
  
  void init() {
     for(int i=0;i<no_pages;i++) {
       pageTable[i][0] = -1;
       pageTable[i][1] = 0;
     }
     for(int i=0;i<no_frames;i++) {
       frames[i] = -1;

     }
  }

  void input() {
    cin>>frameString;
  }

  void LRU() {
    for(int i=0;i<frameString.size();i++) {
      int no=frameString[i] - 48;
      pageTable[no][0] = i;

      if(pageTable[no][1] == 1) continue;
      
      int index = -1;
      int min_index = -1;
      int min_value = 100;
      for(int j=0;j<no_frames;j++) {
        if(frames[j]==-1) {
          min_index =j;
          break;
        }
        else if(pageTable[frames[j]][0] < min_value) {
          min_value = pageTable[frames[j]][0];
          min_index = j;
        }
      }

      index = min_index;
      pageTable[frames[index]][1] = 0;
      frames[index] = no;
      pageTable[frames[index]][1] = 1;

      for(int j=0;j<no_frames;j++) {
        cout<<frames[j]<<" ";
      }
      cout<<endl;
    }
  }

  void Optimal() {
    for(int i=0;i<frameString.size();i++) {
      int no=frameString[i] - 48;
      pageTable[no][0] = i;

      if(pageTable[no][1] == 1) continue;
      
      int min_index=-1;
      int index=-1;

      for(int j=0;j<no_frames;j++) {
        if(frames[j] == -1) {
          index = j;
          break;
        }
        int k=0;
        for(k=i+1;k<frameString.size();k++) {
          if(frames[j] == frameString[k] - 48) {
            pageTable[frames[j]][0] = k;
            break;
          }
          if(min_index < pageTable[frames[j]][0]) {
            min_index = pageTable[frames[j]][0];
            index = j;
          }
        }
        if(k==frameString.size()) {
          index = j;
          break;
        }
        
      }
     
      pageTable[frames[index]][1] = 0;
      frames[index] = no;
      pageTable[frames[index]][1] = 1;

      for(int j=0;j<no_frames;j++) {
        cout<<frames[j]<<" ";
      }
      cout<<endl;
    }
  }
  
};

int main() {

  Page_Replacement p(8,3);
  p.input();
  p.Optimal();
  
  
  return 0;
}