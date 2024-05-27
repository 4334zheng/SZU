#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
//#define Nodenum 16
//#define Edgenum 15
#define Nodenum 50
#define Edgenum 147


class Graph
{
    vector<vector<int>> adj;
    vector<vector<int>> edge;
    vector<int> father;
    vector<int> tree;
    int visit[Nodenum+1];
    int connectnum;

    int cut1,cut2;
public:
    // 初始化图像 + 计算连通分量个数
    Graph()
    {
        adj.resize(Nodenum + 1);
        edge.resize(Edgenum + 1);
        father.resize(Nodenum+1);
        tree.resize(Nodenum+1);
        cut1 = -1;
        cut2 = -1;
        get_data();
        connectnum = DFS();
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
        if((fl = fopen("D:\\99\\exp5data\\mediumDG.txt","r")) == NULL)
        {
            cout<<"Can not open file!"<<endl;
            exit(1);
        }
        int n1,n2;
        jointset_init();
        for(int i=0;i<Edgenum;i++)
        {
            fscanf(fl,"%d%d",&n1,&n2);

            int f1 = jointset_find(n1);
            int f2 = jointset_find(n2);
            if(f1 != f2)
                father[f2] = f2;


            // 存邻接表
            adj[n1].push_back(n2);
            adj[n2].push_back(n1);
            // 存边集
            edge[i].push_back(n1);
            edge[i].push_back(n2);
        }
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

    // DFS算连通分量数量
    int DFS()
    {
        visit_init();
        int num1 = 0;
        for(int i=0;i<Nodenum;i++)
        {
            if(visit[i] == 0)
            {
                num1++;
                DFS_visit(i);
            }
        }
        return num1;

    }

    void DFS_visit(int k)
    {
        visit[k] = 1;
        int length = adj[k].size();
        for(int i=0;i<length;i++)
        {
            if(visit[adj[k][i]] == 0
            && !(k == cut1 && adj[k][i] == cut2)
            && !(k == cut2 && adj[k][i] == cut1))
                DFS_visit(adj[k][i]);
        }
        visit[k] = 2;
    }
/*-------------------------------------------------------------------------------*/
    // 基准法
    int count_bridge_basic()
    {
        int result=0;
        for(int i=0;i<Edgenum;i++)
        {
            cut1 = edge[i][0];
            cut2 = edge[i][1];
            int after = DFS();
            if(after != connectnum)
                result++;
        }
        return result;
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

//        while (father[x] != x) {
//            father[x] = father[father[x]];
//            x = father[x];
//        }
//        return x;
    }

    // 基准法 + 并查集
    int count_bridge_jointset()
    {
        int bridgenum1 = 0;
        for(int i=0;i<Edgenum;i++)
        {
            // 初始化father
            jointset_init();
            int result = Nodenum;
            for(int j=0;j<Edgenum;j++)
            {
                if (i == j) continue; // 删除第i条边  那么就不算这条边
                int f1 = jointset_find(edge[j][0]);
                int f2 = jointset_find(edge[j][1]);
                if (f1 != f2) father[f1] = f2, result--;
            }
            if(result != connectnum)
                bridgenum1++;
        }
        return bridgenum1;
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

    int bridge_basic_tree()
    {
        visit_init();
        int result = 0;
        int beforc = connectnum;
        vector<vector<int>> tree_edge;
        for(int i=0;i<Nodenum;i++)
        {
            if(visit[i] == 0)
                gettree(i,-1,tree_edge);
        }
        for(int i=0;i<tree_edge.size();i++)
        {
            cut1 = tree_edge[i][0];
            cut2 = tree_edge[i][1];
            int after = DFS();
            if(beforc != after)
                result++;
        }
        return result;
    }

    /*-------------------------------------------------------------------------------*/
    // 基准法 + 并查集 + 生成树法

    // 判断两条边是不是同一条
    bool judge_sample_edge(vector<int> &e1,vector<int> &e2)
    {
        if(e1[0] == e2[0] && e1[1] == e2[1]) return true;
        if(e1[1] == e2[0] && e1[0] == e2[1]) return true;
        return false;
    }

    int count_bridge_jointset_tree()
    {
        visit_init();
        int result = 0;
        int beforc = connectnum;
        vector<vector<int>> tree_edge;
        for(int i=0;i<Nodenum;i++)
        {
            if(visit[i] == 0)
                gettree(i,-1,tree_edge);
        }
        int bridgenum1 = 0;
        for(int i=0;i<tree_edge.size();i++)
        {
            // 初始化father
            jointset_init();
            int result = Nodenum;
            for(int j=0;j<Edgenum;j++)
            {
                if (judge_sample_edge(tree_edge[i],edge[j])) continue; // 删除第i条边  那么就不算这条边
                int f1 = jointset_find(edge[j][0]);
                int f2 = jointset_find(edge[j][1]);
                if (f1 != f2) father[f1] = f2, result--;
            }
            if(result != connectnum)
                bridgenum1++;
        }
        return bridgenum1;
    }

    /*-------------------------------------------------------------------------------*/

    void test()
    {

        double Start ;
        double End ;
        cout << "connectnum: " << connectnum << endl;

        Start = GetTickCount();
        int bridge_basic;
        for(int i=0;i<100;i++)
            bridge_basic = count_bridge_basic();
        End = GetTickCount();
        cout << "bridge_basic: " << bridge_basic << endl;
        cout<<"TimeCost: "<<double((End) - (Start)) / 100 <<"ms"<<endl<<endl;

        Start = GetTickCount();
        int bridge_jointset;
        for(int i=0;i<100;i++)
            bridge_jointset = count_bridge_jointset();
        End = GetTickCount();
        cout<<"bridge_jointset: "<<bridge_jointset<<endl;
        cout<<"TimeCost: "<<((End) - (Start)) / 100<<"ms"<<endl<<endl;

        Start = GetTickCount();
        int basic_tree;
        for(int i=0;i<100;i++)
            basic_tree = bridge_basic_tree();
        End = GetTickCount();
        cout<<"bridge_basic_tree: "<<basic_tree<<endl;
        cout<<"TimeCost: "<<((End) - (Start)) / 100<<"ms"<<endl<<endl;

        Start = GetTickCount();
        int bridge_jointset_tree;
        for(int i=0;i<100;i++)
            bridge_jointset_tree = count_bridge_jointset_tree();
        End = GetTickCount();
        cout<<"bridge_jointset_tree: "<<bridge_jointset_tree<<endl;
        cout<<"TimeCost: "<<((End) - (Start)) / 100<<"ms"<<endl<<endl;
    }
};



int main() {
    Graph my_graph;
    my_graph.test();
}
