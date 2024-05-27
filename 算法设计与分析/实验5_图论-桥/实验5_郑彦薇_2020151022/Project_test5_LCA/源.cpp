#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<sstream>
using namespace std;

#define maxv 1000000
vector<int>Node[maxv + 1];
vector<int>BFSTree;//生成树
int vexnum;
int arcnum;
int visit[maxv + 1];//访问数组
int depth[maxv + 1];//顶点深度
int father[maxv + 1];
int set[maxv + 1];//并查集数组，即用于路径压缩的父亲数组
int Loop[maxv + 1];//环边
int Count = 0;

void CreateTree(int v)//生成树
{
	queue<int>Q;
	Q.push(v);
	depth[v] = 1;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int y : Node[u])
		{
			if (visit[y] == 0)
			{
				visit[y] = 1;
				father[y] = u;
				set[y] = u;
				depth[y] = depth[u] + 1;//深度加1
				BFSTree.push_back(y);
				Q.push(y);
			}
		}
	}
}

void BFSTraverse()
{
	for (int i = 0; i < vexnum; i++)
	{
		if (visit[i] == 0)
		{
			Loop[i] = 1;
			visit[i] = 1;
			BFSTree.push_back(i);
			CreateTree(i);
		}
	}
}

void LCA(int x, int y)
{
	if (x == father[y] || y == father[x])
		return;
	if (depth[x] < depth[y])//使得x为深度最深的点
	{
		x ^= y;
		y ^= x;
		x ^= y;
	}
	while (depth[x] > depth[y])//x上升到与y同一高度,方便查找lca
	{
		Loop[x] = 1;
		x = set[x];
	}
	//寻找lca最近公共祖先
	while (x != y)
	{
		Loop[x] = 1;
		x = set[x];
		Loop[y] = 1;
		y = set[y];
	}
	int lca = x;
	//路径压缩
	int temp_x = x;
	int temp_y = y;
	while (temp_x != lca)
	{
		int temp = set[temp_x];
		set[temp_x] = lca;//将这些点的父亲变为最近公共祖先，且深度为最近公共祖先+1
		depth[temp_x] = depth[lca] + 1;
		temp_x = temp;
	}
	while (temp_y != lca)
	{
		int temp = set[temp_y];
		set[temp_y] = lca;
		depth[temp_y] = depth[lca] + 1;
		temp_y = temp;
	}
}

void LcaCount()
{
	BFSTraverse();//通过BFS建立生成树
	for (int x : BFSTree)//遍历生成树中的点
	{
		for (int y : Node[x])//(x, y)为边
		{
			LCA(x, y);
		}
	}
}

void LoadData()
{
	ifstream fin("C://Users//4334//Desktop//datainfo//test.txt");
	//ifstream fin("C://Users//4334//Desktop//datainfo//mediumDG.txt");
	//ifstream fin("C://Users//4334//Desktop//datainfo//largeG.txt");
	fin >> vexnum >> arcnum;
	for (int i = 0; i < arcnum; i++)
	{
		int v1, v2;
		fin >> v1 >> v2;
		Node[v1].push_back(v2);
		Node[v2].push_back(v1);
	}
}

int main()
{
	cout << "数据载入..." << endl;
	LoadData();
	cout << "载入完成..." << endl;
	clock_t start, finish;
	start = clock();
	LcaCount();
	finish = clock();
	for (int i = 0; i < vexnum; i++)
	{
		if (Loop[i] == 0)
			Count++;
	}
	cout << "该图中桥的数量为：" << Count << endl;
	cout << "the time cost is: " << double(finish - start) << "ms" << endl;
	return 0;
}