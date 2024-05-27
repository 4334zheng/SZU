#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include<time.h> 
#include<windows.h>  
#define MAX 1000000
#define INF 0x3f3f3f3f
#include <iostream>
using namespace std;
LARGE_INTEGER start,EndTime,freq;
int h[MAX];//用于存储每一个顶点最后连接的是哪一个顶点;
int EdgeNum = 0;//用于记录边的数量，记住，每一对平行边的序号一定相邻;
int Start,VNum;
int Map[1000][1000];//用于记录两点的相邻与否；

struct Node
{
    int from;//始点
    int to;//终点
    int flow;//流量 
    int next;//始点下一个连接边
}Edge[MAX];

int Min(int a, int b)
{
    return a < b ? a : b;
}

void AddEdge(int f, int t, int w) //添加边 
{
	EdgeNum++; //边数++ 
    Edge[EdgeNum].from = f;
    Edge[EdgeNum].to = t;
    Edge[EdgeNum].flow = w;
    Edge[EdgeNum].next = h[f];//始点邻边 
    h[f] = EdgeNum;//记录下一次再有以f为始点的边
}

int deep[MAX];//分层 
bool BFS()
{
    memset(deep,0,sizeof(deep));//初始化 
    deep[Start] = 1;
    std::queue<int> Q;//队列 
    Q.push(Start);
    while(!Q.empty())
    {
        int q = Q.front();
        Q.pop();
        for(int i = h[q]; i != 0; i = Edge[i].next) //(第一个实例)刚开始从点1开始，但是从第三条边开始。然后再是第一条边 
        {
            int to = Edge[i].to; //该边终点 
            if(deep[to] == 0 && Edge[i].flow != 0) //deep为0且其流量不为0 
            {
                deep[to] = deep[q] + 1;   //终点是始点深度＋1 
                if(to == VNum) //有增广路 
                {
                    return true;
                }
                Q.push(to);
            }
        }
    }
    return deep[VNum] != 0;
}

int DFS(int from, int Flow)//from是当前点，Flow是流进点的流量
{
    if(from == VNum)
        return Flow;
    int sum = 0;//sum用来记录这一点from到底能够流多少流量;
    int r = Flow;//r在接下来用于记录这一点from流了一定的流量之后，还剩下多少流量可流出;
    for(int i = h[from]; i && r; i = Edge[i].next)
    {
        int to = Edge[i].to;
        if(deep[to] == deep[from] + 1 && Edge[i].flow != 0)//只找比当前点层数多 1的点进行增广
        {
            int key = DFS(to, Min(r, Edge[i].flow));//递归找到以这个点为起点能流过多少流量，流进的流量为r和权值的最小值;
            if(key == 0)
                deep[to] = 0;//如果以这个点起不能再流进，那么这个点作废;
            Edge[i].flow -= key;
            Edge[i + 1].flow += key;//边i + 1是边i的反向边;
            r -= key;
            sum += key;
        }
    }
    return sum;
}
int CIN()
{
	memset(Map,0,sizeof(Map)); 
	memset(h, 0, sizeof(h));
	Start=1;
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
    for(int i=2;i<=n+1;i++) //第一层 
    {
    	if(Map[1][i] == 0)
        {
            AddEdge(1,i,b);
            Map[1][i] = EdgeNum;
            AddEdge(i,1,0);
            Map[i][1] = EdgeNum;
        }
        else 
        {
            Edge[Map[1][i]].flow += b;
        }
	}
    for(int i=2;i<=n+1;i++)//第二层 
    {
    	for(int j=2+n;j<=m+1+n;j++)
    	{
    		if(Map[i][j] == 0)
	        {
	            AddEdge(i,j,1);
	            Map[i][j] = EdgeNum;
	            AddEdge(j,i,0);
	            Map[j][i] = EdgeNum;
	        }
	        else 
	        {
	            Edge[Map[i][j]].flow = 1;
	        }
		}
	}
	for(int i=2+n;i<=m+1+n;i++)
	{
		if(Map[i][VNum] == 0)
	    {
	        AddEdge(i,VNum,a);
	        Map[i][VNum] = EdgeNum;
	        AddEdge(VNum,i,a);
	        Map[i][VNum] = EdgeNum;
	    }
	    else 
	    {
	        Edge[Map[i][VNum]].flow = a;
	    }
		//Map[i][VNum]+=a;
	}   
	return m*a; 
}
int main()
{
	int total;
	total=CIN();
    /*int N,i;
    scanf("%d", &N);//点的总数;
    Start = 1;
    VNum = N;
    int a, b, c;
    memset(h, 0, sizeof(h));
    memset(Map, 0, sizeof(Map));
    while(scanf("%d%d%d", &a, &b, &c) != EOF)
    {
        if(Map[a][b] == 0)
        {
            AddEdge(a,b,c);
            Map[a][b] = EdgeNum;
            AddEdge(b,a,0);
            Map[b][a] = EdgeNum;
        }
        else 
        {
            Edge[Map[a][b]].flow += c;
        }
    }*/
    int Finalflow = 0;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    while(BFS())
    {
        Finalflow += DFS(Start, INF);
    }
    QueryPerformanceCounter(&EndTime);
	double time = (double)(EndTime.QuadPart-start.QuadPart)/(double)freq.QuadPart;
	cout <<"运行时间为"<<time*1000<<"ms\n";
    cout<<"最大流是："<<Finalflow<<"\n";
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
/*
6
1 2 16
1 3 13
2 3 10
2 4 12
3 5 14
4 3 9
4 6 20
5 4 7
5 6 4
*/
