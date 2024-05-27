#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<sstream>
using namespace std;

#define maxv 1000000//最多点数
vector<vector<int>>Node;//邻接表
vector<int>father;
int vexnum;
int arcnum;
bool* visit;
int** edge;//边集
int Del_start;//当前被删边的起点和终点
int Del_end;
int Count;//桥的数量统计

void init()//初始化访问数组
{
	for (int i = 0; i < vexnum; i++)
		visit[i] = false;
}

void DFS(int v)
{
	visit[v] = true;
	for (int i = 0; i < Node[v].size(); i++)
	{
		if (visit[Node[v][i]] == false && !(v == Del_start && Node[v][i] == Del_end) && !(v == Del_end && Node[v][i] == Del_start)) //没被访问过且边未被删
		{
			DFS(Node[v][i]);
		}
	}
}

int DFSTraverse()//计算连通分量
{
	int ans = 0;
	init();//初始化数组
	for (int i = 0; i < vexnum; i++)
	{
		if (visit[i] == false)
		{
			DFS(i);
			ans++;
		}
	}
	return ans;
}

void DFSCount()//计算桥数
{
	Count = 0;
	int ans_before = DFSTraverse();//删除边前图的连通分量
	for (int i = 0; i < arcnum; i++)
	{
		//根据边数设置循环，记录当前被删边的起点和终点
		Del_start = edge[i][0];
		Del_end = edge[i][1];
		int ans_after = DFSTraverse();
		if (ans_after > ans_before)//如果删边后连通分量数增加，该边为桥
		{
			cout << "bridge" << Count + 1 << " " << Del_start << "--" << Del_end << endl;
			Count++;
		}
	}
}

//基准法+并查集
void JoinSetInit()
{
	for (int i = 0; i < vexnum; i++) 
		father[i] = i;
}
int JoinSetFind(int v)//查找父亲（即查找顶点所在集合）
{
	if (father[v] == v)
		return v;
	father[v] = JoinSetFind(father[v]);
	return father[v];
}
void JoinSetCount()
{
	int ans_before = DFSTraverse();//删除边前图的连通分量
	//cout << "ans_before=" << ans_before << endl;
	for (int i = 0; i < arcnum; i++)
	{
		init();//初始化visit
		JoinSetInit();//初始化father
		int res = vexnum;//统计集合数
		for (int j = 0; j < arcnum; j++)
		{
			if (i == j)
				continue;
			int f1 = JoinSetFind(edge[j][0]);
			int f2 = JoinSetFind(edge[j][1]);
			if (f1 != f2) {
				father[f2] = f1;//合并
				res--;
			}
		}
		cout << "father:";
		for (int i = 0; i < vexnum; i++)
			cout << father[i] << " ";
		cout << endl;
		if (res != ans_before)
			Count++;
	}
}


void LoadData()//读取文本文件
{
	//测试运行时间
	//ifstream fin("C://Users//4334//Desktop//datainfo//test50-100.txt");
	//ifstream fin("C://Users//4334//Desktop//datainfo//test50-200.txt");
	//ifstream fin("C://Users//4334//Desktop//datainfo//test50-300.txt");

	//自定义小规模数据验证算法正确性
	ifstream fin("C://Users//4334//Desktop//datainfo//test.txt");
	//ifstream fin("C://Users//4334//Desktop//datainfo//mediumDG.txt");
	//ifstream fin("C://Users//4334//Desktop//datainfo//largeG.txt");

	fin >> vexnum >> arcnum;
	edge = new int* [arcnum];
	for (int i = 0; i < arcnum; i++)
		edge[i] = new int[2];
	visit = new bool[vexnum];
	Node.clear();
	Node.resize(vexnum);
	father.clear();
	father.resize(vexnum);
	JoinSetInit();
	for (int i = 0; i < arcnum; i++)
	{
		int v1, v2;
		fin >> v1 >> v2;
		//cout << v1 << " " << v2 << endl;
		int f1 = JoinSetFind(v1);
		int f2 = JoinSetFind(v2);
		if (f1 != f2)
			father[f1] = f2;
		//创建邻接表并存储边信息
		Node[v1].push_back(v2);
		Node[v2].push_back(v1);
		edge[i][0] = v1;
		edge[i][1] = v2;
	}
}

int main(int argc, char** argv)
{
	clock_t start, finish;
	start = clock();
	Count = 0;
	LoadData();
	//DFSCount();
	JoinSetCount();
	finish = clock();
	cout << "该图中桥的数量为：" << Count << endl;
	cout << "the time cost is: " << double(finish - start) << "ms" << endl;
	return 0;
}