#include <iostream>
#include <time.h>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

#define CNum 5    //颜色数
#define Num 450    //点数

class Node 
{
public:
    int color;  //当前颜色 
    int ColorState[CNum + 1];  //颜色状态，1为可选，非1为不可选
    int ColorNum;  //可选颜色数，即ColorState中1的数量
    int NextNum;  //度数 
    Node()   //初始化 
	{
        color = 0;
        for (int i = 0; i < CNum + 1; ++i) 
		{
            ColorState[i] = 1;
        }
        ColorNum = CNum;
        NextNum = 0;
    }
};


int map[Num + 1][Num+1];  //邻接表
int MRV(Node *node)
{
	int min=9999;
	int ans=0;
	for(int i=1;i<=Num;i++)
	{
		if(node[i].color==0) //没访问过的点 
		{
			int min1=node[i].ColorNum; //该点能够染色的种类数 
			if(min>min1)
			{
				min=min1;
				ans=i;
			}
		}	
	}
	return ans;
}
int MRVAndDH(Node *node)
{
	int min=9999;
	int ans;
	for(int i=1;i<=Num;i++)
	{
		if(node[i].color==0) //没染色过的点 
		{
			int min1=node[i].ColorNum; //该点能够染色的种类数
			if(min>min1)
			{
				min=min1;
				ans=i;
			}
			else if(min==min1)//当相同的最小染色数时 
			{
				if(node[i].NextNum>node[ans].NextNum)  //选择度数最大 
				{
					ans=i;
				}
			} 
		}
	}
	return ans;
}
bool front(Node *node,int type,int j,int v)  //向前探查 
{
	node[j].ColorState[type] = -v; //删除该点颜色 
    node[j].ColorNum--;  //该邻接点可染色数目减一 
    node[j].NextNum--;  //该邻接点的相关度数减一 
	if(node[j].ColorNum<=0)  //发现删除节点后没有其他颜色可填 
		return false;
	return true;
	
}
//回溯法主体 
long long DFS(Node *node, int v, int count, int used) 
{
    if (count == Num) //到最后一个点，放回该点的方案数 
    {
        return node[v].ColorNum;
    } 
	else 
	{
        long long ans = 0;
        for (int i = 1; i <= CNum; i++) 
		{
            if (node[v].ColorState[i] == 1) //该点v可以染i色 
			{
                long long tempans = 0;
                node[v].color = i;   //该点颜色记录 
                bool NewColor = i > used;  //是否是新使用的颜色？ 是就为true 反之为false 
                
                for (int k = 1; k <= map[v][0]; ++k) 
				{
                    int j = map[v][k]; //j为邻接的点 
                    if (node[j].color == 0 && node[j].ColorState[i] == 1) //未涂色且该颜色可选 
					{
                        if(front(node,i,j,v)==false)
                        {
                        	goto Recall;  //向前探查发现错误直接回溯 
						}
                    }
                }
                if (NewColor==true)
                    tempans = DFS(node, MRVAndDH(node), count + 1, used + 1);
                else
                    tempans = DFS(node, MRVAndDH(node), count + 1, used);

                Recall:  //数组回溯 
                for (int k = 1; k <= map[v][0]; ++k) 
				{
                    int j = map[v][k];
                    if (node[j].ColorState[i] == -v) //回溯优化 
					{
                        node[j].ColorNum++;//可染数目++ 
                        node[j].NextNum++;//度数++ 
                        node[j].ColorState[i] = 1;//回溯 
                    }
                }
                node[v].color = 0;  //回溯 
                if (NewColor==true) //如果颜色为新 ,轮寻 
				{
                    ans += tempans * (CNum - used);
                    break;
                }
                ans += tempans;
            }
        }
        if (ans>100000000)  //15色  与25色 
		{
			cout<<ans<<"\n";
		}
        return ans;
    }
}

int main() 
{
    Node node[Num + 1];
    fstream open("D://TempProject/le450_5a.col");
    //fstream open("D://TempProject/le450_25a.col");
    //fstream open("D://TempProject/le450_15b.col");
	string line;
	while(getline(open,line))
	{
		if(line[0]=='e') //为map邻接矩阵赋值 
		{
			int i=2;
			string temp1,temp2;
			while(1)
			{
				temp1+=line[i];
				i++;
				if(line[i]<'0'||line[i]>'9')
					break;
			}
			i++;
			while(1)
			{
				temp2+=line[i];
				i++;
				if(line[i]<'0'||line[i]>'9')
					break;
			}
			stringstream stream1(temp1);
			stringstream stream2(temp2);
			int v1,v2;
			stream1>>v1;stream2>>v2;
			//比如 1 330   map[1][0]=1   map[1][1]=330 
			//map[330][0]=1   map[330][1]=1
			map[v1][0]++;
		    map[v1][map[v1][0]] = v2;
		    map[v2][0]++;
		    map[v2][map[v2][0]] = v1;
		    node[v1].NextNum++; //度加一 
		    node[v2].NextNum++;
		    //cout<<v1<<" "<<v2<<"\n";
		}	
	}
    cout << "邻接表赋值完毕" << endl;
    clock_t startTime, endTime; 
	startTime = clock();
    long long a = DFS(node,1, 1, 0);
    endTime = clock();
    cout << "运行时间为" << (endTime - startTime)*1000 / CLOCKS_PER_SEC<<"ms\n";
    cout << "方案数:" << a << "\n";
    return 0;
}





































