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
                int index =INT_MIN;
                int replace;
                map<int,int> mp;
                for(int c = 0 ; c<frame;c++){
                    int flag2= 1;
                    for(int p = i+1; p<pages.size();p++){
                        if(frames[c]==pages[p]){
                            mp[c] = p;
                            flag2 = 0;
                            break;
                        }
                    }
                    if(flag2){
                        mp[c] = 0;
                    }
                }
                
                for(auto x : mp){
                    if(x.second == 0){
                        replace = x.first;
                        break;
                    }
                    else{
                       if(index < x.second) {
                        index = x.second;
                        replace = x.first;
                       }
                    }
                }
                cout<<"replace index : "<<index<<" "<<frames[replace]<<endl;
                frames[replace] = pages[i];
                // j =(j+1)%frame;
                pageCount++;
            }
        }

     printFrames(frames);
    }
    return pageCount;

}
int main()
{

    vector<int> pages {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int frame = 4;
    cout<<pageFault(pages,frame)<<endl;

return 0;
}