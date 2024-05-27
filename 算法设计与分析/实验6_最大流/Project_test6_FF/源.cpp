#include<iostream>
#include<ctime>
#include<algorithm>
using namespace std;
int visit[1000];
int Map[1000][1000];//�������Ӧ��ͼ
int vexnum, arcnum;
const int INF = 999999999;

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
		int ans = DFS(s, INF);//�ҵ���Դ�㵽��������·��
		if (ans == 0)//û������·�������
			return f;
		f += ans;//�ҵ�һ������Ϊans������·��
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
		cout << "���ڷ��䷽��" << endl;
	else
		cout << "�����ڷ��䷽��" << endl;
	cout << "the time cost is: " << double(end - start) / (CLOCKS_PER_SEC * 1.0) * 1000.0 << "ms" << endl;
}
