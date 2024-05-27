#include<iostream>
#include<queue>
#include<ctime>
using namespace std;
#define MAX 1000000
#define INF 0x3f3f3f3f
int link[MAX];//记录每个顶点最后连接的顶点
int arcnum = 0;
int vexnum;
int start;
int Map[1000][1000];//流网络图信息的存储，记录两点是否相邻
int layer[MAX];//分层

struct Node
{
	int v1, v2;//起点、终点
	int weight;//流量
	int connect;//下一个连接边
}Edge[MAX];

int MIN(int a, int b)
{
	return a < b ? a : b;
}

void AddEdge(int s, int e, int w)
{
	arcnum++;
	Edge[arcnum].v1 = s;
	Edge[arcnum].v2 = e;
	Edge[arcnum].weight = w;
	Edge[arcnum].connect = link[s];//始点的邻边
	link[s] = arcnum;//记录下一条仍以s为始点的边
}

bool BFS()
{
	memset(layer, 0, sizeof(layer));
	layer[start] = 1;
	queue<int>Q;
	Q.push(start);
	while (!Q.empty())
	{
		int q = Q.front();
		Q.pop();
		for (int i = link[q]; i != 0; i = Edge[i].connect)
		{
			int end = Edge[i].v2;
			if (layer[end] == 0 && Edge[i].weight != 0)
			{
				layer[end] = layer[q] + 1;
				if (end == vexnum)//存在增广路径
					return true;
				Q.push(end);
			}
		}
	}
	return layer[vexnum] != 0;
}

int DFS(int v, int weight)
{
	if (v == vexnum)
		return weight;
	int sum = 0;//记录v点具体能够流多少流量
	int del = weight;//del记录剩余流量
	for (int i = link[v]; i && del; i = Edge[i].connect)
	{
		int end = Edge[i].v2;
		if (layer[end] == layer[v] + 1 && Edge[i].weight != 0)
		{
			int key = DFS(end, MIN(del, Edge[i].weight));
			if (key == 0)
			{
				layer[end] = 0;//该点不能再流进，相当于该点作废
			}
			Edge[i].weight -= key;
			Edge[i + 1].weight += key;//i+1是i的反向边
			del -= key;
			sum += key;
		}
	}
	return sum;
}

int CreateMap()
{
	memset(Map, 0, sizeof(Map));//初始化
	memset(link, 0, sizeof(link));
	start = 1;
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
	//建表
	for (int j = 2; j <= n + 1; j++) {
		if (Map[1][j] == 0)
		{
			AddEdge(1, j, b);
			Map[1][j] = arcnum;
			AddEdge(j, 1, 0);
			Map[j][1] = arcnum;
		}
		else
		{
			Edge[Map[1][j]].weight += b;
		}
	}
	for (int i = 2; i <= n + 1; i++) {
		for (int j = 2 + n; j <= m + 1 + n; j++) {
			if (Map[i][j] == 0)
			{
				AddEdge(i, j, 1);
				Map[i][j] = arcnum;
				AddEdge(j, i, 0);
				Map[j][i] = arcnum;
			}
			else
			{
				Edge[Map[i][j]].weight = 1;
			}
		}
	}
	for (int i = 2 + n; i <= m + 1 + n; i++) {
		if (Map[i][vexnum] == 0)
		{
			AddEdge(i, vexnum, a);
			Map[i][vexnum] = arcnum;
			AddEdge(vexnum, i, a);
			Map[i][vexnum] = arcnum;
		}
		else
		{
			Edge[Map[i][vexnum]].weight = a;
		}
	}
	return a * m;
}

int main()
{
	int initflow = CreateMap();
	int maxflow = 0;
	clock_t time_start, time_end;
	time_start = clock();
	while (BFS())
	{
		maxflow += DFS(start, INF);
	}
	time_end = clock();
	cout << "The MaxFlow is " << maxflow << endl;
	if (initflow <= maxflow)
		cout << "存在分配方案" << endl;
	else
		cout << "不存在分配方案" << endl;
	cout << "the time cost is: " << double(time_end - time_start) / double(CLOCKS_PER_SEC) * 1000.0 << "ms" << endl;
}