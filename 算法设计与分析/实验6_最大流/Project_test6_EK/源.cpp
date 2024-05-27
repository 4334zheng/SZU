#include<iostream>
#include<ctime>
#include<algorithm>
#include<queue>
using namespace std;
#define maxn 2000
#define INF 999999999;
int flow[maxn][maxn];
int father[maxn];
int ANS[maxn];//残留网络的增广流量
int Map[maxn][maxn];//流网络对应的图
int vexnum, arcnum;

int CreateMap()
{
	memset(Map, 0, sizeof(Map));//初始化
	int n, m, a, b;
	cout << "请输入论文数量m：";
	cin >> m;
	cout << "请输入评审数量n：";
	cin >> n;
	cout << "请输入一篇论文需要安排的评审数a：";
	cin >> a;
	cout << "请输入一个评审最多可评论文数b：";
	cin >> b;
	vexnum = 2 + n + m;//论文数、评审数以及首尾两个节点
	arcnum = n + m + n * m;//首节点到评审、论文到尾节点、评审与论文一对m
	//建表
	for (int j = 2; j <= n + 1; j++)
		Map[1][j] += b;
	for (int i = 2; i <= n + 1; i++)
		for (int j = 2 + n; j <= m + 1 + n; j++)
			Map[i][j] += 1;
	for (int i = 2 + n; i <= m + 1 + n; i++)
		Map[i][vexnum] += a;
	return a * m;
}

int EK(int s, int e)
{
	int f = 0;  
	memset(flow, 0, sizeof(flow));
	memset(father, 0, sizeof(father));
	queue<int> Q;
	while (true)  //BFS找增广路 
	{
		memset(ANS, 0, sizeof(ANS)); //初始残留网络的流量 
		ANS[s] = INF;
		Q.push(s);
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			for (int v = 1; v <= e; v++)
				if (!ANS[v] && Map[u][v] > flow[u][v]) //UV有流量且残留量为0 
				{
					ANS[v] = min(ANS[u], Map[u][v] - flow[u][v]);//start->v路径上的最小权值 
					father[v] = u;//记录v的父亲u
					Q.push(v);
				}
		}
		if (ANS[e] == 0) //残留网络中无增广路径 
			return f;
		for (int u = e; u != s; u = father[u]) 
		{
			flow[father[u]][u] += ANS[e];
			flow[u][father[u]] -= ANS[e]; 
		}
		f += ANS[e]; //最大流更新 
	}
}

int main()
{
	int initflow = CreateMap();
	int maxflow;
	clock_t start, end;
	start = clock();
	maxflow = EK(1, vexnum);
	end = clock();
	cout << "The MaxFlow is " << maxflow << endl;
	if (initflow <= maxflow)
		cout << "存在分配方案" << endl;
	else
		cout << "不存在分配方案" << endl;
	cout << "the time cost is: " << double(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}
