#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<fstream>
#include<assert.h>
#include<string>
#include<sstream>
using namespace std;

#define n 150	//����
#define edge 2000 //����
#define color_num 4	//��ɫ��
int a[n + 1][n + 1];//�ڽӱ�洢�㼰���ڵ���Ϣ

class Node
{
public:
	int color;//��ǰͿɫ
	int colorEnable[color_num + 1];//��ɫ��ѡ״̬��1��ʾ�����ø���ɫ��0����
	int colorEnableNum;//����ʣ�����ѡ�����ɫ��,��colorEnableNum��1������
	int next_D;//��Ķȼ����������������
	Node()//��ʼ�������Ϣ
	{
		color = 0;
		colorEnableNum = color_num;
		next_D = 0;
		for (int i = 0; i < color_num + 1; i++)
			colorEnable[i] = 1;//һ��ʼ�����Ϳ��ɫ����ȫ����ɫ
	}
};

int MRV(Node* node)
{
	int min = 1e20;
	int index = 0;
	for (int i = 1; i <= n; i++)
	{
		if (node[i].color == 0)
		{
			int min1 = node[i].colorEnableNum;
			if (min > min1)
			{
				min = min1;
				index = i;
			}
		}
	}
	return index;
}

int MRVandDH(Node* node)
{
	int min = 1e20;
	int index = 0;
	for (int i = 1; i <= n; i++)
	{
		if (node[i].color == 0)
		{
			int min1 = node[i].colorEnableNum;
			if (min > min1)
			{
				min = min1;
				index = i;
			}
			else if (min == min1)//��ʾ�ж����С��ɫѡ����Ҷ����
			{
				if (node[i].next_D > node[index].next_D)
				{
					index = i;
				}
			}
		}
	}
	return index;
}

bool Forward(Node* node, int s, int j, int v)//sΪv��ǰͿɫ��jΪv����һ�����
{
	node[j].colorEnable[s] = -v;
	node[j].colorEnableNum--;
	node[j].next_D--;
	if (node[j].colorEnableNum <= 0)
		return false;
	return true;
}

long long DFS(Node* node, int v, int count)
{
	if (count == n)//���һ�������Ϳɫ
	{
		return node[v].colorEnableNum;
	}
	else
	{
		long long cnt = 0;
		for (int i = 1; i <= color_num; i++)
		{
			if (node[v].colorEnable[i] == 1)//v����Ϳiɫ
			{
				int temp = 0;
				node[v].color = i;
				for (int k = 1; k <= a[v][0]; ++k)
				{
					int j = a[v][k];
					if (node[j].color == 0 && node[j].colorEnable[i] == 1)
					{
						//node[j].colorEnable[i] = -v;//��j���Ϳɫ��ɾ��i
						//node[j].colorEnableNum--;//��Ϳɫ����1
						if (Forward(node, i, j, v) == false)//��ǰ̽��
							goto Recall;
					}
				}
				temp = DFS(node, MRVandDH(node), count + 1);

			Recall://�������
				for (int k = 1; k <= a[v][0]; ++k)
				{
					int j = a[v][k];//jΪ��������
					if (node[j].colorEnable[i] == -v)//�ж�j�Ƿ�Ϊv����һ����
					{
						node[j].colorEnableNum++;
						node[j].next_D++;
						node[j].colorEnable[i] = 1;
					}
				}
				node[v].color = 0;
				cnt += temp;
				if (cnt > 100000000)//����������࣬��ǰ����
				{
					return cnt;
				}
			}
		}
		return cnt;
	}
}

int main()
{
	Node node[n + 1];
	memset(a, 0, sizeof(0));
	int e[n + 1][n + 1];
	int v1;//�ߵ������յ�
	int v2;
	int sum = 1;//ͳ�Ƶ�ǰ�ı���
	memset(e, 0, sizeof(e));
	srand((unsigned int) time(0));
	while (sum <= edge)
	{
		while (1)
		{
			v1 = rand() % n + 1;
			v2 = rand() % n + 1;
			if (v1 != v2 && e[v1][v2] != 1)
				break;//����յ㲻����ұ߲��ظ����ɹ�����
		}
		e[v1][v2] = e[v2][v1] = 1;//��ʾ��v1v2Ϊ�˵�ı�������
		//cout << "e " << v1 << " " << v2 << endl;
		//�����ڽӱ�
		a[v1][0]++;//v1�е�һ��λ�ô���������������֮��ÿһ��λ�ô����������
		a[v1][a[v1][0]] = v2;
		a[v2][0]++;
		a[v2][a[v2][0]] = v1;
		node[v1].next_D++;//��
		node[v2].next_D++;
		sum += 1;//���������µı�
	}
	/*
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	*/
	clock_t start, finish;
	int t = 1000;
	long long answer;
	start = clock();
	while (t--)
	{
		answer = DFS(node, 1, 1);
	}
	finish = clock();
	cout << "the time cost is:" << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	cout << "�ܷ�����:" << answer << endl;
	return 0;
}