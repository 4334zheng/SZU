#include<iostream>
#include<algorithm>
#include<fstream>
#include<assert.h>
#include<string>
#include<sstream>
using namespace std;

#define n 450	//����
#define color_num 5	//��ɫ��
int a[n + 1][n + 1];//�ڽӱ�洢�㼰���ڵ���Ϣ

class Node
{
public:
	int color;//��ǰͿɫ
	int colorEnable[color_num+1];//��ɫ��ѡ״̬��1��ʾ�����ø���ɫ��0����
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
	//string file = "C://users/4334/Desktop/information/le9_4a.txt";
	string file = "C://users/4334/Desktop/information/le450_5a.col";
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
			//��ȡ�ߵ���������
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
			//�����ڽӱ�
			a[v1][0]++;//v1�е�һ��λ�ô���������������֮��ÿһ��λ�ô����������
			a[v1][a[v1][0]] = v2;
			a[v2][0]++;
			a[v2][a[v2][0]] = v1;
			node[v1].next_D++;//��
			node[v2].next_D++;
		}
	}
	infile.close();
	clock_t start, finish;
	int t = 1;
	long long answer;
	start = clock();
	while (t--)
	{
		answer = DFS(node, 1, 1);
	}
	finish = clock();
	cout << "the time cost is:" << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	cout << "�ܷ�����:" <<answer<< endl;
	return 0;
}