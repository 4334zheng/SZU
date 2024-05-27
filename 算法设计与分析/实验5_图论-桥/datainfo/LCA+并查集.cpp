#include<iostream>
#include<time.h>
#include<Queue>
#include<vector>
#include<windows.h>
#include<fstream>
using namespace std;
#define N 1000000
#pragma GCC optimize("O3")
LARGE_INTEGER start,EndTime,freq;
int PNums,LNums;
int ans = 0;
int Visit[N+1];   //访问数组 
int DN[N+1];     //每个点的深度 
int VA[N+1];     //father 
int Uset[N+1];   //路径压缩 
vector<int> BFSTree;
int Loop[N+1]; //环边 
vector<int> nodes[N+1]; //点 

void BFSForTree(int Index)  //生成多个连通分量的生成图 
{
    queue<int> Q;
    Q.push(Index);
    DN[Index] = 1;
    while(!Q.empty())
    {
        int x = Q.front();       //表头弹出，用来广度搜索 
        Q.pop();
        for(int y : nodes[x])
        {
            if(Visit[y]==0)
            {
                Visit[y] = 1;   //置于以访问 
                VA[y] = x;
                Uset[y] = x;
                DN[y] = DN[x]+1;  //深度加一 
                BFSTree.push_back(y);
				Q.push(y);
            }
        }
    }
}

void BFSTraverse()
{
    for(int i = 0; i < PNums; i ++)
    {
        if(Visit[i]==0)  //可能多个连通片 
        {
            Loop[i] = 1;   //环边的起点 
            Visit[i] = 1;  //置为已访问 
            BFSTree.push_back(i); //BFS生成树储存 
            BFSForTree(i);
        }
    }
}
void LCA_Uset(int x, int y)
{
    if(x==VA[y]||y ==VA[x]) return;  //排除生成树的边 
    if(DN[x]<DN[y])   //使得x为深度最深的点 
    {
        x ^= y;
    	y ^= x;
    	x ^= y;
    }
    int tempx = x, tempy= y;  //用来路径压缩 
    while(DN[x]>DN[y])  //使得x上升到与y一样的高度 
    {
        Loop[x] = 1; 
        x = Uset[x];
    }
    while(x!=y)  //找到lca，即最近公共祖先 
    {
        Loop[x] = 1; 
        x = Uset[x];
        Loop[y] = 1;
        y = Uset[y];
    }
    int LCA = x;
    //进行路径压缩 
    while(tempx!=LCA)  
    {
        int tempanc = Uset[tempx]; 
        Uset[tempx] = LCA;      //将这些点的父亲变为最近公共祖先，且深度为最近公共祖先＋1 
        DN[tempx] = DN[LCA]+1;
        tempx = tempanc;
    }
    while(tempy!=LCA)
    {
        int tempanc = Uset[tempy];
        Uset[tempy] = LCA;
        DN[tempy] = DN[LCA]+1;
        tempy = tempanc;
    }
}
void MainForBridge()  //主要调用函数 
{
    BFSTraverse();  //通过bfs建立生成树 
    for(int x : BFSTree)   //在生成树中的点 
    {
        for(int y: nodes[x])//xy代表边 
        {
            LCA_Uset(x,y);
        }
    }
}

/*void TestForTrue()
{
	cin>>PNums>>LNums; 
	for (int i = 0; i < LNums; i++)
    {
    	cin>>v1>>v2;
    	nodes[v1].push_back(v2); 
		nodes[v2].push_back(v1);	
	}
	return ;
} */
void LoadFromFile()
{
	ifstream fin("C://Users/Qk_A/Desktop/temp/实验五/largeG.txt");
    fin >> PNums >> LNums; //点数边数 
    for (int i = 0; i < LNums; i++)
    {
    	int v1, v2;
        fin >> v1 >> v2;
        nodes[v1].push_back(v2); 
		nodes[v2].push_back(v1);	
    }
}
int main()
{
	cout<<"载入图中.....\n"; 
	LoadFromFile();
	cout<<"载入完成\n";
	//TestForTrue()      //为小数据测试算法正确性 
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    MainForBridge();
    QueryPerformanceCounter(&EndTime);
	double time = (double)(EndTime.QuadPart-start.QuadPart)/(double)freq.QuadPart;
	cout<<"并查集+LCA结果：\n";
    for(int i = 0 ; i <PNums; i ++)
    {
        if(Loop[i]==0)
        {
            ans ++;
            //cout << VA[i]<<"    "<< i << "是桥\n"; 
        }
    }
    cout << "共有" << ans << "座桥\n";
    cout<<"本次耗时为"<<time<<"\n"; 
    return 0;
}


