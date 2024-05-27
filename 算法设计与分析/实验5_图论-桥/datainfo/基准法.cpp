#include <iostream>
#include <time.h>
#include<fstream>
#include<string>
#include <vector>
#include<sstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
#define max 100    //点数
vector<vector<int> > nodes;
int PNums; //点的数量
int LNums; //边的数量
int DelStart;  //删除边的起点 
int DelEnd;   //删除边的终点 
bool *Visit;
int **Edges;  //边 
int count;
void DFS(int v)  //从第v个顶点出发递归地深度优先遍历图 
{
	Visit[v]=true;
	for(int i=0;i<nodes[v].size();i++)
	{
		if(Visit[nodes[v][i]]==false&&!(v == DelStart && nodes[v][i] == DelEnd) &&!(v == DelEnd && nodes[v][i] == DelStart)) //没被访问过且有边 
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
int DFSTraverse()  //计算连通数量 
{
	int ans=0;  
	InitForVisit();  //初始化数组 
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
void MainDFS()  //主体 
{
	int BeforeDel = DFSTraverse(); //删除前的连通分量 
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
	ifstream fin("C://Users/Administrator/Desktop/作业/算法设计与分析/实验五/test1.txt");
    fin >> PNums >> LNums; //点数边数 
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
    //TestForTrue();  //自定义输入图来验证算法准确性 
    count=0;
    LoadFromFile(); //从文件获取图 
	MainDFS();
	cout<<"总的桥数目为"<<count; 
}
