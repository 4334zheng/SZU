#include<iostream>
#include<ctime>
#include<algorithm>
using namespace std;
int visit[1000];
int Map[1000][1000];//流网络对应的图
int vexnum, arcnum;
const int INF = 999999999;

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

int DFS(int s, int f)
{
	if (s == vexnum)
		return f;
	for (int i = 1; i <= vexnum; i++)
	{
		if (Map[s][i] > 0 && visit[i] == false)
		{
			visit[i] = true;
			int temp = DFS(i, min(f, Map[s][i]));
			if (temp > 0)
			{
				Map[s][i] -= temp;
				Map[i][s] += temp;
				return temp;
			}
		}
	}
	return 0;
}

int FF(int s)
{
	int f = 0;
	while (true)
	{
		memset(visit, 0, sizeof(visit));
		int ans = DFS(s, INF);//找到从源点到汇点的增广路径
		if (ans == 0)//没有增广路，最大流
			return f;
		f += ans;//找到一个流量为ans的增广路径
	}
}

int main()
{
	int initflow = CreateMap();
	int maxflow;
	clock_t start, end;
	start = clock();
	maxflow = FF(1);
	end = clock();
	cout << "The MaxFlow is " << maxflow << endl;
	if (initflow <= maxflow)
		cout << "存在分配方案" << endl;
	else
		cout << "不存在分配方案" << endl;
	cout << "the time cost is: " << double(end - start) / (CLOCKS_PER_SEC * 1.0) * 1000.0 << "ms" << endl;
}
