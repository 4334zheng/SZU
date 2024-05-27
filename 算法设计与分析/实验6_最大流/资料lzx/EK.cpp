#include <iostream>
#include <cstdio>  
#include <cstring>  
#include <cmath>  
#include <algorithm>
#include<time.h> 
#include<windows.h>  
#include <queue>
using namespace std;
#define maxn 1500
#define INF 0x7f7f7f7f
int Map[maxn][maxn],Flow[maxn][maxn];
LARGE_INTEGER start,EndTime,freq;
int Father[maxn];
int Remain[maxn];//残留网络的增广流量 
int EdgeNum,VNum;
int Edmonds_Karp(int start,int end) 
{
	int maxflow=0; //最大流 
	memset(Flow,0,sizeof(Flow));
	memset(Father,0,sizeof(Father)); //初始化 
	queue<int> Q;
	while(true)  //BFS找增广路 
	{
		memset(Remain,0,sizeof(Remain)); //初始残留网络的流量 
		Remain[start]=INF;
		Q.push(start);
		while(!Q.empty()) 
		{ 
			int u=Q.front();
			Q.pop();
			for(int v=1; v<=end; v++)
				if(!Remain[v]&&Map[u][v]>Flow[u][v]) //UV有流量且残留量为0 
				{
					Remain[v]=min(Remain[u],Map[u][v]-Flow[u][v]);//start->v路径上的最小权值 
					Father[v]=u;//记录v的父亲u
					Q.push(v);
				}
		}
		if(Remain[end]==0) //退出条件，即无增广路径 
			return maxflow;
		for(int u=end; u!=start; u=Father[u]) //汇点->源点 
		{ 
			Flow[Father[u]][u]+=Remain[end];//正向流更新 
			Flow[u][Father[u]]-=Remain[end];//反向流更新 
		}
		maxflow+=Remain[end]; //最大流更新 
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
	int total=CIN();
	int Finalflow;
	QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
	Finalflow=Edmonds_Karp(1,VNum);
	QueryPerformanceCounter(&EndTime);
	double time = (double)(EndTime.QuadPart-start.QuadPart)/(double)freq.QuadPart;
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
