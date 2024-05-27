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
int Remain[maxn];//����������������� 
int EdgeNum,VNum;
int Edmonds_Karp(int start,int end) 
{
	int maxflow=0; //����� 
	memset(Flow,0,sizeof(Flow));
	memset(Father,0,sizeof(Father)); //��ʼ�� 
	queue<int> Q;
	while(true)  //BFS������· 
	{
		memset(Remain,0,sizeof(Remain)); //��ʼ������������� 
		Remain[start]=INF;
		Q.push(start);
		while(!Q.empty()) 
		{ 
			int u=Q.front();
			Q.pop();
			for(int v=1; v<=end; v++)
				if(!Remain[v]&&Map[u][v]>Flow[u][v]) //UV�������Ҳ�����Ϊ0 
				{
					Remain[v]=min(Remain[u],Map[u][v]-Flow[u][v]);//start->v·���ϵ���СȨֵ 
					Father[v]=u;//��¼v�ĸ���u
					Q.push(v);
				}
		}
		if(Remain[end]==0) //�˳���������������·�� 
			return maxflow;
		for(int u=end; u!=start; u=Father[u]) //���->Դ�� 
		{ 
			Flow[Father[u]][u]+=Remain[end];//���������� 
			Flow[u][Father[u]]-=Remain[end];//���������� 
		}
		maxflow+=Remain[end]; //��������� 
	}
}
int CIN()
{
	memset(Map,0,sizeof(Map)); 
	int n,m,a,b;
	cout<<"nλ����: ";
	cin>>n;
	cout<<"mƪ����: ";
	cin>>m;
	cout<<"a: ";
    cin>>a;
    cout<<"b: ";
    cin>>b;
    VNum=2+n+m;
    EdgeNum=n+m+n*m;
    for(int i=2;i<=n+1;i++) //��һ�� 
    {
    	Map[1][i]+=b;
	}
    for(int i=2;i<=n+1;i++)//�ڶ��� 
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
	cout <<"����ʱ��Ϊ"<<time*1000<<"ms\n";
    cout <<"�����Ϊ"<< Finalflow << "\n";  
    if(total<=Finalflow)
    {
    	cout<<"�н�\n";
	}
	else
	{
		cout<<"�޽�\n";
	}
    return 0;
}
