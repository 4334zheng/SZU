#include <iostream>  
#include <cstdio>  
#include <cstring> 
#include<time.h> 
#include <cmath>  
#include<windows.h>
#include <algorithm>  
using namespace std;  
LARGE_INTEGER start,EndTime,freq;
int Visited[1000];  
int Map[1000][1000];  
int VNum,EdgeNum;  //点的数目和边的数目 
const int INF = 999999999;  
int DFS(int Start,int Flow)  
{  
    if(Start == VNum) return Flow;  
    for(int i = 1 ; i <= VNum ; i ++) 
	{  
        if(Map[Start][i] > 0 && Visited[i]==false) 
		{  
            Visited[i] = true;  
            int Tempans = DFS(i,min(Flow,Map[Start][i]));  
            if(Tempans > 0) 
			{  
                Map[Start][i] -= Tempans;  
                Map[i][Start] += Tempans;  
                return Tempans;  
            }  
        }  
    } 
	return 0; 
}  
int FordFulkerson(int start)  
{  
    int flow = 0;  
    while(true) 
	{  
        memset(Visited,0,sizeof(Visited));  
        int ans = DFS(start,INF);//找从源点到汇点的增广路 
        if(ans == 0) 
			return flow;
        flow += ans;//找到一个流量为ans的增广路 
    }  
}  
int CIN()
{
	memset(Map,0,sizeof(Map)); 
	int n,m,a,b;
	cout<<"n位评审: ";
	cin>>n;
	cout<<"m篇论文: ";
	cin>>m;
	cout<<"a: ";
    cin>>a;
    cout<<"b: ";
    cin>>b;
    VNum=2+n+m;
    EdgeNum=n+m+n*m;
    for(int i=2;i<=n+1;i++) //第一层 
    {
    	Map[1][i]+=b;
	}
    for(int i=2;i<=n+1;i++)//第二层 
    {
    	for(int j=2+n;j<=m+1+n;j++)
    	{
    		Map[i][j]+=1;
		}
	}
	for(int i=2+n;i<=m+1+n;i++)
	{
		Map[i][VNum]+=a;
	}   
	return m*a; 
}
int main()  
{
	int total;
	total=CIN();   
	int Finalflow;
	QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
	Finalflow=FordFulkerson(1);
	QueryPerformanceCounter(&EndTime);
	double time = (double)(EndTime.QuadPart-start.QuadPart)/(double)freq.QuadPart; //计算时间 
	cout <<"运行时间为"<<time*1000<<"ms\n";
    cout <<"最大流为"<< Finalflow << "\n";  
    if(total<=Finalflow)
    {
    	cout<<"有解\n";
	}
	else
	{
		cout<<"无解\n";
	}
    return 0;
}
/*43 15
1 2 20
1 3 20
1 4 20
2 5 1
2 6 1
2 7 1
2 8 1
2 9 1
2 10 1
2 11 1
2 12 1
2 13 1
2 14 1
3 5 1
3 6 1
3 7 1
3 8 1
3 9 1
3 10 1
3 11 1
3 12 1
3 13 1
3 14 1
4 5 1
4 6 1
4 7 1
4 8 1
4 9 1
4 10 1
4 11 1
4 12 1
4 13 1
4 14 1
5 15 1
6 15 1
7 15 1
8 15 1
9 15 1
10 15 1
11 15 1
12 15 1
13 15 1
14 15 1*/




