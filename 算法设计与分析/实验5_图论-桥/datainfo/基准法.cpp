#include <iostream>
#include <time.h>
#include<fstream>
#include<string>
#include <vector>
#include<sstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
#define max 100    //����
vector<vector<int> > nodes;
int PNums; //�������
int LNums; //�ߵ�����
int DelStart;  //ɾ���ߵ���� 
int DelEnd;   //ɾ���ߵ��յ� 
bool *Visit;
int **Edges;  //�� 
int count;
void DFS(int v)  //�ӵ�v����������ݹ��������ȱ���ͼ 
{
	Visit[v]=true;
	for(int i=0;i<nodes[v].size();i++)
	{
		if(Visit[nodes[v][i]]==false&&!(v == DelStart && nodes[v][i] == DelEnd) &&!(v == DelEnd && nodes[v][i] == DelStart)) //û�����ʹ����б� 
		{
			DFS(nodes[v][i]);
		}
	}
}
void InitForVisit()
{
	for(int i=0;i<PNums;i++)
	{
		Visit[i]=false;
	}
}
int DFSTraverse()  //������ͨ���� 
{
	int ans=0;  
	InitForVisit();  //��ʼ������ 
	for(int i=0;i<PNums;i++)
	{
		if (Visit[i] == 0)
        {
        	DFS(i); 
			ans++;
		}
	}
	return ans;
}
void MainDFS()  //���� 
{
	int BeforeDel = DFSTraverse(); //ɾ��ǰ����ͨ���� 
	for(int i=0;i<LNums;i++)
	{
		DelStart=Edges[i][0];
		DelEnd=Edges[i][1];
		int AfterDel = DFSTraverse();
		if (AfterDel > BeforeDel) 
		{
			count++;
            //cout << DelStart << " -- " << DelEnd << " is bridge\n";
        }
	}
}
void TestForTrue()
{
	cin>>PNums>>LNums;
	Edges=new int*[LNums]; 
    for(int i=0;i<LNums;i++) 
    {
    	Edges[i]=new int [2];
	}
    Visit=new bool[PNums];
	nodes.clear();
    nodes.resize(PNums);
	for (int i = 0; i < LNums; i++)
    {
    	int v1,v2;
    	cin>>v1>>v2;
    	nodes[v1].push_back(v2); 
		nodes[v2].push_back(v1);
		Edges[i][0]=v1;
		Edges[i][1]=v2;		
	}
	return ;
} 
void LoadFromFile()
{
	ifstream fin("C://Users/Administrator/Desktop/��ҵ/�㷨��������/ʵ����/test1.txt");
    fin >> PNums >> LNums; //�������� 
    Edges=new int*[LNums]; 
    for(int i=0;i<LNums;i++) 
    {
    	Edges[i]=new int [2];
	}
    Visit=new bool[PNums];
	nodes.clear();
    nodes.resize(PNums);
    for (int i = 0; i < LNums; i++)
    {
    	int v1, v2;
        fin >> v1 >> v2;
        nodes[v1].push_back(v2); 
		nodes[v2].push_back(v1);
		Edges[i][0]=v1;
		Edges[i][1]=v2;		
    }
}
int main(int argc, char** argv) 
{
    //TestForTrue();  //�Զ�������ͼ����֤�㷨׼ȷ�� 
    count=0;
    LoadFromFile(); //���ļ���ȡͼ 
	MainDFS();
	cout<<"�ܵ�����ĿΪ"<<count; 
}
