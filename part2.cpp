#include<bits/stdc++.h>
#define ull unsigned long long

using namespace std;

map<ull, ull> block_map, distance_map;
ull cur_access, acc_dist, N, addr=0, block_addr;

int main(int argc, char *argv[]){
    FILE* fp;
    int tid;
    char input_name[100];
    cur_access=0;
    acc_dist=0;
    N=0;

    sprintf(input_name, "%s", argv[1]);

    ifstream inputfile(input_name);  //file object for reading
    while(inputfile >> tid >> addr){   //file reading line by line
        block_addr = addr >> 6;
        auto it= block_map.find(block_addr);
        if (it != block_map.end()){
            N++;
            acc_dist=cur_access - it->second;

            auto it_dist=distance_map.find(acc_dist);
            if(it_dist != distance_map.end()){
                it_dist->second++;
            }
            else{
                distance_map.insert({acc_dist,1});
            }
            block_map[block_addr]=cur_access;
        }
        else{
            block_map.insert({block_addr, cur_access});
        }
        cur_access++;
    }
    string out_name=input_name;
    for(int k=0;k<3;k++)    out_name.pop_back();
    out_name+="csv";
    fstream fout;
    fout.open(out_name, ios::out | ios::app);

    double count_cumulative, cum_fun_value, scaled_dist;
    count_cumulative=0;
    for(auto e : distance_map){
        count_cumulative+=e.second;
        cum_fun_value=count_cumulative/N; //y-value
        scaled_dist=log10(e.first); // x-value
        fout<<scaled_dist<<", "
            <<cum_fun_value<<"\n";
    }
    return 0;
}