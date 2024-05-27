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
int Visit[N+1];   //�������� 
int DN[N+1];     //ÿ�������� 
int VA[N+1];     //father 
int Uset[N+1];   //·��ѹ�� 
vector<int> BFSTree;
int Loop[N+1]; //���� 
vector<int> nodes[N+1]; //�� 

void BFSForTree(int Index)  //���ɶ����ͨ����������ͼ 
{
    queue<int> Q;
    Q.push(Index);
    DN[Index] = 1;
    while(!Q.empty())
    {
        int x = Q.front();       //��ͷ����������������� 
        Q.pop();
        for(int y : nodes[x])
        {
            if(Visit[y]==0)
            {
                Visit[y] = 1;   //�����Է��� 
                VA[y] = x;
                Uset[y] = x;
                DN[y] = DN[x]+1;  //��ȼ�һ 
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
        if(Visit[i]==0)  //���ܶ����ͨƬ 
        {
            Loop[i] = 1;   //���ߵ���� 
            Visit[i] = 1;  //��Ϊ�ѷ��� 
            BFSTree.push_back(i); //BFS���������� 
            BFSForTree(i);
        }
    }
}
void LCA_Uset(int x, int y)
{
    if(x==VA[y]||y ==VA[x]) return;  //�ų��������ı� 
    if(DN[x]<DN[y])   //ʹ��xΪ�������ĵ� 
    {
        x ^= y;
    	y ^= x;
    	x ^= y;
    }
    int tempx = x, tempy= y;  //����·��ѹ�� 
    while(DN[x]>DN[y])  //ʹ��x��������yһ���ĸ߶� 
    {
        Loop[x] = 1; 
        x = Uset[x];
    }
    while(x!=y)  //�ҵ�lca��������������� 
    {
        Loop[x] = 1; 
        x = Uset[x];
        Loop[y] = 1;
        y = Uset[y];
    }
    int LCA = x;
    //����·��ѹ�� 
    while(tempx!=LCA)  
    {
        int tempanc = Uset[tempx]; 
        Uset[tempx] = LCA;      //����Щ��ĸ��ױ�Ϊ����������ȣ������Ϊ����������ȣ�1 
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
void MainForBridge()  //��Ҫ���ú��� 
{
    BFSTraverse();  //ͨ��bfs���������� 
    for(int x : BFSTree)   //���������еĵ� 
    {
        for(int y: nodes[x])//xy����� 
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
	ifstream fin("C://Users/Qk_A/Desktop/temp/ʵ����/largeG.txt");
    fin >> PNums >> LNums; //�������� 
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
	cout<<"����ͼ��.....\n"; 
	LoadFromFile();
	cout<<"�������\n";
	//TestForTrue()      //ΪС���ݲ����㷨��ȷ�� 
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    MainForBridge();
    QueryPerformanceCounter(&EndTime);
	double time = (double)(EndTime.QuadPart-start.QuadPart)/(double)freq.QuadPart;
	cout<<"���鼯+LCA�����\n";
    for(int i = 0 ; i <PNums; i ++)
    {
        if(Loop[i]==0)
        {
            ans ++;
            //cout << VA[i]<<"    "<< i << "����\n"; 
        }
    }
    cout << "����" << ans << "����\n";
    cout<<"���κ�ʱΪ"<<time<<"\n"; 
    return 0;
}


