#include<iostream>
#include<queue>
#include<ctime>
using namespace std;
#define MAX 1000000
#define INF 0x3f3f3f3f
int link[MAX];//��¼ÿ������������ӵĶ���
int arcnum = 0;
int vexnum;
int start;
int Map[1000][1000];//������ͼ��Ϣ�Ĵ洢����¼�����Ƿ�����
int layer[MAX];//�ֲ�

struct Node
{
	int v1, v2;//��㡢�յ�
	int weight;//����
	int connect;//��һ�����ӱ�
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
	Edge[arcnum].connect = link[s];//ʼ����ڱ�
	link[s] = arcnum;//��¼��һ������sΪʼ��ı�
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
				if (end == vexnum)//��������·��
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
	int sum = 0;//��¼v������ܹ�����������
	int del = weight;//del��¼ʣ������
	for (int i = link[v]; i && del; i = Edge[i].connect)
	{
		int end = Edge[i].v2;
		if (layer[end] == layer[v] + 1 && Edge[i].weight != 0)
		{
			int key = DFS(end, MIN(del, Edge[i].weight));
			if (key == 0)
			{
				layer[end] = 0;//�õ㲻�����������൱�ڸõ�����
			}
			Edge[i].weight -= key;
			Edge[i + 1].weight += key;//i+1��i�ķ����
			del -= key;
			sum += key;
		}
	}
	return sum;
}

int CreateMap()
{
	memset(Map, 0, sizeof(Map));//��ʼ��
	memset(link, 0, sizeof(link));
	start = 1;
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
	//����
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
		cout << "���ڷ��䷽��" << endl;
	else
		cout << "�����ڷ��䷽��" << endl;
	cout << "the time cost is: " << double(time_end - time_start) / double(CLOCKS_PER_SEC) * 1000.0 << "ms" << endl;
}