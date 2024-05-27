#include<iostream>
#include<ctime>
#include<algorithm>
#include<queue>
using namespace std;
#define maxn 2000
#define INF 999999999;
int flow[maxn][maxn];
int father[maxn];
int ANS[maxn];//�����������������
int Map[maxn][maxn];//�������Ӧ��ͼ
int vexnum, arcnum;

int CreateMap()
{
	memset(Map, 0, sizeof(Map));//��ʼ��
	int n, m, a, b;
	cout << "��������������m��";
	cin >> m;
	cout << "��������������n��";
	cin >> n;
	cout << "������һƪ������Ҫ���ŵ�������a��";
	cin >> a;
	cout << "������һ������������������b��";
	cin >> b;
	vexnum = 2 + n + m;//���������������Լ���β�����ڵ�
	arcnum = n + m + n * m;//�׽ڵ㵽�������ĵ�β�ڵ㡢����������һ��m
	//����
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
	while (true)  //BFS������· 
	{
		memset(ANS, 0, sizeof(ANS)); //��ʼ������������� 
		ANS[s] = INF;
		Q.push(s);
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			for (int v = 1; v <= e; v++)
				if (!ANS[v] && Map[u][v] > flow[u][v]) //UV�������Ҳ�����Ϊ0 
				{
					ANS[v] = min(ANS[u], Map[u][v] - flow[u][v]);//start->v·���ϵ���СȨֵ 
					father[v] = u;//��¼v�ĸ���u
					Q.push(v);
				}
		}
		if (ANS[e] == 0) //����������������·�� 
			return f;
		for (int u = e; u != s; u = father[u]) 
		{
			flow[father[u]][u] += ANS[e];
			flow[u][father[u]] -= ANS[e]; 
		}
		f += ANS[e]; //��������� 
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
		cout << "���ڷ��䷽��" << endl;
	else
		cout << "�����ڷ��䷽��" << endl;
	cout << "the time cost is: " << double(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}
