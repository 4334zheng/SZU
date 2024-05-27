#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<sstream>
using namespace std;

#define maxv 1000000//������
vector<vector<int>>Node;//�ڽӱ�
vector<int>father;
int vexnum;
int arcnum;
bool* visit;
int** edge;//�߼�
int Del_start;//��ǰ��ɾ�ߵ������յ�
int Del_end;
int Count;//�ŵ�����ͳ��

void init()//��ʼ����������
{
	for (int i = 0; i < vexnum; i++)
		visit[i] = false;
}

void DFS(int v)
{
	visit[v] = true;
	for (int i = 0; i < Node[v].size(); i++)
	{
		if (visit[Node[v][i]] == false && !(v == Del_start && Node[v][i] == Del_end) && !(v == Del_end && Node[v][i] == Del_start)) //û�����ʹ��ұ�δ��ɾ
		{
			DFS(Node[v][i]);
		}
	}
}

int DFSTraverse()//������ͨ����
{
	int ans = 0;
	init();//��ʼ������
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

void DFSCount()//��������
{
	Count = 0;
	int ans_before = DFSTraverse();//ɾ����ǰͼ����ͨ����
	for (int i = 0; i < arcnum; i++)
	{
		//���ݱ�������ѭ������¼��ǰ��ɾ�ߵ������յ�
		Del_start = edge[i][0];
		Del_end = edge[i][1];
		int ans_after = DFSTraverse();
		if (ans_after > ans_before)//���ɾ�ߺ���ͨ���������ӣ��ñ�Ϊ��
		{
			cout << "bridge" << Count + 1 << " " << Del_start << "--" << Del_end << endl;
			Count++;
		}
	}
}

//��׼��+���鼯
void JoinSetInit()
{
	for (int i = 0; i < vexnum; i++) 
		father[i] = i;
}
int JoinSetFind(int v)//���Ҹ��ף������Ҷ������ڼ��ϣ�
{
	if (father[v] == v)
		return v;
	father[v] = JoinSetFind(father[v]);
	return father[v];
}
void JoinSetCount()
{
	int ans_before = DFSTraverse();//ɾ����ǰͼ����ͨ����
	//cout << "ans_before=" << ans_before << endl;
	for (int i = 0; i < arcnum; i++)
	{
		init();//��ʼ��visit
		JoinSetInit();//��ʼ��father
		int res = vexnum;//ͳ�Ƽ�����
		for (int j = 0; j < arcnum; j++)
		{
			if (i == j)
				continue;
			int f1 = JoinSetFind(edge[j][0]);
			int f2 = JoinSetFind(edge[j][1]);
			if (f1 != f2) {
				father[f2] = f1;//�ϲ�
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


void LoadData()//��ȡ�ı��ļ�
{
	//��������ʱ��
	//ifstream fin("C://Users//4334//Desktop//datainfo//test50-100.txt");
	//ifstream fin("C://Users//4334//Desktop//datainfo//test50-200.txt");
	//ifstream fin("C://Users//4334//Desktop//datainfo//test50-300.txt");

	//�Զ���С��ģ������֤�㷨��ȷ��
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
		//�����ڽӱ��洢����Ϣ
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
	cout << "��ͼ���ŵ�����Ϊ��" << Count << endl;
	cout << "the time cost is: " << double(finish - start) << "ms" << endl;
	return 0;
}