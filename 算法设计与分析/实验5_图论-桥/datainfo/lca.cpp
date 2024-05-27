#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define Nodenum 1000000
#define Edgenum 7586063


// hash 函数标记重复边
struct edge_hash
{
    size_t operator() (const vector<int> e1) const
    {
        int a = (e1[0]<e1[1])?(e1[0]):(e1[1]);
        int b = (e1[0]>e1[1])?(e1[0]):(e1[1]);
        return a*2022 + b ;
    }
};

struct edge_cmp
{
    bool operator() (const vector<int> e1,const vector<int> e2) const
    {
        if(e1[0] == e2[0] && e1[1] == e2[1]) return true;
        if(e1[1] == e2[0] && e1[0] == e2[1]) return true;
        return false;
    }
};

class Graph
{
    vector<vector<int>> adj;
    vector<vector<int>> edge;
    vector<int> father;
    vector<int> tree;
    vector<vector<int>> untree;
//    vector<int> height;
    unordered_set<vector<int>,edge_hash,edge_cmp> circle_edge;
    vector<int> height;
    int visit[Nodenum+2];
    int commont_num;
    int untreenum;
    int connectnum;
    int cut1,cut2;
public:
    // 初始化图像 + 计算连通分量个数
    Graph()
    {

        adj.resize(Nodenum + 1);
        edge.resize(Edgenum + 1);
        father.resize(Edgenum);
        tree.resize(Nodenum + 1);
        untree.resize(Edgenum + 1);\
        height.resize(Nodenum+1);
        circle_edge.clear();
        commont_num = 0;
        untreenum = 0;
        cut1 = -1;
        cut2 = -1;
        get_data();
//        connectnum = DFS();

    }

//    void init_all()
//    {
//        for(int i=0;i<Nodenum;i++)
//        {
//            visit[i] = 0; father[i] = i;
//        }
//    }

    // 获取本地数据
    void get_data()
    {
        FILE *fl;
        if((fl = fopen("D:\\99\\exp5data\\largeG.txt","r")) == NULL)
        {
            cout<<"Can not open file!"<<endl;
            exit(1);
        }
        int n1,n2;
        int n11=-1,n22=-1;
        jointset_init();
        for(int i=0;i<Edgenum;i++)
        {
            fscanf(fl,"%d%d",&n1,&n2);
//            cout<<n1<<":"<<n2<<endl;
            if(n1 == n11 && n2 == n22)
            {
                commont_num++;
                continue;
            }
            int f1 = jointset_find(n1);
            int f2 = jointset_find(n2);
            if(f1 != f2)
                father[f2] = f1;
            else
            {
                untreenum++;
                untree[n1].push_back(n2);
                continue;
            }
            // 存邻接表
            adj[n1].push_back(n2);
            adj[n2].push_back(n1);
            // 存边集
            edge[i].push_back(n1);
            edge[i].push_back(n2);
        }
//        for(int i=0;i<Nodenum;i++)
//        {
//            cout<<i<<": ->";
//            for(int j=0;j<adj[i].size();j++)
//                cout<<adj[i][j]<<"->";
//            cout<<endl;
//        }
//        visit_init();
//        for(int i=0;i<Nodenum;i++)
//        {
//            if(visit[i] == 0 && jointset_find(i) == i)
//            {
////                cout<<i<<endl;
//                dfs_getTree(i,i,1);
//            }
//        }
//        for(int i=0;i<Nodenum;i++)
//        {
//            cout<<i<<" : "<<tree[i]<<" : "<<height[i]<<endl;
//        }
    }

    // visit 数组初始化
    void visit_init()
    {
        // visit数组清零
        for(int i=0;i<=Nodenum;i++)
        {
            visit[i] = 0;
        }
    }

/*-------------------------------------------------------------------------------*/
    // father 数组初始化
    void jointset_init()
    {
        for(int i=0;i<Nodenum;i++)
            father[i] = i;
    }

    // 查找父亲
    int jointset_find(int x)
    {
        if(father[x] == x)
            return x;
        int gfather = jointset_find(father[x]);
        father[x] = gfather;
        return gfather;
    }

    /*-------------------------------------------------------------------------------*/
    // 基准法 + 生成树法
    void gettree(int cur,int pre,vector<vector<int>> &t)
    {
        if(pre != -1)
            t.push_back(vector<int>{pre,cur});
        visit[cur] = 1;
        for(int i=0;i<adj[cur].size();i++)
        {
            if(visit[adj[cur][i]] == 0)
                gettree(adj[cur][i],cur,t);
        }
    }


    /*-------------------------------------------------------------------------------*/

    // 判断两条边是不是同一条
    bool judge_sample_edge(vector<int> &e1,vector<int> &e2)
    {
        if(e1[0] == e2[0] && e1[1] == e2[1]) return true;
        if(e1[1] == e2[0] && e1[0] == e2[1]) return true;
        return false;
    }

    /*-------------------------------------------------------------------------------*/

    void dfs_getTree(int start,int direct_father,int hei)
    {
        visit[start] = 1;
        tree[start] = direct_father;
        height[start] = hei;
        for(int i=0;i<adj[start].size();i++)
        {

            if(visit[adj[start][i]] == 0)
            {
                dfs_getTree(adj[start][i],start,hei + 1);
            }
        }
    }

    void lca()
    {
        visit_init();
        for(int i=0;i<Nodenum;i++)
        {
            if(visit[i] == 0 && jointset_find(i) == i)
            {
//                cout<<i<<endl;
                dfs_getTree(i,i,1);
            }
        }
        visit_init();
        for(int i=0;i<Nodenum;i++)
        {
            for(int j=0;j<untree[i].size();j++)
            {
                int x = i;
                int y = untree[i][j];
                if(height[x] != height[y])
                {
                    if(height[x] > height[y])
                    {
                        while(height[x] != height[y])
                        {
                            visit[x] = 1;
                            x = tree[x];
                        }
                    }
                    else if(height[x] < height[y])
                    {
                        while(height[x] != height[y])
                        {
                            visit[y] = 1;
                            y = tree[y];
                        }
                    }
                }
                while(x != y)
                {
                    visit[x] = 1;
                    visit[y] = 1;
                    x = tree[x];
                    y = tree[y];
                }
            }
        }
    }

    void count()
    {
        lca();
        int visitnum = 0;
        for(int i=0;i<Nodenum;i++)
        {
            if(visit[i] == 1)
                visitnum++;
        }
        int bridgenum = Edgenum - commont_num - visitnum - untreenum;
        cout<<bridgenum<<endl;
    }










    void test()
    {
        double Start = GetTickCount();
        count();
        double End = GetTickCount();
        cout<<"TimeCost: "<<End - Start<<endl;
    }
};



int main() {

    Graph my_graph;
    my_graph.test();
    return 0;
}
