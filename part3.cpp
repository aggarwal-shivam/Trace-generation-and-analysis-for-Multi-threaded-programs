#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
map<ull,ull>innermap;
map<ull,map<ull,ull>>outermap;
ull CacheHits=0,CacheMisses=0;

class Cache
{
	public:
		ull tag,set,way;
		
		ull flag=0;
		void setGetter(ull addr);
		void tagGetter(ull addr);
		int isMissOrHit(ull set, ull tag);
		void LRU(ull set, ull tag);
};

void Cache::setGetter(ull addr)
{
	set = (addr & 0x1FFC0) >> 6;
}

void Cache::tagGetter(ull addr)
{
	tag = (addr & 0xFFFFFFFFFFFE0000) >> 17;
}

int Cache::isMissOrHit(ull set, ull tag)
{
	int hit=-1;
	pair<ull,ull>temp;
	auto outer_itr = outermap.find(set);
	if(outer_itr != outermap.end())
	{
		innermap=outermap[set];
		for(auto e: innermap)
		{
			if(e.second == tag)
			{
				temp=e;
				hit=1;
				break;
			}
		}
		if(hit==1)
		{
			innermap.erase(temp.first);
			innermap.insert({flag,tag});
			outermap[set]=innermap;
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

void Cache::LRU(ull set, ull tag)
{
	auto outer_itr = outermap.find(set);
	if(outer_itr == outermap.end())
	{
		outermap[set].insert({flag,tag});
	}
	else
	{
		innermap=outermap[set];
		if(innermap.size()<16)
		{
			innermap.insert({flag,tag});
		}
		else
		{
			innermap.erase(innermap.begin());
			innermap.insert({flag,tag});
		}
		outermap[set]=innermap;
	}
}

int main(int agrc, char *argv[])
{
	
	char input_name[100];
	ull addr=0;
	int tid;

	sprintf(input_name, "%s", argv[1]);
   
    string output_name=input_name;
    for(int k=0;k<4;k++)    output_name.pop_back();
    output_name=output_name+"_cachemiss.out";
	fstream fout;
	fout.open(output_name, ios::out | ios::app);

	ifstream inputfile(input_name);
    Cache cacheObj;
    while (inputfile >> tid >> addr)
    {
     	cacheObj.setGetter(addr);
     	cacheObj.tagGetter(addr);
     	cacheObj.flag++;
     	int hit = cacheObj.isMissOrHit(cacheObj.set,cacheObj.tag);
     	if(hit==-1)
     	{
     		CacheMisses++;
     		fout<<tid<<" "<<addr<<"\n";
     		cacheObj.LRU(cacheObj.set,cacheObj.tag);
     	}
     	if(hit==1)
     	{
     		CacheHits++;
     	}
    }
    cout<<"Cache Hits:"<<CacheHits<<" Cache Misses:"<<CacheMisses<<endl;
    return 0;
}