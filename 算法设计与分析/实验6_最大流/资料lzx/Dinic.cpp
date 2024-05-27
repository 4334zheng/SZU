#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include<time.h> 
#include<windows.h>  
#define MAX 1000000
#define INF 0x3f3f3f3f
#include <iostream>
using namespace std;
LARGE_INTEGER start,EndTime,freq;
int h[MAX];//���ڴ洢ÿһ������������ӵ�����һ������;
int EdgeNum = 0;//���ڼ�¼�ߵ���������ס��ÿһ��ƽ�бߵ����һ������;
int Start,VNum;
int Map[1000][1000];//���ڼ�¼������������

struct Node
{
    int from;//ʼ��
    int to;//�յ�
    int flow;//���� 
    int next;//ʼ����һ�����ӱ�
}Edge[MAX];

int Min(int a, int b)
{
    return a < b ? a : b;
}

void AddEdge(int f, int t, int w) //��ӱ� 
{
	EdgeNum++; //����++ 
    Edge[EdgeNum].from = f;
    Edge[EdgeNum].to = t;
    Edge[EdgeNum].flow = w;
    Edge[EdgeNum].next = h[f];//ʼ���ڱ� 
    h[f] = EdgeNum;//��¼��һ��������fΪʼ��ı�
}

int deep[MAX];//�ֲ� 
bool BFS()
{
    memset(deep,0,sizeof(deep));//��ʼ�� 
    deep[Start] = 1;
    std::queue<int> Q;//���� 
    Q.push(Start);
    while(!Q.empty())
    {
        int q = Q.front();
        Q.pop();
        for(int i = h[q]; i != 0; i = Edge[i].next) //(��һ��ʵ��)�տ�ʼ�ӵ�1��ʼ�����Ǵӵ������߿�ʼ��Ȼ�����ǵ�һ���� 
        {
            int to = Edge[i].to; //�ñ��յ� 
            if(deep[to] == 0 && Edge[i].flow != 0) //deepΪ0����������Ϊ0 
            {
                deep[to] = deep[q] + 1;   //�յ���ʼ����ȣ�1 
                if(to == VNum) //������· 
                {
                    return true;
                }
                Q.push(to);
            }
        }
    }
    return deep[VNum] != 0;
}

int DFS(int from, int Flow)//from�ǵ�ǰ�㣬Flow�������������
{
    if(from == VNum)
        return Flow;
    int sum = 0;//sum������¼��һ��from�����ܹ�����������;
    int r = Flow;//r�ڽ��������ڼ�¼��һ��from����һ��������֮�󣬻�ʣ�¶�������������;
    for(int i = h[from]; i && r; i = Edge[i].next)
    {
        int to = Edge[i].to;
        if(deep[to] == deep[from] + 1 && Edge[i].flow != 0)//ֻ�ұȵ�ǰ������� 1�ĵ��������
        {
            int key = DFS(to, Min(r, Edge[i].flow));//�ݹ��ҵ��������Ϊ�����������������������������Ϊr��Ȩֵ����Сֵ;
            if(key == 0)
                deep[to] = 0;//������������������������ô���������;
            Edge[i].flow -= key;
            Edge[i + 1].flow += key;//��i + 1�Ǳ�i�ķ����;
            r -= key;
            sum += key;
        }
    }
    return sum;
}
int CIN()
{
	memset(Map,0,sizeof(Map)); 
	memset(h, 0, sizeof(h));
	Start=1;
	int n,m,a,b;
	cout<<"nλ����: ";
	cin>>n;
	cout<<"mƪ����: ";
	cin>>m;
	cout<<"a: ";
    cin>>a;
    cout<<"b: ";
    cin>>b;
    VNum=2+n+m;
    for(int i=2;i<=n+1;i++) //��һ�� 
    {
    	if(Map[1][i] == 0)
        {
            AddEdge(1,i,b);
            Map[1][i] = EdgeNum;
            AddEdge(i,1,0);
            Map[i][1] = EdgeNum;
        }
        else 
        {
            Edge[Map[1][i]].flow += b;
        }
	}
    for(int i=2;i<=n+1;i++)//�ڶ��� 
    {
    	for(int j=2+n;j<=m+1+n;j++)
    	{
    		if(Map[i][j] == 0)
	        {
	            AddEdge(i,j,1);
	            Map[i][j] = EdgeNum;
	            AddEdge(j,i,0);
	            Map[j][i] = EdgeNum;
	        }
	        else 
	        {
	            Edge[Map[i][j]].flow = 1;
	        }
		}
	}
	for(int i=2+n;i<=m+1+n;i++)
	{
		if(Map[i][VNum] == 0)
	    {
	        AddEdge(i,VNum,a);
	        Map[i][VNum] = EdgeNum;
	        AddEdge(VNum,i,a);
	        Map[i][VNum] = EdgeNum;
	    }
	    else 
	    {
	        Edge[Map[i][VNum]].flow = a;
	    }
		//Map[i][VNum]+=a;
	}   
	return m*a; 
}
int main()
{
	int total;
	total=CIN();
    /*int N,i;
    scanf("%d", &N);//�������;
    Start = 1;
    VNum = N;
    int a, b, c;
    memset(h, 0, sizeof(h));
    memset(Map, 0, sizeof(Map));
    while(scanf("%d%d%d", &a, &b, &c) != EOF)
    {
        if(Map[a][b] == 0)
        {
            AddEdge(a,b,c);
            Map[a][b] = EdgeNum;
            AddEdge(b,a,0);
            Map[b][a] = EdgeNum;
        }
        else 
        {
            Edge[Map[a][b]].flow += c;
        }
    }*/
    int Finalflow = 0;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    while(BFS())
    {
        Finalflow += DFS(Start, INF);
    }
    QueryPerformanceCounter(&EndTime);
	double time = (double)(EndTime.QuadPart-start.QuadPart)/(double)freq.QuadPart;
	cout <<"����ʱ��Ϊ"<<time*1000<<"ms\n";
    cout<<"������ǣ�"<<Finalflow<<"\n";
    if(total<=Finalflow)
    {
    	cout<<"�н�\n";
	}
	else
	{
		cout<<"�޽�\n";
	}
    return 0;
}
/*
6
1 2 16
1 3 13
2 3 10
2 4 12
3 5 14
4 3 9
4 6 20
5 4 7
5 6 4
*/
