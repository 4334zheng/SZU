#include<iostream>
#include<algorithm>
#include<fstream>
#include<assert.h>
#include<string>
#include<sstream>
using namespace std;

#define n 9	//点数
#define color_num 4	//颜色数
int a[n + 1][n + 1];//邻接表存储点及相邻点信息

class Node
{
public:
	int color;//当前涂色
	int colorEnable[color_num + 1];//颜色可选状态，1表示可以用该颜色，0则不行
	int colorEnableNum;//区域剩余可以选择的颜色数,即colorEnableNum中1的数量
	int next_D;//点的度即区域的相邻区域数
	Node()//初始化结点信息
	{
		color = 0;
		colorEnableNum = color_num;
		next_D = 0;
		for (int i = 0; i < color_num + 1; i++)
			colorEnable[i] = 1;//一开始区域可涂颜色包含全部颜色
	}
};

int DFS(Node* node, int v)
{
	if (v == n)//最后一个点完成涂色
	{
		return node[v].colorEnableNum;
	}
	else
	{
		int cnt = 0;
		for (int i = 1; i <= color_num; i++)
		{
			if (node[v].colorEnable[i] == 1)//v可以涂i色
			{
				int temp = 0;
				node[v].color = i;
				for (int k = 1; k <= a[v][0]; ++k)
				{
					int j = a[v][k];
					if (node[j].color == 0 && node[j].colorEnable[i] == 1)
					{
						node[j].colorEnable[i] = -v;//在j点可涂色中删除i
						node[j].colorEnableNum--;//可涂色数减1
					}
				}
				temp = DFS(node, v + 1);

			Recall://数组回溯
				for (int k = 1; k <= a[v][0]; ++k)
				{
					int j = a[v][k];//j为相邻区域
					if (node[j].colorEnable[i] == -v)//判断j是否为v的上一个点
					{
						node[j].colorEnableNum++;
						node[j].colorEnable[i] = 1;
					}
				}
				node[v].color = 0;
				cnt += temp;
			}
		}
		return cnt;
	}
}

int main()
{
	Node node[n + 1];
	memset(a, 0, sizeof(0));
	string file = "C://users/4334/Desktop/information/le9_4a.txt";
	//string file = "C://users/4334/Desktop/information/le450_5a.col";
	//string file = "C://users/4334/Desktop/information/le450_15b.col";
	//string file = "C://users/4334/Desktop/information/le450_25a.col";
	ifstream infile;
	infile.open(file.data());
	assert(infile.is_open());
	string line;
	while (getline(infile, line))
	{
		if (line[0] == 'e')
		{
			int i = 2;
			string temp1, temp2;
			//获取边的两个顶点
			while (1)
			{
				temp1 += line[i];
				i++;
				if (line[i] < '0' || line[i]>'9')
					break;
			}
			i++;
			while (1)
			{
				temp2 += line[i];
				i++;
				if (line[i] < '0' || line[i]>'9')
					break;
			}
			stringstream s1(temp1);
			stringstream s2(temp2);
			int v1, v2;
			s1 >> v1;
			s2 >> v2;
			a[v1][0]++;//v1行第一个位置存放相邻区域个数，之后每一个位置存放相邻区域
			a[v1][a[v1][0]] = v2;
			a[v2][0]++;
			a[v2][a[v2][0]] = v1;
			node[v1].next_D++;//度
			node[v2].next_D++;
		}
	}
	infile.close();
	clock_t start, finish;
	int t = 1;
	int answer;//解的个数
	start = clock();
	while (t--)
	{
		answer = DFS(node, 1);
	}
	finish = clock();
	cout << "the time cost is:" << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	cout << "总方案数:" << answer << endl;
	return 0;
}