#include<bits/stdc++.h>
using namespace std;

void printFrames(vector<int>frames){
    for(auto x : frames){
        cout<<x<<" ";
    }
    cout<<endl;
}

int pageFault(vector<int>pages,int frame){

    vector<int>frames(frame,-1);
    int pageCount = 0;
    int j = 0 ;
    for(int i = 0 ; i < pages.size();i++){
        // page is not present
        if(frames[j] == -1){
            pageCount++;
            frames[j] = pages[i];
            j = (j+1)%frame;
        }
        else{
        // given page is already present in the vector or not
            int flag =1;
            for(int k = 0 ; k<frame;k++){
                if( pages[i] == frames[k]){
                    flag = 0;
                }
            }
        // if flag == 0 then page is present and if flag == 1 means page is not present
            if(flag){
                frames[j] = pages[i];
                j = (j+1)%frame;
                pageCount++;
            }
        }

     printFrames(frames);
    }
    return pageCount;

}
int main()
{

    vector<int> pages {7,0,1,2,0,3,0,4,2,3,0,3,1,2,0};
    int frame = 3;
    cout<<pageFault(pages,frame)<<endl;

return 0;
}