#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;

map<ull, vector<int> > block_thread_map;

int main(int argc, char *argv[]){
    int tid=0;
    ull addr=0, block_addr;
    char input_name[100];
    sprintf(input_name, "%s", argv[1]);
    
    vector<int> temp(8,0);

    ifstream inputfile(input_name);
    while(inputfile >> tid >> addr){
        block_addr=addr>>6;
        auto it=block_thread_map.find(block_addr);
        if(it != block_thread_map.end()){
            block_thread_map[block_addr][tid]=1;
        }
        else{
            block_thread_map[block_addr]=temp;
            block_thread_map[block_addr][tid]=1;
        }
    }
    cout<<"total distinct block accesses: "<<block_thread_map.size()<<endl;
    vector<ull> sharing_profile(9,0);
    int nums=0;
    for(auto e : block_thread_map){
        nums=0;
        for(auto q : e.second)  nums+=q;
        sharing_profile[nums]++;
    }
    cout<<"sharing profile of the program is as follow \n";
    for(int i=1; i<9;i++){
        cout<<i<<"  "<<sharing_profile[i]<<"\n";
    }
    return 0;
}
